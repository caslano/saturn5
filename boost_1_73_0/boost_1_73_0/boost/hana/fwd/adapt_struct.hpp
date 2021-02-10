/*!
@file
Documents the `BOOST_HANA_ADAPT_STRUCT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADAPT_STRUCT_HPP
#define BOOST_HANA_FWD_ADAPT_STRUCT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note:
    // The weird definition as a variable seems to exploit a glitch in Doxygen
    // which makes the macro appear in the related objects of Struct (as we
    // want it to).

    //! Defines a model of `Struct` with the given members.
    //! @ingroup group-Struct
    //!
    //! Using this macro at _global scope_ will define a model of the `Struct`
    //! concept for the given type. This can be used to easily adapt existing
    //! user-defined types in a ad-hoc manner. Unlike the
    //! `BOOST_HANA_DEFINE_STRUCT` macro, this macro does not
    //! require the types of the members to be specified.
    //!
    //! @note
    //! This macro only works if the tag of the user-defined type `T` is `T`
    //! itself. This is the case unless you specifically asked for something
    //! different; see `tag_of`'s documentation.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adapt_struct.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_ADAPT_STRUCT(...) = ;
    #define BOOST_HANA_ADAPT_STRUCT(Name, ...) see documentation
#else
    // defined in <boost/hana/adapt_struct.hpp>
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADAPT_STRUCT_HPP

/* adapt_struct.hpp
E6bIaUDOfjeQX0xYyj5HdiI7UhAjdPgYF1RwwPaxA9JY5o+4jmnKrbkqpR4JxzpRy1nEfVpO8JPGnaMQHatAytVymRdVKR5TkPzj5WX0bjy+HDEnu8FI1vBiHL3+eHY+js6GCqvaD1jmtOlH26wYkUEVoreyWEBoE5pWgWX8f2AGYWSuR5GT8i5eLuVMG/dFTHufFM1a5Lcm8lWBKVSaqBV3TWg2BlmkCGBxaq8nwmOhOriQC5gcncehKj1x2NMRsNBzJwqGOJhmAnLGgcCj+uB1VfNBKdGcfSn0CLeGzPSSZaaEG7lBsWzR3jYg1pgkTS8sMGtMbLiQJeib/tppS8K5/dxSYs+Y0ecJz3Ke0ZYuE6dlwJqEazqRk5ppPGnqyx0Nj2esMMNxs+bkYjgcnIyjwdXVxRUNIVlCxVdjBE1kwsvZnswwe2Im5kW+oOkgMNlCL3zNUcco8EsTVFyjPjyOoNrJ5HUOdhxu5isHSHHOsScU/8AuR2zXSq03eaiY4vKQsCyvi3KcLKQCHJ99GFxFx5eXiiMcSySbshRmVH0LTg/B9zXiGmV5Zmj8CaLbKsY9tnWeor36P0ek/59KNACDZi+rH5bpNXLpDntQNHvkWeh1V8knRuvVCP55QQ3J6QE5VudARGgjGlvY
*/