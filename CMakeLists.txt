cmake_minimum_required(VERSION 4.3)
project(foundation LANGUAGES CXX)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

# CMake's default flags are dropped; every flag is listed below.
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")
set(CMAKE_STATIC_LINKER_FLAGS "")
set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "")
set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "")

# These two are target settings, not flags: CMake adds them itself.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL") # /MDd, /MD
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT Embedded)                         # /Z7

set(output_dir ${CMAKE_BINARY_DIR}/bin/$<LOWER_CASE:$<CONFIG>>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${output_dir})

# ---------------------------------------------------------------------------
# fndlib
# ---------------------------------------------------------------------------
file(GLOB_RECURSE fndlib_modules CONFIGURE_DEPENDS src/foundation/*.ixx)
file(GLOB_RECURSE fndlib_sources CONFIGURE_DEPENDS src/foundation/*.cpp)

add_library(fndlib STATIC ${fndlib_sources})
target_sources(fndlib PUBLIC FILE_SET CXX_MODULES BASE_DIRS src FILES ${fndlib_modules})
target_include_directories(fndlib PUBLIC src)
target_compile_features(fndlib PUBLIC cxx_std_20) # /std:c++20

# PUBLIC: whatever links fndlib is compiled with the same options.
# No /EH*: the project is built without exceptions.
target_compile_options(fndlib PUBLIC
  /nologo
  /permissive-
  /utf-8
  /W4
  /WX-
  /diagnostics:caret
  /errorReport:prompt
  /FC              # full paths in __FILE__ (FND_ASSERT)
  /GR-             # no RTTI
  /GS
  /sdl
  /fp:precise
  /Gd
  /Zc:wchar_t
  /Zc:forScope
  /Zc:inline
  /FAs             # assembly listings with source
  /FAu             # ...UTF-8 encoded
  /Fa${output_dir}/asm/
  $<$<CONFIG:Debug>:/Od /RTC1 /JMC->
  $<$<CONFIG:Release>:/O2 /GL>
)

target_compile_definitions(fndlib PUBLIC
  _CRT_SECURE_NO_WARNINGS
  WIN32_LEAN_AND_MEAN
  NOMINMAX
  UNICODE
  _UNICODE
  _WINDOWS
  $<$<CONFIG:Debug>:_DEBUG FND_DEBUG>
  $<$<CONFIG:Release>:NDEBUG>
)

set_target_properties(fndlib PROPERTIES STATIC_LIBRARY_OPTIONS $<$<CONFIG:Release>:/LTCG>)

# ---------------------------------------------------------------------------
# unittests
# ---------------------------------------------------------------------------
file(GLOB_RECURSE unittests_modules CONFIGURE_DEPENDS src/unittests/*.ixx)
file(GLOB_RECURSE unittests_sources CONFIGURE_DEPENDS src/unittests/*.cpp)

add_executable(unittests ${unittests_sources})
target_sources(unittests PRIVATE FILE_SET CXX_MODULES BASE_DIRS src FILES ${unittests_modules})
target_link_libraries(unittests PRIVATE fndlib)
target_link_options(unittests PRIVATE
  /DEBUG
  $<$<CONFIG:Release>:/INCREMENTAL:NO /LTCG /OPT:REF /OPT:ICF>
)
