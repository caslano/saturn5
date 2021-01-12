
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
4vDiTaXnvbugBDXqqbo5W/QuUHrRZCJhRbW2ISpt2y/lx/4uqxVPpi39bVb2/i96Z2ffBbGLc/8X/3tfKJ1INGoV4dqeLDoDVXvV1DS2oaKmqjbdYLka06XqxjzRG6r0UGtwI47bkdKmlX3/U/wKPnJ4TotU1UXSbrXnr09n/VDpe0Q0n8zTrPVuoxq1SF/An+FpeVq7FCl9qr5cK5p1eeVX3clbbQ16+6dDRW898VlYk6+H
*/