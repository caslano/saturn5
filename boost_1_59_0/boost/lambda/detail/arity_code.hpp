// -- Boost Lambda Library -------------------------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// --------------------------------------------------

#ifndef BOOST_LAMBDA_ARITY_CODE_HPP
#define BOOST_LAMBDA_ARITY_CODE_HPP

#include "boost/type_traits/cv_traits.hpp"
#include "boost/type_traits/transform_traits.hpp"

namespace boost { 
namespace lambda {

// These constants state, whether a lambda_functor instantiation results from 
// an expression which contains no placeholders (NONE), 
// only free1 placeholders (FIRST), 
// free2 placeholders and maybe free1 placeholders (SECOND),
// free3 and maybe free1 and free2 placeholders (THIRD),
// freeE placeholders and maybe free1 and free2  (EXCEPTION).
// RETHROW means, that a rethrow expression is used somewhere in the lambda_functor.

enum { NONE             = 0x00, // Notice we are using bits as flags here.
       FIRST            = 0x01, 
       SECOND           = 0x02, 
       THIRD            = 0x04, 
       EXCEPTION        = 0x08, 
       RETHROW          = 0x10};


template<class T>
struct get_tuple_arity;

namespace detail {

template <class T> struct get_arity_;

} // end detail;

template <class T> struct get_arity {

  BOOST_STATIC_CONSTANT(int, value = detail::get_arity_<typename boost::remove_cv<typename boost::remove_reference<T>::type>::type>::value);

};

namespace detail {

template<class T>
struct get_arity_ {
  BOOST_STATIC_CONSTANT(int, value = 0);
};

template<class T>
struct get_arity_<lambda_functor<T> > {
  BOOST_STATIC_CONSTANT(int, value = get_arity<T>::value);
};

template<class Action, class Args>
struct get_arity_<lambda_functor_base<Action, Args> > {
  BOOST_STATIC_CONSTANT(int, value = get_tuple_arity<Args>::value);
};

template<int I>
struct get_arity_<placeholder<I> > {
  BOOST_STATIC_CONSTANT(int, value = I);
};

} // detail 

template<class T>
struct get_tuple_arity {
  BOOST_STATIC_CONSTANT(int, value = get_arity<typename T::head_type>::value | get_tuple_arity<typename T::tail_type>::value);
};


template<>
struct get_tuple_arity<null_type> {
  BOOST_STATIC_CONSTANT(int, value = 0);
};


  // Does T have placeholder<I> as it's subexpression?

template<class T, int I>
struct has_placeholder {
  BOOST_STATIC_CONSTANT(bool, value = (get_arity<T>::value & I) != 0);
}; 

template<int I, int J>
struct includes_placeholder {
  BOOST_STATIC_CONSTANT(bool, value = (J & I) != 0);
};

template<int I, int J>
struct lacks_placeholder {
  BOOST_STATIC_CONSTANT(bool, value = ((J & I) == 0));
};


} // namespace lambda
} // namespace boost

#endif

