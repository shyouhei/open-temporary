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

static VALUE tmpdir = Qundef;
static VALUE tmpsuf = Qundef;

static VALUE
open_temporary(int argc, VALUE* argv, VALUE klass)
{
    char* str = NULL;
    int   fd  = -1;
    VALUE buf = Qundef;
    VALUE dir = Qundef;
    VALUE suf = Qundef;

    rb_scan_args(argc, argv, "02", &dir, &suf);

    if (dir == Qnil) dir = tmpdir;
    if (suf == Qnil) suf = tmpsuf;
    
    SafeStringValue(dir);
    SafeStringValue(suf);

    buf = rb_sprintf("%s/%sXXXXXX", StringValueCStr(dir), StringValueCStr(suf));
    str = StringValueCStr(buf);
    fd = mkstemp(str);
    if (fd == -1) {
        rb_sys_fail("mkstemp(3)");
    }
    else if (unlink(str) == -1) {
        /* unlink failed, no way to reclaim */
        rb_sys_fail("unlink(2)");
    }
    else {
        return rb_io_fdopen(fd, 0600, str);
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
