target_sources(romtiflam_core PRIVATE
    arm9_context.cpp
    arm9_exec_arm.cpp
    arm9.cpp
    decode9.cpp
)

add_subdirectory(thumb)