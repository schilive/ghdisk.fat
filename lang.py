import sys
import re


G_KEYWORD = '_'
# The following regexes/regeces/regrets have each one or more capturing groups
R_STR = r'(?:(?<!\\)"' + r'((?:(?!\\|").|\\.|\s)*)' + r'")' # Captures the string content
R_STRS = r'((?:' + R_STR + r'\s*)+)'                        # " the series of strings
R_CSTRS = r'\b' + G_KEYWORD + r'\b\s*(?:\(+)\s*'\
    + R_STRS + r'\s*(?:\)+)\s*(?=[,)])'                     # " " " " " as the 1st parm in the func keyword

# The following regexes contain a string
R_MTCMT = r'(?:(?:^|\n)(?!\n)\s*?#, empty(?!\n)\s*?(?=(?:$|\n)))'
R_MSGID = r'(?:(?:^|\n)(?!\n)\s*?msgid(?!\n)\s+' + R_STR + r'(?!\n)\s*?(?=(?:$|\n)))'
R_MSGSTR = r'(?:(?:^|\n)(?!\n)\s*?msgstr(?!\n)\s+' + R_STR + r'(?!\n)\s*?(?=(?:$|\n)))'


class CString:
    def set_string(self, string):
        assert(type(string) == str)
        self.string = string

    def set_location(self, location):
        assert(type(location) == list)
        assert(len(location) == 2)
        for i in location:
            assert(type(i) == int)
        location[1] >= location[0]
        self.location = location

    def __init__(self, string, location):
        self.set_string(string)
        self.set_location(location)


class CStrings:
    def add(self, c):
        assert(type(c) == CString)
        self.list.append(c)
        if c.string in self.strings:
            self.strings[c.string].append(c)
        else:
            self.strings[c.string] = [c]

    def __init__(self, cs = None):
        if cs is None:
            cs = []
        self.list = []
        self.strings = dict({})
        for c in cs:
            self.add(c)


class PotString:
    def set_msgid(self, msgid):
        assert(type(msgid) == str)
        self.msgid = msgid

    def set_msgstr(self, msgstr):
        assert(type(msgstr) == str)
        self.msgstr = msgstr

    def set_location(self, location):
        assert(type(location) == list)
        assert(len(location) == 2)
        for i in location:
            assert(type(i) == int)
        location[1] >= location[0]
        self.location = location

    def __init__(self, msgid, msgstr, location):
        self.set_msgid(msgid)
        self.set_msgstr(msgstr)
        self.set_location(location)


class PotStrings:
    def add(self, p):
        assert(type(p) == PotString)
        assert(p.msgid not in self.dict)
        self.dict[p.msgid] = p

    def __init__(self, ps = None):
        if ps is None:
            ps = []
        self.dict = dict({})
        for p in ps:
            self.add(p)
    

def parse_c_file(content):
    assert(type(content) == str)

    result = CStrings()
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


def parse_pot(content: str, allow_empty: bool = True) -> PotStrings:
    assert(type(content) == str)

    line_feeds = [m.start() for m in re.finditer(r'\n', content)]
    line_starts = []
    if len(content) != 0:
        line_starts.append(0)
    for lf in line_feeds:
        line_starts.append(lf + 1)

    result = PotStrings()

    msgid = None
    msgstr = None
    empty_comment = False
    message_block_offset = 0
    for ln, ls in enumerate(line_starts):
        # The function str.find() returns -1 if it fails to find. Pretty handy.
        le = content.find('\n', ls)
        l = content[ls:le]

        if re.match(r'^\s*?$', l) is not None:
            continue
        
        m = re.match(R_MSGID, l)
        if m is not None:
            msgid = m.groups()[0]
            continue

        if re.match(R_MTCMT, l) is not None:
            empty_comment = True
            continue

        m = re.match(R_MSGSTR, l)
        if m is None:
            print('Fatal error: bad PO/POT file: unknown command in line \'' + str(ln + 1) + '\'',file=sys.stderr)
            sys.exit(1)
        if msgid is None:
            print('Fatal error: bad PO/POT file: command \'msgstr\' is not used after a \'msgid\'',file=sys.stderr)
            sys.exit(1)
        if msgid in result.dict:
            print('Fatal error: bad PO/POT file: message is translated twice: msgid = \'' + msgid + '\'',file=sys.stderr)
            sys.exit(1)
        msgstr = m.groups()[0]
        if not allow_empty and msgstr == '' and not empty_comment:
            print('Fatal error: bad PO/POT file: msgstr is empty: msgid = \'' + msgid + '\'',file=sys.stderr)
            sys.exit(1)

        result.add(PotString(msgid, msgstr, [message_block_offset, le + 1]))
        msgstr = None
        empty_comment = False
        message_block_offset = le + 1
    return result


