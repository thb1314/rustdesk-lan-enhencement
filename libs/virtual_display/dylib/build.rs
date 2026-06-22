use cc;

fn build_c_impl() {
    let target_os = std::env::var("CARGO_CFG_TARGET_OS").unwrap_or_default();
    let target_env = std::env::var("CARGO_CFG_TARGET_ENV").unwrap_or_default();
    let mut build = cc::Build::new();

    if target_os == "windows" {
        build.file("src/win10/IddController.c");
    }

    build.flag_if_supported("-Wno-c++0x-extensions");
    build.flag_if_supported("-Wno-return-type-c-linkage");
    build.flag_if_supported("-Wno-invalid-offsetof");
    build.flag_if_supported("-Wno-unused-parameter");
    build.flag_if_supported("-Wno-incompatible-pointer-types");

    if build.get_compiler().is_like_msvc() {
        build.define("WIN32", "");
        build.flag("-Z7");
        build.flag("-GR-");
        // build.flag("-std:c++11");
    } else {
        build.flag("-fPIC");
        // build.flag("-std=c++11");
        // build.flag("-include");
        // build.flag(&confdefs_path.to_string_lossy());
    }

    if target_os == "windows" {
        if target_env == "gnu" {
            build.define("__USE_MINGW_ANSI_STDIO", "1");
        }
        build.compile("win_virtual_display");
        println!("cargo:rustc-link-lib=cfgmgr32");
        println!("cargo:rustc-link-lib=newdev");
        println!("cargo:rustc-link-lib=setupapi");
        println!("cargo:rustc-link-lib=ole32");
        println!("cargo:rerun-if-changed=src/win10/IddController.c");
        println!("cargo:rerun-if-changed=src/win10/IddController.h");
        println!("cargo:rerun-if-changed=src/win10/swdevice_compat.h");
    }
}

fn main() {
    build_c_impl();
}
