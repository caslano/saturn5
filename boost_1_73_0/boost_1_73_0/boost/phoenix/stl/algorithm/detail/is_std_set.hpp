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
fRD5wzQLs6SPKiiYjZIsi9Mspey3WKyNvhL40wMUxwle4oES9IvBBptWeqyO3H6N+6fptO/T7af53v4frVaAm0OU9HhRadgBmM5GPuYd2Ov9Rqfv4YiWjdUhsoajvbhEij4FP6FsDdvqTeLpoPd0MHY36p1a4unm5F3nr6L62w+b41kyiPKHTJWmV0A+mY5PpuFwVT06JUHaWl2mJzrrtvsOUEsDBAoAAAAIAC1nSlLVPg6ChwQAAEcTAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC9NYWtlZmlsZS5pbmNVVAUAAbZIJGCtl21v4jgQx9/zKUbbfdGeOCChNvi0eypH2120LFSFalWpUhQS0/guJChO+iD1w984YGDldfGLTQUZjOc3Y48nf3ryx++7Gidw9ArqV4AX3pXDTZH/y6Py15OD4A02f+j0gPcjIdqw93gLzuCoxxuc1h7BNsYnZQfBkTAPKjH11laOD4EycaRxgn7DfP1aiMekhNPhGXiM9eFP8Dt+pwmXYSZ4CrOSZwtePDbhU1yPXCThy0tL8r+bwEsI01YNmidCgsyX5XNYcEA7FRHPJI8hlBBzGRVigR9EBmXCYSlSDsPpzf1o8qUJz4mIEmS85hXIJK/SGJLwiUPBIy6eNoh1
*/