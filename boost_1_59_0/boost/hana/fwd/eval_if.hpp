/*!
@file
Forward declares `boost::hana::eval_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EVAL_IF_HPP
#define BOOST_HANA_FWD_EVAL_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Conditionally execute one of two branches based on a condition.
    //! @ingroup group-Logical
    //!
    //! Given a condition and two branches in the form of lambdas or
    //! `hana::lazy`s, `eval_if` will evaluate the branch selected by the
    //! condition with `eval` and return the result. The exact requirements
    //! for what the branches may be are the same requirements as those for
    //! the `eval` function.
    //!
    //!
    //! Deferring compile-time evaluation inside `eval_if`
    //! --------------------------------------------------
    //! By passing a unary callable to `eval_if`, it is possible to defer
    //! the compile-time evaluation of selected expressions inside the
    //! lambda. This is useful when instantiating a branch would trigger
    //! a compile-time error; we only want the branch to be instantiated
    //! when that branch is selected. Here's how it can be achieved.
    //!
    //! For simplicity, we'll use a unary lambda as our unary callable.
    //! Our lambda must accept a parameter (usually called `_`), which
    //! can be used to defer the compile-time evaluation of expressions
    //! as required. For example,
    //! @code
    //!     template <typename N>
    //!     auto fact(N n) {
    //!         return hana::eval_if(n == hana::int_c<0>,
    //!             [] { return hana::int_c<1>; },
    //!             [=](auto _) { return n * fact(_(n) - hana::int_c<1>); }
    //!         );
    //!     }
    //! @endcode
    //!
    //! What happens here is that `eval_if` will call `eval` on the selected
    //! branch. In turn, `eval` will call the selected branch either with
    //! nothing -- for the _then_ branch -- or with `hana::id` -- for the
    //! _else_ branch. Hence, `_(x)` is always the same as `x`, but the
    //! compiler can't tell until the lambda has been called! Hence, the
    //! compiler has to wait before it instantiates the body of the lambda
    //! and no infinite recursion happens. However, this trick to delay the
    //! instantiation of the lambda's body can only be used when the condition
    //! is known at compile-time, because otherwise both branches have to be
    //! instantiated inside the `eval_if` anyway.
    //!
    //! There are several caveats to note with this approach to lazy branching.
    //! First, because we're using lambdas, it means that the function's
    //! result can't be used in a constant expression. This is a limitation
    //! of the current language.
    //!
    //! The second caveat is that compilers currently have several bugs
    //! regarding deeply nested lambdas with captures. So you always risk
    //! crashing the compiler, but this is a question of time before it is
    //! not a problem anymore.
    //!
    //! Finally, it means that conditionals can't be written directly inside
    //! unevaluated contexts. The reason is that a lambda can't appear in an
    //! unevaluated context, for example in `decltype`. One way to workaround
    //! this is to completely lift your type computations into variable
    //! templates instead. For example, instead of writing
    //! @code
    //!     template <typename T>
    //!     struct pointerize : decltype(
    //!         hana::eval_if(hana::traits::is_pointer(hana::type_c<T>),
    //!             [] { return hana::type_c<T>; },
    //!             [](auto _) { return _(hana::traits::add_pointer)(hana::type_c<T>); }
    //!         ))
    //!     { };
    //! @endcode
    //!
    //! you could instead write
    //!
    //! @code
    //!     template <typename T>
    //!     auto pointerize_impl(T t) {
    //!         return hana::eval_if(hana::traits::is_pointer(t),
    //!             [] { return hana::type_c<T>; },
    //!             [](auto _) { return _(hana::traits::add_pointer)(hana::type_c<T>); }
    //!         );
    //!     }
    //!
    //!     template <typename T>
    //!     using pointerize = decltype(pointerize_impl(hana::type_c<T>));
    //! @endcode
    //!
    //! > __Note__: This example would actually be implemented more easily
    //! > with partial specializations, but my bag of good examples is empty
    //! > at the time of writing this.
    //!
    //! Now, this hoop-jumping only has to be done in one place, because
    //! you should use normal function notation everywhere else in your
    //! metaprogram to perform type computations. So the syntactic
    //! cost is amortized over the whole program.
    //!
    //! Another way to work around this limitation of the language would be
    //! to use `hana::lazy` for the branches. However, this is only suitable
    //! when the branches are not too complicated. With `hana::lazy`, you
    //! could write the previous example as
    //! @code
    //!     template <typename T>
    //!     struct pointerize : decltype(
    //!         hana::eval_if(hana::traits::is_pointer(hana::type_c<T>),
    //!             hana::make_lazy(hana::type_c<T>),
    //!             hana::make_lazy(hana::traits::add_pointer)(hana::type_c<T>)
    //!         ))
    //!     { };
    //! @endcode
    //!
    //!
    //! @param cond
    //! The condition determining which of the two branches is selected.
    //!
    //! @param then
    //! An expression called as `eval(then)` if `cond` is true-valued.
    //!
    //! @param else_
    //! A function called as `eval(else_)` if `cond` is false-valued.
    //!
    //!
    //! Example
    //! -------
    //! @include example/eval_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto eval_if = [](auto&& cond, auto&& then, auto&& else_) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct eval_if_impl : eval_if_impl<L, when<true>> { };

    struct eval_if_t {
        template <typename Cond, typename Then, typename Else>
        constexpr decltype(auto) operator()(Cond&& cond, Then&& then, Else&& else_) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr eval_if_t eval_if{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_EVAL_IF_HPP

/* eval_if.hpp
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
*/