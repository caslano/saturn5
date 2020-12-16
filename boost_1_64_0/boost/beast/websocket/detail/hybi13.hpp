//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_HYBI13_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_HYBI13_HPP

#include <boost/beast/core/static_string.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include <cstdint>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

using sec_ws_key_type = static_string<
    beast::detail::base64::encoded_size(16)>;

using sec_ws_accept_type = static_string<
    beast::detail::base64::encoded_size(20)>;

BOOST_BEAST_DECL
void
make_sec_ws_key(sec_ws_key_type& key);

BOOST_BEAST_DECL
void
make_sec_ws_accept(
    sec_ws_accept_type& accept,
    string_view key);

} // detail
} // websocket
} // beast
} // boost

#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/hybi13.ipp>
#endif

#endif

/* hybi13.hpp
/KbOqP/GRg/8Gex2Xs7gXiswz2Ii+jLxe4YJ+4t1OqvX7yLH9mESC3XeZk3KknuL/+pwh/jvEJjPv2sw/8CIDDVxpci9zpV7TZwzX9bhIiON+x7mC8dYq6yGUra0+WLqj4bR+kNZRcpX1UUl38Vf7cA0NDevxzyDaUSdicXnyoQC062yUI25VmKdI/Le7vNM2XaJ6NOTbBlpytvknZGT54pf8sTUPU998dSNOXpu/b0qE9djFhA+4wNTN6gX8zg2diLbEheRJ0YXK1f8X04rNbpYGkeihPlTQZ3gUVSeGPdaLt1yreOqz71D3YNWVbPPzttyraI5Z/wvYl8scaTKE82eSFxGt3uTuI8y8onTkhxZpHHV4n597Holvy1yrbxesy8af3LPqRH3VJ34ec5zVYG/iHslI0ctlaOOjKlDfSkDW5AntZEn5TFxmMV1MJWKlSe9jyVPyGeukc/qLyNCfpykMsUtY9p45JC3fnSvYMmvaYD6AevD87lH6ofe+pE1q7B+LHSVtdYF9Z9k9rsYKfbEwD7+/RQTITe0j3HCVQ90s54SPyllJD+5nSXlYdfxdPFTPqDyRN29ZyrfKn7YW0rLaLXYV6CTEivxfpdg6o6UU6ojA3zGOsMkbA21syuSjAvqmXI9yHP8SHytYF3dwwEj5ZpxjHLNgQsjynC+t/2ba+QF1yQvzLiJ5+AazxHRzhedpLoY+h0yGZNnt/OPPOWonUDUPkD9J0eWl7Zp4+4n21V+Gz+R8lvHuMbd6J9eXKcg77qUYNwYKTv7+8jOtCiyc7RHdrrHXKr4wS9V8+8UfXdKcMnJuRPs9yffdyb1V8nvXUndqrrq2wRPG2go7s2tyvgo9JNZ4Efjryt+WtunnZt8a5l87G/Gun+Q673L3d9M8NSho/oGN177ipGYyfhb/r4nD7SriN5X3C7+B7j7Co0jUerNJMkfopJQWreMHzPW5JdjZPJ23Hh+d18yHQmg/YTXfWhRmWzG6KmVbTn8+2RwktYh0s81k34fmeuWy5JOlcPYo8jhvol6nq/m/WeY6Xb73e/OexXDmveaj27db/WfaORwrtjfttrIiCmqHNZwY8jBKpFy2JTrE+JnGfqCsZGy09TTeeKnP6VYychLZKO8G/4I+9WUsTXXSv6uqPk93b/NR+w3pkpfOzHVMetVDi7/yJ2Pxx4LF/hvavLxEbGv4ErAGhw9HzXcWKuj//jX7NX0kPhbJjuO9cOo7NTwjaLJTnWvb8a8nXjv70/d2VK5QI6GqpdJiS8bjjuVN/zKMbz3N+SPYAKbGFVh66OqteODyezGRDoom7BVdAwbWa5J+i6wUe57o9WWO4/A2O/9JX3PPZHjXfd8154q/vNv+wvf9/OyJs7NzZ6zQCbicI46F7f/BM3FOXMR46v6p22HK21szRI1PTtOUHqcdrEqqcAzFvklYMLkX0rBnIIdIN1MrGk+fWTqn0mX+q/gpMv1ni+vpTqH5vir5J4HaAu0nht3iYd26povy2lnmfru9ZdyHPnwUcQ7UoKpX5JOuVbdXCNt6i/FzC9JOjx5OL+6vkvpGGEDJkAepn7qzcNJWYy0sormocpI9X8Ho4f6Zq5pg1xLVtlrhyE20zdqGEotUfMlTeyX0UfX0bzSOHRsVt+Jw+58NJ40E09liecs7MPEfp01TOM5yxuPyoKcrKzcgvQkajwzxU9XxptBjdsJV90lQ7xjx2xx76iy0vHfwX5q0z9fV8vuG0o+Hows5/5m3Cy3NuPB+npN88NTrhk1dH8ALdeGmK+I14ooVziF0NHahvpP0PeL6HNzCZ969wrUcGZct/g4xsM+zx85r6hrBqOvDfRfC3b8a7uOdw0=
*/