/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_OF_HPP_JOFA_100910
#define BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_OF_HPP_JOFA_100910

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(interval_type)
    }

    template <class Type>
    struct has_interval_type 
      : mpl::bool_<detail::has_interval_type<Type>::value>
    {};

    template <class Type, bool has_interval_type> 
    struct get_interval_type;

    template <class Type>
    struct get_interval_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_interval_type<Type, true>
    {
        typedef typename Type::interval_type type;
    };

    template <class Type>
    struct interval_type_of
    {
        typedef typename 
            get_interval_type<Type, has_interval_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* interval_type_of.hpp
XpFuDrCpzoJGmq5TrjmCsbhQqZJIjm0aTcS2qvLy+uKCdoWlYpfGklPHLZFFUxy4YzqYGMl5rcg1RRPJoioU5DZZADecDufnP4pnk8Iu35d/Evutjrcsc6F4Y2yVCEvHSpKPFsaQVKnZ6Bg2yBDVlEvns8FyNp0urslKa4dI7oxWUdbA7Hfw5DyVFZbtsBdK/cbWRpGN7kHF2SMMRPNvAtF64gA3d9qICyW5FFGi5XKsCaGeVUYGB3DpskNMZ7rSjOlql1cEgAvyYfy3pyKlyyZH/YIIp2Bb83PI2qEE3Cd3sGGDA48H4/bAO5nZzGFlZattCVyaJLIij6D8Udarcy88KhjgbIdJawBa2pzWImDXWsjmN24lgQEcJkFWyixn/CUBGxIxLlI4IdmjNVCvYfIK2fvZ39pTfYtko4Leq8RvnBdQxmzwl7NtWRLNvSkoSiuxIwBjdRGcUB72Swh+uso69mebKB6uj44ANx5lYl1XNfs/h2JJ8IKUwhWuLVo7Ke9d+O6yxe+eRTkiFbThiOXfEasg6JfO9wi/KTtakDAc8K2ke+tThVkBSq2BdFnUeaXJK4wwEL4IADdF6bHPJQoS0WVnAfGf2Z/yQj8jijbKiWezD5SWJSkrI2DPI1nITjmSR6VOgwRsvRl0
*/