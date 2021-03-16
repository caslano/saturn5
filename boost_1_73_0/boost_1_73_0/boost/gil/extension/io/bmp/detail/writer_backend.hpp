//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/bmp/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// BMP Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , bmp_tag
                     >
{
public:

    using format_tag_t = bmp_tag;

public:

    writer_backend( const Device&                      io_dev
                  , const image_write_info< bmp_tag >& info
                  )
    : _io_dev( io_dev )
    , _info  ( info   )
    {}

public:

    Device _io_dev;

    image_write_info< bmp_tag > _info;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* writer_backend.hpp
i/Ichsgir6WSI4uQeSw4Uci1Gm10e0a4C7FGXNO3NvS510P9SGV6qGdaeoZi0eKPV6mX0Te3Ip+ZO+I4M7PXHGNkDwI33CedYRVeiOkuA4oK+v8tjqg/5oDweSMOXLc/4rjXRhz32cjiIaIVtg4hf4DoRKI/IIpbdT/RM2wdQoccKQsdSux9MnaVYNcLdqNgiDMYK9EOA6MD5F62VNsosrbr9yVgrKlFNFg/I9zN3CeADXtt+MVE4cx4XmBmfFo=
*/