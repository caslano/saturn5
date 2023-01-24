
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
Lj/bGfYc9ef4PogIgHeXckxtTJFC5WEtMC+bpc/A+KXNXEC/NlXnB59Hrk4JY9RYNpgmHAsuA2eGW8PT6MQRmocWWI1q4V1Znw9QnRFvEcIWCBKHsvx2sPx+suCerM+E34Q1ZOAP3DlSeIoe1okXGpa4T7o1W66XDT6sWVpLrT0eJwtqUQjE7XbEOwiecqvhbWF4K7O5JygLtHgnc67ADYEkLwEmfCDjLFBh8YYLb0n49kFbicjCALWNojXzpb+SOUii3GHAQpa5gUylI3tupxn0M3HB6QLLsaSdewnH4rs2IJubkRiWDVP4NhNrqyueomBvyywJ3UkaHv4wqJjwMUsoV640uQs7E6M7I2QVHkugMPQjRwLHhUzNIp9q1ylmOgbkUpDlV+qmGo62L6a97cqZGyWnM/AhPtdMjF92ZKxzVyW1B1SYw/LMx+7HFOMGU+HmeRkISW9S+KqLesyUlAXOzm3nFmHrCWMnuC62ECyxsKJ+g+gI5JITxxZneMApESWagv5DrrbiXt3OGFr6i1ydmOSKB/mbXF1B8Fe5uuN1Bi+boWHQ3+XqD3+Vq0PO9tl9LIsh7/4iV8+bMtv2lk9L6JcbSsut7RZ9Wpdvz4LX5dEU7fAEdfqmK5n+Ra7+DeXJ+ZX7yJ6Z7wXx2xzOKaIBhUNV21Dyzg4IPhkVjl6cBKaIfQu7fROQHJgkptQdu3biBU1arHyOEAuj
*/