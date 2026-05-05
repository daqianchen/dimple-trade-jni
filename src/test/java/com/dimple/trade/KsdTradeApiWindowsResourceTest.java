package com.dimple.trade;

import java.net.URL;
import java.util.Arrays;
import java.util.List;

/**
 * Windows 打包资源检查。
 * 这个测试不会加载 native 库，只校验 jar 中是否包含 Windows 运行必需的三个 DLL。
 */
public final class KsdTradeApiWindowsResourceTest {

    private static final List<String> WINDOWS_NATIVE_RESOURCES = Arrays.asList(
            "/win-x64/cryptopp.dll",
            "/win-x64/KSDTradeApi.dll",
            "/win-x64/dimple_trade_jni.dll"
    );

    private KsdTradeApiWindowsResourceTest() {
    }

    public static void main(String[] args) {
        for (String resource : WINDOWS_NATIVE_RESOURCES) {
            URL url = KsdTradeApiWindowsResourceTest.class.getResource(resource);
            if (url == null) {
                throw new IllegalStateException("Missing required Windows native resource: " + resource);
            }
        }
        System.out.println("Windows native resources are complete.");
    }
}
