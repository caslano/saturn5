// (C) Copyright 2010 Daniel James
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_UNREACHABLE_RETURN_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>

#if defined(_MSC_VER) || defined(__GNUC__)
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    BOOST_UNREACHABLE_RETURN(x)
#else
#define BOOST_IOSTREAMS_UNREACHABLE_RETURN(x) \
    return x;
#endif

#endif

/* unreachable_return.hpp
VUeTRhhSQgeloX2d9rx11vP7oeLKYnwwXXnDJ3XbhvHoapObQ643b34zWwNkCRtNxzFQgNnwucPJT/Ktz+XBKOx/xG4LwZomtv+riP7PCqeQ4L8rnOoO1rauXrb/zt7E7nrDAahbFfkXeH/5bNH3FPCCtU9JnhOPzfhFySMrEe8bJawTNFbGDk5o1pzkAZzhFf1J+VCJxpAoVpLKLJFoxlTmO4cgsr15n9mBxLUUEZfVoWfrTofZRZUPqSKaTnPqjksDS1vI9jkV+jBd6SwbjsfJVrcteOvj84qbX2+rn0Cw16ZTL8Bj1M9BZ1We/dq1LMxuf0EwkuUTGdf+Y2eWOocx+MEHkaYqi+uY2Wo8L5W+Mwrpohcj+4yei12FpY9ujwlBg3AjnvTCO7Cxj0FgYMAcYywa/ezrv4rkadOCuyjUsyh1DF0nvVD+TR2q871cOZ1XDuarIPeFyOmeCVVtuAkXbKwiY/fdyzdYZ6ffrNBI379PUKAcuyV/WkoRsZxup8kK78rnGAf3K7d87RDxF8V2M4M86WEjgzTOfTwbn+7QnV6Pg5weKcxzUFYWiKe4hV6ae29NVLVxEu4vJG6r1N7WG0I6Pa1wlGeBmUgM6PGg73Rub9qdnOSuMudgeg53rPFJFm4+193/2HZXBCr2M1wiDnKKS7Fivr8qPKTo31L7LmnQ+JSBYLw2J8p9QT4MrrCjvd1KH87P31qn
*/