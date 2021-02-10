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
BYWkrnxKuMZ4SvIf4oLdAjrPnC3NE3/FRXu3+cwQG1/Ext52tZfuOYcSdiTR31XHrbIyH8ZMvNKd7kLitNnd1LlvGp9HT1acp0pYQ7qA5tM8/7RaVNWQ7FViIl90C952B8ORUiz8OMRTpWcHGpmSfiZhuTx4/px3p/NLn36Vg4HUVH5sLEeGMIN/l0g0hnjtgJPnYV7mxMnMc0XKCqr9od0ddXvvYLenf7EyIlYLDMuKYQRHqq9SCSmAgyEBzKDz7xed4ahlhiRX2QgtJduRREriCDS8xKfwncfRgxmIfj/nJCDYVasXC7RWOrS37e4pSc3hjzG6EeH45uAvUYeXWSSat0k2dQSHd0G5k4PnB7wNF/13A/o97va6o4bwZOMOKUeYh2J66PJ0jsModoVvhm84QdfrqNN9H3TSuyTmbmuaC3p9OB/8jFRMldGVyZSjhQzH5TQN/oyJt4sL9tD8h+gkO6qsNUYNHAy1GtzlUXE/u4R2GGmvCvEdYj9wEi53mX5jc3eEE+CQBbrp6eesKEWUnTBt4NETyoId4U0nHp6ejzjrxvEgfv9N9GP0vCUxEZ/SaPP9N5tYXxGI1Eknmai754OQXhOkA4a0+f71ZjTNPqXs/gZ8zzMdLpJxKkHqgLu1yIsiu4SSepVN
*/