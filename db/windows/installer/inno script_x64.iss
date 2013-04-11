; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "djondb"
#define MyAppVersion "0.1"
#define MyAppPublisher "djondb"
#define MyAppURL "http://djondb.com"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{06E2AA02-A2E7-4DF2-8C18-0E4FE0F7D94C}
AppName=djondb Server
AppVersion=0.2
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputBaseFilename=setup_djondb_x64
Compression=lzma
SolidCompression=yes

[Types]
Name: "full"; Description: "Full installation"
Name: "standalone"; Description: "Standalone Installation"
;Name: "service"; Description: "Windows Service Installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Components]
Name: "standalone"; Description: "Program Files"; Types: full standalone custom; Flags: fixed
;Name: "service"; Description: "Install Windows Service"; Types: full service custom;

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Dirs]
Name: "{app}\"; Permissions: everyone-modify

[Files]

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\Release\djondb_win.exe"; DestDir: "{app}"; Components: standalone; Flags: ignoreversion
;Source: "..\Release\djondb_service.exe"; DestDir: "{app}"; Components: service; Flags: ignoreversion
Source: "..\Release\pthreadVC2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\Release\djondb_shell.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\djondb.conf"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\installer\vcredist_x64_vs2010.exe"; DestDir: {tmp}
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Run]
Filename: {tmp}\vcredist_x64_vs2010.exe; Parameters: "/passive /Q:a /c:""msiexec /qb /i vcredist.msi"" "; StatusMsg: Installing 2010 RunTime...
;Filename: {app}\djondb_service.exe; Parameters: "-Install"; Components: service; StatusMsg: Registering djondb service...

[UninstallRun]
;Filename: {app}\djondb_service.exe; Parameters: "-Install -u"; Components: service; StatusMsg: Removing djondb service...

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\djondb_win.exe";
Name: "{group}\{#MyAppName} shell"; Filename: "{app}\djondb_shell.exe"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\djondb_win.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\djondb_win.exe"; Description: "Launch djondb standalone"; Flags: nowait postinstall skipifsilent


