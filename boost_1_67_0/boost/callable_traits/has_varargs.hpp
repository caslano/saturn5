/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_HAS_VARARGS_HPP
#define BOOST_CLBL_TRTS_HAS_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ has_varargs_hpp
/*`[section:ref_has_varargs has_varargs]
[heading Header]
``#include <boost/callable_traits/has_varargs.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct has_varargs;

//<-
template<typename T>
struct has_varargs : detail::traits<
    detail::shallow_decay<T>>::has_varargs {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::has_varargs;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct has_varargs_v {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Variable templates not supported on this compiler.");
};

#else
//->
// only available when variable templates are supported
template<typename T>
//<-
BOOST_CLBL_TRAITS_INLINE_VAR
//->
constexpr bool has_varargs_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::has_varargs::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none

[heading Behavior]
* `std::false_type` is inherited by `has_varargs<T>` and is aliased by `typename has_varargs<T>::type`, except when one of the following criteria is met, in which case `std::true_type` would be similarly inherited and aliased:
  * `T` is a function, function pointer, or function reference where the function's parameter list includes C-style variadics.
  * `T` is a pointer to a member function with C-style variadics in the parameter list.
  * `T` is a function object with a non-overloaded `operator()`, which has C-style variadics in the parameter list of its `operator()`.
* On compilers that support variable templates, `has_varargs_v<T>` is equivalent to `has_varargs<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`has_varargs_v<T>`]]
    [[`void(...)`]                      [`true`]]
    [[`void(int, ...) const`]           [`true`]]
    [[`void(* volatile)(...)`]          [`true`]]
    [[`void(&)(...)`]                   [`true`]]
    [[`void(foo::*)(...) const`]        [`true`]]
    [[`void(*)()`]                      [`false`]]
    [[`void(*&)()`]                     [`false`]]
    [[`int`]                            [`false`]]
    [[`const int`]                      [`false`]]
    [[`int foo::*`]                     [`false`]]
]

[heading Example Program]
[import ../example/has_varargs.cpp]
[has_varargs]
[endsect]
*/
//]

#endif

