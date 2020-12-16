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
6j+oTP9kOqQR9aEapV6QotE+Ui9VjZZHdWOBx6jnq5pFadZRXzub0sxpDNJpvGwXhxDdoUR3zvRxT9p1VtyhRvU+t3H6GCpzmQMWpR47H8E2fITlyXt+hzdqXshbxJAe2WjG4iEHW052G24UdrtfMVxWdxs93dWT7hoay8Vq4VOV3jqQIeL7F02NBZs6ivjpvI5uZJ8My3F0XXDsexJoyH7Y58J42M+xAg+YeaR9HQf84pKyi+8eFV65Xp4sZM0jhbzT4WQRfxcWd26iKNr+uTwnke02UPqnNCrGNcwO4p5KOm8t2DXyBYZizZ7eWIg1uz4QUztxofUFcZzZmtQ4+/wNrEZNLItu6d14ATw5Ej7bwBW/16qJ7lS+wOtQ8EqM53NxxWmQ/8RAHO6jmIAdoemSyUTWILLQuR2PTwna58CFA4NdawZXUkck3kvGKqcT4svr7oXraAHbp9XHjW7NrffLqVzVXhzXqY0uxg7xoORrXyjkbC6Tp82HzwFNrE5Bf7n4oF45O3gN4Hq/lBGPFGLpFzcG1o/6u8CsDfNWThdl6LUuTm8s57svr3udfgn3bbaMTfYMTnaEohzkfXHtiiP+GNat94Cy2fgYrt7XtGeRbttEmfv0/RouqdOwBPEevBwf0ThNSC0lGBTvJPtZjVPv3X62N9aczW3Pj7HC2EBt79zGMvf7lIhv1+k6GoP+4aWNFC/k7VV0Ai5ptN58mi4rp+bJ/eYKb6zrprK1Uj+5kvtBzZd5ctlXefj87CB+jSfX04rI3uvxWOrp93wPP9/LY8DLQz9+HmsFj+4icl7APIAvIeeFkqaEjp/n5ePL+nzJo4SsESo/4FwHRfcvKrR5s/co5kFH10+16Rjlif+NnHF6z/P+Br97e29yXGI+bP8Xax0E4kbyHBt1uslrY06/L6X4+WRjJf4648vOZzIopJlCn3XW4nZVuO/Dk2Gc2mBKjH9LRBu4xGvjGbyf4dlglnjkmBb8ZRvAOLqE7uLqwzgq5xazvLnDZGPQj/Qo4c8Q77Ju/PSXkSxIL/sG48N+MXB5z55eImxuFvHzbe6lxPNyTxdaJp2PzP8K7u8sXur6FY1cFjkHC58u5v+v8vqcK6WuAX81tyGLA5z1pfO/GjA/vjNXJL7zNbZMkEWWyZb/tV79XqvfGc+8+IzP64nXGxr9/T3dhm3+Up9vIv5/DrMeuB2cauxej/5ZVdjTH07lMei58fwtcn5T5l4up8NTPZt/myhPi7ib5lRq39cLfGM9aDz8Dq5ji5e8b/DS6jQy7bv5nemZF/4MDunM33tJr6d6NvE+j8f7PRu5gdLdW6Qv+yBwsn1+iNPyO9O3hu0j8R8Bvidwn5L9irWMsaglmIxX3WG/w8/frL/B7Imilxq2fqQaMP+YqNe0PU/iIlHk6dFiCO7Lz/bOon/Cq/tP4r3oOnI/87tV9Hk5zoN1aPI/QQV1fpuH13qU+M8Cdgzws3iPnO//99rxLPV5qusdYm30F7EHeLjwDRwqft9XP7Wt3qFl8drqnSyrpTnVs5dd3H+KuHXiAVszPL5GY0BanBuT5X1WHefBcsg87vb6NMCLxqzvduNyiXrQaWW+36Y539mi//2u19a+57Wt71Ma2C+n+YHX7+m8WovEzNzrratP9OzifsprVpjjQYReptLvBT3H3Ug7mY2nSNzNT6keoDu+m8+zM358O/s517PtL++R8sy25fsl2eKDng5bgJdt8NckR15885PrV5bDq9/fib7yC167/gPLB5yn/2rS/8OerZr8vTp6hGR7KpVvIc9XyLa9OngU9BLf6tnYPoFHWk6fJ/zfGE969/CPUTlbmN7hOc6Hy5QvmgcwTYI=
*/