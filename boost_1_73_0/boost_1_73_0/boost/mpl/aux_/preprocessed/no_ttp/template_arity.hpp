
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
NKwlF/9nbrE8+/9QSwMECgAAAAgALWdKUsqS4DmxAQAAbQMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2MTNVVAUAAbZIJGCNU8Fu2zAMvesriBY+OkqXYQUCwTk0G9od3CBOu2Mg20wjVLEESU6Xvx9lx3EPGTZCsCTq+Yl8zxYBfaikx4wJ1ewMTe94+jCu9hkrfmxWrFYOq2DciQk+Hgneo9ktu4UC3RFd6lWNTDi0+kSAWgZZ7bF6z1i9GAIocniBIcZVHzl0oBzyfJ7nIH1b0v0sdR+LfkTQ3d8JZvfwUzYRAl+m0ylYLalOpXESfgeiSRf9+AfN13tYYgWzgcaZC4fgnxoT/NxtJ8ODVtiEswxVtyGI78TJmN8FSy8MW2FJ1p7FotOQFOuH5dOaa1VGS3h8fLubTawGQlrpEJLVryXX5u1yFqURfCQC0cgD9r7BxTdwGJzCo9QE4D0CRGUOB9nUGUtTchWq1ultX/M27tPUtuWVgwmlIW0heSm+r+cQm5pznjw+F5un1TwpisfV83oT5+2VajnxqsYjkZJE/FKDsIa+wv9Ug6DWmQq9v6rImIylx6Rpo22frqCbz+50vr2iU7sTRF9B7gI6CHuESAl76aFEbODG7024YeLYYYmC
*/