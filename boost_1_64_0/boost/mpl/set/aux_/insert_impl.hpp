
#ifndef BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/item.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/na.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {
template<  typename Set, typename T > struct set_insert_impl
    : eval_if< 
          has_key_impl<aux::set_tag>::apply<Set,T>
        , identity<Set>
        , eval_if< 
              is_same< T,typename Set::last_masked_ > 
            , base<Set>
            , identity< s_item<T,typename Set::item_> >
            >
        >
{
};
}

template<>
struct insert_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename PosOrKey
        , typename KeyOrNA
        > 
    struct apply
        : aux::set_insert_impl<
              Set
            , typename if_na<KeyOrNA,PosOrKey>::type
            >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
6nEfb49yt/LY2cl+fQ9wv+8K7WX+uQf8W8e5TEbdeRxbH2ggrJ/9ugZzbIPt172Jc+SHpuXYv1HwuSjHOxbt/ZXZRPgs80OT7dc/g32ZCrty/n0bdo/K+j/E0Z/jnQvty7PPi2BjIdddBu3lGfMq+3UsYrYeNt7kuhvhyyfc1z6x3/AyjmOb/UZr8vERtl/PGLaxD6wqH6uHEUdebu84dM7L7Z1AuSGswWn4J/dgZ1EujfP2I8pNYnYJLMz94HdoUIZZ3uKW3xocRyGwI6xVEWPurzjntxhzyrPoUsYi8kypvLHw3ayBCzbe4/G5urFMme+sbcxbjsfi+qj7pYNYY2PBe9lGU/gn91v3I47S7PNDxqJNZf7PWFwr1uUJYyF5PtMG5WSetZ0xh8TW0ZhP1sTEG/PLmuPuiEPa64U4urMGPvjSjGPrC13E50HGPLKGeThyNJTZi/BZ5gXGIG8Ps88TYGMe+zIJmjbifv8GcmknUpr/Q2xvMZuJ2OQ6bA60epxztBA2xvMYuxQ2gtxPVxqzBTTE1iHelhxbCLrIM7mPweR52WfIbxn2ZSf86yDr/xDbei53CL4M4/x+jrzJWuevENunrMEplJvANr6HXXlWfh75kPWJP8OXVI7tsjF/ce7jeUpYewXZ54LGnHLNX9iYS84VTmPhXnxOvtWYd7Ss/zOWWU3e/zUWrcd2qxmLk7UztxuL5Of+V8+Ypzv3tUbwbxzrdzeY5Og+tBdiGw+CFZf1f/BZ1hC0Qrw7Zf4PPh/nY+FZlJO1JM8b83fgunEoJ/NmifC5Nef3BWOOm2X+DzqncLkMYyHpGwORy6/Yv2GIrTKzv6JuhK+RXkLd6nysjod/O9mXV6Gf3Ae8Dl1k7cybyPkgzuUM+CLzNLOhyxvcdxcY88m6zSDaOyDr/xCHPE9ea8zzANf90FjAw2yzMYesd/wU8e6S+T/oIuuW9kCDt9nng2hP5pCPoZzsBfelsaC8M/UN8ivvdJ2BprLW6hz8E59/ggYTZf4PvtzNOXeUNLvN5f1fYz6Z07rJWGY5LnezMe8S1rkk2qst+/8Z88uak0qo+xSz22BjPvehWsYcst6sLuq25Hgbgn3FObqrJMZEZs2MRc6zjeaIV95BeMRY3EVZ/4e6cp7xIjZZL/AM2hPWwVhIntt3QXuiVYIxR1/uQ0lg8pw9xZh7LPeXdNi4jdsbAF1kzedQY85nWPuRxjzHuZ+ONhY9wHGMQ91FrMEryNufnKMpiE3eo5+Oumf5Pi/TWFjuXWbB7sMc73zUncm6LIHOczne5YjjIPu3BlrNZxsb4PM6vif+COXmsN2t0FT2RNiBcrO4vd2Io5ORa+f/jDmWyfwf2Druf18YC16S9X+I4xifK74z5h/FsUVR91c+pi/C55bcn39Fe7JG6U+Ukzmy/Ldavx/Imt5ozPMMx1HMmF/W+5QwFpX2yqA9eae/orHwL+xzVZSTdzhqgn0s6/+MReQd3gbwT+aHmsC/e1mDe4155R7RY8wt+xo8jDhKcy4fB+si83/GgrJvY1vEtpjH9ueMOXeyL52NZWbyuaebMZeM7T0Rm8TbG+WEpcG/ruxzf8R2D2s6xJjDx3VHwEZlWf+H9gYxexmxyfxuAPnYy33yNeRNrp+nGQvIHpzvoO549uU91D3Ddechl7P52F8MTWUvx/eR3zqcy9VgspftB9DPwcf+JvhSgMemLcZCD7ON7cZ8teT9X7BMWf+H9sTnI4jtZo43Al1knvUk8raL7X6LeCezLj+gPVkjcgH9ajz3g1/g32/syx+wez+3l6+U9edlsv7PmE/WtRRFuSLsX3FjUVl/WtqY/0u2UQF1R7MGVVDOze0=
*/