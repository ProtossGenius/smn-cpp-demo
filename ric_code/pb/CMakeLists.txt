# 查找当前目录下的所有源文件

# 并将名称保存到 DIR_LIB_SRCS 变量

aux_source_directory(. pb_src)

# 生成链接库

add_library (ric_pb ${pb_src})

