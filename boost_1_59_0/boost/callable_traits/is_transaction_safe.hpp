/*
@file is_transaction_safe

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP
#define BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ is_transaction_safe_hpp
/*`[section:ref_is_transaction_safe is_transaction_safe]
[heading Header]
``#include <boost/callable_traits/is_transaction_safe.hpp>``
[heading Definition]
*/


// inherits from either std::true_type or std::false_type
template<typename T>
struct is_transaction_safe;

//<-
template<typename T>
struct is_transaction_safe : detail::traits<
    detail::shallow_decay<T>>::is_transaction_safe {

    using type = typename detail::traits<
        detail::shallow_decay<T>>::is_transaction_safe;
};

#ifdef BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES

template<typename T>
struct is_transaction_safe_v {
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
constexpr bool is_transaction_safe_v = //see below
//<-
    detail::traits<detail::shallow_decay<T>>::is_transaction_safe::value;

#endif

}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* none
*
[heading Behavior]
* `is_transaction_safe<T>::value` is `true` when either: 
  * `T` is a function type, function pointer type, function reference type, or member function pointer type where the function has a `transaction_safe` specifier
  * `T` is a function object with a non-overloaded `operator()`, where the `operator()` has a `transaction_safe` specifier
* On compilers that support variable templates, `is_transaction_safe_v<T>` is equivalent to `is_transaction_safe<T>::value`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`is_transaction_safe_v<T>`]]
    [[`int() const transaction_safe`]   [`true`]]
    [[`int(*)() transaction_safe`]      [`true`]]
    [[`int(&)() transaction_safe`]      [`true`]]
    [[`int(foo::* const)() transaction_safe`] [`true`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int(foo::*)() const`]            [`false`]]
    [[`int() const`]                    [`false`]]
    [[`int() volatile`]                 [`false`]]
    [[`int() &`]                        [`false`]]
    [[`int(*)()`]                       [`false`]]
    [[`int`]                            [`false`]]
    [[`int foo::*`]                     [`false`]]
    [[`const int foo::*`]               [`false`]]
]

[heading Example Program]
[import ../example/is_transaction_safe.cpp]
[is_transaction_safe]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_IS_TRANSACTION_SAFE_HPP

/* is_transaction_safe.hpp
WJ63iNStRfQgCjJOjJ8ck0qTOICA4Jz8pwUIk6ulR7wVt1d9rbjToDR4GC6EigrMQfsI4eokJZSO8jryGa+zmv2V02ToCe3TNdtTs134wgTiILLXluyvAbIFRvOAgTu2rRW+Dku3ROGVTQ1Q50tauXdw+S4k/jSX1Hf4ASqEH+rPjDAAihM2cWly5RGCidTGqlU/SWmRldMI4OLBLx6tlqac1g6Wwxaf9eddNyC4rkccN29jVLWonF8cwpz7oaAE4EPTMyUYvbK29dxo9RhuF8Y3Awe1dPorxj/q0DXJ5LlUqecsLbuzuOMWhgk7P/tApjObZ7+lybcQWRZwWsQ0iYpl/3vTx2WVWwZos2iLYH30cER+JWz0+rIlhI5YW3AIgBdkohPgja4Hmrt9VWb2TEikt90Gk57lxXzMCn9pn0EJJ9FC3xtkjYyYlYKm9pHYm7jf2R0YF+YzPuBcccxCHzxcf39dw2rbOhA4IwrKs6uZw34wfiSsHY+fqWFvrwuVkdRoM4uGsi1qRLK7eykm5vMa5gDU+08nbjp2Pq+2WTDgR+5RIUL9NfxqEBodmD9L9oroJn5hH7Nm9YQRlxpODxO3iWWw7OT5nAhji5YHakioapXSSbNJ6WgS9YO20OEY9wp9JDTGZznN/zxVtl2gHVjmMv6MPcjOOOYvSh171nsdV18mkqavYDOsRgySZQ5H3QXRfIVWhNhibg2CJzJIYOdmrCCwHfyPlWUjcq7mPT8JAax87DEgBcEamfPjRZVwLCr6ocMd2w4YJq7Zh9lfjjJtt1dk0DgRQieZ40o6e3+hb/83WW3bqOq3oUoHIYbA2VQfwil8D76OizBrFFRLm2ZZKn6NZW+hdndl2dx38lzxL38ECBGMICWQWp/HSl86ccFfsjWL07eEyqY25eeqUexFTODLTYKP5QrFJy9Qe0BaBEjQdSEHPBOnjRDRFvpYYFittPG2EU9NAW4IS9Jc74uO3uBRMQLXT5kMVupIS7SrZoiFZhwxp8XkWgjBh3zkZMzcfmPNF/vxTCdFpuvk+TEFAsdJluQdTxWsvFFY3DBPFLjXjp73DqAJs+CC0v7hRZ1kZMzwfsSB247382Xnc9e13HhQHY4WLjlzkMWxtHAhDBRs7fgvrOOG8Njpvc6tNYzoaEGr7wBIeLhozruFJN97wvrTQeb3iRO14A2A0Yzwuxbji2Yv9/0k24LX1GHqns6M09clozWPY9anV1ertjVcux5qi9ZQBG7kR0ajrwbmR0OM+04117FWO74l5ykKlNAPhjyMuM86mXE9GFFG+MFXNygUqcHT/HcgOwuC78ZNBV+8C65u6R5kw3YWN+Enb1dgSIzZGIzmLV0H0hhkxgrtq3oxTaQluvxa0QhMhAdSVFDm5YzA+wU7Pce1+Orh2yH8sum9Mu4of5QVe2PFlU9EGFYQ4mag0IRsRg3lBbZ72eN/q2e9ixcxWTSdUtKIe7TgSx+ySyvrqG1SGIPG/BFi9r2Rh/XAmHrKiP2gejEpofORaWro4kmhCwJQMYInJ+NOX7yUvoYx66nfEGd3tYaI4Ubk9eNYMJcxN2SF1U7TgJcBjb/I9g7bNVSNylKz5Tq3YNx8KVhhVCgi7L+SUYSm7olnsrdx63o6A50kqhBSipTH1n6iQKE4LBKffjssgHu+LkRgkPohTWSkSeJwjG9NdAQzraCvGq6nRSrxK+2denFlJF2hOoZ82saE9Z+L5h9TVIKvY049mF88zL7DPI3uvJVqeFreMtrQuVUTO+w+J1AifXh/un5JOESHyEw0Nji30KHaYwZW3f93WOKpXAI8K154MtjesZAmd+vH/4QsugVAjj4xv1+2a4l4Ht+RdTME3xpDU/qLrHv4h7LfQlP4v1tMQPjxodKa6S1nkL12wS0OFAdFERzbUC2lfEtD1D90d5NP9GQFlb6lEMREq3nZoT6oWDqV8cNc6y+ODFMgzXXU/Nscj12mec6rkFrUXqbOW6KjIfI7JmIklMU6qKMaJvrP9wn0k3L14oCsdLjysgkbKgPc4wzgL/T7HCW1EUyRdHCuadGBnA32syFzqNOuIr73XL7omjQPmYw4ofIWdAZr4ti6g53GxU5Xuuv3Gspp7r298Tgwneaq55JnV/PzTPeozr50OvUac7TdXPPat3T6r9J4E5LkNKwY+GEWku3ihoPqwStDyUOiqRK5M3XQ4DkULTWUZ8oJ8zx92CA7LsihD9/LQ4+lPi80qcEbARr40JfHLmwS8l7ETh+3I9jxl/COuEfIm9mum4yimuVKI9BNf5K/stuYgBDEEqYkN8XgpiMTUvNeQSxGVQS3WEU77OJuMoSlu60AYu1DkZiAGPd86zqDTwROYpYq2k7GaSfZFUewJGPWLShI14WMFjIrn43B5ENSArvMdWZmsBb8S8yNKNWJX/LcxbY4WBtzX1Irh4FzNFgBRcbHnU9NtZ8tg71xvhJ/SG4qWPY6Hk075ImRGBbszpHUZ0UZ5zVaXyL9osWiDk4VfD08eLVnh9lBEP0LDelXyf7ZIUkTSw/72O3YLO0e8ImY5p4mO1mR/urH5HfMd7GXJunzLxvYH+8vr40OdBn7NyGF2fJ8t4MPuq/kOhjvOkirPIH6+PMtoe4jghjHOW4no4hi9/Eb7JxeiMZiMQVu6KjLuu5BcCo0C53u9zx4FcWqMWT52jecaAsyQR2CjEwhe7VwtZETQPcjg/3fTwSM8MCsavAicRB9F9VbE3vVPRuunqwCQ7saxu7R3fhf6ATKzt2ssumDoEeE5HNZQEbvqXHEXNdzSK+sFKdQnmspSBdfCRuSpMLXUVU88m6dfk33PkhsxbYft9ZCePAFshpBjjbnkfofRlqXvSgRCMHM+OH4UZ0wAGj4LgvA6fgdIOZeKZGDhYnWzDibQKJZVVE9lLOhgODAkrzpwxpjuDFcLyn7v/3rU+O2ChfKaae+I+yqjfvrZWGxK5Fd6jE6jrZvUcLqihcVxSGFJgo61ubo+R/62KNS21JDgFrnLeeVLWw6pC7qtAZpi86114dSwanX2t8k7DC2NLw5l5vm8c2vjMpg/4x9vh8mycKVECC/PNhZltV2Xpt7YL7Wr46LoKx+bP/+8uN3ujHKFUdUuDHETVOtd/Vfu73+wdx7bMOXH5vOzEeZheKRWPZB2T9f6ZqO1d5GuEycbfAFLKDAjP/htSgm7y9MvddqW29L++6PSBIUBEWKVpynr+eenoH1tqCllcRVxf1Mumsl6lKYiv6J/TxRAnnn80k0QXHbpzEEbX0JI2bbf5Rclc/eREibRJ0ACqT5ItqafcPqr1w7XvLGlzE+1qtuzgTU/f5cjzDDEqS7RamOg0+L06lOKeGPHBXwfDJbLyB+rDpkD8Ve1csRV4+757OCrMcAGHxIozhYlKHWvbztjy/8zOGbDTpOFEMboZ5L2UBWkPGoQwECLSI9DAVy+ad5GyVkEZxKzU4AWdLSnMX4vjHAwbEWodle4wp1A/CyI8SYqlFnIGztmYFt/DsCOJP5INKle1g7C7MvM5/PlmW66DaPGARn4X5NWHHCtYo/JzDCwGP+nBccT1eR3IZw3bxhc+rQ/J/2YwzFipo95eS53TPHQpGr6jQZFnBMXhIpDbQ7uTvi3FIN57BnYHdzY9jfcrbz8hq+bl8FWOGMrjORG+NDXbr3w1IVAcknCeUKEUZY9+beesc2/0shWipkQ1TNCnlZrHG7Svbi1eJ9k3Fgojpfp2x9Cmm9Ymp6NG8PmXxfTbfRYIqrQCtpJ6mqrai7gYTXUq9bdj6Fc24vl+YG+DJFlqB9oqhJtxLr3DxNlpAZcGltMHf0gRXtrV+jlLWR+kKjSdgorNFMZPstF1e6LApRdwx3xx9KzdGBsddODc9Yl85VcTVev4Zvm/k+y3InfgDOEsT1J/JtDRKhyfOp9v54hEDV325KDbsHDplx5mjA6eVd8XEW7djYSOWEt+T75etDxecWsN9MUjRKgaqp4nyAOHdiD0nmxDPd1fMVCmvUBGnmfGygr1SzXodZ/zooJejvO1oa7ptzPh2s5kTqUtTPRZO7m0lLL9ShXcZC4rvpbdYcLv4OExIREOnHXYBcuXf++kPYs1fdCYMW9hFDvogYp8hLkCl42big7IEB4FHr32fz4YrCpNxvcJACj/OVuXxABrdZ5Kjy0C5Zqguffy9kBIpioY4fSLo5qekc2JqRh6U5DToe5DCBcAdvQRR43XYgAhgHemb+pHqxOFFEMk0ApD2R9DzQQX/rQlY2QrMYvwVmt4TNMf1crbLZmnZmwMKJsDTk8bYaJRM03n7uPOa3OAyKRPx4AkYfcxlcyMFE2grjbcEZvTHiZ90PQMsMaBRrkYoDh4cebLs7NalO0tBJe2DiXVemHiELL0bhj4nArNxx0SXwzE/SoJ8VnNOgM0wxp19vJ2CBs9+umwNmaEXx8lmaJgTx02Ufvwqg7Q+dFJbn0D6+VUWjf646NtG3CkQLFQ5JiL341f+L+7scn7fTUzWBmsuHDTjwxkLDCy6XQs18h4sGqWc3b2z5WnalXa35jUdCgbpT00zE4KOmlQffBOt0cUiJZj7t4dHJ6btjXEGLm0SfWP6nEzvQXSTei9mys1EUEO1ug4lcbXun+YAeSWORL2Q81lxVSbdF/tEkVpQgUnL37qgD9D9hLLo4zTntF4ibGgZcRla7PKRoM4erCB2r4VS1+KNQhhfDZDnMzIgRPaNSJwVcK5r1hiC+g22y/DCHN+WMHXfowRtOfU3f+jke4CmEDYO2bRLc2K8Mnt7S2R4nosj8jSyeSi5tF4+dDnMF4pGPqXjPP6d1mL2rov6FgiCxCKdpWWbcnASmLDe4/9p/BxbOJMVn5UtkFL+OXoAjAQxEaa6iVs1tNldPVDGds2xer7xeBojlB5i4kuqji2B4ERGjiWV5KAfuQ/JGb1wHHlcypx7UtmT1KeQxrlYIgr4NhF2UTNVc7JIsr2JPcRoskAsGnPkI8C3ARmFHD0Mu3HDLs4nnvYCcn5DDDsFbDMGfdNZgXxWw1vN8lIhBEb4fQOIdrX5eOcTm5BRFsz933fHbZZbzU8e6XTthnFh3K6Df56VN/kjYMh23il540zg92QMF9nHXNNq22XcryerYsWTnEmlFg0XBnAP047nUzJMNk1U3nGlh1gSceAfhubErTieNjotKksUymBl3ooQFf+n7cELPPHtcRmyPO5CCPyWGb3kIf7Y303jPs5hlwiziviVdCOvs/Vepjm8R9SrMceWjPMmii8hue17dojcjsQ/lLLouFCVXCmdMPanUCIhLIsUD8SFA1ApKd7V7+qObvc3AK66t6hKlTQ8Mi442YpkU4YaGxCJKWzn5ZuF5I0/VYzICDxs2HAhPy8fQf7NHF3znkwPdBq0zMX81xAEwDG4W9sR0yBzehmbsLB0dbTiXPdaUmAB0k9IH1neX1oV0lLpOFZSMv39E1KqWN/3XqO1VeR0XJyJ6EFEGDz+s/lTFkHFqWLHRMhMjAmoKfzWaAH8LEcm6W1SyHHdlP8wS7hRZ7rE5pvfDNNFuwTtq4nNRld8mNMc8HIv8SrehaMWy9blOWEPtNv0jKNB13aIU6R13ksWNmz3YHEfJZbaXFDm5TYROr0XfcYpjQqowdTK1MYz75plgAWremlBuGzk1noAJ1HYyzvL78zm3lk3j7/32YLSs6AaHtcE8S4mJYNj13uOxUBepSHrf7Ci7jw17UOzYqOmE4vKgQdEFDuKpG+dNlNFOUQ+r3zMB1m9sFcdglGer+GPhRxRqGL4FbUUimSGlW2sE7hgoYQKZpf9SDd43/Mhplw3r1L9K71lnMtkdMR7iA70Admwt2jVGtdpmEfuPhYvwjKhvdYbbCIiHOHTQmEOVviQio8MoS72GcIy9T9YIcAuD7IGMwlqEFfXCKHHR8HEhnl5AqeZjVS3Jwmxkj2a3PNd0x20ftRChC96xsZQpyaRfT5jgXeHFLk7sjoRf7lvA5bPj4BMvIk6xqu3mngILh5c13y3njsEKOEKuyxULtahJ9W7uqJP+Fdo8zUXHGWHsihdwj+NSqq7Yd10IDqKEdCXzN4qtamGsBaZFypeEIbi3jdZqZh6OGpJUPk6gn4vrwvhK23FO5pdjXEgM0lCZhwuBybFPKOatiQ/5sP6xzjEfoa3sF+lTXiCStMScqQ3qayHS0YYEaEwXFBNEtTzDkg4Qaav+I26fWGU1tPH1+Tp+WezjwloO4uXtL5xaJRGFmphMH28ll3vldtGMOCw7vYZZbdfTulB03BHllZIixnZzUf28UOixsL9M06OqNrTxHLaNxSOslpoXkI9eYIOY5YuMuXaX1leJz/CjhVhSiBmBQJqP+iCk72802RNewrfopnpxj5488TDNVegZh/wi2tU1NEMH9U6jP8bPH0HlXO6BeEDb4g9HjuHc+uMcz+klMR9+XPGdukpzKTBcOh2StfUJCO2dDaqRijQ1cw+nQhHh1RnVr1Ghgxkf4/m9Z7Y0W+PG+VQbyZ3/WpuIYzvbjmnopRN3T/HyQ/oggAkOUOOH3kirlT1svWxlUNlPfFufcQiU6wHZTBqp0ASsSRCLStvGgEuZH/q40hmZJ+vZHA/DWSMUOWN0XbBQYCXY9X8dxCEtFXUKKSY1XyLZs6Xlvh372Tpe36waU3fgVv5Tv0om5N3AY9FLQUOsWR934s7gSHxk1AXoFFLfQzcPkNjhBBGK0kQdDOPb6lTkPMp7QzyTnGK6xOxvl+oBlyUgkeLCfoGhg6oRVRo0ERphqkrT6UKPkej9AF+FD57XR55cjhPh+etjGzg3vE8EaYxbnI9x+xMHCghL+Y6BVxkrE0HGysd6o08ywA6yMGVvg3MjjANlCOwlufiN8syWleBPT5U9/yEWcotbrZiduUD0dN/oj0Ayd1V3bkfzrfZ7pdjR8j9Zw7pjJu+0IjMKvgw7Rk99NLSBcdN4Ar64+hwdomhIV9Y3cPZ5/1S2CwHIxZpR+0ffmGKgnMz/DloGHfRb0wo3WlIVGY2u3HAF70xum/RQUEWijtseL6Cq2pcxo9BwTOuB4kqO76FfkTmsU70+HmfEQc3MN15plfmEZlPbjfqQKJCcLFXf53XrDNIaR51uyvW/hmY+Bg2HLNYk6EmtCCYxCMFLNQNFL/ii8pLUy4s2twTeB3/lswoNSADPtKrDYNlLUwZWKDcxgjxR/seAqH7bwt7anH29S5PNwl8jyEKi7jUjzOxZb35HuDRRN2NBFuC4CY0m1PcmCLUpoBcM4KuwDXgOU5v2I4QrG38qq5eTySajuiIQIY3rB0gisjSz/kD9MkHhRHrGGOaEM64W4y/iz/vxX/1/k4GT7VslfXGX7O0kmwDNQNqqRFAwF0nNu1k1T4Pzu1DsOqlasoHT5qc5zachawC/VGgDs8Kc3nj7up3OhihT1OC0BNgwSpRjoL8ee9IJlY1KHD744SoM2TCKW7OwH0vIpj39QQRdTat6Key8/ZpNTi7tFhf7yEt/2dlcylWjf2OyRuRDaY7HmQjugEzxRahWfNMCn+hEyfkJb1LT4zP8XxYUfASJPrbVGK+XPnEkF9mNqsMZJNsIpWUYHyjsthKJ/PwF1im6q1+x9SrHHfN9zHMd
*/