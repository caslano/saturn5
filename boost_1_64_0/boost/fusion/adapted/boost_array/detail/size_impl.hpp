/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_27122005_1251)
#define BOOST_FUSION_SIZE_IMPL_27122005_1251

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::int_<Sequence::static_size> {};
        };
    }
}}

#endif

/* size_impl.hpp
wT/SjuetnS98AdRt1x/+INRu5wt//414TiFOwSdD3fZ6gN8Jtdtx4bvdhGepzRN+KtSN2IXfAjXbdYa/BuVxrnNzzBwHtdp1g18B5dCmAH8eake52RAzn9qAcjtf+HKo084X/jjUavOHf+QW9G/zhy+AEjZ/+INQo80fvtfXYiZEn0n4CBujfRa+CnLs/sI3Q2XbHr7XrXju2zWEj4B8e33CV0Flu4bwzbaN3SP4XgW8dti5F9AeKtv+C2gPZWzOBbSHPJxbKqD9bejT5gMfAbm2f/gqqIDyAL7Zltv+4Xt9HTnbfOAjIB/lWfgqKGPzh2+GHJs/fK9vIB/bHr5pI8rXY+++ieflt3A9IHa+HTPnQo2IC/A+HbhmbBv4Vihl29yOZwLUhDj5nZj5MtRjr1X4Y1Aa5ea7eA5BCcQZ+JWQQVyCn3QHrn/EHvxGqBlxEf4s5CIO7sR1C+UQh/Drv4e52HPhR38f9wviLPwKKG/zhD8PtdpxizFzOOQhTsOnQ74dC/59qM32Cd9jE+5Nmz/cg9rtuPBRd2GdEfvwvX+Ae9D2A78FKtpz4YfdjesNsQvfBnXZNfkhxoJCey78Uz/Cul2H3Kx3Yj0Rp+EroJLNGf5bqNuu7b1YW6hs+7kPz/D7sZ52TeCpB7BuODcDvwpKXIdyePRB7J3tE74NakBc/nHMfDjEOYg9+C9+ij2y8WbMHUrbNvAzH8aa23J44mdYT8Qp+BNQBrHzCL5mgHKIk4/iWQFlbQ7w5ZCLOIBvhvK2T/i+XVhD2w/8BChAnIWfD7XadYD/BPIQl+DvfwzrbNvDJ0O+zQf+DajDzhH+O6gNsfk55gV12hzgU6CibQ+/EwoRh/DYL7AXtk/4FVDJ9gP/wBasrV0r+CioG7EL3wglr8e58D9ABrF5HK8LUAPiLHzNVuyF7bOE1wLIQbnzJF77nsLaIU7/GnsKNSIuwF+HPMTJp2Pml1Dexs/EzLFQk+0TXoDa7bjwT3RjPRFn4EugHGIf3vos5m7bwPd/Dntqx4JfBfmIi/Cm36Cd7RN+FxQgLsGnbsN+IQ7gm6Bm2w/8GSiNuAzf83nsu80N/kUoY/uBF6xse/jvX8Ba2XFfjJk3oCLiVBlf+0Bddq1ewpr/Futs84c/DYV2fX6H6wfqsOXwfV/G3tkYnvk99sLOET7iVaytbf86rg372/o3oDwSN8F74qYBcXmfuGlPxo2DOHlg3HQdGjcJxJmBcTPwY3G8jmHNPx43Jx0RN4Nt+ZFx8xi0GnHqk3GzHFpmzx0SNyOgSYg9+Neg0YiL8LpPxc182wY+D9qAOIDv9um4GYY4DX8DmmH7/Ezc7JOOm5G2DfwZaCni7FFxc+IX4mY94rA5jr9diJt1iM1xcTMcGorYhb+QiZuNts3wuPnIiLh5wM4X/ij0sJ0vfLeRcbPF5gOfBg2xbeAPQIl27C/84JPiZpvNDT4fakC5D38MchCX4Zd+JW5etmOdEjf7jsJaoTwFP+1U5Ie4AI+cFjdP2bHgJ0FNKHfhd0MpOxb8Y6fHTTPiDPwmaDTiIvzX2bjJ2D7PiJt7oEl2XHj/qVhDxGYm5g6lbZ/wb0IbEYfwAXmsle0H/sySOL6mQJtz4viZGuZj53Ih+l+ONUfsXRQ3D0J32Hzgg1cgP5sPfNLKuOl3o/3ZWdy0roqbvojL8MY1cdMHsQe/Zm3cxG05/D2XxM2rODcJHwW9bMeFPwo9bPOH73Ep5o72Wfgel2GdUZ6Gb4C22PzhH78c62ZzgF8NPWDnAv8N1GTzWRc3x1wRx2eV4TqBPwRNQlyC7xlgPW05/JT1WEPEmeuwF9djrRCn4EffiHVA7NwUN20bcI0=
*/