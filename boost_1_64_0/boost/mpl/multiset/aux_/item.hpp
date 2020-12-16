
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
28QWDKhcOh/HyMc2+/mgZUDH19/J5n3WeqSZNuVwuHLpd1WPs/7CMtZ/M+Vgmw/ZP5o2EiNdSpfDV72VA95uPuiaIGxEefJgLPtUax6M7+5naN/bLZI8pMoxqtdJ+5SqPNA7Rfig8NFK05QO13NJm5Ca42A22q+zldgD/VRN3qKr2G+3cpudvNFkZbnKJQ/V6zoj60qUcoiVc7XQzro4Mf6S89R8XKRUtX+eRla1lxc5OMtxXNg/R7V5KLKTh6/Jg6GMPOQaM+F4HlrYzYN2n6TcZv86sdxOHjhJHV53GdcI7fbfZv8asc3eum9iHzhyfTBUK52H08r3h7083MQ+sM1DC8mD+lpdXM3+NcrttlJ5MF2gylEG9q9P2jLIqV56/WdZf4Bp/WEjlLXaXCnLc41c29y4TsmDlEmqtgwulZGHyFJ5kJKooPWbYxE2Sh19sVybikjfsn6Daf3KHYzqOuB4LIJcBzTxawlojkXIJSWo2qbxRLlOW67jcsxo8htV07SyJyW/60jfkd/8apr8yvHq+D1Pi3Lm95Lkz3q9lX54bfJ7UvIbIfkdSPpeKd/q1vwacs35vXFMjrqtnwTN+VU6L5nJyabjXfKSV0sWJMfafFIReSm05kViTir2/kwTfyKBgep8mXfQJpKL7NufepO/GnbzlVve62GLm8zXUcnXdjk/N5KKlXOzpm2+St/HWTJ2w1jV612zJU5Hk0drH8LPtGS8MVJS2r4pY7/n1zatPEG2I4p0UbnO1bK3HVK+FbQdLSpgO3rIdgxQKu1kP9SW+p9Lyvdm6e3gosmVz4EYtxt8X5Q+RlTnGNNIu1/WPFava1r4IInt6o+/9DZVgPFfQoaSNVVOdQ5dU6u6P1vb3DbSja/v6jzH2+SZaZQ8q+6VS7djdES2oZFsgzc+2pNrTp1K0saV5hvJgWtsVfc/6pTO/9Ne5Wvjyjbvuapr3iXrfb4mBm2PHMCfSp3vh1ii3OfVtWxLKoeecRs81c8FbnDdtbQZxGeDslKdNd/qNrQ8MZdkUH13XLX0s55UKu9K22RHKf/dLGgE4+51s7ZNVqL9jtHssyXupsyulnN8GemKcj/nbt5OOa+Vy9RNnttcR6X8rdtOnmW7tfvPU7v/5DyX9pZU5zifmUR7T7SNGZVhjRx/q5Djj/GVNG2LjTUfgLI9vjc4Bmt7On4MltW+2DlN+2Klj8szNu2NFdm0yVUssc7ZcnyctNPe2CWb9sZKymhvzJ9plKE9yUViMNZTTnvZTmO7WIma89Th78tO9tvt0pxXnnKyRMg+GohXe5sq12XdynnlcHuT6vstVzv3W24294eelnypvzOs++FPBl8+GxKkTM3njvpcUp2DRWW0PXZYtnOynFcjSX+wnfn1zdv5n59Xsl7td2bp+2Lb88j2u1Jz3znHy7TS2aTaUp66PqzL9I5NzqzMbF4JSueylK7PyHHkO8ia16Rs7Xsp2VmJln2Ua9MmqK+UcT3VfWlifFbWbFV8brSzTTWJ5y2rLbTyx+2WNz63vHG45Y07HmWM203p/nXrdyd0ulI49WjykjlN21Rcm2rXi9tdopPn4rjYTptmYZWJE8Jw9MCB6I2D0A8HYwccgsEYgT1wKA7HYTgGh2M0jsA7cCTOw0hcgKPQFEcsz8XR206bK12YzgWD0AuDVfNtu858vWW+PjJfX9V8hS5lt/ESIvN1x9uxh2o+XZWy1zdB5pso65sk8xlIvjJfqsxXC5NkvgYSl9YIfdAH/bExBmIT7I6+GIotcAy2wgnYGhPQD/XYFi3lI+t1t5NfD4nP9sS6SJ4lDlOexWKizKeOw2wkx0cT9MCm6I2+2A6bYQA2x2BsgeM=
*/