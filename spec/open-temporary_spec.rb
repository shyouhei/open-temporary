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

require_relative 'spec_helper'

describe File do
	describe "#open" do
		context "when passed nothing" do
			subject { File.open }
			it { should be_kind_of(File) }
			its(:size) { should be_zero }
			its(:path) { File.exist?(subject).should be_falsy }
			it("can be written") { expect { subject.write("foo") }.to_not raise_error }
			it("can be seeked")  { expect { subject.rewind }.to_not raise_error }
			it("can be read")    { expect { subject.read }.to_not raise_error }
			context "when passed block" do
				it "yields" do
					ex = Exception.new
					expect do
						File.open do |f|
							f.should be_kind_of(File)
							raise ex
						end
					end.to raise_exception(ex)
				end
			end
		end
		context "when passed something" do
			subject { File.open IO::NULL }
			it { should be_kind_of(File) }
			its(:path) { File.exist?(subject).should be_truthy }
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
