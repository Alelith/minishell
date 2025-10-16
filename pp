
minishell~> export a= b=o
==38654== Invalid read of size 1
==38654==    at 0x4067C8: str_len (str_len.c:20)
==38654==    by 0x406038: str_compare_all (str_compare_all.c:20)
==38654==    by 0x405B32: exists_env (exists_env.c:22)
==38654==    by 0x404F6F: save_var (export.c:43)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Address 0x4b9d100 is 0 bytes inside a block of size 2 free'd
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A2B: update_env (update_env.c:24)
==38654==    by 0x404F15: save_var (export.c:37)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Block was alloc'd at
==38654==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x406D30: str_substring (str_substring.c:26)
==38654==    by 0x4059A6: get_key (dict_utils.c:17)
==38654==    by 0x404EA4: save_var (export.c:31)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654== 
==38654== Invalid read of size 1
==38654==    at 0x406083: str_compare_all (str_compare_all.c:24)
==38654==    by 0x405B32: exists_env (exists_env.c:22)
==38654==    by 0x404F6F: save_var (export.c:43)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Address 0x4b9d100 is 0 bytes inside a block of size 2 free'd
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A2B: update_env (update_env.c:24)
==38654==    by 0x404F15: save_var (export.c:37)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Block was alloc'd at
==38654==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x406D30: str_substring (str_substring.c:26)
==38654==    by 0x4059A6: get_key (dict_utils.c:17)
==38654==    by 0x404EA4: save_var (export.c:31)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654== 
==38654== Invalid read of size 1
==38654==    at 0x4060B8: str_compare_all (str_compare_all.c:26)
==38654==    by 0x405B32: exists_env (exists_env.c:22)
==38654==    by 0x404F6F: save_var (export.c:43)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Address 0x4b9d100 is 0 bytes inside a block of size 2 free'd
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A2B: update_env (update_env.c:24)
==38654==    by 0x404F15: save_var (export.c:37)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Block was alloc'd at
==38654==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x406D30: str_substring (str_substring.c:26)
==38654==    by 0x4059A6: get_key (dict_utils.c:17)
==38654==    by 0x404EA4: save_var (export.c:31)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654== 
==38654== Invalid read of size 1
==38654==    at 0x4067C8: str_len (str_len.c:20)
==38654==    by 0x406038: str_compare_all (str_compare_all.c:20)
==38654==    by 0x405A16: update_env (update_env.c:22)
==38654==    by 0x404F8C: save_var (export.c:44)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Address 0x4b9d100 is 0 bytes inside a block of size 2 free'd
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A2B: update_env (update_env.c:24)
==38654==    by 0x404F15: save_var (export.c:37)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Block was alloc'd at
==38654==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x406D30: str_substring (str_substring.c:26)
==38654==    by 0x4059A6: get_key (dict_utils.c:17)
==38654==    by 0x404EA4: save_var (export.c:31)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654== 
==38654== Invalid read of size 1
==38654==    at 0x406083: str_compare_all (str_compare_all.c:24)
==38654==    by 0x405A16: update_env (update_env.c:22)
==38654==    by 0x404F8C: save_var (export.c:44)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Address 0x4b9d100 is 0 bytes inside a block of size 2 free'd
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A2B: update_env (update_env.c:24)
==38654==    by 0x404F15: save_var (export.c:37)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Block was alloc'd at
==38654==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x406D30: str_substring (str_substring.c:26)
==38654==    by 0x4059A6: get_key (dict_utils.c:17)
==38654==    by 0x404EA4: save_var (export.c:31)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654== 
==38654== Invalid read of size 1
==38654==    at 0x4060B8: str_compare_all (str_compare_all.c:26)
==38654==    by 0x405A16: update_env (update_env.c:22)
==38654==    by 0x404F8C: save_var (export.c:44)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Address 0x4b9d100 is 0 bytes inside a block of size 2 free'd
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A2B: update_env (update_env.c:24)
==38654==    by 0x404F15: save_var (export.c:37)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Block was alloc'd at
==38654==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x406D30: str_substring (str_substring.c:26)
==38654==    by 0x4059A6: get_key (dict_utils.c:17)
==38654==    by 0x404EA4: save_var (export.c:31)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654== 
==38654== Invalid free() / delete / delete[] / realloc()
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A2B: update_env (update_env.c:24)
==38654==    by 0x404F8C: save_var (export.c:44)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Address 0x4b9d100 is 0 bytes inside a block of size 2 free'd
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A2B: update_env (update_env.c:24)
==38654==    by 0x404F15: save_var (export.c:37)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Block was alloc'd at
==38654==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x406D30: str_substring (str_substring.c:26)
==38654==    by 0x4059A6: get_key (dict_utils.c:17)
==38654==    by 0x404EA4: save_var (export.c:31)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654== 
==38654== Invalid free() / delete / delete[] / realloc()
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A38: update_env (update_env.c:25)
==38654==    by 0x404F8C: save_var (export.c:44)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Address 0x4b9d150 is 0 bytes inside a block of size 1 free'd
==38654==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x405A38: update_env (update_env.c:25)
==38654==    by 0x404F15: save_var (export.c:37)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)
==38654==  Block was alloc'd at
==38654==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==38654==    by 0x4065F0: str_duplicate (str_duplicate.c:20)
==38654==    by 0x4059D5: get_value (dict_utils.c:22)
==38654==    by 0x404EE4: save_var (export.c:35)
==38654==    by 0x404E5A: export (export.c:58)
==38654==    by 0x4030C2: switch_commands (utils1.c:26)
==38654==    by 0x40375D: execute_builtin (utils2.c:21)
==38654==    by 0x403952: fork_and_execute (utils2.c:56)
==38654==    by 0x4054E1: try_command (try_command.c:93)
==38654==    by 0x401376: main (main.c:67)

                                                                 
                                                                    
                                                                    
                                                                    
                                                                    OTRO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


