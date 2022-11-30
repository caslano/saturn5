/*!
@file
Defines `boost::hana::if_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IF_HPP
#define BOOST_HANA_IF_HPP

#include <boost/hana/fwd/if.hpp>

#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/eval_if.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Cond, typename Then, typename Else>
    constexpr decltype(auto) if_t::operator()(Cond&& cond, Then&& then_, Else&& else_) const {
        using Bool = typename hana::tag_of<Cond>::type;
        using If = BOOST_HANA_DISPATCH_IF(if_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::if_(cond, then, else) requires 'cond' to be a Logical");
    #endif

        return If::apply(static_cast<Cond&&>(cond),
                         static_cast<Then&&>(then_),
                         static_cast<Else&&>(else_));
    }
    //! @endcond

    namespace detail {
        template <typename T>
        struct hold {
            T value;
            constexpr T&& operator()() && { return static_cast<T&&>(value); }
        };
    }

    template <typename L, bool condition>
    struct if_impl<L, when<condition>> : default_ {
        template <typename C, typename T, typename E>
        static constexpr auto apply(C&& c, T&& t, E&& e) {
            return hana::eval_if(static_cast<C&&>(c),
                detail::hold<T&&>{static_cast<T&&>(t)},
                detail::hold<E&&>{static_cast<E&&>(e)}
            );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_IF_HPP

/* if.hpp
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
*/