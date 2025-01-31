import sys
import re
import collections


# The following regexes/regeces/regrets have each one capturing group
R_STR = r'(?:(?<!\\)"' + r'((?:(?!\\|").|\\.|\s)*)' + r'")' # Captures the string content
R_STRS = r'((?:' + R_STR + r'\s*)+)'                        # Captures the series of strings


class CString:
    def _assert(self):
        assert(type(self) == CString)
        assert(type(self.msgid) == str)
        if self.indexes is not None:
            assert(type(self.indexes) == list)
            assert(len(self.indexes) == 2)
            for i in self.indexes:
                assert(type(i) == int)
        if self.msgstr is not None:
            assert(type(self.msgstr) == str)

    def __init__(self, msgid: str, indexes: list[int] | None = None, msgstr: str | None = None):
        self.msgid = msgid
        self.indexes = indexes
        self.msgstr = msgstr
        self._assert()


def parse_c_file(file: str, keyword: str = '_') -> list[CString]:
    assert(type(file) == str)
    assert(type(keyword) == str)
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
        #print(f'STR = {string} = {file[result[-1].indexes[0]:result[-1].indexes[1]]}')

    assert(type(result) == list)
    for i in result:
        assert(type(i) == CString)
        i._assert()
    return result


def parse_translate(trans_file: str):
    r = r'^\s*msgid\s*' + R_STR + r'\s*^\s*msgstr\s*' + R_STR + r'\s*'
    result: list[CString] = []
    for m in re.finditer(r, trans_file, flags=re.M):
        msgid = m.groups()[0]
        msgstr = m.groups()[1]
        result.append(CString(msgid, msgstr=msgstr, indexes=[m.start(0), m.end(0)]))

    assert(type(result) == list)
    for i in result:
        assert(type(i) == CString)
        i._assert()
    return result


def generate_template(cs: list[CString]) -> str:
    assert(type(cs) == list)
    for c in cs:
        assert(type(c) == CString)
        c._assert()

    out = ''
    for c in cs:
        out += f'msgid "{c.msgid}"\n'
        out += f'msgstr ""\n'
        out += '\n'
    assert(type(out) == str)
    return out


def replace_c_file(c_file: str, c_cstrs: list[CString]) -> str:
    assert(type(c_file) == str)
    assert(type(c_cstrs) == list)
    for i in c_cstrs:
        i._assert()


    indexes: dict = dict({})
    for n, c in enumerate(c_cstrs):
        indexes[c.indexes[0]] = n
    # Totally my idea, not from SO, 100%, no cap
    indexes = dict(collections.OrderedDict(sorted(indexes.items())))

    #print(indexes)
    for i in reversed(indexes):
        c = c_cstrs[indexes[i]]
        st = c.indexes[0]
        end = c.indexes[1]
        trans = c.msgstr

        c_file = c_file[:st] + '"' + trans + '"' + c_file[end:]
        #print(f"{st}:{end}: {c_file[st:end]}: {trans}")
    return c_file


def cmd_make_template(c_filepath: str, tmpl_filepath: str):
    assert(type(c_filepath) == str)
    assert(type(tmpl_filepath) == str)

    c_file = open(c_filepath, 'rt')
    c_content = c_file.read()
    c_file.close()
    c_cstrs = parse_c_file(c_content)

    tmpl_file = open(tmpl_filepath, 'wt')
    tmpl_content = generate_template(c_cstrs)
    tmpl_file.write(tmpl_content)
    tmpl_file.close()


def cmd_replace(trans_filepath: str, c_filepath: str):
    assert(type(trans_filepath) == str)
    assert(type(c_filepath) == str)

    trans_file = open(trans_filepath, 'rt')
    trans_content = trans_file.read()
    trans_file.close()
    trans_cstrs = parse_translate(trans_content)

    c_file = open(c_filepath, 'rt')
    c_content = c_file.read()
    c_file.close()
    c_cstrs = parse_c_file(c_content)

    if len(c_cstrs) == len(trans_cstrs):
        for c in trans_cstrs:
            for C in c_cstrs:
                if C.msgid == c.msgid:
                    C.msgstr = c.msgstr
                    break
            else:
                print('Fatal error: translations in C file and translation file do not match', file=sys.stderr)
                sys.exit(1)
    else:
        print('Fatal error: translations in C file and translation file do not match', file=sys.stderr)
        sys.exit(1)
    #for c in c_cstrs:
    #    print(c.__dict__)

    c_content = replace_c_file(c_content, c_cstrs)
    c_file = open(c_filepath, 'wt')
    c_file.write(c_content)
    c_file.close()


