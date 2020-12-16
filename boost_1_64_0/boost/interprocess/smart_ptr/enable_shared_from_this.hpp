//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/enable_shared_from_this.hpp
//
// (C) Copyright Peter Dimov 2002
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED
#define BOOST_INTERPROCESS_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/assert.hpp>
#include <boost/interprocess/smart_ptr/weak_ptr.hpp>
#include <boost/interprocess/smart_ptr/shared_ptr.hpp>

//!\file
//!Describes an utility to form a shared pointer from this

namespace boost{
namespace interprocess{

//!This class is used as a base class that allows a shared_ptr to the current
//!object to be obtained from within a member function.
//!enable_shared_from_this defines two member functions called shared_from_this
//!that return a shared_ptr<T> and shared_ptr<T const>, depending on constness, to this.
template<class T, class A, class D>
class enable_shared_from_this
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   protected:
   enable_shared_from_this()
   {}

   enable_shared_from_this(enable_shared_from_this const &)
   {}

   enable_shared_from_this & operator=(enable_shared_from_this const &)
   {  return *this;  }

   ~enable_shared_from_this()
   {}
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   shared_ptr<T, A, D> shared_from_this()
   {
      shared_ptr<T, A, D> p(_internal_weak_this);
      BOOST_ASSERT(ipcdetail::to_raw_pointer(p.get()) == this);
      return p;
   }

   shared_ptr<T const, A, D> shared_from_this() const
   {
      shared_ptr<T const, A, D> p(_internal_weak_this);
      BOOST_ASSERT(ipcdetail::to_raw_pointer(p.get()) == this);
      return p;
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef T element_type;
   mutable weak_ptr<element_type, A, D> _internal_weak_this;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_ENABLE_SHARED_FROM_THIS_HPP_INCLUDED


/* enable_shared_from_this.hpp
L4o6iEzcRG2rNRqYk9lOY7/HpV+m22+t9Gvj9lsl/Vq7/UqkX4bbb5np16ajptJDs653toxTrM3mPUI9xjgW1Qa/Ne4RTmOqgK6phbW9zhWwvC7l1HMFkAts7NidZ8Ql5wrM44mWsb1Rve1zn7dBLsMoAyuzG8/rGvJ5JOdzSK6/+pvEyK/Ut0xwO/9zVVQG+Tz6TfYQVO8V6G1vwd/fHoJ9MoT/xeEDClp89sZT+YcXtlw8bfDA0B6Cv9c9BIVdq0Y4hz/SSY7Rad6BnhmlYB3E96TH743yN40NFotxULiBHr+f4N9lcBvkb6ydMeK/Raz54N+zhZ4sy7yE4+Uev+/y+H23x+8VHr+Xefwu4TgLxZgA/w6De5B/R8H9jX83hnucf2fCreXfLVGuNfx7SBjKw7+dYdL+Fu1ZxOu6Y6x2ZJAG2zWC5yaWOy9MyIH4PYzruoT3V3wITGA7Vyl8nMbH9fh4CLgWHCnqF7yC7V0tBffyvof7wLvZ/tX94OPgA2wH623wSXA/uBH8XLQv+Cv4NJjE9q9asf2rLPB5sDf4EpgLvizSB0vBceA/2D7Wdt7f8DXwZvB1cC24A3wEfBPcDP4TfA4sA0Vb7QK360a+d7C9rUPgbvAo+Db4I/gO6Agz7DCdA4ryNgYRjuq5g8b7o4D1uT0iwBbcHp9CTvAo28n5jO07fe5hf2o1h29L4a32p2Zx+NkgvZuDNcC53H5zuP2uBNPZ/1y205XJx+59Oo9zOjGKfTr/zel8C0aDJzzCaZ94D/c9hzvJ4X7gcE64BA7Xj8PFgQUcbjGX4xYwle23/UVcl1w/t4HnsT23Fh723O4Au4DFbG9rGZhN52V9OjndVYr6vJbtJ13P9spuAMewHbOb2b8YnA/eBS4E7wEXcL9eKO2u0T4K8jq02l2b5mF3TaQ/ne01zQRrsf21s+hY1rOT44tW1POXHN9XoEjnaxkOHdd7+5zicD9z+/ziYeetmMNdSeGsdt4mcP+aCPYCJ4P9wcvY7tgU3mc1n+02FYCzhD/HX2quC8ezkeNPATdz/I5ww95ZTTAWrAXSWk0wHkwCM8DaYHv27wCmgiPANPBS9h8H1gUng43BOWAT8AawKbiQ/ZeDF4ArOFwJ2Ay8D2wBPg22BF+g80Y5cs11z7jWuRzRYC8uB+4JVI50ULTvueBfwAbgOWBDsKXID9he5AcU8a6Dc3K8d3C8SWR3kJ+FYUY//R5sLq4rsDUYi3y1AX8MM+rjJ7CraF9wgGhfcDj4KzgaDIf8RDACnAFGgnM4HtHuUeCNYDR4M/vfAsaAt/Mx75fL62ipL9r2y83h/jKYnx9DwIbgUJCeO2B73uc2CxzF/Woc7987GryG1mIY7TYWXMD73y6uZBdsOYcrYf/72f9BPn6cj9fz8VN8vJXDlbL/2+z/Mfv/i/fd/cw45vs7r9ME2ynu7wO5H+eALcFBYFsw16P/bOLwXRT9pyeHz+bwvcFMsA/3+37c7/uCnY1jzhevOwTaKPKVyfG243gvBFuD7WW+eF2fOl+dOHxnDt+F89WV85XF+epm5AvH8r5YLOO13ReHcrwjOL5RHN9ojm8kxzfaI74Kji9LEd9Yji8PvBCcAHYCJ4IXibYDuxnHfL/kNWSgQ3G/TMF1I5gKxtF7pgyX5SNcXQ53FoerFybzn8vh+iryH6sbz8HG4DlgU7Ah2BJsDDYHe9OxEV+Juc4IfZXjSwCXcnw/QE7wJzAF/BmsC/4CirwmhRnxRoKZYBTYkf07gTX4fhIH9mL/bDAezAVrgiPYfySYAI7hY37+8vof9DXF8/chrqc1YDT4MHg2+ARYH3wcbAWuBzPYvzW4AbyQj9k=
*/