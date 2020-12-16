//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/scoped_ptr.hpp
//
// (C) Copyright Greg Colvin and Beman Dawes 1998, 1999.
// (C) Copyright Peter Dimov 2001, 2002
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SCOPED_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_SCOPED_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/pointer_type.hpp>
#include <boost/interprocess/detail/utilities.hpp>
#include <boost/assert.hpp>
#include <boost/move/adl_move_swap.hpp>

//!\file
//!Describes the smart pointer scoped_ptr

namespace boost {
namespace interprocess {

//!scoped_ptr stores a pointer to a dynamically allocated object.
//!The object pointed to is guaranteed to be deleted, either on destruction
//!of the scoped_ptr, or via an explicit reset. The user can avoid this
//!deletion using release().
//!scoped_ptr is parameterized on T (the type of the object pointed to) and
//!Deleter (the functor to be executed to delete the internal pointer).
//!The internal pointer will be of the same pointer type as typename
//!Deleter::pointer type (that is, if typename Deleter::pointer is
//!offset_ptr<void>, the internal pointer will be offset_ptr<T>).
template<class T, class Deleter>
class scoped_ptr
   : private Deleter
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   scoped_ptr(scoped_ptr const &);
   scoped_ptr & operator=(scoped_ptr const &);

   typedef scoped_ptr<T, Deleter> this_type;
   typedef typename ipcdetail::add_reference<T>::type reference;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:

   typedef T element_type;
   typedef Deleter deleter_type;
   typedef typename ipcdetail::pointer_type<T, Deleter>::type pointer;

   //!Constructs a scoped_ptr, storing a copy of p(which can be 0) and d.
   //!Does not throw.
   explicit scoped_ptr(const pointer &p = 0, const Deleter &d = Deleter())
      : Deleter(d), m_ptr(p) // throws if pointer/Deleter copy ctor throws
   {}

   //!If the stored pointer is not 0, destroys the object pointed to by the stored pointer.
   //!calling the operator() of the stored deleter. Never throws
   ~scoped_ptr()
   {
      if(m_ptr){
         Deleter &del = static_cast<Deleter&>(*this);
         del(m_ptr);
      }
   }

   //!Deletes the object pointed to by the stored pointer and then
   //!stores a copy of p. Never throws
   void reset(const pointer &p = 0) // never throws
   {  BOOST_ASSERT(p == 0 || p != m_ptr); this_type(p).swap(*this);  }

   //!Deletes the object pointed to by the stored pointer and then
   //!stores a copy of p and a copy of d.
   void reset(const pointer &p, const Deleter &d) // never throws
   {  BOOST_ASSERT(p == 0 || p != m_ptr); this_type(p, d).swap(*this);  }

   //!Assigns internal pointer as 0 and returns previous pointer. This will
   //!avoid deletion on destructor
   pointer release()
   {  pointer tmp(m_ptr);  m_ptr = 0;  return tmp; }

   //!Returns a reference to the object pointed to by the stored pointer.
   //!Never throws.
   reference operator*() const
   {  BOOST_ASSERT(m_ptr != 0);  return *m_ptr; }

   //!Returns the internal stored pointer.
   //!Never throws.
   pointer &operator->()
   {  BOOST_ASSERT(m_ptr != 0);  return m_ptr;  }

   //!Returns the internal stored pointer.
   //!Never throws.
   const pointer &operator->() const
   {  BOOST_ASSERT(m_ptr != 0);  return m_ptr;  }

   //!Returns the stored pointer.
   //!Never throws.
   pointer & get()
   {  return m_ptr;  }

   //!Returns the stored pointer.
   //!Never throws.
   const pointer & get() const
   {  return m_ptr;  }

   typedef pointer this_type::*unspecified_bool_type;

   //!Conversion to bool
   //!Never throws
   operator unspecified_bool_type() const
   {  return m_ptr == 0? 0: &this_type::m_ptr;  }

   //!Returns true if the stored pointer is 0.
   //!Never throws.
   bool operator! () const // never throws
   {  return m_ptr == 0;   }

   //!Exchanges the internal pointer and deleter with other scoped_ptr
   //!Never throws.
   void swap(scoped_ptr & b) // never throws
   {
      ::boost::adl_move_swap(static_cast<Deleter&>(*this), static_cast<Deleter&>(b));
      ::boost::adl_move_swap(m_ptr, b.m_ptr);
   }

   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   private:
   pointer m_ptr;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED
};

//!Exchanges the internal pointer and deleter with other scoped_ptr
//!Never throws.
template<class T, class D> inline
void swap(scoped_ptr<T, D> & a, scoped_ptr<T, D> & b)
{  a.swap(b); }

//!Returns a copy of the stored pointer
//!Never throws
template<class T, class D> inline
typename scoped_ptr<T, D>::pointer to_raw_pointer(scoped_ptr<T, D> const & p)
{  return p.get();   }

} // namespace interprocess

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

