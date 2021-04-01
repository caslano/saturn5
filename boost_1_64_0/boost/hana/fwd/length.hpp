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
o/xkGyVUxj4sg2StMkWyUKMFIhHqxCp9Y5B4cOdPusBhJCF+NhIZ2ya0xlsk1mUJusIrpbF36GW+rKljSFGDdDrlAxRd0oeBGDPYpXukPK1LlRKCMhpvbjmnkYe4T/5sSotZYYyxXcjz7dheNE7bwoiyvGUZRf+kIdotdjqdRJYXqMREkXbNC0/NyGbtLh+pmQ3F0rb67bY6opNp1N4OdBoBX3Ca7a6MqPEZF6feJrvThJOdij6ElUfubjSxbZRYrOsXZ/l1/X0HWgwW9suJ3l6m2iTYvKgfaV5cKbZJGovCd6jf+0uNR3T3CESGpKFBb7Ngi6RKVFkh9ALKDQtP0PhWzlYK4d/FKUjtqQH9GnyO4EasgVdBWZUnOBSECQaGPuUp07EPW5/X9eju0q0QFaW8jEWxH41JRTXjrG2CC9bzNzIaqrYj7lQ4bulj8M4CEp1gho4Jy/mj7DrvoMDYAU6eq75VwQDpyMsUvi4jnBodOLDkaAFAJEJ2CfN75augnFkFGsWfrzIcj+S45KglbeWLYAlcO/MuHoghYsIAP7Ek55jB6FO1D8yxiA==
*/