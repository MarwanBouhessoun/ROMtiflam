target_sources(romtiflam_core PRIVATE
    arm9_context.cpp
    arm9.cpp
    decode9.cpp
    update_flags.cpp
)

add_subdirectory(thumb)
add_subdirectory(arm)