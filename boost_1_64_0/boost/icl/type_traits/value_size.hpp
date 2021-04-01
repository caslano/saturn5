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
PXM4/etJE0gprg4l5cYRJkaAOtA1lifO3zqkmUqBLFjahyMkfR2RxBGMRtn9uWInN3phNGIL0r39LNExq1hte928892e69yEdrGVwRbV1O3UtczzZBVKkG+9gTQBFPnoStjor0Uqp11BY4KVC0bdTokYti3NDUnscXHgMiIpM1oikAX1Y21G4pxQI0OJKbFv2IRKHNAymuMSj2PABKIBwerAhd4zAaESutSKsvqSmMx2jDedOtvxQJWvyKSkFm1AphQwPbOE358OcjshCndeX3EkHix4u01jRaARp32d/pGqvio0ZCt/6T0SyqbhXBUqRk/Z7gTk/yOwv/84CfsJZ/YSQsTHJfgi04ATikOSXYQknV6vOZt7fJxZ7onqW0xRE+tXaON1SFVlGyATdZlfUf5BY8V/R5gg5NH+YlQcDhtWVKXc6DbYw+5N6FfDIaOKC7tvxGYP5K8AfWAn2pLnowg5h7uLV5l4So4TEY+pJAco3LTk6Z7ZH2YOPovPDNml6FGyuXCK60SmDmiNawXD5vQNPDfPDd/kdI39Hu5wa17IZslT1/3bZE1YXw==
*/