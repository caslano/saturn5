/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <cstddef>

namespace boost {
namespace intrusive {
namespace detail {

template<class NodeTraits>
class common_slist_algorithms
{
   public:
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;
   typedef NodeTraits                           node_traits;

   static node_ptr get_previous_node(node_ptr p, const node_ptr & this_node)
   {
      for( node_ptr p_next
         ; this_node != (p_next = NodeTraits::get_next(p))
         ; p = p_next){
         //Logic error: possible use of linear lists with
         //operations only permitted with circular lists
         BOOST_INTRUSIVE_INVARIANT_ASSERT(p);
      }
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static void init(node_ptr this_node)
   {  NodeTraits::set_next(this_node, node_ptr());  }

   BOOST_INTRUSIVE_FORCEINLINE static bool unique(const const_node_ptr & this_node)
   {
      node_ptr next = NodeTraits::get_next(this_node);
      return !next || next == this_node;
   }

   BOOST_INTRUSIVE_FORCEINLINE static bool inited(const const_node_ptr & this_node)
   {  return !NodeTraits::get_next(this_node); }

   BOOST_INTRUSIVE_FORCEINLINE static void unlink_after(node_ptr prev_node)
   {
      const_node_ptr this_node(NodeTraits::get_next(prev_node));
      NodeTraits::set_next(prev_node, NodeTraits::get_next(this_node));
   }

   BOOST_INTRUSIVE_FORCEINLINE static void unlink_after(node_ptr prev_node, node_ptr last_node)
   {  NodeTraits::set_next(prev_node, last_node);  }

   BOOST_INTRUSIVE_FORCEINLINE static void link_after(node_ptr prev_node, node_ptr this_node)
   {
      NodeTraits::set_next(this_node, NodeTraits::get_next(prev_node));
      NodeTraits::set_next(prev_node, this_node);
   }

   BOOST_INTRUSIVE_FORCEINLINE static void incorporate_after(node_ptr bp, node_ptr b, node_ptr be)
   {
      node_ptr p(NodeTraits::get_next(bp));
      NodeTraits::set_next(bp, b);
      NodeTraits::set_next(be, p);
   }

   static void transfer_after(node_ptr bp, node_ptr bb, node_ptr be)
   {
      if (bp != bb && bp != be && bb != be) {
         node_ptr next_b = NodeTraits::get_next(bb);
         node_ptr next_e = NodeTraits::get_next(be);
         node_ptr next_p = NodeTraits::get_next(bp);
         NodeTraits::set_next(bb, next_e);
         NodeTraits::set_next(be, next_p);
         NodeTraits::set_next(bp, next_b);
      }
   }

   struct stable_partition_info
   {
      std::size_t num_1st_partition;
      std::size_t num_2nd_partition;
      node_ptr    beg_2st_partition;
      node_ptr    new_last_node;
   };

   template<class Pred>
   static void stable_partition(node_ptr before_beg, node_ptr end, Pred pred, stable_partition_info &info)
   {
      node_ptr bcur = before_beg;
      node_ptr cur  = node_traits::get_next(bcur);
      node_ptr new_f = end;

      std::size_t num1 = 0, num2 = 0;
      while(cur != end){
         if(pred(cur)){
            ++num1;
            bcur = cur;
            cur  = node_traits::get_next(cur);
         }
         else{
            ++num2;
            node_ptr last_to_remove = bcur;
            new_f = cur;
            bcur = cur;
            cur  = node_traits::get_next(cur);
            BOOST_TRY{
               //Main loop
               while(cur != end){
                  if(pred(cur)){ //Might throw
                     ++num1;
                     //Process current node
                     node_traits::set_next(last_to_remove, cur);
                     last_to_remove = cur;
                     node_ptr nxt = node_traits::get_next(cur);
                     node_traits::set_next(bcur, nxt);
                     cur = nxt;
                  }
                  else{
                     ++num2;
                     bcur = cur;
                     cur  = node_traits::get_next(cur);
                  }
               }
            }
            BOOST_CATCH(...){
               node_traits::set_next(last_to_remove, new_f);
               BOOST_RETHROW;
            }
            BOOST_CATCH_END
            node_traits::set_next(last_to_remove, new_f);
            break;
         }
      }
      info.num_1st_partition = num1;
      info.num_2nd_partition = num2;
      info.beg_2st_partition = new_f;
      info.new_last_node = bcur;
   }

   //! <b>Requires</b>: f and l must be in a circular list.
   //!
   //! <b>Effects</b>: Returns the number of nodes in the range [f, l).
   //!
   //! <b>Complexity</b>: Linear
   //!
   //! <b>Throws</b>: Nothing.
   static std::size_t distance(const const_node_ptr &f, const const_node_ptr &l)
   {
      const_node_ptr i(f);
      std::size_t result = 0;
      while(i != l){
         i = NodeTraits::get_next(i);
         ++result;
      }
      return result;
   }
};

/// @endcond

} //namespace detail

/// @cond

template<class NodeTraits>
struct get_algo<CommonSListAlgorithms, NodeTraits>
{
   typedef detail::common_slist_algorithms<NodeTraits> type;
};


} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_COMMON_SLIST_ALGORITHMS_HPP

/* common_slist_algorithms.hpp
pB36GT8Flqj9LRn3EW1+7gp1HrR77BqlQ/vm+66vtntZbsLOsWoYz5ekq7Xbs517yoNqX2dmHaqm3QvyFlnaMbcqnWj1vB2Nva5oKteIKzWumifOXcMKvk4SRbekqVxzNTqEnEe1k29OgDDmaOPcyNj0cPoazbbxhmH+gLImiNE2xNkijGuuTGtvmnOMYkTVU7VKv4kbbV+fT2CJYT6Be9P55xXffAK9Rw3vOHH0uOz+9sQH6lyuTa9wPgHinvy8B6Qt50GeYyWf05sH53NuY86nIZ8FC5h6Ra65dY0qzivx9f4t/ioonBfqWSqgXEerUC7yEWRfHI8wjhdQ1tFnBpd1YzopGsoqEz2EdV7SXwm/Tyb9lZOf52FteuXzPPSUsnZvEVBWeT/p4JTV//O2vKrI+1vF5e3glMEpr6Gsup68S1RhLhHy4JS1tn9Z/cp51FDOJ6inzFDlnDovj/MaVjkzA/J/vArnSs+/6nOQ/Oa0DM7vxzz3ZofKL5+0aSDy87U2+1gY+dDrKL6Vuf3MCXlMGqTge6t57rFTaJP0e4OeX+us4Pw+yTktMOfX2zCFeU5JQ3uPqrhdKjiFdkk7/wHf6TleQHnLAssrz+VF5vJK4xTe+SmqQttUdApt0wdNKm+bjsOD/8E1a0/X3DRVXcs2aZkdvmTRpO0lbRdce9tL24f1iF949Oc3Z01V17IdMt0OHz/t7tfi7x/z1yVfTvjm+rSxe39+a9ya55qp+pw1Fc1Nswfhp/rM18N3xU9X/lbfGMr4uysyDZ0Cezgdf78n4QNc6tnTCecZ3Pm7l/Y33zqUfmsXaWnp99R0+mp/9xb9zci58vcu5Dz5+xjST/7uRjrOPAS7y8fzlwWMiz+LRslmaxgN28IY2AYmybZvnpViSSdH0tHnWXlUxtdvlnHXJbCuzA/TDv4WdoTbYGe4BQ6HT8KRMk/MxXArnOjVk/ktxCdT/FfL9PktZL6YKLgTxsNdsKHMF3OuzPPSDb5lybwfcBI8IOPxfweXwYPwBpkn5kbRvwn+Ht4O34BrJb1i2e+rlzLJ32WGejks9XJE6uNPsB78M2wv88n0gn+BfWU+jH7wbzKvzkcwD34MZ3j3yzwW4ncGL5Dj6vNYdJHz2g2mwvNhmoxzbwt7wizYHQ6Rce5DZdx7tmz77KdMjhNnsJ8OcpyOYj8ZYj+dYax3W9IRHybQwJBOf0lngKQzSNLJgvVl+wuZsyNd0sl0edOxy3VC0vmaaqkJv4N2eAviNYXfi939IPMyWISPsQEL4JnwctFfBD3wKlgNLoPVZd6VaPgIrAkfhQlwM0yE22BduFPS2Q2T4auwnsybUx8eg6mwDDaE38FG8HuZV4Y0rWbwLHgGbA+bQ86pymdP2MKZF0d8S6QuywLmxflU7O+YXB9lUPV5wnT4hdjhP2AH+JnUE9syv5T4b4DrJX19fqkhMr/MCLnus2F9OAm2hFNgW5gn1+NUuQ6nwe5wNOwj85AMg+Pl+p8AZ0k6i+Cl8Co4ERbBHLhMm/9jpeMbwDUt+ayDoKN+xKWd4B8p77VSzl/ADAmfLOHTJHy6hN8Lr5P5ZJbBJ+D1cKvobRO9/RL/VQmXdcul75Z+bcmXvm75bMnXXNgKzodt4ELYVsJnwkK4ACKq/JfDZaJ3vej9SuLfJuFiH9KfxzVvsI+bxT5WwsbwVthM5vlpbudZ2u9VsKvMA9TD3i/pZyEHJf12kn51pLuknynp95XrsT88S+YBaQ37STkHSnrTnf4RzE7Sq4lMkPTWSHr3SDt/r+SzWOzpAZgr850tlnnOSmWes52y/aJsS/75Vh06/13keF0l/90l/z0k/90k/z209LIlvSY=
*/