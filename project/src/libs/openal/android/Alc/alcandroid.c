#ifdef ANDROID
#include <jni.h>
#include "alMain.h"
#include "apportable_openal_funcs.h"

static JavaVM *javaVM = NULL;
JavaVM *alcGetJavaVM(void) {
	return javaVM;
}

	//when called as a shared lib, this is automatic
	//but when embedding it that will be an error
#ifdef LUMEN_LIB_OPENAL_ANDROID_SHARED

	jint JNI_OnLoad(JavaVM *vm, void *reserved) {
		alcandroid_OnLoad(vm);
		return JNI_VERSION_1_4;
	}

	void JNICALL JNI_OnUnload (JavaVM *vm, void *reserved) {
		alcandroid_OnUnload(vm);
	}

#endif //LUMEN_LIB_OPENAL_ANDROID_SHARED


void alcandroid_OnLoad( JavaVM *vm ) {
	BackendFuncs func_list;
	if (apportableOpenALFuncs.alc_android_set_java_vm) {
		apportableOpenALFuncs.alc_android_set_java_vm(vm);
	}
	javaVM = vm;
}

void alcandroid_OnUnload( JavaVM *vm ) {
	if (apportableOpenALFuncs.alc_android_set_java_vm) {
		apportableOpenALFuncs.alc_android_set_java_vm(NULL);
	}
}

ALC_API void ALC_APIENTRY alcSuspend(void) {
	if (apportableOpenALFuncs.alc_android_suspend) {
		apportableOpenALFuncs.alc_android_suspend();
	}
}

ALC_API void ALC_APIENTRY alcResume(void) {
	if (apportableOpenALFuncs.alc_android_resume) {
		apportableOpenALFuncs.alc_android_resume();
	}
}

#endif
