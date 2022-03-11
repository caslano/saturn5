//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_YN_HPP
#define BOOST_MATH_BESSEL_YN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/detail/bessel_y0.hpp>
#include <boost/math/special_functions/detail/bessel_y1.hpp>
#include <boost/math/special_functions/detail/bessel_jy_series.hpp>
#include <boost/math/policies/error_handling.hpp>

// Bessel function of the second kind of integer order
// Y_n(z) is the dominant solution, forward recurrence always OK (though unstable)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_yn(int n, T x, const Policy& pol)
{
    BOOST_MATH_STD_USING
    T value, factor, current, prev;

    using namespace boost::math::tools;

    static const char* function = "boost::math::bessel_yn<%1%>(%1%,%1%)";

    if ((x == 0) && (n == 0))
    {
       return -policies::raise_overflow_error<T>(function, 0, pol);
    }
    if (x <= 0)
    {
       return policies::raise_domain_error<T>(function,
            "Got x = %1%, but x must be > 0, complex result not supported.", x, pol);
    }

    //
    // Reflection comes first:
    //
    if (n < 0)
    {
        factor = static_cast<T>((n & 0x1) ? -1 : 1);  // Y_{-n}(z) = (-1)^n Y_n(z)
        n = -n;
    }
    else
    {
        factor = 1;
    }
    if(x < policies::get_epsilon<T, Policy>())
    {
       T scale = 1;
       value = bessel_yn_small_z(n, x, &scale, pol);
       if(tools::max_value<T>() * fabs(scale) < fabs(value))
          return boost::math::sign(scale) * boost::math::sign(value) * policies::raise_overflow_error<T>(function, 0, pol);
       value /= scale;
    }
    else if(asymptotic_bessel_large_x_limit(n, x))
    {
       value = factor * asymptotic_bessel_y_large_x_2(static_cast<T>(abs(n)), x);
    }
    else if (n == 0)
    {
        value = bessel_y0(x, pol);
    }
    else if (n == 1)
    {
        value = factor * bessel_y1(x, pol);
    }
    else
    {
       prev = bessel_y0(x, pol);
       current = bessel_y1(x, pol);
       int k = 1;
       BOOST_ASSERT(k < n);
       policies::check_series_iterations<T>("boost::math::bessel_y_n<%1%>(%1%,%1%)", n, pol);
       T mult = 2 * k / x;
       value = mult * current - prev;
       prev = current;
       current = value;
       ++k;
       if((mult > 1) && (fabs(current) > 1))
       {
          prev /= current;
          factor /= current;
          value /= current;
          current = 1;
       }
       while(k < n)
       {
           mult = 2 * k / x;
           value = mult * current - prev;
           prev = current;
           current = value;
           ++k;
       }
       if(fabs(tools::max_value<T>() * factor) < fabs(value))
          return sign(value) * sign(factor) * policies::raise_overflow_error<T>(function, 0, pol);
       value /= factor;
    }
    return value;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_YN_HPP


/* bessel_yn.hpp
YeK3H3QE2dP5EOLWZEVChWIZSDZq7SiGepc5hYp46a9F6NNwxs4FdjYKByUUW/o/rEo/S6fYXZ+eZ5oPaMdQjx0YEQduBcxCcaqSmZAWwKCbqTccsjyD6rWLTFbHn1VSb0B+AcqXhfwnROHRdja1ajxrZWVAyXPm12DJ5TveiPYTXi/UuNxzkdtt+Jh/qz7MLCxtIx4e+3ImsrEm3Xx1cwwpfe9F41LUDuP23zt8RmrhEPRaF0Y4SZH73CWqQVaMNJef328ZbQZWo54gdJoL5vLn8PclOg2GL6+6A3D+xbUhE4eTEFKttwWhFwFo0tWCRchR4H2ZAxsb2jmRmkwXNPQCbbVefdz8FgMiW3v2fnLMBZTOp+6ck8iKtBMdevEtbWhPs23OOyjT+yb+F54DRiRVvoLHyGLZ6apL/XbbVBN7E/aCMGp/zhk/qFY+VTUtqdVp4uBFhioi2/6pyLL71CaQ9ej9fR2vFYMNv2+T+4Uvcb6ygs5lFT0Zk6EedVlqo8lcgiOhj2DBV7Wf1Gjgdr+rknDfHsc2wLk2J04MR4jn908Njhn9TWI47wG4opJtcS7jZNxHvNh9ZjfhK7AKVEbaXWYo1ijko0I/SjOzvPenogeOlTy4TJVrQQ5HY9D/UGTpttaUrJPsSC7Z8xTyReK0MhnhKNwgAoHAjnAqDouK+IYcUfc0j4fxQpZmTnxivK5AelLB34su0czmiVWC2vDKyRt/b+3eOJq7G4z2kDcB6WthTalJPMSiP/a/HwjoUMhpnZL1xSMq3aVSVLzX4JX3zhy/oVzDdcF1DtqKC3l2wQIfl+IOEi+2LCOzMBTMBY5cDRaxbddtYIaamIsvXmK5QRx9NrOpvs3xiLe6UxzKAkXRtQjQEDq01kPVn2QayPe+4qc8VoGg6PWTSA01rfuNIxur2JKG1qfS7XzilRFzwrqxme1TS03JxxueN3LbzOMkGScs+QwoCdxWe3QHdfRWLcwic6azkOa4yjRI/DiMmSE02bCDOEABYZT+sJwkxS15Dq2jplVXLYtM7a+X2nOP5lWDGxrSrS3reN1/4gnit+r0FkXpaq8eVfCDembL0dkUM+MIY1htPbYO+on/Te6m9fSmLWYI+lOwd+KffrbD2RgejDlHyYVM5HrXBkACxLiFvg1sPcl6kHJda8hL1UHJlelkt/mIzPhGo7DprZ9GoS/6YAvSzZDKTDOD/ZSCIGLeKcgwEwgU+6W2boVDT9vT+R9jThizIy7TC076Ijn4honFTPRHEymVZpMqzu8/L7he/WsbY6WmlrHLq9KvmAcz4yjqEs8dvFl6UjuI9zXVDaClB92JI0trnlFOWu4kej9lDaY4+z5roV6Vkfl3mNq86fQZWlT1zkQxDnHtAmOWuKGpubppCaPP7dWGh3lKdZ4JqURgHlYy3AMX7GOxDfVRKF0xcmXGRjeyvAoNy+P3pa6kSOWNuFPtJcXNpTBc8NDWZDhMTMDQQk3KunVqLCqNSo6n6v5vyxewnB3rRZXgp7RI1Z/QDJd2Xf2aDj/CDJhE2iZixKzA5lSOChQDLHiMZM6T46cCQ4dIPhDTTpNN94Pfh47sLdSKYLdtYz8lJbQ3/AxlL3yB6aghdCKwVqOQqhKzvqd9YF+V/n5rcEcyzzI4DhTYzAMobD3aWjlpX5kMH0Xs22twiYWWJO1oKSzbHIMv8nY9PhVDf1awRX3RCBt0/rRqzPZ6JI2Y6WRB+noc872UPnI62JACQktZYQIerbmNxN0w1QYYlKfHHDoqfPkCdcEjDWWAM4H0VXo6fcZhzehUt9Updu5GQkCaJByUpgAALP/TmNWwlUsnnchsZ3r0nFxOnuPf+mEPpvzT0ctt6fPppOTnST6nOZQITkHpbZdvRNz5ABQeiNkW9BqybhwDEeWrPMlhc41j037d2K2Km4NFe7dAycK5gIsvOBS2XQSDlZqOrTzLhdOBldQDDVQJ7Y9NnuJjQs+Sv7ebSMZpVggVHptnlCbHEqiNt4/5Ck0OE6xUWZZnZUGlgA6rWfE5sylLUzKt9INLsT3lEPtlS2i4bF81L6KMoRWNWQdwsEJlacnl27S0Ly6f7gNPjGLSJuTCelvaVwO1u6x2g26JBhqpjEUshdK4qEDwXP/LTUUHx5Fv9OJrOwGNlrDxWBMrnWocDYvVpXCk/0z3q/Ve/8b9yjgiNRg6sakd1VyvzWD9GsfeAs0LnG4nNj6LL+2sqREIdsT0iiNJRiMIt8xJbpdRdq5ELoMbQU4XtytVImF6rY29BJVbvvq1qHsiEjyyNne981SY/od61x1Lh4/xSrOC6C64WoytGcw3ooKjomdmUnG/vCVxgLNr+Iawq0njPxHx+5ix2FLqTjnV8LyEswId3ydcvf3J+PdWyKk577Dxc70jud5fxXk3jpFmX9tts6elxe00DZe6wTp3gN5sifX2XRuN3FChd1TNbFJ89iugmSH8f2RzE6J9AvRGneUO4zDXxk/OqipejciBl1oCGFV1Zi/CBWUtWZwB3sGpwF68z8dLpNnM2baVUWcfzYqaNvNNr2dWEj7FYUr9CHfERq3ZLNEzbTAccCUhkfGZHf0rHLDzmFzmLCDpcjSFc0ovm+/h0dbvFZBgXNgjocxOC8OKWLp01/FiaM/bzjAF/Tmye2/z5Q43++v8b2hmEVDjJKpw0Bor5+nmKnKyBtMGyamFERFn2W7Vh7zrlq1VVWY3VH3gxHY3DtAsxFkIJwbZspEfYbq9tmN1pStLWb45AyvvyskGIHep9DOTkEXSqyKKt2cuJMVymgxmyP9JWJJS0zLjLjcbnyPGLy6epTGVeKrJ3vJErn+EspB5Qei4O14EcLuPWFKhZR37AfgLSbFkAXf+JxNXFWuz2fL/o+Vk/Tex/z9vvDu9/AT4slFR30VVXN1wku0cA8AosrvNMhM0l1vYQRstQR6iqkpC49cofWlcDprvO8fPpmaTmVYutrp/i0rY7UoNmT6lHvfCGU/ERXZSUrActRdXXbIa6kh9rupzV4MydruD6jFCiyXUMEzO6sIdaXAt0tOM+6TaIUzgeln9jsdVp+/fojoz9HD+455l0adowmVvlDNaEOVeQNxw1Gdt9whjN7dzNhcJDTSFLxtElnnp9ntOAH4eCmAflPpnhRQV6lZpUNxS2u2nxIeb/qkAkzbYaqziWtcartVKwvTfgURn5Ih2t9/WB+02dYGWCZ13RKGXWZ+CYRweLPFQdW/1VssZgBhXo/WdLAfSTU9aginiv+2cnZHsxwWUBV2Z1zn9s2vshpFA1BRghK06cxRcwm/EAAYNTKBpoNZr2nud3XOE+5gEvwwH5lzXQtJWszOsVvrwgKfIazAEKi81dKlHoJdI4QzE4lK/GHS/os/CH/F/Pfu30cU+1O3yRI2Yef2/A3gi/zXG2dhaUyq71m8jsRdFHu8w6/wXO0Kchnc248RzqPDmobG/uUKNqDQlRCbYNK7uaPHmFWWuS0dQYZcihFomzrCj9Hwn5r1ITQk3/c9TbKlRKkxkOPt6By+C+SIfBAnKPQW9WW0oaCgwPQEKggrfbplagSG5OXmPd0NziT8aBqzoDFww1fQYmRT2o/jGTWm/YVuNP8Pj2VMwLT6mRfIUy3yFCOaD2UjDL2N6SB+tKCFuXQF/CzTaK78P3g+tXbFtp6jE7LOgiwRWCcRlBdpPnDkItcMb8crD7mj69d3wngFyTpKwJJYVV4sldKeOKjHS8mH8s64TNXzYRpOL+b8yZPXM1D2sfBQB2zTFoxICjaxhJhUbiF/dDpFfyH8xCg2psJXeaoqmJ0WADtzy66FEBkh8N9N3nbp0GudW3y1ILKGx/CbnsXqBLTH4wAT3UT+MSTJE4YyRxHMvPFG72Sv5LAFAis3w2NSby1BZG4898gX8/FPXTz2+NfS0RyTot5ciBtDY0bqbntyE5RRzG1uB4KDgixrbzhg/hpXHZS7QYiZgPbch2ShMc3ESbb3bBYX/rcvU3PDW/Qyh36UD2IJe5fgNit0YZy21IMcJThipbyuHTjDp+TEk2TxwfwE/8CeN0egC0OacbtOBXO2hzXia8X8guKsdsOs6ccPxq7hOtu4UW7aVkGgfLVs+qWzu0Z3OA2l7fPjgR2WPG16odzdQvNtaDYv0DUwBM+EzumodI4bDxlqRq4T2fYPs34U6THx0KDY0qJfjAd6C+mPucGA07cEkWmkNjtUc0KuvCDurZk/L/Bfj3UUHMZ04IljUMwNQ6SZTaT94W3uVB7fXkx0KV4DplNa2Dflaw2OcH0LHSRiNzA5yZspCSRFqzHDNaVdfF3eq8k0xDU1Fv9ZUm1d/WaJpe7A8lLSL+luL7BIyxEC2YOvGMyPEdeCQ/MpJ20djHP976xGDaHVLMfWXCc5w3et/srhOGwArZpG1yFahW7PwtVRFV4vwIXHKvNFSt0tX1Bw9Xt01Zygf4eAAllnOkCuBnMiix4vvGsMU9lZ4c7eVapNXHmz4+02xHk95QTA9vtA2tKQBvwt46FDjf7dSk+5WJoCnz6xYo89roZ//jS4fOl/qohffkRcO5eC1vuVZSsLk3CjpvuYmcUKRE2K9dN45ztyO3/pUaHoV0ii43NYOlr0IZSLk8pOiSg0KNBGkKnyWsbn6dHkSp16tZRjYQKWEpMa0hoQVrMoFcXRTJMYrHAAoBb6Nt/WUBthLGGvWZCVeKCnT2vm5ohcFqO+0zhmRknyPFmeObnq80nSF5NjsMjz6c3/mSnJPUnQyvwbfBnwXa7GeV4SmKBzVCswDNEwqb1/Kvbcz6GGZTGWa9J7/GwwTLoFOhO+HyGEuEoGhN3NJLZjy8GlchXjslw+hgNWhA42bY17j783LBXpYVRJmHVyt5Qt1DWDzbUSOsOraOjYQ6MHVtteLF8JVwSi9sb9MtQjN8+miY4jCZE+sUwhP80k59WgoKJ4oek77HwALgPR/NFzKuUQYx39kYUFyodeN3tj9Zw/7+M/QoeiHj4aRbhezBug5yEDEaX1LA4+Wj91vKi7tTY4ebN++ngXDc7VHfzMGW3xo7V1kWN7TR2r6UMht3OSFeERDsX03YX7rgG1lPaLhHZetKQigppzSNiR8IjRLf43n+u4b+jiYZlU+6pyGEF12B09H405oMknqoo7epLnpm1ld1mOge/Ry3jyf7W4b0upCfSMh2BJ6Rnb3Z0/JfyAiv7qo8J3sR47lvTRLR4i+RMZlcXjEjCe3FtHnWM6gh8Uf6mSeae3BOx/iAdbPorl8P8GIFS8Wpu2v3t2WONhlHHsEcrxBt2JtZHquJZXUTi7jcNXQBiRgIG4uNK3s+TUI2KegQZYDQr/Byg0X5N0hsHOC2Sux8lrs4ovMw02N21zKkHJqOqR6GPwjMob0V5YIzLiQeS3o/17OpDkYvKMTCOFRoDCwDQk8IeaRAqUgJ2bJyAlf/mDbmhp7rwPx5MhDK/R6hGnn3aTNr9v/Ev84DBgn6U2q9hrFLAEG0AhUmffhEPUHFu7Im+sTvLYoK9Kp4SKbAqWrAv5wMwHCZe73PYsGunD3+88H7RIrynvHdfQxrb9eOswMKPc1KMc7LIPq3noZM2kMneoL/AqTDz6vfYt18JHQPz5o6KENugyQst/pq/p/ruIIAHqUJ+UbEhqQn/3uukDgW/ZFf51vMKsVnV15mKZ1GdymO7jdzY89J/72WuDvEkXtjueD/5y8f+nnE2X8ha2GuImtKvT/BZeHiQ16od9j6cInD0w+XPiNfqM+3u0DgNr7dcCUm/i5bXlNqMX65gexktr77db3DAHihfzik+CTtg/s1/foo1b4ApTv0v6B6W+bZf0leF2X/YYGf9R75PD7/Y69s8SM/ZxGz/j5ASYvuBUu/Pp1my8LI/mG80cMPxfSdOR5god6syj315871n38Mzvr68ei1j4FAPv7yzP2HQeWf0T34603wLcV6w/MT/Fr9j3WxzYGfsoX+n70zk/3NvZxtto3n5b4w41W8PuoX+p/4+78M13383DJ1ReYcG58YJ7+957Y6f7ra+ndXTwF8qmEgR9bJqEl5ZT+3sb/DBLXmNR/18LukF+m/O/rbx8FZFyz+a8pd57u5NOvQN4sP4JYdh2K5zv787vfKfw37jfYd/OMy3naez8xfEafse4vBE6djqa6pfT5zxd30iT+Ovx93+8qwquyFu77Dwf/Pqx82mL0lhkzPYbl79F1xm+i/4z/a15tfoX/7w1l48evtWAGwn0c5RrYXsLPT7imKey3BevtzPD3nMwv9+XpT1XfrD9h9qJ5idBzSd/ntez3cVWrnR149VVIrT8a+RZFGTL5My8A+A/8O+UD85H5xFxSHhm/jF/GF//71zY5haHhPlAXPi80B8+XCH79LXu+cMOuMAVC468i+CqPvpGk4GddbsB9uAHYkBv/KNSeNygn4CggKhn+VflQ5bY/ZZkZTPQ0tDXBtCeeftbr7Zd1iDGpGirbS0oK699jBMAbx5sx/kGxqalL/Gtdy2hDHaAltrcxZoO1exXVO/9bi9UTAVR2aMEhkd8H/YhTTc+MmGtxoPBfqx9+SELhX/5LW8sv8bcZ0Ro+1bfP3X7xTpfPxs7aThXAbMbfy90UsnZUMQN+T3aXrc/fDfJTqqihv701rxcGGP6vyFUS1jR2/q6k47Vt/jJPXPfnycLOV6fYHYbnO3dgXL41FGY0o3MXmfrVwsv3INdI4VxaB6DNyA8p9NLsFK0gmbFZz0wGI6QjXoVFfwjQJwz9fLI1LsGSrmf5ObFiE52/7c73qQ6Sg0zri31lIBTR2DPWOiSunKWLnRudC4Cv3xyf3/x3vmRpAsMrOnurSq31b2jCunfkcxIxSMoR3hsuFdFBFQB2DiVDe/2rCjU8ZerN9ne88JxEgPB+79ouHKDe7nlmh6P09ZIo6NV9AQ3BYVD3+ROCK4HeL3YkPIoTBL6HUvgJ+H9s2f08Jz13Iy6ZQN7KrZ995o0JCLZwUXQsx2qjdWZd1/iTdubFWUVm1wsnU0eT0YTujnfEM4yxJe4ECriH/V4RUleLZlebLi+/s/bkXbXAZ/ixr+S8AifyqS5CdvU+OAYw6y6fFQB74BF2Wp65sPlSw9cznLdMruGQFM2NRh4UrfLCC3i4BcVn0j8iFFt5ee4K9n/W6zEeXFCovJ83Z8oxFR0JmOADEJLodTph4Sp34VLfJgQSiPm0DH67DZbWiIFne+HE2x+WXE1vfU6A6VaqRqFXwNuTYztD6jI42vIbPrkLGfiSoHuhciKgjPnUrnYr0PSSctYb6scrRMPR24Q0DHU19hrAXLHK/y4FLG8mqpl7lMo7WQ3WDvMF3SOJ7ufwJm/ZbedxPoa7M6Zb7LWTNAyBK3bd1VFM7S/fwN8J687WuuQ99upffPOJAqP1IGFWDmLSXDR4AX3jFs42fIKswcFRUqWzSp1PQux48JCfUTNLDHrs+8N8JerdpCVp9nHs3ikWA4JNqaYZK++80kTDe0NEAweNJFt2nK8kmgwXppGcnKUYR8Sui6xUceZXyUYaKVNh5oI97iwfUmFv/qJO7s4Bi/MdnMpQ8ekG/ZQr8oevYA5atcGyO8M962Vx/0SHnQIoCAnQxa6Hq/ERvPFVekUw9TMv9P5iWznu6ZipCmsL1R3CpsybLD6lu5NSeEssI2T8wf27yExItPYgN4EFSIEQNhjJM+eE1wsjLRTp49v/SHXhbNAKQZahO/7gtrtQMSq593dqfXMZtMxOk2LkohfEFvFMup0HhXWIGMLHEyj5+E9hdpCva/2rLUd/8DF2lpCnjHNbBHFglrElgQLFJ+NzW+3REOnxbAQwum/MWDTf53RouShZjfAJsEwk4ZWo99uzt8Hyg7QmkNUOuJKqSB5wAvXhPEFQ/5XBtrd5rXWBpx6loH6rpNIb23Vn4KURwUDrbW8VI7RNUHc35A64Tc8F7jPVVbK18uKfByw9PdSQClic47w8CaVwr4QgkYC2ftinpOyFAXmfYjCHnFw8MGQQmFcnjjpjX/WttdhSMiuHBqmlAlGJkef+vSQ1OSQotYd63fekUVFzA9AFxKkVVN3wtqS8MQQBuGl/mfuAcwj+v+dnrH5PkB6g2coolHOZTEbg/AvebVM1zvHczMgBem50YERJ9zwlEkS9klR6kJdF8E7yblDLmujEvChsn/eCEmILhM8bSxg8u0fZGhtRhmoTUzQQyMrxdC9It3uu3zmnpGCdTAFKhc+OVvZdhFI0P29dFcYPrep2CqwsJ4acmINb7gfrj6aLIRTpHBjYf9lvG8yPjTWKN1IAErgIdG1M5+x0d4LB6eMurj1WpOS9H0bGeyakin0wa0GH71WjngQV+ZoMQnKOOsckd8NIbyEDvQkYX7iohu6GOeK+vsaSGis261561zb1/7iNP76sYfJfKJ7zTY+Mqb7kxyRZTQclKHG3ItgNkK+wk6BTbj37uJwdbBdAaS6vh6IBuwlydKJkh9zuJglEIOHtrBkQhiB3ryQzEDtlo4F2uv7sMBw0k7qR/YEUvQibCM7HhH++EPt8+GsX41r8AzQibiVFBTqwZfee1DjVDNI8QLSPyxmjamBgF/wc/ii4CRZfe6fMGjTtV96Qv2ubSGY1EiQuGDV6OptukVgof7KiZchrMu+GJ+YFp0FxraIUDfnVK2g9RX/B3Ac/OXRXsxsPzinJNwDTkr3nab3nbBUMBGoT5opDTMSik+AW5gPeebG68LLqXfbQQdadzMqgp+DlYMrPm5RyBxRog9FN7jlQ82tTu/GU8OW+l9jQT13/hm4aVP7hrgcyTSG6TqBOgUkBYbTxVnhh7oxFE/z6OkrwiFlPaskCbYf8ELEm+X4W7lnUARi9Rsz4xGASHluGGD8wzn4h2Vt0h35CWlLubBN0OCkUH0DfEsW4fbT8mX+XLeNdTlDZprwWOxPCFIGnCRdE4yphtiy0xkXLN9yDIMqfDrbilcwTDr5HcuEfEMR3Vwv/rsLm0xT25oZntPOQbvasu4rv4ztUVqbzLgw/APYAMptf3Q8xJMFdsP4YUo4M0xzn4Ap99rfVZC3sbX/TYqdFs1nCXHEOAdDRT2zCYpN2QUMXXyWlmvJb2qqFVPhRfG4N0C3uSVlP3yPXBWXMXLnbCC+5DSDeWuqHPLcMLlgfR29+TZolXHWRECAkTDWqnonsZuQ=
*/