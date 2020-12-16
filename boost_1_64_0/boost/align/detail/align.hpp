/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align(std::size_t alignment, std::size_t size, void*& ptr,
    std::size_t& space)
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    if (size <= space) {
        char* p = reinterpret_cast<char*>(~(alignment - 1) &
            (reinterpret_cast<std::size_t>(ptr) + alignment - 1));
        std::size_t n = space - (p - static_cast<char*>(ptr));
        if (size <= n) {
            ptr = p;
            space = n;
            return p;
        }
    }
    return 0;
}

} /* alignment */
} /* boost */

#endif

/* align.hpp
rNt3XfjMld597rzS2MzUr3L/kGUIINOxEQ/zxuOq+qiRLzYKM6Luwb+4sx7VkY9x0UhNeoXCNUZ1IdIrYx7bDDp3gS2/kqgrCacvO6G0G+c8kA3O+svocyKKzcX7ogaoiqW8bGM5XQqGb+q2YhJkiBTwJQZfiGZe+ZRMk4J22lE+ijGT3c8NC7SIg3fsgmiQSbSRBWHrmv/8D/zRcpRKiyX/39dMElx51CLBJKRgIsbCa4rG4SV+PZJNPuvKZfzNbTizCxKyC85WEbNIaZLBh2zS8Fm9DAkUTO8i2sDg7w8PW4Gnx9EohcuKsjwRZuAnRI7MAGVMZaMUR4Sexkw5TF0zk+PM0DggM0IroqTqCraaUXBecnF2wblAO+AUtH+F5oBu6pB2zSGeSPu0f7BhffIrxgrU1J9rcqImV0FD1flecjFqYJnNG+E7gGIAOycSGb0AMnqvfBg4gHqNF/rtVhiBGDIfb9SH4q6eLMb+VOQMbNiTiNPctoDn3aUm/0GoHElDsQW5UiyyZrEuXGzaxkyjtQ54s+wRybztuJ8RNWqqDgZU/tPx08qhTu4npwBkF/n4KyYpTa0SUqKzOXLunV0ki+X27ZiZH2vfoGHqsZct//8E0/8fy5scHKA3Lyut10PZ9cY4RuVNwsKbL9As3JnXq5X3UrGEhbtTUY/3fLJq0GOit73hisVDkhecrx/Lc5dh0BS5I5DjmXD8/uOY47+Wt8J09cLGmuhq1vsSN2WkPklRWvEV8lR8tea0/ULr+zJetiy/u5Pp/ARh4o2xloSBt+YfWRLGxSMpGCRLGGWQMPyejfg/ytfHX+EAtCerAbT/7Oc9AvLA63/WRxDZY8z4QsWM5ZG5wrofySPTHwu3am9U+hf5/TFhXdenlky7hUSBxvjkL0Y+RxWQv2kMI3+5e/h6ui+zE03RjcTMSfZS0+8iVltlnsD3dRIpdlM4SbF3mxrdTo+xq+pw/H8H6s00/OrBMQxTP2MLAfT3DyyAfDSRKqc2WN6wu9tfBniwvKrPfVqOLyWKiGu9t3mYGykOOKSpiwhAlbtweUPsYsuySPDim5k4FP1pD9ARCv+aKrr/yX7+HKScS/4Ak2gf4xvNYo/3HtiakzdxeCC1l4l3X15KpDeN/XmhQKDlH/1k8wpQmkjfb2QefQ1/P4sVfyh9ePuZ9thPoCP+XP0T3k5WvyW/+uzfXACFbw/JxK6t4CKsPBDecdBZLbzLkok7kv7jHCGJt2k5ueE+cRdzqeYwV5XTUfVsYx1vz7ZRXw+PYrHlvqJGWmHxzB3iHZb5Pv8Fz01XkZBtiu7TcsVCWRBaoRVju6/fUiwJh9VHoGDw4Eex2EnI1wv2RunbQpIKoRFpqsLYuudgGZIPpN4RwvvsNOz3gn+2o1mCxqMvBM73lIN0SC/fBpPmCkBddnY0CUMJ6JsaSkZK7EwyaLrMw7Je1nA0w54dy16cWajTTUR3v+rKDi5943lVR5mYmXv1AbRbUK7cz4rl5hK+4w404fK5r1Kr7g6415Ee6mwZtVakf55jM84MwfSkU5PTk4uBI32QTRxUyhrew+3c7CSPillTJYQKS7ET/eSBNsFJ7GU+6JmXe5UQrS/3K4BT/yXDOX8i578a+Y1bkyj7jgL2nUgE+acbpWroLw7qNHvmtVTDn+NCaQS2szyWNpHnfUXnLTvQoI5BS67CTtLTB9AafZz1oeV0k8U7NqsXJ+Fmc9p+FJ8AOlyr1UbNqzt48Lo8PRDfZTU6bN2D7lSjn8Wr3KRYgWVZfQ5xiq2RuybwQ4J6+QF+SESOyR0I30Oomhkf6Oguyxbq6C4/3qeju/wBM4HtHZhJOerAUUc9vDaqwes=
*/