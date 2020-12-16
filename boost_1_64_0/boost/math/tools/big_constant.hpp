
//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_TOOLS_BIG_CONSTANT_HPP
#define BOOST_MATH_TOOLS_BIG_CONSTANT_HPP

#include <boost/math/tools/config.hpp>
#ifndef BOOST_MATH_NO_LEXICAL_CAST
#include <boost/lexical_cast.hpp>
#endif
#include <boost/type_traits/is_constructible.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost{ namespace math{ 

namespace tools{

template <class T>
struct numeric_traits : public std::numeric_limits< T > {};

#ifdef BOOST_MATH_USE_FLOAT128
typedef __float128 largest_float;
#define BOOST_MATH_LARGEST_FLOAT_C(x) x##Q
template <>
struct numeric_traits<__float128>
{
   static const int digits = 113;
   static const int digits10 = 33;
   static const int max_exponent = 16384;
   static const bool is_specialized = true;
};
#else
typedef long double largest_float;
#define BOOST_MATH_LARGEST_FLOAT_C(x) x##L
#endif

template <class T>
inline BOOST_CONSTEXPR_OR_CONST T make_big_value(largest_float v, const char*, boost::true_type const&, boost::false_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(v);
}
template <class T>
inline BOOST_CONSTEXPR_OR_CONST T make_big_value(largest_float v, const char*, boost::true_type const&, boost::true_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return static_cast<T>(v);
}
#ifndef BOOST_MATH_NO_LEXICAL_CAST
template <class T>
inline T make_big_value(largest_float, const char* s, boost::false_type const&, boost::false_type const&)
{
   return boost::lexical_cast<T>(s);
}
#endif
template <class T>
inline BOOST_MATH_CONSTEXPR T make_big_value(largest_float, const char* s, boost::false_type const&, boost::true_type const&) BOOST_MATH_NOEXCEPT(T)
{
   return T(s);
}

//
// For constants which might fit in a long double (if it's big enough):
//
#define BOOST_MATH_BIG_CONSTANT(T, D, x)\
   boost::math::tools::make_big_value<T>(\
      BOOST_MATH_LARGEST_FLOAT_C(x), \
      BOOST_STRINGIZE(x), \
      boost::integral_constant<bool, (boost::is_convertible<boost::math::tools::largest_float, T>::value) && \
      ((D <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits) \
          || boost::is_floating_point<T>::value \
          || (boost::math::tools::numeric_traits<T>::is_specialized && \
          (boost::math::tools::numeric_traits<T>::digits10 <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits10))) >(), \
      boost::is_constructible<T, const char*>())
//
// For constants too huge for any conceivable long double (and which generate compiler errors if we try and declare them as such):
//
#define BOOST_MATH_HUGE_CONSTANT(T, D, x)\
   boost::math::tools::make_big_value<T>(0.0L, BOOST_STRINGIZE(x), \
   boost::integral_constant<bool, boost::is_floating_point<T>::value || (boost::math::tools::numeric_traits<T>::is_specialized && boost::math::tools::numeric_traits<T>::max_exponent <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::max_exponent && boost::math::tools::numeric_traits<T>::digits <= boost::math::tools::numeric_traits<boost::math::tools::largest_float>::digits)>(), \
   boost::is_constructible<T, const char*>())

}}} // namespaces

#endif


