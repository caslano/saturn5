
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
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
RP0lcQDjPRhTK7996w7FrbhaR826S2R5Hw/i30pDbBdGxEKNDdnaI11+955a+NVTsi5Q8fjciu3sQcedxZ3IlsbbloRiso7QS0aUKo4krIO+ah5TMR53XOlw42rCscfHUBRBsDvjjyP3h4/96ufFBIdZgE63FoRu2shhVcRkcM5ms57D1Ub8Js4T67B4z6DyBjowZdd0m0ppgw0I3s2x4kz2+1aptsGAnd4BOLG52rhAZz2niecNgNxZsh6aW15JXeGxnr+q5g3gvmfNNfXXB3lrX1N1wehHuat1O9aYop8Vlm4jcpXomdLvZF4HnI+dUzzIXn4hXXiokOP5MClUJwOsscKGiDeSz4fs24uIDVTXeN8rF90SEmWxRBQNnovrCUKoRF371U1NoLuBw8DHCW8Q7uabSyie6q2CdaF2wGbBSivQygMTfKmQnQIMPzpc29TJjbHLKf+hAJyfGao2or3XU7V+0hsVLRtkMoqvKH94hMVM9kEUF6b7zzs61gjhmZRSRfGK5vJx8b/ySN5aHg18I3uJW0CHB+TuTk2IIm9LdN/fPl76w3WjzXT6V1jJfdfPGqcE81rVQdXB+Og2/aA0pOSD+py/c3zIpw6bR/I80COuJ3Hg4tLBKSG0sdvMgVvaDNNcBmO0v17OX511JPOn3a+QuuJFAm2QTOzYuISzqPGgqw1dgtuL3BOiPSyTJfnXF3jlBN1jO4tW
*/