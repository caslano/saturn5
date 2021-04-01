// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_SEEK_HPP_INCLUDED
#define BOOST_IOSTREAMS_SEEK_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/integer_traits.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/ios.hpp>       // streamsize, seekdir, openmode.
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct seek_device_impl;

template<typename T>
struct seek_filter_impl;

} // End namespace detail.

template<typename T>
inline std::streampos
seek( T& t, stream_offset off, BOOST_IOS::seekdir way,
      BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    using namespace detail;
    return seek_device_impl<T>::seek(detail::unwrap(t), off, way, which); 
}

template<typename T, typename Device>
inline std::streampos
seek( T& t, Device& dev, stream_offset off, BOOST_IOS::seekdir way,
      BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    using namespace detail;
    return seek_filter_impl<T>::seek(detail::unwrap(t), dev, off, way, which);
}

namespace detail {

//------------------Definition of seek_device_impl----------------------------//

template<typename T>
struct seek_device_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          seek_device_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, iostream_tag, istream_tag, ostream_tag,
                  streambuf_tag, two_head, any_tag
              >::type
          >
      >::type
    { };

struct seek_impl_basic_ios {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    {
        if ( way == BOOST_IOS::beg &&
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.rdbuf()->pubseekpos(offset_to_position(off));
        } else {
            return t.rdbuf()->pubseekoff(off, way, which);
        }
    }
};

template<>
struct seek_device_impl<iostream_tag> : seek_impl_basic_ios { };

template<>
struct seek_device_impl<istream_tag> : seek_impl_basic_ios { };

template<>
struct seek_device_impl<ostream_tag> : seek_impl_basic_ios { };

template<>
struct seek_device_impl<streambuf_tag> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    {
        if ( way == BOOST_IOS::beg &&
             ( off < integer_traits<std::streamoff>::const_min ||
               off > integer_traits<std::streamoff>::const_max ) )
        {
            return t.BOOST_IOSTREAMS_PUBSEEKPOS(offset_to_position(off));
        } else {
            return t.BOOST_IOSTREAMS_PUBSEEKOFF(off, way, which);
        }
    }
};

template<>
struct seek_device_impl<two_head> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    { return t.seek(off, way, which); }
};

template<>
struct seek_device_impl<any_tag> {
    template<typename T>
    static std::streampos seek( T& t, stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode )
    { return t.seek(off, way); }
};

//------------------Definition of seek_filter_impl----------------------------//

template<typename T>
struct seek_filter_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          seek_filter_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<T, two_head, any_tag>::type
          >
      >::type
    { };

template<>
struct seek_filter_impl<two_head> {
    template<typename T, typename Device>
    static std::streampos seek( T& t, Device& d,
                                stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode which )
    { return t.seek(d, off, way, which); }
};

template<>
struct seek_filter_impl<any_tag> {
    template<typename T, typename Device>
    static std::streampos seek( T& t, Device& d,
                                stream_offset off,
                                BOOST_IOS::seekdir way,
                                BOOST_IOS::openmode )
    { return t.seek(d, off, way); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_SEEK_HPP_INCLUDED

/* seek.hpp
sz2eQ5ZhvnsLXKCcZguPkdTVuZj9dypS6cT04WzEoOCM+ymbGPdNSt0IvAuTmltnWbOjdHQXWt8h5WYNA/iC9828gjbE28tiT/2qN6+I+Ib8HVJNZgWg8DTb9K6ds8npDffj+zWMNTNR+2pGodHoX2APg/C3lIYGzusD7KwCYhs1CuLIps1J+j8zrinLk37UceZI6xc0XAUIb4SN6nMMBgP9ikZOse1hfroPq5W5lxOBBDT7C1Ebu3jNqBrcpI1WVBG8mEhDNM7OxCqw6Gmtedi9jbKiVYHwJ5fVvp1u6saXxOeteZdqQsMgs/+Xr9UpWfO766VprmZl4mnhCfc85GXU895crIEOiOqce+VwzFQR/uCWG6QIazf7GXoiNwon/H2BnDILEtThvs269yyHnD7GevRH9XjDS7Jl9YFHUp74MXdVipQ0E3BdfeFt0QDjOf9eAxCQKMQjIIvz+FHUBxuGzkVUqaigNB0Bv8ldW7A8tt9ORNt0JtBP7Ajpi8Apx+zax2TKtrakOjSFpnPRZUTLXY7B+eJg82DZEscEoruk720N+D+XlQzWkA==
*/