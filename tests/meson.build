
test_srcs = files(
    'src/node_value.cpp',
    'src/node.cpp',
    'src/scalar_value.cpp',
    'src/source.cpp',
)
test_deps = [
    catch2_dep,
    unordered_tree_dep,
]
test_args = []

test_exe = executable('testexe', test_srcs,
                     dependencies: test_deps)


test('unit tests', test_exe, args: test_args)
