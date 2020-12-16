/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_SLIST_NODE_HPP
#define BOOST_INTRUSIVE_SLIST_NODE_HPP

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
struct slist_node
{
   typedef typename pointer_rebind<VoidPointer, slist_node>::type   node_ptr;
   node_ptr next_;
};

// slist_node_traits can be used with circular_slist_algorithms and supplies
// a slist_node holding the pointers needed for a singly-linked list
// it is used by slist_base_hook and slist_member_hook
template<class VoidPointer>
struct slist_node_traits
{
   typedef slist_node<VoidPointer>  node;
   typedef typename node::node_ptr  node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node>::type    const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const const_node_ptr & n)
   {  return n->next_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const node_ptr & n)
   {  return n->next_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->next_ = next;  }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SLIST_NODE_HPP

/* slist_node.hpp
h1fDn8Nq+Dt4A2wbxC6wA9wNTX3x5vfBix31ZZ2uj/Vqfy+H2drO1fZiuEH3yY3Wc0Gd0p3peC4YqnSHwTZwOEyD58LucBTsCSfAXnCs7l/j1A6eB2eY49a6CpqfdL/juYA2ytT3xUp3idJbqvbnYjhN2zO1fSNcBm+Gq+Et8BL4UbgC3gVXwXt1/A1Y4803gv113jMJ90iPX6TQnMGTsCd8HQ6Ev4Xj4O/hBbAOlsFT8DL4JtwB34I3wL/Cu+Hf4CMwwPl8GgThS7AV/AlM0/lvA0/BtvAvsB3sFOS46sFub44MfEj260jYKb2fJZ8W8DswtP+70v8FOAn+EC6AJ+BS+CJ8j/ZfD1+BN8NX4fthLbwN/hTeB38GH9TxN+AAf96Faa/N+1AK7OGtf6L25hT01qXYq/gtdX+y16XgvcePdyDBeDUJxjucYLzjCcarjRPvCau8dQnGC/T34/EuZscz73R+vPQE4+XFiTfcyrcgwXiFCcYrTjDeygTjVVrxCiLs92mrvNVWvKNR651Y9S/BeAfixFtlxatJMN7hBOINMOOcYl9POdQ/ux7OJNQq/hjHc1ONniMehub5Ve+1j8Kh8DE4Gn7RXy9O43xgN5OevV4c27qe74Pt4f0wA34WdoUPQKMXCRQrnWfUvva3vrV8Sfocgp3h0zAHHoF94TNwOPwGHKntMdp+Dzyq56/fwPfBb8Eb4DG4B34b3gG/o+eJ5+CT8Dh8Dr6k54iX4Z/gT+Bb2v6rtrsEsS3sCr8Pz4LPw4Hwh3CItgu0PR2egDPhz+Ac+CpcBl+D6+Ev4AZtV2j7YfhL+Aj8DfwS/DV8WttvmOc2jSPQGIeDqlNpsmcHtffpMAdmwjyYDfNVX0bBrnAm7A6Xw7PgFpgH74T94e/gQBhKezDsB4fCibAAlsARsByOhlfC8fCD8Hy4D06En4KF8H44GX4ZToVPw2nwOTgHvgDnwdfhfNiJ8pXAbFgKu8OFsC9cBAvgEjgaLtV1cNTrd4Zpqm85hEOqt7/XdVAHW8E/qP6eUr39k+rZm3AsbKP7/FtsXwDfhvPhO7AC/k317+96fm1N/I9Kbh8Mwv0wRff9FvBp2BIe0fY3tM27uJFvD5Fv+B6kfr6pjvfS5cRLgZdAM6YddoCrdb7XwHPgZXAC3AinwE1Kf2/Q68szcU36wwjXqT5tVno74RB4lerN++BcuAsugdfAKngt3A6v13PDjXruuRneD98PPw/3wEPwA/A4vAX+CN4Ka7W/Dn5YdvkIzISfgH3hU3AGfBrOhV+Fi+DX4Ap4RPXyGbgW3gGvgB+H1yqdW+Gd8DZ4F7wT3g0fhffAr8FPq37eC5+H98Gfw8/CN+EDMCXUHwJbw4eg+d4L+8CH4QD4BdXTR+AM+EW4CD4Ol8An4MXwS1DPd+oz4lw5nu86tSBf2BmmwizYCebA7jAXDoJd4WjYHU6GvWApzIdL4dnwItgXroT94HrYH27U8ceTWB+seW2w/9zaYI9sS/2/Xx9syw2pTV4jbG9F6v/MOmG7b0ht8lphB5CthqzVl/CaYY/ckPquWjfsGOWtI/S4ETsQygh7CA8Qnie8Q+ixm/XCCOsIBwjHCG8R8m5KDcwhbCfcQzhOCNyMHQjFhOsI9xAOE14mBN7PMUIhYR1hD+ERwgnCO6Fje5AjbCfsJxwi1BLeIfT4QGpgAmEl4TrCA4SjhJOE1FtYh4wwgbCMUE04SDhGeIuQdWvzemPNf81/zX/Nf/9Pf/+29f/MJKbQAoCnv/7fjpyAv2bY8WDDmiIphKWE1SE/F+m87zT4CTW5y82oN76T4+ywxma+aWQW8J0rxe33Il1zG+UrFr+i/pg7PO0=
*/