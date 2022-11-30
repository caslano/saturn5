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
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
*/