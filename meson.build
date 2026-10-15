project(
  'openlibm',
  'c',
  version : '0.8.8-taisei',
  meson_version : '>= 1.3.0',
  default_options : [
    'warning_level=0',
    'c_std=c99',
  ],
)

cc = meson.get_compiler('c')

c_args = cc.get_supported_arguments(
  '-Wall',
  '-Wno-unsupported-floating-point-opt',
  '-ffp-contract=off',
  '-fno-fast-math',
  '-fno-rounding-math',
  '-fno-math-errno',
  '-fno-builtin',
  '-fno-strict-aliasing',
  '-ffp-exception-behavior=strict',
  '-fno-gnu89-inline',
)

c_args += [
  '-DASSEMBLER',
  '-D__BSD_VISIBLE',
  '-DOLM_TAISEI_NO_EXPORT',
]

subdirs = [
  'aarch64',
  'amd64',
  'arm',
  'bsdsrc',
  'i387',
  'ld128',
  'ld80',
  'loongarch64',
  'mips',
  'powerpc',
  'riscv64',
  's390',
  'wasm32',
]

foreach dir : subdirs
  subdir(dir)
endforeach

arch_subdir_map = {
  'x86_64'  : 'amd64',
  'x86'     : 'i387',
  'ppc'     : 'powerpc',
}

arch = host_machine.cpu_family()
arch_subdir = arch_subdir_map.get(arch, arch)
arch_src_var = f'src_@arch_subdir@'

c_args += cc.get_supported_arguments({
  'x86_64'  : ['-m64', '-msse2', '-mfpmath=sse'],
  'x86'     : ['-march=i686', '-m32', '-msse2', '-mfpmath=sse'],
}.get(arch, []))

# Trick to thwart unneeded dllimport/dllexport and visibility("default") attributes
# Avoids warnings and lets unneeded functions be DCE'd from the executable even with --whole-arcive
public_c_args = ['-DOPENLIBM_DEFS_H_', '-DOLM_DLLEXPORT=']
c_args += public_c_args

have_fenv = true

if is_variable(arch_src_var)
  src = get_variable(arch_src_var, [])
else
  src = []
  have_fenv = false
  warning(f'No arch subdir for @arch@; fenv won\'t work')
endif

if host_machine.cpu_family() == 'wasm32'
  have_fenv = false
endif

enable_long_double = true

if host_machine.cpu_family() == 'wasm32'
  enable_long_double = false
endif

long_double_mdig = enable_long_double ? cc.get_define('LDBL_MANT_DIG', prefix : '#include <float.h>') : '53'

include_public = include_directories('include', 'src')
include_private = [include_public]

src += {
  '64'  : src_ld80,
  '113' : src_ld128,
}.get(long_double_mdig, [])

include_private += {
  '64'  : include_directories('ld80'),
  '113' : include_directories('ld128'),
}.get(long_double_mdig, [])

long_double_is_double = long_double_mdig == '53'
include_private += include_directories(arch_subdir)

subdir('src')
src += src_main
src += src_bsdsrc

filtered_src_stems = []
filtered_src = []

fs = import('fs')

foreach f : src
  stem = fs.stem(f)
  if stem not in filtered_src_stems
    filtered_src_stems += stem
    filtered_src += f
  endif
endforeach

openlibm_lib = static_library('openlibm', filtered_src,
  install : false,
  c_args : c_args,
  gnu_symbol_visibility : 'hidden',
  include_directories : include_private,
)

openlibm_dep = declare_dependency(
  include_directories : include_public,
  link_whole : openlibm_lib,
  compile_args : public_c_args,
)

meson.override_dependency('openlibm', openlibm_dep)

if host_machine.cpu_family() != 'wasm32'
  subdir('test')
endif
