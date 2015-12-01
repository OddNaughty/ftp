# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable(serveur
        serveur/create.c
        serveur/func1.c
        serveur/interpret.c
        serveur/main.c
        serveur/tools.c
        serveur/func2.c)
add_executable(client
        client/main.c
        client/files.c
        client/create.c
)
# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries (client LINK_PUBLIC libft)
target_link_libraries (serveur LINK_PUBLIC libft)
