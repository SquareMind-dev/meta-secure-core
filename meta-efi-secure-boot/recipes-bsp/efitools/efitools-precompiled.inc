require efitools.inc

SRC_URI += '${@d.expand("${UEFI_SB_LOCKDOWN_EFI}")}'

do_configure[noexec] = "1"
do_compile[noexec] = "1"

do_install() {
    #echo > ${D}${EFI_BOOT_PATH}/LockDown.efi
    if [ x"${UEFI_SB}" = x"1" ]; then
        install -D -m 0755 ${WORKDIR}/${UEFI_SB_ARTIFACTS_DIR}/LockDown.efi ${D}${EFI_BOOT_PATH}/LockDown.efi
    fi
}

do_deploy() {
    install -d ${DEPLOYDIR}

    if [ -e ${D}${EFI_BOOT_PATH}/LockDown.efi ] ; then
        install -m 0600 ${D}${EFI_BOOT_PATH}/LockDown.efi "${DEPLOYDIR}"
    fi
}
