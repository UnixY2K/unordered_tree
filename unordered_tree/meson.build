unordered_tree_incl = [
    include_directories('include'),
]

unordered_tree_srcs = files(
    'src/node.cpp'
)

# static link only library
unordered_tree_lib = static_library(
    'unordered_tree_static',
    unordered_tree_srcs,
    include_directories: unordered_tree_incl,
)

unordered_tree_dep = declare_dependency(
    include_directories: unordered_tree_incl,
    link_with: unordered_tree_lib,
)
