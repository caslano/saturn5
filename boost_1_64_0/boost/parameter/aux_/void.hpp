// Copyright Daniel Wallin, David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_VOID_050329_HPP
#define BOOST_PARAMETER_VOID_050329_HPP

namespace boost { namespace parameter { 

    // A placemarker for "no argument passed."
    // MAINTAINER NOTE: Do not make this into a metafunction
    struct void_
    {
    };
}} // namespace boost::parameter

namespace boost { namespace parameter { namespace aux {

    inline ::boost::parameter::void_& void_reference()
    {
        static ::boost::parameter::void_ instance;
        return instance;
    }
}}} // namespace boost::parameter::aux

#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x580))

namespace boost { namespace parameter { namespace aux {

    typedef void* voidstar;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* void.hpp
4NcTzvPptSfrcbLJ8uL3EoWNLBUmoXEuW6OrgE8pSWX7qIK5QZUdfqRIn5ydaJBxpLKoJXLCrqMYuZEpwFcu8bdo0YH18I6TkA90zLY6E09yZXPtY/jbVhs8Lgq6de1MR2tUDLeDD7Ml1wcOlM5z8/BcOeUD5vXzarSBLPvKioSe9r2HhTeAz1hVDTBPwrgQqVu4uUuPZZcNWJ7RxF0I3WvMxofL06dUr0Li/SyreyLhX4rVNPBECForMCaxyo3KcqjMyRmPFgSRW97idSqsptSBZT5oo9rnvpnilAR8pp7Dh3ZVI0wLSvLjm15t/cOSsafiXNBrH4giFWIEhDOa5NZ5L8QrF4VOAncBVWXs1pPBSTyEo4YdycKZcNCjwPsRXLwumBfQWi2ldi3qYxyp8urvxXpdCBibIm/suMdYHdDUfW3mpo3oN3BOIkiPoPFOtkCjovNKmg2KYX4U1wipGEIUjz9NyajXy/fvNzw/VfAxPO6YuwgoYl8KxoUXNbn+HdPh/oSzghSwq6oW2bbLOyVJZv46XCpLShAE/gDYovjDA77PWlJ2GZnJag==
*/