// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_reverse.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REVERSE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_reverse
        : is_std_list<T>
    {
    };
}

#endif

/* has_reverse.hpp
CyYotho+O4gQdvCPtH35zU6NtjlDZ6ml8bqg95ywK+OZAZazH0O6BXipwKN5IAeiB4a2NhUGvXq2atX9eNs6Pq3LpkNzWftwk6wbJyq+5LFg0u65skPjYfSrRnQULxomCf5rBIGANYpS/+NrnmUhTSg3qYdIp3kYL/p2mpNX8lP2IWdnTixGnrvjFAT+hiJSoVyY/kjbn2Es4VUmyGXALNHzRWcs8VFOAgoFoY/LOy1IxFESdtLB/MSD4hIniedhv3chCt66Mw1Y1xIjBfkLB9L3OA+VPsUDRC+/lv5Ad43FRTxgpxxpd5cONgOEGH5gJXTubYZnX6i1h0MHSe0/CRBOrpOZ+KtQhHszp1IJNHo3/RoxRFgZRUqRra1q6JxF9Bb9GXzir3kP69JAzKUSLFAqamfyRHsF+KBjDGv2Y75RYYgab3Wk+6mFoYwMLxm35qzT3DZoTsr0MfXWzgrcxlZCuD7LB/5EmcW0a0/BNsflYuGpXjRSfsWY3+ay9Yfe8sLwd1rj/UV/rNAcVdNretHSPz1/ecpq6G/7E5mWfwTTi/rUlAQ+FLeSIg==
*/