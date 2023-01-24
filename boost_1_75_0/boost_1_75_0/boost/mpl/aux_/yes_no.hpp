
#ifndef BOOST_MPL_AUX_YES_NO_HPP_INCLUDED
#define BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

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

#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


namespace boost { namespace mpl { namespace aux {

typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];

template< bool C_ > struct yes_no_tag
{
    typedef no_tag type;
};

template<> struct yes_no_tag<true>
{
    typedef yes_tag type;
};


template< BOOST_MPL_AUX_NTTP_DECL(long, n) > struct weighted_tag
{
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    typedef char (&type)[n];
#else
    char buf[n];
    typedef weighted_tag type;
#endif
};

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
template<> struct weighted_tag<0>
{
    typedef char (&type)[1];
};
#endif

}}}

#endif // BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

/* yes_no.hpp
QvcISWRvASHXbWX+ex9QhHBb9/nXBlYSzCfswQLvQg1RXCDEb1pX9xyKfzbf92ya20cJC4u4fUDijIaKvsM46rX2MGhhX4gLtk6uhkIz2dt+f+mkJ8HAdjMpwT69lcYOCbMWeB9f4V7efIb1DnYQhHiTsz/7u8r5rpJI/ZN5QByedO9al2/pLCXmgWW3e4AALq+J4eNHE5b4ALfHYGFvse8ZVgJ1qtiyYl4R7IuE1zeHgN8JP6ldpZg8C1N818/UvUw43rM1hELWCd9vt/1OCAp0lCPC4PIGSSJ2rkFA1xjVL3wOP9V054R+T8vNZPhyeJnVsUNTOoZ+RNMJj/gkrl2yJXlexHezE9w6DTBw1YYk/BQl2eb1kQg5zf/arTqMps5mMldCQyCzQniYohBV0di+yuaT1FnqI5kELzsrjmmKWQM28el4JNmBOr3gdCWdE/OWBivD4kwjOFEykuIONHpHwS+wQe8Cw0g4sBP+bOrDgIC98baiZokEyGwfE8On5nEfLC78dvrRD/lIT222seii0jOP4KY2YKNP1hG6vwbtnF05vUGhXjNefIgHwpcHHXpqs3G66d/frqOW+gWRP+c5FAALjKlHK6vtHFu8PVicdSNRQ/yGiSMZxIHZQJ8qJ4+2pvPLo2kVkxbVOGd6PlIvNN8Q8VKtkWZSBwDO0lMV5bOM31pOeKMdZBQL4It20yMlzGdA6c976e2X
*/