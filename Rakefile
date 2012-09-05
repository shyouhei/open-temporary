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

soname = 'ext/open-temporary/open-temporary.so'

file soname => Dir.glob('ext/open-temporary/*') do
	Dir.chdir 'ext/open-temporary' do
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
	task spec: 'ext/open-temporary/open-temporary.so'

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
