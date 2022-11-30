/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
Copyright (c) 1999-2006: Cortex Software GmbH, Kantstrasse 57, Berlin
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_VALUE_SIZE_HPP_JOFA_081004
#define BOOST_ICL_VALUE_SIZE_HPP_JOFA_081004

namespace boost{ namespace icl
{

template <typename Type>
Type abs(Type val) { return val < 0 ? -val : val; }

/// static class template for the size of a type's value
/** This function is needed to be able to order values according
    to their size. This is used to e.g. prefer simple test
    instances and to express this simplicity independent of the
    type of the test case.

    @author  Joachim Faulhaber
*/
template <class Type>
struct value_size
{
    /** The size of a value is used to be able to order values according to
        their simplicity */
    static std::size_t apply(const Type& val);
};


template<> inline std::size_t value_size<int>::apply(const int& value)
{ return abs(value); }

template<> inline std::size_t value_size<double>::apply(const double& value)
{ return static_cast<int>(abs(value)); }

template <typename Type>
inline std::size_t value_size<Type>::apply(const Type& value)
{ return icl::iterative_size(value); }



}} // namespace boost icl

#endif

/* value_size.hpp
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
*/