# Arduino-builder
Makefile with the native arduino-builder using to build Arduino projects.

Just copy Makefile and sysutils to Arduino project or integrate it into git repository:
```bash
$ git remote add builder https://github.com/boringplace/Arduino-builder
$ git fetch builder 
warning: no common commits
remote: Counting objects: 18, done.
remote: Compressing objects: 100% (12/12), done.
remote: Total 18 (delta 4), reused 18 (delta 4), pack-reused 0
Unpacking objects: 100% (18/18), done.
From https://github.com/boringplace/Arduino-builder
 * [new branch]      master     -> builder/master
$ git merge builder/master --allow-unrelated-histories
Merge made by the 'recursive' strategy.
 Makefile                  | 46 ++++++++++++++++++++++++++++++++++++++++++++++
 sysutils/arduino_path.cmd |  8 ++++++++
 sysutils/arduino_path.sh  | 10 ++++++++++
 3 files changed, 64 insertions(+)
 create mode 100644 Makefile
 create mode 100644 sysutils/arduino_path.cmd
 create mode 100755 sysutils/arduino_path.sh
```

And run with by default:
```bash
$ make
```
or run with special ARDUINO_PATH:
```bash
$ make ARDUINO_PATH=<Arduino installed directory>
```
