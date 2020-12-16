/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_MEMBER_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_MEMBER_VALUE_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/parent_from_member.hpp>
#include <boost/move/detail/to_raw_pointer.hpp> 
#include <boost/intrusive/pointer_traits.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type will
//!store a node_traits::node
template< class T, class NodeTraits
        , typename NodeTraits::node T::* PtrToMember
        , link_mode_type LinkMode
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   = safe_link
   #endif
>
struct member_value_traits
{
   public:
   typedef NodeTraits                                                   node_traits;
   typedef T                                                            value_type;
   typedef typename node_traits::node                                   node;
   typedef typename node_traits::node_ptr                               node_ptr;
   typedef typename node_traits::const_node_ptr                         const_node_ptr;
   typedef pointer_traits<node_ptr>                                     node_ptr_traits;
   typedef typename pointer_traits<node_ptr>::template
      rebind_pointer<T>::type                                           pointer;
   typedef typename pointer_traits<node_ptr>::template
      rebind_pointer<const T>::type                                     const_pointer;
   //typedef typename pointer_traits<pointer>::reference                  reference;
   //typedef typename pointer_traits<const_pointer>::reference            const_reference;
   typedef value_type &                                                 reference;
   typedef const value_type &                                           const_reference;
   static const link_mode_type link_mode = LinkMode;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr to_node_ptr(reference value)
   {  return pointer_traits<node_ptr>::pointer_to(value.*PtrToMember);   }

   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr(const_reference value)
   {  return pointer_traits<const_node_ptr>::pointer_to(value.*PtrToMember);   }

   BOOST_INTRUSIVE_FORCEINLINE static pointer to_value_ptr(const node_ptr &n)
   {
      return pointer_traits<pointer>::pointer_to(*detail::parent_from_member<value_type, node>
         (boost::movelib::to_raw_pointer(n), PtrToMember));
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_pointer to_value_ptr(const const_node_ptr &n)
   {
      return pointer_traits<const_pointer>::pointer_to(*detail::parent_from_member<value_type, node>
         (boost::movelib::to_raw_pointer(n), PtrToMember));

   }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_MEMBER_VALUE_TRAITS_HPP

/* member_value_traits.hpp
3WA18s5MS47Mv7WWJn+oE5yrcV5f4O6DysSvDN/wVfoGMI7mo00ezALdGZcEUhfiGloifiT+ROAfUviBEvOdGvLHx5M4U4y5U5PEvdRIveeR51T95mr1q5+Znb49nNmjPDP7Mtw/C0HHUpff3LeipXJVU3iO/FLu7gN7CP5k6ARPQdrGu6lM09bir3H3fKslrMqaqVrEzGOMr8uDsNLV1qh5Ev5F0VWxFzQcMMuVmI75bGighI3F2abtnqFXi98SazRq6HKeB4yV2kPVrInoj/qo4PW1UpBvjrZfOSr+KdHxyiNz7FIJr0YsJZ/1WpVwQ8AnndS+LBh2U+Ceyor/viuJsYs8RJ4px3fUvTmUXeMf1mnUWd6+cGIh5U8d09uV7QnyCMcj3oR3hzy339nsdwaeQBrGMcjU/sBt3xhDfG3ulqnb5TnfleG7GjnCieZxpKfCQavMZPv9SMaRdVWbtL3feIWjvbe/Qr47yfjxDvrXNmyu5wExYF+gFJJ7LzbMkyrtS4Px+t/SJK2C8PjC9PYjvfkyviS8s8d7lsmf9ap2ylXtlNTd90i96/f5jnwynPCd1OP8KcUrap8pZQiFb7mPrIyRC5j4gnHY1kWW1EtVDZbOm+uMvEF8fT5BTvIC3bxeJL7QUuSj3QHtrfm/JDxD3/eTNyRRt8//QvAmyjuIAc5+n2cE+4KASGw1nHNO4EvC5oa2t3fvQRXB5Wp1wPbg2M6yanoJipQ/y6TLAsruDmf4czDJHMDnAKvU3ZJlbhtxmDecG7BuGgW3CbJ/v6ntkJZB/sO75EdA23US/phrn6NGvj/m6WlVe0xty/QS6qr6/grujTmetgh+qand9bQoG9zYsL22iu9nYVd6uZyVCa17QesnBP9eT/Rder4pFtw/2HvsXPds7APBH+DpBn9XX6bebswnJHhFnh52vjXG/g7zxyyxUuYQyb8J+T8meNd5DDJv5nUXct9qh+uC8Un/IcQP44zyJLqXf6OEt3jyYAckQi/5SesPr0tZx0mdHkSyEVzYydBwswHfWh55p9gShbu5rrJ6U3mNth9rkvwvtDOxs8xjXgsk/i7E91mDMQs5ZXtV/L3oR8Bz6zrPkws9tT/FGD3BnoPaqJGy34l8b5Pw+z3Z0sdZLtUltDOIW8N16HnQXmZleq5x9067hacCklYz0npa8BqYFsutpRUE/L3Q182+BHR/0hrKNYWT1gH4fkTS24/0jkt6az0RPmysL19XFbFBr+JQp9EB4D8i+Ds9hnczgrMPON8VnDJJczVllCDRtUVjeneRxzb7s8Q9YKs1SG8rZEtbavyk5EyHla5VwbtUXuEnkoW+I/WQ695jKJay7EYaXdGeF+INXH/Zkz6O+WL9Xa7O8X1xbzGI03yX8xYj9BQeY8TMeZTP8J76J4F3S1b4d3EOIMfdbe20C5OMzDUQc56GMVn6BtpTH5PFv8X1d/uLa1dGtVUu20ofq4P7w0QO417wIrhdat21MjJW11WJUZ1YO9vkY7Sr4A42r71WRusMezoJnWGsH93edhTNRfdE9Iala3rDiq9yaaau/fj5pZA0jxXcNHs5+voOrLu+BPgt8xk10jW+V3P3sJdJ+PvWAmB/CCm0AD6IFGLHw0L24cmC78E5FSzNwH0e7utwhn6HONxHSpxX8O2xpqp8APfCKZlGPtpw+WewFpK3GFkwbzJIXbgOpKVZWr1TVkH8g8DnnRxv6G7/hyHSTPGmdvKOQkwl3VR9ZxVwDsBR7vHrtnTo76De/Dvg7oT7tIJJ7D0TnU395KroewpjV5nvw7zTEk7sC3BevndeodaDgh9aW72p0pV8JXoj94jgbgetc0ztj7SMdqk=
*/