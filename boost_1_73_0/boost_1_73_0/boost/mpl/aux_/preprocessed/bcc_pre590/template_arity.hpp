
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
1I0CFRFDqmmq2w+xMvATMYcdE2vaEd7S2nIIG3Uotvy/hRa2U8jzyLS7bxp3xNRSM+K7r8vkSVGic7d9EPB20L+/O0/9PF3O786fHm7XWUdcM4vOaMEFuRBWZSq7N8ezqzN/so3V3g4b6AKxcEZpsmwvfFtHXQ/pUKdDwU8W/KPF7yvkryWo2+/kZ/3D8ODGPCyOjt6EPwpDLFi8J/dqtB8XmeWx5c+Tz0MiX34SvwBQSwMECgAAAAgALWdKUseABc09AgAALgYAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNzZVVAUAAbZIJGDdVd1P2zAQf7fU/+HUiRdEcZqxTURZK8QYIHWAION18pxLYzWxi+229L/fOU7ppO1h0njZpCjxx+X8+7hLco/OS+FwwnKlK0OPBW43xpZuwq6K4q67weVFwSrTNGbTGCm8MprlfB+Y8/juG3hAu0Y7cqpElltcNlvaLYUXMRsfH4/hbTKGolYO6BKwQWVLAx6fPbTonJgjuI2TjXHIPgmPGRQrPILkFG7MGtJknMD4JDs5zZIELr8ULB6ZQWAyct2EV2KBbNZDzSAA4OmH90mSpMf+2U+lMY1THj/W3i8zzoU2vka7sg2fim8OpdHl7gV2brRGGTNF
*/