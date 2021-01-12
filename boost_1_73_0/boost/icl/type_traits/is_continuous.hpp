/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910
#define BOOST_ICL_TYPE_TRAITS_IS_CONTINUOUS_HPP_JOFA_080910

#include <string>
#include <boost/mpl/not.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_continuous
    {
        typedef is_continuous type;
        BOOST_STATIC_CONSTANT(bool, 
            value = mpl::not_<is_discrete<Type> >::value);
    };

}} // namespace boost icl

#endif



/* is_continuous.hpp
4RYKgenvZh1M657+CUn/MtJTDT8fphoOXeKPthiS+nXPck+qolyR9FBYkYRlXxlJ+t3nu6W/JoGkV8NCEooIRN/wac3Y3z1LUFH1S0VVk0NVh6GqunuWl4KKKu1ld4DsMB2gl11f5dWuQO16tywaKtCoru6O6oMK1TGdq8ALVYEbVbZB1bqnG6pCjUrJqk8Pymo4eE/1a+1p6J4lHFQ+SFrHKoH17aEFFmYmCqyme6YfpyiB
*/