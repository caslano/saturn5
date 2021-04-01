/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNED_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNED_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline bool
is_aligned(const volatile void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return (reinterpret_cast<std::size_t>(ptr) & (alignment - 1)) == 0;
}

inline bool
is_aligned(std::size_t alignment, const volatile void* ptr) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return (reinterpret_cast<std::size_t>(ptr) & (alignment - 1)) == 0;
}

} /* alignment */
} /* boost */

#endif

/* is_aligned.hpp
es3t8dwXYQ70qc8p1l7F9mW/j4LkKYKaMvNFVfQwFDJiMsbRYxK104bXE33OPf5RIoCIQhDj+s+fdWc8rCDlC618h2SHkgO6kyljEzJbp+qqdMVi5Cptva2TIkshe0cD3HT1N8DD4MoijBYy8+HW3UgHvg8EfRXtaWVyjZkIqja8YJNaxzMAGfkiE0UvH/mr5jP7WGIjiRlBAW4iVp9sYqSWRmN2oajNivYUrnonZc7+GG3QlGsK77s5lR3dCmEURA8h9R1CU+SY4aQEVoHPg4JAKzqaOFYLVj4HcO3rkFKIYqgdXzMI6LdZVThgat4FlYgsg8jYklVb25TO81/v08xrOqSlRLtsvjxIg24WWmSlCoc4+5W5x25XFK80csiviAPFluWUVGUKcG9ooYXcEuXELhWtRl5BWZ9imJ1Vh6eTvENofqa7Zk+kqkBpwgxpywkn0Bbeb6EyQfO0lfaxaIRsfwxifjVpneSYaZA06tvqZZJrlVcWYb1gjAPFI3C0eKsSfILNNzvhaeFy/UP8tlJvhHAfMI0aVy8U6bdOU9TYpKpJLEbGTgUPJQ==
*/