/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_MAP_HPP_JOFA_081107
#define BOOST_ICL_TYPE_TRAITS_IS_MAP_HPP_JOFA_081107

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_map
    {
        typedef is_map<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_map.hpp
6tpwlignWMRIELP1AqbCDo4NLbfrr8/fZq8awxgn/XtXO4cGNvXJTxlfPwmzwPdRl6yXOj9KJUCeuyKzlXE/95oGAvIp105ENtPYy6GDUC7IdIoaZDDxTaYPL2/2uZOBROJaZGmLLOYiqc/OR8AoMPAEKHcI6lZ6tPFPOoqpCqwB/ajNoaYoTQOTMKGnveu+umNZ/6J4/LntBWU/gfKf6t3VTxy2txPe0Is0H2rXCtwICdVlkO0/AIkCsF2RAu2XU/oql8zK+KK7/G1e7Shleyzfc9PLPdAwlKTwZsYq/hBBbtuPZc4LPC4dj+7QFdrkLDfvp1WRy1uGk4CTj0JqHiZiTqrc3ceEiXB+f9iqhuwDDP3MH4kNZvXb+xdsOxyhqJc11LASx2mLXN5g41pmWVkwUpgJtKxVim+FvwjkclRhxsvwXd4C/0cJUVSYE8SXcGPwlP/iwNlN183UMNnjxWYpcYvozL6LlIZdALAvThJX0n7LewNQ3E8CnFkSWdaBJD10QtCkmISkLHQ+MRQhw1ZPsjjotZ9Zp7e7sL3AJhqa8abzCML6u0fmeQ==
*/