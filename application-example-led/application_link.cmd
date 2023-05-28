/*----------------------------------------------------------------------------*/
/* Linker Settings */
--retain="*(.intvecs)"
/*----------------------------------------------------------------------------*/
/* Memory Map */
MEMORY
{
    VECTORS (X) : origin=0x00010020 length=0x00000020
    /*sector 4/5 are used for application */
    FLASH_CODE (RX) : origin=0x00010040 length=0x8000 - 0x40
    FLASH0 (RX) : origin=0x00018000 length=0x00200000 - 0x18000
    FLASH1 (RX) : origin=0x00200000 length=0x00200000
    STACKS (RW) : origin=0x08000000 length=0x00001500
    RAM (RW) : origin=0x08001500 length=0x0007EB00
}
/*----------------------------------------------------------------------------*/
/* Section Configuration */
SECTIONS
{
    .intvecs : {} > VECTORS
    .text align(32) : {} > FLASH_CODE
    .const align(32) : {} > FLASH_CODE
    .cinit align(32) : {} > FLASH_CODE
    .pinit align(32) : {} > FLASH_CODE
    .bss : {} > RAM
    .data : {} > RAM
    .sysmem : {} > RAM
}
