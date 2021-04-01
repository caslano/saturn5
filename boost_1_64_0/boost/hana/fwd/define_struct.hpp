/*!
@file
Documents the `BOOST_HANA_DEFINE_STRUCT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DEFINE_STRUCT_HPP
#define BOOST_HANA_FWD_DEFINE_STRUCT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note:
    // The weird definition as a variable seems to exploit a glitch in Doxygen
    // which makes the macro appear in the related objects of Struct (as we
    // want it to).

    //! Defines members of a structure, while at the same time
    //! modeling `Struct`.
    //! @ingroup group-Struct
    //!
    //! Using this macro in the body of a user-defined type will define the
    //! given members inside that type, and will also provide a model of the
    //! `Struct` concept for that user-defined type. This macro is often the
    //! easiest way to define a model of the `Struct` concept.
    //!
    //! @note
    //! This macro only works if the tag of the user-defined type `T` is `T`
    //! itself. This is the case unless you specifically asked for something
    //! different; see `tag_of`'s documentation.
    //!
    //!
    //! Example
    //! -------
    //! @include example/define_struct.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_DEFINE_STRUCT(...) = ;
    #define BOOST_HANA_DEFINE_STRUCT(Name, ...) see documentation
#else
    // defined in <boost/hana/define_struct.hpp>
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DEFINE_STRUCT_HPP

/* define_struct.hpp
nWAMcyY5u++hoNDe+qd6uJIMAyh8PFe71qBrHr+Htl51HkUMnU16TufGqXJkL4dtOonSmWXDkEVJY9LwTdkcNzurpkih0Njt0T9gWWNu2xhOtxklnoId/rqKPcqAS7OdgJHnM9Zfk7QfgHYDKPDDnQ/n9fEPHBT+rNlaLiTlk8GMpN2JB9AAmh4A84f7frsF8OW21Ev1TqQOo+h82wG71NxRjthQ27fIV2JRFn16jE4tMZ4u0vvnslMeszhBu/tPSdyQU70Ft7+yD/SnTqwvIdtoYuYvs8Tn6Hs3mv7N+x/jmXAUjB9iFs3Zt8U7uSojj8cOc9f/S5hSQQqN2tiQOnWweqOumGLxC8YxHORMJi5FBnfgDc0BMics0nVFbDOZhNp8l7ZYsLDIfmBiYuhlkZeWoWP92CfFRoHW8ZDJtB9ifCWzlPalGlB4SvOlXDPYgiX1b7zZUjGZle/Mk5D4dpUBWm9AMkrDT44xPqTyKERx7iFUbXk2ocOYd4uwxGT29B4qDwRDw6xp/BLR5dQ1qQNAPj36Nd+OvwWihkHFR2wUK+2QlZHHTKHpqQ==
*/