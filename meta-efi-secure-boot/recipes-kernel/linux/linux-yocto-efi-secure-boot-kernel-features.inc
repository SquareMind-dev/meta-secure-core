efi_secure_boot_sccs = "\
    ${@bb.utils.contains('DISTRO_FEATURES', 'efi-secure-boot', \
                         'cfg/efi-ext.scc', '', d)} \
"
KERNEL_FEATURES:append:x86 = " ${efi_secure_boot_sccs}"
KERNEL_FEATURES:append:x86-64 = " ${efi_secure_boot_sccs}"
