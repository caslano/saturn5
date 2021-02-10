/*!
@file
Defines `boost::hana::always`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ALWAYS_HPP
#define BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/create.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! Return a constant function returning `x` regardless of the
    //! argument(s) it is invoked with.
    //!
    //! Specifically, `always(x)` is a function such that
    //! @code
    //!     always(x)(y...) == x
    //! @endcode
    //! for any `y...`. A copy of `x` is made and it is owned by the
    //! `always(x)` function. When `always(x)` is called, it will return
    //! a reference to the `x` it owns. This reference is valid as long
    //! as `always(x)` is in scope.
    //!
    //!
    //! ### Example
    //! @include example/functional/always.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto always = [](auto&& x) {
        return [perfect-capture](auto const& ...y) -> decltype(auto) {
            return forwarded(x);
        };
    };
#else
    template <typename T>
    struct _always {
        T val_;

        template <typename ...Args>
        constexpr T const& operator()(Args const& ...) const&
        { return val_; }

        template <typename ...Args>
        constexpr T& operator()(Args const& ...) &
        { return val_; }

        template <typename ...Args>
        constexpr T operator()(Args const& ...) &&
        { return std::move(val_); }
    };

    constexpr detail::create<_always> always{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ALWAYS_HPP

/* always.hpp
LWA9vDJPhq6xiB8qlgyJuXrmjB+EByAm5+CEGdtYeJtKC42TC8inr1Sor+qGLNVkmoSD0duP7wbj8ej8omP42CEHLnXIy02rDJIl606Q9aKl7j4wMDN5HYyu1Greo5f4lUigg7x6PxcI5r309raliX9Q6vVYGe94fPwzXqN4iz67+9SN9Nq7+1bE8iEPdIqbCfR156U53lzq6Wj0b+bH7Fzp/GDgy46qffs0FCzfOcOHjL3BgUdR6eTRZZEGh9FiGXipN3vFcYJofN7cDykEkQIvIndCAd6Ek9xVta2XL570NcmD75voPu/DAcUdw/MIuzs8xV0zg7UXNWH9DLqkhZ7T3FyBHwvVaMzMFl69NDPnF/WNKQYoZQpyiFDxRCTbYljTjIK7jnvlSiXdaKqMb5clGc2m/0zENSGC9cJpfLdMnccwyfzNnEcmD4o/Rk56I7T5lYQkFuGx2aalu6PbAzOPjw+4Sbpf5Qf7pe1aChWbFoVaNK9BrxrWQKIGobPNM5pOV3HcrJW37kzbaErbuHRn5LBuxLC5xbi5Id1j9Bo2N8SeRmXNhBx9N7ijwxUqehW7y2uQCHhk9S3abyP2+5arai8tbBRgIN5HMMqFF7vBwXsQakq6ewRbF5+1uXyP3pO1nAN/Pve9rfde
*/