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
rhS6vdDcg265WFAcmRlkkH5EPfRmbuGPnyXKDdyt6Eh4EwTUXteDgE/f2YOAH9/Zk4BXZIErovLcsSuzwMaMJCo3pqLS8EUPVB77MskCmiQLvNd+GQvMGtIDgw/v6IFBZhIDVmgDJFAQ0atMcB6R2f/vcKlv7MkDqfi8lZ7Ep/DOFHw0CXzcLv4XbKdGqMe/J9y9KYXVXlLYnJTC2u5IKezXn/cg3kwozo6D2gA00Qok9LqIDR47czU2OD+oBxEr5qtSJSxSYHUfPhJM8/deHJuCBxzsPEwROVrJaVEnvDwLfOvj+ja0vfC5Z5HfRFqSUAc6TqazE1qVVhpw+fjAHanLR7ptyE7jVHuzl28lo2LrxrCDfEJyvXfQxX8jIvrgcRwT7zrcdFD2v+aJ5TqeWBljluTGHztofRemFT3lCH5dpCoQ2juANMM3m8vrA4Pcmwstt+0PWJUTJwwMfhfTsbZleGp36emIUD+UnPHU8z5n3IVnfgdOpZz5ifMDrF0/pXZuPGw6Pm25IeCcttwSGM2WW6CRBnnk1Qa5H1tt9lvc/O/Yrv/EvZ8gL4LJZ7mF3T02qYsXmWdTtGyl5Ybly6pDdTLt1c6vpn0Z36Ve5832I2hEG5UyTUtqw6/CEIqnsJGdW9H263Ov0/PNDnTVDBIf/FY8dwCe/PlZqKS57uGaMH5qwx2BwbF+MFWAkIkwXPwf0MEja+iwO/g1
*/