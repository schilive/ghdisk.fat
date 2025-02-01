import sys
import re


G_KEYWORD = '_'
# The following regexes/regeces/regrets have each one capturing group
R_STR = r'(?:(?<!\\)"' + r'((?:(?!\\|").|\\.|\s)*)' + r'")'             # Captures the string content
R_STRS = r'((?:' + R_STR + r'\s*)+)'                                    # " the series of strings
R_CSTRS = rf'\b{G_KEYWORD}\b\s*(?:\(+)\s*{R_STRS}\s*(?:\)+)\s*(?=[,)])'   # " " " " " as the 1st parm in the func keyword


class CString:
    def set_string(self, string: str):
        assert(type(string) == str)
        self.string = string

    def set_location(self, location: list[int]):
        assert(type(location) == list)
        assert(len(location) == 2)
        for i in location:
            assert(type(i) == int)
        location[1] >= location[0]
        self.location = location

    def __init__(self, string: str, location: list[int]):
        self.set_string(string)
        self.set_location(location)


class CStrings:
    def add(self, c: CString):
        assert(type(c) == CString)
        self.list.append(c)
        if c.string in self.strings:
            self.strings[c.string].append(c)
        else:
            self.strings[c.string] = [c]

    def __init__(self, cs: list[CString] = None):
        if cs is None:
            cs = []
        self.list = []
        self.strings = dict({})
        for c in cs:
            self.add(c)
    

def parse_c_file(content: str) -> CStrings:
    assert(type(content) == str)

    result: CStrings = CStrings()
    for m_strs in re.finditer(R_CSTRS, content):
        strs = m_strs.groups()[0]
        start = m_strs.start()
        end = m_strs.end()
        string = ""
        for m_str in re.findall(R_STR, strs):
            string += m_str
        #print(f'STR = {string} = {content[start:end]}')
        result.add(CString(string, [start, end]))
    return result


def generate_pot(cs: CStrings) -> str:
    assert(type(cs) == CStrings)
    r = ''
    for msgid in cs.strings:
        r += f'msgid "{msgid}"\n'
        r += 'msgstr ""\n'
        r += '\n'
    return r


def cmd_make_pot(c_filepath: str, pot_filepath: str):
    assert(type(c_filepath) == str)
    assert(type(pot_filepath) == str)

    c_file = open(c_filepath, 'rt')
    c_content = c_file.read()
    c_file.close()

    c_cs = parse_c_file(c_content)
    pot_content = generate_pot(c_cs)

    pot_file = open(pot_filepath, 'wt')
    pot_file.write(pot_content)
    pot_file.close()


def main():
    if len(sys.argv) <= 1:
        print('Usage: <command> [<args...>]')
        print('Commands:')
        print('\tmake_pot <c_file> <pot_file>')
        print('')
        sys.exit(0)
    command = sys.argv[1]
    command_argv = sys.argv[2:]

    if command == 'make_pot':
        if len(command_argv) < 2:
            print('Fatal error: required arguments not given', file=sys.stderr)
            sys.exit(1)
        elif len(command_argv) > 2:
            print('Fatal error: too many argument given', file=sys.stderr)
            sys.exit(1)
        c_file = command_argv[0]
        pot_file = command_argv[1]
        cmd_make_pot(c_file, pot_file)
    else:
        print(f'Fatal error: unknown command: \'{command}\'', file=sys.stderr)
        sys.exit(1)
    sys.exit(0)


if __name__ == '__main__':
    main()
