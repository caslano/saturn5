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
ufeY/suf8XmMw+mMjVrE2MWv+PAf/w3z2YYOH85Yz3vBOp+XfZn9e/H3HRiv0ZdgzkCOuZvDbcw6Xnx/bxb6D/1o3VnU338CxnY05sufUH9zqftniO+HIKOz3gR/tzF2GOoc9zhj78GOt70CPj+AnTqKse1OQ91lovxProQ9nCdt9AxOH3X2gRw+hFyPhp3atIFd9SX05Ydh/pr2E99HocxPV8O2o3pvZ7jcU9tAliME7TOh
*/