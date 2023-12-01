target("main")
    set_languages("c++23")
    set_kind("binary")
    add_files("src/*.cpp")
    set_rundir("$(projectdir)/runtime")

    after_build(function (target)
        if not os.isdir("$(scriptdir)/runtime") then
            os.mkdir("$(scriptdir)/runtime")
        end

        os.cp(target:targetfile(), "$(scriptdir)/runtime")
    end)