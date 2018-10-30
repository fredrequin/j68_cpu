..\tools\vasmm68k.exe -m68010 -Fsrec -s19 rom_testbench.asm -o rom_testbench.s19 -L rom_testbench.lst
..\tools\srec_cat.exe rom_testbench.s19 -crop 0x0000 0x4000 -fill 0x00 0x0000 0x4000 -o rom_testbench.bin -binary
..\tools\srec_cat.exe rom_testbench.bin -binary -o rom_testbench.mem -mem 16
..\tools\srec_cat.exe rom_testbench.bin -binary -o rom_testbench.mif -mif 16
