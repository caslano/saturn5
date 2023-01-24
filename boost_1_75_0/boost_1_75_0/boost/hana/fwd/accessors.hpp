/*!
@file
Forward declares `boost::hana::accessors`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ACCESSORS_HPP
#define BOOST_HANA_FWD_ACCESSORS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Sequence` of pairs representing the accessors of the
    //! data structure.
    //! @ingroup group-Struct
    //!
    //! Given a `Struct` `S`, `accessors<S>()` is a `Sequence` of `Product`s
    //! where the first element of each pair is the "name" of a member of
    //! the `Struct`, and the second element of each pair is a function that
    //! can be used to access that member when given an object of the proper
    //! data type. As described in the global documentation for `Struct`, the
    //! accessor functions in this sequence must be move-independent.
    //!
    //!
    //! Example
    //! -------
    //! @include example/accessors.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename S>
    constexpr auto accessors = []() {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct accessors_impl : accessors_impl<S, when<true>> { };

    template <typename S>
    struct accessors_t;

    template <typename S>
    constexpr accessors_t<S> accessors{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ACCESSORS_HPP

/* accessors.hpp
w9GYSP1UIrVnVOq+aeS1HRj93SIYnG3KIcDu5CFAJc4I/II7paO29TgDYFUwTtP+nQVltAjuGsKK+pjYTJW2iI1V3D0EyZLVefmADrXDPZWm0bRMhYcve67G5q0N4w4kUk6sMjsbfWYIH3zcOzex7DSj89YPsNgIFurldWdVaDenodubaUGbtRztAfjv9UrbonTugLuOfEGGECGsYW1aMvtzNMUFbmC02xmJYAavFBb59mK+gnP4mgQEa6TJbAthvN/L70gUv9WAJpL386J00bOhk6CTntcQiKZlMLqLIYAxnb3Dl4n4CqQELGDQLC/OLLTLf6ZdhboUYPgMydRY/wnkiKWVauDitYm0Nyk12JYIGQIhZbNmWMN9DOIkLrBCIMr2h15781ty5bEVf6Tw6+JQBdGHmfF15ezDxb/6EoGhg53XaQv7TXpu/Vb4xfwAhMgKWPZQcMtkrVhzBh8N7UQ8QHi2d0Qi78CrzwhzN061RMd36FlJzx2IcP+zNAKEc1Eo3fJOoi4uGARHipZPD8V11nB/SAAt0NutzsuYVpBQAEQCHDepTTAYkrd8rCNu4HeaVQ6Qdaj4DYyCl/rYNtH0yKg+FDG8Hh4mIQ9mvWvpWzna+LkIzbZHRYDLReldLszRKjB4XCsaYcIZtRF+o6NGCA72ohenRqXZnmpW49dS/GPW8E04JxxKFabR1VF4IFZfA9Mq2y/TOYKX
*/