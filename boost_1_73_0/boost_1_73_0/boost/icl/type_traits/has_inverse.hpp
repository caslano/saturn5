/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205
#define BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205

#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost{ namespace icl
{

    template <class Type> struct has_inverse
    { 
        typedef has_inverse<Type> type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (   boost::is_signed<Type>::value 
                     || is_floating_point<Type>::value ) ); 
    };

}} // namespace boost icl

#endif // BOOST_ICL_TYPE_TRAITS_HAS_INVERSE_HPP_JOFA_090205



/* has_inverse.hpp
4PaOWuHb+E6w2zjXw5yc39KYnAZi8i7jD/BhFSP/9DIaWT66zSC8QlFjbU4Vq4s8oynvrRrN0dhn5AXOe4QJzXzj+o6F/VoUGrJpqLIopNbjfjVYPDC/P6YGc0WMFKHI97xwu1fdG1uasE8C5XogRLP5OBfsIjx58T0Ty8WCGl/DiOYLWP9rvQ6LICBlWWRm2hmvTQP1FJboff8EdUISGIzUGbZN9hQsavhHvh3Y/qW9ydyBkZlGy3DQ+QL2mCGZN68cTxNPXUVC59yG05+Pgk2s+jF8F7a6SctCjwVu4jIlHoK9oHEg8u08zhNOc9yyuOEEI57CX3GKTu3Qdi9xZPj2xqPqcoC7nRprkler8T51xnoemuYzXqZSybCa7h+T4b3dV0qwwtCPHPfM9p2QZlqQZPvVthoPUCb/A2RetWYM5kiDgibak1QssviOyRI2I++aFJLFU+py6ICiHt+qxuRxffq2NRg4fjTwvdHAC12PWphNGj2hJymoaxKXE1LsYqmKUJ5zGmsvp1NIYJaXuUybKwLwmuA5pcpboiAgqxpoVH0tNaOZOGxEcRgndKJMPWjo9775QzmvOk0QDhwv6ofvI9sbbjxF+oXNb1gcH4zH+PuhBNJoyLXO7cj1KhOt0aUqsJbdO/cmcDaZ
*/