
#ifndef BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

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

#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/has_begin.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   include <boost/mpl/aux_/msvc_is_class.hpp>
#elif BOOST_WORKAROUND(BOOST_MSVC, == 1300)
#   include <boost/type_traits/is_class.hpp>
#endif

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace aux {

// agurt, 11/jun/03: 
// MSVC 6.5/7.0 fails if 'has_begin' is instantiated on a class type that has a
// 'begin' member that doesn't name a type; e.g. 'has_begin< std::vector<int> >'
// would fail; requiring 'T' to have _both_ 'tag' and 'begin' members workarounds
// the issue for most real-world cases
template< typename T > struct is_sequence_impl
    : and_<
          identity< aux::has_tag<T> >
        , identity< aux::has_begin<T> >
        >
{
};

} // namespace aux
        
template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : if_<
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
          aux::msvc_is_class<T> 
#else
          boost::is_class<T> 
#endif
        , aux::is_sequence_impl<T>
        , bool_<false>
        >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#elif defined(BOOST_MPL_CFG_NO_HAS_XXX)

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : bool_<false>
{
};

#else

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : not_< is_same< typename begin<T>::type, void_ > >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#endif // BOOST_MSVC

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct is_sequence<int>
    : bool_<false>
{
};
#endif

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, is_sequence)

}}

#endif // BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

/* is_sequence.hpp
62r07pPW2/H8pcIRjJkHJ/F1VrV0zJ2W3GZL/pAsHjxrH4spgtrWZpeEwitbT6JbMUOaXxJ0gBEjXobwD3/gT2rZ9Y5Q06x466e7YKS+gkUiyytWzvk2r4hbojQuX3L63M0FitkRCq8+X498gqMgtxEX3m5OYP+vnFQ3LY+dJn5/3ECbUB8dDolzqUgRf2TzYggS+ULdBAqgnCe7LUStsQFDmugvzwkj/aYe1Axazq6EWlvCt9WDKs8eSxqPY50BI9M/v6MgK8elX0u+o87VFOhN9TqFMDpNRyJ5nq4A6cssPr6BoiAOIYu35r2/F3GvrILFVwDxzHPaUzGE/iYEArDQjek8tV8iEmMky17sPusn99659XwHOm5KWhzJQolCVTIDc+6+Kfxv0jofDLL8u8OMyr6m1JMBWVefVA38LHcetMeF7uOgEUsrQS0tBWLQjvJ+MTF68Y2FD1x37VQBjXiRmdtElC1tVMZ21AHjW6mkK6+rDjRtx4r1ln9Wd6+tsJs8l+61VwfGtkDdT+1c1zlM/Pf7DlqgXCsrY57rk57rXAbJrqUpY14l6QprUZH79p3P8FFd11p3D2cRMC3/SPNO6o2BR/tNYOywff8DKO3RBKLfsf+8dgP6BPf41K3bo8pl2OND/DjbdEYWVHAj2BpQq9aTETi1SqOMr+Hh6bDlYiZb0y+mdOKMRTRu9oRWbzPblKsJx/X2w87z
*/