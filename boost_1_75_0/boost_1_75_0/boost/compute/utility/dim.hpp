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
IBpTaeN1uqLqz9221VFlOZXRrrLvTxV4cHEBApvvPoFwMbLVaHRLXR6efIqadMHstvO0tcvOOkvDj0dWRZdGOsNb7L3UonV6teVK/23RmAnaxHglThiv27rY7nw3VZ6m8orXJjRgn69J0LxPbISqBm36qdemkYHbwurucEsdcVumTY9EturoE/aNGCLToHTURJFW0sKWJYQnF9JFf8GZ0f7j/n3I/fueGW2LY+7fL3D//m2OS4EvT8OH+C2779zsvvNV953D7NsTCejUHqA/tX+XLvmPRlUmMpx01ET269TFJQ+5l++7l+fdy7+5F307XercS7t7+Zh7WeVeNriXbe7lv7mXve7lm+7lqHv5J/fyS/fyrnuJ3EGXU9xL2r0MuZe17uVP6eLUan2WtaSUHsgg3sah9s5CvM2HxBUY/39q/tiVdNH3cSwB8R6jrD9fHZvAswg9m0PP6G+T9MxCbL7rx5YcPwl+LG8Y253hx378UbavvUCVVz/q+t0Z8zI0drEt6qButdL6GZtogWv9b1jg2gBrVZz4hPge2ACN/TvFvmALqZJOif8eLFgT4Ql9jzVMrMYKy9iX6PdV+1VlhgDD/9Crb7i6gYup8h0qybBnQ9onYu5zN1mir+cNR9KuoXQiIfu0c9iLR/ea+oqXiKNuspZpWtsX2/aYc5YOb46cq6P3RHLOQKQjtjF+fmJN/Tsk1S4MJc+PJ2LZ
*/