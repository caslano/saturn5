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
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
*/