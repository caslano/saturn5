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
P9b0Iz4nv4FwPiefON6E8zn5GsJlXs25PcJVVxl8s04Y4dOD/unLb4WH9sPn0C8DQ3zA/gkMeWZzB2BWet8Fhrwzn3rArLn3WYVRePfc+5ltwM2mDPzlHcBZ/WP+uxO42czRj8Ru4Gzu/tKeJpy3mceafO9r8Pac/M8PaYy3FcwPby9sl/NDb2nWo9tdlPCxqRHzDuUxcx8yEn7kZY5TPfCZG9Z5UxRfc5ts8K2cVPsGrVtmVG9428pV9QZZjNH1KDBbHmuHHyhOC280At7SWDcPb7s087ptnTxSIHvXe3q8m4eaQj2qvUxw7XnPM3sNDMLGntgk6VXPo2UPw1zhKMLx4cL+h4FRT8B8wAiXLU75GTon7817zukzfW/EfA7p9HWPtPHeLzCePvYbgSMtYEe2NBjyB128qDCk1xpnHx8DbvVE45uyHRyzVwH/2w7gZs9BXf1zZ4OjNgb3eif5PeEwTCI3z+/7fV97HjnxbooPFzdpkUZqBr7WxkmVwG+1cCqS0fcOt+M38aud+FHgdzvxaeD1U218w9jDuWHhp6Z4+SbeY+O8fGstnJfvVhufY+V/r43z8l1t4bx8d1s4L199hOFykczLd6OF8/JNvM/GefnW2vgcK38L5+WbfL+N8/JdbeNUPnU2lKhxoQjyPHGasYHCAxlONxzOOG4ezJBbOzVe4zsrdN+22jQ4rzIOa3d0Fop+3uZgbx9xXRnKmwbnz4zD2ik4/jZw7L4GziuMw/obOGPbwbHbPDjznRxe/l8M5fDyH9nRxePlv9rJ4eW/28nh5a/Huzi8/DcYh/UJcCZ2dnF4+TeGcnj5X+vk8fI/s6uLw8v/cieHl/+/nRxd/mavdTdxgHeeGx3ayzida6eXH7I50y3O5YdtTjutM/sZR5a5zTn+BsZhE9G3NXl+E+Pgu4izsDebOPusYu4h3qX8HC42+/A4P0Q4fdARLiduOlzGZvLP6XDKKYXvk2PS9+Tayg37o9Rjhp/vZ7E/yff+l4AhXWA3gSGNwZxoS4MhX5g3rCmsn5Y9xxsbazA+acGbv9s1bmgf7xzv0Bi0TnI4I1SYoXHYG/2MbDbZ/i9ljM7M4BgZ3COjJldiHVz4haPt0qHxog/Lc2XwEKfJwzrkXfwszIu9LM7dB7ZnwR7VoxSfkTdzj4ph1h4Vw/je1sE3sDgZdsXGjg6w2zY2PcDEGxm2sW7uwQHD52NQvjeZGC/DOYbxMtxk2Bwv3wGGsTJcYRgvw22G8TKINxNm1L1ZPoaxMsgfDMzeY2TYHC8fw3gZDr7FwqaN8jGMl+E2Yaijz81dMMv3uFl2jl0nDHFybOStZpyXN3pm+QiDHMduMrk5FufBt5l54dgVwhAnx24Thjhpi8wo39vNODl2XWKIU2PYGz9ox0kWjsClrzUer43fPMjiBo6yvoP10znWFwlD3By7LTHEqzFa/75D/r0pDWuPnpzZaL4nW6QtjhOcpg8K1rx3xuR4a497I+xNBuCoI7ZXC5yNFZhfWDimu3y/ts2ZNnw9AWfjCvBHd9g43w9eA87bPPbDW/gqkz883sL5mSJw1uagg9sMZ+0HcYid4LA+BHtQ4Hz8xBucbZyV8cwuG+f1dKOFt+tpYrfN4fW0YuNWPf3Cxq16OrTHxnk9XbFxq55+Z+NWPU3vtXFeTy+18HY9/RMc9g0AXu+zcV4P37dxqx7GH7Lxdj0s2RyrHn5m41Y9HJywcV4PX7Zxqx5es3GrHo4/bOO8Hq7auFUPf2vh7XrIH7E46C/63QeFzw7dG195FPjchdYeNc1HGM72tw8/ZmLtM4/X3mLi9JpZO/1DbwOnc2/+2kEDn27ja08YeEf88SHgWB4=
*/