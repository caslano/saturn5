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
VJ6LVK5n5XpXe0+3G2y3zhjvMBIAa5NivLV3pYvMDECIt1kFfzWt+So7403X5hvRjBci668oRbOztVn8rYlotgbY364oYBOxlQo16nR3dwRWke+ae6Wnz92uL4R9Zg546ZPTeUV62WsZWFWLUQx7e7z8qgID2Zi84ZlN8Vrno/Q6nvUMXfFVU/2FeJmJ3lvwp79b8wRIei1fS7e/y2M9HR6/MmWgVw2Eerh88Ecgmw+/DPXWpKBP1DNvGjZuGQ0=
*/