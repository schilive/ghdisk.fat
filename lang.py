#!/usr/bin/env python3

import sys

G_C_SPACE_CHARACTERS = set([" ", "\t", "\v", "\n"])
G_PO_SPACE_CHARACTERS = set([" ", "\t", "\v"])

# Implementation-Specific
G_FILE_ENCODING = "ascii"
G_KEYWORD = "STR_TRN"


class CId:
    def __init__(self, content, begin, end):
        self.content = content
        self.begin = begin
        self.end = end


def replace_all(target, indeces, replacements):
    while len(indeces) != 0:
        furthest_indeces_index = 0
        for i in range(1, len(indeces)):
            if indeces[i][0] > furthest_indeces_index[0]:
                furthest_indeces_index = i
        begin_index = indeces[furthest_indeces_index][0]
        end_index = indeces[furthest_indeces_index][1]
        replacement = "\"" + replacements[furthest_indeces_index] + "\""

        target = target[:begin_index] + replacement + target[end_index + 1:]

        indeces.pop(furthest_indeces_index)
        replacements.pop(furthest_indeces_index)
    return target


def print_fatal(message):
    print("Fatal error: " + message, file=sys.stderr)


# Returns a list of 'CId's with all translation identifiers and their begining and ending indeces.
def parse_c(file):
    # <keyword> <space*>

    offset = 0
    result = []
    while True:
        begin = file.find(G_KEYWORD, offset)
        if begin == -1:
            break
        offset = begin + len(G_KEYWORD)

        while file[offset] in G_C_SPACE_CHARACTERS:
            offset += 1

        #assert(file[offset] == "(")
        offset += 1

        while file[offset] in G_C_SPACE_CHARACTERS:
            offset += 1

        #assert(file[offset] == "\"")
        offset += 1

        string = ""
        while file[offset] != "\"":
            if file[offset] == "\\" and file[offset + 1] == "\"":
                offset += 1
            string += file[offset]
            offset += 1

        #assert(file[offset] == "\"")
        offset += 1

        while file[offset] in G_C_SPACE_CHARACTERS:
            offset += 1

        #assert(file[offset] == ")")
        offset += 1

        result.append(CId(string, begin, offset - 1))
        continue
    return result


# Returns dict[str, str]
def parse_po(file):
    result = dict([])
    lines = file.split("\n")
    msgid = None
    for l in lines:
        offset = 0
        while offset < len(l) and l[offset] in G_PO_SPACE_CHARACTERS:
            offset += 1
        if offset == len(l):
            continue
        # Else it is a <command>
        
        while l[offset] in G_PO_SPACE_CHARACTERS:
            offset += 1

        name = ""
        while l[offset] not in G_PO_SPACE_CHARACTERS:
            name += l[offset]
            offset += 1
        
        while l[offset] in G_PO_SPACE_CHARACTERS:
            offset += 1

        #assert(l[offset] == "\"")
        offset += 1

        parameter = ""
        while True:
            if l[offset] == "\"":
                break
            if l[offset] == "\\" and l[offset] == "\"":
                offset += 1
            parameter += l[offset]
            offset += 1
        
        #assert(l[offset] == "\"")
        offset += 1

        while offset < len(l) and l[offset] in G_PO_SPACE_CHARACTERS:
            offset += 1

        if offset < len(l):
            #assert(l[offset] = "\n")
            offset += 1

        if name == "msgid":
            msgid = parameter
            continue
        #assert(name == "msgstr")
        result[msgid] = parameter
    return result


# Returns the string
def generate_pot(ids):
    result = ""
    for i in ids:
        result += "msgid \"" + i + "\""
        result += "\n"
        result += "msgstr \"\""
        result += "\n"
    return result


def cmd_create_pot(argv):
    if len(argv) < 3:
        print_fatal("Not enough arguments given")
        return 1

    file_in_object = open(
        argv[1], 
        mode="rt", 
        encoding=G_FILE_ENCODING,
        errors="strict"
    )
    file_in_content = file_in_object.read()
    file_in_object.close()

    cids = parse_c(file_in_content)
    ids = []
    for i in cids:
        ids.append(i.content)

    file_out_object = open(
        argv[2], 
        mode="wt", 
        encoding=G_FILE_ENCODING, 
        errors="strict"
    )
    file_out_content = file_out_object.write(generate_pot(ids))
    file_out_object.close()
    return 0


def cmd_create_po(argv):
    if len(argv) < 3:
        print_fatal("Not enough arguments given")
        return 1
    
    file_in_object = open(argv[1], "rb")
    file_out_object = open(argv[2], "wb")
    file_out_object.write(file_in_object.read())
    file_out_object.close()
    file_in_object.close()
    return 0


def cmd_apply_po(argv):
    if len(argv) < 4:
        print_fatal("Not enough arguments given")
        return 1
    file_po_name = argv[1]
    file_c_name = argv[2]
    file_out_name = argv[3]

    file_po_object = open(
        file_po_name, 
        mode="rt", 
        encoding=G_FILE_ENCODING,
        errors="strict"
    )
    file_po_content = file_po_object.read()
    file_po_object.close()
    file_c_object = open(
        file_c_name, 
        mode="rt", 
        encoding=G_FILE_ENCODING,
        errors="strict"
    )
    file_c_content = file_c_object.read()
    file_c_object.close()

    cids = parse_c(file_c_content)
    trans = parse_po(file_po_content)

    replace_indeces = []
    replace_replacements = []
    for i in cids:
        replace_indeces += [[i.begin, i.end]]
        replace_replacements.append(trans[i.content])
    file_out_content = replace_all(file_c_content, replace_indeces, replace_replacements)

    file_out_object = open(
        file_out_name, 
        mode="wt", 
        encoding=G_FILE_ENCODING,
        errors="strict"
    )
    file_out_object.write(file_out_content)
    file_out_object.close()

    return 0


def main(argv):
    command = None
    if len(argv) < 2:
        print_fatal("No command given")
        return 1
    command = argv[1]

    if command == "create_pot":
        return cmd_create_pot(argv[1:])
    elif command == "create_po":
        return cmd_create_po(argv[1:])
    elif command == "apply_po":
        return cmd_apply_po(argv[1:])
    print_fatal("Unknown command given: '" + command + "'")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv))
