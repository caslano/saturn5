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
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
*/