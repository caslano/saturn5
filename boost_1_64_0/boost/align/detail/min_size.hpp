/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MIN_SIZE_HPP
#define BOOST_ALIGN_DETAIL_MIN_SIZE_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<std::size_t A, std::size_t B>
struct min_size
    : integral_constant<std::size_t, (A < B) ? A : B> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* min_size.hpp
i4TGCYReOsjo1BAevDicbEmAvThx5p6dGGU1f6F5cg9j3muDG99fza7vf/urfSVbB424EhKB4fIR2OHzXQ+3wOqILIvwMKZ7cL/7oBSztuwr0/iKb84r4G02/E5LAhkJcJzo1wTjAjoI3EGDMNxvs4Zg25RbrTqXo9wppyLYIuv/Ps0rIpsi1vTkvZTBmEnC2VwS062fMOaXuY8Oa+vbxmr29j3zKzDo0rtz3KK+BSfLj40PLGTbcZ/Ywct/z/I2uFgw/etB+om8YevW8ZwRJ86gt4DUatFIdcPypKPwFUZkWVyy8U51QfBLaUrxRcdG3xcc07BgJZS94hr/DYxUq6XiPyYKOsC9YpeB6Cg1b61dEffXCFd7BgGNm6hHjFZR8B0YfWd1lt5wpWMqDLeJOOf1CnVhzRMce367MPj+DytlSIP6LqxahT2Fw6hp02mrdOXEoiSzVsvxI9uveb6qP+SRdeU+eKvB40mQH6JkcfHucYXdnt/xGP31192c/P3E96lNnS1jekH+crIACgBTnhkLmjmTcSpdwk05+O2igB/zXnln0fdplxF5pA==
*/