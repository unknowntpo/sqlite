

project('cdemo', 'c', 'cpp',
  # https://mesonbuild.com/howtox.html#set-default-cc-language-version
  default_options : ['cpp_std=c++11'])

# Demo module sources
module_sources = [
    'module/add.c'
]

# Dependencies
shared_dependencies = [
    dependency('glib-2.0')
]

includes_dir = include_directories([
    'include',
    'include/add'
])

gtest = subproject('gtest')

subdir('src')
subdir('test')
