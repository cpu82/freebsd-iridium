--- third_party/skia/src/core/SkCpu.cpp.orig	2019-03-11 22:08:22 UTC
+++ third_party/skia/src/core/SkCpu.cpp
@@ -74,6 +74,8 @@
     #include <sys/auxv.h>
 
     static uint32_t read_cpu_features() {
+return 0;
+#if 0
         const uint32_t kHWCAP_CRC32   = (1<< 7),
                        kHWCAP_ASIMDHP = (1<<10);
 
@@ -82,6 +84,7 @@
         if (hwcaps & kHWCAP_CRC32  ) { features |= SkCpu::CRC32; }
         if (hwcaps & kHWCAP_ASIMDHP) { features |= SkCpu::ASIMDHP; }
         return features;
+#endif
     }
 
 #elif defined(SK_CPU_ARM32) && __has_include(<sys/auxv.h>) && \
