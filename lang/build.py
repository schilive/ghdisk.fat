import sys
import re


# The following regexes/regeces/regrets have each one capturing group
R_STR = r'(?:(?<!\\)"' + r'((?:(?!\\|").|\\.|\s)*)' + r'")' # Captures the string content
R_STRS = r'((?:' + R_STR + r'\s*)+)'                        # Captures the series of strings


class CString:
    def __init__(self, msgid: str, indexes: list[int]):
        self.msgid = msgid
        self.indexes = indexes


def parse_c_file(file: str, keyword: str = '_') -> list[CString]:
    r = rf'\b{keyword}\b\s*(?:\(+)\s*{R_STRS}\s*(?:\)+)\s*(?=[,)])'

    strings: set[str] = []
    result: list[CString] = []
    for m_strs in re.finditer(r, file):
        ms_strs = m_strs.groups()[0]
        string = ""
        for ms_str in re.findall(R_STR, ms_strs):
            string += ms_str
        if string in strings:
            continue
        strings.append(string)
        result.append(CString(string, [m_strs.start(0), m_strs.end(0)]))
        print(f'STR = {string} = {file[result[-1].indexes[0]:result[-1].indexes[1]]}')
    return result


def generate_template(cs: list[CString]) -> str:
    out = ''
    for c in cs:
        out += f'msgid "{c.msgid}"\n'
        out += f'msgstr ""\n'
        out += '\n'
    return out


def cmd_make_template(c_filepath: str, tmpl_filepath: str):
    c_file = open(c_filepath, 'rt')
    c_content = c_file.read()
    c_file.close()
    c_cstrs = parse_c_file(c_content)

    tmpl_file = open(tmpl_filepath, 'wt')
    tmpl_content = generate_template(c_cstrs)
    tmpl_file.write(tmpl_content)
    tmpl_file.close()


def main():
    if len(sys.argv) <= 1:
        print('Usage: <command> [<subcommand>] [<args...>]')
        print('Commands:')
        print('\tmake template <c_filepath> <outout template filepath>')
        print('')
        return
    command = sys.argv[1]
    command_func = None
    
    if command == 'make':
        if len(sys.argv) <= 2:
            print('\tmake template <c_filepath> <outout template filepath>')
            print('Subcommands:')
            print('\ttemplate')
            print('')
            return
        subcommand = sys.argv[2]

        if subcommand == 'template':
            if len(sys.argv) <= 4:
                print('Fatal error: required inputs not given', file=sys.stderr)
                sys.exit(1)
            c_file = sys.argv[3]
            tmpl_file = sys.argv[4]
            cmd_make_template(c_file, tmpl_file)
        else:
            print(f'Fatal error: unknown subcommand: \'{subcommand}\'',file=sys.stderr)
            sys.exit(1)
    else:
        print(f'Fatal error: unknown command: \'{command}\'',file=sys.stderr)
        sys.exit(1)

    return


if __name__ == '__main__':
    main()
    sys.exit(0)
