
test_srcs = files(
    'src/source.cpp',
)
test_deps = [
    catch2_dep,
]
test_args = []

test_exe = executable('testexe', test_srcs,
                     dependencies: test_deps)


test('unit tests', test_exe, args: test_args)
