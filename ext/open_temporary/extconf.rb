require 'mkmf'
have_func("mkstemp", "stdlib.h") and
have_func("unlink", "unistd.h") and
create_makefile 'open_temporary'

# 
# Local Variables:
# mode: ruby
# coding: utf-8-unix
# indent-tabs-mode: t
# tab-width: 3
# ruby-indent-level: 3
# fill-column: 79
# default-justification: full
# End:
