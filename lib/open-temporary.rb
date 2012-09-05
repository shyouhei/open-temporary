# Copyright (c) 2012 Urabe, Shyouhei
#
# Permission is hereby granted, free of  charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without  restriction, including without limitation the rights
# to  use, copy, modify,  merge, publish,  distribute, sublicense,  and/or sell
# copies  of the  Software,  and to  permit  persons to  whom  the Software  is
# furnished to do so, subject to the following conditions:
#
#    The above copyright notice and this permission notice shall be included
#    in all copies or substantial portions of the Software.
#
# THE SOFTWARE  IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY  KIND, EXPRESS OR
# IMPLIED,  INCLUDING BUT  NOT LIMITED  TO THE  WARRANTIES  OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# AUTHORS  OR COPYRIGHT  HOLDERS  BE LIABLE  FOR  ANY CLAIM,  DAMAGES OR  OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

require 'open_temporary.so'

class File
  @@open = self.method(:open)

  # If non-zero numbers of args are passed, works as it ought.
  # otherwise creates and opens a temporay file.
  def self.open(*argv, &block)
    if argv.size.nonzero?
      @@open.call(*argv, &block)
    else
      self.open_temporary(&block)
    end
  end
end

module Kernel
  @@open = self.method(:open)

  # If non-zero numbers of args are passed, works as it ought.
  # otherwise creates and opens a temporay file.
  def open(*argv, &block)
    if argv.size.nonzero?
      @@open.call(*argv, &block)
    else
      File.open(&block)
    end
  end    
end

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
