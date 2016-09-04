set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-access-control -DJUCI_BUILD_PATH=\\\"${CMAKE_BINARY_DIR}\\\" -DJUCI_TESTS_PATH=\\\"${CMAKE_CURRENT_SOURCE_DIR}\\\"")

set(stub_files
    ${CMAKE_CURRENT_SOURCE_DIR}/stubs/config.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/stubs/dialogs.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/stubs/directories.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/stubs/info.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/stubs/selectiondialog.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/stubs/terminal.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/stubs/tooltips.cc
)

add_library(stubs OBJECT ${stub_files})

include_directories(${global_includes})

add_executable(process_test process_test.cc
               $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
target_link_libraries(process_test ${global_libraries})
add_test(process_test process_test)

add_executable(compile_commands_test compile_commands_test.cc
               $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
target_link_libraries(compile_commands_test ${global_libraries})
add_test(compile_commands_test compile_commands_test)

add_executable(filesystem_test filesystem_test.cc
               $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
target_link_libraries(filesystem_test ${global_libraries})
add_test(filesystem_test filesystem_test)

add_executable(cmake_build_test cmake_build_test.cc
               $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
target_link_libraries(cmake_build_test ${global_libraries})
add_test(cmake_build_test cmake_build_test)

add_executable(meson_build_test meson_build_test.cc
               $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
target_link_libraries(meson_build_test ${global_libraries})
add_test(meson_build_test meson_build_test)

add_executable(source_test source_test.cc
               $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
target_link_libraries(source_test ${global_libraries})
add_test(source_test source_test)

add_executable(source_clang_test source_clang_test.cc
               $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
target_link_libraries(source_clang_test ${global_libraries})
add_test(source_clang_test source_clang_test)

if(LIBLLDB_FOUND AND (NOT LIBCLANG_LIBRARIES STREQUAL "/usr/lib/llvm-3.5/lib/libclang.so"))
  add_executable(lldb_test lldb_test.cc
                 $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
  target_link_libraries(lldb_test ${global_libraries})
  add_test(lldb_test lldb_test)
  add_subdirectory("lldb_test_files")
endif()

add_executable(git_test git_test.cc
               $<TARGET_OBJECTS:project_shared> $<TARGET_OBJECTS:stubs>)
target_link_libraries(git_test ${global_libraries})
add_test(git_test git_test)
