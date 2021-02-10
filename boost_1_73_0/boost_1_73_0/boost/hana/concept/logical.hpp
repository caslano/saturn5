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
ef4mfhOfX9w5Hk9n5zI43bO8U6X4LxV4OuZvAh5wdEDy+nUbEZBcnXU0/WpES5O1RPzW3VbFvjuns3DOw2bD/WpN1ql1eXkynLw2S4vyKFSZjItHsmns4W2xOy7l31ZCRMcwnhyfkiNruGv+mZf21VKe1pVoL4eqpFEi+Fepi7b/uuHP/MHC7dXAygmsNLKqmIpDr0bjQxwgpebGkJwGN3V6aXNxifnvHfbqpysN5wFC3YchJphkQuFOazB9r65xGVTEaeG8IW3XZdpPFZHJWkezxMxyUZWgMlFRyCnnAe6tX71IzAs2o7+46ubVPk3+B+kZYuzLIXjKyZH63VnxG40N9gmNFjrMLs7OXGh6/r17OD77eTSdXaDvcaS8EWjm63WCOTXFLVVfaTHHnoNCJpawdgt+Icyc+t6AUbFFjlj29iPuxfm6SgC9VYskUGKFaC5PVJuGV421GTA7cP0PFSqcQbdUScQyzxbJdXUeFIxqkRSVXz/V2QIK6/5WZZ4UgEWyqpEhIKCW2lLw12fovXL0/f/KuSBJ41LqLQWLyu80CE3LQXaoEpjHRk4TgdmhIFZo4pbZij4mTRlOmsRhdSj5xN3fMpEyIfRRCNhqVocNHh6rNpIgYKzahOE1bGmYLXWqzOXxZRjbfBKV
*/