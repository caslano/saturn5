// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_set.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
# pragma once
#endif

#ifndef BOOST_PHOENIX_IS_STD_SET_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_SET_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <set>

namespace boost
{
    template<class T>
    struct is_std_set
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Pr
      , class Alloc
    >
    struct is_std_set< ::std::set<Kty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multiset
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Pr
      , class Alloc
    >
    struct is_std_multiset< ::std::multiset<Kty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_set.hpp
mbgd5B+VwoFWP0R+rMO+zsUFIR4dIGq5XnaiBBCyIus5C+HChTmHi7+Y/AQU/i7zFFfjXgPYwL6vBbgHIcKA5/7ObHYCE0VAB8T7zfBUI2zfTZj679MbVuf02NednTzTTBDI5BRTTS1mntTT8AayqMifMIM0CZN8/rtdJl4S3Xcb1hBXpXkS1X9b35avdyaD9az1m/J0vUwIvvWboecqHQmumGKUuOabV5zhXXCZ1Kkc59eVRaci3ZCklHj6xUtDU1puYu74a79W5yWth3QVrwWgJ2l4Rym0GUMzo9wKydfQaj0HsQw9TLFcDDrG2bfA2XiRWKHb/KJn3MsiUVkU5lFCdOCrvrF4v26zaxHsUZgaMucyR1SRKD/1meSyG31t5OtxM9NyR4jG14adOUvZdofBEnFQ4bzPDo17lawydbpJgqH0g5NfM9dOl0mqy6rC7wAXyjQcJK5VBlPqG5TcOHnmgk98srTZlJJZa4CY3uam9zXPAo1mLGVr+7OsMbjYRgGqRG/kGtd+e8hqy6m/ahauQjpKveoXBgASYEbutNsInnPZH7s+nA+/UFkWegIXKga8OL1n0S0jrqat3+myuu10N9ij18UcejR1J881BagK8+63vGOVrpuTeWOjtWQtilHXJVrayIv019anxqFuN0zy7/1vMAKi2Gxd2tzGtFNazJvKvugwqA3f+cQxiwkncfR/McL3D9IRL3FW
*/