# How to use the command line version injection tool

===================================================
the Script is changed to crack Parallels only !!!!
====================================================


1. Go to this folder from the terminal
2. chmod +x  crack_Parallels.sh
3. crack_Parallels.sh   <====== to start the injector

# App Compatibility
### M-series and Intel versions of the following apps are supported:
Parallels Desktop 18.3.1

the Result looks like this:

====	Automatic injection script starts execution ====
Design By QiuChenly
When injecting, please follow the prompts to enter
[🤔] [prl_client_app] - [18.3.1] - [com.parallels.desktop.console]Is it a supported version and does it need to be injected? y/n(Default n)  <<< Enter y
y
Start injecting the app: com.parallels.desktop.console


====================
2023.2.26 Autumn City Falling Leaves Revised Edition
Thanks to the open source folks at insert_dylib! Repository address :https://github.com/Tyilo/insert_dylib
====================

/Applications/Parallels Desktop.app/Contents/Frameworks/QtXml.framework/Versions/5/QtXml The target file already exists. Should I rewrite it? [y/n]  y
This is a FAT format binary carrying code for 2 architectures (Intel/Apple Silicon ARM64).
Found code load signature: LC_CODE_SIGNATURE load command. Should I delete it automatically? [y/n] y
LC_CODE_SIGNATURE is not the last load command, so couldn't remove.
Add the LC_LOAD_DYLIB instruction to the generic architecture, application:/Applications/Parallels Desktop.app/Contents/Frameworks/QtXml.framework/Versions/5/QtXml。
[*] Make sure that your version is: https://download.parallels.com/desktop/v18/18.3.1-53614/ParallelsDesktop-18.3.1-53614.dmg
[*] Copying forged authorisation documents licenses.json
[*] Cracking completed 

if Parallels hangs then
quit Parallels
run in terminal
/Applications/Parallels\ Desktop.app/Contents/MacOS/Parallels\ Service service_stop  &>/dev/null
now all problems are gone
maybe you will have click 2 times to start the VM ( but only once)
