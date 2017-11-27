@ECHO OFF
SET arduino_path=%programfiles(x86)%\Arduino

IF EXIST "%arduino_path%" (
	IF EXIST "%arduino_path%\arduino-builder.exe" (
		ECHO "%arduino_path%/arduino-builder"
	) ELSE (
		EXIT /b 1
	)
) ELSE (
	EXIT /b 2
)
