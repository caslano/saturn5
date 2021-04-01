/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004

#include <boost/config.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_set
    { 
        typedef is_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = is_std_set<Type>::value); 
    };

}} // namespace boost icl

#endif



/* is_set.hpp
Llri1reIqmOjVc3UMy6kY+Ty1EViIFij0GCmJ9G4Y5a8p73YTQGyoK/qt+LoQM2DeGRbK/kDTRHp3K7ySv7cJbp+1iSKHTFcfs3VbRxGg3IcbfBlenRRXBpTZs1Fgv1apjm8JvD/3u3mU0PF8ttIaFhnuReMhaTiYPARPc1oyLi7HPMakOxadrzeD7ya1i3H7/VMTMY2pR9koaTPWsvFsBryH9bofFLF85a4xN30ORYcTeCFJb1RPEYwf9pQctCaBYRkriMP9S1zcjSLUpWUa1nRQXoyjrAJixPO4r7lrdsXQ4bCXIbpW6UEHFP0vqGxGg1ADUrtZoScPhlw8JpcaLlpVRxZbUn4EpQOJZogmHL5N3Rs1zGrcDptaTEGCvJRV7L9SIOUch38tU6kKSixOyxRpw/9o1/VL+vncCf+Q+9vatQCJARL39sHO2jjHJo33OK8Sx4LtwfQd7Hv/uT8IYBczLFLCxR9iot0zXHvvBcEvUh2TzlCS2FurCW1cHjoE8Mpsx6eIZH+O9mTpGss27MhlYx2wwUctJirxUHnkocgEFqgdBspnXZcag==
*/