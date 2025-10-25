cmake_minimum_required(VERSION 3.23)
project(mssys-jni VERSION 1.0.0 LANGUAGES C CXX)

set(MS_SYS_VERSION "2.8.0")

set(MS_SYS_JAR_PACKAGE "com.mssys")
set(MS_SYS_JAR_NAME "mssys")

# Directory setup
set(MS_SYS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ms-sys")
set(MS_SYS_JNI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/main")
set(MS_SYS_JNI_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/test")

set(MS_SYS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/out")
set(MS_SYS_TEST_JAR_DIR "${MS_SYS_OUTPUT_DIR}/test/jar")
set(MS_SYS_WORK_DIR "${MS_SYS_OUTPUT_DIR}/test/work")
set(MS_SYS_JNI_HEADER_DIR "${MS_SYS_OUTPUT_DIR}/headers")
set(MS_SYS_LIBS_DIR "${MS_SYS_OUTPUT_DIR}/lib")
set(MS_SYS_JAR_DIR "${MS_SYS_OUTPUT_DIR}/jar")
set(MS_SYS_JAR "${MS_SYS_JAR_DIR}/")
set(MS_SYS_NATIVE_LIB_DIR "${MS_SYS_OUTPUT_DIR}/lib/${CMAKE_SYSTEM_PROCESSOR}")
set(MS_SYS_JNI_SOURCES
	${MS_SYS_JNI_SOURCE_DIR}/c/mssys-jni.c
	${MS_SYS_SOURCE_DIR}/src/br.c
	${MS_SYS_SOURCE_DIR}/src/exfat.c
	${MS_SYS_SOURCE_DIR}/src/fat12.c
	${MS_SYS_SOURCE_DIR}/src/fat16.c
	${MS_SYS_SOURCE_DIR}/src/fat32.c
	${MS_SYS_SOURCE_DIR}/src/file.c
	${MS_SYS_SOURCE_DIR}/src/identify.c
	${MS_SYS_SOURCE_DIR}/src/nls.c
	${MS_SYS_SOURCE_DIR}/src/ntfs.c
	${MS_SYS_SOURCE_DIR}/src/oem_id.c
	${MS_SYS_SOURCE_DIR}/src/partition_info.c
)

set(MS_SYS_JNI_LIST
	com.mssys.Br
	com.mssys.Fat12
	com.mssys.Fat32
	com.mssys.MsSys
	com.mssys.Ntfs
	com.mssys.PartitionInfo
	com.mssys.Exfat
	com.mssys.Fat16
	com.mssys.Identify
	com.mssys.OemId
	com.mssys.FileData
)

set(MS_SYS_JAVA_MAIN_SOURCES
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/Br.java
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/Exfat.java
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/Fat12.java
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/Fat16.java
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/Fat32.java
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/FileData.java
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/MsSys.java
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/Ntfs.java
	${MS_SYS_JNI_SOURCE_DIR}/java/com/mssys/OemId.java
)

if (BSD)
	list(APPEND MS_SYS_JAVA_MAIN_SOURCES
		${MS_SYS_JNI_SOURCE_DIR}/OpenBSD/java/com/mssys/Identify.java
		${MS_SYS_JNI_SOURCE_DIR}/OpenBSD/java/com/mssys/PartitionInfo.java
	)
else()
	list(APPEND MS_SYS_JAVA_MAIN_SOURCES
		${MS_SYS_JNI_SOURCE_DIR}/Default/java/com/mssys/Identify.java
		${MS_SYS_JNI_SOURCE_DIR}/Default/java/com/mssys/PartitionInfo.java
	)
endif()

set(MS_SYS_JAVA_TEST_SOURCES
	${MS_SYS_JNI_TEST_SOURCE_DIR}/java/com/mssys/MsSysTest.java
)

file(MAKE_DIRECTORY "${MS_SYS_TEST_JAR_DIR}" "${MS_SYS_WORK_DIR}" "${MS_SYS_JAR_DIR}" "${MS_SYS_JNI_HEADER_DIR}" "${MS_SYS_LIBS_DIR}")

find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include(UseJava)
include(CheckCCompilerFlag)

add_jar(
	mssys-jar ${MS_SYS_JAVA_MAIN_SOURCES}
	VERSION ${PROJECT_VERSION}
	OUTPUT_NAME "${MS_SYS_JAR_NAME}"
	OUTPUT_DIR "${MS_SYS_JAR_DIR}"
	GENERATE_NATIVE_HEADERS mssys-native
		DESTINATION "${MS_SYS_JNI_HEADER_DIR}"
)

if(Java_VERSION_MAJOR LESS 8)
create_javah(
	mssys-native
	CLASSES ${MS_SYS_JNI_LIST}
	CLASSPATH mssys-jar
	OUTPUT_DIR "${MS_SYS_JNI_HEADER_DIR}"
)
endif()

add_jar(
	mssys-test ${MS_SYS_JAVA_TEST_SOURCES}
	VERSION ${PROJECT_VERSION}
	INCLUDE_JARS mssys-jar
	OUTPUT_NAME "${MS_SYS_JAR_NAME}-test"
	OUTPUT_DIR "${MS_SYS_TEST_JAR_DIR}"
)

add_library(mssys-jni SHARED ${MS_SYS_JNI_SOURCES})

target_include_directories(mssys-jni PRIVATE
	"${JNI_INCLUDE_DIRS}"
	"${MS_SYS_JNI_HEADER_DIR}"
	"${MS_SYS_SOURCE_DIR}/inc"
	"${MS_SYS_SOURCE_DIR}/include-fallback"
	"${MS_SYS_JNI_SOURCE_DIR}/c"
)
target_link_libraries(mssys-jni PRIVATE mssys-native)

set_target_properties(mssys-jni PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${MS_SYS_NATIVE_LIB_DIR}")
target_compile_definitions(mssys-jni PUBLIC
	VERSION="${PROJECT_VERSION}"
	MS_SYS_VERSION="${MS_SYS_VERSION}"
	MS_SYS_JNI_VERSION="${PROJECT_VERSION}"
	MS_SYS_JNI_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
	MS_SYS_JNI_VERSION_MINOR=${PROJECT_VERSION_MINOR}
	MS_SYS_JNI_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)

# Collect all .img.xz files
file(GLOB IMG_FILES "${CMAKE_SOURCE_DIR}/src/test/res/*.img.xz")

foreach(IMG_FILE ${IMG_FILES})
	get_filename_component(FILE_NAME ${IMG_FILE} NAME_WE)  # Removes .xz
	set(DEST_PATH "${MS_SYS_WORK_DIR}/${FILE_NAME}.img")
	if(NOT EXISTS ${DEST_PATH})
		message(STATUS "Extracting src/test/res/${FILE_NAME}.img.xz -> out/test/work/${FILE_NAME}.img")
		execute_process(
			COMMAND ${CMAKE_COMMAND} -E make_directory "${MS_SYS_WORK_DIR}"
		)
		execute_process(
			COMMAND xz -dkc "${IMG_FILE}"
			OUTPUT_FILE "${DEST_PATH}"
			COMMAND_ERROR_IS_FATAL ANY
		)
	else()
		message(STATUS "Skipping src/test/res/${FILE_NAME}.img.xz (already extracted).")
	endif()
endforeach()

add_custom_target(run_ms_sys_test
	COMMAND	${Java_JAVA_EXECUTABLE} -Djava.library.path=${MS_SYS_NATIVE_LIB_DIR}
		-cp ""${MS_SYS_JAR_DIR}/${MS_SYS_JAR_NAME}.jar":"${MS_SYS_TEST_JAR_DIR}/${MS_SYS_JAR_NAME}-test.jar"" com.mssys.MsSysTest
	WORKING_DIRECTORY	"${MS_SYS_WORK_DIR}"
	COMMENT	"Running Java test class com.mssys.MsSysTest"
)

add_custom_target(ms_sys_test_run ALL DEPENDS run_ms_sys_test)
