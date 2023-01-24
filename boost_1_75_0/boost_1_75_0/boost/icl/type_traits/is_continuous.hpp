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
UNByZYjwNRdUwPqIsU2X48ssOkCmj7XRAZY+FsPUkHRc7C2wlGOEMb6lra1aHdBxZn9iVeebqu1PHIJXbN/xXPfaHVjVBE/R5NoyGlLT2GlTGhfI4H9rMb1s8SQqj90VxDydivm3z3IqtYCt15tOzXLdZTaXxTFpOXwqjgErUR4DxvpnjCOqTNfK25aN+U40u3l5irj+N86ZMkq5eW+m1Vzn64/spKn+d81i4e9mtn+MniJVxT0G/NSqtDZGMdmibciOljJ9ZDHRLXMR32LN8FRXG1ttKZJ+q2yy83pvtTsYqvfl8Wbb0GbsF0llpS6WoW8tpiWTPpbPK7HPRzKmSdo+NBsmsY/ocTLt4Kjss2pHR80+mnZ0VIw9aDZkmHc4m+8ax1tV2t+xWrUqqNGqvVqrRlWN0tJl701tSgRJqorWHrWqKKWqSuwZQu2ZVmuGBEEoEYSEROToOde5zvrnvr/X5/6+z/O+ed7nvvK8SkmKl6x2bgzdHvb3N7kcovGL+XfIUa/Q9b6lBt2ioJlEbPE45BVvv5yeNivbs0fSQjkPg65SCwQ6pBWgnN/HNbyEfzs8+lJiXipZ7m2UmfiF5arLqOFVnR2JgeDMh5m6x70EzSOgGk2lUvLBPZtozHkjhkOVOskng2JIGja+Mew7PVBPALwlZAFIcUGgLpEIj5ORSwjdIwwkWWgZCcMesAKgYlE09LcdlGqHVhoN
*/