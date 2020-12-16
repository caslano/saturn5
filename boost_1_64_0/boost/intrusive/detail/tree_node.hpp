/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TREE_NODE_HPP
#define BOOST_INTRUSIVE_TREE_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
namespace intrusive {

template<class VoidPointer>
struct tree_node
{
   typedef typename pointer_rebind<VoidPointer, tree_node>::type  node_ptr;

   node_ptr parent_, left_, right_;
};

template<class VoidPointer>
struct tree_node_traits
{
   typedef tree_node<VoidPointer> node;

   typedef typename node::node_ptr   node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node>::type const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return n->parent_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const node_ptr & n)
   {  return n->parent_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->parent_ = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TREE_NODE_HPP

/* tree_node.hpp
fPKjp5NaI2PG/61jxuoxYNsxY3nNgrgHaOGeyYz/zPs8IKglKP5zEuOTe4DRwH7AnsD+wN7AAcAk4DCgBzgQmMqx43HAQcBM4KkcE04FbgQOAX4POBR4A9MfBWYZ9zbAMsrTDTSL8mRzDHsxcCLwQuB04BLgHOBFjIu+FLgaeKk0J7qJ+a5gvvKc6BGMaz0aOBk4BjgPOI7p5xrXJ+Bspuee8pY1GnHA84AjgecDR/F3Jn8fBdYafTXwWeaXwP1DNI6JdwaeBewDnAQcApwMTAeeTTnPAU4DTgGeB5wKzAFOA5YBM4A+4HRgNXAGsBY4C9gAnAN8HDgX+BTXdjzD3/siY/GRsfiv6Fh8ZBz+/2wc/g7M7QUdAL0Fir0zMi4f+UQ+kU/kE/lEPpFP5BP5RD6RT+Tzv/T5t7z/L66o6Ij3//r+5bfq79Vm6uv28eqo0luRp4dMQnDJQThXg3MpmdK5CkjE9xP63IFqD8o34kRGcZzQiPUC2pmEsVP/3IHM7Oy80jUFRXn+nCAGcjHe+XZHDhvjdWo73pXxXqQuyn7cX/2ew258P/T3HF3u0o+fe2Vr4p0r7ly0YM771V+88KMt9u8/1O8h7N8rqN9P2I3vhz5eH+pc7lDfH9i95/CPW9Mn6CtV8rg1Y6IYsW8SGfvmFOBW4BjGvDkDWA2shvNk7MU6axDGfNsc73Ue6w0e57WO8R4BqcZ21eO6wWO5HTOOyzFcefxWHruVx20xXiuP1arHabeBAsZnFWOzgeOyyjFZeTwW47Btj8FK46+OY6+N+N0M4ngrxlqB0vhqSq40rtqOMVXVeKp6LNUyhsrx0+CxU8W4aQhjpk5jpDXmuGj4Y6JtjYfWgaTxT+XYpzzuuRvfN+yNjHFGPpFP5BP5RD6RT+Tz//f5tzz/F64pW64PAIT5/K8/w98o7f13jM/wF1OXi0A/1Pcu+DSOc0tnnr9wttgkwFtZgGDYhV5MV/TPu321n4itD8FU826ZB+cfJ4j5qEwuzdNMEjwp5lzoseL3Ocp5pcxPzCffg981kP0m6NJ5GOaT90MenMvsQ1k3g/S54EZ86TsU++FE28zX1PVKpl5GfGnIj2OUPyiO+AmuobgA1InxGbenQY4AG4qxELGLAddO0CbLUS8q+zE9/jifFx+R2pzTv02czxBzZAuFJFWmHb8vzs015ym3Iv0G7uNXG9/2XPg4rUvCT0UeWnFZEW1j2IEy0wYB+9T9lnP3HgbdDhu02Nig0qUNWpQ2qORcYfCe0M//COu4J3BNCFY5iGPd8XuGmKveT/y+RZ5LbNrpTHFuJn9HaTeJ3yliDnS90GyNd2VxhSGy4PMAuwu+u4Vvv5SKA5i3XUouo356Cp47hew/9tdPiciDsp8rzo8Ollvsw9baCTaFAT6AzrFdTjfjpH9Iv+5PnlrwrE0GT/fM2KhxsTE4ZLaDlngQ+T3kPwj+dTp/t+zYzt01M9+j5DPKbgbfep2vp+9uOUa7zBOPOn9fl69HEfNBOuYj+93lQX4nPzHGK/yu4kTbfjfR2FOuK/sttr0loDvgd00nrH63qvhyVz7nTxsl8ZYXVFYq1wuQV/ZPlCKtuzlm+BfOX+RvKYLB8L8PxPlzA9rpNk9o7TT2M2d7Jcp9GHWR225dD/aHncBL3AEbZn0WYEOxgWlh4dqKgsLLXfX/SO/Y/ycB8wTPeoVtmZ62/csQUZa3SrWXVxDvDiiBSLslld6Tax9WifM/jLpNe9Zs613+rh9LFv3EMfQT1wie56PipDViOnrY5ivE+T9HXaF9rv006qzAtQnU50XBc1XUuKgB1NEopy94jDVsphnN6+B3Rbpe/B2lvSB+x0jrF1Y=
*/