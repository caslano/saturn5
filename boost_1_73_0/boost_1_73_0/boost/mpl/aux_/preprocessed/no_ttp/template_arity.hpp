
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

}}}


/* template_arity.hpp
x1ita+nfq3kZZOU0POtznHeIkTDIcjDV1PhTcqgU+bPP8blMFOp6Id9BQyHfb1eqfiddSc3FXUIejHY3XVGX0ns+s/oexXdK7xTfcdebt/yWZbfbZZ3wfb21qSsfvVpG6l8mlobB4iPPkPov2sEnOFb6rlrtekbJpty97XrhkE25KZtyJRvZBhrd9wvuZRf3gr9iYsO+jlJs80Wh2DCUmQViu1ZIsW2gf691IrZlmVQueWxy66fkhqm3kItC3aQ=
*/