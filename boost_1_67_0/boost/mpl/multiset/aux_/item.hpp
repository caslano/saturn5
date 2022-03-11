
#ifndef BOOST_MPL_MULTISET_AUX_ITEM_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_ITEM_HPP_INCLUDED

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

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   include <boost/mpl/eval_if.hpp>
#   include <boost/mpl/next.hpp>
#   include <boost/type_traits/is_same.hpp>
#endif


namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

template< typename T, typename Base >
struct ms_item
{
    typedef aux::multiset_tag tag;

    template< typename U > struct prior_count
    {
        enum { msvc70_wknd_ = sizeof(Base::key_count(BOOST_MPL_AUX_STATIC_CAST(U*,0))) };
        typedef int_< msvc70_wknd_ > count_;
        typedef typename eval_if< is_same<T,U>, next<count_>, count_ >::type c_;
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
        typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(c_)::value>::type type;
#else
        typedef char (&type)[BOOST_MPL_AUX_MSVC_VALUE_WKND(c_)::value];
#endif
    };

    template< typename U > struct prior_ref_count
    {
        typedef U (* u_)();
        enum { msvc70_wknd_ = sizeof(Base::ref_key_count(BOOST_MPL_AUX_STATIC_CAST(u_,0))) }; 
        typedef int_< msvc70_wknd_ > count_;
        typedef typename eval_if< is_same<T,U>, next<count_>, count_ >::type c_;
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
        typedef typename aux::weighted_tag<BOOST_MPL_AUX_MSVC_VALUE_WKND(c_)::value>::type type;
#else
        typedef char (&type)[BOOST_MPL_AUX_MSVC_VALUE_WKND(c_)::value];
#endif
    };

    template< typename U >
    static typename prior_count<U>::type key_count(U*);

    template< typename U >
    static typename prior_ref_count<U>::type ref_key_count(U (*)());
};

#else // BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace aux {
template< typename U, typename Base >
struct prior_key_count
{
    enum { msvc71_wknd_ = sizeof(Base::key_count(BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<U>*,0))) }; 
    typedef int_< msvc71_wknd_ > count_;
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    typedef typename aux::weighted_tag< BOOST_MPL_AUX_VALUE_WKND(count_)::value >::type type;
#else
    typedef char (&type)[count_::value];
#endif
};
}

template< typename T, typename Base >
struct ms_item
{
    typedef aux::multiset_tag tag;

    enum { msvc71_wknd_ = sizeof(Base::key_count(BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*,0))) + 1 };
    typedef int_< msvc71_wknd_ > count_;
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
    static 
    typename aux::weighted_tag< BOOST_MPL_AUX_VALUE_WKND(count_)::value >::type
        key_count(aux::type_wrapper<T>*);
#else
    static char (& key_count(aux::type_wrapper<T>*) )[count_::value];
#endif

    template< typename U >
    static typename aux::prior_key_count<U,Base>::type key_count(aux::type_wrapper<U>*);
};

#endif // BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

}}

#endif // BOOST_MPL_MULTISET_AUX_ITEM_HPP_INCLUDED

/* item.hpp
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
*/