
#ifndef BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)

template< bool > struct msvc_type_impl
{
    template< typename T > struct result_
    {
        typedef typename T::type type;
    };
};

template<> struct msvc_type_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
    };
};

template< typename T > struct msvc_type
    : msvc_type_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else // BOOST_MPL_CFG_MSVC_70_ETI_BUG

template< typename T > struct msvc_type 
{
    typedef typename T::type type;
};

template<> struct msvc_type<int>
{
    typedef int type;
};

#endif

}}}

#endif // BOOST_MPL_AUX_MSVC_TYPE_HPP_INCLUDED

/* msvc_type.hpp
/1//f+Prr+dyJ1pr4uCbRxs2SAWZNsp/XD6HvzLLGTfocFzb9TbFzvLQb8w+tCx6urSTXlx1R3XwUyNjt9OZ+WMbnzbX7uksEjPsz//NR8W80he2W2kPlt1ReNw3p3FLdNadMwsFxufEH3o1L1k8XeuuSbuy847Nlk1lzNG3N6+ktAwEHteQ2m/hcrpmm/Th2Zx1yzq//Niw9l7Xts8imuvbFd9bfvpwwOvGjNtpgY0P9trO+HwxxrWyy9jXV9vKS//OGw+FlG71+of3Lq255zakkN822O38VGXXkh1nWXnKFo9Z+4f8Vp/91QxzAceu+7WM3/EKsYPTXxtsLzlt1IpveT7bYPm5Zw+vGazb/OD8tyabA9tn/n/+/4fnv7dj6HDP1pblsWvrtr5dxLjVe3DRxpfzzY+feZewyOPV4lyPtTO/n6Kqthjbfew0I47u7FqjMWePkOJyoDBj8PPs/dxVJ9u0mqJGv8V5D2xpkO2sKtoyFKw6p3xCM322RLPG6Ap8VvGJI2/z3G1Wl294IWPRa/rVjf+VbhR96hcnq8ccjcUceoKGRKxWJb7NuHoyxavgW096GmfHrVavKPP3a1Z8j7O++YmpdjpgkC6+WeSXs8x0dZ/s3v79ysWpftPwgv5WpSzmL1pGjDecZ1qvGnu15FhYucNKvV9G5XzZqD/k8X13YyljA9FRkHnB8hbvkkVd3P1fX3m8t9ey7MLmBLtXr3/Ixxwo3hAod+X/+f9//v/n8k8n3+f73zzX+P/Hf8fh6j87xNvdOyRifUzCX/57SNia8NC1f/7ncLHr33/vgrx7+B++/OnbF+vWrSO2bdtGmJiYEB8+fCCqq6sJFotFXL16lXj9+jXx6tUrIj09nQgICCC4XC7x/v17QlpamvjVr35FCAQCgslkEsPDw0RUVBSRk5NDuLu7E6qqqkRJSQmho6NDDA0NETIyMoSPjw8xb948QlNTkwgPDycOHDhANDQ0EDt27CAuXrxIVFZWEllZWcTmzZuJwcFBgsFgEPfu3SOcnZ0Jc3Nz4tmzZ0RISAixbNkyorm5mZCSkiLU1NSIU6dOEX19fYS9vT1x+/ZtorOzk/Dw8CCCg4MJJycn4smTJ8QM/K31kiVLiEePHhG+vr7EokWLiDW4Ktfb25vYs2cPQaVSiaNHj+Jm7yuJyclJ4s6dO8TZs2cJU1NTYsOGDYS8vDxhbGxMfnjhp0+fiKqqKmL79u3EkSNHiN7eXuJn+KS+1tZW4vr164S1tTWxZcsWYuPGjYSoqCgRHR1N1NbWEmVlZYSFhQXR3t5OKCsrE7NmzSK6uroIBQUFYvHixYSDgwMRGhpKPH/+nFBXVyfk5OQIDQ0NwtLSkqDRaMSxY8cIJSUlfOiSH6GiokL85je/IXR1dYkfP34Qbm5uRFtbG3Hu3DmiqamJqKmpITZt2kRkZ2cTenp6xO+uQ3z79i1x+vRpYvny5cT379+JyMhIYv78+cSZM2eI+/fvEydOnCCSk5OJoqIiYteuXcTPf/5zIi8vj1i4cCERFBREaGlpEbm5ucSLFy+I312fs2LFCuLBgweErKws8etf/5r43TFnzhyiuLiYGB8fJ+Lj44nu7m5i9+7dhIiICPHmzRvi6dOnBIVCIfh8PtHT00McPHiQyMjIIJYuXUqkpaURM2fOJO7evUvMnTuX2L9/P2FlZUXExcURERERxJcvX4jR0VGioKCASElJIRobG4mXL18SCxYsIPLz84nHjx8TBgYGxK1btwhbW1vixo0bBI/HI1JTU4lDhw4RMTExhJeXF0Gn04krV64QYWFhCIwZ8e7dOyIxMZEoLS0l9u7dSxQWFhJr164lLl++TOw=
*/