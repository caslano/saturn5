/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_EXCLUSIVE_LESS_THAN_HPP_JOFA_100929
#define BOOST_ICL_DETAIL_EXCLUSIVE_LESS_THAN_HPP_JOFA_100929

#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

/// Comparison functor on intervals implementing an overlap free less 
template <class IntervalT>
struct exclusive_less_than 
{
    /** Operator <tt>operator()</tt> implements a strict weak ordering on intervals. */
    bool operator()(const IntervalT& left, const IntervalT& right)const
    { 
        return icl::non_empty::exclusive_less(left, right); 
    }
};

}} // namespace boost icl

#endif



/* exclusive_less_than.hpp
O/6QM39q+3OQqTN0mXpOgF7ACKrgj1Gr7JipR04zBkAL1JMVeK4SIWbXfwjuoaL+E+UNExAgzqv6kdxo7v3gEUTTR0vB0hdakzSJ0W0h3/BB9BSBWXGNDnza3st5jGVBUSM38CNo3hMSkrTKIVftuwb9wHUE1CCkNHluP7TDpwaiQaEFABRGFcQhXuT0eO5EzPiCWUxrHARgrIPYe6LstYERaEBuDM+gYJSgB3Q2eQzCe5Q9IB7Dy6S2ZjB7Ct3xJEaHc0IO4c/pcYP8FEx8cmN7074TjoUXcMKpG2FrUXzzyGkACbOnBtjN0B3BX6jsLVAyBJUIXTAoh0kzCkbxow1NoWT6T4hrNg/BKFDt4gk6D/yL7B85DtIL/HBAlOPQBg0aNpDqBxcVCdWEMgGk9UDNbZA0ALjkDpgZMC1K6RWvZjNwMsgG5BaUdFNj615rxOxcdj+p4Ep0k9wanTv9QrsgimrCd4Wo7QsKpPa61x2DXOhms6XqIFa11SJQylDbXV0zEdcnvXtNDO1KNaBIB0oBvhR3u9nqXejtK1pQv7lt6VBLioB0LhHHjWY0r+GJeq639O4XWv2l3m1rJjgbvU3aHaLdae0uMa8RT4ayc420dPW8pZHLjoGo1PYXYt5qTV1tNYBuQ2t2G4BC
*/