//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP
#define BOOST_BEAST_HTTP_DYNAMIC_BODY_HPP

#include <boost/beast/core/multi_buffer.hpp>
#include <boost/beast/http/basic_dynamic_body.hpp>

namespace boost {
namespace beast {
namespace http {

/** A dynamic message body represented by a @ref multi_buffer

    Meets the requirements of <em>Body</em>.
*/
using dynamic_body = basic_dynamic_body<multi_buffer>;

} // http
} // beast
} // boost

#endif

/* dynamic_body.hpp
ihmsMzDr4+HuC+wER5hugrUgHWIVJMAd86Uz5mrLMF5cDoa3V/1Bj92iZc02EPB4IUwnl0EN0qA/zw0fML2Ye8PEc8Nxkqnd9+/eve1ITAkzPfWulUIwVbGTjgRhjBol2Yt0/l/v6peL6x7O70wj8OPdx71fbj6e3Jx/GPQvzltleXgppcWm1NgOgFbxF2jLBKzytRbPqwtLw51ht2SOTjnX6ROzfLBlAwztLkqRSIGQ7ZLwxKOey3MmIpPnRKThUX53Z6vAczpxLoD8/snny17vqkXdlwBZEZ1eXA8sEU9/5DwyJB1St2mNctHWssPzPFebkNlX8Vcg0+glOjP/26P+wB67HcEeeITlWfvYTuQYKuN5mVXsfG4ODUMSj+mVV1e6/KRndN0+oJ9y+MFN77yWzW6b+OPeDktLaUs/fKnNbmWW+kSbEd8cDG3p5rwR2zGLHzKFQXiY5rGu3bqZBlrfhJhwKhqBN3re4rXhYaumTZPD0kqbk1hlAL9dJCWuyAHdSXQLXJI10xZf5uhxewkoW48X+EIrVyWSGd9/2S4mBkhyFrfts8zv32lp+bA+0zaL8WRZwlttN3w+l0rP/SEmIdtVFC1ebUR5nLwkrhEa9+NCAO76KHisQPehmdbPpqgcZq1WOupzIaxc
*/