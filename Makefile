compile-shell:
	gcc -c shell.c

assemble:
	as sys.S

link:
	ld -o shell shell.o a.out --entry main -z noexecstack

# After this command, run this other one in the linux folder: make isoimage FDARGS="initrd=/init.cpio" FDINITRD="~/Git/minimal-linux-shell/init.cpio"
all: compile-shell assemble link
	mv shell init

clean:
	rm -rf shell.o a.out init init.cpio files 

archive:
	echo init | cpio -H newc -o > init.cpio

archive-with-static-lua:
	echo lua >> files & echo init >> files & cat files | cpio -H newc -o > init.cpio

run-qemu:
	qemu-system-x86_64 -cdrom ~/Git/linux/arch/x86/boot/image.iso 

