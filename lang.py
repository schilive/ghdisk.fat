#!/usr/bin/env python3

import sys

G_C_SPACE_CHARACTERS = set([" ", "\t", "\v", "\n"])

# Implementation-Specific
G_FILE_ENCODING = "ascii"
G_KEYWORD = "STR_TRN"


def print_fatal(message):
    print("Fatal error: " + message, file=sys.stderr)


# Returns a set (literally type "set") with all the translation identifiers
def parse_c(file):
    # <keyword> <space*>

    offset = 0
    result = set([])
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

        while file[offset] in G_C_SPACE_CHARACTERS:
            offset += 1

        #assert(file[offset] == ")")
        offset += 1

        result = result.union(set([string]))
        continue
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
    if len(argv) <= 2:
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

    ids = parse_c(file_in_content)

    file_out_object = open(
        argv[2], 
        mode="wt", 
        encoding=G_FILE_ENCODING, 
        errors="strict"
    )
    file_out_content = file_out_object.write(generate_pot(ids))
    file_out_object.close()
    return 0


def main(argv):
    command = None
    if len(argv) <= 1:
        print_fatal("No command given")
        return 1
    command = argv[1]

    if command == "create_pot":
        return cmd_create_pot(argv[1:])
    print_fatal("Unknown command given: '" + command + "'")
    return 1


if __name__ == "__main__":
    sys.exit(main(sys.argv))
