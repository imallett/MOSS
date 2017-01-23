# MOSS
## The Minimal Operating System That Sucks

Once, in college, I woke up in the middle of the night and realized I had to write an operating
system.  No delusions, mind, it would almost certainly remain a hobbyist endeavor.  I'd be happy
if I could get anything working.

Since then, MOSS has matured, but still lives up to its acronym: the Minimal Operating System
that Sucks.

## Setup

### Linux-only setup:

1. Update/upgrade everything
(`sudo apt-get update`/`sudo apt-get upgrade`/`sudo apt-get dist-upgrade`)
2. Install misc. necessary packages: `sudo apt-get install build-essential git nasm kpartx grub`
2. In a folder somewhere, check out `MOSS`.  E.g.:
`cd ~; git clone https://github.com/imallett/MOSS`.
3. [Set up a cross-compiler](cross/README.md).
4. Install tools and emulators: `sudo apt-get install qemu-kvm bochs-x`.
5. Build MOSS.  E.g. `cd source/x86/; ./scripts/all.sh`.
6. Run it!  E.g. `python _run_bochs.py`/`python _run_qemu.py`.
7. [To set up VirtualBox](VMs/README.md).

### Windows + Linux VM setup:

1. Set up and install Linux into a VirtualBox x86-64 VM.  Note that an 8GB HDD is too small to
handle both an e.g. Ubuntu 16.10 MATE installation and a GCC compile.  I recommend at least 16GB,
ensuring that there's no swap file eating half of it.
2. Update/upgrade everything
(`sudo apt-get update`/`sudo apt-get upgrade`/`sudo apt-get dist-upgrade`)
3. Install misc. necessary packages: `sudo apt-get install build-essential git nasm kpartx grub`
4. Insert guest-additions CD into VM and follow the autorun prompt.
5. Add yourself to share folders: `sudo adduser <username> vboxsf`
6. Create a shared folder.
7. Reboot.
8. In the shared folder, check out `MOSS`.  E.g.:
`cd /media/sf_dev/; git clone https://github.com/imallett/MOSS`.
9. [Set up a cross-compiler](cross/README.md).
10. Install tools and emulators: `sudo apt-get install qemu-kvm bochs-x`.
11. Build MOSS.  E.g. `cd source/x86/; ./scripts/all.sh`.
12. Run it!  E.g. `python _run_bochs.py`/`python _run_qemu.py`.
13. [To set up VirtualBox](VMs/README.md).

### Additional Windows

I do MOSS development using the Windows + Linux VM setup above.  The following makes that easier:

- [Visual Studio](https://www.visualstudio.com/) is used for the project files.  Note that (the
real version of) Visual Studio currently only runs on Windows.
- [Python](https://www.python.org/) is assumed to ship with Linux, as above, but on Windows you
have to install it if you want to run any of the Python scripts.  The scripts should be compatible
with either major version.
- The virtualization softwares installed above can also be installed on Windows.  If you do so, the
Python scripts can be run, and the virtualization run in Windows.
- A hex editor is handy.  On Windows, I like [HxD](https://mh-nexus.de/en/hxd/).
- Real hardware that is USB bootable can be fun to put MOSS on.  After building, run
`source/x86/scripts/_install_usb.sh`.

## Orientation

A few selected locations in the file structure to help you get your bearings.

- `cross/` is a handy location to put your cross-compiler.  You need a cross-compiler, and building
it [is also documented there](cross/README.md).
- `resources/` is a place for content-creation (fonts, images, files, associated scripts, etc.).  A
bit messy, I'm afraid.
- `source/x86/` is where MOSS's source is kept, along with project files and build directories.
The ARM branch is not currently being developed.
  - `source/x86/.build/` is where MOSS disk images get built.
  - `source/x86/filesystem/` is where you can add files to be included in the built disk image.
  - `source/x86/scripts/` are helper scripts used to build and convert MOSS images.
  - `source/x86/source_*` sources for MOSS and standard libraries.
  - `source/x86/_run_*.py` are scripts that conveniently spool up a built MOSS disk image in an
emulator.
- `VMs/` is a handy location to put virtual machines for emulation, and is also the location to
which non-Bochs emulator builds output.

## Philosophy

MOSS is designed to be as powerful, but still as clear as possible.  In particular, the main
language is C++, not C, which allows most of the horrible hardware crap to be abstracted into
semi-OO interfaces.  Not all code is up to this standard, since a lot of it was written during
various 04:00 impromptu hackathons, and parts of it are being rewritten, even as the functionality
improves.

## Contributing

MOSS is free for use with attribution, and your pull requests are welcome.  Unfortunately, I
haven't had time to set up a reproducible way of setting things up, and so, like much else in
OS development, it is likely to be painful.
