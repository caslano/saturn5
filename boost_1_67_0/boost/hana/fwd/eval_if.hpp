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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr eval_if_t eval_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EVAL_IF_HPP

/* eval_if.hpp
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
*/