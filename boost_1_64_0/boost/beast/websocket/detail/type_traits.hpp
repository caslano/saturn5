//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_TYPE_TRAITS_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_TYPE_TRAITS_HPP

#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

template<class F>
using is_request_decorator =
    typename beast::detail::is_invocable<F,
        void(request_type&)>::type;

template<class F>
using is_response_decorator =
    typename beast::detail::is_invocable<F,
        void(response_type&)>::type;

} // detail
} // websocket
} // beast
} // boost

#endif

/* type_traits.hpp
7Df79Xv36Od6rTbF78e/BuO3B/8XcBJco/vtx7flnphJmOE+++zr/vqeffV1T33dS9/soc/++cfeO1/3zdc98yP3yNf98UuwNz5nPuj++H774ete+Lr/vXvv+yMY1373Zp/78bq//XLM0dtirZRV7GWPycDkY9Zh9mLiV8dafTFzMCsxuzGHMA1u5/wJzHzMSsxuzNeY6nfEWv0xOZiVmH0Ya02s1R2Tg1m1pnT/+9Jf6a/0V/or/ZX+Sn//nd9/Zv//2RPnyPb/f3z//8w6ltEd4L1IfvfY835wLdzEx6o2d/msASQJ7WRZVtR12RquhdEFGi/2i4It+TdyvV8yfs4wYT5nxW41awtXX7diZF3cfF0XFy44237uZNf509vW2WEW4G+mxJPmiof153wjidd4dG8Es05aDk82Z+KfKWFqBzrbukiBsro20Imrrlmzmy73Ox8fGYFoOkazxM/ogF8Y97pB4jZr/5ZH0TsSnRTxd0mw0F3OgDdr9W4W925BP53OO+TedQKJ+tyOzjNPb/SWmoqf2+V5FjYUP7NzZ3J/3Zf6Gon/VFf8C8yaw79J2Jq+6xJ17wx9/kU8f1XLrSM0ROLt6tER+rNcOzP4DTEVpjlr1kQ7xa613S0lzjOYDy1r1nAvsa/h4yzWKJJM1hAXmGdI127op2f0JNdO1fXG8XUK7Rsx99Q+Ph2jteu96xpzrKLrGsmXSL1TqZfUba5p3ebaMrMWWZ9b1yxH27Nyv74CsTbIagZ3wbu5z/IN0fQO2tGKo+v/PVcQLtg/UE3X6zpxdVOdBEppo22PD1Tgi9E+q26kXqCeja7hWJU13DotaNqz1rWAq64lWZSV+L0pqGfra9jOepa8tn/Xmtpd4r5a91x3/Hco0s5d7U79aLvzW6+ra4gX/03SEkjUNcS17i7Y37sCz2rW8EbEt8LIGFc71jrbV+IrZyVrfR0s9l8CPdHWGsms0uuBqh697ETVO3hA/D0emBeoa7l0D0xZdZVy+JBdCk6OVjbS7ipphW0g8cV49mxMFP+N1R+R8hsuz1uH9Jp9HPVeDZCTZdH8eNTylSsqe3rJfT4NFNhp6RJfZ7d+uZG/O8Tv+MBdVgLrDSqqvHXyfERBnqs+w3bxuzkwg/zw1WlQubNdyuXuYGF55E3PzinsO5bJs1zFesthVpLW1fpy7SXsDfmefKqzn7Q+d0Xs+DP2GJU1Ro8ROeOvx74R4mb0Gp5Tv9C9/42RNanRZU2xsmWMj2xZKNeknRnZklLGK2+W+8ibFR55493T8ut4S372+qMa8GW4gfu0uSeKzsBERh65WXl5WZPcKgNR5c9YieeBUGuje+jE3SyavoC6t/aMGVRPIN1y9r4x/hqb/mmU2O8LtSSk08cGTB/bW/LmPvFzdsg5u+EvYq8t9aaanW9ivyzUlVzqwUpW21+2udfJxIM//tp3n8qnKHutTBH/a0IpVsglszQe/tP0qP0iy++shyG2XBT3HqEiZzmo3HxR3HsFC+wmXb77QrwpfuuHPP2/ysgPxC0h6p7lbeBw8fOopIV1UPzoIbU8EuENm6TfVnvAelPsMa7x0PTc2bPII8371pLW05C9Qd3nQtOPVLyU9piCn9zoOsXoK6gOsXv/FLXXUfsFmN01CuIZr2aj6hz9Cp1rPXSswN86XihZG7bHC/vu+/3jBdWDSLdc4wXyimtSb6PuzVL7Xq++Q0+1h9V+IMI9YZPXffimUn2I4vQhbs6V5z33ieG/1ow97dKE06ed/dMPS0v1IUqiD7HbvG/RlnRdAkVpbYP2r4p+z64G68Jk2ALWgm1hbTgU1oFnwjkwHabAqbAunA3rwVzYEC6BjeDlsDE=
*/