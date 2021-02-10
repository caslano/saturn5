//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_UTILITY_DIM_HPP
#define BOOST_COMPUTE_UTILITY_DIM_HPP

#include <boost/compute/config.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {

#ifndef BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
/// The variadic \c dim() function provides a concise syntax for creating
/// \ref extents objects.
///
/// For example,
/// \code
/// extents<2> region = dim(640, 480); // region == (640, 480)
/// \endcode
///
/// \see \ref extents "extents<N>"
template<class... Args>
inline extents<sizeof...(Args)> dim(Args... args)
{
    return extents<sizeof...(Args)>({ static_cast<size_t>(args)... });
}

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1800)
// for some inexplicable reason passing one parameter to 'dim' variadic template 
// generates compile error on msvc 2013 update 4
template<class T>
inline extents<1> dim(T arg)
{
    return extents<1>(static_cast<size_t>(arg));
}
#endif // BOOST_WORKAROUND(BOOST_MSVC, <= 1800)

#else
// dim() function definitions for non-c++11 compilers
#define BOOST_COMPUTE_DETAIL_ASSIGN_DIM(z, n, var) \
    var[n] = BOOST_PP_CAT(e, n);

#define BOOST_COMPUTE_DETAIL_DEFINE_DIM(z, n, var) \
    inline extents<n> dim(BOOST_PP_ENUM_PARAMS(n, size_t e)) \
    { \
        extents<n> exts; \
        BOOST_PP_REPEAT(n, BOOST_COMPUTE_DETAIL_ASSIGN_DIM, exts) \
        return exts; \
    }

BOOST_PP_REPEAT(BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_DETAIL_DEFINE_DIM, ~)

#undef BOOST_COMPUTE_DETAIL_ASSIGN_DIM
#undef BOOST_COMPUTE_DETAIL_DEFINE_DIM

#endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

/// \internal_
template<size_t N>
inline extents<N> dim()
{
    return extents<N>();
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_UTILITY_DIM_HPP

/* dim.hpp
Jw12hTFP1z0J4YVqYt7kV1LlahmjZyNd8DynhN+gCYZSyEV5Q72KRVEZ5UMpheynEkkgUm33lSgdC3G6SGxw25NDz6zWwrSA3qz5kjIrUZpSQiqdTrje9XnZdzDKbb179ZqXBb2QqUU5dg9H45Ph+bMe/GPPedrtTOHoX4j+6h6/uHr+atD/Y7//eBr+udeDvW6414tWpuaiV3+30xAG0KE1172jbucg6Dyi7xAtIztpZEPNt5bFloEhNb6GVxHxK2JsCKMWG10NDn3T6Bxs/N9/ERJFshMcyuWTOM2XHj8cXoIr06QcbnaOhqZJaFL67XJQcG0eh3Sy3h1odsVYtrw/TKK4Fee5mfdauRhux3jvee+9/wBQSwMECgAAAAAALWdKUgAAAAAAAAAAAAAAAB4ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9VVAUAAbZIJGBQSwMECgAAAAgALWdKUvt/TJeRAgAAwgUAACwACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DTWFrZUxpc3RzLnR4dFVUBQABtkgkYK1SbU/bMBD+3l9xCnxIp9Ag9mkTmpa1BSpoqNoiVAnJcuNL4y2xI9vhRcB/3zm0wKSiahKu2rPde17ufHtf
*/