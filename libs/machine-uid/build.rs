use cc::Build;

fn main() {
    println!("cargo:rerun-if-changed=src");
    if std::env::var("CARGO_CFG_TARGET_OS").as_deref() == Ok("windows") {
        println!("cargo:rustc-link-lib=kernel32");
        Build::new().file("src/win.cpp").compile("machine-uid");
    }
}
