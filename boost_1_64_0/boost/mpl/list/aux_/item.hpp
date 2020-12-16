
#ifndef BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/long.hpp>
#include <boost/mpl/list/aux_/tag.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template<
      typename Size
    , typename T
    , typename Next
    >
struct l_item
{
// agurt, 17/jul/03: to facilitate the deficient 'is_sequence' implementation 
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    typedef int begin;
#endif
    typedef aux::list_tag tag;
    typedef l_item type;

    typedef Size size;
    typedef T item;
    typedef Next next;
};

struct l_end
{
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    typedef int begin;
#endif
    typedef aux::list_tag tag;
    typedef l_end type;
    typedef long_<0> size;
};

}}

#endif // BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED

/* item.hpp
r229fmQ5/tb1esLzirnNblMfWY6uHqft1OMn8gdb1+MJzzXmevxOPWQ5unoEu9lvjyTrejzh+UfbHrIcXT0u2qnHBfKnWNfjCc9J5npkUI+BsiBtPWLcbetxSTl+revxhOcpcz1uKvVgQdb1uONuvz3SrevxhOcuXXvIgrT1SMpnW48rfvxvqVU9nvB8Zq7HNaUesiBtDOVZqUcjOcfVI7UoxvnEVA/ri7pHnueUZbeQZfvnlzEVSa6y/KusQYws2+4FYxbW0xIr4Sg2wVEsg6NYCUcxEU9vvBz7MQKOYigcxQI4iq1wPmbBfiyJ8zEUlWcq85f2ivgkuoVn8wMnxx4b+k2zeY5iT5yP6XA2hiLzZ/zJ9wv53pFk1Vdf3EX6yLAJ+mAXLIM9sBzGYnkcgRVwFFZEiSGQ7wxsb1m+NoagtsQQ1EFvrKvJFyj58tvJ94bkm4zuOEWTLziTfK9IvljJF6fJF5NJvlDJFyb5BmvyJWWSb4zkGyv5XtXkS84k30uSr6/ke1mTLyWTfJ0l34uSr4smX2om+VpJvuclX2tNvn3afI7GiZF8jbTPdpR8LSWfNvalkuxXlbECVsUq+Cw+h9WwMdbAplhTltvYRa7r0FOWmwtryHKnSX2mYwFMxiI4Q5PfP5P8wyX/CMmfKPlHavIHZ5J/qOSPlPzDJH+UJn9SJvnHS/7XJP8EyT9Rkz8lk/xBkj9Y8hsk/0BN/n2Z5O8u+XtI/p6Sv5cmf3om+dtJ/vaSv4Pk76jm57XUcf6mkr+Z5G8u+Vtot7/kb2QnfxHZr4picfTEeugl+cuTYiR/YcmfA70kvwezvKRvrd8fPF+INPuPR/ex/T/0qT2t/rQn7Uuz/r105Fe5bPrR9rHN0kn3SVXv53PpRIokJZNSSWmkDJLXA347TepHSiKlkA6SzpNyPczn4ktqTwp/mN3Xlv3KfmW/sl/Zr+xX9iv7lf3Kfj2t11/S/x8ZMfBpPP9P6bdvoOm3T5a+8qNyP/dT0n3l95xvm+9b67udstJvn9XfG9+jnLAYF4fPSSpYi/cPNP2mPMVYH+pYS8bSl+mr8pvza5q/a2MBPKR/3JvkKt+Vr5Gn9jTL+kWGGmKDwiINg+Mefa/aet2KatZNFqHvF5Dy60r5teU3+YGa8qNjRtLnmKh0UMTHjnS+DsbfKkt5kdJPflK253HSb7RzsqY8NuMTb0P5bS5SpiF2MPBvze/GjfOytm1zTtdv21oyfV22bc/pVtvW6lmBxaVti5F2kCdluv55jRxoIRwEzrVrRLRuO7bPZb+sfVZljZDCstLPlNkzId2kf7y2/F6jBv5CeemW8kISYoIGhRsiorL2nJ/cRR4mW54JqS2bJTBteU5VaPQg87NumNb85l+m5WGU6ra0V/+1Uv+hsh8OJmUo/bYz1PqHEQhk7C1y+pxCWdrjTpah+13uMP6njRMaZoijKvpjxT+P7TPCJjxLPTV1JETIqboZrOoRQVL24ckz9fv4hzL9q/l3zVbxAAHSbq3M54tZujoFGSKdPIY1Y3fIMW31G/Aw3farn9c2PuMGdU211EMbzpTlfX23lK09tpbZKeumcmzZLyvIEJv1Y1nK07VxATfb8m5RXpq+POWn3FkuR7a9rg0nu9nGof1GOen6ckITjUU5f77QnpMjQhJ165hhu47s2/xvtq5s+mkfPcaM9Tpqt91c6X8fIPtrX9Jt1tFDW458sgUx9UTHOudgut7joqNcdM+WjTTonzkzzM4+5pbPfnsk26unqRCn2sX6/BfvoLwUfXlx4QnxIdEjnCvLYHUeay/98tdlG1yWMTlSdWXFOdfuaBmP49HjIESQ7H22l5yjP+9FyPQ=
*/