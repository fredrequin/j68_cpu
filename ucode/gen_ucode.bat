..\tools\microcode20.exe -mif j68_ucode.asm j68_ram.mif > j68_dec.mif
..\tools\microcode20.exe -mem j68_ucode.asm j68_ram.mem > j68_dec.mem
..\tools\microcode20.exe -vlog j68_ucode.asm dpram_2048x20.v > decode_rom.v