/* big_constant.hpp
KwhCN/BvOY6w+u4W0VuS2K+ir1P59rBrvY5ZUOKM/0yjST0xilG+Ael4AQHMknd4o06bnULbFalnaNMnl+ZntPf+zRIjHgD0EihvM9sNHL6vgxy0s5f0Vn3zvdIHG+GgKORjfaf8zldARXsSbMdQg1KLRbpbx9PtO+V5do/EtOqi77u3pNvxNlVdUQ3XbquR7yVMm63G3zV6u63GW+4jMaYuNvmH3icxVv3gs7HEzt53MBY7i0z75n7CUvm4RMJ8+X5tGCGJ3nUPtGFk1yP7l/tLnFJOjIUkdRAtDCWo2jtYOC1RzbZq4gEcq3TyyfOSxh4ItAH+PX8mabaPzjsfJGnSX2bZ7DP/os83Ue7WZZzm/898Ew/pDwj4eijr4/I6GzPI7+RbNtjYQX4nf7pxTWxPffMe3kJY+6VEiau7bQCOYoxTjIFBWNQBlrpt2wlnP7IothL3GICjtMnX+k7Eag9mSlxp+LXptt4D29OGs9+SP763DSermfrDPsKp1jvaHmE/YagNZJqyjPP313EoiOb4gzadiki4LYdsHBWR8n74QS047MzSHyzHSJvSiafVfZMLSb/0YJMulGtIt+mwSccBqugSnX0IYvSuYPnXZA9txVkx/W6241r9Zs48rBWr2bPuOdKOQTUmiRt+eBtOFljOSXf+aVjzL+mXnpvmTnGrc1JzB/FxVV7FKjfLvMLX3BHAZvuEdXdx5I/Dmg2/k9Zu6TJw+CT+8aGTanynkW8M+eS7qh87VVky8BMVjnWfgj5RwHcH/zA/I/6dHL0o/o//piRzXSPzrCYzZ2FSFmnhtwg9g4dNIRVT0GVKnxhYL9Kvh++UblY5WEL6Zxz9kvX3A5CIkOSVzTn7T8Z7VpiGYQEF75ewKzKxShnqtpeVyXeumSH13J64uZ95ccb6EsrOc2B//YKOYKY7D3GoVPJxsnADNw+KmPEUvPDY8a5IG33FSf2R1yhpnair0Kmqql+rR4+LbE43+Tss3/8xHXknHGdpltd2vaHvjMcqYtymjIaM3IHJxw9LS8ZT+PUluIqjeiJ/0JqMlFVBnkZOgSLsf0p+Yda39OUdRdZ708fOafIyFsCwi8sigxpcU6QwMIb/I5nUxy5iv5X3z3Wexnnh230MdVOossSYKpv7DVWO57EiDpOkDOOBckZrvFTK+P1Qsnhh6dRjGfkE+ag5nsKyCoLEY9hXNG5HXrvIIjb5uq7JqRk8SVRFnGeNnDPKlRc/Hur5or4vfetpbRCxoPQSLy4iHOfYo2CQz4HHDSiXT1nqNDLeosmIWZ5nbu1nKcqQNWQLobvmDxv908/j2nWLHJVrFNdmUj/hsWUzr2i8BcvDNIIJfI224l5E8A2EOhF7RKNLNqGM0RGYW7I8SkMco2f76NPN2yimLf1XArwI06qlD9d062jmQJ9Xrk2rc0QepF5d5IU6R8g6qKXPxr/oYyn2+aNTkDJZdunjp617Tck7ME1OyOIkyKswdUTq8Jd1J/ruM6E5u50uX48kBTP1WOm/y5AVholbpFlJsrhTJV3eCPVRp8nTsiYnYqXvBVUWkZjT3C/nf5eny4asOoyr3C08PU9SoMyUqcv03r/oukR1VedZTFIcbjrZrLldyX+i6e8fVfkLBvN5VsCgIQH9aWRG6Z+O7B8q74my8uI6zvol6KqdFKCjB5W7o2Soryu6enFS2mvS3YmkL013l+dmECL1RTdLuuSVdzJbdBoPnHRQnimIRgocxDu2S6cDUe6H33hPSSOb7ZlV1AVHfeh72RjModxTHtjLMWv7arnWgjFtd6//YVjzfVXkXp4XxS3bWDd9aMcf9b4Y5lGSppWv+606jb6O5M7vuHwX/JM=
*/