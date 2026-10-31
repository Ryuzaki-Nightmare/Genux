#ifndef BOOT_H
#define BOOT_H
//TYPEDEFs

typedef unsigned long   UINTN;
typedef unsigned int UINT32;
typedef unsigned char  uint8_t;// 255
typedef unsigned short uint16_t;// 65k
typedef unsigned int   uint32_t;//4b
typedef signed short int16_t;
typedef long long unsigned int Uint64_t;
//Genux Time Struct
typedef struct {
   uint16_t   Year;              // 1900 - 9999
   uint8_t Month;             // 1 - 12
   uint8_t Day;               // 1 - 31
   uint8_t   Hour;              // 0 - 23
   uint8_t  Minute;            // 0 - 59
   uint8_t    Second;            // 0 - 59
   uint8_t    Pad1;
   uint32_t    Nanosecond;        // 0 - 999,999,999
   int16_t    TimeZone;          // —1440 to 1440 or 2047
   uint8_t     Daylight;
   uint8_t     Pad2;
} GENUX_TIME;
typedef struct {
    void *MemoryMap;
    UINTN MemoryMapSize;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
    UINTN MapKey;
} BootInfo; //memory map for Genux


//GOP STRUCTS

typedef enum {
        PixelRedGreenBlueReserved8BitPcolo,
        PixelBlueGreenRedReserved8BitPcolo,
        PixelBitMas,
        PixelBltOnl,
        PixelFormatMa,
} EFI_GRAPHICS_PIXEL; //based on EFI_GRAPHICS_PIXEL_FORMAT


typedef struct{
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t ReservedMask;
} EFI_PIXEL_MASK; //based on EFI_PIXEL_BITMASK

typedef struct{
    uint32_t Version;
    uint32_t WidthResolution;
    uint32_t HeightResolution;
    EFI_GRAPHICS_PIXEL PixelFormat;
    EFI_PIXEL_MASK PixelInformation;
    Uint64_t FrameBufferBase;
    UINTN   FrameBufferSize;
    uint32_t PixelsPerScanLine;
}EFI_GOP_INFORMATION; // based on EFI_GRAPHICS_OUTPUT_MODE_INFORMATION








#endif
