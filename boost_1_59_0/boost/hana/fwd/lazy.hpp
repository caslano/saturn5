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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr auto make_lazy = make<lazy_tag>;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_LAZY_HPP

/* lazy.hpp
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
*/