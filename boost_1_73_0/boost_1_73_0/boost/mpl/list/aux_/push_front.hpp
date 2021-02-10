
#ifndef BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::list_tag >
{
    template< typename List, typename T > struct apply
    {
        typedef l_item<
              typename next<typename List::size>::type
            , T
            , typename List::type
            > type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
iX187znHRwkMaiOFxgELkmylaHjCfamKSA/YOAzn1QNuRyGTSj0lqJvxpyhYwN+wAa+3f4QFFjssXJ1EyIIC83RPq5Ewoi7Iu50uHHsezD6DLrVMlUaHXQuDPoRbPALvAqZqR5CuB92e37vwCXz7JXTYUGUGM+OG+5zABp8Nj80mddgCjTusaPkwmQ+/f/3mdcXKW0lxKvseXV26z7ufziU1jo5Po5XsLS8hFybu80uI1EYkWb8znYU/rieL4d1sMbruWFovHe8wW5vYh57DHLZUiuTWigLeKCThwzSx2Fq4rD4IoCs7Biw2Jif4yycEmdhgbckRFCgx2SE0HkMZYwZbnWRrkFtt1AbGShv/qKHaLKks3YMpFc0aTRV5XRICqTYbkUV1U5/zg/FsEU7m/oHtNp/dh7xEXorM8LMTcCWkas3pQM9OOubZgDuGdtUOYnq+c6VNKl4b0GsjlAx4xCJZ7cE6A2JlsAATI9iEQSw0LJFEtXWsDJXYVVgqkBfKKKnSAaOQwe/EXtLisP+wcdgDWeperYmET2YVKT94HN0vJrOpw66kxJymD/mhPbiAvzULVkmKYA3rt/+Q34aNimjSxqtt8zxFo6XIseIDdczghnbTmvVXk8G2L5HhkZKa20m3OcmODSgBwzjR
*/