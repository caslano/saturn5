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
/LImjdz1IGx94T3WXE7wJevptOQPhS4jBq03dEHAR9i+/NzVk3qlTQHf+CRd7sinWN7fxl/wRNLzyiaflWLTWUG5BDjjrg2EMrDU0FiUz6qIHCjcu1DGX2avhVyuyvhw87+GIGitgBH2a1zls002N6UdK207R1kTJEQgqrYUtYrQWR9Qwqdr6myWIkPvewpyDnBnexz3b/OU/ikcYUg4rKx8Bxl/M6COLj6/l9HHAM9YgMnVsdFohiTeSAHDmcCP7+PVHym0VkijFFM8EV7D5HCnxHl5jLSE7KRDfOTFlDZz1TnNABZzNrGpQXO8D1/C8qZiKyuMdmTizyDUr7hcTQ+Caq5umEPijnm9a9K5w1ki+ODXubeOQ4fVrNDuYV45i/6s5aostyg+ZV0FB+/A7HO4j1taF/E0pS2XwHekuH9sPWyRdD+6HQN8bN9ojndxRMwn3Pa3vS/qU89/wmv3K8ZcA1ab5Ms7lvjRqLi0+6nBO++c5M4E9JTPvAE5Y9Q47e6LLP/26/5L42aTz8+TdZEFTKjEk3YiMZPGYaU7GIoGn7zWR0LwVup498DmbWbGaN9de/0omWzuNFKFnJv9pfdS8bdavF08muB4SzVqvKPAKODL/rTmZW9+xWD9MK5jnGuwwDNOBPU66ekxquLOcAHxiCnl/a6KUZy7AD9KR8Te7LILVHm8TccI8RFDJSqZplQ3zaZZhU8F7b75
*/