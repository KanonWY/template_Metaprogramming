


# 查找目录下的所有 cpp 文件
file(GLOB SOURCES "*.cpp")
message(STATUS "----> SOURCE" ${SOURCES})

# 遍历每个 cpp 文件并生成对应的可执行程序
foreach (SOURCE ${SOURCES})
    # 获取文件名（不带后缀）
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    # 将该文件编译成可执行程序
    add_executable(${EXECUTABLE_NAME} ${SOURCE})
    target_link_libraries(${EXECUTABLE_NAME} yaml-cpp pthread)
endforeach ()
