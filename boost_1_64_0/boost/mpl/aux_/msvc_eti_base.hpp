
#ifndef BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED

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

#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)

template< bool > struct msvc_eti_base_impl
{
    template< typename T > struct result_
        : T
    {
        typedef T type;
    };
};

template<> struct msvc_eti_base_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
        typedef result_ first;
        typedef result_ second;
        typedef result_ tag;
        enum { value = 0 };
    };
};

template< typename T > struct msvc_eti_base
    : msvc_eti_base_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else // !BOOST_MPL_CFG_MSVC_70_ETI_BUG

template< typename T > struct msvc_eti_base
    : T
{
#if BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304))
    msvc_eti_base();
#endif
    typedef T type;
};

#endif 

template<> struct msvc_eti_base<int>
{
    typedef msvc_eti_base type;
    typedef msvc_eti_base first;
    typedef msvc_eti_base second;
    typedef msvc_eti_base tag;
    enum { value = 0 };
};

}}}

#endif // BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED

/* msvc_eti_base.hpp
ZdAY6gx7hifDi+HLiGDEM5IY6YxsRh7jCKOAUcKoZNQw6hkdjD7GAGOQMcqYZshpq2trarO0f3cPESttD21vbV/tEO0wbVxtrp2gnay9S7tIu1y7SrtOu0m7Wbtfe0B7SHtYe1J7WpuqQ9fh6gh0PHV8dAJ1gnRCdOJ0knXSdXJ18nSKdCp1qnVqdK7p3NTp0unRea3zTmdEZ0xnUkdEl6JL01XX1dHV1zXWtdC11/XS9dEN043QjdON103RTdfN0M3WLdAt1C3WrdVt0O3W7dN9rTukO64rwqQwpZgsJpvJYVoxuUx3pi/TjxnIDGNGMdOYWcxcZimzglnFbGQ2M1uYncweZj9zmDnKnGCK6knpKeup6rH1nPQEekI9b70QvQi9KL1EvWS9FL10vXy9Ir1KvRq9er1mvVa9u3pdek/0evR69cb0xvUm9Wboi+vT9VX1WfoW+k76Qn0vfR/cGCpVP1M/Rz9Pv0C/UL9cv0q/Qf+ufpv+E/0+/XH9CX1RAykDmoGiAcuAbcA14BnwDbwM/AwCDcINIg1iDJIMUg3SDLIM8g0KDSoMqg2aDFoMWg06DXoMhg3GDJRZqiwuy5blzfJj+bNCWFGsaFYcK4GVwspl5bMKWKWsSlY1q451jdXMamf1s4ZZIobihlRDuqG6IcNQx9DC0MmQb+hp6GsYZBhsGGoYYRhvmGqYZ1hoWG/YYHjNsNPwiWG3Ya/hkOG4oQhblC3H1mEz2Xy2BzuYHc6OZMew49lp7Ax2FjufXcQuZZezG9lN7E52F7uf/Y49xB5lzzCiG2ka6RtxjHyM/I1CjMKNooyijeKM0ox2Ge0xyjMqMKozqjdqNrpr1GPUbzRoNGI0aUQ3ZhlbGFsZOxnzjb2MfYz9jSONo41jjJOMM43zjI8YFxuXGJcZNxjfNR4wHjQeNZ4wnjKmmNBMlE2YJhwTrom9icAkwCTQJNIkwSTVJMMkx6TQpMKk2qTWpNWkzaTbpM+k3+SdybDJtIm4qaYpw5RnKjT1NPU2DTUNN4013WVaYFpkWmZabVpj2mx607TDtNd0hpmImbgZ1UzVjGGmb2ZqZmVma2ZvxjcLMAsyizFLNEsxSzfLMcszKzArNisxqzKrNbtm1mR216zDbMBs0EyUQ+FIceQ4LA6bI+C4c7w43hxfTgAnhhPPSeakctI4JZxyTjWnidPGaed0c3o4A5whzhhngjPDnGrONGeb25rzzP3NA82DzCPMY80TzZPN082zzXPNi83LzOvMG81vmreat5t3mfeavzYfNp80nzIXsaBYqFroWLAsTC3sLYQW7hZeFsEWoRYRFtEWcRYpFtkWRywKLcosqiyaLG5adFp0WwxZjFtMW1AsFS2VLTUt2ZZcy0DLYMswyyjLGMt4ywTLJMtMyyOWhZallhWW1Za1li2WrZZtlu2W7yyHLEctJyzFrfStjK04VlwrgZWHVZBViFWEVZRVnFWiVYpVmlWRVbFVhVWd1TWrVqsOq0GrEaspqxnWNGu6taq1urWttbu1v3WAdZh1pHW0dar1Huts6zzrAusS60rreusW6w7rPusR62lrCleZq8k15VpxeVwB15cbzo3hxnITuEncZG4qN5ObxT3CzecWcWu5DdxGbhO3k9vDHeAOc0VtxG3kbJg2Fja4vZoNz8bbxsfGzybQJtQmyibaZo9Nlk2FTaVNnU29zV2bdpt+m3c24zYzbEVsxW3Vbfm27raetj62wbahtvG2KbaZtsW2Zbblti22nba9tiO2o7bjtqJ2UnY6dlZ2XDuBnYedl52fXYBdiF24XYxdrF2yXZbdEbtSu1q7ZrsWuza7Trsuux67Prt+u2m7Gfaa9kw=
*/