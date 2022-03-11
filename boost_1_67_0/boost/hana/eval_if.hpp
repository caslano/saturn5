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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EVAL_IF_HPP

/* eval_if.hpp
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
*/