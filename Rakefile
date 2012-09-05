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

require 'rubygems'
require 'bundler'
begin
	Bundler.setup(:default, :development)
rescue Bundler::BundlerError => e
	$stderr.puts e.message
	$stderr.puts "Run `bundle install` to install missing gems"
	exit e.status_code
end
require 'rake'
require 'rake/clean'
# use 'rake clean' and 'rake clobber' to
# easily delete generated files
CLEAN.include('ext/**/*{.o,.log,.so}')
CLOBBER.include('ext/**/Makefile')

soname = 'ext/open_temporary/open_temporary.so'

file soname => Dir.glob('ext/open_temporary/*.{rb,c}') do
	Dir.chdir 'ext/open_temporary' do
		ruby 'extconf.rb'
		sh 'make'
	end
end

begin
	require 'rspec/core'
	require 'rspec/core/rake_task'
	RSpec::Core::RakeTask.new(:spec) do |spec|
		spec.pattern = FileList['spec/**/*_spec.rb']
	end
	task spec: soname

	require 'yard'
	YARD::Rake::YardocTask.new

	require 'jeweler'
	Jeweler::Tasks.new do |gem|
		# gem is a Gem::Specification... see http://docs.rubygems.org/read/chapter/20 for more options
		gem.name = "open-temporary"
		gem.homepage = "http://github.com/shyouhei/open-temporary"
		gem.license = "MIT"
		gem.summary = "A variant of Tempfile that makes File instead"
		gem.description = "A variation of tempfile standard lib, that actually creates a File instance."
		gem.email = "shyouhei@ruby-lang.org"
		gem.authors = ["Urabe, Shyouhei"]
		# dependencies defined in Gemfile
	end
	Jeweler::RubygemsDotOrgTasks.new
rescue LoadError
	# OK, they can be absent on non-development mode.
end

task default: soname

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
