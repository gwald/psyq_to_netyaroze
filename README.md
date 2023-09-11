# psyq_to_netyaroze
Updated Net Yaroze headers which let you use Psy-Q SDK as if it was Net Yaroze SDK, for the 
[PSX.DEV](https://www.psx.dev) Visual Code template project. File include/psyq.h replicates Net Yaroze excusive features.

# Net Yaroze Documentation
https://archive.org/details/net-yaroze-documents/020-1997-userguide/mode/1up

# Net Yaroze SCEE archive with examples
https://archive.org/details/webyaroze.7z

# Executable Load Address
The linker tells the program where to load the program in RAM, the default address is 0x80010000 (PSX RAM address range from 0x80010000 to 0x801fffff which is 2MB).

Loading at 0x80010000 is a problem because that's the location of the Net Yaroze libps.exe file (like a DLL which makes executables smaller to transfer over serial - See [Memory Map in the Net Yaroze User Guide PDF](https://archive.org/details/net-yaroze-documents/020-1997-userguide/page/38/mode/1up) for more information, we need to change it in the MakeFile using:

>LDFLAGS=-Xlinker --defsym=TLOAD_ADDR=0x80090000

# Siocons Script
Siocons is a DOS program that uploads files to the PlayStation, at a specified RAM addres and then run.
This script can be use to package the assets and executable into a single PlayStation executable using [Yarexe](https://github.com/gwald/Yarexe).

The loading of assets into RAM can also be replicated in Visual Code. The debugger has to first pre-loaded the assets into the correct RAM address when pressing F5. This is done via the file in your project folder: .vscode\launch.json

You would load your assets a similar way to the siocons script, ie:

>local dload data\OPTIONS.TIM 801292E8
>
>local dload data\SWORD.TIM 8012A508
>
>local load main.exe
>
>go

In the .vscode\launch.json file, autorun section, the equivalent would be:

>"restore data\\\\\\\\OPTIONS.TIM  binary 0x801292E8",
>
>"restore data\\\\\\\\SWORD.TIM  binary 0x8012A508",
>
>"load ${workspaceRootFolderName}.elf"
>
>"tbreak main",
>
>"continue"

There are 4 slash for the DOS path because of the communication protocol in GDB. 

# Repo from
https://github.com/gwald/psyq_to_netyaroze
