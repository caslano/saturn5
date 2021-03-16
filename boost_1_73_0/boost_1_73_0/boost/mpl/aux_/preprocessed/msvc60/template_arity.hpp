
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
MFSEb1JFsmy7Webkj0oP74aCPn52msUj4fVLUk1opFHoasKPhs6zqQm/bkUBfvX5npslxdPR9bFU4ig1ZSK1lWqEaG+bsKrmKlIFZLia/kKOjUo18KdSNfgmEdlk2SazbHB3HaTvkZLSc1/e/Nxs+j728fyOfIGwq81pAuJHvBjNOtC4qW1lPmy7odpW7gRE29uEVYUrlHWtpL+QqU+pEK5EqhDfpHXJsu1mGdRHGhv1+N9Om/0sQMGeNHqOV+g=
*/