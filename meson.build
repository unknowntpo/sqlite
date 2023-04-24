

project('sqlite', 'c', 'cpp',
  # https://mesonbuild.com/howtox.html#set-default-cc-language-version
  default_options : ['cpp_std=c++11'])

# Demo module sources
module_sources = [
    'add/add.c',
    'db/db.c'
]

# Dependencies
shared_dependencies = [
    dependency('glib-2.0')
]

includes_dir = include_directories([
    'include',
    'include/add',
    'include/db'
])

gtest = subproject('gtest')

subdir('src')
subdir('test')
