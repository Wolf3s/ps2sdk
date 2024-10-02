function(compile_multiple target srcfile)
    cmake_parse_arguments(PARSE_ARGV 2 "arg" "" "" "OBJECTS")

    foreach(obj ${arg_OBJECTS})
        add_library(${obj} OBJECT ${srcfile})
        get_filename_component(def ${obj} NAME_WLE)
        target_compile_definitions(${obj} PRIVATE "F_${def}")
        target_include_directories(${obj} PRIVATE ${EE_INC})
        target_link_libraries(${target} private ${obj})
    endforeach()
endfunction()

