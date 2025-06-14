require efitools.inc

#SRC_URI += "file://${UEFI_SB_ARTIFACTS_DIR}/LockDown.efi;sha256sum=${LOCK_DOWN_EFI_SHA256SUM}"
SRC_URI += '${@d.expand("${UEFI_SB_LOCKDOWN_EFI}")}'

# python __anonymous() {
#     lockdown_uri = d.expand(d.getVar('UEFI_SB_LOCKDOWN_EFI'))
#     d.appendVar('SRC_URI', ' ' + lockdown_uri)
# }

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
