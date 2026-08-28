inherit module user-key-store

module_do_install:prepend() {
     ${@uks_get_shell_env_export(d)}
}
do_install[network] = "${SIGNING_NEEDS_NETWORK}"
