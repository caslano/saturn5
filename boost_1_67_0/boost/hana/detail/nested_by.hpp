/*!
@file
Defines `boost::hana::detail::nested_by`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_BY_HPP
#define BOOST_HANA_DETAIL_NESTED_BY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>

#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename Predicate, typename Object>
    constexpr decltype(auto) nested_by_t<Algorithm>::
    operator()(Predicate&& predicate, Object&& object) const {
        return Algorithm{}(static_cast<Object&&>(object),
                           static_cast<Predicate&&>(predicate));
    }

    template <typename Algorithm>
    template <typename Predicate>
    constexpr decltype(auto)
    nested_by_t<Algorithm>::operator()(Predicate&& predicate) const {
        return hana::partial(hana::flip(Algorithm{}),
                             static_cast<Predicate&&>(predicate));
    }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_BY_HPP

/* nested_by.hpp
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
*/