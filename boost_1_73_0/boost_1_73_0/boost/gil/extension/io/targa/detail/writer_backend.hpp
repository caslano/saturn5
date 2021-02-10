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
3In4IW7VBNwcD2gDPS9toUMoY3mSHSnmoGjDg2bP0KesbDWxTa3+L2aGu5r5s/um3FqFgbp9V2x1hU4CquTfQbaVktFlbqfo+K9ij6GY/cE098JNBl3UIl5cXJzrPZHZnNNMBQtVTDQsYkGmlvLy1ZsC6oRYOfmuHtPGhEqEjiS6ljQIDHDpALB5yvUeWe85zLtv4aX+KKIZNA1jTSkLSvTSPtNIjvFkh67WRzG7CvDMhCqy4dckXtSeKkv7mCIpH0vK3pxQNX/20qjzM5LEWSlgudSPTm/ofafSqW+90/1ByhDEwkqwjHrq6qMYWB7MGuEfbFmIX9kIeY9MOdCetHyRhjCNtGE1lZHw5DjBA34xV2QbNYcor2MLxF/lpWYOjNkILg3bZV18cFCoVeaay5pDWu8P8obqUMRl7dmk98onw6pziKhxHwg3i1xMB1keqCELhE7QrpHav1aF0LQwHj8WJ4PBef/omB9k5XL4BctDNezj2wQPCnF5RCoP9WENPBynAQPX5xygo81ffV5OnZTjqo1OoSS7VOinenCVQ6tjVmaTiirOc35MpfA8L85UmI2GqH8rhIU/8z1d/Oha8Jo6RU1+nFheifzZxhlbWrBeS63zERGomdNfxojtrIwfFtDU+oDa1Zc3aiFj
*/