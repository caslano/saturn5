
#ifndef BOOST_MPL_SAME_AS_HPP_INCLUDED
#define BOOST_MPL_SAME_AS_HPP_INCLUDED

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

#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename T1 >
struct same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : is_same<T1,T2>
    {
#else
    {
        typedef typename is_same<T1,T2>::type type;
#endif
    };
};

template< typename T1 >
struct not_same_as
{
    template< typename T2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<T1,T2> >
    {
#else
    {
        typedef typename not_< is_same<T1,T2> >::type type;
#endif
    };
};

}}

#endif // BOOST_MPL_SAME_AS_HPP_INCLUDED

/* same_as.hpp
O7ZrwDqiux7A8JlwBpacNpjua03rSZz++fTG8bbBBBir6dEqtQIv9L3qtt7n7lmRSDeSa4d+mPJkwR/oeXgNdvGN/T7+1b7CnfRZhLIV5xluTPCsFJs3MgvN+UK9Ny45j8u85mDc9QBy8e6NPTrCL8lHa2NzHY2/sA5CJBSODCckr3ikwAF3IiDSoBegJ0wLn2ktTVlroQW1OvLuAp0ap8plbTUTzSh0eDd66MmVUotMpcU+96wQ/SdfHlwKwqMWahIgpbbOC8KPadJY7BhfMGpyWjrZH8pV62zqgR1bVdMOjUfepg02iKrhN4aoVNY6uqjdnEw2gy85fTYPujbbeQT1EA83CVGm/TBgSo4DFjhviJZiyyLNthi0arOG9cNmX7ggQRxXEb9a8Q8zLu+d9od7mnZYZMH6XAVS0gvYY6BPCppB2TW9eHWn/KR4cc4RgeIO9LBd58D3QevumrTg8V6wAKb8FShVjejZmoRsuGN/qKFMc5rWJ8chEg/tuXdRPaTbX68GmzyTu8cJBactWCUcrSIwVbC8JfycP8VBaZiEv82SRXrw+m8b8A==
*/