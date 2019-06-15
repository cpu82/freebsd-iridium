--- pdf/pdfium/pdfium_engine.cc.orig	2019-03-11 22:01:01 UTC
+++ pdf/pdfium/pdfium_engine.cc
@@ -133,7 +133,7 @@ constexpr base::TimeDelta kMaxInitialProgressivePaintT
 
 PDFiumEngine* g_engine_for_fontmapper = nullptr;
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
 
 PP_Instance g_last_instance_id;
 
@@ -413,7 +413,7 @@ void Release(FPDF_SYSFONTINFO* sysfontinfo) {
   fontinfo_with_metrics->default_sysfontinfo->Release(
       fontinfo_with_metrics->default_sysfontinfo);
 }
-#endif  // defined(OS_LINUX)
+#endif  // defined(OS_LINUX) || defined(OS_BSD)
 
 PDFiumEngine::CreateDocumentLoaderFunction
     g_create_document_loader_for_testing = nullptr;
@@ -663,7 +663,7 @@ bool InitializeSDK() {
   config.m_v8EmbedderSlot = gin::kEmbedderPDFium;
   FPDF_InitLibraryWithConfig(&config);
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   // Font loading doesn't work in the renderer sandbox in Linux.
   FPDF_SetSystemFontInfo(&g_font_info);
 #else
@@ -688,7 +688,7 @@ bool InitializeSDK() {
 
 void ShutdownSDK() {
   FPDF_DestroyLibrary();
-#if !defined(OS_LINUX)
+#if !defined(OS_LINUX) && !defined(OS_BSD)
   delete g_font_info;
 #endif
   TearDownV8();
@@ -712,7 +712,7 @@ PDFiumEngine::PDFiumEngine(PDFEngine::Client* client, 
   IFSDK_PAUSE::user = nullptr;
   IFSDK_PAUSE::NeedToPauseNow = Pause_NeedToPauseNow;
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   // PreviewModeClient does not know its pp::Instance.
   pp::Instance* instance = client_->GetPluginInstance();
   if (instance)
@@ -1176,7 +1176,7 @@ pp::Buffer_Dev PDFiumEngine::PrintPagesAsRasterPdf(
 
   KillFormFocus();
 
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   g_last_instance_id = client_->GetPluginInstance()->pp_instance();
 #endif
 
@@ -2973,7 +2973,7 @@ bool PDFiumEngine::ContinuePaint(int progressive_index
   DCHECK(image_data);
 
   last_progressive_start_time_ = base::Time::Now();
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   g_last_instance_id = client_->GetPluginInstance()->pp_instance();
 #endif
 
@@ -3448,7 +3448,7 @@ void PDFiumEngine::SetCurrentPage(int index) {
     FORM_DoPageAAction(old_page, form(), FPDFPAGE_AACTION_CLOSE);
   }
   most_visible_page_ = index;
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   g_last_instance_id = client_->GetPluginInstance()->pp_instance();
 #endif
   if (most_visible_page_ != -1 && called_do_document_action_) {
