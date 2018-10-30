..\tools\vasmm68k.exe -Fsrec -s19 rom_vubug.asm -o rom_vubug.s19 -L rom_vubug.lst
..\tools\srec_cat.exe rom_vubug.s19 -crop 0x0000 0x4000 -fill 0x00 0x0000 0x4000 -o rom_vubug.bin -binary
..\tools\srec_cat.exe rom_vubug.bin -binary -o rom_vubug.mem -mem 16
..\tools\srec_cat.exe rom_vubug.bin -binary -o rom_vubug.mif -mif 16
