/*!
@file
Forward declares `boost::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCEPT_RING_HPP
#define BOOST_HANA_FWD_CONCEPT_RING_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-concepts
    //! @defgroup group-Ring Ring
    //! The `Ring` concept represents `Group`s that also form a `Monoid`
    //! under a second binary operation that distributes over the first.
    //!
    //! A [Ring][1] is an algebraic structure built on top of a `Group`
    //! which requires a monoidal structure with respect to a second binary
    //! operation. This second binary operation must distribute over the
    //! first one. Specifically, a `Ring` is a triple `(S, +, *)` such that
    //! `(S, +)` is a `Group`, `(S, *)` is a `Monoid` and `*` distributes
    //! over `+`, i.e.
    //! @code
    //!     x * (y + z) == (x * y) + (x * z)
    //! @endcode
    //!
    //! The second binary operation is often written `*` with its identity
    //! written `1`, in reference to the `Ring` of integers under
    //! multiplication. The method names used here refer to this exact ring.
    //!
    //!
    //! Minimal complete definintion
    //! ----------------------------
    //! `one` and `mult` satisfying the laws
    //!
    //!
    //! Laws
    //! ----
    //! For all objects `x`, `y`, `z` of a `Ring` `R`, the following laws must
    //! be satisfied:
    //! @code
    //!     mult(x, mult(y, z)) == mult(mult(x, y), z)          // associativity
    //!     mult(x, one<R>()) == x                              // right identity
    //!     mult(one<R>(), x) == x                              // left identity
    //!     mult(x, plus(y, z)) == plus(mult(x, y), mult(x, z)) // distributivity
    //! @endcode
    //!
    //!
    //! Refined concepts
    //! ----------------
    //! `Monoid`, `Group`
    //!
    //!
    //! Concrete models
    //! ---------------
    //! `hana::integral_constant`
    //!
    //!
    //! Free model for non-boolean arithmetic data types
    //! ------------------------------------------------
    //! A data type `T` is arithmetic if `std::is_arithmetic<T>::%value` is
    //! true. For a non-boolean arithmetic data type `T`, a model of `Ring` is
    //! automatically defined by using the provided `Group` model and setting
    //! @code
    //!     mult(x, y) = (x * y)
    //!     one<T>() = static_cast<T>(1)
    //! @endcode
    //!
    //! @note
    //! The rationale for not providing a Ring model for `bool` is the same
    //! as for not providing Monoid and Group models.
    //!
    //!
    //! Structure-preserving functions
    //! ------------------------------
    //! Let `A` and `B` be two `Ring`s. A function `f : A -> B` is said to
    //! be a [Ring morphism][2] if it preserves the ring structure between
    //! `A` and `B`. Rigorously, for all objects `x, y` of data type `A`,
    //! @code
    //!     f(plus(x, y)) == plus(f(x), f(y))
    //!     f(mult(x, y)) == mult(f(x), f(y))
    //!     f(one<A>()) == one<B>()
    //! @endcode
    //! Because of the `Ring` structure, it is easy to prove that the
    //! following will then also be satisfied:
    //! @code
    //!     f(zero<A>()) == zero<B>()
    //!     f(negate(x)) == negate(f(x))
    //! @endcode
    //! which is to say that `f` will then also be a `Group` morphism.
    //! Functions with these properties interact nicely with `Ring`s,
    //! which is why they are given such a special treatment.
    //!
    //!
    //! [1]: http://en.wikipedia.org/wiki/Ring_(mathematics)
    //! [2]: http://en.wikipedia.org/wiki/Ring_homomorphism
    template <typename R>
    struct Ring;
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCEPT_RING_HPP

/* ring.hpp
7HdxurskREZUw6/vh2ne8t/RibqxWpUhIRscJx9L3MJbQhdDUral5OTy3FT/hwlSIJXNuXogKwbF1i8L0mopdjaZhXuW5tOL2dzCoCwY6Jp5q+jxILy2rXGQWP+lOWgsCPkH76kre4lqz4qN8RdUWaIrX5pDBVm9VtZvGX+yKEyGVMlEibxbMnocX+W1XaX2idkyHQUdociu2QdmsEXRcioMd4zy5wilurxsa1Ue46n3h2Bn/yyrKtHZ4qtX1PYcR8nm1zxOwC5KE8Wjd6CnIi+RHYEI11RLew496jyWb639ii7Q6//ObwEEH6tSFH/AONTTJljzAe//IWyZ7fwuzszXImXpW+BF1mU+42vIVqbv5NuzXk4XbPpbWl4r0L7VNpwURYOu+ybFV/o5ufhG8avuRNeEyy12PqhcL67irOF2sRnDUFftnfKydFJrXFftGul/mvpwtkc8sEKZhqcTVQX+l+GPAeGnsHkyTJMWqknXxY2gdP9GPe1EGa5Lg9OwsTYEGrseuCc4hqyDt8sz9w1kSpd7w8Pj82+j8VkoeiKhthnmXuLtbZUPimZtDJ0d3mebfobWE+ZKMYMm7lgcOLcw+hf9fvbyC/clvpO1brq9fNC+xA0bLOfmwb51+KBt5kdjtYXpH1u47TI3iSiWkqWvfXAk6qaH/TB94L0s/+IFoJIpRN7s20zy41T4hJIyK3Thdgq2adPgdZKlVrcUbhfTQLOWOeEpd4pIUdw20iO8NQxGq5UpRO0z+sEUEuCPY3h5tsMcdRhOTkx8oB5rqctnraUur18tNdRb+iW61ZwbWo0Ib64dqo1Zmx3hWHVla5luVA1ey0MJ9OMzq0E/1jL9KH5Rpx/4lI9WWYV0+sfoFugS6vhNua/l+DHF5JgKN9Rfd2K6wKGnaUvX0niEmdY2VZbHgWykXc1REadWtjabhrtVlaux8jz8wm9SnkbKt/jef1X5pAHs0HnNlfPVNYcsp7aQw7Bx1LHKQvb7AddNOhERu1bJETDTRcikYjKiUspIG63ySGso/jGNqmc/qDeq+JyfPpzEUlrMHH2JG/pb30mvnAh/ihee5HQtU+vyZ2vIz04Qc835uYz8/G4KPOGhGM/l9d+i5kP/fNSv+PH9mI5jFz3B1w8yNKkKja13pQrNyrcJ4nFkxg4fK32ktgxbRX82vx1Hf+a/3xL6Y7Eo+vPDi43Sn/e/iKc/U5749fTHhOXf32usPf3j3WzzZlobVOmcLuy+mtwCuvuon9Fwizw7PLoPZ48L4AEtpRYeLxBfoTegEayVuianXSQzAHvjAMTf/4S23KiV8mgtpdHKaGafJEdqfnhjLUZpaXYTWYsHKP18Tj3fSJ3j9ZXukgDOD79Rm0OaRtqY+dnoL70wmJwYSieDA5jPozsaaluVRKNbq4ycS9xJZKC2cD6P8Da4b6OyWXZFnCDxX8IYLDEwyAUGf5cYXBB+szZXG0wYLMlG859GyqjA5ARgsETHQNGXgaAvfbWyJZx7UhFSpbLl3ZVL5sgTrR0MCuFCQOdIb60SGOMVhEcdEYglTCDaAvHD4bOM8oz6I8rDNdkPtaqXRhs8Hw3QePkbi++lymZV+d+6xsWzd8r65hyXmDBMt3mpgn3/2TUM0yx/4OlpHhdgHhUAF2wAoNT3qLPNs8oLH6ps82iCQESeneZl61/ML8yT881p/l9i6wzmv8UIbMfKWDzrsKcJDlLW97BY63lQ1UTpWcRgeAqlCuRwXvKYkZ97PmKafHSdmHD6vIMtkhgd3gOba3dw/TFuOfGjnLOPcAh43WPiaEiEAzW66M62iIsL2de6nSmlu4jVP2ojcQKS/9+Vgi8uT2TYvGyZESs=
*/