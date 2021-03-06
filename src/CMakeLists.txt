foreach(SUBDIR doom)
    add_subdirectory("${SUBDIR}")
endforeach()

# Common source files used by absolutely everything:

set(COMMON_SOURCE_FILES
    i_main.c
    i_system.c           i_system.h
    m_argv.c             m_argv.h
    m_misc.c             m_misc.h)

# Dedicated server (chocolate-server):

set(DEDSERV_FILES
    d_dedicated.c
    d_iwad.c            d_iwad.h
    d_mode.c            d_mode.h
    i_timer.c           i_timer.h
    m_config.c          m_config.h
    net_common.c        net_common.h
    net_dedicated.c     net_dedicated.h
    net_io.c            net_io.h
    net_packet.c        net_packet.h
    net_sdl.c           net_sdl.h
    net_query.c         net_query.h
    net_server.c        net_server.h
    net_structrw.c      net_structrw.h
    z_native.c          z_zone.h)

add_executable("${PROGRAM_PREFIX}server" WIN32 ${COMMON_SOURCE_FILES} ${DEDSERV_FILES})
target_include_directories("${PROGRAM_PREFIX}server"
                           PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/../")
target_link_libraries("${PROGRAM_PREFIX}server" SDL2::SDL2main SDL2::net)

# Source files used by the game binaries (chocolate-doom, etc.)

set(GAME_SOURCE_FILES
    d_event.c           d_event.h
                        doomkeys.h
                        doomtype.h
    d_iwad.c            d_iwad.h
    d_loop.c            d_loop.h
    d_mode.c            d_mode.h
                        d_ticcmd.h
    i_endoom.c          i_endoom.h
    i_glob.c            i_glob.h
    i_input.c           i_input.h
    i_joystick.c        i_joystick.h
                        i_swap.h
    i_musicpack.c
    i_sdlmusic.c
    i_sdlsound.c
    i_sound.c           i_sound.h
    i_timer.c           i_timer.h
    i_video.c           i_video.h
    m_bbox.c            m_bbox.h
    m_cheat.c           m_cheat.h
    m_config.c          m_config.h
    m_controls.c        m_controls.h
    m_fixed.c           m_fixed.h
    net_client.c        net_client.h
    net_common.c        net_common.h
    net_dedicated.c     net_dedicated.h
    net_defs.h
    net_gui.c           net_gui.h
    net_io.c            net_io.h
    net_loop.c          net_loop.h
    net_packet.c        net_packet.h
    net_petname.c       net_petname.h
    net_query.c         net_query.h
    net_sdl.c           net_sdl.h
    net_server.c        net_server.h
    net_structrw.c      net_structrw.h
    sha1.c              sha1.h
    tables.c            tables.h
    v_diskicon.c        v_diskicon.h
    v_video.c           v_video.h
                        v_patch.h
    w_checksum.c        w_checksum.h
    w_main.c            w_main.h
    w_wad.c             w_wad.h
    w_file.c            w_file.h
    w_file_stdc.c
    w_file_posix.c
    w_merge.c           w_merge.h
    z_zone.c            z_zone.h)

set(GAME_INCLUDE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/../")

set(SOURCE_FILES ${COMMON_SOURCE_FILES} ${GAME_SOURCE_FILES})

set(EXTRA_LIBS SDL2::SDL2main SDL2::SDL2 SDL2::mixer SDL2::net)

if(PNG_FOUND)
    list(APPEND EXTRA_LIBS PNG::PNG)
endif()

add_executable("${PROGRAM_PREFIX}doom" ${SOURCE_FILES})

target_include_directories("${PROGRAM_PREFIX}doom" PRIVATE ${GAME_INCLUDE_DIRS})
target_link_libraries("${PROGRAM_PREFIX}doom" doom ${EXTRA_LIBS})
