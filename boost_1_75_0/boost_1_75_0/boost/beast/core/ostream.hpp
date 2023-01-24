//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WRITE_OSTREAM_HPP
#define BOOST_BEAST_WRITE_OSTREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/detail/ostream.hpp>
#include <type_traits>
#include <streambuf>
#include <utility>

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
#include <boost/beast/core/make_printable.hpp>
#endif

namespace boost {
namespace beast {

/** Return an output stream that formats values into a <em>DynamicBuffer</em>.

    This function wraps the caller provided <em>DynamicBuffer</em> into
    a `std::ostream` derived class, to allow `operator<<` stream style
    formatting operations.

    @par Example
    @code
        ostream(buffer) << "Hello, world!" << std::endl;
    @endcode

    @note Calling members of the underlying buffer before the output
    stream is destroyed results in undefined behavior.

    @param buffer An object meeting the requirements of <em>DynamicBuffer</em>
    into which the formatted output will be placed.

    @return An object derived from `std::ostream` which redirects output
    The wrapped dynamic buffer is not modified, a copy is made instead.
    Ownership of the underlying memory is not transferred, the application
    is still responsible for managing its lifetime. The caller is
    responsible for ensuring the dynamic buffer is not destroyed for the
    lifetime of the output stream.
*/
template<class DynamicBuffer>
#if BOOST_BEAST_DOXYGEN
__implementation_defined__
#else
detail::ostream_helper<
    DynamicBuffer, char, std::char_traits<char>,
        detail::basic_streambuf_movable::value>
#endif
ostream(DynamicBuffer& buffer)
{
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    return detail::ostream_helper<
        DynamicBuffer, char, std::char_traits<char>,
            detail::basic_streambuf_movable::value>{buffer};
}

//------------------------------------------------------------------------------

#ifdef BOOST_BEAST_ALLOW_DEPRECATED
template<class T>
detail::make_printable_adaptor<T>
buffers(T const& t)
{
    return make_printable(t);
}
#else
template<class T>
void buffers(T const&)
{
    static_assert(sizeof(T) == 0,
        "The function buffers() is deprecated, use make_printable() instead, "
        "or define BOOST_BEAST_ALLOW_DEPRECATED to silence this error.");
}
#endif

} // beast
} // boost

#endif

/* ostream.hpp
GH47Sg0FmLDa9woKiO2GBnJH7rf75BNEdEwAM7CFlRCsU1Nh6EkJ2YKjPsRTwuAWEt50MxCjZX96tCdSLHApRDx9eCNQPFswpkWpMghQToNaZ30/DB9mgulnwXQwN6xJaRDrknTwJfiQRk08lIUjITiCOHHCGUJjYiybxm8Q621LgJK+kjhBxam2jRYYHYwGvqIiosmsDiawJjVKN6Lv6jdXzHPd5g4kpSEhFY52pW7UhhEL2wo9Yt75a/IzUo17Taiy3XzXtlhU35I/OhPUe3S92blBKSvmZf7HVJ5/Z2PEBeSKOfIRGXWIw3vwZ5v6zewK/BfxHb5kQKLK7Ro02H6ouyJvawGIiZn7vRHIswsZQKNITdpZqQkW841rHYZtV7laKUa1fLyE69efDFzPLKlKNTOLEQE+FrWimftxY0/mvZg0c4nl60zq3eTjv57gzpFQUxEoynSU+8eaiop/eOf7WAVH65TQyqSSxxU36lQl3/IktwTkId5r0m8l/cQuxgUksXed83QGnkHne+0nEaBXKpqtcsx/or2aBGO0sspU93eoz3XopgRgVtE98Ulh/q6FoCllIMacRcSnnUg2Ya2fjb+kVBQ7UJc/mFgcG1paEPvMwkm2akWxfibPrKBeNvjwuN5fZ0QtiwgTWkZHZPESUY0rWdoXB8R/T8cHoE3/ajjQ7NJMpY317/1x/Vn9BgfGAUEA30LwQBKA
*/