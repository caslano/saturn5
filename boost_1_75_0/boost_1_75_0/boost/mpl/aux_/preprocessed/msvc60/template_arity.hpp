
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
U+LP9MFjz/ZPrVcPwZTGmWFYmtokaW+5ijOupFVbfw7+tkm1G+tKmTsJtlSKtqHUHeWf8/C4n50IFlPQurypprl2HL2XNj6xwweJh60+JURU3mULlh7y6R5cktPXVg7LqmU3y4GfIYZ5AHlOeA6kmaVxpE/TfLB+mSTr3cEHztNiofW6IelFqB86bZ7sfaHe6myrmihM/ZrToySrqMfOQezJ0aFzrJMd1Pl0+fkJBWhtfYbBYeXhF8Mt2pWHJozEIk387PAwIWhDtlVT+SpQ4ZNLKdvEJeOH3dVNco61aIYmw28VX3s+H/76rM7/yS+K+lvePKbKkm7weKPq+UToA0DCy9Wx1ldvlMlDIfixscaNwmbLEpPbTiUiJarG3CMY+2T8N1+tSesdiXvd/+TKfJCZDGsivAJXWmMXL8su5u3mHqDxz9pOO+5avT3PTo5gdUnlMF6Fw53t1oM05+6oXA42mN9k1XlWavOk6ioLmeZixZfXKhIokyl7Z2e9E7FO1uPmAcdVCOtsWpNkskShI/8q00f9THNDhczIAeLTm5OiuGxVjjrV8GMxe5Yu0pnG8nMoXU0ci+45UiSzsmtxQkSHduwEORNsmdlRLd4tkO498bFnSarCW8/p9c56Uq1G25bjc8s0JY/uS+45VQlpitXfL6W9OfezOhqhHEZLnkI2U8MPjW6VhKyzlTfyqMd/w6sB6oMhti0jcHGD
*/