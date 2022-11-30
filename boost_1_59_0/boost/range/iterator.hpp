// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ITERATOR_HPP
#define BOOST_RANGE_ITERATOR_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/config.hpp>
#include <boost/range/range_fwd.hpp>
#include <boost/range/mutable_iterator.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/eval_if.hpp>

namespace boost
{

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)  

    namespace range_detail_vc7_1  
    {  
       template< typename C, typename Sig = void(C) >  
       struct range_iterator  
       {  
           typedef BOOST_RANGE_DEDUCED_TYPENAME   
               mpl::eval_if_c< is_const<C>::value,   
                               range_const_iterator< typename remove_const<C>::type >,  
                               range_mutable_iterator<C> >::type type;  
       };  
    
       template< typename C, typename T >  
       struct range_iterator< C, void(T[]) >  
       {  
           typedef T* type;  
       };       
    }  
    
    template< typename C, typename Enabler=void >
    struct range_iterator
    {

        typedef BOOST_RANGE_DEDUCED_TYPENAME  
               range_detail_vc7_1::range_iterator<C>::type type;  

    };

#else

    template< typename C, typename Enabler=void >
    struct range_iterator
      : mpl::if_c<
            is_const<typename remove_reference<C>::type>::value,
            range_const_iterator<typename remove_const<typename remove_reference<C>::type>::type>,
            range_mutable_iterator<typename remove_reference<C>::type>
        >::type
    {
    };

#endif

} // namespace boost

#endif

/* iterator.hpp
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
*/