def cmd_update_template(c_filepath: str, tmpl_filepath: str):
    assert(type(c_filepath) == str)
    assert(type(tmpl_filepath) == str)

    c_file = open(c_filepath, 'rt')
    c_cstrs = parse_c_file(c_file.read())
    c_file.close()

    tmpl_file = open(tmpl_filepath, 'rt')
    tmpl_content = tmpl_file.read()
    tmpl_cstrs = parse_translate(tmpl_content)
    tmpl_file.close()

    new_msgs: list[CString] = []
    for c in c_cstrs:
        for C in tmpl_cstrs:
            if C.msgid == c.msgid:
                break
        else:
            new_msgs.append(c)
    #for i in new_msgs:
    #    print(i.__dict__)

    unused_msgs: list[CString] = []
    for c in tmpl_cstrs:
        for C in c_cstrs:
            if C.msgid == c.msgid:
                break
        else:
            unused_msgs.append(c)
    #for i in unused_msgs:
    #    print(i.__dict__)

    if len(unused_msgs) == 0:
        print('Note: nothing to remove!')
    else:
        for m in unused_msgs:
            #print(m.__dict__)
            #print(tmpl_content[m.indexes[0]:m.indexes[1]])
            tmpl_content = tmpl_content[:m.indexes[0]] + tmpl_content[m.indexes[1]:]
        tmpl_file = open(tmpl_filepath, 'wt')
        tmpl_file.write(tmpl_content)
        tmpl_file.close()
        print(f'Note: {len(unused_msgs)} messages removed')

    if len(new_msgs) == 0:
        print('Note: nothing to add!')
    else:
        tmpl_content = '\n' + generate_template(new_msgs)
        tmpl_file = open(tmpl_filepath, 'at')
        tmpl_file.write(tmpl_content)
        tmpl_file.close()
        print(f'Note: {len(new_msgs)} messages added')


def cmd_update_translation(tmpl_filepath: str, trans_filepath: str):
    assert(type(tmpl_filepath) == str)
    assert(type(trans_filepath) == str)

    tmpl_file = open(tmpl_filepath, 'rt')
    tmpl_cstrs = parse_translate(tmpl_file.read())
    tmpl_file.close()

    trans_file = open(trans_filepath, 'rt')
    trans_content = trans_file.read()
    trans_cstrs = parse_translate(trans_content)
    trans_file.close()

    new_msgs: list[CString] = []
    for c in tmpl_cstrs:
        for C in trans_cstrs:
            if C.msgid == c.msgid:
                break
        else:
            new_msgs.append(c)
    #for i in new_msgs:
    #    print(i.__dict__)

    unused_msgs: list[CString] = []
    for c in trans_cstrs:
        for C in tmpl_cstrs:
            if C.msgid == c.msgid:
                break
        else:
            unused_msgs.append(c)
    #for i in unused_msgs:
    #    print(i.__dict__)

    if len(unused_msgs) == 0:
        print('Note: nothing to remove!')
    else:
        for m in unused_msgs:
            #print(m.__dict__)
            #print(trans_content[m.indexes[0]:m.indexes[1]])
            trans_content = trans_content[:m.indexes[0]] + trans_content[m.indexes[1]:]
        trans_file = open(trans_filepath, 'wt')
        trans_file.write(trans_content)
        trans_file.close()
        print(f'Note: {len(unused_msgs)} messages removed')

    if len(new_msgs) == 0:
        print('Note: nothing to add!')
    else:
        trans_content = '\n' + generate_template(new_msgs)
        trans_file = open(trans_filepath, 'at')
        trans_file.write(trans_content)
        trans_file.close()
        print(f'Note: {len(new_msgs)} messages added')


def main():
    if len(sys.argv) <= 1:
        print('Usage: <command> [<subcommand>] [<args...>]')
        print('Commands:')
        print('\tmake template <c_filepath> <outout template filepath>')
        print('\treplace <trans filepath> <c filepath>')
        print('\tupdate template <trans filepath> <c filepath>')
        print('\tupdate translation <template filepath> <translation filepath>')
        print('')
        return
    command = sys.argv[1]
    command_func = None
    
    if command == 'make':
        if len(sys.argv) <= 2:
            print('\tmake <subcommand>')
            print('Subcommands:')
            print('\ttemplate <c filepath> <output template filepath>')
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
    elif command == 'replace':
        if len(sys.argv) <= 3:
            print('Fatal error: required inputs not given', file=sys.stderr)
            sys.exit(1)
        c_file = sys.argv[2]
        trans_file = sys.argv[3]
        cmd_replace(trans_file, c_file)
    elif command == 'update':
        if len(sys.argv) <= 2:
            print('\tmake template <subcommand>')
            print('Subcommands:')
            print('\ttemplate <c_filepath> <template filepath>')
            print('\ttranslation <template filepath> <translation path>')
            print('')
            return
        subcommand = sys.argv[2]

        if subcommand == 'template':
            if len(sys.argv) <= 4:
                print('Fatal error: required inputs not given', file=sys.stderr)
                sys.exit(1)
            c_file = sys.argv[3]
            tmpl_file = sys.argv[4]
            cmd_update_template(c_file, tmpl_file)
        if subcommand == 'translation':
            if len(sys.argv) <= 4:
                print('Fatal error: required inputs not given', file=sys.stderr)
                sys.exit(1)
            tmpl_file = sys.argv[3]
            trans_file = sys.argv[4]
            cmd_update_translation(tmpl_file, trans_file)
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
