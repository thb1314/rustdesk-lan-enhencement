fn main() {
    if std::env::var("CARGO_CFG_TARGET_OS").as_deref() == Ok("windows") {
        if std::env::var("PROFILE").unwrap() == "release" {
            use std::io::Write;
            let mut res = winres::WindowsResource::new();
            if std::env::var("CARGO_CFG_TARGET_ENV").as_deref() == Ok("gnu") {
                res.set_windres_path("x86_64-w64-mingw32-windres")
                    .set_ar_path("x86_64-w64-mingw32-ar");
            }
            res.set_icon("../../res/icon.ico")
                .set_language(0x0409)
                .set_manifest_file("../../res/manifest.xml");
            match res.compile() {
                Err(e) => {
                    write!(std::io::stderr(), "{}", e).unwrap();
                    std::process::exit(1);
                }
                Ok(_) => {
                    if std::env::var("CARGO_CFG_TARGET_ENV").as_deref() == Ok("gnu") {
                        let out_dir = std::env::var("OUT_DIR").unwrap();
                        println!(
                            "cargo:rustc-link-arg-bin=rustdesk-portable-packer={out_dir}/resource.o"
                        );
                    }
                }
            }
        }
    }
}
