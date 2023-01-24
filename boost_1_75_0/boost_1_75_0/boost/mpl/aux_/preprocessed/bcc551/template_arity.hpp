
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
Wn5mRpAv+CN/lOoFBjQl7U/JV21SRp0Y/xKuLynDU4q64HrqGAuRF7eTuT2XqZeygEZqF/5mVev1oFA7WQ8IPUh4C32AUy5O3PQxyK4tfAZmFia5P2VtgP4yF9vqwZ/vpXdXx3Sjcgs6sRmOLaMQ2ik6na89P4ezjCVfNWbZC15qNYSUZhKJLzqOqAlMy4uJ37T53bZPS07eC4uDTFSSwZpXCKceWg5z6LP0HycDXu4n3hNzahJBa8Kv/aCtHvQFufVxS0Ple7xHAkyhGwVDW3eAW5/nFrKlX+5V7lWzy0xPUIFS93dbWNmJvG4TUoIYfxH+iXaTrSbmkCO7Rm7elfShuzAlyjeqjG/R5CiipY5Kn2K1x72ZGq6tZ1n5S2zB3Kss2MvB0QTdqBolOtSljglEg9SR/qr5WZsL6pU3WlaOJ3EFKBJm+pq+B9WFKxsKuX+1KD59/KYXMBIznLjpmPGezsdztTkWUiryEJ0b5ogjGqiquul1IDSodsoxfV45q+Jlb0oF3pkdWFy1OZBqyB60FxfdU+ecbmb/lcXZQ6yNacS6E2UgQ2jcOu6L9BBRbX7tjjnVrK1HIlqNLUhfX5VF+h81t7fcD6+MXwowkLa99ncu1FlRFbNlKQCqtC195bSgJWGVdosLdJYDgB5hM1k/ZaUjjs4WCCRxvop+zynDnstwf8VCEorFKRxAb9+5K+xlYBtpkTBdYB7z
*/