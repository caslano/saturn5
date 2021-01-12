//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/targa/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// TARGA Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , targa_tag
                     >
{
public:

    using format_tag_t = targa_tag;

public:

    writer_backend( const Device&                        io_dev
                  , const image_write_info< targa_tag >& info
                  )
    : _io_dev( io_dev )
    , _info( info )
    {}

public:

    Device _io_dev;

    image_write_info< targa_tag > _info;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* writer_backend.hpp
3pU7l5cT9+xLyDQOSX4dj9s80iHZXhcp2w23lH1bcuDCRdw6kRv5hlNcxXPXURQnExVpPLGpwnNeSA7SZoCTzH2rLvOAxxP8Sv+QDG6JlMEWild9QbB/M/b4iFu563ISmfPsLViivNPtlO/wO2DS3LNIAmT/fgz6xaHeHoXUxcYtRe7SXcDvknzmAW/OKkZYoHsie9CkJI/Vezabk7KHFkW9QYXU23JLFbGTu3wt/y0jWym6
*/