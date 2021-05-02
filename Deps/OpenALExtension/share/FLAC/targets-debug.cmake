#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "FLAC::FLAC" for configuration "Debug"
set_property(TARGET FLAC::FLAC APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(FLAC::FLAC PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/FLAC.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/FLAC.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS FLAC::FLAC )
list(APPEND _IMPORT_CHECK_FILES_FOR_FLAC::FLAC "${_IMPORT_PREFIX}/debug/lib/FLAC.lib" "${_IMPORT_PREFIX}/debug/bin/FLAC.dll" )

# Import target "FLAC::FLAC++" for configuration "Debug"
set_property(TARGET FLAC::FLAC++ APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(FLAC::FLAC++ PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/FLAC++.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/FLAC++.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS FLAC::FLAC++ )
list(APPEND _IMPORT_CHECK_FILES_FOR_FLAC::FLAC++ "${_IMPORT_PREFIX}/debug/lib/FLAC++.lib" "${_IMPORT_PREFIX}/debug/bin/FLAC++.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
