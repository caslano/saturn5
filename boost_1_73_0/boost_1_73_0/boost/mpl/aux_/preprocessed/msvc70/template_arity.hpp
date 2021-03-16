
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
L0PxdZLmnvlYU1ohJuMSV7ZdYjE4msv16uSTrThHdD13kYlXPG6H3TJDsYF/JxOM0+9lNH1dxe8YBMUeKhSNHCi1UZ/6QHMIvZY4DNeIQJAPMjJJpyM7jXREg0KDJ9vFav/kcensLsIVcQr3KYwtRJBY9RS9rFCKU73SrJ/WH/XwZ+C8s9rht1vMPr/idFttxFYa/5v0nlRnPEWjuj7hZowi4nR/CSz//GBjIA7WB7nXs0AUZ6f1KUF3rP0whzo=
*/