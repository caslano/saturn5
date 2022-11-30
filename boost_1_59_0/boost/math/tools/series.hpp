//  (C) Copyright John Maddock 2005-2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_SERIES_INCLUDED
#define BOOST_MATH_TOOLS_SERIES_INCLUDED

#ifdef _MSC_VER
#pragma once
#endif

#include <cmath>
#include <cstdint>
#include <limits>
#include <boost/math/tools/config.hpp>

namespace boost{ namespace math{ namespace tools{

//
// Simple series summation come first:
//
template <class Functor, class U, class V>
inline typename Functor::result_type sum_series(Functor& func, const U& factor, std::uintmax_t& max_terms, const V& init_value) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   std::uintmax_t counter = max_terms;

   result_type result = init_value;
   result_type next_term;
   do{
      next_term = func();
      result += next_term;
   }
   while((abs(factor * result) < abs(next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, const U& factor, std::uintmax_t& max_terms) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   typename Functor::result_type init_value = 0;
   return sum_series(func, factor, max_terms, init_value);
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, int bits, std::uintmax_t& max_terms, const U& init_value) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   result_type factor = ldexp(result_type(1), 1 - bits);
   return sum_series(func, factor, max_terms, init_value);
}

template <class Functor>
inline typename Functor::result_type sum_series(Functor& func, int bits) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   std::uintmax_t iters = (std::numeric_limits<std::uintmax_t>::max)();
   result_type init_val = 0;
   return sum_series(func, bits, iters, init_val);
}

template <class Functor>
inline typename Functor::result_type sum_series(Functor& func, int bits, std::uintmax_t& max_terms) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   typedef typename Functor::result_type result_type;
   result_type init_val = 0;
   return sum_series(func, bits, max_terms, init_val);
}

template <class Functor, class U>
inline typename Functor::result_type sum_series(Functor& func, int bits, const U& init_value) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING
   std::uintmax_t iters = (std::numeric_limits<std::uintmax_t>::max)();
   return sum_series(func, bits, iters, init_value);
}
//
// Checked summation:
//
template <class Functor, class U, class V>
inline typename Functor::result_type checked_sum_series(Functor& func, const U& factor, std::uintmax_t& max_terms, const V& init_value, V& norm) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   std::uintmax_t counter = max_terms;

   result_type result = init_value;
   result_type next_term;
   do {
      next_term = func();
      result += next_term;
      norm += fabs(next_term);
   } while ((abs(factor * result) < abs(next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}


//
// Algorithm kahan_sum_series invokes Functor func until the N'th
// term is too small to have any effect on the total, the terms
// are added using the Kahan summation method.
//
// CAUTION: Optimizing compilers combined with extended-precision
// machine registers conspire to render this algorithm partly broken:
// double rounding of intermediate terms (first to a long double machine
// register, and then to a double result) cause the rounding error computed
// by the algorithm to be off by up to 1ulp.  However this occurs rarely, and
// in any case the result is still much better than a naive summation.
//
template <class Functor>
inline typename Functor::result_type kahan_sum_series(Functor& func, int bits) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   result_type factor = pow(result_type(2), bits);
   result_type result = func();
   result_type next_term, y, t;
   result_type carry = 0;
   do{
      next_term = func();
      y = next_term - carry;
      t = result + y;
      carry = t - result;
      carry -= y;
      result = t;
   }
   while(fabs(result) < fabs(factor * next_term));
   return result;
}

template <class Functor>
inline typename Functor::result_type kahan_sum_series(Functor& func, int bits, std::uintmax_t& max_terms) noexcept(BOOST_MATH_IS_FLOAT(typename Functor::result_type) && noexcept(std::declval<Functor>()()))
{
   BOOST_MATH_STD_USING

   typedef typename Functor::result_type result_type;

   std::uintmax_t counter = max_terms;

   result_type factor = ldexp(result_type(1), bits);
   result_type result = func();
   result_type next_term, y, t;
   result_type carry = 0;
   do{
      next_term = func();
      y = next_term - carry;
      t = result + y;
      carry = t - result;
      carry -= y;
      result = t;
   }
   while((fabs(result) < fabs(factor * next_term)) && --counter);

   // set max_terms to the actual number of terms of the series evaluated:
   max_terms = max_terms - counter;

   return result;
}

} // namespace tools
} // namespace math
} // namespace boost

#endif // BOOST_MATH_TOOLS_SERIES_INCLUDED


