/*!
@file
Defines `boost::hana::insert`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_HPP
#define BOOST_HANA_INSERT_HPP

#include <boost/hana/fwd/insert.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Set, typename ...Args>
    constexpr decltype(auto) insert_t::operator()(Set&& set, Args&& ...args) const {
        return insert_impl<typename hana::tag_of<Set>::type>::apply(
            static_cast<Set&&>(set),
            static_cast<Args&&>(args)...
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct insert_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct insert_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename N, typename Element>
        static constexpr auto apply(Xs&& xs, N const& n, Element&& e) {
            return hana::concat(hana::append(hana::take_front(xs, n),
                                             static_cast<Element&&>(e)),
                                hana::drop_front(xs, n));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_HPP

/* insert.hpp
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
*/