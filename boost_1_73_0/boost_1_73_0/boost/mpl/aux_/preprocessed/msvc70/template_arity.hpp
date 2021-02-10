
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
TCtbslPXK/kWdf7FXOFQpu+rP1j1z3CKQwnnlIJe94Ny6PcoscH3QhkyEIo3Bs9YEk2oeEhSGbc9sMXg/Hd+6B9QSwMECgAAAAgALWdKUjgeVF6PAgAAewUAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q1MDNVVAUAAbZIJGDVVFFP2zAQfrfEfzh1QpPQQtJStjUykVhBwBi0gghtmvbgOpfGIomj2Gkpv37nJC1o4oHXPSSxL3efv7v7fNyisVIYjBhXZarp84ibta4TE7HLOJ63L7g4j7vFdHZ7ez7tN1WtnzavlvBNGCVBNDZjrcE2ZYk5K5rcKsb9F2Tud4exD3CP9Qprz6gEGa+xyjf027RGWSQRk5owpFW69ApdKqtrin71n/cOHV1/eDiEURDAjVpmdgOpKhFUmSAme2yPInfePBFW/BM0uwazNjLXBtmZsBhC3OAnCCZwq1fkMQxgOA7Hk5B8L25i1nEPwRXR6zj5qXhE9kOQ4UYnKlWY9CjDI/jelO4cQhmFw2CLch6LZQiD0TAYHXuJ/OIdTcafR+PJ1wEjwh3Nlq3MUD6+K8//Iqs+He73XScxTHOFpe3FINvNTg0Ry6yt2pfXKW+rg4girdY5KAPrTFjaQGNcPYxFkYBO
*/