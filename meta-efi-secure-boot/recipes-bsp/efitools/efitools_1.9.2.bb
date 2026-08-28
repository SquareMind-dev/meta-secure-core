inherit user-key-store

require ${@'efitools-precompiled.inc' if d.getVar("EXTERNAL_SB_SIGNING") == "1" else 'efitools-build-lockdown.inc'}
