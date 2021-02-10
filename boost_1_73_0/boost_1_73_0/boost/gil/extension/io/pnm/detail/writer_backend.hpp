//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/pnm/tags.hpp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

///
/// PNM Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , pnm_tag
                     >
{
public:

    using format_tag_t = pnm_tag;

public:

    writer_backend( const Device&                      io_dev
                  , const image_write_info< pnm_tag >& info
                  )
    : _io_dev( io_dev )
    , _info( info )
    {}

public:

    Device _io_dev;

    image_write_info< pnm_tag > _info;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* writer_backend.hpp
IrFSyjHUxwHB9aQt0cZsNHbcxe36MJMoCvIsM29zWaDoQhmv5tnnWLCxZWtwsZj3MSHAcTaPSeBSIVrfRuYtuwksp96i5ip5HveGu5A2doFZhnrngiypNyhj70QjxM/iyHmqmaLl57xh76QAUz//LlZ1//ahO+Kcu+r53nf2yHh7brX70pETMPl9B0f9UTQ699M2MQfMDuf57HHvjtA44BV667GzSq0EJoRxTq5tq7d5dXJPjtpHJx0tkys3E5Q7sLDM70uHu2wXLm9o8n34+pQbTqInmTvrSbFDIMOT9qBz/BgQ9/fl3+G6wjD+iOyc2NkkyMCYRpt680FIbQJGzqsn4TtIvBcqdGE2nUvALzwSoHzitHiz5F76FDBeQ7+RYUbJPM1XRaAkDgta6EeZIxfb1B6Bs+Orh2RuflmCSHFd3PnvShBpsmx/aYLIehZGVqJqccK3XKQMwVWIhY0ytlFcZcppJkXG3iMlTgF8eATzzrLPxO67cF25QjZpOko1BYdwT9J/3oi0DaGi0x5+jM/a77pHce/i7E1nUHGPgCJ+llxn40MN8eZiaq2ovMtNTkWzUFUHNGS0Xaf0X1+TFhmMg/Ln7jSL11i1W1jl0pA9zmT8eFNtZ1UxC+dyaTxPVF19JsUYZlqEwfiK
*/