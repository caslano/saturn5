// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_ROUND_FWD_HPP
#define BOOST_MATH_SPECIAL_ROUND_FWD_HPP

#include <boost/config.hpp>
#include <boost/math/tools/promotion.hpp>

#ifdef _MSC_VER
#pragma once
#endif

namespace boost
{
   namespace math
   { 

   template <class T, class Policy>
   typename tools::promote_args<T>::type trunc(const T& v, const Policy& pol);
   template <class T>
   typename tools::promote_args<T>::type trunc(const T& v);
   template <class T, class Policy>
   int itrunc(const T& v, const Policy& pol);
   template <class T>
   int itrunc(const T& v);
   template <class T, class Policy>
   long ltrunc(const T& v, const Policy& pol);
   template <class T>
   long ltrunc(const T& v);
#ifdef BOOST_HAS_LONG_LONG
   template <class T, class Policy>
   boost::long_long_type lltrunc(const T& v, const Policy& pol);
   template <class T>
   boost::long_long_type lltrunc(const T& v);
#endif
   template <class T, class Policy>
   typename tools::promote_args<T>::type round(const T& v, const Policy& pol);
   template <class T>
   typename tools::promote_args<T>::type round(const T& v);
   template <class T, class Policy>
   int iround(const T& v, const Policy& pol);
   template <class T>
   int iround(const T& v);
   template <class T, class Policy>
   long lround(const T& v, const Policy& pol);
   template <class T>
   long lround(const T& v);
#ifdef BOOST_HAS_LONG_LONG
   template <class T, class Policy>
   boost::long_long_type llround(const T& v, const Policy& pol);
   template <class T>
   boost::long_long_type llround(const T& v);
#endif
   template <class T, class Policy>
   T modf(const T& v, T* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, T* ipart);
   template <class T, class Policy>
   T modf(const T& v, int* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, int* ipart);
   template <class T, class Policy>
   T modf(const T& v, long* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, long* ipart);
#ifdef BOOST_HAS_LONG_LONG
   template <class T, class Policy>
   T modf(const T& v, boost::long_long_type* ipart, const Policy& pol);
   template <class T>
   T modf(const T& v, boost::long_long_type* ipart);
#endif

   }
}

#undef BOOST_MATH_STD_USING
#define BOOST_MATH_STD_USING BOOST_MATH_STD_USING_CORE\
   using boost::math::round;\
   using boost::math::iround;\
   using boost::math::lround;\
   using boost::math::trunc;\
   using boost::math::itrunc;\
   using boost::math::ltrunc;\
   using boost::math::modf;


#endif // BOOST_MATH_SPECIAL_ROUND_FWD_HPP


/* round_fwd.hpp
pv1jJsbO+TV3HDHD4rqMAf0B3hS2nDBx9pvCPxCjDAPzTQHvVxZOl+kxi94u07iFs94U/mFjrHib904ixlpWbB+hqddYWEv+kddaGJZN7S8bp8lHMVyP6zquoEpTN3z4nD8Uh+1tamzMqoCplhWpjENtOq0sUqwUledEAId10OC7A80hw/k+cUuV+WRVelnXDTOoA+dZWx0/1nj8KC48UF1wHOhRvH+QflXiOf99HcVZEThBOEEBWQj7GxV7IqlCLyyiyhEzpwG7Qo/wLVjLviHtBZZkduaBIxWMXaQ9IWmStCiSJCFA5h37PaxDYno055G/4/9HJzZec+HvuarvITyjSv9BUayyNv9s/RCcFI1xUyMGDjI6t5V3e5ON4/J4vX5qi47jshjzg20mxpbL2TEMA8mdlLX/qafpOLOuK7tb6EYOlt88Xcegqybb/+7R6Wabj+w16VQJ5yx+FmLQf5P3DK5nx7N1DGZo5vje+5ne8Ju6iUvPUTFQBg83qmfxgInpX1LleNdBnW62N38e01FGKxbwmUMCw5UbbeY18fk2Dsuk/fDaCwRm4J2JbsVE23JY0pbF7/jdiPbnFxMN28C02y8TtHcLj8KFWekbqeTJPipokkEVm+jBK5jO4jJ//5VAX2PfPPQqoD/Avrlv1MJZ+8/Io4gZnguY/Z+OAVb4fGPqE1wbiT5yXKNj57A89RjSkaLkVuH3vRH9PbAs/Nz3k0EONF9Lm9ah90/NhiboBnntuaUzy2h+g/iZXn7gJy7YoOWD8icxh5lR/mWtfGnukiWV01PQb2iw96IRVRZ4awyzMqQsZBJM+8IRdV+IM3jZiP3ckZF5TBu/jz6q21EEcR7F8LBQyYjvIDpm0jJl/4LK91g3qbIo6+bO8tn39IDDeItVseNRUoJNgxuBOYloKdlwcluf0PpFWNDWVZTip3L1tv5YxZ5I4zzOq1DmwgOk8V57B7Foj5SE4N8TUso4u+zfaG2MojgA89900I+IJR3EPcRyfDx4nwajGbMjuRbWQfxLb0MeJmkZhqIvCfturAcGtF5PUGdhUsOoCRbevdCfWRxUJLMgk21s8633abyeIwKsJUlVOHMDXuI07OOOHjPi9Kd+F75gMniwmphfuTiHBr26rbFzTBtb3dov66pbwfvrksnE+TYMGbPS9RMvLAfG0OHS7MIK6EIu0AQk21hDxiIp/bxKu8IY2uZi3dFloz+7ZZ24aQ4zYaY/o1do9ednDVlzL8uyBBo4B7wWJ/fLN47p751VWnl+nA+a6L4bVkdmanieOKb7AlZlnFVhJZpHHObcvmPIF+ZlFyZTrNsLT1o5Av+g8hUOHHSrqugmoi7ByQyKfeZ9lWe88kX+XLccpC1UGBwa8yr+sST2fD+AOT47kWvy4Pqv9ZfvllB4GjjYxfAiLuyJDJv14/obaxgFuUhtMo88xKHm4tTriTLPrf2w6wTzw+sZ0+vJEzjhRz4MgXm7nhJ5ApUHsFlWg6Fj8D/41u545DVw9vp0Ic/2PXktn5ausIM0goh5LWA6pcBwjH1G0fkJRjbsydJ/RF6+2YxYzQu7Hv7d7n+BdjlIt88GXM8IYKQe166n0R1cHVVjQQbdInXTGO5NM4av5xdG9flbZ7Xf9QPHyoloxLX9jlZ+mrsuKA1cp1lwq7K5843q3wrKrqsyKx/2W724eZuW5VnS4Ru0Hr/9eTauJV9BK87IV9CKMfIVAEa+qVk4NV8BYOAwa2PUfAUS87iNoTH0m42AWWMMXdlk0S2bicXNAvN4m7z8jd/WUXWReVLnwovkwoKRF/2WhstTN4zKMhTxc/XzwFMv1848fuKHeQrX7QnhijKAcl52FTs=
*/