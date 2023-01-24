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
kVrw/eAfhMZsXNsJPNrVcX1ma2z/qlMBo8Y86rp6jDDAdzesiawt2o0Rv2SxxW+tgT/EcwTad5/xj1DNeG2dbO72PqTe6oWP4XP9xAxv5r0vsx09AN/0u2O3Qc0JYAr+ciXCD0Ajm+Nm8dnCrqPn5R8XyfV4qfS28FrAah4NpyeBUE9cLY2mAopUmS+rc+D+aZ76FXcRaFSBZchqxmk9OPINz9OoZx9M9/6c/8TKWPVaBE26h9dSn3ubQ0WWfrijcuaWBrZdmlLy3CLDkrPKi13pnqHNa50y8jw5+rn/zLAw/re4CeGGtSeNOH2HxugZhXTrawPRLNV2d3cp9hpDj+NO5iE6HsvV1qNGz75Husb+8+jHyKik1Em4mQWuN7At3jOSgXQq3r3Ykv+17R/E37C5ydmAwfrbSnDRu9K2J8qKtU7DVyN83HurcfnzTqpTPN+N1vqN1IxGkVp4mi8azRbFVoCWjNZsaeRHeDb2tWFA9G2FW1NNgIYiWCQahUwH4YE9lDKFKBrRpm16LLfTmM7n+grnzXrgp1myzg6ZVng9lrKChLFj7nuE14Lk69873PiIk6u4D34+W2BxYD6XCh+Y9vKc7h0X7XLR+8HYkeQW9Rjz6icUiP9eUN9/yq/lk8TZxwzd52xKZ1gFyTNd8gaE2cXpkMpo7hiZyxT2uWzmxeB8VdQ6t2rkGAF/l7vRLKIvz5zzppB9vNg2
*/