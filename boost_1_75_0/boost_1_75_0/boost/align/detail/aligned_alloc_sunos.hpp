/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_SUNOS_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_SUNOS_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::memalign(alignment, size);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_sunos.hpp
3VWK8WLy25qzplD/QEMVKZGA9Sv9xeuam5S7hbekUQOX0B9j28SvkiYjvUU/KLwBETPh2sqbL1LpR4wELl/Z8qUW9wDLJeS94f7dWgXOgzkPKpiqIhkAK2kz82QGLZejw+Huv6ErQCCZ0SNDn+/GO6ln9U+bNBKVns3LnO7irYGb+L+xWFA9s+awOxkvkmfJsGkwnh/Vc99coEHo7b1Vci8CZq94dz2GVnUT8j8ecuFaIhsw1qwM+TBTMMeJNzDyA52EFl5mmk8tqOjMt8sDfTotTAymQrmci1mNiqHin7pE3H9a4iWAHr4Jz76b6wVQvah0lEVKimriXLLjxn6kGA8Evk+5sN10qxvggvOd3vq+X4U6CriPIx7u96h8HCJWR80SZ5ki5SxqWq9Kx36V+D2iPxig9hCRnD53jmV1lAuuXZx8LvV9lgSSvK8s9QX7fWE9PTqSg/qkhD+Ixv+xqal8Yfl9CRwW9n4eHa055z+NO5Kz/de8JxqfYlOLf4e7v1dYpuqDYetD865QCfD+2N1tI/3AGL+AL/pfEbt9HRhw9H8NXutD+zxf6Avu/qT5P4Gp/28hq+WB3m/Hu/Wkb7jjm7xF/yvSt88z/wU9x/4jI35fORDF6P4SWz4Qhbn/hFaL/8IYf0OXEv6EHnhDRwu4eCDz+qpx6P3oCpS+/SRQiw/EHX+z+q+tR36Tj/kEtoK5yed/lPT/JLj5
*/