//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STATIC_CONST_HPP
#define BOOST_BEAST_DETAIL_STATIC_CONST_HPP

/*  This is a derivative work, original copyright:

    Copyright Eric Niebler 2013-present

    Use, modification and distribution is subject to the
    Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)

    Project home: https://github.com/ericniebler/range-v3
*/

namespace boost {
namespace beast {
namespace detail {

template<typename T>
struct static_const
{
    static constexpr T value {};
};

template<typename T>
constexpr T static_const<T>::value;

#define BOOST_BEAST_INLINE_VARIABLE(name, type) \
    namespace \
    { \
        constexpr auto& name = \
            ::boost::beast::detail::static_const<type>::value; \
    }

} // detail
} // beast
} // boost

#endif

/* static_const.hpp
+t8oy+wCAchgYoQam0LTCbXmJPXe56sPyfsud967p3eBp3QRz0aCDMa35ZnT7ktK7Gfv1NIPT5APebRAJ7zYJmwQ/GDgLjHF9ReGrFbkSot94dmpQaEfY4NGFIRh1zA9vYNCu0KKtxB27OcYdHY30Asr9nMsi4WxyslWmMZ4z5+KBsYOQZXxegYCNEn/kvMMVxwTDIl2qP3tv65hN0LnsvDUA60ZMeLLnbu+4ZyVMFBrdTqXd08H+rfQnp51q2kvVEDImH5XfGTQSNCcnk67B9QuREtSBSgt4bL5U+7LizWnbkI5AXUqXXQTw86Iw4ja2cqL/l3Gutl4qb0S7N92hnpmRquh7HYeuhhG2Yfu/5i+iGjTL3SdzmKrdPodf+wOLdwA3hMtX36+F53AmQReOnwDpnUj8F1jNVoePD7pjxDxbXO4f/gcCk4n/6kTm47KPEb3qYFI6cazJhlFsSYp2Tw42EFgHfTxNB8WmG//Zo4obgY0g5joPRvsNFw3FjSiAJb1Mmsz9HkMlMMVlq/BCh9tHRANbRegS88C+xvpZ8DbkK/VsgWCFcLC7WZ2+Ay/Q4iWQ9EgSZxlYjLsiGdgiCtvImx23jru+i9TPKoEnUSMsh64uOywKcuhS6PWnE88MLx1w5oj83UX/hwtbCsobc+5AUGH7IqHpnVA84CMDd4nl85xHjfkTYcK91GH/TPmBJWX+ajkkXEXUwY7
*/