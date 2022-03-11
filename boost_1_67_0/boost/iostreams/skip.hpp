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