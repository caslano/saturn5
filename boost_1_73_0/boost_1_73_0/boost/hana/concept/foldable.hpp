/*!
@file
Defines `boost::hana::Foldable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_FOLDABLE_HPP
#define BOOST_HANA_CONCEPT_FOLDABLE_HPP

#include <boost/hana/fwd/concept/foldable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Foldable
        : hana::integral_constant<bool,
            !is_default<fold_left_impl<typename tag_of<T>::type>>::value ||
            !is_default<unpack_impl<typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_FOLDABLE_HPP

/* foldable.hpp
dPjL6Hw0baR+OTxyjy8mh8iLO5y+uvhlNDmXA4KderC+RrLpCOhG0+npVC7gU0eLEXXW8VPXVFvXMg94iMHSsANZReyAh4XWxH8fgoP4IMWsOh/iluCeuGGbRLBP5FsH+LBbNTw0TTW6Ww4Pb4HsqaSDh1+Lmf5pWGPVrNmmelJTQvvWgXqFZGEcJEEXezpsQxmEuWb2ZPEu3nCYIpEc68YejqAE2thh15CoNkyUqlpdt0U6FxNwLEdS5U6nKby26eAepJaSrP5qYzRIRM2zA64fnS1fwVbnKBhTAtKkZrMT9/B0MhkdnmvL+oR7HR34acy45y9hq8c7BCC22JR7EGKZv8zj9xhI5jcZBK0gVdEIGeUZ8pwoB/GMwc6AF+s8Y/M8CHjaV0OdQ+BTnTBYrdPExwDhxTcs5tcQxHEo0TcnTmAQiO8r7LOOPJiGf8hMHtRwiAES8GcQ0TH8ZWHElmGWgYYVDiKn4bDR6bGDEWk0fDUcTwajN6cXJ0cvT04PX9NrmgKYHtCXCJweREQIlxEEQwgsKmaOs2cQ1t4DDIBV+B4sinBHkMc+Yg4GLmZZDMX29xn6BxnW9bDwcpsWOka3CRgEvQrszwyIYTyEFA+SNA4lha3wg5KtkilsDxDkdRI/I5MU+YrXhfis
*/