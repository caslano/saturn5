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