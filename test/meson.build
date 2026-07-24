
test_kwargs = {
  'dependencies' : openlibm_dep,
  'c_args' : ['-D__BSD_VISIBLE=1']
}

test('double', executable('test-double', 'test-double.c', kwargs : test_kwargs))
test('float', executable('test-float', 'test-double.c', kwargs : test_kwargs))
