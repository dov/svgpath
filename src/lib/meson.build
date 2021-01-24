cairo_dep = dependency('cairo')
inc = include_directories('.')
deps = [cairo_dep]
libsvgpath = library('svgpath',
                     ['cairocontext.cpp',
                      'svgpath.cpp',
                     ],
                     dependencies : deps)

libsvgpath_dep = declare_dependency(
  include_directories : inc,
  link_with : libsvgpath)

install_headers(['svgpath.h'],
                subdir : 'svgpath')
