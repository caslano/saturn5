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

#ifndef BOOST_INTRUSIVE_LIST_NODE_HPP
#define BOOST_INTRUSIVE_LIST_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
namespace intrusive {

// list_node_traits can be used with circular_list_algorithms and supplies
// a list_node holding the pointers needed for a double-linked list
// it is used by list_derived_node and list_member_node

template<class VoidPointer>
struct list_node
{
   typedef typename pointer_rebind<VoidPointer, list_node>::type  node_ptr;
   node_ptr next_;
   node_ptr prev_;
};

template<class VoidPointer>
struct list_node_traits
{
   typedef list_node<VoidPointer>      node;
   typedef typename node::node_ptr     node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node>::type   const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous(const const_node_ptr & n)
   {  return n->prev_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous(const node_ptr & n)
   {  return n->prev_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_previous(node_ptr n, node_ptr prev)
   {  n->prev_ = prev;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const const_node_ptr & n)
   {  return n->next_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const node_ptr & n)
   {  return n->next_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->next_ = next;  }
};

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_LIST_NODE_HPP

/* list_node.hpp
yhZg16403lkjI3PdouA/0FlrnitOEqavURv+PP1G5D9jrYiP9R1R7rabQ+p6cdn3VEcy3C7H/+l5k38PuduiQUfI/di53/1djj1Je70DnYThe1nCrvFEU+KzPGcE3ne133vJkiHXr9Ja93nayvnxxdJu4/T8JAwIOT+2TBEy74pM9Q3mGmpTZpWjZ3lYPRuR2SsyC417bqDMLmTes2TaVv/Olnnftb0g42Lvs+Ac297nAPHf5fgbbE/adjhXeg96J8e5B4m/G3pM/1X4Xe5RTkdSGY0cLIf/RCbxXKOtifFnfztbmOi3uSJ5kb5fZdHwlLeV2bYID+4DsGhg2PupkuODvaus60/P+zW5VlgVaz5Hiv6YMPrrw73a/vXaV/1J8DY5/v2orsyKtu9FvWdZYaOca2TzTMt/uhcbyawhnaz9E5a/RC5O5bC7JnKPegtZMTXbO87Km+yB3kPSuCD6HvJm3nuTVP8lUp670dxb7522btJy5HVPfM3jFRLnDuZSdkKGMCeOz4hTUFSk12kq/LnkbwfPCfHMDWzlte+l6RJvguT3EPl9RuR+zfFWhi4xSuL0iXtFJlHiHCBOPynjudG3B5SxxHk2+Ijj6OSYfX+/0DkHl0lZbmCeaBfjeLnTP5wvxx/3VHBc0nfy3FLyJ4XzYBrF6JOGSHpbo0bRdm7yxnsl3DlHm7yPee5yztF+8j9c5CdGr5X249gkvvDCCmkujg3jZyV+njfBs4z3rZPQnqj9ka37Ee9iz+us3YqV557D6JZwZn9r/ymzLT3Gs81FufazFn5Hz21eHyslrT6knA4+uS3zs/2231YE29NJVZkRbbVPa/39JxKi24Xa0lG5/Lb6LBJzZZfgZ5Gz8HPYs7E99zncbYn17kPifIS7zXjmeAgZaPrlOeSERmwYc/5C+jD6DbGnE3JPlD5B+6SgfdUHoSQV9odRGYTPNvsksWlu9ElsEehuj0LjeYPvk841eo8c/4i5xOtd729m/CTT9pJeU1fJ8RO9cc7xRc5zzmOz9VlW+5Vt4n+Fx7FnnTb0Mwn7xFMfv8S5Ph6XY2/wLF7jXB9rzrPCYiT+QeJvFZn3jPgXSXyrGnfLsSt5DkxwrteZEr+7+m19XiN+qfP+8YrEH2Je207Zukm83k7Z0sV/FnXe27zWnXTT5PiZRj0ukvZg982PSFpvG8cry+z+PBVeJsfbeWcxK1v7N817O/z+vupakTnOG9R3OPeXG+R4a+9IymTF+Yo4N0tYm7DX8B/leGia1rXpo+3tSdJ3j4T+CdFEcHmHF7nDyO0TuZyQ5/9U/D69Nq1r8YV29ddbciPX29rzwl1vXBPG9WY+R5i2fnKTQ+3AfIDsQdFbXTo/b2r2mCkzZkyyjcEU8Y2tsth5pvbqM7Wr3W+jbe0Q2SKXa8yQc56hIrcD84qUS5/rtaw7/GUNtJ+XElrOj5HzzHEvp76aR1ROdATk/60jzL+Z34Mu+X0L2cQw+dVXgojyiw7zmd39vBhyzvPvEZarjfncquflLNsGV6p7+0sPV06638UlxUsjPTfpcyJrgypX/z5wlGV1a4M7O4SW9VPkMueozSWnrNl2IyxZpM/euxqxu4QO810uvI0pQ9b5XtcEm1q7Qu0u6XklvWA7Ymmh5f2S+Fnu5dWLLrLyZgWV4VATbEeZZTDb4kGX/H6DbLZrfk2rcE23CWfXUc1xoWnWkWZ++DR5ZtJvWw3XETqO3DYcul1tw63t6N6Gy93zq5bSIjun5U1ow+VzjtxOWlPacPXxoeV9rwvhYcsr33QiOj/VcyK3lVY958htpe1rgq00d9th4W1sudvwCm+rK+FGK3z56pnldw/aV/LIY/s=
*/