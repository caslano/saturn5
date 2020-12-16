//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_ERROR_HPP
#define BOOST_BEAST_HTTP_IMPL_ERROR_HPP

#include <type_traits>

namespace boost {
namespace system {
template<>
struct is_error_code_enum<::boost::beast::http::error>
{
    static bool const value = true;
};
} // system
} // boost

namespace boost {
namespace beast {
namespace http {

BOOST_BEAST_DECL
error_code
make_error_code(error ev);

} // http
} // beast
} // boost

#endif

/* error.hpp
sB3XAazx0AGsKffUAcBP+3UACz10AGkV7joAMnOb5xE+6nleWB3AGA8dQFOFtw4A/lx1AOdXBHQAykiNtD/+l3QAa110AHdlI6PKEB0A7LrPSwmrdQBdietT7VpN1i0dAGE6pgMgXdw6XYfsWzx0AFnOMoS2w9C2QZyo20ZYHcAYDx1Ac6W7DkDYc5M1cTpXB7DMQwewsnJdOgD4i+kANhgdwBilA3iuLrlmk8y1/ca3VOckPH/MgTEdwH+hA/g4VAfAu7Z9OoA15R3TAaRVdK4OoKmic3QAaZUd0wFkVXauDqC5smM6gJWVHdMBFDKXqN0rpgOI6QBiOoANTQewiH55FfQc1Ab13TvJyIPKoMV7x3QA//Wz3ub/dYeY8w5TA9Ch+f9gmf8XqPl/3SHVR6j5jKUEUHP92zINPeedLHPeWfJ9Pg0aS/y6A4Ln2Dott3mDhB8qbp9xuXIPtN+xrs+67mlY4TcRt4SXM+Iye9nPRttNzXvOUf7bKv931LnWB861n514nPJPFzfpSfrqXjrCvUqYFZSba30N+/nhJWnRz72c559RLts5afDOb8I7d+WepfgwDHh23Lf4Y1zouaLb9OabzFvupf7GYrjKFNYkbkZU+o+ge/VDzhBfFB+qC9qN9pFW6slng+FuF0KcsDqhiV46oQnW/TMyFz9a9CCHix4kq9RLD2JnzN0mYjsVt1qdpbuY8taQxydKH8Jtd1ugExmaYJ+rK/kfMAiHKf+GQBvdXaVTbN3LwMM9lqUSRs7x20+FGSlubmdS7qR26VnM9jWr1L19rZIKqxQ57S86i5WucnKXETIJnLGt4k1m/uCT+rTSyvCUx6fKfydveegwo7U8+papNhKiG8mNQm+WLm54wi35IauPnbLSbSppIzdZQWUe+h27uDzkNaMsRF6kt255HVQWXl6EccirJTp57RaNvKrLLHk5x4THNgrV6Y3blPYQIi9vOYlMJE6y8iMf/j7Q0unh1z6dnnXmK+nhPtDRL6qS3HVlrWXuujJbEdz4J17n6Mss2a7qGjS+CX9GuU1fZmNKjj904404zjMvM5T7QNs7lo8OecfmgVsq/8n29ld3iGoO0v6sMHCWLu0vX7l3pgVm85vVriWapJ0bSFvL6Z4IzuEOlpOc9SfvWD/vGSqM1XYlXxkbtyjX7Ve5p5UH9X/RURYmu+sol5Z76yhtVRDTU24gesrZSk95mvHJ9B9+z9n5wdtHNhy1Sdf4mJ5yfeoprXNgPrHpKVfIWX/T+Vuf3SLfxbNc9ubvITqtPcEe4ERwJLgPmAMWgluCk8Ap4F7gNPld6zYP8D4rY6ykvxuYAe4O9he36FT5VvXWqU4THeJ0MAGcAeozqCTe0S46zJGiwxwFDgVHgxXiPhzMAS35rJR0Kl3k01/SGQBCxiCRz2BwNJgpchkGFoFDwf3FLenzLeKd/haSfq6kv5Wkv7WkP0bS317Sz5P0t7frLMu8dbDFIr/9RH4lYFdwf1v81rL260yLIKNc6sGlfNVSvhqJd4i0p1owH5wD7gfOBavl98PBeht/S8vbp5N9THSyOfvE9LExfWxMH7uh6WMn0y/roIuhlVAbNLAQOy2oFmqBVhbG9LKxJ/bEntgTe2JP7Ik9sSf2/B+f9bb+X12JQtlc/u+Y/b+1/z9Prf9XycJ/wPZ/Jxfb/5vC7P+fNxIdR0nweu/43T3WeQkbdp03rO2/1/7/shIv23/4+Rf2/zeXuK6XkpmrfTfho7bvDmv777X/39jfa80b/jzWuvvsH7r//6N/yfbfbf//raZduoPvBmlL7mtYhNW2/z8NV36Vsk3fWickTPvWCS3bf9LFbaUb2f7/pc4yhLY=
*/