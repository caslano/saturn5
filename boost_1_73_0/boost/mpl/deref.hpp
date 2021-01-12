
#ifndef BOOST_MPL_DEREF_HPP_INCLUDED
#define BOOST_MPL_DEREF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/msvc_type.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct deref
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename Iterator::type type;
#else
    typedef typename aux::msvc_type<Iterator>::type type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,deref,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, deref)

}}

#endif // BOOST_MPL_DEREF_HPP_INCLUDED

/* deref.hpp
KcI8gnJ+GK3pUnafyfkEkfP9PvsSd3mM37VN95ByKxqofYI7tjl+TdJbqxDpxQp4mTg+AZb0ShotzaP/qXSWV9vYJj3KYuQdJDX/LOnrFqCmTxk/EOA6vWbpyz9MrqcdCYfK42OO6bU0C/6nrqPatDn2gXpF+k/PKcM7GhblWm5dt1zBrfszvwB9IehDnK9pUZrxCM34AM14H814Z814O814brDzeE7w/V9D7/f3pLJDX1zm
*/