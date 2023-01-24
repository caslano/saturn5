/*!
@file
Forward declares `boost::hana::length`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LENGTH_HPP
#define BOOST_HANA_FWD_LENGTH_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the number of elements in a foldable structure.
    //! @ingroup group-Foldable
    //!
    //! Given a `Foldable` `xs`, `length(xs)` must return an object of an
    //! unsigned integral type, or an `IntegralConstant` holding such an
    //! object, which represents the number of elements in the structure.
    //!
    //! @note
    //! Since only compile-time `Foldable`s are supported in the library
    //! right now, `length` must always return an `IntegralConstant`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/length.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto length = [](auto const& xs) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct length_impl : length_impl<T, when<true>> { };

    struct length_t {
        template <typename Xs>
        constexpr auto operator()(Xs const& xs) const;
    };

    constexpr length_t length{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LENGTH_HPP

/* length.hpp
83Op6o3ymdyB44FhHOy46o5L8E78XrYFq8PNfy5nbzKKI3hz7awpYGMTizPUNKar2jbORbAn1lh0q8KPxn3/rDPhY59hDVETPROBtfGn2u4+RIkEMhVM6tJoBj9W5B01HtM3BjY8gYi1/qDLaY8kqcCa9+gWa0ly7dwEKs+JV5l1fX4Dh328eVxw19hQ3539BckX2X3KhqlVe9cC9saMoZVCzSWQCDbNjWDuNf9h/p5bRAequTmB6BiR+fckz4LOfs5vNTG7g7LXafH0ZwwbrThqX1Az96S8fvnHtQ0HDq+77s1BZz8ekj8bnSrkvIYBaEwEaLrOr+hdGHLekDWGSownXP5jZuDxi3+NFAHjyGzyWMnu38u8yzeB9rnd3wkYUwPdGHKIJswNBGYJjpgtzlEO3NWEmcQwYju/2Q5YulhzWm9iwo4CKRr1Ppq/NyMOCZuCd7z1ZJpX6unEB3RTvFyRHR6bIXjvPB0uKyy8EpEOuARMqLp/i1mZMBDSehDXJicL/Y51oZ/ug9Ih058h26t93jsHUG2TdPPuVFn2zlid6J6ovj9QP5w+8jZCEluRgv4arkM1n8XRhLCeYZ5GnbF0oAsm7U0AsfMGp9wOfFSGHO0znVshG1aHY/Lr0m41+2E+vQhTyZqBTQNfPiaBhCqrkhXdFxB44KCPyv1rfCDduV/iAwX/nrVHXac2af/O9N39E93D8GvII1bf
*/