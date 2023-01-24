// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// To do: handle bidirection streams and output-seekable components.

#ifndef BOOST_IOSTREAMS_SKIP_HPP_INCLUDED
#define BOOST_IOSTREAMS_SKIP_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure.
#include <boost/iostreams/operations.hpp>
#include <boost/iostreams/seek.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename Device>
void skip(Device& dev, stream_offset off, mpl::true_)
{ iostreams::seek(dev, off, BOOST_IOS::cur); }

template<typename Device>
void skip(Device& dev, stream_offset off, mpl::false_)
{   // gcc 2.95 needs namespace qualification for char_traits.
    typedef typename char_type_of<Device>::type  char_type;
    typedef iostreams::char_traits<char_type>    traits_type;
    for (stream_offset z = 0; z < off; ) {
        typename traits_type::int_type c;
        if (traits_type::is_eof(c = iostreams::get(dev)))
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("bad skip offset"));
        if (!traits_type::would_block(c))
            ++z;
    }
}

template<typename Filter, typename Device>
void skip( Filter& flt, Device& dev, stream_offset off,
           BOOST_IOS::openmode which, mpl::true_ )
{ boost::iostreams::seek(flt, dev, off, BOOST_IOS::cur, which); }

template<typename Filter, typename Device>
void skip( Filter& flt, Device& dev, stream_offset off,
           BOOST_IOS::openmode, mpl::false_ )
{ 
    typedef typename char_type_of<Device>::type char_type;
    char_type c;
    for (stream_offset z = 0; z < off; ) {
        std::streamsize amt;
        if ((amt = iostreams::read(flt, dev, &c, 1)) == -1)
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("bad skip offset"));
        if (amt == 1)
            ++z;
    }
}

} // End namespace detail.

template<typename Device>
void skip(Device& dev, stream_offset off)
{ 
    typedef typename mode_of<Device>::type     mode;
    typedef mpl::or_<
        is_convertible<mode, input_seekable>,
        is_convertible<mode, output_seekable>
    >                                          can_seek;
    BOOST_STATIC_ASSERT(
        (can_seek::value || is_convertible<mode, input>::value)
    );
    detail::skip(dev, off, can_seek());
}

template<typename Filter, typename Device>
void skip( Filter& flt, Device& dev, stream_offset off, 
           BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    typedef typename mode_of<Filter>::type                 filter_mode;
    typedef typename mode_of<Device>::type                 device_mode;
    typedef mpl::or_<
        mpl::and_<
            is_convertible<filter_mode, input_seekable>,
            is_convertible<device_mode, input_seekable>
        >,
        mpl::and_<
            is_convertible<filter_mode, output_seekable>,
            is_convertible<device_mode, output_seekable>
        >
    >                                                      can_seek;
    BOOST_STATIC_ASSERT(
        ( can_seek::value || 
          (is_convertible<filter_mode, input>::value &&
          is_convertible<device_mode, input>::value) )
    );
    detail::skip(flt, dev, off, which, can_seek());
}

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_SKIP_HPP_INCLUDED //------------------------//

/* skip.hpp
GLV8p6L55zY5pjc2lqY3rSwhXI2BHUsnTCsHCwQHJqlfvkitrAxoV8pWD7ng/zU2dnBtTUsSbAFNYRVUplknZgtPOnOfKiwCviM5yAQ432FwhJmd+RTbOJgiPe2lPk6xlntPJp3ApZ20pqcLnJzqMCUXRUa27u4+//59HxpaJyERa0v311xi7lff7HRT1CxpUodL9l1PI7VeCGOD2o3/dFza2YjQPrFp4jW82vaov29HhQXQ3gN8M17Syg8xTSoTZ0k8WzsCJ//t4mlVuL2viVm8JS+nmE/DMJ2INvjUTwEzO2d9j1rnlhRnA8kEpRoWnS8u3y3iGzZIG2vQz6z9tVITD0vaxS1LWhO/vkr+5GZcTcORaPxrkFY3De+rhKQXN0dGkYVctvgBLnFXZbKKlRrl/7Ti3nz/UutweXP2zUpJEIsclb6+o5iE1uqCcG1erzNOywXPhlQvuXSuWKdee+T9LdaW4K/7rBz7q691BdNjg8MWhEVBjL+ZxWdh/NWLy/s+q5kqakKXF+0Yx9qwiFz8Ywj3JlF7BwXV3nftNOwOEjH0fgfdPYjOMDbJ4YnB8ZORlRjHijixKri0TTi4onVujKN/zW3t1zqBnd34aBkn2GEzlhx+V7TqCMIe3RRUS1T4fczdK3pjDXooeb366r7o7Cx0XOHW9bMYOtw1WXYTz9EBwMREFpXY3nnsr+2trd6gl8BTU2/32kfH
*/