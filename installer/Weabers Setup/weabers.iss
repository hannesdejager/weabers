; Weabers installer
; Hannes de Jager 1 Aug 2006
;

[Setup]
AppName=IA Weabers (Web Application Browser and Server)
AppVerName=Weabers Version 1.1
AppPublisher=Inspired Archetypes
AppPublisherURL=http://www.inspired-archetypes.com
AppSupportURL=http://www.inspired-archetypes.com/weabers.php
AppUpdatesURL=http://www.inspired-archetypes.com/weabers.php
DefaultDirName={pf}\Inspired Archetypes\Weabers
DefaultGroupName=Weabers
DisableProgramGroupPage=yes
OutputBaseFilename=weabers_setup
Compression=lzma
SolidCompression=yes
Uninstallable=yes
DirExistsWarning=yes
WindowVisible=yes

[Files]
Source: "..\..\bin\weabers.exe"; DestDir: "{app}"
Source: "..\..\bin\lua5.1.dll"; DestDir: "{app}"

; Lua files
Source: "..\..\bin\onBuildMainMenu.lua"; DestDir: "{app}"
Source: "..\..\bin\onInit.lua"; DestDir: "{app}"
Source: "..\..\bin\onReady.lua"; DestDir: "{app}"

; Sample app
Source: "..\..\bin\apps\sample\index.html"; DestDir: "{app}\apps"


; Borland System files
Source: "c:\Program Files\Borland\CBuilder6\Bin\cc3260mt.dll"; DestDir: "{sys}"
Source: "c:\Program Files\Borland\CBuilder6\Bin\borlndmm.dll"; DestDir: "{sys}"

[Icons]
Name: "{group}\Weabers"; Filename: "{app}\weabers.exe"
Name: "{group}\{cm:ProgramOnTheWeb,Weabers}"; Filename: "{app}\weabers.url"
Name: "{userdesktop}\Weabers"; Filename: "{app}\weabers.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Weabers"; Filename: "{app}\weabers.exe"; Tasks: quicklaunchicon

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[INI]
Filename: "{app}\weabers.url"; Section: "InternetShortcut"; Key: "URL"; String: "http://www.inspired-archetypes.com/weabers.php"

[Run]
Filename: "{app}\weabers.exe"; Description: "{cm:LaunchProgram,Weabers}"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: files; Name: "{app}\weabers.url"





