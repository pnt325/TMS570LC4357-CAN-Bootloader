/*----------------------------------------------------------------------------*/
/* Linker Settings */
--retain="*(.intvecs)"
/*----------------------------------------------------------------------------*/
/* Memory Map */
#define FLASH_ECC_ORIGIN  (0x00400000)

MEMORY
{
    VECTORS (X) : origin=0x00010020 length=0x00000020
    FLASH_CODE (RX) : origin=0x00010040 length=0x8000 - 0x40
    FLASH0 (RX) : origin=0x00018000 length=0x00200000 - 0x18000
    FLASH1 (RX) : origin=0x00200000 length=0x00200000
    STACKS (RW) : origin=0x08000000 length=0x00001500
    RAM (RW) : origin=0x08001500 length=0x0007EB00

    // ECC_VEC  : origin=0xf0400000 length=0x000004 ECC={ input_range=VECTORS algorithm=F021}
    // ECC_FLA_CO : origin=0xf0400004 length=0x3d000 ECC={ input_range=FLASH_CODE  algorithm=F021}
    // ECC_FLA0 : origin=0xf0400004 length=0x3d000 ECC={ input_range=FLASH0  algorithm=F021}
    // ECC_FLA1 : origin=0xf0430000 length=0x40000 ECC={ input_range=FLASH1  algorithm=F021}

    /* Bank 0 ECC */
    ECC_VEC      : origin = (FLASH_ECC_ORIGIN+(start(VECTORS)>>1))
                                    length = (size(VECTORS)>>3)
                                    ECC    = {algorithm=F021, input_range=VECTORS}
    ECC_FLA_CODE     : origin = (FLASH_ECC_ORIGIN+(start(FLASH_CODE)>>1))
                                    length = (size(FLASH_CODE)>>3)
                                    ECC    = {algorithm=F021, input_range=FLASH_CODE}
    ECC_FLA0     : origin = (FLASH_ECC_ORIGIN+(start(FLASH0)>>1))
                                    length = (size(FLASH0)>>3)
                                    ECC    = {algorithm=F021, input_range=FLASH0}
    /* Bank 1 ECC */
    ECC_FLA1     : origin = (FLASH_ECC_ORIGIN+(start(FLASH1)>>1))
                                    length = (size(FLASH1)>>3)
                                    ECC    = {algorithm=F021, input_range=FLASH1}
}

ECC { F021 : parity_mask = 0xfc
             mirroring = F021 }

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
