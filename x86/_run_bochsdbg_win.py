from subprocess import call

def main():
    #http://bochs.sourceforge.net/doc/docbook/user/using-bochs.html#COMMANDLINE
    call([
        "C:\\Program Files (x86)\\Bochs-2.6.2\\bochsdbg.exe",
        "-q",
        "-f","C:/dev/C++/MOSS/0.6/scripts/bochsdbg-MOSS-win.txt",
        "-log","C:/dev/C++/MOSS/0.6/bochs-log.txt"
    ])
if __name__ == "__main__": main()
