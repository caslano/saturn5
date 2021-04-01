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
/vT7RzoXnEAlrHZrgk/D0mA2QcJ3Yxa585362xxb/iY9XZCbUJCk3pankn+kamtLp+EM7ATp6uPYfBMlD5kxezEgX19BNY/FPLa/cIk0Hd6yzXVLMoPsMidZCGhQuli07Ceq52JgAH2r7DqwQ0u8nu8b3Bt7KSoPLdwGBt26GQDpIkxpwrW5CeZzxY1H5MzBXahjoaSJMVG3fPlqrXdWjy1dmmf2v51m6daUxn8tGWPHv8hPdKRQjjgP7RueRC69wEiPuy5gSxPrSJ2Hqefuid52GcVNXOj93xf52HpT4k9+JEJMalF5i9jYI+ldjaw6iyJb2aCoYW7Jc+LKqZOKm/he/T7vP7e4davJaGTRFFvc/ooEWPEl3yMAkhcY50Dpdn6I0ErVnFjTVExpsrzEbaTANnykbsJxMecGwy5HpX0JauFVYz2LEkP+WuKBECBmAeIBRB2H0+ILi8FHGJqtvMhjOnZfxXV/VD32FLSVZPfRJI915D+FXrUo1qf56KR0YDeu35KbiQsoGMH8ZiV8KTbr//wOiQhsbEl2GD3Aq0DdZR6L3i3tGskquQ==
*/