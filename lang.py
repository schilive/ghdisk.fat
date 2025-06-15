#!/usr/bin/env python3

import sys
import enum

G_PO_C_CHARACTERS = set(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                         'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                         'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4',
                         '5', '6', '7', '8', '9', '!', '#', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', ';', '<',
                         '=', '>', '?', '[', ']', '^', '_', '{', '|', '}', '~', ' ', ':'])

G_C_SPACE_CHARACTERS = set([" ", "\t", "\v", "\n"])
G_PO_SPACE_CHARACTERS = set([" ", "\t", "\v"])

G_C_PUNCTUATORS_1 = set(["[", "]", "(", ")", "*", ",", ":", "=", ";," "#"])
G_C_PUNCTUATORS_3 = set(["..."])
G_C_OPERATORS_1 = set(["[", "]", "(", ")", ".", "+", "-", "&", "*", "~", "!", "/", "%", "<", ">", "=", "^", "|", "?",
                       ":", ",", "#"])
G_C_OPERATORS_2 = set(["->", "++", "--", "&&", "<<", ">>", "<=", ">=", "==", "!=", "||", "*=", "/=", "%=", "-=", "&=",
                       "|=", "^=", "##"])
G_C_OPERATORS_3 = set(["<<=", ">>="])

# Implementation-Specific
G_FILE_ENCODING = "ascii"
G_KEYWORD = "STR_TRN"


@enum.unique
class CContext(enum.Enum):
    COMMENT = enum.auto()
    CODE = enum.auto()


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


def is_valid_c_string(string):
    offset = 0
    while offset != len(string):
        if string[offset] in G_PO_C_CHARACTERS:
            offset += 1
            continue
        if string[offset] == "\\":
            if len(string) - offset >= 2 and string[offset + 1] in {"\"", "\'"}:
                offset += 2
                continue
            print_fatal("Backslash character does not follow either <\"> or <\'>")
            return False
        print_fatal("Unsupported character used: \"" + string[offset] + "\"")
        return False
    return True


# Join lines which end in "\"
def join_backslash_lines(file):
    lines = file.split("\n")
    result = ""
    for l in lines:
        result += l + "\n"

        if len(l) == 0:
            continue
        if l[-1] == "\\":
            result = result[:-2]
    #assert(result[-1] == "\n")
    if file[-1] != "\n":
        result = result[:-1]
    return result


# Returns the file's content without the and preprocessor directives
def remove_c_preprocessor(file):
    lines = file.split("\n")
    result = ""

    for l in lines:
        # We can safely ignore empty lines
        if len(l) == 0:
            continue

        offset = 0
        while len(l) - offset >= 1 and l[offset] in G_C_SPACE_CHARACTERS:
            offset += 1
        # We can safely ignore lines with only space characters
        if len(l) - offset == 0:
            continue

        if l[0] == "#":
            continue
        result += l + "\n"
    if file[-1] != "\n":
        result = result[:-1]
    file = result
    return result

# Assumes 'remove_c_preprocessor()'.
# Igores comments.
# Returns None if there is no next token, otherwise returns CId.
def get_next_c_token_real(file, offset):
    if len(file) == offset:
        return None

    if file[offset] in G_C_SPACE_CHARACTERS:
        while len(file) != offset and file[offset] in G_C_SPACE_CHARACTERS:
            offset += 1
        return get_next_c_token_real(file, offset)
    if len(file) - offset >= 2 and file[offset:offset + 2] == "/*":
        offset += 2
        end_comment = file.find("*/", offset)
        if end_comment == -1:
            return None
        offset = end_comment + 2
        return get_next_c_token_real(file, offset)

    # Clusters
    if len(file) - offset >= 3 and file[offset:offset + 3] in G_C_PUNCTUATORS_3:
        return CId(file[offset:offset + 3], offset, offset + 2)
    elif len(file) - offset >= 3 and file[offset:offset + 3] in G_C_OPERATORS_3:
        return CId(file[offset:offset + 3], offset, offset + 2)
    elif len(file) - offset >= 2 and file[offset:offset + 2] in G_C_OPERATORS_2:
        return CId(file[offset:offset + 2], offset, offset + 1)
    elif file[offset] in G_C_PUNCTUATORS_1:
        return CId(file[offset:offset + 1], offset, offset)
    elif file[offset] in G_C_OPERATORS_1:
        return CId(file[offset:offset + 1], offset, offset)

    # Strings
    if file[offset] == "\"":
        end_string = offset + 1
        while True:
            end_string = file.find("\"", end_string)
            if file[end_string - 1] == "\\":
                end_string += 1
                continue
            if end_string == -1:
                return None
            break
        return CId(file[offset:end_string + 1], offset, end_string)

    # Identifiers
    token = ""
    end_token = offset
    while True:
        if len(file) == offset:
            break
        if file[end_token] in G_C_OPERATORS_1:
            break
        if file[end_token] in G_C_PUNCTUATORS_1:
            break
        if file[end_token] in G_C_SPACE_CHARACTERS:
            break
        end_token += 1
    return CId(file[offset:end_token], offset, end_token - 1)

# Returns a list of 'CId's with all translation identifiers and their begining and ending indeces.
# Validates that the strings are <C string>
def parse_c_and_validate(file):
    file = join_backslash_lines(file)
    file = remove_c_preprocessor(file)

    result = []
    tokens = [None] * 4
    offset = 0
    for i in range(0, 4):
        token = get_next_c_token_real(file, offset)
        if token == None:
            return []
        tokens[i] = token
        offset = token.end + 1

    while True:
        if\
            tokens[0].content == G_KEYWORD and\
            tokens[1].content == "(" and\
            tokens[2].content[0] == "\"" and\
            tokens[3].content == ")"\
        :
            result.append(CId(tokens[2].content[1:-1], tokens[0].begin, tokens[-1].end))
            if not is_valid_c_string(result[-1].content):
                print_fatal("String at line " + str(file[:offset].count("\n") + 1) + "is invalid")
                exit(1)

        token = get_next_c_token_real(file, offset)
        if token == None:
            break
        for i in range(1, len(tokens)):
            tokens[i - 1] = tokens[i]
        tokens[-1] = token
        offset = token.end + 1
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

    cids = parse_c_and_validate(file_in_content)
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

    cids = parse_c_and_validate(file_c_content)
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
