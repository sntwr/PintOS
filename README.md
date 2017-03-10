# PintOS (Course)
This was a course project for CSE531 (Operating Systems) taught at IIIT - Hyderabad in Monsoon-2016.

## How to setup PINTOS on Fedora
- This is what you need to do get PintOS working on Fedora:               
- Tested on Fedora 24                                                     
- If you're on a lower version of Fedora, use 'yum' instead of 'dnf'      

1. Install qemu
```
sudo dnf install qemu
```
	In Fedora, qemu is designed to support multiple archs. 
	qemu- commands run cross-compiled binaries straight from the elf. 
	qemu-system- commands start an OS. So we need a symlink (cause there
	ain't no qemu. It's called qemu-system-... depending upon what
	architecture you want for your emulated system)
```
sudo ln -s /bin/qemu-system-i386 /bin/qemu
```
2. Fix the error: `stropts.h: No such file or directory while making utils`
```	
sudo dnf provides '*/stropts.h'
```
	You'll get a list of packages that provide the required header.
	This one that worked for me was glibc-arm-linux-gnu-devel
```	
sudo dnf install glibc-arm-linux-gnu-devel
```
	This is not enough since the headers are installed in 
	`/usr/arm-linux-gnu/include` while we need them in `/usr/include`.
	So, either modify CFLAGS in the make file or as a quick fix,
	give your system stropts.h by making symlinks.
	We'll use the latter approach. (Remember to remove these later,
	although I don't think they'll do any harm.)
```
sudo ln -s /usr/arm-linux-gnu/include/bits/stropts.h /usr/include/bits/stropts.h
sudo ln -s /usr/arm-linux-gnu/include/stropts.h /usr/include/stropts.h
sudo ln -s /usr/arm-linux-gnu/include/bits/xtitypes.h /usr/include/bits/xtitypes.h
```
3. Then cd into src/utils and build
```
make
```
4. [For convenience] Create a `bin` directory under your Assignment 
	directory and add that to your `PATH` (temporarily). 
	Copy the scripts in `src/utils` to the `bin` directory.
	Also, copy `squish-pty` and squish-unix to the `bin` directory

5. In your `bin` directory, make the following edits to the script `pintos`
	i. change line 103 to: `$sim = "qemu" if !defined $sim;`
	We are doing this because pintos wants boch as the default emulator.
	So, if you don't supply an emulation option when invoking pintos, it'll
	try to use boch. By making the above change we make it look for qemu
	as its default emulator

6. [Testing] cd to `src/threads` and make
```
cd src/threads
 make
```
	To check if pintos works, cd to `src/threads/build` and invoke the
	multiple alarms test
```
cd src/thread/build
pintos run alarm-multiple
```
	You'll get something similar to this (ignore BEGIN QEMU ... stuff):
```
	PiLo hda1
	Loading...........
	Kernel command line: run alarm-multiple
	Pintos booting with 3,968 kB RAM...
	367 pages available in kernel pool.
	367 pages available in user pool.
	Calibrating timer...  129,228,800 loops/s.
	Boot complete.
	Executing 'alarm-multiple':
	(alarm-multiple) begin
	(alarm-multiple) Creating 5 threads to sleep 7 times each.
	(alarm-multiple) Thread 0 sleeps 10 ticks each time,
	(alarm-multiple) thread 1 sleeps 20 ticks each time, and so on.
	(alarm-multiple) If successful, product of iteration count and
	(alarm-multiple) sleep duration will appear in nondescending order.
	(alarm-multiple) thread 0: duration=10, iteration=1, product=10
	(alarm-multiple) thread 0: duration=10, iteration=2, product=20
	(alarm-multiple) thread 1: duration=20, iteration=1, product=20
	(alarm-multiple) thread 0: duration=10, iteration=3, product=30
	(alarm-multiple) thread 2: duration=30, iteration=1, product=30
	(alarm-multiple) thread 3: duration=40, iteration=1, product=40
	(alarm-multiple) thread 0: duration=10, iteration=4, product=40
	(alarm-multiple) thread 1: duration=20, iteration=2, product=40
	(alarm-multiple) thread 4: duration=50, iteration=1, product=50
	(alarm-multiple) thread 0: duration=10, iteration=5, product=50
	(alarm-multiple) thread 0: duration=10, iteration=6, product=60
	(alarm-multiple) thread 1: duration=20, iteration=3, product=60
	(alarm-multiple) thread 2: duration=30, iteration=2, product=60
	(alarm-multiple) thread 0: duration=10, iteration=7, product=70
	(alarm-multiple) thread 1: duration=20, iteration=4, product=80
	(alarm-multiple) thread 3: duration=40, iteration=2, product=80
	(alarm-multiple) thread 2: duration=30, iteration=3, product=90
	(alarm-multiple) thread 4: duration=50, iteration=2, product=100
	(alarm-multiple) thread 1: duration=20, iteration=5, product=100
	(alarm-multiple) thread 3: duration=40, iteration=3, product=120
	(alarm-multiple) thread 1: duration=20, iteration=6, product=120
	(alarm-multiple) thread 2: duration=30, iteration=4, product=120
	(alarm-multiple) thread 1: duration=20, iteration=7, product=140
	(alarm-multiple) thread 4: duration=50, iteration=3, product=150
	(alarm-multiple) thread 2: duration=30, iteration=5, product=150
	(alarm-multiple) thread 3: duration=40, iteration=4, product=160
	(alarm-multiple) thread 2: duration=30, iteration=6, product=180
	(alarm-multiple) thread 3: duration=40, iteration=5, product=200
	(alarm-multiple) thread 4: duration=50, iteration=4, product=200
	(alarm-multiple) thread 2: duration=30, iteration=7, product=210
	(alarm-multiple) thread 3: duration=40, iteration=6, product=240
	(alarm-multiple) thread 4: duration=50, iteration=5, product=250
	(alarm-multiple) thread 3: duration=40, iteration=7, product=280
	(alarm-multiple) thread 4: duration=50, iteration=6, product=300
	(alarm-multiple) thread 4: duration=50, iteration=7, product=350
	(alarm-multiple) end
	Execution of 'alarm-multiple' complete.
```
	If you get a similar output: Hurray! It works!
	Otherwise: Try to find what you did wrong (see REFERENCES at the end).
 	Also: below is my assignment directory's `tree -L 3` for reference
```
	.
	├── bin
	│   ├── backtrace
	│   ├── pintos
	│   ├── pintos~
	│   ├── pintos-gdb
	│   ├── pintos-mkdisk
	│   ├── Pintos.pm
	│   ├── pintos-set-cmdline
	│   ├── squish-pty
	│   └── squish-unix
	├── misc
	│   ├── fedora-howto
	│   ├── fedora-howto~
	│   ├── pintos.pdf
	│   ├── Pintos\ Projects:\ Introduction.mht
	│   ├── pintos.tar.gz
	│   └── Project-PintOS.pdf
	└── pintos
			└── src
					├── devices
					├── examples
					├── filesys
					├── lib
					├── LICENSE
					├── Make.config
					├── Makefile
					├── Makefile.build
					├── Makefile.kernel
					├── Makefile.userprog
					├── misc
					├── tests
					├── threads
					├── userprog
					├── utils
					└── vm

	14 directories, 21 files
```

Cheers,
Sandip

[REREFERNCES:]
1. https://pintosiiith.wordpress.com/2012/09/13/install-pintos-with-qemu/
2. https://bugzilla.redhat.com/show_bug.cgi?id=439403
3. http://forums.fedoraforum.org/showthread.php?t=194667
4. http://web.stanford.edu/class/cs140/projects/pintos/pintos.pdf

