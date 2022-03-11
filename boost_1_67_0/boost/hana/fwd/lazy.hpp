/*!
@file
Forward declares `boost::hana::lazy`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LAZY_HPP
#define BOOST_HANA_FWD_LAZY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-datatypes
    //! `hana::lazy` implements superficial laziness via a monadic interface.
    //!
    //! It is important to understand that the laziness implemented by `lazy`
    //! is only superficial; only function applications made inside the `lazy`
    //! monad can be made lazy, not all their subexpressions.
    //!
    //!
    //! @note
    //! The actual representation of `hana::lazy` is completely
    //! implementation-defined. Lazy values may only be created through
    //! `hana::make_lazy`, and they can be stored in variables using
    //! `auto`, but any other assumption about the representation of
    //! `hana::lazy<...>` should be avoided. In particular, one should
    //! not rely on the fact that `hana::lazy<...>` can be pattern-matched
    //! on, because it may be a dependent type.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! 1. `Functor`\n
    //! Applying a function over a lazy value with `transform` returns the
    //! result of applying the function, as a lazy value.
    //! @include example/lazy/functor.cpp
    //!
    //! 2. `Applicative`\n
    //! A normal value can be lifted into a lazy value by using `lift<lazy_tag>`.
    //! A lazy function can be lazily applied to a lazy value by using `ap`.
    //!
    //! 3. `Monad`\n
    //! The `lazy` monad allows combining lazy computations into larger
    //! lazy computations. Note that the `|` operator can be used in place
    //! of the `chain` function.
    //! @include example/lazy/monad.cpp
    //!
    //! 4. `Comonad`\n
    //! The `lazy` comonad allows evaluating a lazy computation to get its
    //! result and lazily applying functions taking lazy inputs to lazy
    //! values. This [blog post][1]  goes into more details about lazy
    //! evaluation and comonads.
    //! @include example/lazy/comonad.cpp
    //!
    //!
    //! @note
    //! `hana::lazy` only models a few concepts because providing more
    //! functionality would require evaluating the lazy values in most cases.
    //! Since this raises some issues such as side effects and memoization,
    //! the interface is kept minimal.
    //!
    //!
    //! [1]: http://ldionne.com/2015/03/16/laziness-as-a-comonad
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename implementation_defined>
    struct lazy {
        //! Equivalent to `hana::chain`.
        template <typename ...T, typename F>
        friend constexpr auto operator|(lazy<T...>, F);
    };
#else
    // We do not _actually_ define the lazy<...> type. Per the documentation,
    // users can't rely on it being anything, and so they should never use
    // it explicitly. The implementation in <boost/hana/lazy.hpp> is much
    // simpler if we use different types for lazy calls and lazy values.
#endif

    //! Tag representing `hana::lazy`.
    //! @relates hana::lazy
    struct lazy_tag { };

    //! Lifts a normal value to a lazy one.
    //! @relates hana::lazy
    //!
    //! `make<lazy_tag>` can be used to lift a normal value or a function call
    //! into a lazy expression. Precisely, `make<lazy_tag>(x)` is a lazy value
    //! equal to `x`, and `make<lazy_tag>(f)(x1, ..., xN)` is a lazy function
    //! call that is equal to `f(x1, ..., xN)` when it is `eval`uated.
    //!
    //! @note
    //! It is interesting to note that `make<lazy_tag>(f)(x1, ..., xN)` is
    //! equivalent to
    //! @code
    //!     ap(make<lazy_tag>(f), lift<lazy_tag>(x1), ..., lift<lazy_tag>(xN))
    //! @endcode
    //! which in turn is equivalent to `make<lazy_tag>(f(x1, ..., xN))`, except
    //! for the fact that the inner call to `f` is evaluated lazily.
    //!
    //!
    //! Example
    //! -------
    //! @include example/lazy/make.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <>
    constexpr auto make<lazy_tag> = [](auto&& x) {
        return lazy<implementation_defined>{forwarded(x)};
    };
#endif

    //! Alias to `make<lazy_tag>`; provided for convenience.
    //! @relates hana::lazy
    //!
    //! Example
    //! -------
    //! @include example/lazy/make.cpp
    constexpr auto make_lazy = make<lazy_tag>;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LAZY_HPP

/* lazy.hpp
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
*/