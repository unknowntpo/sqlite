test_sources = []

foreach source_path : module_sources
  test_sources += '../src/' + source_path
endforeach

# https://gerrit.openbmc.org/plugins/gitiles/openbmc/gpioplus/+/3f49f01e3da03c41c0b53b55c8d53afff96190a6/test/meson.build

# Ref: https://mesonbuild.com/Subprojects.html#using-a-subproject
gtest_dep = gtest.get_variable('gtest_dep')
thread_dep = dependency('threads', required: true)

# https://gerrit.openbmc.org/plugins/gitiles/openbmc/stdplus/+/458aeae0c60c5c3afbfd5c87bd8637372b26e93d/test/meson.build
assert(gtest_dep.found())

gtest_module = executable('gtest_module', [test_sources, 'add/gtest_add.cpp'],
    dependencies : [shared_dependencies, gtest_dep, thread_dep],
    override_options: ['cpp_std=c++11'],
    include_directories: [includes_dir]
)

test('Gtest Test Valid', gtest_module)

gtest_db = executable('gtest_db', [test_sources, 'db/gtest_db.cpp'],
    dependencies : [shared_dependencies, gtest_dep, thread_dep],
    override_options: ['cpp_std=c++11'],
    include_directories: [includes_dir]
)

test('Test DB', gtest_db)
