///////////////////////////////////////////////////////////////////////////////
// Copyright Christopher Kormanyos 2014.
// Copyright John Maddock 2014.
// Copyright Paul Bristow 2014.
// Distributed under the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Implement quadruple-precision std::numeric_limits<> support.

#ifndef BOOST_MATH_CSTDFLOAT_LIMITS_2014_01_09_HPP_
  #define BOOST_MATH_CSTDFLOAT_LIMITS_2014_01_09_HPP_

  #include <boost/math/cstdfloat/cstdfloat_types.hpp>

#if defined(__GNUC__) && defined(BOOST_MATH_USE_FLOAT128)
//
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma diagnostic ignored work :(
//
#pragma GCC system_header
#endif

  #if defined(BOOST_CSTDFLOAT_HAS_INTERNAL_FLOAT128_T) && defined(BOOST_MATH_USE_FLOAT128) && !defined(BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT)

    #include <limits>

    // Define the name of the global quadruple-precision function to be used for
    // calculating quiet_NaN() in the specialization of std::numeric_limits<>.
    #if defined(BOOST_INTEL)
      #define BOOST_CSTDFLOAT_FLOAT128_SQRT   __sqrtq
    #elif defined(__GNUC__)
      #define BOOST_CSTDFLOAT_FLOAT128_SQRT   sqrtq
    #endif

    // Forward declaration of the quadruple-precision square root function.
    extern "C" boost::math::cstdfloat::detail::float_internal128_t BOOST_CSTDFLOAT_FLOAT128_SQRT(boost::math::cstdfloat::detail::float_internal128_t) throw();

    namespace std
    {
      template<>
      class numeric_limits<boost::math::cstdfloat::detail::float_internal128_t>
      {
      public:
        BOOST_STATIC_CONSTEXPR bool                                                 is_specialized           = true;
        static                 boost::math::cstdfloat::detail::float_internal128_t  (min) () BOOST_NOEXCEPT  { return BOOST_CSTDFLOAT_FLOAT128_MIN; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  (max) () BOOST_NOEXCEPT  { return BOOST_CSTDFLOAT_FLOAT128_MAX; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  lowest() BOOST_NOEXCEPT  { return -(max)(); }
        BOOST_STATIC_CONSTEXPR int                                                  digits                   = 113;
        BOOST_STATIC_CONSTEXPR int                                                  digits10                 = 33;
        BOOST_STATIC_CONSTEXPR int                                                  max_digits10             = 36;
        BOOST_STATIC_CONSTEXPR bool                                                 is_signed                = true;
        BOOST_STATIC_CONSTEXPR bool                                                 is_integer               = false;
        BOOST_STATIC_CONSTEXPR bool                                                 is_exact                 = false;
        BOOST_STATIC_CONSTEXPR int                                                  radix                    = 2;
        static                 boost::math::cstdfloat::detail::float_internal128_t  epsilon    ()            { return BOOST_CSTDFLOAT_FLOAT128_EPS; }
        static                 boost::math::cstdfloat::detail::float_internal128_t  round_error()            { return BOOST_FLOAT128_C(0.5); }
        BOOST_STATIC_CONSTEXPR int                                                  min_exponent             = -16381;
        BOOST_STATIC_CONSTEXPR int                                                  min_exponent10           = static_cast<int>((min_exponent * 301L) / 1000L);
        BOOST_STATIC_CONSTEXPR int                                                  max_exponent             = +16384;
        BOOST_STATIC_CONSTEXPR int                                                  max_exponent10           = static_cast<int>((max_exponent * 301L) / 1000L);
        BOOST_STATIC_CONSTEXPR bool                                                 has_infinity             = true;
        BOOST_STATIC_CONSTEXPR bool                                                 has_quiet_NaN            = true;
        BOOST_STATIC_CONSTEXPR bool                                                 has_signaling_NaN        = false;
        BOOST_STATIC_CONSTEXPR float_denorm_style                                   has_denorm               = denorm_present;
        BOOST_STATIC_CONSTEXPR bool                                                 has_denorm_loss          = false;
        static                 boost::math::cstdfloat::detail::float_internal128_t  infinity     ()          { return BOOST_FLOAT128_C(1.0) / BOOST_FLOAT128_C(0.0); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  quiet_NaN    ()          { return -(::BOOST_CSTDFLOAT_FLOAT128_SQRT(BOOST_FLOAT128_C(-1.0))); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  signaling_NaN()          { return BOOST_FLOAT128_C(0.0); }
        static                 boost::math::cstdfloat::detail::float_internal128_t  denorm_min   ()          { return BOOST_CSTDFLOAT_FLOAT128_DENORM_MIN; }
        BOOST_STATIC_CONSTEXPR bool                                                 is_iec559                = true;
        BOOST_STATIC_CONSTEXPR bool                                                 is_bounded               = true;
        BOOST_STATIC_CONSTEXPR bool                                                 is_modulo                = false;
        BOOST_STATIC_CONSTEXPR bool                                                 traps                    = false;
        BOOST_STATIC_CONSTEXPR bool                                                 tinyness_before          = false;
        BOOST_STATIC_CONSTEXPR float_round_style                                    round_style              = round_to_nearest;
      };
    } // namespace std

  #endif // Not BOOST_CSTDFLOAT_NO_LIBQUADMATH_SUPPORT (i.e., the user would like to have libquadmath support)

#endif // BOOST_MATH_CSTDFLOAT_LIMITS_2014_01_09_HPP_


/* cstdfloat_limits.hpp
FQxuOibPSGsZZ8+sppOjNdTWnX41U/KNnaBtsBWUJ3KAuVJQD8Ivc8LUXika4+E5rHOx61vr546RC7GOCqUnDos4GCVZX6xAPerTejPesNf1K9qWKLTApHfvYoo8EJu1extOKjl1HGBefKsJC7X7bZ8fNuwa8QsuS8ynEMi2n5PFchI9B+AMcZqiGuuMG7INNeY5u1FRIR2qezZQLqqhN7sa78bluKYPF7Rguxlsz+W6KpmOwWgCDRVbV0Nui1baEND3VdVtdRyp5EN7No5yXA3mSq1/a2hjYxzVXHkinM1E3wKwXeZZa9mbwq38PJ54r7+xRgDwfwCAQ0tdd1OwKAzM3LFt27Zt6x7btm3btm3btm3bRr9/2j60+5I8ZSaZZHcDHNfmIIONkGsvzbSlhduEUHzcwA69FeCirb6gGlEJ/seB9o/W0e26P+vWKiRQ2SKKM0yNc5dtNsJc3TodES1zavsJUqnMwLIFD0fgqfQD2KjTCAaK/ge3HvPcotkttABPWrSkyiItBN+ujYjHdHj6pfwOUrQgQ25NySM/ggYLOYLxC5oTM1/9Cf0cWmi+BUzDFbG4Qf42E7b3ZKduhMpR7HlMZjQsN5v5JuQoYsrkvu35wBg1vMS0Lp4rF7jgj24GX7QzPYXRT2XNdQ6TAjt/mQ4JxwFzrRbOxhaXYbUqmsEQFmzlxXhYOK/trmnMU1o/9nbvWVmMZlgPhHcgh0Ryek22d7SyKe6bTBxx/FD60Rq7HRlQMKsfz7RNEU1dkr0guQu0ceNQPdrxmItDX9JM6B76ZnHjKTydrq0AFRJwoaEGk4oLwO/zOqrEevYhNA6upaJiaY+FQ/RUgCy/Iwlpxb2yoBVs5/jaIAd73ISXLVXJ/bX0Bk04goG7tgvlxrQPzFkK/UPdFT51kNskPLJk0bk09c3GkwOnvinzuJhWM6XIxrRH72fNzK2bcKFLrEGuQ84jGDtLBrWzsptTtyuP7dFRewPi4KLfTSKWbfiT1P0KtsSjs7v3YCWmo61O2+19TI1Uh61bd3eHMeOVxxujEaluOiKcaLhhv1ohzQTeCHc4CyWPDXTbJd6GkibFx+x665DxQypOydnvToWLpVgtLQV4tQC2gRWXgb1tZIBgJBel0BN3OLIhTYKxOMhfNS4dBskJtuT4GrzuY662gnkx8gTJOxSMFCrAUmKEl6SNSBSPLe5SWt1injtPSFGfaDLupoUOrJbK/IVIw1vU6+f+pX9JrxtalQW8b2ZCoXXsmWoi5Y653m2LJsja+z4NaPAjKuCf5R3g0y7BwlaI27gU0Sn4nCN5sfere6RzI4PZrEhgziQav/2pLOWy4uyggH1fJ4eUEwMAVlF+mMMjFvOwPHJDSDe3xpLe/TCWuKZSUsV2v0upp3bc7uN4WZVqhKfT61nJeUNKwJJEUPlE1Nzt6YPrbk6jwuJDekZ31TAjh/RIj0LvitsJ6OHVjMOy1Mot/ut9lMNmF5zH9fuG5lr+O4Rvricjffwtc6pL1N2g8o5Wayt524UQzNnTk+r1sTG8Obbav1IF3iDa5GT3AGfGLbsRXR6jDrEXxqyvoxjRN24PpJ3J2EhBsQTjBASqJWCEInYs39433qq8JpwhLUbomo94OjObBts6+g26kWSuxKN9MKTrnkVFhb3bXWyJzKMcDOkC1ssUm5ue4EIrp/mXOafst1U9lteRbW2152jKKzQ/VStn5G4OeSWBFMRSebgDdI/n6tbi2LtKOGJtFUNVm/rlQaxPS2eVy7C5H2MulmFh9ld4ZIpYTXfcKE1LEbvFzuzu1FhGTmX14ERld5jB6sp+RqnchobsV4lXk/ijZzAXndXHeoh3os2MSjgH4x4Un5rKL+X8cu/1/mNSHziyk2Blo9Acm3Ak5+JB6APqSMG/y0X5DG5rXJ04i/2WBfhcHVG9isc6huHTGiyZi+tTjUMb2qVct5BBak1I62UDAAwtbpHFrZRVF55PUmvABynOzCsOMGcTg6duzG5xM/aalAEQLp6itxYdMF6pHnYNw0fcX44xoA/37rN49fKDCKTHxy7uOYuwzs/uRe+W1hZKghTyFJnQoVR1bVTwGoosAytUUJGKiJ7g7p9xJaPPasa+ba6+CRvz8m0f9nYELzJfdnRyfXffPbp8tbMMZ9cl2IvzIv2hDjPSruv8DMeXwZql2u4DdECwnciDbJfpVOEHmeUTmwelDa9qOiQrd9cL82NGsmA4XdRqWNQOxX9V1iNkDSPq8oKj1Rm66IPo5FtVnA4KWPj4Y02CHy0wrE6tyD/6VG7FJzOEwNcuZl+sqOEURSq8RL/aoI8etoDCYEKU/6a3HxF6ypdTFIwxCfCHytMvJ4Xu2lofholiTNUSncbG/Q+/6D1+sZDaMULSxXDKKJ2/2FDn8+oe3q8yRb6vHz8x+MZDp6Fu0BjdG2QSCtGPYdXtk7vVNbIUECWCJN5rgkBV2ioqdTXyLtOpLCUiUTdRDinEzSbZEKTi2M9xCchhWO2zJgkPlHZkItYqyA0AbYGjaCg6PKhzDaZ5e/DhCZfkuOQBlpIkaT6BpeiMLHeqJif4q27YWnGVww46Vf3HKdATyuO68HOJLTlZTRo1A+LZ81WqBSwMIulj2+AxORl1cn5cZTxXe1F9Lpy7emC4n6Ltcqfys/R8Rm00CLrzjmqgmy7/Gpqw31KUb5dzOWFg0dwvuA2h7Wb7kEtpEIQ15mya5NdcQDjrSOCqMs5M28zRzrszqX2tHJNyRniOqRVlgS/2eY8KJQ78CS0pwKycfifJPhYYRrohrzuzkBL5bEAe0VPObzfk1lbm6fJrlHhzpW4zkodyV5MSDEq7aqU1GcMDo4k+qf9ygIIMZ6QKMmTES2zyRJwMHjupv23NsebeDceTeoQelGF+2iRLRuMBsEuCPpE++uCa6rdDBQLsO4gy302vWGvU9gtMSwygDS/8+9eacjmAiZsYTzX/ZC4A/n77bvRLzpUqS5g8s2iDqJMKvVwRivy6CoYI+ETKNZx6JnmyW5q7z1rao9xU9s63jOuMib/0WudKHrO+qoZ4e4zkpKKtu2iugxgsWYCP/jQ4aINECH48l8a717CmQUDsPG4s8XeIiWOZW4bHPsA/PDLwLdPecnnqJyK1Xk/F8r7quH3xD6D6lFkGt0Ne4XZiHdNdyxIT6JL/RjpXWG6Ngf3e9GiWLjmGA+DirwarG2fZ/8g8jFV/iUifY2nhEJXa6X7duITyVtSa/exoaLet+w+YbY3CqX3LOKjl7iRkeVLP90DlmuTnbFw5fcEEfHpcZ06f958rf5o7Fi+LBxdrI25+ekfOkh6zRZ+tbE/T90Ogy/8U6dXX3M7cjhbf7Io6y2E1wfCeHkqOB+hs1pVpG3waVu6pHt16AwS3jgVflBlpQc94lVAHo0hVeuuWurBSFGfBCwiQmvYX26wq6NJnMRmEA1cjasJv2YKpkYJEhwNLT//6I4/ab8fh8rlpBBXan2HOY4CizSbcXgv8PSNzjtSbiJBXCjCa/iLZgn1/rifMgXglksOS+aeVuoC3L59haI83mBXGKPYUmF2Sm6r/wpexhCzbxZLkoyCZUHsazIm2HbA8lv2DcbeO3d1R8ssdPS17zcpAE4N+cvaEPkq0VhN5ZCiZXiLYzBM8fYhk9vwtaHtP1kNX5/yddn9c6140rlFjtNaP/2wPaPpt2RzNLnIF3bW1NPBpPN0TeIpPampyuu2/wJpFybuSZd8Nvu/sujVyEE4d8J5sCXe/nBHPPXlyPNtP6lNWfjYjzq5BfbVtiUS/IX8P77XR586HNiUfdLihddT+LTt67W6++1Uqzp5zynU+I2UR7nbVrEKpq7W9EaI+92Fe62TeSitV+qwQh7de4p+aNbFeDj7cPkq+bN9VOh9cvBt2aj+IG0S80bxTPT2Re+O9z0ITfaW1w2hv2BTotPK8Tjltg/uyu90CtHBhyOvwLUp/bsR4v8HqjFO7z7XBXyWU2WrZK8zM7+VNNj3Yn+ewv422SYxDQov9Bv4jTR2p24IQDJ8aUzHLPZrozIN/L3sxGPub2wutfXST8+ydfeA2t9xv5GIKP3kOHaLv3uT2+BvFEeqXc0nZT9M/AFJBjXnHT/3UI8V7MYrJexD0EPO2g+JG8x2r79rls0ueUQ48EkyKmJA+9Xt69klgR50JT4sbaxLViFjDJCPSIyuCK2gyn56mWfkRcGmd3nJ6lIjuCrLckmAOjnPC5acMCzoSXouXb3MxDw3LmvcbQOMJq6Qqo/xPmpBvam+LU97OzI+K5bc9d6ZmGNLSk+7z/z7G699HP5XdxGTZqBjkuwLBqyjeOW1H1v7Ohr/gJM6OLhSm0+TZQmhSB+uqsP5RzhjJrWV5g8lv9V2EN9kQZW2cH+nWOb2j8NWFdXIobQiBfo3Nj/Hg4akupWAcf/cguxvSDIEmcf8YqLkmGb/+nBQ2BpJwv5HIHpuyAocwWkd67Sj693REoV2ZNEvsr0+SO6/SXFI0jWtun1z9Dfn9AEMHZnAGsH3xoz96rhZHjC/PsLq8x84P9pRHbSP0yp1wxkK5w/60YiVpMxS4BYYkbZB/arIzb7QO7mgtUChX/T0ckX14m635Mbsp+rMNfNQ0BXMvyLbPPG4bF0UAQd+hdMXkpQVj6xUM0WLXvLSeLaz03m9h2t2xgzDh2Ynxh1/+Wvm27F1wLulAhq0vv5K7/A3i+kzBC4O3UagIVUcoIVehCyeWEJ2ePaQtzUItxE1ETUsu/eu2Wgt55YgzCVZIPLGtPbFQlbBa6Vpxy9yIrHqbMJgjf02D18BmnvnGRvMj6l5Pw/9bdtPfmuUBanrLvDCCSZS54q8e01BDAtcBS4RfjbenUuIfMLYS2Iv0Y93KfmDrw9po/J6a1IaK3OPYkeIVAPxjKFuyG9MxXVWhWlYOzfUL4EJtiyvdrKy87CS74k1KcMGL/8ipRt3sSHw2ppr7EfJQx97Rt4/RORq23ztxc5fzRLnBvjp1X1Vnuo6kbJoo+qV1i3zSk3UwJtfkLNCUO7iqoqXNAN/HKoG4ub8f7OkOwOfcywe91Da4bUE6v1sk89hSfAFbgDVy1BB+600hEXt6N24GLZ1vIWj2M0XyFTxEaTSBGdYjS+1sI5Kz1h1vdji+WPGqpcs8bcDuTnUrJY4w1CiyTLE1SHjJi+nUWzMS7n/T5XEg5SJPueH7iDZ0XLerM4WM3JnuJ4m1IrfBkjESx6fhNlM5kxVhfr0hhoxR836rquP6nnSq/Gvf5colPd/9KzUav3Ts09fn9vW6cuCeWdjeTs1F2LxKFesqeVisHgb7jn2KdG/fwVZFz+t9d/x1UpR4GzWpL63p2p1JVAE0MlCyTAw8zssEgfZDcp1T3CqLSsHTX1zW+yQ1p4gYW4I+m+8OmM2kvvPv6CVabpUelp7UmrwsGuc307umDX/wbVkGAb3jlR7ifdNvw54oLEskcQL2zh7YShbe8LyLuhNZUezfE76TNBw5QkMaqFFrCCJcCthGX7h8JbJYIgC9pM1wRffqiss26amjCT34a9KCyjEpzRdtMkEfbqi6uUqwI/QZwYCrfE+R8vrlcGP6j3K1ZxtdTHWz+cE3I0TpvAeAMpmW3DR34i322L6qxnMWdI16uFqFmXcuMGvTkbbdyA91pydOdhhb+hgL4dlRg3Vvh9lbYeP8ztDhMV5QZGCqvHo96Llj128ANOCtrp8PKbVcuD1+IT10+Kw8MBdrG5INnBXYx/6Yc9u8yb5H8M9Bdx4eSpsDLp0vTmB/PEoCzIQG5oAKIOO6zjD0PpjG9+y0P4L8flf+TBKSyqrko7Ie6Fki2edFc0XVvvaRmVjzAEpX1jxGDghuLQtajmadixUfK9BKLluoNz5OUFS4Yh7srr1Iu6y63fv+bu8x8fIPrQVccZuNm4QjSPGyFWxZmg1Gfrm0IK6ifu7PTu4cW9u+rmTaoYsvdr4lO8PfXy5PVqSeD47espcqXgxUSe8ZxbdYuA7Mb59ZsJ3WpTF8uXyusj/khZr+3vGUYEYxqurgrtI728u2LTw9a5sZf1M9BVt9Y7AYzB55lH5cEeY6KHSiZt6JguTE9fDISW7wJsh3z7Vy693+tQ/kymHDzkPQ++y1MXdYBL1XhMolAdcpSVvjdVZNBZzF+Xb/gS3e08jS/INu8dT54GB6m/jHUCTS1tusG7Q6DX+ezYIr3tfbd8QBsDFi9Jl549jhF28N8C+aEbQO1gyZ264bg5zAsWuyFbIHg6Hr0YkvQp7fzacEHVjn/U/Vj5bsjOgDJY8OquN80obdg7tLwV31yx7Rh6OJgPkPjTpzHMYONC2Em/ctoiUUUw5O7W6KTR1ScglHKXZCcpFBDneEs6UCtIzT3W3CX2O1HR/Bq6vgdgF3p7iIfrwGxo8yduaCVe6swAaNXQ1l6+tsSdHzVVdKi/fSRdKgEP1Fjs9YFtjoxwgrc1M47/P1KZl/JdrKI8QCsqp72PB8qIPuYdyo9wdzhVA/3Fvzted5CSr+VSwFnKKDbx2G8NjPWgpQQog82seV4lXFxFOuWcM71aKtrmtQEnVrqo7V7dcWLpcmlsod4dK6C6uBJjT1hQnZTNzX5JHd+XOCU85UVXe4iTa+qYl78Oi3ctbS4FJN35eajewdv9FYEcepVDQ/vInn7ywJ/0d6y5c01TQobdN+H+b7YTZwha3HzRzoy11dBHHLWWLuXQ8b4ttuDTJ/cl5uwiZRgkrWeBPTkuGdSKUP6tuOtzKU3530FE+e6/yl+Vxd5XW9ar4aT5A0OhUb/0ZKZvPxFF4IANg34eNfuDXlBSp1GdN2Pn5ZpglSYa/ZyfjsusgEvaL9y/c5e0pOkhsX3HGL5l1tprGd1d/290u7oMzMt+jXXfgGbYGaBtKM9NTtlG0LWK+n85pdEwT7BinqNL6CQJUIiOmDb1n/WT01Qp5+fDua3rcYUmitZF7dRO6fJFtReoPA1YRlYF/b6bL/T9u3Qabcpo+XiJbXpzzRbTzJbd8GJH5+m9MBD8PfDAF4i0OC/fmfkwYe3W3kgenaXNq2+H1b5VpgZPfmyZzoQ23LRsxZxCLVD0b52YxJC1Xxudj3wejtJflp7ncfTYn2UGpQRe6EhdTPxwN/oqDbwyRt+l+G8QuSaYAb81jKcCQjwspgaHHyqJQydVWx9cMtumczB2yNPCFQX07XvDc8Nr+nQOh4c+nUu1tvJ3jgaR3duR/A07fKHM8Nx6MQK+y74/5e+fSWjZpL4kCuiGRbTuQKrBnBno4CUeP+F3STuJ/yN4jIZ9LKv7qyFXGfFzW9lxU9nxW1/515+MgP8slJygnxbEgmQGOE2PGbhpu1tAG+UxoaWYYpy1xC2/3VAaMLjBVRj0POM/x+g3+k9QECz1v+tvz4ffDNb+l5+6z85Un6bP2/dX18fu/Z7b/j/Ks2/X5A+gSwy4Ff8n+X4z6R+wL1FGAudX+W6z6x+4L8FBAuhX7K+V+k/yBBO9v7ej+r6j4v63ovq/5vZlEX2vuetzd6JgBcsDBv/Hu+9uyY5udLxO//KQ5gK/6XRne1Dpw1dP0M8Pe36Cf/zPBy3vOs98dR8PrnRY0ANP8H2G9VxX/xI7t55PdHgDYF8/P2RwOy9ln8dcv9q6erUJvnRqmX8vlG/Nf1/TcHsHre9Wubdx94tfv7FwCy9wd6F3Z68wv8Sy9jv/n3Y7Cl97I26Kf69yuk/ror7Gc41hH7Jx2k8PP/dm/l03dlt8b/vgT99Pv/T0bP502Ng8+B29TMDsdKz8ja3IKYk4qWmEYPR8dc18Lc6Megw8S/Zam46SW/Ka4+9hYLMQ1dbnu6T3N+Y3VhbWvdD3v0NIkD/y/qy+Q34fcPymTu3E9qc+mvCDz1S/WPX0jHwsw258e+2eajp6DepuSjJOO1TrLhxu6UBSwVdK2lFf+F4Wum7sKvnGWqHfyp72ft727vB3Rl7P/fDMBfUloaCG2CL2JzQbPwvgug+R9cJIB+gYo83Zm2Y+CX+K+t5Xz+OyaBXwYghuwvoxqBiHIACIJOfyBRgOamd4qnPKBLiySnI2QrPenAwsO0z7C+QP5haz0rnTejPzYnPoJ5LrhffnGF84+yj5NtmB9ZmsheFN1DkChKEgXQtm3btm1bv23btvXatm3btm3bxvQsTkTuqyry3lWx/lTvf9/qychedMtv5erh1FR99VYwvh0H5XL25nZx9PDll9c87Pbu1T6beWueBPbu9CyjfqY+dNtZc78vZL63yRcobui2sH/ZZV/v1yzn/Ysgqu282o3L5Weuk9bGh/HtpB0zWevF2KlK2Vdv4/fur+Vv56UvOVuV/kxnz95XEUfLhNs+qi3qXqF/cwzhi5MS0FUEIeglQmL0vWcKbGIwWM0un9Y+oSJ3mKam/w2uv4SUow0Grr+Pgp7pYEad4FxfhViXOoiGWK/6qRXxZ8TX51mKmJLZVeLZDj9z8MVqPWNKPkUjqGNoLPxG/anLTwlKr/Mnc0AB6nPSbGqLc9N7o3WvQyivG51JraoXt4dPK/6Zmo4VwptzEejyHlh3CM0QGVjXcBZYwjR7wJ89dHIyneCOlC+UnIWtg9PzXwm3B4sZGkzJKKfJWJLkqolT/j3jgjeewpdmw8vn2QCt7ofHwUCWprKK9AbsHlAlGMcLfT2NG4VFgbQyCfzArVCQ7K1zJTxUND/oRjVQiQEgIxxr+i/gElcZSWhWLnLTj8X5KOZY+MYlwLAIMHRFQT7DuAKrvTKk0XExIU6ZexV2zz+R72E33Nwjtdb3xTY0XTE/XoOZlqp8FOHf+sXVtxmydN9dqoOCBlcElVk8I7sLAt/K7X/qw8CXz9d4N3vbubBa73g2yenro9h4RKl6iaEfeBKswZEwO+/xwEDxvQp9LsXegk493EIFMml6dtra+V4DwbA/G96muiY/d7dVuk8sMr2JR3PFdDjeZtbrBHtgHS5vBFUdawg0zqdwrnBvHbjwbvKu5+nijlwuQ2vvJ6fHz7E5AN6PQH6r1KfCicmqKo4CbUc7d1un1PZM/aqUqTWwRFVSZrQZAk879p6bCzl7xg2+XzkGineKxg8PEhIhL2znLzExlhjQli25Gy1amku5jz1R39Mq0+2U07yi4rSVUkB+RDt57PsIVuFgFiEd9ZZSQUNcZL7jzNIDPLucbkAXQg8=
*/