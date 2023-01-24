/*!
@file
Defines `boost::hana::Applicative`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_APPLICATIVE_HPP
#define BOOST_HANA_CONCEPT_APPLICATIVE_HPP

#include <boost/hana/fwd/concept/applicative.hpp>

#include <boost/hana/ap.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename A>
    struct Applicative
        : hana::integral_constant<bool,
            !is_default<ap_impl<typename tag_of<A>::type>>::value &&
            !is_default<lift_impl<typename tag_of<A>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_APPLICATIVE_HPP

/* applicative.hpp
B+5ZcKxrCZKaFlGsnZn/fD4W3VZHelV7MEV17FfmZR1cjyHj7Edd5/LoIgZVj1eHg6BkAQb87cW4xp9RLyHin03VdK/9rOmMQLrXviu57tXCthlI92oS/mvdK3TlWboXX878h/Dvo4n9QohdztwufLcqJpMqtp+rYqiHFnwiGDyJV0WXMx+/EvF8iPEJX49YBErWfY/ReibqWftAeY3qWQ3fCJGJ/QJBmz89fyRpnGEQnzloNagSYnUzf0yejw1anjl/JL2ujZs94ijMEEyI4wQuRlj1zM6YzL/VM/e/JGgmkmOezVigOKTAlJg8d+p5Gl/i0c0uMcQqQX8Pk2oecWjHCPiIqhkdsYuuYraujOkBg9SXz0d4S9UYZazl/MrYZiw5Uo8V8ATKWPVEUsZQsyloYUU4yaAqljSDB59tRZK0XUSqGDAAYgMtbOZpSHaUlp3p2AKucyulA25yQ3kMw3LGqt2uWLUbPWcSPTkLUCFaSCmL2Z0vYt+UtqunQFJTGxXg7GdAlIb+wa4CjqPPcfuyHG3ig1eiqiAdpmnOzSZrxQWceCgK9ulq8SztbdSLmtRMc5ybfTWI+kMHpMlq9tmc+nnkUgaVTXxG4zLzh3KZ6UMP1p1UrNl2inXbTgfadu6F+gV36VPbNO6oxKu2b9RZVdvwBxIFO4JKMQk0braCKsf8RZ3IoC2aSikUu5ww+5AsI9Z8Qs4jPquT
*/