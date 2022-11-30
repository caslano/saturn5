/*!
@file
Defines `boost::hana::eval_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EVAL_IF_HPP
#define BOOST_HANA_EVAL_IF_HPP

#include <boost/hana/fwd/eval_if.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/eval.hpp>
#include <boost/hana/if.hpp>

#include <type_traits>


namespace boost { namespace hana {
    //! @cond
    template <typename Cond, typename Then, typename Else>
    constexpr decltype(auto) eval_if_t::operator()(Cond&& cond, Then&& then_, Else&& else_) const {
        using Bool = typename hana::tag_of<Cond>::type;
        using EvalIf = BOOST_HANA_DISPATCH_IF(eval_if_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::eval_if(cond, then, else) requires 'cond' to be a Logical");
    #endif

        return EvalIf::apply(static_cast<Cond&&>(cond),
                             static_cast<Then&&>(then_),
                             static_cast<Else&&>(else_));
    }
    //! @endcond

    template <typename L, bool condition>
    struct eval_if_impl<L, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename L>
    struct eval_if_impl<L, when<std::is_arithmetic<L>::value>> {
        template <typename Cond, typename T, typename E>
        static constexpr auto apply(Cond const& cond, T&& t, E&& e) {
            return cond ? hana::eval(static_cast<T&&>(t))
                        : hana::eval(static_cast<E&&>(e));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Logical
    //////////////////////////////////////////////////////////////////////////
    template <typename C>
    struct eval_if_impl<C, when<
        hana::Constant<C>::value &&
        Logical<typename C::value_type>::value
    >> {
        template <typename Then, typename Else>
        static constexpr decltype(auto)
        eval_if_helper(hana::true_, Then&& t, Else&&)
        { return hana::eval(static_cast<Then&&>(t)); }

        template <typename Then, typename Else>
        static constexpr decltype(auto)
        eval_if_helper(hana::false_, Then&&, Else&& e)
        { return hana::eval(static_cast<Else&&>(e)); }

        template <typename Cond, typename Then, typename Else>
        static constexpr decltype(auto) apply(Cond const&, Then&& t, Else&& e) {
            constexpr auto cond = hana::value<Cond>();
            constexpr bool truth_value = hana::if_(cond, true, false);
            return eval_if_helper(hana::bool_<truth_value>{},
                                  static_cast<Then&&>(t),
                                  static_cast<Else&&>(e));
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_EVAL_IF_HPP

/* eval_if.hpp
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
*/