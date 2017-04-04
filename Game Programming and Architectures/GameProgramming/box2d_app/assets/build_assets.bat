set FBX2SCN_EXE=..\..\gef_abertay\tools\fbx2scn\build\vs2015\x64\Release\fbx2scn.exe
set OUTPUT_DIR=..\media

set ASSET_NAME=space_frigate_6
set FBX2SCN_FLAGS=-scaling-factor 0.075 -strip-texture-path -texture-extension .png
%FBX2SCN_EXE% -o %OUTPUT_DIR%\%ASSET_NAME%.scn %FBX2SCN_FLAGS% %ASSET_NAME%.fbx

set ASSET_NAME=dark_fighter_6
set FBX2SCN_FLAGS=-scaling-factor 0.025 -strip-texture-path -texture-extension .png
%FBX2SCN_EXE% -o %OUTPUT_DIR%\%ASSET_NAME%.scn %FBX2SCN_FLAGS% %ASSET_NAME%.fbx

set ASSET_NAME=small_fighter_1
set FBX2SCN_FLAGS=-scaling-factor 0.008 -strip-texture-path -texture-extension .png
%FBX2SCN_EXE% -o %OUTPUT_DIR%\%ASSET_NAME%.scn %FBX2SCN_FLAGS% %ASSET_NAME%.fbx

set ASSET_NAME=asteroid_crystal_6
set FBX2SCN_FLAGS=-scaling-factor 0.05 -strip-texture-path -texture-extension .png
%FBX2SCN_EXE% -o %OUTPUT_DIR%\%ASSET_NAME%.scn %FBX2SCN_FLAGS% %ASSET_NAME%.fbx

set ASSET_NAME=Bomb
set FBX2SCN_FLAGS=-scaling-factor 0.005 -strip-texture-path -texture-extension .png
%FBX2SCN_EXE% -o %OUTPUT_DIR%\%ASSET_NAME%.scn %FBX2SCN_FLAGS% %ASSET_NAME%.fbx

pause