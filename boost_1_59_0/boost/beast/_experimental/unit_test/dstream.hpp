//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_DSTREAM_HPP
#define BOOST_BEAST_UNIT_TEST_DSTREAM_HPP

#include <boost/config.hpp>
#include <ios>
#include <memory>
#include <ostream>
#include <sstream>
#include <streambuf>
#include <string>

#ifdef BOOST_WINDOWS
#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/debugapi.hpp>
#endif

namespace boost {
namespace beast {
namespace unit_test {

#ifdef BOOST_WINDOWS

namespace detail {

template<class CharT, class Traits, class Allocator>
class dstream_buf
    : public std::basic_stringbuf<CharT, Traits, Allocator>
{
    using ostream = std::basic_ostream<CharT, Traits>;

    ostream& os_;
    bool dbg_;

    template<class T>
    void write(T const*) = delete;

    void write(char const* s)
    {
        if(dbg_)
            boost::winapi::OutputDebugStringA(s);
        os_ << s;
    }

    void write(wchar_t const* s)
    {
        if(dbg_)
            boost::winapi::OutputDebugStringW(s);
        os_ << s;
    }

public:
    explicit
    dstream_buf(ostream& os)
        : os_(os)
        , dbg_(boost::winapi::IsDebuggerPresent() != 0)
    {
    }

    ~dstream_buf()
    {
        sync();
    }

    int
    sync() override
    {
        write(this->str().c_str());
        this->str("");
        return 0;
    }
};

} // detail

/** std::ostream with Visual Studio IDE redirection.

    Instances of this stream wrap a specified `std::ostream`
    (such as `std::cout` or `std::cerr`). If the IDE debugger
    is attached when the stream is created, output will be
    additionally copied to the Visual Studio Output window.
*/
template<
    class CharT,
    class Traits = std::char_traits<CharT>,
    class Allocator = std::allocator<CharT>
>
class basic_dstream
    : public std::basic_ostream<CharT, Traits>
{
    detail::dstream_buf<
        CharT, Traits, Allocator> buf_;

public:
    /** Construct a stream.

        @param os The output stream to wrap.
    */
    explicit
    basic_dstream(std::ostream& os)
        : std::basic_ostream<CharT, Traits>(&buf_)
        , buf_(os)
    {
        if(os.flags() & std::ios::unitbuf)
            std::unitbuf(*this);
    }
};

using dstream = basic_dstream<char>;
using dwstream = basic_dstream<wchar_t>;

#else

using dstream = std::ostream&;
using dwstream = std::wostream&;

#endif

} // unit_test
} // beast
} // boost

#endif

/* dstream.hpp
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
*/