/*!
@file
Defines `boost::hana::Orderable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_ORDERABLE_HPP
#define BOOST_HANA_CONCEPT_ORDERABLE_HPP

#include <boost/hana/fwd/concept/orderable.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename Ord>
    struct Orderable
        : hana::integral_constant<bool,
            !is_default<less_impl<typename tag_of<Ord>::type,
                                  typename tag_of<Ord>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_ORDERABLE_HPP

/* orderable.hpp
cqenGH1xdWbachvaPPxya/awkzx7mNOB/IkfrieZaXYVGdTsqgRcxcoFQCjNiuvuyq0mRB/cl+oGy5nagzGCJo+OF4bgq118xc8jg2ROxOOFEE3Iwa+Bik8YTVuvPVVSRvpbJ1bxHQeHGFT5pWAlK0AZN9gG0UO9gHCRligNKyhHp2b0qhDtrI/3kDu/unN67IiyDOYUpc6IyelnTq/PHy5K/mHcJ6oHWT3SqU63DsOGoi1w
*/