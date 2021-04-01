/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_CONTAINER_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_CONTAINER_HPP_JOFA_081004

#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_container
    { 
        typedef is_interval_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

    template<class Type>
    struct is_interval_map
    {
        typedef is_interval_map<Type> type; 
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<is_interval_container<Type>, is_map<Type> >::value)
            ); 
    };

    template<class Type>
    struct is_interval_set
    { 
        typedef is_interval_set<Type> type; 
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<          is_interval_container<Type>,
                       mpl::not_<is_interval_map<Type> > >::value)
            ); 
    };


}} // namespace boost icl

#endif



/* is_interval_container.hpp
5eWF6HC18St1Tj2DuI9ezVP5SNfx/1RS1TjSHvmdl6S9CxyiNuV75HLBjZBGg9TuOHR3YMZOBl+sSg3OONUEVR0gVrhHUG13mRt1ee9IdwDzbTCXfoV1Oax4sHRadDiV+BXp0lamUPtbBcz5oNT/qFip940HeXjIqIzFNo0Nd7ijavtuMArgUrMILTKQSIUit6V59+2QGmmt4bYA2urVF/YVmHqAe6Ail+pM9pzpvWw3PLZkmx7TiuVk48tNOYsCut2RK+ZnLe/88C0STN13E8gszGvhmtLa+GjQ4iYH3aXIBGL5kqVi3sMAkY1yW15aBXt32C8q0BMgJRBDpUpq3MRxSo1thiR/pgn1XkoOtXRB90kZcuP8axcqZJWO1O6aexdX7aNoNqAMvj6jzmhU5SvTBXHjWwSEYbE3WSA51j0OTRjqiP2cGj88YmKtLhJnYff4LbxddZWJ2qEMi14LSHqRfRORtGk0Zu7+zrWPthxzCgg3YDr6OD1GV26BxCWBHJozx8ensTslkuKHpNp8d5dx2qCyUvHSfBh2ietmzrnhYqs126/t8Av5Bg==
*/