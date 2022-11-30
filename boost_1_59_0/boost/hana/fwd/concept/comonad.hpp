/*!
@file
Forward declares `boost::hana::Comonad`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_COMONAD_HPP
#define BOOST_HANA_FWD_CONCEPT_COMONAD_HPP

#include <boost/hana/config.hpp>


namespace boost { namespace hana {
    // Note: We use a multiline C++ comment because there's a double backslash
    // symbol in the documentation (for LaTeX), which triggers
    //      warning: multi-line comment [-Wcomment]
    // on GCC.

    /*!
    @ingroup group-concepts
    @defgroup group-Comonad Comonad
    The `Comonad` concept represents context-sensitive computations and
    data.

    Formally, the Comonad concept is dual to the Monad concept.
    But unless you're a mathematician, you don't care about that and it's
    fine. So intuitively, a Comonad represents context sensitive values
    and computations. First, Comonads make it possible to extract
    context-sensitive values from their context with `extract`.
    In contrast, Monads make it possible to wrap raw values into
    a given context with `lift` (from Applicative).

    Secondly, Comonads make it possible to apply context-sensitive values
    to functions accepting those, and to return the result as a
    context-sensitive value using `extend`. In contrast, Monads make
    it possible to apply a monadic value to a function accepting a normal
    value and returning a monadic value, and to return the result as a
    monadic value (with `chain`).

    Finally, Comonads make it possible to wrap a context-sensitive value
    into an extra layer of context using `duplicate`, while Monads make
    it possible to take a value with an extra layer of context and to
    strip it with `flatten`.

    Whereas `lift`, `chain` and `flatten` from Applicative and Monad have
    signatures
    \f{align*}{
        \mathtt{lift}_M &: T \to M(T) \\
        \mathtt{chain} &: M(T) \times (T \to M(U)) \to M(U) \\
        \mathtt{flatten} &: M(M(T)) \to M(T)
    \f}

    `extract`, `extend` and `duplicate` from Comonad have signatures
    \f{align*}{
        \mathtt{extract} &: W(T) \to T \\
        \mathtt{extend} &: W(T) \times (W(T) \to U) \to W(U) \\
        \mathtt{duplicate} &: W(T) \to W(W(T))
    \f}

    Notice how the "arrows" are reversed. This symmetry is essentially
    what we mean by Comonad being the _dual_ of Monad.

    @note
    The [Typeclassopedia][1] is a nice Haskell-oriented resource for further
    reading about Comonads.


    Minimal complete definition
    ---------------------------
    `extract` and (`extend` or `duplicate`) satisfying the laws below.
    A `Comonad` must also be a `Functor`.


    Laws
    ----
    For all Comonads `w`, the following laws must be satisfied:
    @code
        extract(duplicate(w)) == w
        transform(duplicate(w), extract) == w
        duplicate(duplicate(w)) == transform(duplicate(w), duplicate)
    @endcode

    @note
    There are several equivalent ways of defining Comonads, and this one
    is just one that was picked arbitrarily for simplicity.


    Refined concept
    ---------------
    1. Functor\n
    Every Comonad is also required to be a Functor. At first, one might think
    that it should instead be some imaginary concept CoFunctor. However, it
    turns out that a CoFunctor is the same as a `Functor`, hence the
    requirement that a `Comonad` also is a `Functor`.


    Concrete models
    ---------------
    `hana::lazy`

    [1]: https://wiki.haskell.org/Typeclassopedia#Comonad

    */
    template <typename W>
    struct Comonad;
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONCEPT_COMONAD_HPP

/* comonad.hpp
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
*/