/* series.hpp
jbOpYRshP1qyJffpYm6ApmdKBvqi4grGoBbL0O7jzNPSWYGbdpTiw7HZrAoWlVjqHyij19LRbBLjdCthwGZTAgrGfgXYkMS0M2QH5e7Gq+NXy3Y2H1SkTC48P0twcafVQIpUQHWe/mhR13qx8611Y0SzLruPrcOhu+04WUXUPG7P2ViYrtFEeO6v9FSVvskdknamKIC8aQtUwDpKSN1NJ1EkAXGnb0xCZRXIoTM6lFK2xpVXWs5TrZbIm56wgbjQ07gDTbdwsJdSMKlgf7YeLiPQs0B1gY3GxnYGVZKP1CCw0TMP2vOnG7x3Zh/H3v7+/f0N4AEECPwT9Cf4T8if0D9hf8L/RPyJ/BP1J/pPzJ/YP3F/4v8k/En8k/Qn+U/Kn9Q/aX/S/2T8yfyT9Sf7T86f3D95f/L/FPwp/FP0p/hPyZ/SP2V/yv9U/Kn8U/Wn+k/Nn9o/dX/q/zT8afzT9Kf5T8uf1j9tf9r/dPzp/NP1p/tPz5/eP31/+v8M/Bn8M/Rn+M/In9E/Y3/G/0z8mfwz9Wf6z8yf2T9zf+b/LPxZ/LP0Z/nPyp/VP2t/1v9s/Nn8s/Vn+8/On90/e3/2/xz8Ofxz9Of4z8mf0z9nf87/XPy5/HP15/rPzZ/bP3d/7v88/Hn88/Tn+c/Ln9c/b3/e/3z8+fzz9ef7z88fAN6/+y/7WK7NeWnjl1ZVxHIOmLCORnDEnHZZlws4CFOlgs+3Qm95zaYeEV363ZGtRouwspBFlhfRmLqu93l7Gs/fPecd0byg2chDrrEgbylliPrlHm91jSee0zjN1PUKnqlrK0GVKToPT4gx5QafblXWgr580j1JPJDdvHuDJI9xN/bBIhQjE/ecAnPDckGyeW0LysQzEunO9rqU/uO24MRzUJGXVvypoVs3GXDtsdm9h4wLx47z0jRebgGox9B9XAFu0dpkf6LX37B4SNXX7Fmt4lUEJn8eQ2sgxYLCgJfrx3ikslBORN/jVmfUcLbPW3etudiV8YTK69c4Srh0NS6AxVZZORc1R03sphkugRvS3oeDto6g5jGEa0Jn8uTfHkmixmZRUTv1+c21h1rL4vWfUOI9SXvuq+iooTaCPcAwwuaB53lyGhXLm8VRni7KjQUv66ySRa2ANU7Ke+OWIbKHfMdIIwMnWSubgeL5sMtGWdITfAUo6ZEYq04rnAj0iKa0r2M9mSurdsTHor2fLyOOukdsD6+X8KgeSDJGEP17ImFcnRf6nAZO0poHwz4rcDuwJEwHWvJuteM+dlLAYNoEHGe8FmlUY6bX2kizQ03l8GM67qj/CkhVvW5qpNCZV7CihqjOzMLmk4Wp+rf2zmYOKrjEOrOFZ086dcffuDFQly35341G1kbiwb+a6mf76ZeiKhZfZ2q4wgF4piGCuBWWfFIAtwU2lQQ4eOxWWXJDq5e0bWH7Os2Uw5lPVVQyBO+2WlzBz6uYG7nMtXtKZLVXh2CN61DMuQov+xngZFkXI4/Yy03AwIpHsHj8kl/ONYFpdOwI9x2PVWjniFb2HVB7h85HY7M+ZydopbJ11fkdxYBtnkvj+mmEbUeWSbuzNMoKAwOBZOc+c/bM2wYTUTzX9A/reu/yxMHua4XUPse7xwg6gKDaITS4RSFStkh7AMomnzvabpg/UrWC2SUoEQWtjFlUDb1mRrhwY9zZ2rK2RPw+Hx7sH832WU6iIR5Fbap7iHT4ZVgnKdSHjmMbLgfFX8040rbvfXXlaRElLRxc+mnpT5y5vud1fWBJiTApt9zIpjxr8PFqFZHLNu02GRqBd/EzOgt2du2sWxcfwzyCT+YlBscOxLDapwzl4ql+DgvJn1yQFxD81e2GlFSoqSiuBbHSEbRqzkdsrGQbYOtKtnSBJfpyBMqnLGtMOibh2qkL6ovGtr49ddxzIy2OG5lEXrJXCZCT21JNCNN3XmkcpMmKKS0aOZWRPBpnWDLU2BznMTBqsM4XnXQJ5xwarTRYKHQxDQouyjLPlBWQGJnMyiX8F+wibDpV9hbEn+1MLuF0eS++3ZfzKQS5zCjR4RApPXy1kP7DFt5XqgYpZyivMxhWs2Q7i4B/psnHxAUKTKuWdl2unS61xrXorkd33UWfcNd9qA7Pr5XAZe1/5GNu78CjYKDUo/MADR+0rtpzMDI8Q8o9uGenpF6ypKcsKpskabmddGgfF5kqfb+o0rBfyM5KGHcAVyBsE9d/Wb7B+KTwWmTxwTYPX/o3+pPUjWIUrJaZyVZVlqgewCuFCVHoIX3yc/sJZb0T0MJsrVUlQ+zSb16spKMEggMC5+rrjvXbK99YVxJbd3SF6v20W6XEy8JxvuJJBqW1xKMn5d+fRhJsTHRCiya5C9anfsJa3KV43lYTe+UhL7E3lkuJnXgpdY7lR4EKlZtZUyhC9mjp0dTn8cFGwQr7k/dq3qZ3nJmhWsomzlbcQmkyk6LgHquEp3ATEjLrcP4p4EbN2taeiIxeDXmJWA927uyE8evgigzg9hXpkiHeYkcMhSdrJZZ58ReaFt2qEIA+j/jMMn3tiuSdXFkUC93B8c3Kpk373QoLncEnP4pefemRhN8gPjfLNk7Wf0ZNSDmaIoNIKE4CogZLMx0deLotSQFw4xca9oe5ylrNa3czNfgcoTZEO/wWlc54QbnjbzTkos9JGRlz+ZRvbWmoTuqE4scpbwe+PqEl5fpJy3sUSysZ9505VIiDSf9Nh2OdW1ULSe55cFl7WGi0Kz9zEvQvYbAkmmNjegRQZEIhWyhc9BRweIKBLg9OvIRcz0/Qati2VX/di5lhz7RoaWm6DW7QKLFDbjc5EfTbufIOo258mtG+31eHDtQMhRfWCs2yBnoAi5ongDgl+PhcBvCZ7Fiw5oKZuqIei6cuoEDOSUdS7Kbe8rVL5Y6A64lZP4MhsbccjYSJm6xcZ/UlBpfn8RlmvAl0GSzZ+BT8ZsFRUIx1JL+22fRCLUG9+Sj7HpENqYn4SsJC+YtQA3OqmFFYUWYsaEj/9M3+iFoi36hEdczYdBYTF5zBiqby5txnDuk5EIoRsInezdUBlelI2vN+2u5zCDqOR393huj3F3iY1BOCUqtdv+7/YDh5vNPoY7U9Xg+0lfxTWNBQKZS9Kv+c55q+NDeXx1wR6+A0ZtbKnwpBexhhPhRs1koydgy2LH8LSD4PI33+ddVPZpuXhYZy9VKdxsFpJStF7Uzds0b8cYJ8Nu6F/+CgHBpuoLN2xEu4US+ShL00rGGPqj6JgyyqpSQUCzAtvZlo9BaRmvY00AeDtLVtQIwNiJv23AhOHdhNEjOQifUh1jt/zNS0hd/sxIeKjd/MhYH78qpvqGg5vD+gvl7p7Cho0L1bdTJEaMVzfgSnN1gxV5BaZhE4bw0jsQKWfrVq1US6N8UcN/a4GwfM96TSk9xmzAeUgyfrZRAQxbNozhbAm3M/hykdzpYBJRpjrMchLJTqdH5+qkP111Z474lnz7RRPRq4p/H+Wop0ZiN+9NSBxDcKR2ajjwmzWshN1b/cVfdDLENcWhy4gdx717j9KJfuqtpqtKpAlxme5kTW7c0TbwMS7Y5jxPl6wUsZANRcWgCgwtYFkp0cHwkqhUbiievkML6thCapd13bxomuePpiW310ZibYXUApi4LIC6WNp6FTKjnvqXz9rxsByRwLqvhO5NEcc1rANpNDAhLruzLxP0WDdNSis53YJn9jxinZV4vK8eOdQ4F3o8Re/zHk+0uQE/JrsuEhP6wdIp8PkPnfYaknhyZFTSyCVorN447RpBinE2Zy45GqWND9w6JIaQkyIt2m8A7YYqJrNg/B/hthvRyJQo0RYbfBpK9UJ0Rtn9FAQ2nph6Xu4QiUNEVJbYyyaO1YVf7qYzKKBlLN4+3KQMeILfeC7hUJaTHKxCeOBldbPY/oNRoMoj2aS1rJbbGalAsBcbIYrggoAs/edItga9l9yHberfDBMoNDqb634l7L+DLyTia6abe6y3Wg8Ud0GfyQ4KG8lAbltqlNvrhIzYTq7bZ0u5opwcFWxsq9x52KNJqKo9d6FcV2mn0Wcin0IRCD6P/Q7/I1hziBdGw96sx2k8LV3bGj6nTr13rDknzzb/jJB8+NhUUeGZSmOBnOSpHrJTP+y2ArxTCq6mm56yoT512yoVwWnsDvmtmlZiXFHlIyoCy+sVP8OINfJfw0KIEbmIXHZ0MP5iFzTwQD87RPgrcoQIbHzO/MpgJXs8+o75CfrRUdppeqc0d/t/WDDJ2UJt/tULFRKS8XGFgxJoDCquayELXrh1xqH+saqOKYnjgVI3YgVmikutzkcRPw7LdqmDCE0viOcYRE8RZKbeIpO7HQUQvhHo+ZFbUSu9kso76QME5xfQxVJnMNel4Zaa3Sat4snYZgEyPJbMfwgjvWRxgadMd95xo2CzbaEU96HK1719WpEgfHEohvHSSyfeTeatAk+koEbDTJsmGOsyJ15IU18nfAbb9Rcca5xYHNxWSqU9aTRcAfIwfAiAtgCHiyYLKhetF+LUq4g4m3yLKop3T9PdgX21uDzPo4w5KSkFjzLiJbuYIIlzV16hXc0m64e/TEv1M/isaEEzR5NcWv0cPAArOlm4/zGq6AYgamNFxEplyT/8TwIZkAJ06mejENghBWMS8SVFH3nnhxD4eGrdoCbWqL9CIS0oM9jsfuJL2TZvmu/F4LgSuXxNfoNsNY2NNUFYWT74E3q0BuO4Csnu7qlyqUUugdyP2PV8V9wscAi+XInzLHSOrpX/tJVXeFAjSXoHyW/H51yOiJSgeSeCQSr36+C5w3b7LdJWMzN0b7VP7pMt5pP+ruUi3ieIGDO5sCQWIXiiMugNbU72+GV0Znra0Az0pEMuoYd9TooF/RnjFFumhuVLOYQh35kUBJ5bBN5ik/p1x1r+FtKifjQBtQR3+3jihrv1Lf+B1mm/H5yelblHHRG/aVTGpfYrTLOmxex9iaFQhkxGF6If8+oS+Xy3B/hG+6waN4ByvdNlc+4fWDOW/75jQQqEOJurFmOOoEEGyzLToWpRTuGeOFd49+ry0YwfH1pplDOqSvY6NK6EGVfknw0mGZZOhJKrLQf5hAn89nQpP2thWu9wffj55LqRjVZ3CKWPNCWC87PR/0sVMMU8eRYtS9GvqaVdhD7d6LjIV52q8boQfTmTc/DB4lftak7UjPlr0cMjlA7D/ZVnzOQ/Zm8bjJYfAPxRJriAdGh9Niiq69+5B6PElzqIlL3+McYPHUq/yh+DmlDPc/49YEYCdBY2qV6EYHJDC1ZmJvRvQM6+zE+vNbP43vlxSlDR8toWwbG1VKI6/MAm1cOnhInCKYmQQCeRm80WPUaw5E//GYVAt8t/fV7miWKEsa9DOmtlpnOSJagPus2SdBbP3gHxyAX1LxrA0mE+48C4nAy9BLbyA6DqM6dThbe0fi1le4AAs2+opbZVp+3sMQjsJVTDsWfPPycSQbiCOWODX7LVSm5m2tsQFoeMcbXVVmhrP6pq5l/vh8J6nj8eonxw0EaoVefSG5BK1Ern6ekZsvF+LVgOyHbHrcCPzNfu/1CQ+lrrojX4H9usVK7hR0ZggpcKV2EUKt+P7CXhlNypfIMyoubBSTz9ltJmyXhKGFFr1WSd/7PW5kY7SbnsL+nHCa0C9skZgm9UMR1uytJ/QZhnxEWTQNZJyFy/TB9G98R+Dr4dhX6czK7K8LQewDH63yBne+a77mcj8/zvZL9KQ4RN1v/R0YUxNDpT6L3MLkBaFTdwiYVdksovt1Die95PzQ+YGkJUYhOeT3rWUZ/39hGW1QSoMS/kzXn98MerGBsFQgKugrvwnM6bRnMOQr1hyhCpCQh8sYAHC5sarchhs9m6WYROIyZCJfRFlop5P4ZfqDKC2aUVZOU8Po0aBUpjy/tcpHA5LruxiurZU/qJZn5SQ1Rp4/vxivu7CJMv2irh8alfTk2l+7AwBM4/410OV9YC1TavgBHzhdvYUAiDdQ/FCNv3LwJSn4Dxk3vYwhKDcHjRPUjouO3fsOCmC4U23d5yyoSfKq1NZsTcMx+SNGkmwMY+etagVYv1C9CI5WdTvXzJDGglvrQ7XfkH7zLsNNVCGypv6Iw2TdKor4MRFPdiQCWA+9JZgXC3RNRWbENBnzZq+TMmT7NAAU/fGwtOaNKpYh4TjN5iJRxyc2++TYLOy21YzuVSvznxQozu49diljkzi0qSL47tdJpFl6DY5i/ZlNxBWOlTSOSVbxFvKLyzUjmPX5qDTwzL4JmJlFKvL7PIrWxTkbWu/gI4ym2zb+IuOToZrXwwf3qtciXYKuKQvYojspOzPM1Prkt9PEqHq/1ILWo77BMe8yMkXxPfJpUOZnGQRvRfGgrZyOUQSpPbfuFtxO3cUbAoU3h5tydA5X2VyZlmKEr0cB+wEVmsiyiCDIfYB7ZspBFozOlTw/Gdg1RzGq4SetyU/N56ivX2LuAOgsCP/4XOGBkI2hkPuWSVn1sz0ybW8gq532IFmQGg/zNPKyvvEov5CRRlJpT8Xh3+QiME5mbAYEZswg6TyoAj4Tk7ZIm+tUrVqiihv6mBn1ITVsanRR/vFY/+emLgtHVD4wyBfUMI88ny7ZzS0zwC1SMgw9rXH+bGAYb1kwX1EtwvQAwvhcTPOvArvjyYjmP1i8BrQf7LwAbm8hItNaxFO6hRCrgFYLCrso6FdLSdogYXSLH/DfPDJMiwQxV9380AHCFWYtF4kKbSTWxGhxR/QVpcV8EYbnhkDzx0s3nMROROnutSDQuseJ2pgNNff1t6SgeuW7/vhUVhXstha9pkOT3QkVh+6i+Bhfs7UXcg1pd/iyE0hAKBc0JgU7/SawVOgbgpyoOVf6ayB96iZWicEJGXIyj54qJUpwANrzhQQbtHaJyunoo3f/8huF9peFHMA6NHQZ2ZQGkurrblsbzapiZ1U0XUWGk0DN8WpJbs3Va6N/+V+1nRpb5X+tWCZfOcYNi7LhzvJ9izmtAjKc/AMuKTHuBrFazV3Zwdwdw9pSgky6Gtl9moGYbmXZSW1/N6NmjBkzrBNJZV0lQ/FtKZxHVKNcWYGJoxfQCETFpiTqSD5JE6jdJU4bGxNPElLQsSPXoPpNxeSGRHvcorQYXxbJQBGZkLQIY5lup/3rv/WceCLW97cxeTqTMQCZupkpWFmvoI0+USN9dvLutmKVw/F542cKd9+PyAJUlbRPxC2q/mN424dQyZsuzZYq9ZLrwh/Ee0lp4IWtUVysPjM9PH4fpGHdJ2t8aHtYUe8m0+SC7v0l8kPw+f/ecrGSbG047NYJUyMkn/D3rBg9GjhCFlUj+fCnW3Uefng2Y7FZRoNiMsBf2it2Rfn2mnEGli/ywPl4N9EA813XUCu0Iisz4eN22C57BdrD/z0gfcX/9gA+AJShtMp5eeR7QPDJ/SLsyM1jD+xfv2+c9YAD0N9gRQiu0hFsvwkE4xa4xC/c8HnPTZtU0b38urIA1Km4dv8WBAJiYFcVwRjC6fIxv1Ri1Uda5OPrpYrTNFnv2yQ90yApwfSFNSb8x2yaU+BGnJIraQpWwUDi5E2cZdfvcxm7fL9J7627sDNPxJ55fr81ZOHQ2vtZsLSLf4NWfSP17N3hADCARxTGFCxoXgxx
*/