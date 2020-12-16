/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_TUPLE_EXPAND_10032005_0815)
#define FUSION_TUPLE_EXPAND_10032005_0815

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/tuple/detail/tuple_expand.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    tuple(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
        : base_type(BOOST_PP_ENUM_PARAMS(N, arg)) {}

    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<BOOST_PP_ENUM_PARAMS(N, U)> const& rhs)
        : base_type(rhs) {}

    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<BOOST_PP_ENUM_PARAMS(N, U)> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* tuple_expand.hpp
915Xv2bJE2HqhH4SYl1Vteu2KhbDMzxEpsuyzMm9mCdMeqSK67k78P8TIKWofj9upJXH+iwHkZOwJAkDESYFq/XO1x5uR11QtLmzDX+ct9wb3iNoji9SFrjCzbgXoKjKxaMNO7ocj5h83GNeGbiBEAWTXVila6UKVJ2Zlb/PV5Pek/MddGatHb2J9LFyl09eNDPG/nNxYldM/9xwE9chDk924XYgSF1L7OH89du7Yk3JPbJ3Q/AKZKzxTtt0FIJ7jddHMg/ltfN9OD3ZH8m5xvqgirvMNeb1dL0846kTOvFt76u+bgV+gQzGd9bMPue5ZZ65iR/m8q2HLR1qfRLfITGxJ3gUhG7MSwab6Ca8N9Cyr35rwoxX9vPE44lfXTRn708eMWU/L0h46ueeo2QjHPcMrH7SFQ4XuRuwpTH44uouzfNw5AP44OLJ5dWdjdepllhUrVG/LQD5fv8Hff3Bu+a7jjXBevjGCUVCYL3nhBg20cLo5QeMf5me7MbIsRyJf+nAwUQAHj1uMJ+bamNwDb/GHJ2WGCSXdXApjgsfspfQl9ZgHI7vMI7MfBbMzYsyCEXIus3X2fpfPBtM+AMWRpkbeoHDupJVcTO8o4/wchaUUVCWXs6ky1Z3p47keQDob1Avk+sgq8+A+qHWRxIvkFZVE/+xjk089xhIF6HDWGWslgWwrf4Dfu6a8E+dUuPvfg0EpeMm9qa3Ke1bhebU3U57pv1csEAkmV+Wwf/bThdGZvuInSApvTRW7WNpbZveZfqDxGh3z3VFDLpjLrFgaQVFbEnk+mEWcR45EjvEB2Ufq9rJ7mk+ZMSJXJoQiRc09QsY6m99v55gIO36lEGr5yu4RzktaUoNKMS2hvSVPSYd2xm2jaN7LTq2sUbHNYrB9oXxdvsIHdvWw+q1A/aqo7B2AJP4S9V3vFPOiBkJB9vZplwsEpD2tYF/6WXQx+jzI0+Vaw9ViesEqjjMwSU196/DiiefXOPPfkHiN6HGVBtZ26syHkL2JFsSt/TIGgfBpoA7N0Sh0idrGU98iBETBivfSiE8n74K55Uqhdsay57Tha1uR9LYx+p1lM88FLCDiyMaEz3U6yw333p/QxZMFM4PL9Tp29aY8m0mZmPThGnMzOslRhL66ypfqyhIhdHpv/7LKVku47s2lnWZnde0Iz9HGpS3op7X+Xtt/cEyDRvwev2gavq1LZWhGxp391tt3NbKFhSvghm4s66NW7kLIiuHy7U8TNPLGhzJPgNTPrlKN1SpN64NzxGYLq/RD5Wcra1KWVWxately0vnA/uexmId2dZ2X0FaNaI3KppcsNrAscgGHfOVeclDP7rttSiZ+6zXxIQf/Ln0y7BOPoKrvuq18CfIObz6XhkBVNkgFS0CX38YeaBnky1sa6zkTe2FslY01VTkepo6o3RI9nnqu7yvE3TUup+K31SVUfqfXNOeKWlGu1Mo9esWLNSAz6nlzihcR97Lc7G1rLndMKgWztfV2AWqV7aILka0RPI+t+Z9IeW9JeNj6zQwxWf5BXnPWy3Xs+RSZLdMoXio/zBlppZMiqQyn13zlK28qdmsdD2stmFR4SuHAr9iuZ8xvusikDxHD0J/Vtk9GslwaKMMX2XprriJWsSebdtpw7Ferkhs5ZvQvtXmmzYP6+WaJbtCoVzM/5HEaf9St8eekf/blhyKpOl6ZC3zkiGzdn9YNm+25BFUh32XDVnaRZr2vcuSR5HEPpT5PlMmhMhJB2DK/JAlkyK703zFlLm8NBoa9fGTLXmIMoVhWX9W4aUrb+ri5/Bb2wfdbclXKBRc7Tklxrp9lEeL/dOLRVmfo3zFEZvmLy5GeXjamMPehDHVG3A=
*/