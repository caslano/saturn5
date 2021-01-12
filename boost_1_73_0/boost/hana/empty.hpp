/*!
@file
Defines `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EMPTY_HPP
#define BOOST_HANA_EMPTY_HPP

#include <boost/hana/fwd/empty.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    constexpr auto empty_t<M>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::empty<M>() requires 'M' to be a MonadPlus");
    #endif

        using Empty = BOOST_HANA_DISPATCH_IF(empty_impl<M>,
            hana::MonadPlus<M>::value
        );

        return Empty::apply();
    }
    //! @endcond

    template <typename M, bool condition>
    struct empty_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct empty_impl<S, when<Sequence<S>::value>> {
        static constexpr auto apply() {
            return hana::make<S>();
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EMPTY_HPP

/* empty.hpp
QViGmUF5xbp8dbBNBFXXNXM/ldRoSPREyjsT2dzxVhUZeRI8fXTaA+1ZTv43IbPwNmc8GBnusRZV1e9QLhO0WHC6pAQNch8EX+V9evYR1z6PqRu3dZt4XlVVq7zaYFv5Y5VtImTa0WBfYkSI/5ZEud/QbYSwOloWyQuzv4pyTlRgyWir7q5yf/0eSUO+7gq5s7jHNrJfprqzeTEGXOHexbhNsLarW1ibuQpuw6VkagsvJWrO
*/