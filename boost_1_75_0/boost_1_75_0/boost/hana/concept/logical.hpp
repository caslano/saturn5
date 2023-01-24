/*!
@file
Defines `boost::hana::Logical`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_LOGICAL_HPP
#define BOOST_HANA_CONCEPT_LOGICAL_HPP

#include <boost/hana/fwd/concept/logical.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/eval_if.hpp>
#include <boost/hana/not.hpp>
#include <boost/hana/while.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename L>
    struct Logical
        : hana::integral_constant<bool,
            !is_default<eval_if_impl<typename tag_of<L>::type>>::value &&
            !is_default<not_impl<typename tag_of<L>::type>>::value &&
            !is_default<while_impl<typename tag_of<L>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_LOGICAL_HPP

/* logical.hpp
TWaDE4P1B8xONmZMjBzizzU3C5jKyUrx/dmZnSwPXqM0U8KlmNIQis5abn5Wi7+gl2F0IM9DE8wU5p8tN+tmH/rowo8d+sfZ+FHNNQP/j6vPxwqDYJ+aAlPoD7/B6ciCe0u4RCFtlDfbTNK66s2JqXE/He8bAzeT8GYY3EyGG6lIzU+pbfUtUwvNte/5LkVxaUV4XTIFMtJYdnAW6ZXdbBFy5xKUTIKdfYINtMWcZNUCuW2g8arrLFGLxXdI+dCf4SIrnqWCUj0I877ZZMNSr6q+mqo6Sd4CVZ1QvYVXNRluqKoi3GBVffGry+yoY5WPhulynU3dZGar6DaRTfyS44tdCy/UnDQtslGmxWdVcxBRXwMbwQ3R3OhUYFWLQA0W1LvNpr0YX1hdalETx6rW4aYDpga+0Zw7XF1dfc2KRYs6AHHXFCyH3+HV15CkNiF4AfsHSKvy5mTDFgt7H27D+cmrSUtmb8GTstmmbjSz1228gveDyrmfvYQ5ArZG9izdJDa61GOFhXJnj7zPXKSuNcMkaibHL8DMfVZ7QNwp4gbzrAag30WWrgw8zGUB8XDxYQzEpTZPDYvo4V62oAd+N8WJtoTgdK+lXPwK8rbeIO5sKBc3tBvLxX2BBHsAV6DjTIMAVf5ckP6pFoRUl0XdSzA4gFXl4vxbjSM3WuS96LMV/Kco70IlkN76E69Vr7Oq36jNMBXFZFqgNsQ8
*/