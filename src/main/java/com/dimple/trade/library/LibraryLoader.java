package com.dimple.trade.library;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * 从 jar 或外部目录中提取并加载本地依赖库。
 * 所有中文注释统一按 UTF-8 保存，避免后续出现乱码。
 */
public final class LibraryLoader {

    private static volatile boolean loaded;

    private LibraryLoader() {
    }

    /** 只加载一次本地库，避免重复 System.load。 */
    public static synchronized void load() {
        if (loaded) {
            return;
        }

        try {
            String os = System.getProperty("os.name", "").toLowerCase();
            File nativeDir = resolveNativeDir();
            System.out.println("[dimple-jni] os=" + os + ", nativeDir=" + nativeDir.getAbsolutePath());

            if (os.contains("win")) {
                loadWindows(nativeDir);
            } else if (os.contains("nix") || os.contains("nux") || os.contains("aix")) {
                loadLinux(nativeDir);
            } else {
                throw new IllegalStateException("Unsupported OS: " + os);
            }

            loaded = true;
        } catch (Exception e) {
            throw new RuntimeException("Failed to load Dimple trade native libraries.", e);
        }
    }

    /** Windows 下依次加载加密库、交易库、JNI 桥接库。 */
    private static void loadWindows(File nativeDir) throws IOException {
        File crypto = extractOrResolve(nativeDir, "cryptopp.dll", "/win-x64/cryptopp.dll", false);
        File trade = extractOrResolve(nativeDir, "KSDTradeApi.dll", "/win-x64/KSDTradeApi.dll", false);
        File jni = extractOrResolve(nativeDir, "dimple_trade_jni.dll", "/win-x64/dimple_trade_jni.dll", true);

        System.out.println("[dimple-jni] loading " + crypto.getAbsolutePath());
        System.load(crypto.getAbsolutePath());
        System.out.println("[dimple-jni] loading " + trade.getAbsolutePath());
        System.load(trade.getAbsolutePath());
        System.out.println("[dimple-jni] loading " + jni.getAbsolutePath());
        System.load(jni.getAbsolutePath());
    }

    /** Linux 下在加载前补执行权限，避免 so 无法装载。 */
    private static void loadLinux(File nativeDir) throws IOException, InterruptedException {
        File crypto = extractOrResolve(nativeDir, "libcryptopp64.so", "/linux-x64/libcryptopp64.so", false);
        File trade = extractOrResolve(nativeDir, "libKSDTradeApi64.so", "/linux-x64/libKSDTradeApi64.so", false);
        File jni = extractOrResolve(nativeDir, "libdimple_trade_jni.so", "/linux-x64/libdimple_trade_jni.so", true);

        chmodIfNeeded(crypto);
        chmodIfNeeded(trade);
        chmodIfNeeded(jni);

        System.load(crypto.getAbsolutePath());
        System.load(trade.getAbsolutePath());
        System.load(jni.getAbsolutePath());
    }

    /** 优先使用外部指定目录，否则在当前工作目录下创建默认释放目录。 */
    private static File resolveNativeDir() {
        String configured = System.getProperty("dimple.trade.native.dir");
        File nativeDir = configured == null || configured.trim().isEmpty()
                ? new File(new File(System.getProperty("user.dir")), "dimple_trade_native_libs")
                : new File(configured);

        if (!nativeDir.exists() && !nativeDir.mkdirs()) {
            throw new IllegalStateException("Cannot create native dir: " + nativeDir.getAbsolutePath());
        }
        return nativeDir;
    }

    /** 从 jar 资源中提取并覆盖目标文件，避免复用旧版本 native 库。 */
    private static File extractOrResolve(File dir, String fileName, String resourcePath, boolean required) throws IOException {
        File preferred = new File(dir, fileName);

        InputStream in = LibraryLoader.class.getResourceAsStream(resourcePath);
        if (in == null) {
            if (!required) {
                return preferred;
            }
            throw new IOException("Missing required native resource " + resourcePath
                    + ". Build JNI library first and place it in " + preferred.getAbsolutePath());
        }

        try (InputStream input = in; OutputStream output = new FileOutputStream(preferred)) {
            byte[] buffer = new byte[8192];
            int read;
            while ((read = input.read(buffer)) != -1) {
                output.write(buffer, 0, read);
            }
        }
        System.out.println("[dimple-jni] extracted " + resourcePath + " -> " + preferred.getAbsolutePath() + " (" + preferred.length() + " bytes)");
        return preferred;
    }

    /** Linux/Unix 平台下补充可执行权限。 */
    private static void chmodIfNeeded(File file) throws IOException, InterruptedException {
        String os = System.getProperty("os.name", "").toLowerCase();
        if (!(os.contains("nix") || os.contains("nux") || os.contains("aix"))) {
            return;
        }
        Process process = Runtime.getRuntime().exec(new String[]{"chmod", "775", file.getAbsolutePath()});
        process.waitFor();
    }
}
