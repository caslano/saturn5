
#ifndef BOOST_MPL_EMPTY_BASE_HPP_INCLUDED
#define BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_empty.hpp>

namespace boost { namespace mpl {

// empty base class, guaranteed to have no members; inheritance from
// 'empty_base' through the 'inherit' metafunction is a no-op - see 
// "mpl/inherit.hpp> header for the details
struct empty_base {};

template< typename T >
struct is_empty_base
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_empty_base<empty_base>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

}}

namespace boost {

template<> struct is_empty< mpl::empty_base >
    : public ::boost::integral_constant<bool,true>
{
public:
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,is_empty,(mpl::empty_base))
};

}

#endif // BOOST_MPL_EMPTY_BASE_HPP_INCLUDED

/* empty_base.hpp
rhAhx8tuwo+Fzxle7IIuPvRGH/dmF6ToTckRGNiMsq41l7/5w+81hI+ySdZ4/Ko/b+DTd+7CbQgbCOVht3VfbTXLVViVuGl3nLpgceEzw4Vr00IbYDURg2Er1TGhurNELIoj32UhM0d10RKrQDP9mKCzge/YRDLPCg9u5+B0qGJx+9EWRhJkN1SksgCjhscNG2pElqlkpqFQptfTNW0sdR3/PiBiGuJCtb7uOB+Lp9BHNC+zpkBimj2rqtyGs2ASHErQqKhIPrPIETC3sUjq+as+8c+jeiJ8mROxYSM2K4Tdo+JFqgrTDq7iTbGGdjV+gfdDJblofNakiHJBSnPUyEeQiXKRJDG7x/c+T668nnYKa7hSNtpiQZMvJfQ5Wd9j0nhzmuX5hmxihyS9d5fCGZsH0kk2llJ6jcfe5CcJFMjJ5pxGSy8u3vUgtbm1ger+1Owznb+3eP9cWW4EfFuYX8c8vwl7ANuDmOQxpFbd+IfLpA4VfnmTVohkRXlbaJgO7l+wm+KOkmMbJW1tdfsn9XV49m1t+a3L4CK8gwW82K0IbC+IY+N4i6lQsdJKUecvML6clcUcn0/CbOwSvGcXEeMh3GlO1Bu2oQkU5H7n+Fsp8+3KTEl0QPtRC9WLN8LLC8LLvaZTPnGv63BfV4XnB4deJqvQvVRPLtsaSdQslgERaNQdbaJXqC2APuK6UMB8QWrTPqPVcQInqKyi
*/