def generate_pot(msgids):
    assert(type(msgids) == list)
    for i in msgids:
        assert(type(i) == str)
    r = ''
    for msgid in msgids:
        r += 'msgid "' + msgid + '"\n'
        r += 'msgstr ""\n'
        r += '\n'
    return r


def cmd_make_pot(c_filepath, pot_filepath):
    assert(type(c_filepath) == str)
    assert(type(pot_filepath) == str)

    c_file = open(c_filepath, 'rt')
    c_content = c_file.read()
    c_file.close()

    c_cs = parse_c_file(c_content)
    pot_content = generate_pot(list(c_cs.strings.keys()))

    pot_file = open(pot_filepath, 'wt')
    pot_file.write(pot_content)
    pot_file.close()


def cmd_replace_c_file(pot_filepath, c_filepath, original_c_filepath=None):
    assert(type(c_filepath) == str)
    assert(type(pot_filepath) == str)

    c_file = open(c_filepath, 'rt')
    c_content = c_file.read()
    c_file.close()
    c_cs = parse_c_file(c_content)

    if original_c_filepath is not None:
        original_c_file = open(original_c_filepath, 'rt')
        original_c_content = original_c_file.read()
        original_c_file.close()
        original_c_cs = parse_c_file(original_c_content)

        if set(original_c_cs.strings.keys()) != set(c_cs.strings.keys()):
            print('Fatal error: original C file and C file have different translatable strings',file=sys.stderr)
            sys.exit(1)
        for msgid in original_c_cs.strings:
            if len(original_c_cs.strings[msgid]) != len(c_cs.strings[msgid]):
                print('Fatal error: original C file and C file have different number of occurences of the same message:'
                      + ' -->msgid = \'' + msgid + '\'', file=sys.stderr)
                sys.exit(1)

    pot_file = open(pot_filepath, 'rt')
    pot_content = pot_file.read()
    pot_file.close()
    pot_ps = parse_pot(pot_content, allow_empty=False)
    del pot_content
    #print(pot_ps.__dict__)

    # We need to sort otherwise the location may become incorrect.
    #
    # For example, if we have the file 'ab cd' and the locations [[0, 1], [3, 4]], then if we first substitute the first
    # location to 'pt_ab', we will have 'pt_ab cd'. Then if we try to substitute the second location to 'pt_cd', we will
    # have 'pt_pt_cd'.
    c_cs.list.sort(key=lambda x: x.location[0], reverse=True)
    for c in c_cs.list:
        if c.string not in pot_ps.dict:
            continue
        p = pot_ps.dict[c.string]
        c_content = c_content[:c.location[0]] + '"' + p.msgstr + '"' + c_content[c.location[1]:]

    c_file = open(c_filepath, 'wt')
    c_file.write(c_content)
    c_file.close()


def cmd_update_pot(c_filepath, pot_filepath, dry = False):
    assert(type(c_filepath) == str)
    assert(type(pot_filepath) == str)
    changed = False

    c_file = open(c_filepath, 'rt')
    c_content = c_file.read()
    c_file.close()

    c_cs = parse_c_file(c_content)
    del c_content

    pot_file = open(pot_filepath, 'rt')
    pot_content = pot_file.read()
    pot_file.close()

    pot_ps = parse_pot(pot_content)

    for string in c_cs.strings:
        if string in pot_ps.dict:
            continue
        c = c_cs.strings[string][0]
        pot_content += generate_pot([string])
        changed = True
        #print(f'NOT PRESENT: {c.__dict__}')
        print('Note: message not translated: \'' + c.string + '\'', file=sys.stderr)

    pot_remove_locations = []
    for string in pot_ps.dict:
        if string in c_cs.strings:
            continue
        p = pot_ps.dict[string]
        pot_remove_locations.append([p.location[0], p.location[1]])
        changed = True
        #print(f'USELESS: {p.__dict__}')
        print('Note: useless message : \'' + p.msgid + '\'', file=sys.stderr)
    # Vide 'cmd_replace_c_file()'
    pot_remove_locations.sort(key=lambda x: x[0], reverse=True)
    for l in pot_remove_locations:
        pot_content = pot_content[:l[0]] + pot_content[l[1]:]

    if dry:
        if changed:
            sys.exit(1)
    else:
        pot_file = open(pot_filepath, 'wt')
        pot_file.write(pot_content)
        pot_file.close()