minishell~> </<</>/>>
Syntax error: redirection without file/limiter
Permission denied: /
==44768== Syscall param access(pathname) points to unaddressable byte(s)
==44768==    at 0x49DC9BB: access (access.c:27)
==44768==    by 0x401C9D: check_file (tokenizer_redir.c:19)
==44768==    by 0x401EEE: proccess_redir (tokenizer_redir.c:54)
==44768==    by 0x401BE0: handle_redir_token (tokenizer.c:35)
==44768==    by 0x401A50: tokenize (tokenizer.c:57)
==44768==    by 0x40545E: try_command (try_command.c:85)
==44768==    by 0x401376: main (main.c:67)
==44768==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==44768== 
==44768== Syscall param openat(filename) points to unaddressable byte(s)
==44768==    at 0x49DC5AB: open (open64.c:41)
==44768==    by 0x401F20: proccess_redir (tokenizer_redir.c:55)
==44768==    by 0x401BE0: handle_redir_token (tokenizer.c:35)
==44768==    by 0x401A50: tokenize (tokenizer.c:57)
==44768==    by 0x40545E: try_command (try_command.c:85)
==44768==    by 0x401376: main (main.c:67)
==44768==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==44768== 
==44768== Invalid read of size 8
==44768==    at 0x401996: tokenize (tokenizer.c:52)
==44768==    by 0x40545E: try_command (try_command.c:85)
==44768==    by 0x401376: main (main.c:67)
==44768==  Address 0x4b70108 is 8 bytes after a block of size 128 alloc'd
==44768==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==44768==    by 0x40635D: callocation (callocation.c:19)
==44768==    by 0x406404: reallocation (reallocation.c:26)
==44768==    by 0x40267D: split_command (split_command.c:34)
==44768==    by 0x402028: get_tokens (tokenizer_utils.c:28)
==44768==    by 0x401972: tokenize (tokenizer.c:51)
==44768==    by 0x40545E: try_command (try_command.c:85)
==44768==    by 0x401376: main (main.c:67)

Da tres errores en tres bloques distintos.







                                        TERCER ERROR!!!!!!!!!!!!!

minishell~> echo hola > file > file2 > file3 | ls
'<'     file2   include   Makefile    obj   src
 file   file3   lib	  minishell   pp
==45369== 
==45369== HEAP SUMMARY:
==45369==     in use at exit: 208,539 bytes in 242 blocks
==45369==   total heap usage: 1,259 allocs, 1,017 frees, 252,480 bytes allocated
==45369== 
==45369== 2 bytes in 1 blocks are definitely lost in loss record 1 of 71
==45369==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==45369==    by 0x4065F0: str_duplicate (str_duplicate.c:20)
==45369==    by 0x401F76: proccess_redir (tokenizer_redir.c:58)
==45369==    by 0x401BE0: handle_redir_token (tokenizer.c:35)
==45369==    by 0x401A50: tokenize (tokenizer.c:57)
==45369==    by 0x40545E: try_command (try_command.c:85)
==45369==    by 0x401376: main (main.c:67)
==45369== 
==45369== LEAK SUMMARY:
==45369==    definitely lost: 2 bytes in 1 blocks
==45369==    indirectly lost: 0 bytes in 0 blocks
==45369==      possibly lost: 0 bytes in 0 blocks
==45369==    still reachable: 208,537 bytes in 241 blocks
==45369==         suppressed: 0 bytes in 0 blocks
==45369== Reachable blocks (those to which a pointer was found) are not shown.
==45369== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==45369== 
==45369== For lists of detected and suppressed errors, rerun with: -s
==45369== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)


