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
// is_std_list.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_LIST_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_LIST_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <list>

namespace boost
{
    template<class T>
    struct is_std_list
        : boost::mpl::false_
    {};

    template<
        class Ty
      , class Alloc
    >
    struct is_std_list< ::std::list<Ty,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_list.hpp
KMX3NHDrUfBgZfOs/1GPAph4LqQ/jGTW279fImp8dXJV6useVqK8yZCFTNyp994JS/pWv4QdENnL20Patd125LqB/u/0rDtbsv3wUYoT7MHLmyqMfJ/dNR+zIUlbXGyYs/wqxiJx6+Dj+P02qH3IndXd09Ct9Ps8oLjrRr21xvXExM0PlNIdL5viScrgKOX+q327M/lmV4cnIUlT2wp09bcuVNQuylQtuQZAvbi5VBr+xMoCDktbzuL4GqpV0MJ4wnZTvMR6tZ1lVJu5UukVz+/gGOPQodN0tX8PIyFxsvLpDlr41L1EYUyq4Zl4t0YvN5HPgMJNUcnrzgverpoZoqqyjPxYpPn8sMkcyjUV3BPORDMPmTCIckXs5J0gUmmWXwY6+DU0QNakIW2PD5oaGDYge4VlgxpIRTRgoOIY6WZSThCTT/oI+eHV4Fu95kKMBCSIXcz6NGFPuziNuborEEZ09yevwOhikXssKheXaX1yJKZMH4CqSw1xxYlUQ/+aDLKb+w1u5VCvZroqqTYTUOKFCsolDUEUFKBBBinfDpc6xjz5qzQ3Ant32A==
*/