
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_STACK_CONTEXT_H
#define BOOST_CONTEXT_STACK_CONTEXT_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

#if ! defined(BOOST_CONTEXT_NO_CXX11)
struct BOOST_CONTEXT_DECL stack_context {
# if defined(BOOST_USE_SEGMENTED_STACKS)
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];
# endif

    std::size_t             size{ 0 };
    void                *   sp{ nullptr };
# if defined(BOOST_USE_SEGMENTED_STACKS)
    segments_context        segments_ctx{};
# endif
# if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id{ 0 };
# endif
};
#else
struct BOOST_CONTEXT_DECL stack_context {
# if defined(BOOST_USE_SEGMENTED_STACKS)
    typedef void *  segments_context[BOOST_CONTEXT_SEGMENTS];
# endif

    std::size_t             size;
    void                *   sp;
# if defined(BOOST_USE_SEGMENTED_STACKS)
    segments_context        segments_ctx;
# endif
# if defined(BOOST_USE_VALGRIND)
    unsigned                valgrind_stack_id;
# endif

    stack_context() :
        size( 0),
        sp( 0)
# if defined(BOOST_USE_SEGMENTED_STACKS)
        , segments_ctx()
# endif
# if defined(BOOST_USE_VALGRIND)
        , valgrind_stack_id( 0)
# endif
        {}
};
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_STACK_CONTEXT_H

/* stack_context.hpp
fRV+i26AVrYExuOO8CYmUhMSBqBULKDX6sbSen+86r3DryVwb5surJ3fN+hvMA6wKoYgpIl83oL7XftP3gXy9Id9Mtv7BtE/lcoc4eibd0ftT+mozFzv3KK6WaEc6ua3CZ95ZH2DPetan+e766JnQm6Vfmn1gvldrG2Yhnw4zo0Zp7cbnf6++CBHzoc9BVPmDilDPHOZH8F6FaZvL431Kfce2VHv79rUe24XxPa2OdKGu4SfddOg2bV5sKtngK45IlWbJ3R/lpjyLYeuno7eTgjhZIFsDz8E48b69108dtyUhHx8iEeZkHiD9M2AMUGruYWN/M4xwpeQf7zbwH9KvC/1cqmdme2lO753E2y5R6ipScdBXnF/TvCV7jslc4k5NNZ+AWOtz59HUQBSfkFN22qAle4x7hZUc9DAgvVbV7kfd2bSo1w8BJE+u0/to8j8lwkuu9219Ww51/yrBJ5r5q9zho6DhkIpG2j5e2OHLJv2jRR9on/t4PlJilgfhOEzYPy2/jpRKT7S2oGBjU75ovfgYnNEbr+d3hjCyEq+UYnPKvH6O6GLNmu+7L3eC/OaP+pYkz2TB7iPSIIwTvrMOHm8hub+DjY5VCjmgjveu81bjQq/GM5g/SbhfMih7Ro39EFKX+6lR/H90n0unQyf23oDw/QSYjAGr3K8yoUpHJtX872RZJApZX5P9X1QxrjS+QPBPuHlx4dOS7oz9Vznnwh2i4n3cTvE+1DYnfo+pOyVPAQ6fm+go0Y9K807GGfnEJThtJT5ZaxN035hm5bKpYcmevxGl/qwFfpLbd1SY+v2s52iqtKj9MBNEOtojcZYlXpG+a1n8hOgHzYLrY0UXFdhF2g5B3wksIXjZWxh1tlCsUNHunsQIMtLxZalgwuPJcCBxFDqXbWuq2OQy8dllMbPXxLhO7R/ZV405iKn+f4siwX0rsYj8Q3lweciOaVHXZrPJbRKvGB9D+lR9K24jTwLx40EC2Qex5gvjXuVmizk0jTo8N4dxaZzoXhlnL3a9wn36JtErRwLcmRoMjOZdFLXcq0BzO0WlmJP/B359HUUD3MDQPsC10Eyw1ZOet4s2IelA5W4BytvIa2SOeJjuMYG9buWl1amLFjX+XT/3C+3fmOyhzamde9cYe5fHzajBKO70LJ/PVP2r/+VUCq9vedu7NPYALR/baH+/vUrqW4dm54dm6ojzl+QSBKd4kvoWGk1Y0XvaS8Jxi68++zbR4Sd4ZWWeqgd/l7X4yDL5b7OicOigkRYhbuX0xiTsd/uA/j2d08ZB7+jvWNNl5KIZOD3e0b9tGJ9BZ9pJhkDl2/3rIr03PfY3c2ic87tVKa0ZR0DF3rV9dOKoWciWTDRcpmlts+pr+xTB2HU88qoBZZoHVGJ1gHYMEfrKKF1g/gfXr2jwZj8mrB+vy6N8UH2xfggH4zxQarq3fdd1Api7FznYNmhwrici1D4lxk+ojkMLxL8JoL7bkkA+5qDbS/mh7alPIXd4mC7BUh0FX6rg0/mXeP0+0A+RZ59IfWN7gTfaCbxfa/EWU+ODI2Ma6xDgv/W+T3kNak9+DN9dwqTQcz92YTzd29yROs/3Mm1iuL1n/70pz8j6eIiSAxAgs8J4HmuW3yimqqwTzSXcJdUUQfi2wdV7P9wvDNiY8bR9WBbqrjbRQXkb4izyHda5Jsvso/eF4fvmO631EAdNQcwHzw5HIc3U1iVGsuw7ug3iWDtY6F15DqsawrfrD+gX2Y/ye2YBDq8Et7r1nfIE+Yd8nXy/ZsPfLRSmZH88qTbjUpS6dAMKJKF86D49x1+WavjVvSrLjwHuJPzmU+OoUH8VB9bP70YGov0/E8ivB9yHJc=
*/