/* has_varargs.hpp
tmWu0jQruVk7V3hdBVFaHz3s4xtxgc6IInj4e7eEJr0MxeEyM7zzfcZqMWru/nyKxWUAlT27w/jggDHHi2xE2Egb04+fF6jGJWkIOE070z90AJylji57SQoscRm4Y+OCRZgLJe4i+ovwtKnHLy1YkIwiyleNHUzTG/L4FKvn2VPXH3maY4x5Ok0QDx4M43pG0aqEVWev4oxz6EZJWOvu+Zd/nsLrPM/wuxwrWxOfUUhJeVURSYUKEjXai8ikuVq3jxYOvZAiuFeHyfzKBes91mmqoW94SNrm1NoTdW31NksshrY9ZvWDAfGQ7w1YBC1D7qdr9RqtIXgFN1loz4RmplZY8nak06tYuPI0QKeHeUPCTzfExWk8rcc77g5Ns3wEmI2CUKKd4hXsuURXLeVGYC+3FnQanZ6yHg42p+sPFORYGN4tndj8WOjT2a8imfSwWH5xa5rlF41cUURnoYKkCanbS2GK9o27vIC4Id0dw3Gd3jyooyXsLphyCEnprNP5nVNLz84ogm3Vdu/glkezHhh68o2swmsap58EvAPBFq096JvpQp2XjVRvRqB4/eH4gW5i+gjnhSM+9wB0JYnTeL4iXN1SEBNyTzQDCEU+egBZoBeVUQ9lTCd5B3WsyBbnanIEzOWgHo4jiXPJQtIPfP3aKvrjusBX/C7LQD3X43EKRu97TzU1FUSVttGDWxLlrtq9irUwLgz3oZtuCJ3a4st6Dh1pL+nrp3RKc25FfSt3LcmObt+cMYYGczu1ytUhMAzjjERBGAWSdYjiZkA3Y46PIl16l9vxmqPgJ6bR+Hjzd8KYOhjcxE1nnHbfyUJJsDMx1N6Vq/WMM0OTXuV1vOBxvtTCGdeBtNBeloIwvTra64+YJrjFIcaD2jk1XoqOIojsuiVem1ktegDOALRC65ApSlJTQZTBEjO9igtyhtWCB7/21cBqB4LNrtG5K/XyUcicuXkFt5kHhjqbNb53l9Yh/cYUFWBmuqmWp4thS8+80Dx/UbYOSfQnq42S1naboOmHw4N2hD5GTM5IcXE7fQ7HNEUIO3dYrnx8nDeHNvQ86xITctscUGSi8vlUxX7S+gjSrfUH5WBoXzdx2bHb6SYd4SYnhw6FcT3dRjnoJOsJGPnm0qCUTU88EfrrPBOJ5dblmu3elI6r8/RMod8ZpISXk5ijJbHGxW4vwOGYXs4//O3rq56cl85aA/eOioXWZnayWIek0yxngDckdZjOuDA47F5zpq0jmC6xM9UI/ckOVjLFYoHfuUwdQ2ocr0OCnT6EzN0jjz8exqUk7nfoeIDgcOvhHes06rW2ZSOBhzcCffRgDdOjHawYd0xvLVxOI2mRg6F77rb1hy/Qa+U7GuGodrd4f/jGbxWOHi6nLsMO2c2iHjIm8zFtUxQkjWTX6lLeGNRlcJ2OGOgMLIL93/9e6BgqT8479XXT0rLFjcjXrNP4Qp1pFsdOnC7q4Y2X1qkQePoYdq9aq12sZLpEf9yIjpDOpljabmzasTc0d+l96pRfFAz+vEkbJaNz+PEtYVRK4nQ7zOfD7/RSRkk3u3SclzwwROCnllSEIQkjPSOPrT+erfuoZBx3Ec2WoMYP6QclA6YckjefN9RIPqfBJt7CiOD2aZof1yF2e5sA3UrEO8RrUFz6rW99y9ckRl8tBbmEWGnWlIOJaJ0jzsOBO24LnVHrlHS05GhNr4RYFGqaonq16D11FurD0U6W1Y4Uip/OelogaeMzWY0+UZcahXFdmTly7U2ho2dRVqbjLqLBy7M0WnuUdz2ltdS2qqnXtPnSAliHIOTYqAnS2GJAOh9BKpqmstjHUGYeFtHhUyzikAVM+a71yQJdbhdaizgGP5THYmLs0UfCsC52yMun+wtkmOd8rhjJSc2U3loKYm/LaPdqioLE2ph393/3O6bBieiKQaevSLiUBajUOXZzG0oTT9Q1zRo/sCeMHtyfNVbcqGl9pwDqgIlh9+o1oSK8bNeyWJ92M0tpxtc/EEa/oaPng+XQpd7ceeO4HT/+IrrGdujNQAlZ+bFNmYDGaXHHJsZPOMLNNGkmIwg19/VHuxSsqaMjozuPnzJi43XwMJuu8Pxj06PHZf3hdCBedNL937tlSl28TkBXFofz5s3zqxLstQ7HV6ggqrwl0uq+anoFsriQ2D128EAYfXTj5MNBldC0/FTpw9H90wxeI4iulNFcvk2jiJ/LooL5RvRK52FcD9zNPORbvDTZ6mVBof+atRgoh8p/3Bgqd22waRkC1yVhcwO+IuO0AUkz8tijlmxkx3Z1gYh6feN4HaKUNhqouKQvr5+fWCjzUaf74sn1h+N0WAuT14F02IHbb7OFua8/ENbjYVCQwTtvrymrTq8rBzDa7k1epUwJL1IQNh+upPLMzXwh48OSwxg57kEdbe4QYdkAMV97WXrxXlJ61C1DvW4hslGkHE2zvAHjhbCHxbCoEbtOX2cjCMLGTSdF9Zh4Ss8tvvyNMPHk0yaUvovUfd4FU1DG5cVuEkLfyNatlmdCx3SYZrlwkjaeyuAvMj26ktNHAyDCP50xhVIi1LH3ssurRi7yxnTWc5MWM5Ru72pAn9zmT6KOyS+cwSKHQ/fdM2WUcJmNZdrlWZ8NZHZGnZN5Jh6ZKgVJmX8aEcpgu2aO1LWuFhzSW4OuIOQPy+bmYOKkxgmncyAHJV/2EhW7WcNbN1X1HEZLgz9eN5J3aaFu75XTOyZDSFX5lQcfDeP/eYO6qnLWE5syaTep44x1GQ3givHizwsbYcOamtAYVG14y2aCzKRt4t4qCF4MsKm3N7Ss1CUO+FNLXC1DGujNFuiaosX43F0rv9eBeGSE9MN6is32LoJzPE2bmFhRJzOmb85AVz0L7SiJOqHm9N6shVqoZ++qVylIWineaGLIaXfliGGtwrjexVc55C9pelUlUbWkew7C4xeoJvoO2TqEShsd6nHjxrTAgh/q5QY3r+DaGkRTLGZZWV30mL3y7dtC5eb1mp8gYpMCSU/cfuYZ2lXKTqFlQmcJC34oC/pGtj6ezd1H9G34mJ7plMTTdmmaRK1dSQqKqwrK0mrt0Xl+Muo5LqC7qzLJE/OTNNYj67b+sXT9gVAVCVYez9Hwe99JZz2oF/a8HnnoMu3h+CXz3nDnOG1F9bBIvZLYFiPB7cimwHEdk9j4cGgTUU5gk74Y5Iw82tB2sjSMtOr7HowiQxpFoBdD2TOdYpGnU1fqTGhtw7MQw4Si6YKE8Wu13nhki/PPIPqDsJGu8zzd9aW0eVPEA0/DtGpMPR5zW+xw+iwkP7WKcXheh8R1q2zoQFGhqZ6BVqwptfI16ZJq2tVNXFYtN/RhyDeg2xOh/XivP4wg/SCLwxserC2zaQfgMg6MPuFhgwS4aiqI1h82glD5usqh+JGdO0OTHhIy9zQjIS0t8OOKadhRBjQii3W7llT39mKgnXCMQ/PU+CG917eJqdIKLrXWiAEPDvWFsS9dFyae2D0ltysIwtZ9bnKRnePKJ3ZhI9zTMKVq1ojH9AQ7kiqIp4nzEOaG/G5w83YhNDDiIfzTGdKiUKw/YuN0xWF5t/PT0/KCFMrRInajKMfT0OIsKNj4cPqKYKwcriCkkzmfHwztkTdnkEjXxmcjiCsIsMgMP/JwaJ9sq0Q5tGg+lsbWIVJMjp30P7HVioZe7+Wmo8UZGKdjHTK4+8kw9vS+MPrN74XmwaE4OnNbb6z6I2w8j4hNyvA4yNwImJdZ1pSKnorGAAcPDCe0k1VRpaC/Fg4QOQ7c3RdclI0K0ESTeJ9FfGyMZgWYUs/iih9wUbbLRJlnYAqjDrXKJM+xMsjjiKZ8tXhHuLeBy7fWID7FOsPpzI8gSPWZZNR18a3OgBjizls0NZ5elU7hQRm99rGzeu/Fplfc/F7qPxRG9icLNCrqUxUgdatlnSkOecNwbNfTYVgP/yo1lAMhRNis5xbsPj/rfBzNlPLydAxv3mS9LsJFL1zSlGtYUy43RfR7HNAbuuP003Vib57RA021DDTbVEwOG0EufY7h8PS1+EN4TAvpEa6xp/U+TrqGQqCOp4JQNhZeVvTgdfzQwSny6vIL7bHlzixlw+gBXmLyCmKrd1bzQlLyLTCHMbLYPSrmxDsXpUV+0Y+Te/QhzymSl6iSI/CDWzba4hFmzMQ488jTre+GjNxwWxjTfVPeIxfh8t4Y4WzXTpKXmYdxXoQNQxpboMtr0xNB6bo9MPT8cb4it6cDdmqK58paS0ngCHEoBzR3rFlbRTN4HCdJikxM/2D69uCJsv6AXrjbqoqOaDSOZbWeW3Vqlo6gE/O1k2VrhLyC6GyI5m/t7dnoAUJnWC049uTOpOcjs0yJZyAIwDG2vIbLK7itmmYN79ya0U1juk0onPob141Y/J2rTg8TWosgSCZMU7NlvfWYqssCnXwYh/ksTofH4x/WA1YeeHIhHp+A45Mxw9FOlufJ4wJHbInvfpZ2skQL1qQEmDNQSH1GZdn50rCQ4cklLfRCD8aFzRXkRFh/ZASLRIaD0Wm+JeLy7XVJH2+Axk6b5hXEhhZGkHzGeqPImI4YtyRyYfSV9IAwbp9j5WaTwL8hPppeKOcC5ELWCKQS5CtJ0Tp1lHxKj1xVIZ3BksBwPUVXgztYxqT0h7XG2LZt1pg0qNVB0Bfq09ELmjgNO1ljomVc52PsASctgUCbJbHqJutKzwNG8udNjDN2+/QQ/rjxB4TQPxWTpzr20BXEhb8WjGUb2U8ptcEiryB6uqdOU59Wc2QwwpXFhS2GFb0LPqFjJvGS/HiOIDqAbCNIKA+Gkac1B53B85C4Xt6cPWmPzAiRCZqJgQUkI4hkBYFDOGMDvtjEgkY4tJW3bNHnyUZtWmVPoIWWKRZbvXF+zxvjc3dMd/eFyUIdeqZOsZzmRKHHpBi9lzZ+gtdpAGKgf+ypJ+2hHFKFMCUxxB5fAx1MscZ1/VTMn9gdy7W7mT0pKw1ng4Vri9eGS+K44DdTkFi74gbzDDAIJBljNMUp8SGU42CggfdDmEaymzW043F9R2NlMhqoUb1h65EWM5B0PZc8J+jDAcnWqQqIOwLiEUIbYRQXH1Is4hXp3Xg8hxNteqUIcNMy8LMfBdHowilbem1Pr6jMxLS6u+vcc0NFbWDtJprAp6/BZQZnRrPc8SVxWaJpHPDRyxu8O71eVHmgnzY43sZpgI9jWqgj/EWGesAnvdaRTRd5xSNNa7rgHgtTpRfjQEGcAdPByoEDoSlqgJKOtEDg8bL0vtx04sdOrGLpDwypZz2tp8Hfq3ck6I1RAmB8shc3N8HbnF9xPAMpMo4P6LtAuOFtWVvkCBajB7Q7bNJOFspDGkycL8aHG+Owqa09tJ91jk2zEAvLTZLUxjQ36ZLqjtNWZWWAx02+DPdDB8blYlAHFOlyT6j1h1GYjGiVw4czWp3mPPTRg/B0kU4edppsVEzRGVhkgTqXQqZGLNtoca9a6tSpYRrtOFka0N8yHNmxNUzodg16CTcuSO4vgs5A6t+xdq3t9DDFQhkm+wIJuKQOy/qjZcWq0KwdIfJOZzwNtJQf2WBK4b0v4kfPh7IMSXmgITZ5+h2XQ9LyPIQasw6Bvkw7MnoThe9KX5AiD/nd4i8yXjbpoAs4JAWBXiwlnUimWU0xcfhQQ3Lsss476mkdEl3IVcg+baBENoI4Exw6A2NY0TvIVcMQCpJrlGPp51yWvaeuo++lkXIY1p1Z0IvxXhhIYxdZS5j+uEB0S5Bs4ZsKmIsCWE0QJRld5ycPCD2P44nL8PI9DXSNSAloEUYOBAxeupLwANbTxnljnB7v5QG7L9Jti0KGjUc84qB5TIHUp/fZU+4oKOQJZcQ8Aw8yMcr8XrtERr/CoP9EMnQ6lf37MsWP5TbvjhTEZF9ZCxXEFg9iSMkzuHLEa5E4blwLdFcQGGRTLDmO0wBiPa99LtrOZamH1rWkXgdXlOkaMWYeaREkUwS5Y4HD7eHsYGHyeS0w+vF4aBrTB015yMZZMmcY77bjx5b1JBiDgDZKO+ltBJEmQFvV+KNisimh3Fz2MBMDHW6gZ0DH2+1bLQp2Bff4EwEatcPDgauoYpktcnu7iG6vpL1A5bLt9fHnfSXPAIwFLA43t74iFC8CS6xxYORxtE2iwT6PoMVXOboOiErGjeyVng6yk8UUKy9w9MZspfoWbz08lOuWdPCurFdDbf0hv0+xaB2EDf+wpl8Y0mLi/BagnyntobS21Ssc7FJhfZoFFupg6yl5WF8V5XfceejlkweZ8PUHSsJGQ9Lm+VzH1w8/J4b1SoJozltXlDhcI6XrBNdsZZ2/1yJTEALijDXdWkxCBMaa0Z7WE3L8rETR1iFtmk6OPrHd1iHQ7w0cTxc8zKFVJPeDIHEAkGkJCmEf2JFQ8PxjVNXktdye3BksR+F4Y+hxrDEQLl+YwzJ5ABgs59Nt9CBsQkfIR3btMmH0PDGe2O3xwFYtvluWLTdloE1s7SR80I0yozS8O0K62MT48m6XG5cD8pW5wV0QK/SpkYtKTAZ4xHGBkFHRQVqnuxb0QSBPpGuLh9tbVWhRLURTwrWHH/OCh2vGH3h0nKyfy+Kmk6axkTD81M5k21O9HsYb3ytdBON6tknYmpaemowiqhNCh/URhSt3Os880xqhCJeH5cs1BVEkT875Q6r4o1EIww49vCFrXM8PjA20unF390VaqCuZXV2URjrN0N0TPf/I53W/Qy8PCH6m2yM7d4SJXdriVxkoc44kZU0DBXAeTxO35XRu1dF1wpYb7snojxEQGPsL3ZrjTa2/c+X4QBMyjZRMs9jy5T11aG/UxGnd3fOcy7OpCZhYfwDtiMlZZ6kbTQbfmEdF5RHvgsY7NAhXJmApu9jBQvCA5cc2FqGZEublegTrEHtbEKFGeg0mownhjIpu8nk9PIaxktDbJu9/6ICoWt+nhyYIKqraEJCUXyAo1UmPgo/SJxoYQSgaPsjY8kLQdKNKQdIEJDLjjKsHhdWTJ9D44Qw5fpApQfKeerN6u61ZfWho4oD1rFfKBYMn1DZ3N0FL5vVMV5h65Y+4F+H1MjNeamo6snmzFEH0QItJjzHP3MzpOZdVfughI8XpcDxFZTjNlNFzYfLdEB/laCWmh7Ybp2I4YhKbInxxmJfr9A/qeHur8KDctv4Q7myoiJxxGcdLUbT6mL6jz8kx9cQwfawyHuGMiGFVQvfowVT2QCoNU3sfd4Pm87CwTbtZA1KQit56nJhotfl83Nj1CPW6k2aeXiraJWhPzQXBz9wevx8xiXmn4JqGKcrQxkdCk57R2AJXeGKW4aZXxpY3JSMIuKEbiOB6WRSCO/YT1sOzECHC+vMblMXekNQ0uCe6xYT0RTgIx8TlMXpgyrpBkUvaGOmg14zJlPvkiZyeJIGeSWkSOayOPkKfowSaWx9nzfPHi/B6O1T95DQec5YzGUaixP1KwDF3eGmGxG4cSQzVTVfVcUKvpSacgTvHz9rzEHvDsNmuwixvecyUo6hXjMNwu3E39Y0FzgXPRhDVsUe3mDiOOK+HIdhuPZ4tXJQMJagaxuWHAouTY3THdvven/NcUVlZjt8hcW7sM87dPck6SfNBNblGO20qyNW2dm1o0UNNDHndOJ4YemcCxKAgw9vU4bD+EE7ozzDgKPJUhYPFjSJqxnma2cFJqUX5JzsA5yOwyCi8IvFnmjVMfFXboBz5jDEDixCq5asURFtGk5X2yh8HSLtzoRzvqbeMjIT+79xkjev1m65epPO01Jsdn/Y1eoFKbgSNp9Rj2t9GWTj/lE8f5y3i25DWHz69ip+DSGJNaNlosNFFAlnWcXjH53Q7dNwe7342S2wdAr2iEWuKLYnsiR4Q5un2/DGMy0JBuGKWDYRknSTEkZJZPgVNCr574rAq7EkEyY6CMTXo5F3H6Q31dD6qnoUjyAAJFJmplzOwFgwdndmC1TINsWg/Mf78K1SV790VBm/9XpUQx41ei3VeZ4/v9run1Jg2dVFEqTd5ScrTkKfIxMwnjZ/BmjLHTTPTc3kPzW6X0wKeWrR7GqeBh5c2rRIuv96HTYVe3gGR8XTmqfPj5Tl+Lqhm/QHt3sOyEWCbAaYZETIEH2s/5qhyTqZUHIqWJpkMn6VLzUBLWGu0tWb88zrkoZci2WeORfoRwrx+Hj9EpIYYbZk3RqkuNbVGcAQTZY1MVlGv8PGD1GHikc2htOPJUL7v3uxz0dQR49MH0tWzXrdefR6AEQRrzxPUmv4E3dM432J8cTmkI27YRhDRIHd+BIF/Hs4oMqTpWIyvntvxU0cUwd5VEQ6egdh5MtE8TztyeVMLp0+tSC/ZsWxDtkBPRhChrTIaWE8IRaGFbW2sNXLA1jD5eiP7qXwcJEteQQ6mCiK+VgtNDfzqjpJ3oF1bK8NSPJh2IlgdMRi75Q6byjRrO3rw/vttD586Uj+MQ/PkfkiXMssgi3EXNJteKX3n2edU5fL0VYGphziEjIuVQ1+/mC9FKEqoMKjLFuq562uKaM7TCtqus882IdH2hL09yAJ9nKmX6uF05iH53Hg5QOjGDnFTyL69yeiBjEApvEzY6VmTWYXxOBeB14IyR+LPJbPAKWEZ+poOl0MSMHrSgc/ESEF0XyBYwiF+qtpHEXsJ1GfAqhSEsFqmpBv9TFPTBJW+Abm88scXDn/71tAkheUJBdMB5s6xcQGIw9wdC467u6UMMJ3pio0iqp5f80M+T+c4gPkySDO44SHbHtXyiCWcyVeeZciWPw8Z0QbDxOS+iZWTx+tlxjRAGyOdWeFjBOnQA00uqcZ4WoeOI6/2FeQAACAASURBVIaU4/GSnTDoT8+Fy57fZIkVMFNFsbzKl2hMAvBmphhnFl3HgYgzDS7Nt1PrdVJC9uRgMDo6ahtUqvM+MuUVhBGkJAWxKZY3giMoKgUCkoEXhiuFXvIJmmZ5nuMFx7dsD2MbtxjraUgWlEO6mp/G9gaPpz716PR6ty5dpiuN9PUpMZTzAyzUu8440+pKGnC4ifF5OR5nO1hKy0LXniGQr8AyzWKKFTQSjuiWE6fd8cVleNkOKaupqyu0nnZaMi00pdblctr+deNp83jy/niaNSge8nCQ9VFCu7BNVjvxWF28lAQWTr3Il+WNPFmY41DAlDCPmwoRQ1MQotSB1zJeT+JxU08pCFMsNqs=
*/