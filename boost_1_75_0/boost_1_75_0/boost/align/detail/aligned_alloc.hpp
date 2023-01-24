/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/align/align.hpp>
#include <boost/align/alignment_of.hpp>
#include <boost/assert.hpp>
#include <cstdlib>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    enum {
        N = alignment_of<void*>::value
    };
    if (alignment < N) {
        alignment = N;
    }
    std::size_t n = size + alignment - N;
    void* p = std::malloc(sizeof(void*) + n);
    if (p) {
        void* r = static_cast<char*>(p) + sizeof(void*);
        (void)boost::alignment::align(alignment, size, r, n);
        *(static_cast<void**>(r) - 1) = p;
        p = r;
    }
    return p;
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    if (ptr) {
        std::free(*(static_cast<void**>(ptr) - 1));
    }
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc.hpp
1FBodSaGLMHyDKfU1jwrWGM0sZLKj5IKLDJDNd1o/KwYdnWbA43/7AjZvA3E9mbQsIOJ2qcfE0EUsiAt2zAtBa/npz/VCzE1U5vtixnSyxtr6FKpqcjvjxBOtNX0NtgPgdv+Rf5IaWue1QDcLVe/4bfxxpY6PpQ3FmlX6BahDU/jJcErqENNxzqh76lQcy6nz38NU3iuto0vP1BHd8XYznJ2NcYARh9RwN4q7U/tOKRIWNvGLcqT8E/vVEN9ekZPM2wujc5wpE+Hf1OFuphS44ZOLc4Pd8f+ZVYlvUY0qByx3OWfsQwc6uReZadjHvU0qalgNmkPpZEyqYnld69RTBQGGsvciHEF7TaSdPsnQ3yAEZ010Q3C2L69Ot1LUwURxjKlzhcd3xuBe69WOF0SJvwNZeidCmXzG9YcjmaG6xmpvtqPjccuhqF+m1qFVzsUSxT+qGwLIAhV9eGfauBiFA327pu3nXG0ra1lDJer+JqDM3U0O13PePm2tMEI9wxF/GAkwS1QT4XeSZ8CFPpygi1m5+tpPnJmA763+bc8sK+pd7QavuVe+W19d29u+LLkdf6vnlcabdKcxOhOXPmOd/RlkZ9wTD+vmdbyeB47reBuJc1AdeZ8PPt+0w341jUs4QoVMkCKr+qxSSYLO42l4snOhc5nt2qmKNt67zHsTZVqIXrJj4dNtzaXFJcGFofDpp/H6iJfDSbDqqNR
*/