def cmd_update_po(pot_filepath, po_filepath, dry = False):
    assert(type(pot_filepath) == str)
    assert(type(po_filepath) == str)
    changed = False

    pot_file = open(pot_filepath, 'rt')
    po_file = open(po_filepath, 'rt')
    pot_content = pot_file.read()
    po_content = po_file.read()
    pot_file.close()
    po_file.close()

    pot_ps = parse_pot(pot_content)
    po_ps = parse_pot(po_content, allow_empty = not dry)
    del pot_content

    for string in pot_ps.dict:
        if string in po_ps.dict:
            continue
        p = pot_ps.dict[string]
        changed = True
        print('Note: message not translated: \'' + p.msgid + '\'', file=sys.stderr)
        po_content += generate_pot([string])

    po_remove_locations = []
    for string in po_ps.dict:
        if string in pot_ps.dict:
            continue
        p = po_ps.dict[string]
        changed = True
        print('Note: useless message : \'' + p.msgid + '\'', file=sys.stderr)
        po_remove_locations.append(p.location)
    po_remove_locations.sort(key=lambda x: x[0], reverse=True)
    for l in po_remove_locations:
        po_content = po_content[:l[0]] + po_content[l[1]:]

    if dry:
        if changed:
            sys.exit(1)
    else:
        po_file = open(po_filepath, 'wt')
        po_file.write(po_content)
        po_file.close()


def usage():
    print('Usage: <command> [<args...>]')
    print('Commands:')
    print('\t--help, -h')
    print('\tmake_pot <c_file> <pot_file>')
    print('\treplace_c_file <po_file> <c_file> [original_c_file]')
    print('\tupdate_pot <c_file> <pot_file> [-n]')
    print('\tupdate_po <pot_file> <po_file> [-n]')
    print('')


def main():
    def error_too_many_arguments():
        print('Fatal error: too many argument given', file=sys.stderr)

    if len(sys.argv) <= 1:
        usage()
        sys.exit(0)
    command = sys.argv[1]
    command_argv = sys.argv[2:]
    if command in {'-h', '--help'}:
        usage()
        sys.exit(0)

    dry = False
    if len(command_argv) < 2:
        print('Fatal error: required arguments not given', file=sys.stderr)
        sys.exit(1)
    if command in ['update_pot', 'update_po']:
        if len(command_argv) > 3:
            error_too_many_arguments()
            sys.exit(1)
        if len(command_argv) == 3:
            if command_argv[-1] == '-n':
                dry = True
            else:
                print('Fatal error: unknown option: \'' + n + '\'', file=sys.stderr)
                sys.exit(1)
    elif command == 'replace_c_file':
        if len(command_argv) > 3:
            error_too_many_arguments()
            sys.exit(1)
    elif len(command_argv) > 2:
        error_too_many_arguments()
        sys.exit(1)

    if command == 'make_pot':
        c_file = command_argv[0]
        pot_file = command_argv[1]
        cmd_make_pot(c_file, pot_file)
    elif command == 'replace_c_file':
        pot_file = command_argv[0]
        c_file = command_argv[1]
        original_c_file = None if len(command_argv) <= 2 else command_argv[2]
        cmd_replace_c_file(pot_file, c_file, original_c_file)
    elif command == 'update_pot':
        c_file = command_argv[0]
        pot_file = command_argv[1]
        cmd_update_pot(c_file, pot_file, dry)
    elif command == 'update_po':
        pot_file = command_argv[0]
        po_file = command_argv[1]
        cmd_update_po(pot_file, po_file, dry)
    else:
        print('Fatal error: unknown command: \'' + command + '\'', file=sys.stderr)
        sys.exit(1)
    sys.exit(0)


if __name__ == '__main__':
    main()
