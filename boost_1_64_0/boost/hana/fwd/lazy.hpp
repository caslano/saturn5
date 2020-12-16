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
XkTelTGVPQsQqHXu+IAWaoRkT/JWem/QIiG+wLwOkK3PWzyvnQor00QtmX+M87fWDyalcrz4u0VtvqZ372FBVL1mHBr/DafjclY5yOBAnI7G5LeWMW8ZS9sbBuF8Jw5N1WtG0ms0JskReUkm6VIkZVcP55Ooq3FjQ3+xmssiO86ARtt34aRhXUaW1e3I2bKXOGl30u5ufESh7IsvEGU29Oir9u6XYDQwYORaX4Ktnkcjz2+xT+Rni9pJoEn87Wm4QV2fyUc4hfdcsTqxfUR7KufpdkkGNrrrZ+IFyhL1GiXQEY7nkOPMgdrIv/iGc9wc2EdQpfXpvRcIFIGrBSf4V1NhApnW/Y7ULxTentLzlhKxb5exFMx54jYdH+7GCWneAOCdbRL25i+C10gW2JGrqx7YKAfwQkYH/m315ajCWNKXEJUjPZjYRgYnGKESstPHs0C8I9y8EeH82fQM1aZeoxGh+YjS8B+XOWx0L72DLM334FBTJXscWhZ33UJ9goNLjrV+OX+gn5z/x4oocGIax1oBc/rXuWPHKXMvD5IgLqAu+vK3uWMOFZILK5O4a6kR3mXmtN22X7quTLqnmQPpeyaKjLTFarAOf6E4RS1oQ4B0dvFpHpHEJ6QBoKyku6ukCcyRkqz8T9LQFa0khbg6P+z2TOgiXVp8cr6jOdbqdHtchfPcb7e5B0/e4PZQjaa4PQMVZGCsOR/xO9yeKYM6jEj4KHUSJMeATHF2COTuhyap7lc0L3iY0eE01NykPfVTilririepEkVvUY+gypeimpfi+zkxG289CAtw/YRG9+eNoXvzxveOKT2uN/YGHI/tlydZqGDA3Y027Bjjk9LEfsSLsxLpfkJ7ktwygvINEKVP9pIn03cD8mHCezPZxwGlTbzeL56XTVOi888YYcbK8lnwsYRXL5bXOhT+dO2HP0tnVc0h/Car1zMSLUZmMGOv/Psg0f/hH/Mvucy/XOEm/uXatRn+5ZQIk7QfWuIzr+I++kiAPMS7bFp7VLzL/vzLHdApVO+wH4J/GasdzL9cs/GI/Et8k8G/vNZnn9So+Be/Miys3mkGYfvX+Yn4l1LWf9n67u9KSLePqT2TWIzZ1KEXEUm5yHA0kUfiYkLDRFXN00sh/77aE2fgQOPGjdyNkIkghxJs4MZwb5cm5fZjSL3V9bSiyU6ix2/b2VFTUFRpsBlzPA8y+vBGi2ptsJMsVp+jwYBvXmyvdmWlKMMuCdhviX8lDnuuveockTzFYeK13hLxdFFbrEXzv1P3gai3xSc4sJQdcVdW4oOsxHYt0Zll0Nd8/7v1QxX+Qo6tGiyOyTLi3bp3iAL4tvDFG5drZDx3CtUwos2z6CF2UmwUSOZruLYE9Aaqqkl2yCzhvCflEBM0pAdOIhqwDvF8CCeqYcoHsuMX2kXxcv9qxN9NaqPlGkswgSjDAfy/KCDlQOVoA18zIwT7UkA+o2CVvm6CmjGfBBTDE40ls9AQ6HZ80EIRF0B9L9p9lGBmwZQxrmyx3occEcn3LCCj8Dda1CFkpl0DEFS6VEfkMVG7E59j6uyuWMJJPUXNRPv9L7hvIHrKFBK9gwKNTvJvdd/wOglE5Q6lRxxHeK9UTgM7zRYC+/ONs1jedeVqTAIQHVpkmECYLJgoTjtPlKOfu/8OP7X+c2n9v431v1g71Pq3Zdb/lAgvcnnNusz6PxHrH9sASEEtZJSSvIqw/E+obtQyy/+7avkXv6OWv9Cs5f/oq59k+RvnEadj/0BLvNDXRL58qNpsRJ1dy7r3AvnFbRnZSZV19DCE3UnOQNqdHN+mVEQl0kNvkOU729Q695AwhNb6C4YJ1FhWw5zZZbHYCQQQXHo=
*/