/* arity_code.hpp
HfiY12fedX1qQGNVANu9i9SURgTlqoIfnTj2kRa0Wzhdklctl+GX8rpIC1ozOCmhJhThg1VYA4YBBdDbRrIifnhUjz7TtVCR5wrLK6pIwnXUfGAmEvkrqx0leRYNrg2hXO6bPbAYifm4x7DwPCnLbkMN+c/pHowrVUYrCUGi0L5MUvrnnwVx2qRW2ktlH3nKmYw4tjyxElXULtxjkOWkm3/kxkWSjHN22Cda1Mm+v7t0o85wKDnh6d8GFTq1pLmFAPTsg98fh2P8gCOpKVXNcDe4qU/q+LNG2dpEsSkQAADICsEMZEYD4uvvMECww2hwytABrwhIxdy3i6fQGQVp5x0wAy537YyMeSS5hEpOE6acSXrqLjWKniFu6ygJL1VhleLdrywMvcO/0fnoVbfAF6Ck5E68fOkhIwY39lP6bkgA8kHUDnh1k/3c5L/0vVJz2jVbN9iXjDQTI2fnxf4bCnRKsEHU2nOtycIqv9YgTRGEj3Q5Tj7XbI2pvYsQKRFtIfVVmP3SW7dceYWuYD5xBhjTdO+sV7U48Yday4SX4pdM84UXfE7Z4NGHXLUZLFeb2l/6m8+YQDqZveZDAP+4bhwzygXpNsYjIRUpnHUnYMg3BFz86JH+eUft9ty+pU8Z/WXvja6ve9b+Fxq5pDO2NumYljl4nc1OGXjeyj3Gq04PSoxSpzkPDXM0n5uy36SmKlm5s6ou+luY4BcSHxc+q+EYg3ujeaQ62TW4uHTK5xthkGHRdDMQQwj441KdFEnLavBwMr9cIoZKtAmf3b/rkhEz9ca8PWQfBnUXx7QavsrxV9Erl9kLbu3toiieXBEYCyxcEKL+Vb4p31p4ZZX6M01Ijt0ALxVPPyK7eglsYIOCYBiBahbT/IZ1IET7ndvx3NfjFmRGAP0H2H0EaNilnU3AgMZNKdYM9vElUifE3s3rB4YFozndi18aDbv5I7HnHOqiA3rP0m9KowPYJsengBRfmPF7P/F0YEwgA+w+0D6TXCvK3cJMIVzu/gNkkxT057+9M8Fb/vAwDjmbTwQrja0qpYdA9d9xWZBYXSxT7W9gwnGKdY/UYDIfEdy1t7KtxiDcG/rnCFv6nQKbEalJ5JPX5gj3nVvEEU0qyYQRRDSlVkvydHDFvBedAbuKRJ6nfenwkTbJz2K1zkY6QtGW/MrwtlDrdCyOtvN9Wk8JRq4ZSzmyvNcBcf9CC/hbyoWS6ph2oiIhDHPUciLlsY7tBHoQOeaODEKrSxme5GPgCmn7V3DTjisaIBMk/qb+nt5TDHaXXNlOenYNRktICMXxUQXZM082HjjB8TY3/q67l4wjXl9Yn//rE7eF+AA6bCTHCEyDXFQXtJ8f7jDaBRpmWUx3+h7TNiSP2Z1cBsRf0kb1AvoGcUzlvbf+clfkRwmLtzQB0keQzsKwlyG7m4HjtRxKRHAO/NncCQosEi3jHlK1q6ONHmfncik+ap7vzcrtD2CDudjlTkXzq5uUu4mj9SUXjwATLF5DFpKcaFhHarOznauOfbv/5AvXDgyOJkHQnHNb/ksGQp9IFPbH+/bWazPAJGl4l5KRe/6WI63avzNFAaGiGPXRJirAMwYLdvwhON/6pOU4kq3ks0EgAubmdwXq3WX4neo+uKvo4fwvGDtd9oh+Hck2ZAO+sDU2v9KhRoyiGwe8KpslhbGFG3EcR9hH1vkhiQcPGq3O5OyY/H7ilYgZHJls0eOV9Nc9VU8xDbNa00z61vSVTf5UNVtKT3eN0deJjtv5MKkLNLDp2LMM5WFRqpAMb1giHtEloLCnML7F06/AX490hR7hqeoCzc0lYiQOivLsEPdjlR6iiCMvWwbcCaTnnF25dOQKCnGnmC08SK1wpQkKLFJfdBIHJB3gkajYiIBKpLHtsqs6EXnGHup1jDyM8W2cc7ZxO1cIen/1Ta8tzLQ1w/oePFSrYlRU0LRVUSwyIhhKqcwihGHwP5p2NAcT/buGfC7W3vINjr+GLjj0v+U1HfN6paYj6LhOLT1nrF5vt/re55CMR+4rlm0uAV3HUNoSvnfxS7/fDSlo7JGsKP7kqqjYWeK28lzXO1IhFqVpAt6PJ42+Gh/SZlYs9H1KCcIgnKT6MbWx68t+oxaRsjWpyRTtd2QwYAdDIu7PobUITqFZr52UQO5GzSEhDlFCNmc1lbhb0liUEWphR29KgVTQCgTbbycdrRuiMMJdnvJ0PCFwbat7hqim2FiH9UEfy/G65+YUf+sgbnii7VL6pOrFsShaHH0N3r+7LuLWFfHIBj+uylU1bfsMu/1eeba7JF/s0tMbraU3lBxqvP+dH68OXbM5qEKbb6ORue27WJpnGReOG1ZWgDLwUi8ukaLxiVcVyJVOZI+w9bcC97u32qB/Npd+dNs6QGSyBUGtsMe6Riyf3e+15nfibz/uKK+wkeyYpWC6EFBeyVO6A/twmkRTCOkvWr0gYQpw19zvAYqehwThed4pttzWm+c3fRh6I//0z93pAtMUdnFHpSVBd7GO2U4dfoG/y2tsqYevoaoLFo9xPpFBN08rSz1rdmPjcehh/ieZAkwQsq1mhai3nE74zW4rjEP7eyGb01YbhVBBCC57NBtmNe7iYN7lloM7I5JXUs3Nj9fueVDv8Gewlu00wVbSvu83bj0MxeISZeFT4Mj7BspTsYhLiyyqK2GoWEURw+q6mJ7x8ba3+yBSf8++b5ZDSjZZjvcI6WDLYHaeTOj6+wF9Zv7G4X47SfFgZzirWY9h4wl2vKgKvGcgFT488EfwNy4UeaPnUgzw7rhV4zbkqHgfodFkBiI7beXt4RVtGVLN7VfCS4bOYA0fAcZx4Kq1QIuEHlMs4wTRielTjcPtV+uSmdkt4dwqZYOKxj2ndDyvrRpEUfD7jj5xrjp91vneItCFd7PqYOxp1tpOd9NR7L6UMq0cGCnfgYGtDT7I1hsy6Lk0H57XsCdyGSDoiimcoh/JCWGPZfpi1RPTWpHq3wcag3ryvsQk41IbtEA7Dr2NcCT1DA+BJp8pl6MGIvPWueIQNHaR0MiZJvcOhIVLw4eJsmu+yevpGArdoA6O4mo7sNmI4x9SkRg+XUnrTkSC9e9DLUhNt12FdAwT4l13WXAXxWRyoGESyIdMkbPe5aextU1P3JBFgTGv3/nD48uwygnkS0/JDmdbhtyaTjpATFwUAhPRpfJjvytiel+OPy3/3lrGE5uneIhYLoiEF+dkD25ZvGML4ViU8TOTVcPrq9l8NE2dCOl/DkwaGxmjFBqDk/r/t4uXGAdb178mQURdO4FbAa0hPbFMHAI4pAJi21/ritIIunwm2D9/5+6r/a7Ji61pah5br7nW4GYlAWbU9aVCKk9/o1SSWSzbi1NKpC1CFkHGBUCjhiObk6saQ3ivIxFimuSjtbFbP4smsEsy7JdP76/8qWd6ukMFoTWWEwTqGjzuenHN3FJFQpC2HEphhwr1mKUuQEckIrJARJ2Y08OaaSyyEPOKSMHCHoAYZb+he/WgRQpaI86PBStER1EiBp3IgE+dcnaPOEtxj34Dh50phFo43+sASiidxAeADKP0gtYBqrkF0yzU2KsYJ3a71bSQek/zIJMQDyhxhQJJoJQONZNcC4Hy4NCRSOUVhk/QfG/yIlzL/IKZI81ADyAzR5PY3RBR08G8ttHdvP1B/4HLaaM3cAN1Vpw6aaYKXyAKcUvMQQ7hO7b54fatUhbWXGx0qVBqo54JDebKfnlsDfewhw/quPo++KZqFTFA7nUpy2X+cSXCVinOjw8KZYwfIKShNbDlsGo4V3QBhBwbTrFBnq7cLiQG0kVl7eJ0141/g/T8S5QyJvDsqWR47v6+0sg6skYhVoZMosZKJ/v0Vcogh/GvyBAI8N8XbJiLLMPMa92OSP/8sv1+o2piRXP/1fbeNGiBBp7DK/MoYoI91qVSLB8bg4lMVwVqIpkzrek+KYmdiJ1vzhsw12YpIES8YUZYTW6cFwu4fsk1ZK5pIE/dwtIbNtSgZiFVQZQhEdV600Jf4Jhcz2qkq4dRHVfCUnCOU1n/kh/fVM9rAFdRPG4XYrtDid0Y3OFhHG7cP7uVYXuElyNSSKXXyyrmUio3twDNwooMhQW2+4MK9GJ4GOT83mX64ciRI/IoRcW2kL+/GeRUSLoTXa9wkAUAAMiBclDJSnR7gUHW+8P3dXkXmL65BQjoBX75QbJ3X7pFfAEAID/XTz2Pi6OD/6snsaPnTGI7Czp0BPVZhACu17c0Z08cr4nev/WEVN+T8VFs87XPmMpSs/zUJYbLUSyrvU824sS1EdvuhWaCpQArNSQioFrCtzmZY1N/Uj7zBcj1NeOPL5XqyfsOxdaZdKXEGJEDZHHkPsvrebp0BWBKxHKBiOFdB0WfE9RAKH6wYZ2Dsy3yxWsgplSACBCP6lPasYn1e8/mBzO/98Ks0s66hr5AgV5GUXieV/1JhlnG0G4daamkPHay3KJDF9bmPtyrrujSeTyk0T7v86R88rc4XuGD3Uu1MCZCqL6gAdAUInwJD4IvJctm5W13FsXFbe5MF8SkGEAGYGgkMEFCbOTPGs30wmI8Lsg6A6ue620fTcKFBmoOfvFKhK0KxxYHY5gvIoeHJtMMJFQsdG5SATSq7HcPu3j0sVO4bv5xfO37RcbK+7ph1A8MmMPsQBcGjOzEOCjrLvQBCXDT8P7yFo5ODef8w4W+dXKLujLzIJVNgEZdHNxPVD7Nel2jZMJCQZaq6b+UiJ0Ei5BImmXDStIXCUfK0eyVpDLMImBxVEYFaQHvrDZjiZtMaHFOT00vYKKU3WJteo2mJJttZ6256tqgOZxPv2S7Ra567Bd97VNIdt/zdy79fISxZgI8e6HqSKUZdmozODXEAlFWgG0v1whtsr10vTPhN8qbOmvptKgHLZl89z9B4ks2W0w3YrNmcm6dMlEZrn8uU1DGaCnRpLAAewGQCaeFYdypQmlhsLNxL+DlGiNvLF9jGCH40z/35z8tp/nTclQ/LQcAHRFVbAufsPwVuk5+nLlzh/ClPw+o+idRnEYAIQNcjHHDa16bbrJIv42WjsNHUTA2Ht2D9af3/jYonNqHpzpduCMe8vTYt26iLbkDqL7179JP0qpMd6COkkABgCHzoaioAAEQhMoGc2OzEDt05622yEZUXEgSjN395GGFndSGQ5WT5L97qNBKTRkPpId4fXcxHtuFxhzdIFw4BQ3fjmeWX35Tc3vuNpjcGBuaDwhXxnLjeV7D/5kHW1ctne14apI1ZYsmLCLW2UOT/aO/z4/2ZFQRxm2CyuxmwBhP2r/O3bO8ERFGS6qlWJ4GJRCxY+zu2OQ/gAYAXcMb6eLW72ya2OKQYJP00ybfS+uPq0ZIH7YZFL+Wk0cPd6fCSqcB2MblpQuTm/lyN9E7cMO16EQzB0JK+sGNTwD5LoWTbRsCOQAsAHUIp4/8swdhhv8cDo1jt+/sjhx/HZ/mw0B1MXv4k5wYE/75uy5W8/tutZesfmJ0wfXy9X2uEq1aaicCqR+WZkTjEqeu/E2EHOiCCFv+sg8AAPbdFzXMz6M0JAxZB8AQkgmwovoukKNRLwGyDdWfPqCBSXIJGezFfnMBpSZUScwMWj4NgseEHryLvj4tiPKa6VxlgLbPPVk0zz48ip3tMn6H9TTanzjR8N/1XGZ0N7/TNVhVvPEj1euw8X4NS0uWGtMZ16hMtc1GSfOTD2hdiFqMGgEntNOpqvbQoxstQp9Nr6svSyi4avpDy+9Im/ar6ejK2u/aw/1RDU+JvXk0PCIbtREnmCDKiLjFxbL3Ur9ZRy2mPcPIVqcA8VDyVGioKqvXnipTEWOXYG9yjr/MvNRQ9EASqW6ceKgWINdZYsSLhQ5mYZQQ8oecUKKRhbSbhIdJsQCQfOPi35eBNL87CC42oWGLf4FipbDl0Q8ZefT4ua5YczNXdsKQcrisx8qg0TLnhjlKG3xut/kJdud8g7HkK71sJoQRvK3vQVNAozpe0c6PlALIwEKd2C+OP0VI1zOf3/fOUw+CFp+YF6iO8dG1Gvh4yqEAujNjQu/mE551f7v0sV1tqRCBSMv6n1sQ3X6Gi8PPcKH7GS4IyquZ/Ce1vEZsS+Cep3MRlwmcipvFKDnNf5nL8RVG0ATP9jmiAPl6l8R6TrfZj64KDhbFUY8q4LuCCEwCXfIXVJ4kBU4zIqYB4CIfPn9OCFnyUZ1kYkmVHr9Nz4Vj+86wQrM3/0TJ4Mf/tML+f60QezZIQmhAqQYdDvpLydJVqFpWVyNmY90FwR22A9M5VkvcdMLZ+kXdvt2QRRBXNvT+YVTGRufJOpWNeww7MzegzqTvs3rRCEb1hK7iPt+96zF9vmIwVG8dT2FNyCBHpwKjo5coZrmEixcVdhQ5jtWc7E2/e8e4EDa796YgIAMAcZ8dxbu0zaV11tMrhJerfZwhJjS09FVfAiIAJwOfH8kWICENdds0iOscXOc39c5+jowWNB2IjiYF3TZfyq4OahhT+MZ3PWj3pvfemPgxoDrDTq4pX3nWsW973FTWZGoB7AEGCaSxNyZIAzoWBBSkAnZssV+YQguTEkewAAkaaaQgV8pdOU2y0U2TSYhY43Ge/Tp4iwyA97toi7M9Yzk9Wqwjr1VV9y3GRolzdpJtnz8s4jHJ9FZ/0CWdPFPVxxBKG1aZhV2u5t4dZH0+yDK5lMnDhMUt7YxbXzabcl0/xb5MFiAr6KGjlOd/t7A+Z6tp2tc2Wd/0PwlMqkWc9b3jiV9n6H7xjtKWmbFRd//8L9kGoIMN8/JoUXFghYABbaMBczqdMhM6eToVfqAHksrsARHajbQ1yjkCDZYLjOZ7Hvr749OhN2ykuTNlO9NWczM9zh0I7fZgPq02aypM5rEa8/8qMBv62Nem3Xoic6+bKFW2R0gP3cAmNrH9uIVXbm+ObQ1kUmEHNYOtO95FK0a3Ft75yj6EmRFgjpUkOq4SvFhSp+55P3U1RSpN0yep01K2H3TEpnCHwX63baSGddM30fEqp3+7uCpKI9ngTTojMkMLkdMQcy7Md+A+tsTzB1r0H4tsULf+a4RgVjBvmDS2sTf8KwPl/W5YKa1lGTWomkSPEBKhIBEEHXr+nU8lNzRZh08MDOnfB3REr8of6EgaJF721yubmmO/PHY9Zi9KyClAKmch1EcsKlUxSB0AgD8UzEAV+G+vHtgKdDyOaFutOtVhi2q4/v0Bwk2NXnW8eGKKsETdILXJlc9CyDBvOzAZK0N5W3Wd/V5y9UBls0mBouDSZ68ddTz4KNjRgQUhc1XBKQ4U51yutgNZA28aTef2kdTx9lItFvUOyNU4mfy+XCxXhM3KVCnZiT/rEvKt7q99ym1CtrH/DRaCfkwH5tvBNifzkjuw0MVR/N1wP/cRFgKaUaaOMRp2VJodY3Ri34UjPKsrTmDS9wvscY/7fHKNsO1QVUPA7FZUBlISS5DeTkIjM08s69RYoJR9qvBXSlnn+6Yb+/hJAMntVUlROVuLYoIx9ykAQBVghZLB6wfyfpFP5PPloVvvEZI/hjFTFdpnAB/mp77dRsfujQtqVDbbwCxgIpju6KEsWmb0Suhj5ZssYSiz0DQVq4iAVScVLtC+qMp5X0kP7hJzG2EKetr4j5Vq
*/