
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

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
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
SeYuyWVxXBtgvzEZZyb2sojlmu+IlZHp2HSIZZGxrL8bk6n8aLpklpk3pN0kdIzP7iX5lZgB6c1I3zVT0sMoMhLL93NibkhvQGZj05f1BTGF7Pen/Yvr7OwPSQLcx3r0bEuWcsD+LmHKuhzQ7+NM/R5nGsgZDCZ0kY8RR0aiBey6dRvgHDsyl4+zJuSsjGXbur+VmBZouUi1tzVMvibR2mNR/wwLGWkxI6AQHKDLBEMo4VygqrBSr8q+TzL0uQxJRHbY6H9RFESK9ydJeGxJ0B9fEvT7klCv1R5KEr6DNXUJ4js/pEGQv8KQDxqxR/IehPUd+3Fys9X/TRyedgCPPt0fdUF9YvvT0vYYXP/PrRTb1QFruzPtC2gXK+H2qFsui3gSXnKK6y7HQ7EcTmU67SvPptORrSz4PHXRwKGBUeZ7rnhJssEvuyoYIV3zci2CDBf9khm3PoX9afwVSJAke6A8l6u7g/m9HtSlfojmtNIeoENE4Fae0zNEXUSMg0gjEFkInkCRl+1eyZHAY73cQgtY0xUvIJF/IGCNeeVYLfiG4w13Au3LSf9D13J6F1NnSAbWGUujQForvSRRLu2kcWmm3/kwmlj9C9IBj7IVOlsWOx0KBT4wT1EPlEOrs5PRdUcL/Ln0r1WxEMua
*/