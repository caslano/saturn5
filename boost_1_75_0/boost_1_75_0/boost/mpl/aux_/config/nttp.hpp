
#ifndef BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// MSVC 6.5 ICE-s on the code as simple as this (see "aux_/nttp_decl.hpp"
// for a workaround):
//
//    namespace std {
//    template< typename Char > struct string;
//    }
//
//    void foo(std::string<char>);
//
//    namespace boost { namespace mpl {
//    template< int > struct arg;
//    }}

#if    !defined(BOOST_MPL_CFG_NTTP_BUG) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(BOOST_MSVC, < 1300)

#   define BOOST_MPL_CFG_NTTP_BUG

#endif

#endif // BOOST_MPL_AUX_CONFIG_NTTP_HPP_INCLUDED

/* nttp.hpp
aOtIM6hFYrPlo3UWXlrWNdHRzsrOYUZBnxHxrORjMqgYZVOnt1hbW6N0TfyiS4fFEy2tREkRIVNAzsnYaEjr/m/dizj4dAHPNF0mKSlSlxZ5QogbSGjWN8+RDWonDsd6TXp12ht+fi8dsSwHWjWolSfqiY2/I8RXsvKG1YrdisuwcKBCQRbN5G8+Voad6gUJ0YMHZmpdUpvUeNyC0I6XGGPIqM/O3Ph/ltuK4ni2IHpgoHFVd5VRXf0rU2x8VM1nWrhWWzrl3jRsUrSN6giYtcRfaCU3MXM2qlXwMcPTL35Vffk1Wi30E9lEVQLZn6Ij+7FstVsMWRERE2VkxpM0IukoU242f0wqpkpVwzl7rwuye0H2hKbXplkNO+wcXvyT0zTX5vMuxMuVkuGribMmI9Ofdsrlvv5g/nAR6Sjh8tnBXQJNLzsbyMj0urHBjYt72OolqRRbW1oKrKmpAwAomapUmXk8PVMtLayGhnuTJRJzmBWUppQUK9mYoRSccZA+Pb1941IWpmth5ddLzZjtPRpy3Ln4l2L2ClV6Dmxsdz7iejMEPTm5QpDNxVyRHDx6KanIJDIiZkTkX1SU+7uyBjc4U26+yRJz5Qm8oxT7lXKqhnzBIrwi3Ya0RO0uBSETwsEXhuICAE1yPpakL5SUWZX2n0zTppU0wqvKqCVVaehCAQM8QUdo3gDSP+tMK6Ghq0qDp4UIw1jRDGhd
*/