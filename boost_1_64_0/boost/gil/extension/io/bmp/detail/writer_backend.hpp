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
fWBvJf6NnxppK56PPkeFQfBQNdzVI1qcUkE6dPLxUQRF8SYOs+qO/Xe0tozmDtz/pDPvTl2o20nQwonMVb5kw/1ZSMBK9+CCNDNII3VfwinDEOYyXeISohNrztxbbmz2THRlRFeP/wd1Fivjdx0SP9XxynFzJ3TEWsD6OLiGZNkDotwWf1WZBoVl0cb10IjY0MdCJS6hVxaGWvYp2SFXoA2chfm5CNRTQKcHHci/z1prFeN4Zgh02ZgLWsFdciKp9SBsPUF1rn+64tqgAd/YqD+4LzzFvbsgqZFYuAa0OGLDvLk9516YZKdkfrdoIYnx7JR9pOtRyoEJlag9D8Ud9YT9hFzcv93cUkivDXnW43X88zxpDeKiGpBD72uj2xCZ72LZpCLrxWY+Bs04VrfuEK4pr2SSU3uGh3pU1diQFFzvzU8t6ADsV5tnyI5A10LD2NP3X3tTCh3E2kQ58mJwQ3kILBVuF4pJFWVPDWPFT29AA0TPDAZClw3GBJMK+OP4i1+GSoIAl66XeiBjrUuNcfKzBznxBHsjvzietCe46LwfXd6xztXUUtF2sA==
*/