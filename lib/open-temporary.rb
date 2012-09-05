require 'open_temporary.so'

class File
  @@open = self.method(:open)
  def self.open(*argv, &block)
    if argv.size.nonzero?
      @@open.call(*argv, &block)
    else
      self.open_temporary
    end
  end
end

module Kernel
  @@open = self.method(:open)
  def open(*argv, &block)
    if argv.size.nonzero?
      @@open.call(*argv, &block)
    else
      File.open
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
