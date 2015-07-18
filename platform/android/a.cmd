ndk-build -j8 NDK_DEBUG=1
ant release
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore my-release-key.keystore bin/GL2JNIActivity-release-unsigned.apk alias_name
adb install -r -s bin/GL2JNIActivity-release-unsigned.apk