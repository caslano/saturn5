/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MSVC_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::_aligned_malloc(size, alignment);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::_aligned_free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_msvc.hpp
SRaT712s3qUUofnWD8rfmEvzZ973Cym1WUzQ+Tu0dNkAAyjMe7Az04+dq6jXK/h11sZyWzNGdFbEwmS6n1uWNtEoTDfyXall80c0CxXwou4wUvmbfsNcrX1FUt5QrQXFXTe+W8yxaRPPh7AeDDTFwtLCmSPiwkSQJ2bZNqweHTLOum3qFeleDsLg29lfhPL/zQDyi2ruyqsvCho8outQ3Rzx0YEfjyJtu6w/FpWTe49OMnPQpLB6QJTvzUwRtVAIzkh2UNNIyDwId8YNyXDpuIasVi8s6uGN+eWI9XuIYfiTAvlWFkJ8Lr2EBZMv76wcgd7osmVisYcf6sW0DQBrtrUaj+sI26ZTIjSoSoDFa9ur3cPcLC16azjKPYB46fS7w+WeGV3lWcU/ZhHUvSjf1g6OgTswMqh3LqiZYUK1JGj4FeUKxv49ffoE6e5U3hMThZZHypkeEfQfq2a053ftJxZl1nsRT7snJ9pmTUSnMRj2CTBoEwsZ+mRhm9jBquf5tvcBQpFbdF4U4EMlBBPIw/VRQOvg8pflhphOJETmJl+2vTd2em/spG8c3+VaTCBRU33bSVST59ilmXia/0bCdaO1gay4RgBK1EKaGJ8Xoq9H9N3SgLmqyjsdRaEFppRXlnTbMOo9W5bTj1lR
*/