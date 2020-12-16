//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_3_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_3_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_3.hpp
jB4F5fzpYcTCcn731YiF5XzoNYiF5dw+glhYzoXXIWbKiXaqW4HtuqpTKcUrtl808wFZb7xtuJ7Ai1Wy3iA4WW/cvUXs0fJWgstnFsusuVAHc+Yxn3tPLitR1olkCZJxrH+3G9MmpO62frNifn+i+33FAtSHEOyrJ4ep+Xp7/x74PbEAsdF5psOWN01/o6/JKfN74Pv/6D7zu+5L8m5lv/k98P3/owPm90DX1EHzu4nRCtlbbHA7xSBJ58Nhk+wHoywqcpmz8AEx+j3x+RWL07xtuDIL9qjK2nPUT8r1gN+0cV2kJes2dzo2/JU+Pb//tc+vWV23VVaJzEv//MieYKqTQYa/t/ubPpvJA/y87rPeFWBAGnjG/PZJyiH35nsovrhyZdvHH5sM8NWrBGd7KR7uG18IcdideGPmG/sorouHZQ+w0BfrA/sDvA9pIz49PYpDKD+LHzoIOOxjkEP2ibeN4uc9vLodcNjr7CJ/CHGU9+xxPmrOszdPmGuwre4+Xh/FrejoIXjG7vH6ozzny/HJID39JF+HA9iGI4AVa0v72D3IWd3SNibLExsWe2SeYHDW6tZmL5xBrIfnkAOLb1PcqAHiMx+h+E6vi9nm0n8ywPtLD/b8s/1nr0yQOBBxkoiKv2ITWzOVo95dh3OJSb8ZEFN7ASPNgGex+wAj1cS97wGCETvpa9OIYfU9X4m3AU6r/247Bg8Btpua4P7lG3cQHqQDnY/xdu9EnKoH3g3/6FXA2U3V8K7v+hcC/w5C8SRqE9ZtCC8spPPaJkri/ti92ydyKUsUrxu4r7Ob0GYhiivhC++xc+hfv0D9h3CZqipSQ9GF0yc8IXwLSmXKOG3SuIqHMjKa82Xcm9mNwD9VXWdVVvOhUCYacS6qSPWwjMd92Ya1Elx4iNo2SwLxP4yQ870wv0HbpFZF2so8IfnJTwuOwnus7EJQ1ryukybOTFk/Kc/LoDUnUHYjyJfXnKdxU5jCNlI72z5Paor1fHiDtGuSy0TlshmKxrXyhPCb7MucafI0TVRZDkXQdA/PRB/3+TWLi6aFc9ShQBsXIlmwdcLvsi8zn0quFUyaGkXNfZbPXPwsn9+ypkiTtM7EUOC8+MQF0SQi8Cf4HK17w8s2iUQRqDDVw7/SuqRRk3IpBOPyvNbh+xbERVcXtMXZCPxexXkSJxEInROJtj25j3RsZPM6dIXoYF5HSmtwavqmbSsRNaHM3b4MuBTjVZy5sYVCxB8ZlSnKqMlrJYcyKZX5uL3LvkLv63MRR6LKItOpyYJYWBzWarHhInU6a9vkIpFPWNIqPTIrTjvMdTX6pqRtUmp91cokrdgCSqD9xENBXkrEomySdrSsNK9Hg7xkJvKsNDqltUNk4lyY1+NXgr6uMimjwtRL6AW5ngQWBA9tNZ4K5Koiz7gsc9PZkpQQ5nm7dvw8yI00mllB4hrzms9b8Cn47ZrSa8h3TgLH4L4dN2JYGLM6wLuDcRxIhtoihRxzLI33GI6DM9DIPcbeUQ65x5gKcMwG7/aQY5Sc1vnfiGPHBXX+4b5xHFrnI/vHcWi8mIeQk2Jh8Hv+MuLBh4TawD52YFceJOd4d0/vxoOCIe+7Izy/P7COswdDnusTtM/dhRPeLx29DXj0yx72/9MBJ+z/e28n+Nj+f9xwcDRTG+vqUIhDDih/YxSHHPAO7A7A3Wdx5Jzh1wHu+y6ev5NgkDDqvsHc13NYLLTrfRXi4UTs98cPQh5tamzLwwEPmxttTEIONjnaK77acsIFItXhZ3flUR2uXrMbj9ptPzWGh/qEtsshx9enP4zBQ73lRywnnIsxn6dGOQSfeZ3DcZ72Y0I6HFfKYV3y11NOODY=
*/