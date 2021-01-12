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
i47yymsRzgR2Rf8maYjKfNvHp0DyM0mZYA46pfU6pUXzz0lM9IYs420ZptDxklHqq5tHFwm64Z2LuSHv+d54cdoGF2sg6+nQpLnJWGk3xEUr4cJfSV+Cv3hxTBU9+98HdzyJmZ57+gAwPIQRe7x8uUyk/JEeCdOFC3QRojhZ8hQNIajMrO6WB6r86HmDJrqX4cM3UvCM2V7u8K3WMAXHf88G1SMTOmO7+BcRm+3py5D0/1Z/
*/