/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MACOS_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MACOS_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    if (size == 0) {
        return 0;
    }
    if (alignment < sizeof(void*)) {
        alignment = sizeof(void*);
    }
    void* p;
    if (::posix_memalign(&p, alignment, size) != 0) {
        p = 0;
    }
    return p;
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_macos.hpp
pLc3aj7bDLBloc2jQECjG0JXjSpPky5fNKg3slaxwPC/WQ8jPAMnSbLi8mQOaqn4Moy1LAEoEWlYySQj6RUfUhnNLOZWtTdDfxU/L+pnTzaCxgXPXYikGgLYFk9QZtXjS0Xhy1+Npv6QDKb9Wx9SkOLRnZZtAEZY6eBxZg2I9biGRPMxn0wOmW9sG47e5MU+qWwySayDqSp6nZZUTJ9uEz1OXxxBecnsHp+GQrUbfVl4NV+C49pJ8pmptbhl1n+JZci731m6xVuoNj7aTQZjj2UnWJP3fX5hG+/zZci+A2SLfbJ4EBxh70GOYhRNcbu2tr2Nhu6izx5/VTNrSFBif8AbmyLxqzkAidaBtRVnPT3APfY5nMXmxmrR5Ro6gZimmO+mlwB3/vSRXJ1+CLrX+Ioqk7giy+oXYdUdqHJHCeRfrjxI/57kYc2tamTD2UV5+G8/LAVl9QxzJ72J/3XaHeG06AiqS9MBSLf5l8QyB25EqeGoDRnUBCbxieWS3dvwRPk7jyIM7Sp7UI8gNYPUdAOTx0fqO1C3Qsah3PE764UN480stKJipM56yw==
*/