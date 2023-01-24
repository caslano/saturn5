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
/CSMyvZizEIdnITgMoftpG18tai2IynTyIavWLCFXbC+/dW8wq5UbefOoIJwo37yq0uGZESzHPaZwfW7IQhtr3I+0CeVL6H2f0VfXzj+LBPyuWGJF26xXLfQZNnZ0O8Eq1QgB+bDfuur+R+M9JqEElz/fNjJ8GlmpOmj8kYFmC05vHv7Bk3xN4UxidAbJEaCLNPq0IzKsn8kc+oV0sYmfrXKcGA+CPQ0oL3V27TPO40V+BvTxSTlWeN+IH08+mPbS3CaSKmEebUndxMXJfhKYwwbdFGXqh2kUbIJG30NaSPi9aVdHqDoZUHqDm2AFw44sVP4Fz41qy/xVy4EA/lNMQhsrkf87WsZUltOZoddCAoMvTy+3/jPbZotfYfArbyfur4N801n5lUafcwB43YL46chN1zKEKVTOwW27OBZiX9oAmVHBByWaRCTZEO1vIjA1woShvu4slzHBnoBoSyrMUMiKTQjUnISeX1YP3OdEvXMQvLvJ9fwIjaDBpqkyW3rhN26eVRnFzLKN8ie+nZWY/gkPvJwmdKMYMvotUmVJBkmBZc562yRm38ztZHoRsL9DdtHYypU4KUwZuTrelZoesq+C34zV8NKveYeI1+gJv/SnbfOFUm4eRPL009jVndVSkwn6Wx0q5+xigo4XscYu/Tuv2lHHW9DYLQsiu9n7Ugft68rUp89B9CfHK02lcN053mzPkdgKUmIIK2q
*/