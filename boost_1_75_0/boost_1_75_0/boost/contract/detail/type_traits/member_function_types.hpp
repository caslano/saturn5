
#ifndef BOOST_CONTRACT_DETAIL_MEMBER_FUNCTION_TYPES_HPP_
#define BOOST_CONTRACT_DETAIL_MEMBER_FUNCTION_TYPES_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/none.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>

namespace boost {
    namespace contract {
        class virtual_;
    }
}

namespace boost { namespace contract { namespace detail {

template<class C, typename F>
struct member_function_types {
    typedef typename boost::function_types::result_type<F>::type result_type;

    // Never include leading class type.
    typedef typename boost::mpl::pop_front<typename boost::function_types::
            parameter_types<F>::type>::type argument_types;

    // Always include trailing virtual_* type.
    typedef typename boost::mpl::if_<boost::is_same<typename boost::
            mpl::back<argument_types>::type, boost::contract::virtual_*>,
        boost::mpl::identity<argument_types>
    ,
        boost::mpl::push_back<argument_types, boost::contract::virtual_*>
    >::type::type virtual_argument_types;

    typedef typename boost::mpl::if_<boost::mpl::and_<boost::is_const<C>,
            boost::is_volatile<C> >,
        boost::function_types::cv_qualified
    , typename boost::mpl::if_<boost::is_const<C>,
        boost::function_types::const_non_volatile
    , typename boost::mpl::if_<boost::is_volatile<C>,
        boost::function_types::volatile_non_const
    ,
        boost::function_types::null_tag
    >::type>::type>::type property_tag;
};

// Also handles none type.
template<class C>
struct member_function_types<C, none> {
    typedef none result_type;
    typedef none argument_types;
    typedef none virtual_argument_types;
    typedef none property_tag;
};

} } } // namespace

#endif // #include guard


/* member_function_types.hpp
EHkjyENREQFRQVHH9/jmLSgvGWAQERiYAQaHmXFmeIhmZD7R1HxLivg2U69Xe1iZmVpZmVqZmZqZmZmZ18zKzNv+r7XPOTNnYFC633f/t+/36+j+cc5ae++19t5rr73Wfk39rKzowqze7R4sX7LkZfAtCsFfqQHfEnzUwsvgk64Gn3E2+AF14HelZHW2zwGf6jb4STng650C31QLPpcW/NTr2+tmPQC/aG9WiGsx+NoXwL9cDv5qA/hNQNP1Ovg+v4C/+g74cCngN18HXzUdfCEt+ElXwaetA59jO/h+NcuXL8kDH7MS/MU/li+pew18ydng+xrAj27IC3GtA5/WAL6t1hDfWwt+5wXwpVaD75UHvvnNhlllDcX9OswG//kX8FePgn82D3zBysrx/dLBZz4F/lPWkrp5WvAZC8HHLQT/bhb4t/X1DQ2zt8+rXAK+YA7403d3LZ/9MfjzWvCh9oP/eRh82PHgX2nTe3uXgd96DnzN1eBT5oAfPxv8uCzwm65mBdrnlY0I3Az+Vgr42Hu3L5l1Paunaw344w3LDYUPwK+flRLoWLl6+fLLleMHLtm8fVd6irf9XfARPwbftwx8tuXgk+Ws1uZdf//lvWWvbV49G3y2XeAj1oB/+c5r2xvSL586dRh8vdvggzaAjzkbGH+/sHe7QvDzisFHTAG/Xzs7K3r16iVLcsB3vAr+XQ74yL+AD3v05tUL
*/