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
zkUZCzPpWBaE52rxLOu4FmAY/7+Wr03K85NNoQ3IoSUYNB4HNzxC95hDfxbq/7Jq0TLW3+OwFC82GHKCMnW8bICou2BLwrDcHJ8RMGZMtW9cIBxGrUU3eaiXYD8oVV36OcrQ4RgLT5iJ2LPETCcszG+WLQwH3Qdl6zpjFw5k4UrzTBWZhMva0aFurmK3fd5qjvzGJnZpgD12VUoho1fK1Ze9K3wySw3Wn7nn2YUehKR9Wke/
*/