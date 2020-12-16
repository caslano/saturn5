/*!
@file
Forward declares `boost::hana::default_` and `boost::hana::is_default`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_DEFAULT_HPP
#define BOOST_HANA_FWD_CORE_DEFAULT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-core
    //! Mark a tag-dispatched method implementation as a default implementation.
    //!
    //! When defining a new concept with tag-dispatched methods, it is
    //! sometimes possible to provide a default implementation for some
    //! method(s). Making `default_` a base class of such a default
    //! implementation makes it possible to detect whether the method
    //! was dispatched to the default implementation afterwards.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/default.cpp
    struct default_ { };

    //! @ingroup group-core
    //! Returns whether a tag-dispatched method implementation is a default
    //! implementation.
    //!
    //! Given a tag-dispatched method implementation `method_impl<T...>`,
    //! `is_default<method_impl<T...>>` returns whether `method_impl<T...>`
    //! is a default implementation. Note that if there is no default
    //! implementation for the method, then `is_default` should not be
    //! used unless a static assertion saying that "the method is not
    //! implemented" is acceptable.
    //!
    //!
    //! Example
    //! -------
    //! @include example/core/default.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename Method>
    struct is_default { see documentation };
#else
    template <typename T, typename = void>
    struct is_default;
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CORE_DEFAULT_HPP

/* default.hpp
4ny/dX5+gjm3+v379Nvi+jer2lziw3q2ahpXUwm2fVZi1Ht4XX/yErk0rL2Mqqw8pUuGj6yiUk/OetexsDNKzHQBiSYtN7psF3hLDtOrOMznd9otcr1/EmZ2sJeBPv7e+0BidGNPvPXzaWwIFIpXlhnw3qLefq2NBgBYy4vSE98J77ZNbWceAPDAAIjuD/bRB0D0QPBUYwBEDwbdxgDAHObQB0BrvuusJiGzojwlIzKcyMSgSF6aloS7uDoSN9OQ+0G5Tk2SA0afH2Pjpt3tsnezyLvh+Ph+KQczV3rZgoaD472l/7rB0fBR8u8lUj7Arfbc9cbQub9E9gm3aH+LnPQ/vgSBbYn/EOUpN5TupU2W4pu4O6R6xRjVfMFp6FyvSaUD8IJXaUmF4QpUa4FH3P83OxYN/AVZS8oBdIyBer/wik8ZQBoAnGkeeCvuU3C7WAdizMmhl2aub176Mwv6I0T3qoZ/teadWHIbUY9HxtZFxfGTyXkPOQvZeSs5Tx9DzpvJOflmcs4k59YF5LyenJ+xcyI5dwbJOZqc873k9JDzw1vJOYScky4j57lw+qegQvwJc+i0BFwiOCHOr4z8xk+gkg4WI4oplY1SLTRi3EkxBk6I87ub/E6DnxjC2b8L3EURZ78BTv/9RsynKaZlQpzfGvL7+kok+XQ6JbmNef1s8RF/zSUAFUbkTRT51Svj/D4mv8cIwJ5JlGQUJfnaCN5DwQsRbPKz74ffDEqSp1GSbpTEtV8F96XgS5lJyBd7R1KMA6MR+aSJ5PyenAumkfNLcuaUkfNjcs64lctPzklzufzkHMQRXoLTP9jIw0N5/HRFnN8l5LcLfiKBm3Q+pR5/HTlnkfOrCDmnjpYV1I3jTCCw4w0QkwnEvVfE+aW/mOoUCwjspMWU5AyC5b6HnCeT07WEnF3I2ZUjOMl5Kdd/K3Lews5fLgPUoAF1DuXU5wrGxeRdRt5d4W3ym09+yeS31PB7kMt/OfweN/xe5vLDT/S7hsuPHMWIMVx+ch7HvlPJeTY7r75MZv+aAWITlx8gTH5byG9BvN8H5Dedstq1kCB1JaDX8fhrT85ui8jZmpx/4S6y/1Kk32mk/5rSn305Z2/y/pG8u8Hb5Lef/I6K97MfgN/P4wF9RwFBvxfQxffsvI2cd13H5Sfnk+VcfnK+zM6p5FxewOUn52s+co65VPaKHzhgOAUMZOcgci7hOH3JuZZ9e5JzFBfyBCpZ6gGFWndCbQyhljWVghMpuK8RnE/BA8bH+XnI71RK0o3z2XKJxKUjf63Hl4hyK64m5+fcix8nZwITsWXkfPtict7BEdipkXMkQ5hDzofZN0TOruwbIOfVXCVFcPovMfCZTPj8sQjBd3MJsyl4phG8kIJvLGIqZ/JeSt5XUio/V1EbxpspWrQQzpsZ1o/kfLqInNXkfI+df4OT5e2wr0FOL0PYSM7tDOEVck7gCM+Sc/Zycj5Mzjc4wt3k/Poici6B03+3gdfThNdb4yQ1+pOHYlxHMSqMGFsoxqPj4vy2kd/t8BMVAUrSn+Cn3cXjn5x9GdDJ5DxjGI9/cg7hucZJzmPZ2Yqc6aN5/Puoy8wj525ylrDzM59s6wEcfauPurmBxI+EhHNcnJ/tIPz2jyXEmEQuJ1gvsvNOcn58PTnLybmTfX9PzhTOrJjjsnMy5ZR60Oi1BHXFWMbF5N2XvG+hzLpwqrMJwGh2ZpBzJdO7NHLOu5ScHeDEaOT2J2ebcm7/AmSWb0AdQ1D7jY3zm0x+J1FOT3FNbCpgXGSF8aATfdn5HDlPWMjzPznfHsvzP5z/yRoN/3/+lY94/z4mJUSB/srOjUzCqLdZefKFS6ym2ek=
*/