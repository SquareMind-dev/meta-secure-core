FILESEXTRAPATHS:prepend := "${THISDIR}/linux-yocto:"

MODSIGN_ENABLED = "${@bb.utils.contains('DISTRO_FEATURES', 'modsign', '1', '0', d)}"

DEPENDS += "${@'key-store openssl-native' \
               if d.getVar('MODSIGN_ENABLED') == '1' \
               else ''}"

SRC_URI += "\
    ${@'file://modsign.scc file://modsign.cfg' \
       if d.getVar('MODSIGN_ENABLED') == '1' else ''} \
    ${@'file://0001-Force-building-with-OpenSSL-engine-support.patch file://0001-Extract-PKCS-11-URI-from-config-parameter.patch file://0002-Fail-build-if-signing-of-external-modules-fail.patch' if uks_signing_model(d) == 'pkcs11' else ''} \
    ${@'file://0001-Disable-extracting-public-key-from-PKCS-11-URI.patch' if uks_signing_model(d) == 'pkcs11' and bb.utils.contains('DISTRO_FEATURES', 'aws-kms-signing', True, False, d) else ''} \
"

INHIBIT_PACKAGE_STRIP = "${@'1' if d.getVar('MODSIGN_ENABLED') == '1' else '0'}"

MODULE_SIG_KEY = "${@'modsign_key.pem' if uks_signing_model(d) != 'pkcs11' else d.getVar('TOKEN_KEY_modsign_key')}"

inherit user-key-store

do_configure:prepend() {
    if [ ${MODSIGN_ENABLED} = "1" ]; then
        modsign_key="${@uks_modsign_keys_dir(d)}/modsign_key.key"
    else
        modsign_key="${STAGING_DIR_TARGET}${sysconfdir}/keys/modsign_key.key"
    fi
    modsign_cert="${STAGING_DIR_TARGET}${sysconfdir}/keys/modsign_key.crt"

    if [ -f "$modsign_key" ] && [ -f "$modsign_cert" ]; then
        cat "$modsign_key" "$modsign_cert" \
        > "${B}/modsign_key.pem"
    elif ${@'true' if not uks_has_privkey_file(d) else 'false'} && [ -f "$modsign_cert" ]; then
        mkdir -p "${B}/certs"
        cp "$modsign_cert" "${B}/certs/modsign_key.crt"
    else
        true
    fi

    sed -i "s~%MODULE_SIG_KEY%~${MODULE_SIG_KEY}~g" "${B}/.config"

}

module_do_install:prepend() {
     ${@uks_get_shell_env_export(d)}
}

kernel_do_install:prepend() {
    ${@uks_get_shell_env_export(d)}
}