#if defined(_MSC_VER) && (_MSC_VER < 1400)
template<class T, class D> inline
T *to_raw_pointer(boost::interprocess::scoped_ptr<T, D> const & p)
{  return p.get();   }
#endif

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif // #ifndef BOOST_INTERPROCESS_SCOPED_PTR_HPP_INCLUDED

/* scoped_ptr.hpp
Xa7xrkOydUkmPIJl8qQ9ehHsCpKpg5zEm22yhPz2Qecu2lzj35HjYrv2+HOvm+1BuvkJdH6ELnT0t+Bso3DMdSEBR9z8xpXXA7TCcQ0xJ4TjrXAvwr0E9zLcDXDPoHFKwZXgZNafj/Fjdy1lr93umuibKUbf5DUvco9R9qM+1MC0u2asfUowdd65/7BO9klp2532FZ9AZcbYJu8zPp+Py/j4Hj7eycdv8fFbfBxj5Fnbxcdd9lrjG8nH5XUq2W+LYt0NONpzQPS/OpDbq7xO8yY7NWq3CmMNmbc9ThBeea0qrkurbJHv6xKywV2XnvLTqbEnTp2ZR3vWm330Q5I5H3lR22GoA/5MMnGmDv4qxPUPsX4jwb+dBXcfEnWWQnXmuw8VBdCHLPaPOMEaPC8bK3RYxbrtfZXbENeZuOFDxnq/leVsT2GOq9qU49PN+5YurlsOWxtsTOcjdFsbc1h1uynbWaZlyk8XSZl7obSh898p2twatmGy+/4q71Ov0fmz8HSLVO5LcS2dX2/Y+cP1sTYa8+9k0+osm00rt8wOU6azTaY+y5xyy+ijyFaMqwTGYpTrpWS86ai8BmQvxvVA5fVSTXCM03SPeyXRIP/mYzCAPUR83eNEO6dwO6da+qdsvyRLH6V2su5bHmck1pL7Zwv8t1esG97v2T/l6j/jVuPZRyca1wz30WUULlr/WW1/j+K12nstmornJo55jxg6n664F1nDzk/l+9Zs+bydY4TVk8X+itqjqr6LOJTvGfa+yrLq60Len1YYMvr3WozKvi3iUNrAI7ln6VwFdNBjPc5fbtZF1HvivMO+zpHL+w6FfwMlrUcybUmGXhjNOH4w2oOul+2oxD14IG8jO4W6/VpgmZg4ltF7iWshwvWyIzbS27XAYVogzHa6Fkba9mphe618DRjr5l6FW8fXwT+YL4Dz4V4L+rqYaLlvJ5If9Svzvi36Swr1F74mFO8DtZX3crkWusRhXx88FPEef8+9PrjnoJzeeSO6Dxye7bkHx2Dfe6wgfNXXqyNu5Xr14nh7XmdDVjugyKvcEoafHz7zizjkdbEq2f96de1A1derIy+29epI0+t69etq2ss9HOVOUJWbXm0Da6OEA4Gv3044UPX124NTA1+/3aKWvaz7xbvFAct6dbxcZOcM7Tcox7NPzvddXsRR9T4530ufrJdgz+8B5DfDW36pfQLLb0YQ7ZNRjfaZH0D7dHK3D9sAfECTtld3oLxZRnnnzJg2Y+ZVM8TD1f1U1QL61s6SZcX3pO/3d5aVzzD5nap6PkI+8Ocjyaqfj/ZnoUpe2nVQ2ntned4LVj4/Xk9EPQaxh6Lq3Ym+77jeLO9OZv0E95wQ/mluf1mu0JpexZreEW1oLe6xuWf/W//sqafav/hIfPsP15y+Nb3qtbve1vqG1vQGsqaXt0ahb6S54DlwDTx+ny9/07vjOnAo3Hb5m9a7puk8HsfjjzFw6eLeA4q/PryubjDYlNcdtRTheb3RcF5fNAKcDC4BL+d1SFfwOqRF4BiP9UQreV3QajAPfBQcD/4dnAS+w+sxD4BFvF5oDvgFr8P8ktddRiOP14j8gdeC54LXg43B+WAGeCPYE1wAivZdCI4GF4N5upHffHARWMj+swx/XsfD4yJgJ8U6nh2sT1bG6yx38/qst8Dm4C6wnYgD7Mjnef0ef3vTWIRt/V5djvdsMF60I9hMhAE7i3YH+4k2B0eBjUAn2BgsApuAt4FNwTvBZrxe+DzwMbA5uAk8H3wJbAG+CrYEd4MZvG6rK6/b6gZ+y+mIMZPuXI5y85sKYbkcdUQ/43LcxuUoBpPAO7l+1nusR20ILud1a3fxurUSXg8=
*/