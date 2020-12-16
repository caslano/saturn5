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

#ifndef BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/pointer_traits.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type and
//!node_traits::node should be equal
template<class NodeTraits, link_mode_type LinkMode
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   = safe_link
   #endif
>
struct trivial_value_traits
{
   typedef NodeTraits                                          node_traits;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef typename node_traits::const_node_ptr                const_node_ptr;
   typedef typename node_traits::node                          value_type;
   typedef node_ptr                                            pointer;
   typedef const_node_ptr                                      const_pointer;
   static const link_mode_type link_mode = LinkMode;
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr       to_node_ptr (value_type &value)
      {  return pointer_traits<node_ptr>::pointer_to(value);  }
   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr (const value_type &value)
      {  return pointer_traits<const_node_ptr>::pointer_to(value);  }
   BOOST_INTRUSIVE_FORCEINLINE static const pointer  &      to_value_ptr(const node_ptr &n)        {  return n; }
   BOOST_INTRUSIVE_FORCEINLINE static const const_pointer  &to_value_ptr(const const_node_ptr &n)  {  return n; }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP

/* trivial_value_traits.hpp
3rwk7Y26b0l6ehmXXR7HX3faOuB5qZ6+MhafzZY3++mDqNP5ur+mpaPbWrrKaetbLB/daeuA57d6NVvXKF5b3uyTD4Gta1SYnU70u2erzPNknldibd26JTxT1v9cGbJRdfKjSc6VRXQ8uDpmDbfoWByroyyR5LLx/YFscJqSGSXP6SNxjNf1J8ywzlf4z1PXxvXN9wzYTzI+15a5wbHh/rTc+X2dCZaP9Ip8X8fercHeZ4Y1TYm/q1MZUybHB/CtHOKO+g7QQtHzsEHP8egZdOrJJCYfLWpo6JtHdJG+ntaTVzjTunUy93VnWsHGoPt8Qd5uj/cqXkt009Yt1Ya+R+Pvex+jfzsM+Wi3TdIkzE4zqh7sX+O0eaLlTxhs3tpc58peZOXeEnnHL9jSFM93iLH1mIsyM9mao7+7JunpZVt5pdPOOZb/oNsZvbWSvNeT2Na2QdR54jZ++6rLoOsydG036mpX+6Tr/c1rnelNtnwMU3rad8EmFSfMG+ST/y4YcRv7g7o3OHWdCW+XSVdVZd2VI/LaPkyJ62zXIOosejjq7Fvi1Nm1VzltnWL5Q0Zb1ffPXJVLzyvu5zd6Xkn++2eTivv//lnE1sAbnbaOQb5Xt7Vv26b6LTI3fShxuSKvrwNKXK7C27cfxQD63UOGciU9Y7keM9i6tJi/V4220he5s9XzavJ9EXEb21tbhVPXi9DVb9SVvkjWeZ6p8rqaLXnZ9TfevGKMvpe4yO980Zf40Vfij9F55Tqnzn7LlzPprPVnmYnbDfLJ92fEbezry6526noWvKVGXXE7BlAfiMP2Oy7J6d/vKH01eb8DXRx+B2lqfkd0GZW+ydzeA2a76cfd2Rx41X17D7yafD8+kPZetN5paxa2lhttVf24q/pY/qr7frz81eT78UwX/XjEn9xhsPUASlRG2Zq8rx5Jp+XNznTS8dWDUelE++kd/fitQa293OSivQQH0V46DH76TYb2MlfsrXiL097Po0goxl4aiitbQ1rdqe7H3wkNop10GHz0as3f0ct07YZwDEvEvgA0gzxpDdu4HQPlBeoN1axFVGPnM+LvyydyXo3POP8Bn2FNkTae/5i6Xhqzh5T7vR7PkD2NZG2DnG+M6iP81bLvppd6BI7wQpb/47Bd7f9XvSV63zh7fcz4P4fXJU8kBUOeEJ9x7aRt61glP96UT8i6X0sJb9+capqqX1tkjzV7Lc5UldbPmfuaYFyDLXEY10rve+31103riC22d6l4b1Zpz1VyKvvs9aSB18OyGeoak81cssI7ouJsIdK+tRp3qzjXcx7eC5LrFEffHgn71PU5nqnaHmHPq7BCTyZvr1lrGyqo3zVVsv9ZVug21nU59z4Tvt1VskeBN3SfL2OUL3NVnL3PhL9ko+x9Fvpq1nTZ/KyEzc/Gprjf++z7St9xxOuz150cUGGnewrMdgmfhMGVGdnvSPQq3xhZsx161LGeifaz1uv2u9vJ7QsY2d+cOkiYXgezqUPRa5vhVXVjrgqTOiO8HfBmqHBVX+xvN3cN4bebL6uzwq++5u4f+D/2hhdufmX9iVtPqfjmwL/pbP7m79B96/lHN1nhWz9wR2D/X8a+3fPoa5/4+KY33vW/+63nS8dY4d94uuLopxsmvvj6B9rKnp36+ZdYWzbWCm//1bopd1c+NOrWrCe9+a8+8Nh/z7ehE30DulLapbVXWStYBR3Vjpfn9R3/XY5/Cb2uHd+rHVt9QCW4EDquHb+m8XjHhcMXQKna8VjtOEs7ztCOX9Hi9I/rOx6jHY/QjkdpxyM57gXzoUw5Ph3yyfESKEWO3wjRz6rjt0FpEt5Afv1VwndxfFKO7+b4ZTl+2so=
*/