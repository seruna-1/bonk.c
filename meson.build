project('bonk_c', 'c',
	version : '0.1',
	default_options : ['c_std=c11', 'warning_level=3', 'werror=true']
)

raylib_dep = dependency('raylib', required: true)
enet_dep = dependency('libenet', required: true)
box2d_dep  = dependency('box2d', required: true)

cc = meson.get_compiler('c')

subdir('src')

executable('server',
	server_src,
	install : false,
	include_directories: [
		'include'
	],
	dependencies: [
		enet_dep,
		box2d_dep,
	],
)

executable('client',
	client_src,
	install : false,
	include_directories: [
		'include'
	],
	dependencies: [
		enet_dep,
		box2d_dep,
		raylib_dep,
	],
)