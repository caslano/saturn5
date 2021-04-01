/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_GCC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_GCC_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof__(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_gcc.hpp
M043RfCfCp/rKSXEHHiP1XMjIegy3FUJYhBEq8BVlJD3TiuDcusrfAueof3ZnAOX8Z/S57TDBmj3RkwsSxpdeU1234CaXik+MNT7LJTHh9IOFg0LRtcCDAvqqEMx61nf30TNbh00lJRYY2DzUD2TZbhCV0FOt36Sz9imhFxafh4ufHpEA8/lXddLLAeWQ6Vu4OYKwG5oLeX+jYegGqCuNKdGjPt5Qjn19wY3DH5flUw4H2l1WCofgKOAMYCpvTqVgVyrmSwV8urS4AszPMzv4WuVEePsnzVm3tnm/Xm1XJAUeojH82d/Giewu/4mZ5Ybj9sKrc+YQo94kjSRIwtMH9pdJq0QOZxk+S8Zoi7uTZD7M3lg3ZqxJNvXtqi2TfYwxSjDm3NFLUgk63Gv8TfpfyG7vfz9IGX/A2yDKZTCxxGxe79vAweX/4U79hmol1xp/ocxz2leOTpJJ9PfMxHX9c+8nadHaaA4J2fiUIU6vH9IoAo980kUbRUsMxcGvIp8CvD996QzrfohJx6PbvDMl8zJ3zWXERN4YtP0vmdcViEM/bfFdfPop7MUYg==
*/