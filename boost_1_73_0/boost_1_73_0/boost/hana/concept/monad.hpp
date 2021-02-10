/*!
@file
Defines `boost::hana::Monad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_HPP
#define BOOST_HANA_CONCEPT_MONAD_HPP

#include <boost/hana/fwd/concept/monad.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/flatten.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct Monad
        : hana::integral_constant<bool,
            !is_default<flatten_impl<typename tag_of<M>::type>>::value ||
            !is_default<chain_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_HPP

/* monad.hpp
/zRyjomljt6yEOfATZXjmDOItkLfNXcnf5HoM+0Czv93NW9+K3CWzcBwtIDpYggbSZrv+266nNyslnA3ms9Hs+Uabr7DaLZOZL+ms8sMkJ8Hlsen1iOxuAfdtEZj1Wt+3CgGR7rms9YwuRpdXs3FeDW/FvPVYnm9EJPBEVe0xfeLDLWliRXCMN27IAyxzdUwFepEuVpc9d2DAT5xkJZvzFIAzify+z7uUGReF8JHCoa+MANafhigOP2LBJLb1/33LKWOP1BLAwQKAAAACAAtZ0pSaM9PSqJKAAApRAEAHwAJAGN1cmwtbWFzdGVyL2xpYi92dGxzL3NjaGFubmVsLmNVVAUAAbZIJGDtff1320au6O/+Kybe01Ry5O+mTeM6vYosx7qxJa0kN8lre3goibJ5I5G6IhXHu8n//gDMB2fI4YfsdN/uOU+7dSRyPjAYDAbAYID9nW/32WI7rPTj0H8OfOBfqtFfhf/jTWJ7acf5wvj/oNYf8G9ZJ/ssqfLFqbPyKl9Yjao4opdf8LvjlHX0B8KGf/ax5h8OfoUnUA1rtsLl/cq/uY1ZrVVnRweHR2wX/jk6bLAzN/C9ORvGXjD2VjcN9suUnvzXrfv5817kvWowL2bufK+gncMfG+zKXU3YReitoo9eAK34
*/