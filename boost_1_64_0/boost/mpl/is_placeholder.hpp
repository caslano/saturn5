
#ifndef BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED

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

#include <boost/mpl/arg_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T >
struct is_placeholder
    : bool_<false>
{
};

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct is_placeholder< arg<N> >
    : bool_<true>
{
};

#else

namespace aux {

aux::no_tag is_placeholder_helper(...);

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
aux::yes_tag is_placeholder_helper(aux::type_wrapper< arg<N> >*);

} // namespace aux

template< typename T >
struct is_placeholder
{
    static aux::type_wrapper<T>* get();
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(aux::is_placeholder_helper(get())) == sizeof(aux::yes_tag)
        );
    
    typedef bool_<value> type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED

/* is_placeholder.hpp
UxZEvmzZLKUpBX7rOCRSqZwlqAlzHnduaKcGQMiUr8uajap+Ks3nZWploOtlkMhBoTII5ZCLHGOTxxN1XTLRrywqLVhkooZEEWErlsV/vZ4bpnTg/6mnoMrcrWpb8AobisYZgr0mfhKRg1dfcRQwFpTqrs0AJf0e8SdoK/SSFpOWeW+R11wTZz7LJt3srTg5HbDKCvb7MOqZxBkROZxED1aV0X2bOT5KHCGKU/dyqUCHLUnq+Z3s0hX+HPwnMYfhwyTKhwxUW38CtRf0B/RSXbtW/iRQ+XnOvmqZlkI1kYVwiplYCNLLZRVzW+McTa9ViV+X269bZs3JkljQ7DIIM29SDBy4sqtLZkF+gkaMx5A3kM8zV43BjowoOudnrbWgpYXgQajSECGCekLTwVbTxRvf2Ix3nuHfGOBwDAcYaJTAL8xlqEry1jewf8ZvI5aNMUf2oF6tAo166tRFkMS7jH1YAF6/yzlKxO5omu4vWBqYM8uaoLzBI4wqpxnUrbZlzWm3EddDbV9aFGTfOzkLHpk20+nybvFb22sObOseB2JcrJ/Ijj2Q90KJbg==
*/