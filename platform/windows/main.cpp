/*
* Copyright (C) 2009 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

// OpenGL ES 2.0 code

//#define BUILD_ANDROID ANDROID



#ifdef ANDROID
#include <jni.h>
#include <android/log.h>
#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#else 
#include "esUtil.h"
#define  LOGE(a)  cout << a << endl;
#endif

#include "../../src/app.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>



#include <stdio.h>
#include <stdlib.h>
#include <math.h>



typedef struct
{
	// Handle to a program object
	GLuint programObject;

} UserData;



#ifdef ANDROID

extern "C" {
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj, jint width, jint height);
	JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
};


JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj, jint width, jint height)
{
	setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj)
{
	renderFrame();
}

#else

void Draw(ESContext *esContext)
{
	//

	renderFrame();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

int main(int argc, char *argv[])
{
	ESContext esContext;
	UserData  userData;

	esInitContext(&esContext);
	esContext.userData = &userData;


	esCreateWindow(&esContext, TEXT("Hello Triangle"), 800, 600, ES_WINDOW_RGB);

	setupGraphics(800, 600);

	esRegisterDrawFunc(&esContext, Draw);

	esMainLoop(&esContext);
}

#endif
