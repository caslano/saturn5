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
SGEQSDViXL5c6w4Z+8vewF/ngyNj5xgDMmfcO/jFRNsp+WlXvhHkjgZvt/cMlqd3/qpX1o3uJqyMIP2F4IfpJ+EQJFq1Pq3/1S0IMStqyT5PuUxkf/+csthILGnw8pxP9LMMNdQ+rNSLwuhvgIyPoZdqYJLynP3W1I+1aIH6TRNVqqYwDLyfkEIoMtk/MwXNj2ffxB1zDGXZK5oAw5d60uH5rRqPB9D1baT0mWT9E3pWiawyIiisAzl5P7YDhfGKaIejVmHW7so0rfc2V3XiVeFstmH70C72hsbn/mft0PXRG8B5efHZ6vbDjFkhb0dJ+0W534UYnXXhcp0NCgzi0zgbFc5Z3YT8yiNrtUBtTDSc2vBrC0FQ9+3AxJXzWI/Gr9P4vaeFqq+taz31x8r2orjjZAxlt7EkdgBcp14DlQo5d7n+FsAdQxQVOpr88gzhB/IydVyXH7k0H4ENbQiPN1BjQHXGqdyOtf7RtWUbuPU4AZDmmjRJpdTYU89CjPHcIze+xybbYC8cGoFNr1Qh7kVb2Eq1HBvlgg07FVHipWKachqndxECUexKvw==
*/