/*!
@file
Defines `boost::hana::Searchable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEARCHABLE_HPP
#define BOOST_HANA_CONCEPT_SEARCHABLE_HPP

#include <boost/hana/fwd/concept/searchable.hpp>

#include <boost/hana/any_of.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Searchable
        : hana::integral_constant<bool,
            !is_default<any_of_impl<typename tag_of<S>::type>>::value &&
            !is_default<find_if_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEARCHABLE_HPP

/* searchable.hpp
UvqFc+/gpgSvfhkywZFbfS8+Dly93FblUS/pdEtOoPAxYwA63hX+eF3QhKN1ONr/hDMYcVBkvJyxR1+VsDuM4aohPWOk44q+KuYEVzEnOJE5wYnMCV9Om/iVLkf6Ff1ok+cPdWR71WvyAvvd1LtDhgb07rChKXo3nWZZH6imGUZ4DnDVdEDYKl2h3edoX0p45qnUPRNe4TljnCPbytEXCQ9cdj7Zw9s1pxOeYOFPMYUvdoUvdsJT7ISn+H8nPBw=
*/