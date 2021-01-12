/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416
#define BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416

#include <functional>

namespace boost{ namespace icl
{

template <class DomainT, class Compare>
struct is_increasing
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT>
struct is_increasing<DomainT, std::greater<DomainT> >
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_increasing.hpp
Nq/1NuxjWDVvWmCAhtczpA/ExqXay1jskefy1mEmjb1v822msxLSBYxXgHzN3Nn2wXt8PH+biz7h2cu9z98idbWyL1AWXY2aIk2P7aLMzbuAPVxPC0TkzV42l8z6Ldws6MhGaH2FvxT7vvRc56+61e4F5EnzGVawzPQU5rfZH00M4OuSCKjwB/EmFqgh5z5Sk9OS61fHLNfmKje50d1IEZVKqN++lKaIbz5JurXX4/T6bT2X
*/