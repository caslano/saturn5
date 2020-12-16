
#ifndef BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED

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
#include <boost/mpl/void.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< 
      typename T
    , typename Base
    , int at_front = 0
    >
struct v_item
    : Base
{
    typedef typename Base::upper_bound_ index_;
    typedef typename next<index_>::type upper_bound_;
    typedef typename next<typename Base::size>::type size;
    typedef Base base;
    typedef v_item type;

    // agurt 10/sep/04: MWCW <= 9.3 workaround here and below; the compiler
    // breaks if using declaration comes _before_ the new overload
    static aux::type_wrapper<T> item_(index_);
    using Base::item_;
};

template<
      typename T
    , typename Base
    >
struct v_item<T,Base,1>
    : Base
{
    typedef typename prior<typename Base::lower_bound_>::type index_;
    typedef index_ lower_bound_;
    typedef typename next<typename Base::size>::type size;
    typedef Base base;
    typedef v_item type;

    static aux::type_wrapper<T> item_(index_);
    using Base::item_;
};

// "erasure" item
template< 
      typename Base
    , int at_front
    >
struct v_mask
    : Base
{
    typedef typename prior<typename Base::upper_bound_>::type index_;
    typedef index_ upper_bound_;
    typedef typename prior<typename Base::size>::type size;
    typedef Base base;
    typedef v_mask type;

    static aux::type_wrapper<void_> item_(index_);
    using Base::item_;
};

template< 
      typename Base
    >
struct v_mask<Base,1>
    : Base
{
    typedef typename Base::lower_bound_ index_;
    typedef typename next<index_>::type lower_bound_;
    typedef typename prior<typename Base::size>::type size;
    typedef Base base;
    typedef v_mask type;

    static aux::type_wrapper<void_> item_(index_);
    using Base::item_;
};

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_ITEM_HPP_INCLUDED

/* item.hpp
KEIpKtCKDvRjBPFv5TyQinSUoAoN6EMYsxZTXliDApShGW3oxRDSllBeKEUdWtGPcaS8jfNBOjKRgzxUoRYt6EPo7ewLC5CBbBSgDPVoQydGEZPO+SEfFahGD0YQv5R9IQd5KEQVGtCH0DvYBzKQjXo0ow0x7+T6YxlyUYRSNKEHgxhHyjLOCTnIQyFKUI4qNKAd3ehDGKHl3KNYgAxkowBlqEE9BpD4Lo4BuShFE/oxiBGkvJvzQyZykIcq1KIdfQhjGEkZlCkKUIYa1KMZbRhFzAr2iRlIQxYq0IQO9KAfgxhH6nvYP/JQggb0Iem9nBvWoAyVqEEnhhCTyTVDPipQhyb0IGUl20UO8lCOBvQhjGGMIfQ+9oFsFKAMlWhGL4YwisT3sy+kIRfVaEUH+jGClCyuITKRh3LUoht9GEPS7ZQfClCJNowi8QOUF7KQi3xUoBUd6Mc44j/IfpCDQlShAS3oRhhjCGWzHyxGBgpQjDI0ow2dGMDQ/9g7/6ioqi2Oz+iMzggUlPQkQaFERaGgoKTEQCGlQEHBwCBAQaFERaGksMCgJLGkJwWlJSUlJQWmJSopJaUFhS8pKSwwTDRNKClJqbd953PBp/j+f2vpWt81S+bOvefHPvvHd+9zj0AXLM8XTBFkC3YLDgrOCVynyvMEUYJUQZ5gg6BcsFdwRjB6mjxHECSIF2QItglOC3Qh0j+BuyBMECtYKlgt2CjYLagVtAraBecEg0PluYIoQaIgVZAnKBSUC04Izgisp8uzBUGCRYIMwRrBJsEewWmB5Qx5tiBMECtYKlgrOCg4J3ANk/4JEgWpgjxBoWCDYKfggOCEwDpc+iiIECwSrBBsEtQLmgSnBUNmipwIpgjmC7IFqwVrBbWCg4J2wTmB6T55tsBfECXIExQKdgr2CgwR8kyBvcBTECHIEGwT1AvaBKcFukh5psBdECaYL1gqWC3YImgVmGaJbArGCfwFIYIoQaIgT7BBUC7YKTggMNwvzxWMFngKfAVBAvco6ZsgVrBUsFtwUHBO4Bgt9xf4C0IEUYJMQZ6gXLBX0Cw4IbB+QO4t8BXECxYJMgRrBPWCJoEuRuZOMEQwXhAmiBUsFawV7Ba0CtoFrrHyXEGIIFFQLtgrOCOwj5M+CHwFEYJ4wRrBJsEeQb2gTWA5W54lcBeECZYKsgUbBbWCVsE5gesc6afAX5AoyBOUC3YKmgXW8fJMwWiBr2CRYIVgk2CPoF7QJjgtGJIg4ymYL8gWbBQcFLQK2gWmubIWBCGCKEGqoFCwU7BXcEJgPU+eJfAVxAsyBCsEawSbBNsEewRtgtMCy0R5rsBdsFSQLVgraBW0CwYnyVwKXAUhgkxBoaBcsFdwQNAsOCMwPChjK/AVRAjiBWsEmwTbBHsEuofkmQJ3QZhgvmCpYK1gi6BW0CpoFwyeL2MriBLkCXYKmgVnBNbJ8gzBIkGGYIVgm6BJMGKB3FuwWrBWUCtoFzgulH4IogSpgkxBnmCD4IDAsEjaLsgQbBLUC5oEpwWWKSJ3gimCMEG2YK1gi+CgoFVwTmBaLO0WjBOECKIEiYJUQaagULBTcEZgWCKyIRgt8BT4CiIEiwRrBHsE9YImQZvAMlX6JnAXxAqyBWsFGwW7Be2CwWnST0GIIFOQJygUHBAYHpZnCRYJMgT1gjbBacGQR+TeAnfBeEGYYL4gW7BasFawUXBQ0CpoF5wTDF4qfRVECRIFqYI8QaGgXNAsOCEwpMuzBb6CeEGGYI1gk2CPoEmge1TaIRghcBeMF4QJYgVLBdmCjYKDgnOCwY9JXwWughBBpmCDYKfggOCEwDpDxljgK4gQZAjWCzYJtgmaBKcFQ5Y=
*/