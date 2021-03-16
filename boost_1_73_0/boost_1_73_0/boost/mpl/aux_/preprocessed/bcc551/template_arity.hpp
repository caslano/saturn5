
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
VL0cL6bqw3b+kKoPzDkhTR+YU5qm25Yath+n6YN1nkzTB+v8Kk0fotM9XWenpcvPmnjFJelG/tL1vNyaLj9f4RUPGmufM9YOx81LC7NJGfLrH4hphj506fYMfejSzgx96NJ7GfrQpb4+fehSwKcPWCoHm8j1bw7YJFknwc5kNhfsAmbzwILMFoKVMKsCK2W2DGwys2p60MGsFmwqs3p66MFsFb0vwiwMdiGzNWAXMWsEq2C2DuxiZuvpQQmzDfQ=
*/