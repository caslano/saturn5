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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_COMONAD_HPP

/* comonad.hpp
rtZwZ6QGzDx0c+Jhi0Hjk1uf6QHzPohcjZItqZo+ZGCnRLoLC1SFopOSryM5XwfpZoE6k0EVaVAzp32PPtDn5UPMri23QpE2W6GI+BVL5rzVDQfd3wXnrXoZ1Z1qq+4FJP/czDiCY26QJiPMESVP1fSm0ViSX+Nhj8nRquTLKIQYpxmpKnL2sJW93cs323s1veb8Im7/KekphObT+e9mq/1J0FPSLe43pqdbpXKadx+y0qBvLJ/yQeoKV3X79rvBWWiPvkZfW3ssAOiVGnS7mmNAqjk4d7nM/b2sxNJhVRqvpdLJ7ubrUuxdQZJtb1ZaXPvhxLDJ0dCK7QLrd9du7UG/Hfo+8YEHAOWWoADku9tvHLffzbbuq6H7Pw/aqCS6LxPdd0eq+zhN4EGr+2jbaP9FuG2z2zOeK1F+f2NvqnxW3QH4rQ+0RmGA4Uh1lE52LSfTWGTrn8TA1/7+s/Dh9viLrT3iKKXwgbbt8WmqPTiN9wdhosufze2RmxrPxsuyovduatseean20MnWbbJj4eXSMQQO2g66fIPrP9w2n2qp/pva1n9kqnBO402VLEt1taf/53J5J9nKWwhYv72/bXmnpMrjNDfe/31qqsuLc3lzbOUtIv83+ykvliqP0+R/v/Ik/9rqPOUUrPjKcgZ5hAMzwwpY4Liy2Pp9c3rBMyxpTzfLFtNBC80mfcveFazS/vQniWf5go8fnnfpu54mHf5zRyyF+0lEDvztPtzQ/LXfGJye4pgupPXvPouHNrMSi/JIHjIkNT84jS+VJmIcnVraRPeG3TZD0cdYMaM529t2djirjtjVPM1EZxtFKUo25lamZD+Ab9b9X8b9f7kN/6XU//e27f8fpeY3p8m/94fQOy3/nTABZxgDjBdtBO9hOXNfvKeNTKmr8VoKieZh9iIh1HhJmug/Sn6KI5enlA/etrKdo8FfcI8+WWwnR3YA/P3Gg7YGXAzoPdoi3894NIU8J/pkY2pd3X9djlR1qV5m3U01GlJ1YSi3b/xBFWk1Hkp5PCy3VWcZrX8b246HlanacJrAxu9D7+R98IhZYJ63CFeEDjVqbSR+reyi3/9KQ8TVaZAB6IKhMfkIz206LwPr0mt0ybPzv6AZH50USr7G/AvSGhenaJUGtkIDa99FbNkekup0rMNHkwFeXO62vnM8pARN63nwOUnItP8O0fIGS7/ynbta6lfiVPZHq/nWO/z1F2yjXVDty3JTVj2FjP+LxU9oOWhBFNunoLiiQd956UfJK6zkUbG1nt/NBjJhxl7Xo+KXqbCDN4jmr3phYyR1qSdmxxxVopApnbc1a2bdRzs7uVClr8gm3Wsn0lu615URc6GXNwWZ8nDryPWkeO2sr3VKorcjNsdYzMJR3Ma8iWsHeHwBO3Y2x0TFcA73fk8i2FL+GCtiYLGAuOAxG4GOjZTBo43fykFUerddHALBsIs3hW4nP9jCg7gbA01uAY+MjW+Vfy86OVbOgRGxhLWjAn8fEafxk1iE4eZOLJqVFm9zU2RzJdt/Bk9asAWnDeNoGNJNvcmkQYgfnbpOMcNpuLiH6AkUjWepeubQsw49jt84/IrUzb6AdbuPqIA3Psi4AQlRH55pj8pK9r7LplFX2UAz3aDmNtDcvaCl0z0YFofxwZVr5jSZBkqe2+J0lDzPdK4t8dZMG13y3PydxfGcRTU9xWUJug/ImC8iAfimDGn7YSdVSWQ+p1S6MTeDZCzTeMhC6QKN0so7pdbYhUQX7miL8mzEM8oaIXPGLFw2zwdWtcULXPELzLHeJLBJ5leFxbQN+tznVBi7i9bROVLgdjT0y+ZJ7t27zJCLrgjMkwbFS/7qqfjrCa9s92w=
*/