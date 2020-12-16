
#ifndef BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if !defined(BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING) \
    && ( BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 245) \
        || BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, <= 0x0295) \
        || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(600)) \
        || BOOST_WORKAROUND(__NVCC__, BOOST_TESTED_AT(1)) \
        )

#   define BOOST_MPL_CFG_USE_OPERATORS_OVERLOADING

#endif

#endif // BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

/* operators.hpp
A/1v9PvCCX+nn0bfc3m6I/xIX0Q/HU74ib6SfhWc8DP9ufTb4YRf6Jfr9oETDFP5q+m7XZLuDAAmv0t3E302nOAz1fn6dvppcIJFf7duHzjBpt9EvxROiKF/lH41nBBL/xT9Jjghjv55vV1wQjx9Df1uOCGB/k36A3BCIv179PalWEfQhP5j+lQ4oSn9fvoBcEIzts/Xer/ACUn0f6dfASck01vbuF1wgkPfhH43nNCcviX9ITihBX0H+laXpTtCS/pO9Nlw2TKPvgd9KZzQmr4//Qo4oQ39cfRb4IS29COURwWkIIV+vH5fOKEd/ST9vnBCe/oz9HZN8ztCB/p8+vgz/Y6QSj+LPhWuJ0ijr9LvCyek059DnwMn+OmX0BfACQH6y+ir4YSO9FfTL4UTjqK/kX4VnNCJ/la9f+GEzvR30dfACV3o/0S/B+4g6Er/qG6H32KcB0fTP03fDW4A6Eb/Iv1IuAmgO/1r9JPhhAz6d/R+gRN60H9EvxxO6En/Of1aOKGX7v/0W+GE3rr/6/4MJ/TR/f8ZHo9wQqbu//RNc/2O0Ff3f/qecEI/3f/pJ8AJ/XX/py+GEwbo/k+/FE4YqPs//Wo4YZDu//Sb4YTBuv/T74QTsnT/19sFJxyj+z+9Md3vCMfq/k/vwAnHmeo6P5++G5wwhL6UfiycMJR+Ln0pnDCM/jz6lXDC8fQX02+AE7LpV9LvgBOG019Pvw9OOIH+Fr1dedguMEL3c71dcMJI3c/1dsEJo3Q/px8JJ4zW/Zx+MpwwRvdzvb1wwljdz+mXwwnjdD+nXwsnnKj7Of0WOGG87uf0u+CECbqf6/0LJ5yk+7nutzP8jnCy7ufPcnvhhFN0P6fPhhNydD+nnwon/Eb3c/pqOGGi7uf0y+GESbqf06+CEybrfk6/CU4I6n5Ovx1OmKL7Of0eOOFU3c/pD8EJU3U/p2+V73eE03Q/p8+EE07X4zz9ZDjhDD3O05fCCdP0OE+/FE44U4/z4g/ztxplhVw9/rP8Bjhhuh7/6WvghDw9/tMfgBNm6PGf3inwO0K+Hv/pe8IJBfq4oB8LJxTq40Lvdzhhpj4u6IvhhCJ9XOh2gBOK9XFBfw2cUKKPC/p1cMJZ+rig3wq3E8zSxwX9PriDoFQfF7qdC3E+AmUcB77W+xcuC8ym/1FvL1wOKKePeY7XS3ALQAV9Ev0quLVgDn1b+k1w20AlfYB+N9wBUEXfnb7pTJzbQTV9P/o1H6c6wlz64+gXv5vqCPPoR9IPwTLGgvn0J9Fve7+DIyyAt/F6Cv1UlBUWmioudDp9MdwicDa8D69z6dfCrQPnwJt4nUe/AW6j1GH5Gbod4LaAc00VjyrQ6wNXA87j+hTp9oHbC86nn0V/EM4uQkyHvpy+FVwAXEBfRd8TLgtcSD+ffiTcBLCE/hz6yXDCUvrz6afBlYKL2D5L6BfBLQfL2M7L6a+BWwUuNlV86UrdPnCbpA79jfTZt3VwhEvMqOfjKLsbXMp2u43lf4QTLuN6rqOPL8Y4BlZwfTbQZ8IJl/O4eEC/L9xU8Dv6x+gXwAlX0D9DvwJOWMn1eUlvL9wGcCV9Df0OuL3gKvrX9PrDNS1B/J/+jah2uCaqHQag7EhwLdv/Lb2/4ITrTN4f0RfACb+n/5h+KZywin6/Pn7hhOv1eZN+HZxwgz5v0m+GE26kt7bzfAQnrKZvQr8LTvgDfUv6fXDCTfQd6A/BCX+k70Qff5bfEdZw/XvQp8J1AzfrcYM+Gy4H3KLHDfpWY3DfB3+rHjfoK+AWg7V63KBfKe8JbqOfQr8Rbiu4nT6XfiqWXwN/B30x/R64A2Ad/Rx6YxbOR+BO+rPpA3A=
*/