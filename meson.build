# A meson file for building the svg path library
project('svgpath','cpp')

subdir('src/lib')

pkg = import('pkgconfig')
pkg.generate(
	libraries: libsvgpath,
	subdirs: 'include',
	version: meson.project_version(),
	name: 'svgpath',
	filebase: 'svgpath',
	description: 'A svg parsing library',
)
