project(
    'unordered_tree', 'cpp',
    default_options : ['cpp_std=c++20', 'warning_level=3'],
    license : 'BSD-3-Clause',
    version : '0.0.1',
)

# catch2 for unit tests
catch2_dep = dependency(
                'catch2',
                fallback: ['catch2', 'catch2_dep']
)


subdir('unordered_tree')

if get_option('UNORDERED_TREE_BUILD_TESTS')
    subdir('tests')
endif
if get_option('UNORDERED_TREE_BUILD_EXAMPLES')
    subdir('examples')
endif

