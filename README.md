# RustDesk 局域网增强版

英文原版 README: [RustDesk upstream README](https://github.com/rustdesk/rustdesk/blob/master/README.md)

这个 fork 主要面向可信局域网内更清晰的远程桌面体验。

- 新增 **局域网画质优化**，直连局域网会自动开启，用户可随时关闭恢复原版策略。
- 局域网会使用更高的自定义画质值 `1000`，并在支持时优先使用 **真彩模式（4:4:4）**。
- 新增 **图像锐化**，支持关闭、低、中、高预设，并可用滑杆自定义强度。
- 在会话标题栏和显示质量监测中显示当前连接 IP/路径，方便确认是否为局域网直连。
- 新增 **局域网直连**：发现列表里的卡片现在直接用对端 IP 连接，完全不经过 ID 服务器和中继；对同一局域网的设备也不再回退到中继，避免被公共中继限流。可在设置里用 `enable-lan-direct` 关闭恢复原版策略。
- Linux Sciter `.deb` 默认带上 `hwcodec` 和 `unix-file-copy-paste`，并补齐 FUSE 运行时依赖。

推荐的 Linux 打包命令：

```sh
python3 build.py --hwcodec --unix-file-copy-paste
```

完整中文说明见 [docs/README-ZH.md](docs/README-ZH.md)。

下面是官方原版 README，请点上面的英文链接查看。
