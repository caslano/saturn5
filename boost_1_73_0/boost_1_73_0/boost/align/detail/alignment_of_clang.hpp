/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_clang.hpp
/gFoNp7Nr4dLfhuDeNJP/XAepm5mxq8kM69kVthJlwl0EwXtIEln44f9euwA+ZUBXc0A+HUMkF8U6GL98EO5vB5o7hV0niT8fg40z/TDLxP+3gWaLwfAj22BcEtyftje6VuY8UvErwDojh8Av8YB8gsCXXgA/C4YIL/Lge6mAfDbM0B+zwDdbwfA77MB8vsG6NK28utk/HK3MuOXiN/RQDd3APyWDZDfyUB3Sj/8UJ7PHSC/a4Fu9wD4PTVAfr8=
*/