/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_COMPARABLE_HPP_JOFA_100921
#define BOOST_ICL_CONCEPT_COMPARABLE_HPP_JOFA_100921

#include <boost/utility/enable_if.hpp>
#include <boost/icl/type_traits/is_icl_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= Equivalences and Orderings<Comparable>
//==============================================================================
template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator != (const Type& left, const Type& right)
{ return !(left == right); }

template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator > (const Type& left, const Type& right)
{ return right < left; }

/** Partial ordering which is induced by Compare */
template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator <= (const Type& left, const Type& right)
{ return !(left > right); }

template<class Type>
inline typename enable_if<is_icl_container<Type>, bool>::type
operator >= (const Type& left, const Type& right)
{ return !(left < right); }

}} // namespace boost icl

#endif



/* comparable.hpp
ijJ0QRlaI6j2YYztzVFlr937e1VG6UJ7C6JsXw+9qTVsLneQ+9qVqllBUZTElHwLV57rjmr9Lh5bCOdH2bQgWKvfLl8rCLYEhMf/wREuRkL1siXwF+q6nG1MVx0NyRq0blwcmpVa6SthgBo3Tl8xMNHU7yugKcCmY9ybrEBvKOJSsAsdCnZ8YFt7phhCc8lttTQntRy4IgWUPM2BngwCZfH0d/sK8duvuGk61RR9Mzt8q0LCqHv0YQLallcYkUwDHQ0gncMauVAZ4IdkOSZOqpN0MQPvOjazQ+jIgA6uMZuHLEnkTTnWDk65xTNu7UC3/CDZT28oOYBMNczEQvdMhcKt3GnJ44tVlkWSAinEx5uLC5RXdVBO/o4Ts0+cFN+TFWjm4hd8TaKpbvcHpnSoH1cq2Y4vzNjexJ+OyivVCaXg2GGKadtMIVXL5r6goqjr296HwaQ/Oj06fjN5e7Dr8F05d4fS4w5avNctKwdPVJLwrHBkY+/mLDsysvhAXjI8JmyVJb5UOAV70GIwtZMQkdD3HZVGKjnzSbFi9e2ZZlucNkWPD8xLnIspLxXSwhqtdqzaoezM2pqBH5JKWzO5TpG+6xS8rhIbdtX85e89A7GgddFH2TZO8ttantkK3zzsP1BK27iIbuX58YkS
*/