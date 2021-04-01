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
BHmLPQF6NZi6oL5FDeg4f/RK2Q/zLiWxPvXbdx6FCSGAV+uRcXxUD3PQOwwjcxrtAdyfaZFOGnHjUsj47/49PyOeGrruRlBBaAHTlwWxIfdqx04s/mdW+7+Tr1JPGZ4BaUdvgHSEY7crinUBIZCS6ld3zzQILjCB/A+HoM3uMtQTkxYmUQmgCMrQ0pyz5kDLW+c28GqvgnGSxHAZlir3qcIbovkHmPi+80Jl3P2ylUsDWEPxMHOXfLuF/Gn2SiJfugzJZE74BIlCFUuP054bCj/IrqdlWyGCb/5TPVOOdTxqiOziDKoz7eWy3dLAMp4ge+y56e+ZhxoZL6vX8oUzBh6lKQlmFiyQyR+GxO/puKVFYHwGwqZU8P9KBAVTtR2Ysi8ItjfaWqn78aw958/z+W8D4EdXj6/3ntbAJH9t/swS0mu4qwpnAAgbw+MUz8jRam0K1FSveU6Uf66L24gFFCwhAElKciRwHd/ClRQdQm26hJEHLUwU8p43mR1vH9BWCYgRQEmpc5ZhvSbCrtyod+3U3pYAfzyXlLHYuVaf6BZaOioCW6kCJDiCzA==
*/