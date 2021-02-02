set OSNAME=bsOs
set BUILDDIR=\\wsl$\Ubuntu-20.04\home\blackstone\bsOs\kernel\bin
set OVMFDIR=\\wsl$\Ubuntu-20.04\home\blackstone\bsOs\OVMFbin

qemu-system-x86_64 -drive file=%BUILDDIR%/%OSNAME%.img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file=%OVMFDIR%/OVMF_CODE-pure-efi.fd,readonly=on -drive if=pflash,format=raw,unit=1,file=%OVMFDIR%/OVMF_VARS-pure-efi.fd -net none
pause