mkdir  ./bin/
rm -rf ./bin/*.o

nasm -f elf32 ./main.asm     -o ./bin/kasm1.o
nasm -f elf32 ./ports.asm    -o ./bin/kasm2.o
nasm -f elf32 ./handlers.asm -o ./bin/kasm3.o
gcc  -m32 -c  ./idt.c        -o ./bin/kc1.o
gcc  -m32 -c  ./handlers.c   -o ./bin/kc2.o
gcc  -m32 -c  ./screen.c     -o ./bin/kc3.o

ld -m elf_i386 -T ./link.ld -o ./bin/kernel ./bin/*.o
qemu-system-i386 -kernel ./bin/kernel