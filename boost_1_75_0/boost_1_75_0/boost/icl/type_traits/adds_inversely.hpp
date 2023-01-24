/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829

#include <boost/icl/type_traits/has_inverse.hpp>
#include <boost/icl/functors.hpp>

namespace boost{ namespace icl
{

template<class Type, class Combiner>
struct adds_inversely
{
    typedef adds_inversely type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (mpl::and_<has_inverse<Type>, is_negative<Combiner> >::value)); 
};

}} // namespace boost icl

#endif // BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829



/* adds_inversely.hpp
MzlTUY8pF1Oa8CJarmmgPXsTe86g4bu2jMA+/c9r5e/SfG3j2zZMR7zmjV3o5hoVXZ2ORTp2L34QtMZwgBhS2MLI3w0drlzkDQqVQm2MU/GNP1zqW2l8CPDRWajDi+geba2g1HargJ3WmU7HmekgDujHZmAspa8U6LTi8I2ZMxHvOecy+RtJr2CfR+Ufo9/XPUsUHSay8TxynaQoqYX8fAyVuQ7xB+X1m0g/0YM8kLP5VJQj+ICO5LMgntntQB8qnSKXA8U06nnPDEzFv5g6j5ld9Ll27C1W/n4xHYPy0Rj6TAHVM6sHojEO6GDsHaO6YVWJNobwTF052mzne2zc6Ud+VOS+2XsKfNCxx8R1ormkzJiXQT9B2+7Jm4DT/DdqT6KulVunUVXIdzvRvjMT55jWvBYK9XZf4m7wR70IPOh9jO7Up30C86Hy8UhiM3f5jHAPfSfoJcqD57Jdbty3Fzuipv+Hoy7udrN3yQyQc6ASdXnyfES0pF0b/HllBMrwl063yMDLcBj+qfL8s2g/Y4Swp2nbTQP9wF/09TdhgYnq6Eloh1FlvpVNtQvdi1xU705DfxnxBO23wgZNvC/TAVrZp+4IfYdeGqoLHGi/u8pMj1Ha9hkYQ4mXzK+u0Z+BPCibbCV0OdHBUsWAljMddz0PvGuiicqAdH/mk+AdieQdI5Tt+4ZoUuYD03H51nSxSYkg+s4y0hbjlO4/
*/