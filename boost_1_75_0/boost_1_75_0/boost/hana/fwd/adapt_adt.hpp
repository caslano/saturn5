/*!
@file
Documents the `BOOST_HANA_ADAPT_ADT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADAPT_ADT_HPP
#define BOOST_HANA_FWD_ADAPT_ADT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note:
    // The weird definition as a variable seems to exploit a glitch in Doxygen
    // which makes the macro appear in the related objects of Struct (as we
    // want it to).

    //! Defines a model of `Struct` with the given accessors.
    //! @ingroup group-Struct
    //!
    //! Using this macro at _global scope_ will define a model of the `Struct`
    //! concept for the given type. This can be used to easily adapt existing
    //! user-defined types in a ad-hoc manner. Unlike `BOOST_HANA_ADAPT_STRUCT`,
    //! this macro requires specifying the way to retrieve each member by
    //! providing a function that does the extraction.
    //!
    //! @note
    //! This macro only works if the tag of the user-defined type `T` is `T`
    //! itself. This is the case unless you specifically asked for something
    //! different; see `tag_of`'s documentation.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adapt_adt.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_ADAPT_ADT(...) = ;
    #define BOOST_HANA_ADAPT_ADT(Name, ...) see documentation
#else
    // defined in <boost/hana/adapt_adt.hpp>
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADAPT_ADT_HPP

/* adapt_adt.hpp
e7rUzLfpRHFV3wP9yXQg2kUN/khUXE5Bjf/tDLacOIk7IFjOEsuspRC6K0THE9j9/LI3QlKXz0AO7qrX4POtStwOzkSud3+vlv++gq7PqJL8dS2hE1ySioo4uiCEgrkyFS96oF/j9vInlPl9fe/QToyCaf0+bbKPfnlaLQ1tzceMyjkIVRyZovysRnHYjvsd5NfUxX/eQqYYWq5VeDKwUIBzc6/o8jPFt0DUxZ9sEXMQXc4S3CvGESWBQsR5wKgt4cT44+bp3+ByCvoHHdgBaw5UWFOc4MHyiGqLfqfF0ScySaGMgzkWEpgOy7Kp6ujzInWuF5PVkra8RIPoq1j226fw9UUFxrV4J3ZWiTW8Gy2STHLxEi5M1R8PjHXHslz8pxwnJOwfuAYI9JOpr4jKKSIGI3bEMwyXUumaS49h2uwf8hcXoNyBPnjFzrOqi9V7mKKLhVJeb9SiuDAUbW0YUD0LVbP8lsoOlFI+WSCMXHAp2DUtmKksV/Iy/925//PH1SPxe3ociT9uSR6JT8hLORL/CEcr5UgcVjOlXxN2A9F8r9Zl3e604X4P39FBx6epR/xzhiYODSMPNPKGu2g2VOs/EOuP/jEBg5KuaSUwcuDlwGklgEqcULGloFJ7JVQ+/FRWD1PYv2IOVti66YJAx83f7qWiU81/vECg40Z0DCo66MYbeiA6Em/sSbcrFrZCLWydowfd7uyVpFv8
*/