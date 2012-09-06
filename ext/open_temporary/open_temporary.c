/* Copyright (c) 2012 Urabe, Shyouhei
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of  this software and  associated documentation  files (the  "Software"), to
 * deal in  the Software without restriction, including  without limitation the
 * rights to use, copy,  modify, merge, publish, distribute, sublicense, and/or
 * sell copies of  the Software, and to permit persons to  whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included
 *   in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF  ANY KIND, EXPRESS OR
 * IMPLIED,  INCLUDING BUT NOT  LIMITED TO  THE WARRANTIES  OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS  OR COPYRIGHT  HOLDERS BE  LIABLE FOR  ANY CLAIM,  DAMAGES  OR OTHER
 * LIABILITY,  WHETHER IN  AN ACTION  OF CONTRACT,  TORT OR  OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <ruby.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define preserving_errno(stmts) \
	do {int saved_errno = errno; stmts; errno = saved_errno;} while (0)

static VALUE tmpdir = Qundef;
static VALUE tmpsuf = Qundef;

struct fdopen_args {
    int fd;
    int mod;
    const char *str;
};

static VALUE
call_fdopen(VALUE args)
{
    struct fdopen_args *argp = (struct fdopen_args *)args;
    return rb_io_fdopen(argp->fd, argp->mod, argp->str);
}

static VALUE
open_temporary(int argc, VALUE* argv, VALUE klass)
{
    char* str = NULL;
    int   fd  = -1;
    VALUE buf = Qundef;
    VALUE dir = Qundef;
    VALUE suf = Qundef;
    int   mod = -1;

    rb_scan_args(argc, argv, "02", &dir, &suf);

    if (dir == Qnil) dir = tmpdir;
    if (suf == Qnil) suf = tmpsuf;

    SafeStringValue(dir);
    SafeStringValue(suf);

    buf = rb_sprintf("%s/%sXXXXXX", StringValueCStr(dir), StringValueCStr(suf));
    str = StringValueCStr(buf);
    if ((fd = mkstemp(str)) == -1) {
        rb_sys_fail("mkstemp(3)");
    }
    else if (unlink(str) == -1) {
        preserving_errno((void)close(fd));
        /* unlink failed, no way to reclaim */
        rb_sys_fail("unlink(2)");
    }
    else if ((mod = fcntl(fd, F_GETFL)) == -1) {
        preserving_errno((void)close(fd));
        rb_sys_fail("fcntl(2)");
    }
    else {
        int state;
        VALUE io;
        struct fdopen_args args;
        args.fd = fd;
        args.mod = mod;
        args.str = str;
        io = rb_protect(call_fdopen, (VALUE)&args, &state);
        if (state) {
            (void)close(fd);
            rb_jump_tag(state);
        }
        return io;
    }
}

extern void
Init_open_temporary(void)
{
    rb_require("tmpdir");
    tmpdir = rb_funcall(rb_cDir, rb_intern("tmpdir"), 0);
    tmpsuf = rb_str_new_cstr("tmp");
    rb_gc_register_mark_object(tmpdir);
    rb_gc_register_mark_object(tmpsuf);
    rb_define_singleton_method(rb_cFile, "open_temporary", open_temporary, -1);
}

/* 
 * Local Variables:
 * mode: C
 * c-file-style: "Stroustrup"
 * coding: utf-8-unix
 * indent-tabs-mode: nil
 * tab-width: 8
 * fill-column: 79
 * default-justification: full
 * End:
 */
