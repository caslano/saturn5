/*!
@file
Defines `boost::hana::MonadPlus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
#define BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

#include <boost/hana/fwd/concept/monad_plus.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct MonadPlus
        : hana::integral_constant<bool,
            !is_default<concat_impl<typename tag_of<M>::type>>::value &&
            !is_default<empty_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

/* monad_plus.hpp
wOeAjwJ/AtwARIerHgP+QcmeDA7UfwjMC2nbdWLfkOzRKAnJHo0q4JPMR0j2alA0v+1E89taDLc72keO5tlr32V2mmZUgtJFiuhdba4tol0rdugm4+HZh8qpSNCScrRi3Eovtn9/nCOb2wy8e/hU2r/+N9n7rX1swXLPt0y7XHOztnHpP/SYiTz5MsEOAkO1BPM22gxXqlxNVYXtgo/Q1jhaQImRS9MrsToqMcagR4DQCzoXQN0LxNqfKknQobU=
*/