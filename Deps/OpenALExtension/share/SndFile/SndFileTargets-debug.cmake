#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SndFile::sndfile" for configuration "Debug"
set_property(TARGET SndFile::sndfile APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(SndFile::sndfile PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/sndfile.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "Vorbis::vorbisenc;FLAC::FLAC;Opus::opus"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/sndfile.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS SndFile::sndfile )
list(APPEND _IMPORT_CHECK_FILES_FOR_SndFile::sndfile "${_IMPORT_PREFIX}/debug/lib/sndfile.lib" "${_IMPORT_PREFIX}/debug/bin/sndfile.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
