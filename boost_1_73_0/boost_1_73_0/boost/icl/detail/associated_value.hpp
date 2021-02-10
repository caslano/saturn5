/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_ASSOCIATED_VALUE_HPP_JOFA_100829
#define BOOST_ICL_DETAIL_ASSOCIATED_VALUE_HPP_JOFA_100829

#include <boost/icl/detail/design_config.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

namespace boost{namespace icl
{

template<class Type, class CoType> 
typename enable_if< mpl::and_< is_key_compare_equal<Type,CoType>
                             , mpl::and_<is_map<Type>, is_map<CoType> > >, 
                    bool>::type
co_equal(typename Type::const_iterator left_, typename CoType::const_iterator right_, 
         const Type* = 0, const CoType* = 0)
{
    return co_value<Type>(left_) == co_value<CoType>(right_);
}

template<class Type, class CoType> 
typename enable_if< mpl::and_< is_key_compare_equal<Type,CoType>
                             , mpl::not_<mpl::and_<is_map<Type>, is_map<CoType> > > >,
                  bool>::type
co_equal(typename Type::const_iterator, typename CoType::const_iterator,
         const Type* = 0, const CoType* = 0)
{
    return true;
}


}} // namespace icl boost

#endif


/* associated_value.hpp
2BppGWkmCZeBVXJW3oLPa8znceaQ5AimS18EDA8VVVmXkTHuv9LvBTAYL2ZwidEG1EemFNtNF33QnHHvovdJQ9GIZUBynNuyESDfFGg5O9tVGKpyM5BSqdvU4oq7BGrdD2KGAQI+AQKelrvxgTM5lhDHw12JNI9kzTdTfUFZTCy2SYtE8OZSpk123/ZECZPYLzC1Rd2tomUM2zKQRSwM4zrKXlXYgHTAvJC2phRJBJbBiaPZdTqoSaYxColFi9XgwtmWihNGteBZURRhPA+wCWN0y6gjFwRRWbNllUB0q1UC/nnRXAxVtVlKpZJGwF+0n3bvwZ2lswMUdTcLoBxI8zRuUAKh04DvCgXi/6v6emAPRpNFTk5Pul3yDj5OTzrk93gRkWsvXD7QdC5Eb2jKug4UE6+vDvO2Q5g1+ARqOmb9KMvT4GGViwLM4lm+weaP/nkRIzIxt/LZBS7jJ5b7jBEMwZRBuOfQX6DWO9hb1wFOcsXaYeBYF52OLwACHsAyi16SlP7KW0lCvRTbpAdtBjTVMfvKJI49cD8bY5NYDrkZ23dW3+wTzXDgb40Yoz4TMm7dK3uMnag3NCzIvDEcEtAaGyPXMh3E+my5V2RsXhpjULFBC/BK7FFveNu3RpdM0bq+GVpgpQQg9gAx
*/