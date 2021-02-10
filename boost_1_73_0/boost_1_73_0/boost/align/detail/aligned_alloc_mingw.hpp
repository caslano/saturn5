/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MINGW_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MINGW_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::__mingw_aligned_malloc(size, alignment);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::__mingw_aligned_free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_mingw.hpp
8KPs8OwkHJ/KJqo0V+tbelI8RyVvPwbvsfyOc+UZhK0lkUfBd6MVD+takwomaranVZZHZX4Z00mYb94qHwItIHcIhor+bB5v86qYNCvM9PjR/lcDc/4waDVBoxgq5cG3wSyWMJz2IDuc5V89G2Qv4FQcZEcDVCqSHzfyv3pa54MMdQ+K+fKmlH/Xc9QYOAanY9jc8WoJ/6o89SqfT2FofVU0DDL/Jl9MEO94DbfDN5d/kDG/EZB8I0o8SiKIQifKE35pPwrNxFioYjnI/vdqjuFOy3YpP1fy65u6khdHb48vBxnjAP4uw76b4OCHZ8L0cuHX747yhfxjf8pgysaVo4sQft0UF38U8eJMAItVnsv/F3d38pMR1+dn38iP1WQ9oMmNdjuRpDDQxRRglE+GpzkevYAIK/cIJsCz4SuEruA3GftyKjP+qWwRHmvQtL9e1XdnTY3R/jjIbu9uy9l1Aa3muxenHsHwXX1TUzCjygWbuYXWMv0NGtBMkzyQZF0VmvBrgWUwGwG/PjMr2v9AEVSnh/kMyBV0I63HKHLBwMgQXdEUTvshf6x0w2v3uSDz5+pK1FQ3T9tScw4uUL3ENafdIFTSbNWVnre+geMXsgEzMPsuVPSb66OAyqiX0j78zq3yJsLE6nsCcRFd
*/