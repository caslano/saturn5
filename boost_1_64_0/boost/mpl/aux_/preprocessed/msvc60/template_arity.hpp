
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
WtmXNcOFf5fL6WtE75zJe9tfXYLV31ACVWFUkORsOu5aJYxMlRIIOAfo/SD2WYE9zQ6aTK5S57KXpk58SDvc0Jfm+2XBhrO1yeuxY+ZYanjqMXaGy3cgqPBWCXHUzMGCzzsMbGk+opPWwmPRKQqNE+O8ptM7DqNLRfUW17b5cfI9zUZhcAnsrkHObR9rrlK/b6w+9HPlz7xibqSgwAU3GqvjlS+Hev1b1vRpbwJNGsyKtEySgO99nbkO5OGbrtupTEwg+V/3FQP4ScASDZWkJTvXCsBt59ulSU5x/yJCvKG7EEUpliSJOR6yC7WP+usabZUPeBZ3seiFMfQUqPdhgnniIozfhK79jOMizc/39Nyb9CaYo8vuN5atsBZf5KkgAuTjauHSd4V43OhKtLc/75aFTZPzCOV+tskx0RRX5OaEh4k7JTYNbw/0+eAi9zmlDs/1lRVFwmdNyl2GCozWsSbWkgyWBMRuebyhkgfE4f0XekNvK5/gKMc86BMBrKK8SoMat8G2jesEQvI3DmKwKXgLftsWKzyrqh/v9vuv7etnv4340Y2CderPvA==
*/