//GNU-EFI INCLUDES
#include <efi.h>
#include <efilib.h>
#include "boot.h" //this is a local Include

/*IMPORTANTS VARIABLES, SET HERE*/

BootInfo Info;
GENUX_TIME time;
EFI_GOP_INFORMATION info;
EFI_FILE_PROTOCOL *KernelFile = NULL;
EFI_FILE_PROTOCOL *Root = NULL;
EFI_PHYSICAL_ADDRESS Memory = 0x100000; //Pointer to kernel physical address
UINTN MAP_KEY; //variable to use in exit boot services
UINT64   *GetKernel = 0;
UINT64 MHex =  0xFFFFFFFFFFFFFFFF; //Max Value
//Variables Read kernel
VOID *Buffer = (VOID *)0x100000; 
UINTN BufferSize = 100000 ;
void get_time(EFI_SYSTEM_TABLE *ptr){
    EFI_TIME efi_time;
    
    uefi_call_wrapper(ptr->RuntimeServices->GetTime,2,&efi_time,NULL);

        //This is time to use in Kernel
        time.Year = efi_time.Year;
        time.Month = efi_time.Month;
        time.Day = efi_time.Day;
        time.Hour = efi_time.Hour;
        time.Minute = efi_time.Minute;
        time.Second = efi_time.Second;
        time.Pad1 = efi_time.Pad1;
        time.Nanosecond = efi_time.Nanosecond;
        time.TimeZone = efi_time.TimeZone;
        time.Daylight = efi_time.Daylight;
        time.Pad2 = efi_time.Pad2;
}
BootInfo memory_map(void) {
    UINTN MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR *MemoryMap = NULL;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
   
    uefi_call_wrapper(gBS->GetMemoryMap, 5, &MemoryMapSize, NULL, &MapKey, &DescriptorSize, &DescriptorVersion);
    MemoryMapSize += 2 * DescriptorSize;
    uefi_call_wrapper(gBS->AllocatePool, 3, EfiLoaderData, MemoryMapSize, (VOID**)&MemoryMap);
    uefi_call_wrapper(gBS->GetMemoryMap, 5, &MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);

    Info.MemoryMap         = (EFI_MEMORY_DESCRIPTOR*) MemoryMap;
    Info.MemoryMapSize     = MemoryMapSize;
    Info.DescriptorSize    = DescriptorSize;
    Info.DescriptorVersion = DescriptorVersion;
    Info.MapKey            = MapKey;
    Print(L"Success to Get Memory Map\n");
    return Info;
}
EFI_STATUS Open_Volume(EFI_SYSTEM_TABLE *Sptr,EFI_FILE_PROTOCOL **Root){
    EFI_STATUS Status;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = NULL;
    Status = uefi_call_wrapper(
        Sptr->BootServices->LocateProtocol, 
        3, 
        &FileSystemProtocol,
        NULL, 
        (VOID **)&FileSystem
    );
    if(EFI_ERROR(Status))
        return Status;
    Status = uefi_call_wrapper(FileSystem->OpenVolume, 2, FileSystem, Root); 
    Print(L"Success in  Open Volume\n");
    return EFI_SUCCESS;
}
EFI_STATUS Load_Kernel(EFI_FILE_PROTOCOL *Root,EFI_FILE_PROTOCOL **KernelFile){
    EFI_STATUS Status;
     //Pointer to kernel.bin is *KernelFile  
    Status = uefi_call_wrapper(
        Root->Open,
        5,
        Root,
        KernelFile,
        L"\\Genux.bin",
        EFI_FILE_MODE_READ,
        EFI_FILE_READ_ONLY
     );

    if(EFI_ERROR(Status)){
        Print(L"Error in Load Kernel: %r (Cod: %X)\n",Status,Status);
        return Status; //Return error if can't load the  kernel
    }
    
    Print(L"Success in Load Kernel\n");
    return EFI_SUCCESS;
}
EFI_STATUS set_kernel(EFI_FILE_PROTOCOL *Kernel){
    EFI_STATUS Status;
    Status = uefi_call_wrapper(
        Kernel->SetPosition,
        2, 
        Kernel,
        MHex
    );
    
    if(EFI_ERROR(Status)){
        Print(L"Error in set kernel\n");
        return Status;
    }

    Print(L"Success on set kernel\n");
    return EFI_SUCCESS;
}
EFI_STATUS get_kernel(EFI_FILE_PROTOCOL *Kernel){
    EFI_STATUS Status;
    Status = uefi_call_wrapper(
        Kernel->GetPosition,
        2,
        Kernel,
        GetKernel
    );
    Print(L"Success on get kernel\n");
    return EFI_SUCCESS;

}
EFI_STATUS set_kernel2(EFI_FILE_PROTOCOL *Kernel){
    EFI_STATUS Status;
    Status = uefi_call_wrapper(
        Kernel->SetPosition,
        2, 
        Kernel,
        0
    );
    
    if(EFI_ERROR(Status)){
        Print(L"Error in set kernel, for the 2nd time\n");
        return Status;
    }

    Print(L"Success on set kernel, for the 2nd time\n");
    return EFI_SUCCESS;
}
EFI_STATUS read(EFI_FILE_PROTOCOL *Kernel){
    EFI_STATUS Status;
        Status = uefi_call_wrapper(
        Kernel->Read,
        3,
        Kernel,
        &BufferSize,
        Buffer
    );
    if(EFI_ERROR(Status)){
        Print(L"Error on read kernel\n");
        return Status;
    }
    Print(L"Success on read kernel\n");
    return EFI_SUCCESS;
}
EFI_STATUS close(EFI_FILE_PROTOCOL *Kernel){
    EFI_STATUS Status;
    Status = uefi_call_wrapper(
        Kernel->Close,
        1,
        Kernel
    );
    if(EFI_ERROR(Status)){
        Print(L"Error on close kernel\n");
        return Status;
    }
    Print(L"Success on close kernel\n");
    return EFI_SUCCESS;
}
EFI_STATUS Alloc_Pages(EFI_SYSTEM_TABLE *ptr){
    EFI_STATUS Status;
    UINTN Pages = (*GetKernel + 4095) / 4096; //number of Pages
    Status = uefi_call_wrapper(
        ptr->BootServices->AllocatePages,
        4,
        AllocateAddress,
        EfiLoaderData,
        Pages,
        &Memory 

    );
    if(EFI_ERROR(Status)){
        Print(L"Error in Alloc_Pages\n");
        return Status;
    }

    Print(L"Success in Alloc_Pages\n");
    return EFI_SUCCESS;
}
EFI_STATUS gop(void){
    EFI_STATUS Status,status;
    //GOP LOCAL VARIABLES
    EFI_GUID GopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    UINTN SIZEOFINFO, numMode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP   = NULL;
    int i;
    UINTN a = 0;
    
    Status = uefi_call_wrapper(
    BS->LocateProtocol, 3,
    &GopGuid,
    NULL,
    (VOID **)&GOP
    ); //Create  the gop struct

    
    EFI_STATUS STATUS = uefi_call_wrapper(
        GOP->QueryMode,
        4,
        GOP,
        NULL,
        &SIZEOFINFO,
        &Info
    );
    if(EFI_ERROR(STATUS)){
        Print(L"Error on get mode\n");
        return STATUS;
    }else{
        numMode = GOP->Mode->MaxMode;
    }
    for(i = 0; i < numMode; i++){
        status = uefi_call_wrapper(
        //Call to QueryMode
        GOP->QueryMode,
        4,
        GOP,
        i,
        &SIZEOFINFO,
        &Info
        );

        info.WidthResolution = Info->HorizontalResolution;
        info.HeightResolution =Info->VerticalResolution;
        info.PixelFormat =  Info->PixelFormat;
    }        
        info.PixelInformation.RedMask = Info->PixelInformation.RedMask;
        info.PixelInformation.GreenMask = Info->PixelInformation.GreenMask;
        info.PixelInformation.BlueMask = Info->PixelInformation.BlueMask;
        info.PixelInformation.ReservedMask = Info->PixelInformation.ReservedMask;
        info.PixelsPerScanLine = Info->PixelsPerScanLine;
    
    info.FrameBufferBase = GOP->Mode->FrameBufferBase;
    EFI_STATUS Status2 = uefi_call_wrapper(
        GOP->SetMode,
        2,
        GOP,
        a
    );
    if (EFI_ERROR(Status) || GOP == NULL) {
        //catch if can't create gop
        Print(L"Error on Create Gop Struct\n");
        return Status;
    }
    if(EFI_ERROR(status)){
        Print(L"Error on use gop.QueryMode();\n");
        return status;
    }
    if(EFI_ERROR(Status2)){
        Print(L"Error on SetMode");
        return Status2;
    }

    return EFI_SUCCESS;
}
void map_key(void){
    //recriate memory_map, just past MapKey to MAP_KEY 
    UINTN MapKey;
    UINTN MemoryMapSize = 0;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;

    uefi_call_wrapper(gBS->GetMemoryMap, 5, &MemoryMapSize, NULL, &MapKey, &DescriptorSize, &DescriptorVersion);
    MAP_KEY = MapKey;
}
EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    // Efi main function
    InitializeLib(ImageHandle, SystemTable);
    // USE uefi_call_wrapper(Target_Function, Argument_Count, Argument_1, Argument_2, ...); to uefi call
    uefi_call_wrapper(SystemTable->ConOut->ClearScreen, 1, SystemTable->ConOut); //CLEAR THE SCREEN
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *FileSystem = NULL;
    Print(L"Welcome to Genux Bootloader!\n");
    uefi_call_wrapper(SystemTable->BootServices->Stall, 1, 3000000);
    uefi_call_wrapper(SystemTable->ConOut->ClearScreen, 1, SystemTable->ConOut); 
    gop();
    uefi_call_wrapper(SystemTable->ConOut->ClearScreen, 1, SystemTable->ConOut); 

    Print(L"Genux Bootloader....\n");
    Print(L"Success on set GOP!\n");
    get_time(SystemTable);
    memory_map();
    Open_Volume(SystemTable,&Root);

    Load_Kernel(Root,&KernelFile);
  
    set_kernel(KernelFile); // Set kernel to 0xFFFFFFFFFFFFFFFFFFFFF
    get_kernel(KernelFile);// get kernel size
    set_kernel2(KernelFile); //set kernel to 0
    Alloc_Pages(SystemTable);
    read(KernelFile);
    close(KernelFile);
    
    Print(L"Bye Bye Efi\n");
    uefi_call_wrapper(SystemTable->BootServices->Stall, 1, 3000000);

    uefi_call_wrapper(SystemTable->ConOut->ClearScreen, 1, SystemTable->ConOut); //clear the screen to kernel
    map_key();
    EFI_STATUS Status = uefi_call_wrapper(
        BS->ExitBootServices,
        2,
        ImageHandle,
        MAP_KEY
    );
    if(EFI_ERROR(Status)){
        Print(L"Error on ExitBootServices");
        while(1);
    }
    typedef void (__attribute__((sysv_abi)) *kernel_entry_t)(EFI_GOP_INFORMATION *,GENUX_TIME,BootInfo);
    kernel_entry_t kernel_main = (kernel_entry_t) 0x100000;
    asm("cli"); //disable interrupts
    kernel_main(&info,time,Info);//call kernel main in kernel.c

    while(1);     
    return EFI_SUCCESS; // Good Bye EFI :D
    

}

