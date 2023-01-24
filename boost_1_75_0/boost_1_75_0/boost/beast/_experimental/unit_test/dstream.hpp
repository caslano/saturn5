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
gLieG00G4gqUrPWBOT9fEtjcfKKEY4YiYay9hm5HDqWrl69uvs7n5wP5fibfl/O1jK89hrItZ7HWZz2b2hRqV6zXTW2KteMftza1mYIIvsupk8Vmu+3ZJA4RF0+vaZfzR5dzn9/NlzU++Fj/xs6PTd94rv1vfDhJfOPwM7KFl+k17Qtu+wa+vj60vdhfr51ywrw7U2e0e8xdQ8fcqwGboqHHsBkdOeuOPJ6stO0xN/FquZzjr25lPwx9PdzN6KsPYn8d0fOHGK5zW6ab84dkQf4Q4lpeU9jX8+/446Cj6nUFvYlVPGy6gqKvsxUZ91iPQXO6CxNlrhdHGnDTCqUKDiF7FoXPFF8p9arT4SVwCAEx9BSVfWigL9nTO2JVfdWxZEW3pdaBu+QqORu3679Gwq+uSnK5NuyqdnyOv0qLkbN8bfV/rObZkakpouWrcB0d1Zh2AqZlGW7MxMpbyVks3VU7mZmedO32p4h2vMBIOV29ujla5xnT4IkXracj/UmCeemnXtscXecZ8zk6hoiJufsJ08ScWQ3GgWthKGS//D64cZ3Uw7n3URPsWGQ5V7jkHGW5COSLrmqVu6MgOCnddaNgjMtphG849Lkq5WBrwDihxX2tmLFa9AOtMsNTnnrUlb2gBgFqv82QUO8k5fX661sM2fNOsgK//D8gE80RsBjoDJdMRxVkOhO0UtCrg5DYCGegoQWF2pycLJ09
*/