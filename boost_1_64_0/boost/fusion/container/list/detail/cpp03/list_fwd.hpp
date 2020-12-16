/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LIST_FORWARD_07172005_0224)
#define FUSION_LIST_FORWARD_07172005_0224

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/list/detail/cpp03/preprocessed/list_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/list" FUSION_MAX_LIST_SIZE_STR "_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_LIST_SIZE, typename T, void_)
    >
    struct list;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* list_fwd.hpp
1bIfyjXwQHgtjIQ1MBteD4+DN8AyuBKeAm+C58GbYTVcBR+Bt+jKJ2Np4PKZIOWTLuUzUeIlBslvmPy2EU+NEy3tez+JFwoHwp5wDOwFJ8P9YTY8AJbAA+E8eBA8F4bDa2EEvBlGSvkcAjfC/vBNGAW/hQOkfKJhbzgQRsMYOBwOgmNgLBwHB0t5xUm7j4dnwiFwOUyAN8HD4WqYCD+ESfBTOBR+A4+Ef8FhcD/KIBmGweFwCBwBE2EKTIYj4ZIWjsG3duz9n9yf3h6Db37v+lV3Be9wY/FN7V0fvmrHG5NfTx00IF3XUE9I+hp7XN4OdrCDHexgBzvYwQ52sIMd7PDvDdth/j83DFa8/+3y/YfK/P8qtzL/X1GpTv3Xrtf7rsfFDeH/aNfD833XEw7XX/f4rscnGu6v811PGBzHdXXOwS59Gf8TP+L8AGsLtizS/IiKcS1aUxAnOuutdeLw0OskYy1cq+DT228na70hBr0UTCv1VgXQG67XS8G21t5NAfTGGvRSMS3U61s3sUHmAlyDkkFwCVys1PUZqt48tvVX9c0XBYH85gU6v3mVhe90MaxAuFbskmvV2rXicp8//HLffmhcc+j2Q+up+l3V5qP5vXup1zy5LjnvQLneD/7U03cv/8O0hmN0V6s1KsgZnbdGxZd2XYC0axb606bFdUraw7pZp127yJ82radD0/a1sZpu1mtztlR13Nqc7jtbp1F/lpYGD4m21as+HU+AdEIWaulQhe1PZ1OAdBr86cQndkB+UoKt0wlfpKVDs2h/OvXB1munYs/Yvmun4sQeV3drezIW6uyhJtv7LGiNTVsD2JSzSGcTtbE9bPqRz542zBvpqPkhO/p8D+t5LDvOfI/Wzuv4wqlcrxxxxQ27pj41YNw1M7a+cUlpQdvmdWAqfUb/2rB+Jn95sawNK4HBsBRKPAomcLwrJN6VEu8qXbyQJuLdLvFWS7w7dPHCm4j3qsR7TeK9rsVDmoj3mcTbLPE+l3hbEOmX0V/zxlO6wh9LvAil2mB/mASjYCqMhpPgQDgVDoKzYBycA+PhfJgEr4BDYQ1MhvfAEfBFmAJfg6PgZpgKv4Xj4B8wTebHHAUPgRNgfzgJDocZcBpUz3GBU2AFzILz4TR4DjwWLoHT/eUl/TNstSivPrLm7yAYA8P98ehbBY53tsQ7R+Lp5rPQLwoc71GJ95jEe1yLJ30a2N8iXg/dHpmRMNQfj35K4HhlEq9c4lXo2+3CwPEqJd58ibdAv6axiXh3Sbw1Eu9ufXtfFDjevRLvPom3Tt/epf6SLeLtL2soe8NEeIB+3szCwPHOkHhnSryz/PH4zQwcb73Ee0jiPQxf5Z4i/NQLkRXIWuT5NcEtmkMSvso8f8RqzWbT80WGIJs3dW3RPJF6JETmhch8kEZzQRbDVYjM/wg498M476P5+R5hsYHneKxEmprXUYf453IEXkuZ9XpXxxNQ5m8Y5m3InA2Zq2Gep9H8HA2ZnyFzM/zzMda+0VXmZLR+baTFvAvDnIsVpnkWWxHj3Ar/vIr5Mp+iGvmY9rcN6XV3sGMIkoEUIVXIcuR25AlkE7IF6b6W9cRIIpKBFKy1513YwQ52sIMd7GAHO/zN3nnAR1FEYfwAY1ABT6REiHIUNQhigKBBUSNFggKeSIkIXi7JkQRSzuSiCSA5FTto7KioUVFQQWNBsEdFxX4qIvbYsUdFRcXy7d53m9292esB0Z3fb/ybZd+8N2X3dua9nTWTmcxkpkjSdnj/v6LY7SotSMD7/z0CPn3Z1+8vdvCh6coegEmqPQDTDHzqTV7Fl6wUEO0egMvaGPg4va3nXz0o4ANsa+CbS6CfcUlbA78=
*/