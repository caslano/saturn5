/*!
@file
Defines `boost::hana::Comonad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_COMONAD_HPP
#define BOOST_HANA_CONCEPT_COMONAD_HPP

#include <boost/hana/fwd/concept/comonad.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/extend.hpp>
#include <boost/hana/extract.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename W>
    struct Comonad
        : hana::integral_constant<bool,
            !is_default<extract_impl<typename tag_of<W>::type>>::value &&
                (!is_default<duplicate_impl<typename tag_of<W>::type>>::value ||
                 !is_default<extend_impl<typename tag_of<W>::type>>::value)
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_COMONAD_HPP

/* comonad.hpp
nGtf5UyuMWXq1muBnL+bf8xKEC1JXpyeyQTnUsKJZRm6h6T4N/UARrgPOzc6KGVCQYGQgivRJ1lioMesv8L7s4uTk/brPdjwz99Fv+tnzdNzIrd+qOGgvReGtL97gPjylGA9Xh+evAOevTg8b56pD4Fc28+8l1iH0VhMKcxFLdf1G5Shjw9hJVNXpzLEhJg3r8hBic95+lnsQPMYzcaNsJg8VyVFKc2VVAcDUyeh4XTvvLLmJhs+V2Wz69m0l370q0U/qjxXRXVcq3aS6ueqOOswAQkwZp+e6+7mVx5il4Ln+iuW5TzhJLQ8V1KHfjdUSf1cYMkNo8NCgoanhq5fnqn6veWm4ZV0z70pT7M4ZA3rqLMqlCvbBvUxnErzXE8l6DF4YkNkBD0/+rlXfAqqVB/W4IZXtXteWLgtRuRGUNg8Vx/xi6yN8OW6Q/q5ojjMQ9y+AlpRivgJf0LeWftIjLpfSl+KAg0pJwPmOTYr2xDp7YU/+S94i0JwU3teuDizxgos8z9QSwMECgAAAAgALWdKUlWz67JhAgAAOgUAAB4ACQBjdXJsLW1hc3Rlci9saWIvdnRscy9vcGVuc3NsLmhVVAUAAbZIJGCtVNFO2zAUfe9XHJUXQFnDeBobmlaVblRDLWqLUCWkyI1v
*/