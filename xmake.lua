add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})

set_project("First_2d_Sidescroller")

if is_plat("windows") then
    set_languages("cxxlatest")

    -- bruh
    --add_defines("_WIN32_WINNT=0x0601")

    add_cxflags("/Zc:__cplusplus")
    add_cxflags("/Zc:preprocessor")

    add_cxflags("/permissive-")
else
    set_languages("cxx20")
end

add_requires("libsdl")
add_requires("libsdl_image")
add_requires("libsdl_mixer")
add_requires("libsdl_ttf")

set_warnings("allextra")

if is_mode("debug") then
    add_defines("DEBUG")
end
if is_mode("release") then
    add_defines("NDEBUG")

    if is_plat("windows") then
        --add_cxflags("/favor:AMD64")
        --add_cxflags("/O2")
        --add_cxflags("/Oi")
        --add_cxflags("/Ot")
        --add_cxflags("/arch:AVX2")
        --add_cxflags("/fp:fast")
        --add_cxflags("/GL")
        --add_cxflags("/Qfast_transcendentals")
        --add_cxflags("/Qpar")
    else
    end
end

target("First_2d_Sidescroller")
    set_kind("binary")

    add_packages("libsdl")
    add_packages("libsdl_image")
    add_packages("libsdl_mixer")
    add_packages("libsdl_ttf")

    add_includedirs("src")

    add_headerfiles("src/**.h")

    add_files("src/**.cpp")

    --after_build(function (target)
    --    import("core.project.config")
    --    os.cp("config", path.join(config.buildir(), config.plat(), config.arch(), config.mode()))
    --    os.cp("Resources", path.join(config.buildir(), config.plat(), config.arch(), config.mode()))
    --end)
    --after_install(function (target)
    --    import("core.project.config")
    --    os.cp("config", target.installdir())
    --    os.cp("Resources", target.installdir())
    --end)
