/*!
@file
Defines `boost::hana::Comparable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMPARABLE_HPP
#define BOOST_HANA_CONCEPT_COMPARABLE_HPP

#include <boost/hana/fwd/concept/comparable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename T>
    struct Comparable
        : hana::integral_constant<bool,
            !is_default<equal_impl<typename tag_of<T>::type,
                                   typename tag_of<T>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMPARABLE_HPP

/* comparable.hpp
3w8xZznNCVmWy98PzbOJqTJe7WTkg92P79WR7tRaESLnWfxxTqI/idik2TUuWzn/XGAThXLMEkW/j9373ZNGZPVpfs2Pcw1UNyfdamFa4Fy4u4/HvWgTY+R+PFrLxbAk7Ue5F+NzsnAarwWbHTtdGt0pWrtLw6QRW6Xyue0LbWKNjL8T/fyo69u5Qj64uCjGeNezoR/afkIXe3dzIneVzDFv3mgTN8ntXMvdOPpQgDwPrydKqK1d9xQFmBhzmlOrXGpK+jifB60U7dnX+39mE4F6W9sTumgPPrmx82xDg/Wcdvqci/63f4k7MSk7XhY/5Or4wXRbujN+wE30NqpzZJQ9MrqLJvRwj3iqFo0Us7Qbc7RP/1fLaq8/5OjiD3rx7/zqLTarv1aqN5VJa2pA70i6fdqna5gLpjdCVKOefcQsUE9+KIo5VeWy6X016tpXTAN1NR6iolfz6h7xdG+u9lzK8D7afS3h7SZ0i2kffwtlBM+4yxl+fUqWMz7KrrcsNbM9Mqpzp+6dIu3x49P0lr7LqZUkK8V9NIeeO9Bc9lFtiJEVn/aGoQNFiTwWaRMptSvVa3SP+JEpdLdZSpIz/rp07Ya7pMQUukctPntUlt7j0pxaooZII/WGIzNj7B1RUfZOnWK6R0fHU2fLjB+Rlki1oizR8k7cO/5R/9Vg0GB3VPpmRbnDR2gxhccl9PBYt/3FKrndJQv3/qarr2MyHiLhk4D0sTDFEyXjucwjnutF2d/EY/F1PPSDckmPcfokoqq2hxv0PNH62I/+rWNSvxvjlAmxfROSts71nPWd5bZ0Of384liIPEeNE0F0rua6xzjEvJiMVOk+igm303A9Jye/TIpJJiz1SUQWmeOvu2yjK+nnws+fay5rLFbI8efMWnSWaVI88g5/n8VzmvItvSPjiaWfL2+0vmhoophfW84BUjxNTYqHbvTWU6L5IiB9X3ec4rEY8Vyl3Xs6p7UcK16n3+etj5ks5m1DlGptvJ6q3Uf7OovM4Rws26iXNmdd5+ps1+ivoToONCkmI6UNpeXVbqz3SUvpcem5Ha+RbaXNST7bc0qA62g0Tfa9gzbTtyUKzTkuK8Phk8As8pletWV7ac+zWWS3zDN0kP48J30fYWIf1DPvjxo9xhcBWeTzLAplPNdo9Uzaqn0FrGcsT5URzKU/rGtSPHRcco53+O7AhI9LCaKnbCOHltfGpJhkGgGfBITjuVUE+2Ef4U7a7psRkcXIYc7nv321K/yHlWUYertfYtLu/vddRFW10wi/xESpF3wWEo5npAjzQzxq1hifBKXVVeZCD5F973r6eeDZoMcMHcX7cDtFdL5ZcaUbzyv3zVGpqraK98s4gjJZ+Knv3aF9D6K/4kyMx9tTC3yzV68qxttEmB9irPwEC1+EZpHP87hAbl83aN9hbJwh7+Mapo8lXPmNwkyLy+uzP3wRoh5jUIV73B6nzYEl3HeXnJUTzfywvckxhq+H7lps+jN9gmRsN2pzFXFNrjJ0iOgmY+tr4phQeZyPT0aFWpWbKTEN8ojpZo5JyxUYbHJMiVkZPtmFWOTzifvJmG7StrOE+0boSP83WEaxmf7wPJNi0hvISd3PR+fDeJ+YxJOXBy3mnTcq2eh9srPAMd3E441YE7cn/Rlqvj3NMu4FodywDeTc8xChvgaIor+Ze07zcVyVHp7nk17otb1c+m/mNTNSE9NpNOFUI7ujU/eobhRe1yglNP5L/TwlPYMiS6lxZDf07z2QntR8UzVjGwu/FzMSuvrm26ZxSZnpSamdoqs/HkoVeaBualJWrX41XlPZo2Tiweqed08VK0B9QILPf7b6uthj9NVHpWn11d9Ue78=
*/