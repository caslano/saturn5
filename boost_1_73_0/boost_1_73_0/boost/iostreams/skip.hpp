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
LDJ/uDYJ1x8u4mD5wzUUEX+4TA/1h8vV6P5wUIvoD+dFdfvD0Zh+fzgnossfTo/3Vv7wEEQSf7guj9Qfrk/D94cLWZj+cB1VzB8u1cT94RqKiD+cq4eutkK9Z8bJpP5wfS4Nf3gYKpk/XINJ4g9X1Gf4w1XUmf5wNW3YH85RRldjmB87BJHEH67LI/WH69Pw/eFCFqY/XEcV84dLNXF/uIYi4g+H9cj+cG5knz8cj0vxh/Oiuvzh3l9Ivvtd49eL8j5frHZ/Kezwr1x9LqbP+1/KaW5GDNLhqF8p8Hzk/Ow/UEsDBAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAlAAkAY3VybC1tYXN0ZXIvcHJvamVjdHMvV2luZG93cy9WQzkvbGliL1VUBQABtkgkYFBLAwQKAAAACAAtZ0pSDiSOSx0AAAAgAAAALwAJAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkM5L2xpYi8uZ2l0aWdub3JlVVQFAAG2SCRg09fSy0tO4tLX0isuzQdRpcWpRSC6LLmgKD+LCwBQSwMECgAAAAgALWdKUq3FtaRmBAAAID4AADAACQBjdXJsLW1hc3Rlci9wcm9qZWN0cy9XaW5kb3dzL1ZDOS9saWIvbGliY3VybC5z
*/