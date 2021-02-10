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
MJjNvO5wuJstwnE0jcZA6wm/QTqMLob7w+GFNwsewnTP6yb0GuHAsL27fJbtjSWrhXcwlDHCg8Yw3QgA/p4u4zHyV4ZjAjT+FMXj2RL62EYm8rMwXy72brfxxXQSTr2rYdsHhMwP4btJkAf4lX6YhfFkaj8CrOfiQ29/Rw3iOoFZDtIHhQriYUEvNMiyGYwznkY33vg2HH+qaAifxCDLCmjl6TjIwiKus9KHRDzryQyWQeGj+XKWR1FhmES3RRrFeeFFnGU31pOf4myR7t2+sZ5k9gMYbOlBmBZaZSBBHM9gJZfaLtIkT+ynizR/WISFfhefDg9h6Re/jJJSL1EezksPF0ma2w8Bw3xSgAcLMXz5Xfm7Yq8wuKQwvE/hw20Ej/RmwwwybLfetz/6ZyHMdPLQR+E1fh8+1OoWc+BI7oI83F+IIcnm/YHfmSPyo1Z/mIw/gfSnVQGsH8UhLsUP7UH36tKr1eBn/8Nl8z97g59+OnxZ/1086HTxwQ/13+nXfnPUelen1WM0fvPaO/h8cHwwPTjAjo/3Dr/fO7ARBMm9oBHDOoqmW+tYGIRePAuzAst+/v7gxyCLD2kB7+/QFjILstxTn6CgyaSIuA5fFZYQsvI8nCfpQ4Hxw/kkvF7esGQQxAFJ5J91Bt72
*/