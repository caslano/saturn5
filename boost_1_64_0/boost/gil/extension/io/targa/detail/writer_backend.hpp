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
fvxVQmkTR94dDByFRCH855nxIb0cGBHbYgYEdBlSHvrvGv0wfEaBP6x5uDf8w7N0rsGvHRX77ftiXaIh2OZLLkLjj2BafDDCIENfbvOwqcBpwMpVgSETCsZWWevmfklGN5dWHXdSW3+GpeFc77S6/4aK32Z2htDldgzTYNwAAw4QKsLEvcFLh3F/J28fhUjmFyIjIXEeMZ+dvLcnUDPPQWVZgZEi2AhbubrxtkrWv7G7EK76h2lnPSVpuc58S9dHOscuB1h9lpZ0VlcJ/QFCTcxWdrWEftQAj57DPas5EIxAHHLIS6qQx/Koz3BQ269eYIAjhuHnYLf6TLh+1UEr7eYlg6mqpHcoBUvaa4oukZ8KtdCqIaxZemvMS/oJPBKDfkpkZtwJnj+F/lHDRxVbwWIFIn0RBCYtFsWkFY7NI553WgAaTdfX8uc+dnj5lTZkjODBFSUr1K3wPCv2tyDEJOxsdMXB18H8W6URuEykzFziImOJkfqipVEVKXuGx5vsK4ueBaSqUCxQpilqcdfycM8QPWs+3bF+jmILHxPnhi+T/31WlA0SnIQybg==
*/