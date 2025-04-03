inherit module user-key-store

module_do_install:prepend() {
     ${@uks_get_shell_env_export(d)}
}