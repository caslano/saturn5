/*!
@file
Defines `boost::hana::Monoid`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONOID_HPP
#define BOOST_HANA_CONCEPT_MONOID_HPP

#include <boost/hana/fwd/concept/monoid.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monoid
        : hana::integral_constant<bool,
            !is_default<zero_impl<typename tag_of<M>::type>>::value &&
            !is_default<plus_impl<typename tag_of<M>::type,
                                  typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONOID_HPP

/* monoid.hpp
Sq9U5g/juNyuY6JlPmF8vyubWnyT+YTx/m19uVxmIgrGuW95umeizCesKFn4mNS6kh/Mnixy7N1w2U3tWeI7j+iqzDDM+JrDZzpVkPxgvmQnF+wspiwE5kNWPZ9jQdkxGOeQy7ZuHplBmDPZP82aSM2SYPm5LmW6SR/SYAXJTMsGSj1Nhhv/Omd8x4zekh+M3zlmkzL+UuYBsyW7Zeu8Q+YaxjmEfU+UMyQIxr9uDH/4nwvSdxifuyPrJzaRmYdxfscqRfvLzMN4dme/L5NPZl6La/XbpoPMPMxAFlW/ksx1EsySZzCXS6rsu5Z7/0HlAqTWMP51wHq3X2uVpcP4bL0alUPeqZnas+QuuE321vJv4xzqRmfIn+vygKl3fy786/H3te8pC4C5kt3u888dZSEwN7K+p57OVhYBK0i2INLURVksrBBZZdcAZ2WJf0vu2dZ2m7uXsiSYgeL8G7/JrSwFlpss57MvC5SlwxzJ5mxrM0OZyQjjuJ4hPvWVGWAcV/b69tbKfGG2ZDHL3ZOV+cNsyJyne9VUFgjjWtf/OWavslCYHdmjVcftlY2BcV1ytsi5QVkkrCLFuY7L5S31hFmRbcp3+5myZFgJss0t7nWRuoTjfCHbvaV2huQO47gPVj0zlQXDuGZ7K+a+pSwM5kF2ecXKRsqiYOaUX+Olja4oi4FxXZpO7RqlLB5mSRbt9XuwsgSYJ9nCuPL7lKVpz7novttVZZkwrln8s6kdlFmONL5mB9NmM5X5wXiuax1Ybq0sCFaEZ2LU/S3KwmFc67u9ghrIrsAMZGHBa3pI7jCe3daXh4dJ32HOZHVydpFap2nXPLRm0QFl72A8n0eahg+QfRhlXOv6806tVOYE42fpXb53T2XeMJ7db4YBF5SV1MxydMvbskcw3qM9M3NKPQM167IkxzZlrWA8S2f3HLmmLASWl+LWft/1r8wnzMA5PHsg94vQnrNF1/fVZP9gPEsuj9r+kP7BVD2z4utYl5slPYK5kg3/+M8EZamj5Pf5su1S03IrlKXDSlJc33VB16UPo1E3sqUO5XrJDMLcyAatbSDPGQZzJ9vpYiF9j9Liah1t9kRmUDPvWk1kzpJhah+y5mbUtPrS23ew0mTdLZpFKvMYI39mIdt6+Cc3VeYL86W4Y2Htxkt+MB+yBzcj7sqOwWqQpRTPc1BZAqwI24h1Mp9pMHey2fXs05SZjEW+ZJ02fJVa+8KsyM4HXTgicw3j51zZ5vAXmU+YNdmPcT/9pEcwfpYRZxraS49gHmRj3narIT2CmVE9b/uEtpXcYfkorsWoX42lfzBHrvXlYv4ygzDu0Zptc3NIb2F2FHfZzumFMrNxmGuK87rrXkKZAcZxv2ef7Sf1hFUlsx5oLTPYA2ZO1/Scfr631AzmSnHVFzZ9rGwmjOuyde+0S1JPmBfF1aoR8V3ZbpgFxcVfPjRDdhpWkuLONPWaJnWB2ZB5zA8MklnCFFcmG93zq7XMCyw32WTfhzIvgTCuWZz5aIPMEqwoWYddKSWVRcLKk7VcaX9YcoDxbj5JL7NccoDxXG/aO6qs5BCBs44sJMF2jOw0LD/ZdXPHb5IfrACZ+6G2GbLTmm0xtZ2rLFS75s21Ga2URcA8yR5WyT9JWRyMa1bh/KPKkrsWV/vJ2Kky85r9mP2jmMzuBOM92j+3wVKZXVgessB9Ew9J7jDOwXbr/PWSu2aTor27S+4wBzLDoEA5y8fAeB9uLMlZRdlkGO+fW8s++2QfYLwPd29fCJV9gPHM7z7fWL6zYmA8EyWWZPw/90Ej4mAF/29WJsN7vD+9+ZuyJJgz2dQz+54rS4e5kDU+2/qlMrOJkkO2dZxQ+5k=
*/