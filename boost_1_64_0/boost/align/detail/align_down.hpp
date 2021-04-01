/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_DOWN_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align_down(void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return reinterpret_cast<void*>(~(alignment - 1) &
        reinterpret_cast<std::size_t>(ptr));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
crHLj+Zkl1tyLGTe8TKrhy2g7M2cqWWabItTD9cdOp00dEH9LKy/sywELDSf4lbZelU8bBOZDVtBYmZHNRPbhgHPZ9OfM5pRSAk0yuuF4yzpsc2HOSm3t/gcibz+JOM5zvFh8YD7Gf4yAvy7GkFPVIbXgueViRMRGPlsPwxFQUBv6jFcC2RMVLyaVfDIAkhwZ981zosPXvRenJ2I9EFf73FonGE8eszxXYxBPhdO5gzqSbma/hsRqCgVLTEHS8s7n1kdTQFTNy1SniiZ56KXNhcpemh9vfLX7+SPbESf0MKpOxByDbEqLRJMuS7S/+czLMfv4bhNeMd/xRqJZNLbNYoUIok6b7gCpDovJAPqADc71tSM1kAXduqBFwHuJvQ198Hkb8K5Aesx6uu87zpglXBiZRSVyISLYuOxpr5kMIfyvv78u5p6p7/KTrT8Sb/K+5XxvRyNTilQD1XcXaBtnRIeONlw5ryvQj9aoHOUaYfzAsMmzr0EwjICwwyyl+pMKQaBtGCgpyI/nzA2cYYzqgjjyK7713vVPClU9MMW4rfzeVf905Mcczp6sQ==
*/