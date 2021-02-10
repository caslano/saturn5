/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNMENT_HPP

#include <boost/config.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

BOOST_CONSTEXPR inline bool
is_alignment(std::size_t value) BOOST_NOEXCEPT
{
    return (value > 0) && ((value & (value - 1)) == 0);
}

} /* detail */
} /* alignment */
} /* boost */

#endif

/* is_alignment.hpp
tp1XmtaTE3ibGM8CmWpisjODMxdkyGoN+a2IDUuttx66VJd1v0Cn3Rxb1saiDG+3z5rCCo8jaUndMjiHbU+q3sw4sPWqYUdrkYmCSRuzlar68EEW/eFDX3TJRqPRtmlHJLUP4BnLH0JuBpz3Apr1jU0xhjtSt9HMGnoatOTj+w0EqrUaX+wcBqEOr6Y2mEUmjmD3aVLM61sKaK03e0ivm/XZDFhvbT91beM3cn+pY36uHCGqW5cs/HuQahKOXSMI8WEZJNG2z8+x0ZEPMfzl//kQbwSFvk0WEQCap39h0jy8Ipct220Kmj32DuIrWGv4CyiAT/pvzYrJ6nrvIB1aX/O/Nl97UTdzOdeDe+t7eDKS3C/DQ209+u5AhTtNizpAFBJ9pjRRs1yqVVdIaVlwU5s9MelRhhsQuuVZqIpG+3hMsOK1C/u5sxXv4S1aeFopn4RBBhgaYeXd2hWwtPVeyLqiDGZypA3njRKRDzXrbXiU7X5LO8t3HueZ+Ma82wpr8Pk6Dl+cDJIEkCeAy9No8fwBXsQ1cl3txvwhPq92/SIoWAgGH3govcattbFE4qTobpHDFcsE3mu3NdjKvLnL2hgxffC8WJ9nhzNW/kjS+yOFvV8+MC3PjDKkQ61Rb1XfLfJ542wsskJ9FO7f
*/