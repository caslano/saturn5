
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

template<>
struct template_arity<int>
    : mpl::int_< -1 >
{
};

}}}


/* template_arity.hpp
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
*/