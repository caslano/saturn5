/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828
#define BOOST_ICL_TYPE_TRAITS_IS_CONTAINER_HPP_JOFA_100828

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/element_type_of.hpp> 
#include <boost/icl/type_traits/segment_type_of.hpp> 
#include <boost/icl/type_traits/size_type_of.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)
    }

    template <class Type>
    struct is_container 
      : mpl::bool_<
            detail::has_value_type<Type>::value &&
            detail::has_iterator<Type>::value &&
            detail::has_size_type<Type>::value &&
            detail::has_reference<Type>::value>
    {};

    template <class Type>
    struct is_std_set
    {
        typedef is_std_set type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::and_< is_container<Type> 
                              , detail::has_key_type<Type>
                              , boost::is_same< typename key_type_of<Type>::type
                                              , typename value_type_of<Type>::type >
                              , mpl::not_<detail::has_segment_type<Type> >
                              >::value )
        ); 
    };

}} // namespace boost icl

#endif



/* is_container.hpp
OR7NF+Hil4WrB+kqtrApwaEg5RXvCKaJGq5+msGVGx1S2QS9033NW5GqDUxF712sZ57M8YTQPuujYNzpyt27ro8OczJN0+6uZU8GKBUFAC2wd4COHB1aUd1Avs3d4dE4DeAB/LeoyJkBLduuucNJU3dlaWk1KM4XHew3suhcfdDaHlydLmlAmRWdpzJumxS68HO3LM1VgKRm9h+1JRi6YlJ2junaIns3kSRtCmqp0RDGjWB99qTajbDOV7F22u4TTPPaPmq0P+eLU38DyhMhboybKaqN1y2PaLW9u7Ri2oKNs0grlKwrs4MpY8ZpmzJ0e8sIZmlNByJ3a2T4xHMlOF472OWEyV5AWOsnHPY6sHGsnr3VxVn9LkfQ78Vx7dWDsy+r/4QITgobzI0dpuemrLwGHTE6Ye8kr7hxgZ83cCZljUnol/3EWczdiDtSXH684MP7rTJ+6oSt7SRetjZs2NOXvqlxJarjx+e12cFOPzpj8/8dj967bOZG8PZUXJmWDkb+MxT3Bd252LGjvdP1mFK+/LihwR9hbztdbbDujkU7s172C2qMd6bmuY6fF25VR/kkLbG2Kefl9SuXn819FJ2WoR7dciMLTcR94uFZ8ss7XMODvCNBbOnOYeboHNcw/kbw6uhO88rfAOJ0
*/