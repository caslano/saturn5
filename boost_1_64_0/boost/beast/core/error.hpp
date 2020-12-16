//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_ERROR_HPP
#define BOOST_BEAST_ERROR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

namespace boost {
namespace beast {

/// The type of error code used by the library
using error_code = boost::system::error_code;

/// The type of system error thrown by the library
using system_error = boost::system::system_error;

/// The type of error category used by the library
using error_category = boost::system::error_category;

/// A function to return the generic error category used by the library
#if BOOST_BEAST_DOXYGEN
error_category const&
generic_category();
#else
using boost::system::generic_category;
#endif

/// A function to return the system error category used by the library
#if BOOST_BEAST_DOXYGEN
error_category const&
system_category();
#else
using boost::system::system_category;
#endif

/// The type of error condition used by the library
using error_condition = boost::system::error_condition;

/// The set of constants used for cross-platform error codes
#if BOOST_BEAST_DOXYGEN
enum errc{};
#else
namespace errc = boost::system::errc;
#endif

//------------------------------------------------------------------------------

/// Error codes returned from library operations
enum class error
{
    /** The socket was closed due to a timeout

        This error indicates that a socket was closed due to a
        a timeout detected during an operation.

        Error codes with this value will compare equal to @ref condition::timeout.
    */
    timeout = 1
};

/// Error conditions corresponding to sets of library error codes.
enum class condition
{
    /** The operation timed out

        This error indicates that an operation took took too long.
    */
    timeout = 1
};

} // beast
} // boost

#include <boost/beast/core/impl/error.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/error.ipp>
#endif

#endif

/* error.hpp
1wNvBTZy39uFdG+m+3rufwOJ+5d0v0/3X0w35WcX5edu7pO8n/XRosZkyDnL5QDVsVyPs1z7uV/sCcr108B5wO8AVwK/y31zz7DdDgCfBX4P+HPg94HvAp/lvq/ngJuA1jf+F0H5tFetf7c/ATK/1x8G4bu8+iaPb+783g7UvqEn5Hh+I99XhO/doBOg5Hn4Hg4qBjXM6/5m3X11X91X99V9dV/dV/fVfXVf3Vf39d90feXf/5uaG+Xz/2n4/v9n7ft/Mc8mvQvUm+tDL0KhpihH1lOnzV9cVDy3bG312qr1um042sJXa/zkT1a28evEvdUoxd+N/CaI2+JXU+0FQMvGRa3wbTFKkLPzQVyDZXqJmo3GlbV1mo3GlRJ+KVZTF0ucIhVH13uuq61nnForHCU9C3Fo/83HNn+b8MwxMvAFRrd1vIx2TrI7WRfPUzbspH7EL190UEw/lN3HhiHK5WPDEPn2tjnO/QcbuU+jCTQ93sB5THo7QUisdlL1Bj9t78FI4V9pOJT9CSuNWJ+6ZlswvMirXvldwSu8QatTa428ScJTLBnAhXow41NW1jA8Fd8lSlHhTwdj/Qn5cAQNCAtyhDjsofYh5o9I33KpMiyRNMJpixS5EXci+kW4xFkv962rrtfsm04RnnTtW760dae2KTzPC0A+6DfOT5vmddCmBWFcs2ObXgQKhT76Ae82rUejBi47+ePV962finuttHGku9+xPS3+HPCbbnzZYF0FG1EB+9trwjMd6WnnXFBu/MlFrQovAYfV7msrWqQJwGPthRkjNuwDyk6ihKfLN6vh6AMHQ7GGHgfZCB5ij8Dmj+B45FGVUaWvyvoXyUOU37JGsqyG0aDy8wcJ73daZIK2Zay+T3nwlZF8XxlRezbe4vLgTzg+PwPKzUKOx3js2VixfuXImuoWyiLKFSJtCO+V1aYX+4UVb5YxHBKnvo1p/QL3IE+84aQ95svF/RS+loUataZMqbY6T+3TGDrW5AmjvMBD3BOMofCLZH6Qshr3r5E07xJb96Xgcbd/sxghjaWMPSN8l5r1j39LYoIN07Zx18dkJ+s8ROpcrw/Uu/rWJeWXs2suhmzl1wWjDVCdVbWrDC9b3gd6qO+PCmcnmB9bPNoDkSvxPB9ZW99sSPlTpJ4rpb6CDIs/jW5YqBon41endkd7Io+mo8jk19wOumON0JgvJG0jvaBwxHiDfp+5/cZZfn92+421/D5w+42x/H7n9htt+f3a7Zdj+f3C7TfK8vup22+k5feq22+E5feS2y9b+i/8nlV+48X9HeUeJ+7HlXusuPcq9xhxP6Dco8W9W7lz1F6NFGn/So82bqMN+c1g7k2c3QdjzzjvNkZ/GwmZCjw2M06Kei4dE3dv9VyKDfPsf3MYx7LhtQju98W90laFWeYHILcNr8q6WvYVJ/D68SbfRYg5XOI64WoQv18ag+C7xMiXuCmuuDUG4/YBNgnfL3Ce7xD6WXEXGsHwjTXjSf9EsV1FVjbkBwpfli0LtfhtUKTiPU/Nq6qF5/dIbQDHdlisF79Yv+PDH6XMlSizDWW26fmus/IdC7xY0rgf48hler3U1Gp7LG4WnmLDjmdefzxHnkMfTnZYc4ze5tQiwh4KiAwP2I5/Zf/0ascO5xe/EZ7x8iwZjLErQptLPhVrEm2ykyq6MJ5x7ugz9yg1MYxjmfeZCD0NuYYxoUzQRNMuZq6HPGOSD0t0HnP8DSO0Zwf5h6GuE1Q9HDD94O6F+2nxRqpnsIoXLHHmwf2ouDOwI6GfNj+p57xC3cfHVp2yUS7hPem28hABtyVHlSP0/UevSniYvzx3Ot562qpGffjYqmZZ4ZegnvX1HvU=
*/