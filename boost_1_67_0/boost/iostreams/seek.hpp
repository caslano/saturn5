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