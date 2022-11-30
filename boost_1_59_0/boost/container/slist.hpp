//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2004-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_SLIST_HPP
#define BOOST_CONTAINER_SLIST_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

// container
#include <boost/container/container_fwd.hpp>
#include <boost/container/new_allocator.hpp> //new_allocator
#include <boost/container/throw_exception.hpp>
// container/detail
#include <boost/container/detail/algorithm.hpp> //algo_equal(), algo_lexicographical_compare
#include <boost/container/detail/compare_functors.hpp>
#include <boost/container/detail/iterator.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/node_alloc_holder.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/value_functors.hpp>
// intrusive
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/slist.hpp>
// move
#include <boost/move/iterator.hpp>
#include <boost/move/traits.hpp>
#include <boost/move/utility_core.hpp>
// move/detail
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
#include <boost/move/detail/move_helpers.hpp>
#include <boost/move/detail/force_ptr.hpp>
// other
#include <boost/core/no_exceptions_support.hpp>
// std
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

template <class T, class Allocator>
class slist;

namespace dtl {

template<class VoidPointer>
struct slist_hook
{
   typedef typename dtl::bi::make_slist_base_hook
      <dtl::bi::void_pointer<VoidPointer>, dtl::bi::link_mode<dtl::bi::normal_link> >::type type;
};

template <class T, class VoidPointer>
struct iiterator_node_value_type< base_node<T, slist_hook<VoidPointer> > >
{
  typedef T type;
};

template<class Allocator>
struct intrusive_slist_type
{
   typedef boost::container::allocator_traits<Allocator>      allocator_traits_type;
   typedef typename allocator_traits_type::value_type value_type;
   typedef typename boost::intrusive::pointer_traits
      <typename allocator_traits_type::pointer>::template
         rebind_pointer<void>::type
            void_pointer;
   typedef base_node<value_type, slist_hook<void_pointer> > node_type;

   typedef typename dtl::bi::make_slist
      <node_type
      ,dtl::bi::base_hook<typename slist_hook<void_pointer>::type>
      ,dtl::bi::constant_time_size<true>
      , dtl::bi::size_type
         <typename allocator_traits_type::size_type>
      >::type                                   container_type;
   typedef container_type                       type ;
};

}  //namespace dtl {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! An slist is a singly linked list: a list where each element is linked to the next
//! element, but not to the previous element. That is, it is a Sequence that
//! supports forward but not backward traversal, and (amortized) constant time
//! insertion and removal of elements. Slists, like lists, have the important
//! property that insertion and splicing do not invalidate iterators to list elements,
//! and that even removal invalidates only the iterators that point to the elements
//! that are removed. The ordering of iterators may be changed (that is,
//! slist<T>::iterator might have a different predecessor or successor after a list
//! operation than it did before), but the iterators themselves will not be invalidated
//! or made to point to different elements unless that invalidation or mutation is explicit.
//!
//! The main difference between slist and list is that list's iterators are bidirectional
//! iterators, while slist's iterators are forward iterators. This means that slist is
//! less versatile than list; frequently, however, bidirectional iterators are
//! unnecessary. You should usually use slist unless you actually need the extra
//! functionality of list, because singly linked lists are smaller and faster than double
//! linked lists.
//!
//! Important performance note: like every other Sequence, slist defines the member
//! functions insert and erase. Using these member functions carelessly, however, can
//! result in disastrously slow programs. The problem is that insert's first argument is
//! an iterator p, and that it inserts the new element(s) before p. This means that
//! insert must find the iterator just before p; this is a constant-time operation
//! for list, since list has bidirectional iterators, but for slist it must find that
//! iterator by traversing the list from the beginning up to p. In other words:
//! insert and erase are slow operations anywhere but near the beginning of the slist.
//!
//! Slist provides the member functions insert_after and erase_after, which are constant
//! time operations: you should always use insert_after and erase_after whenever
//! possible. If you find that insert_after and erase_after aren't adequate for your
//! needs, and that you often need to use insert and erase in the middle of the list,
//! then you should probably use list instead of slist.
//!
//! \tparam T The type of object that is stored in the list
//! \tparam Allocator The allocator used for all internal memory management, use void
//!   for the default allocator
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template <class T, class Allocator = void >
#else
template <class T, class Allocator>
#endif
class slist
   : protected dtl::node_alloc_holder
      < typename real_allocator<T, Allocator>::type
      , typename dtl::intrusive_slist_type<typename real_allocator<T, Allocator>::type>::type>
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef typename real_allocator<T, Allocator>::type      ValueAllocator;
   typedef typename
      dtl::intrusive_slist_type<ValueAllocator>::type       Icont;
   typedef dtl::node_alloc_holder<ValueAllocator, Icont>    AllocHolder;
   typedef typename AllocHolder::NodePtr                    NodePtr;
   typedef typename AllocHolder::NodeAlloc                  NodeAlloc;
   typedef typename AllocHolder::ValAlloc                   ValAlloc;
   typedef typename AllocHolder::Node                       Node;
   typedef dtl::allocator_node_destroyer<NodeAlloc> Destroyer;
   typedef typename AllocHolder::alloc_version              alloc_version;
   typedef boost::container::
      allocator_traits<ValueAllocator>                           allocator_traits_type;
   typedef boost::container::equal_to_value
      <typename allocator_traits_type::value_type>          equal_to_value_type;

   BOOST_COPYABLE_AND_MOVABLE(slist)
   typedef dtl::iterator_from_iiterator<typename Icont::iterator, false>  iterator_impl;
   typedef dtl::iterator_from_iiterator<typename Icont::iterator, true >  const_iterator_impl;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////

   typedef T                                                                  value_type;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::pointer          pointer;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::const_pointer    const_pointer;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::reference        reference;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::const_reference  const_reference;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::size_type        size_type;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::difference_type  difference_type;
   typedef ValueAllocator                                                                  allocator_type;
   typedef BOOST_CONTAINER_IMPDEF(NodeAlloc)                                  stored_allocator_type;
   typedef BOOST_CONTAINER_IMPDEF(iterator_impl)                              iterator;
   typedef BOOST_CONTAINER_IMPDEF(const_iterator_impl)                        const_iterator;

   public:

   //////////////////////////////////////////////
   //
   //          constructFr/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Constructs a list taking the allocator as parameter.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   slist() BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<ValueAllocator>::value)
      :  AllocHolder()
   {}

   //! <b>Effects</b>: Constructs a list taking the allocator as parameter.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   explicit slist(const allocator_type& a) BOOST_NOEXCEPT_OR_NOTHROW
      :  AllocHolder(a)
   {}

   //! <b>Effects</b>: Constructs a list
   //!   and inserts n value-initialized value_types.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   explicit slist(size_type n)
      :  AllocHolder(allocator_type())
   { this->resize(n); }

   //! <b>Effects</b>: Constructs a list that will use a copy of allocator a
   //!   and inserts n copies of value.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   slist(size_type n, const allocator_type &a)
      : AllocHolder(a)
   {  this->resize(n);  }

   //! <b>Effects</b>: Constructs a list that will use a copy of allocator a
   //!   and inserts n copies of value.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   explicit slist(size_type n, const value_type& x, const allocator_type& a = allocator_type())
      :  AllocHolder(a)
   { this->insert_after(this->cbefore_begin(), n, x); }

   //! <b>Effects</b>: Constructs a list that will use a copy of allocator a
   //!   and inserts a copy of the range [first, last) in the list.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's constructor taking a dereferenced InIt throws.
   //!
   //! <b>Complexity</b>: Linear to the range [first, last).
   template <class InpIt>
   slist(InpIt first, InpIt last, const allocator_type& a =  allocator_type())
      : AllocHolder(a)
   { this->insert_after(this->cbefore_begin(), first, last); }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs a list that will use a copy of allocator a
   //!   and inserts a copy of the range [il.begin(), il.end()) in the list.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's constructor taking a dereferenced std::initializer_list iterator throws.
   //!
   //! <b>Complexity</b>: Linear to the range [il.begin(), il.end()).
   slist(std::initializer_list<value_type> il, const allocator_type& a = allocator_type())
      : AllocHolder(a)
   { this->insert_after(this->cbefore_begin(), il.begin(), il.end()); }
#endif

    //! <b>Effects</b>: Copy constructs a list.
   //!
   //! <b>Postcondition</b>: x == *this.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!
   //! <b>Complexity</b>: Linear to the elements x contains.
   slist(const slist& x)
      : AllocHolder(x)
   { this->insert_after(this->cbefore_begin(), x.begin(), x.end()); }

   //! <b>Effects</b>: Move constructor. Moves x's resources to *this.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   slist(BOOST_RV_REF(slist) x) BOOST_NOEXCEPT_OR_NOTHROW
      : AllocHolder(BOOST_MOVE_BASE(AllocHolder, x))
   {}

   //! <b>Effects</b>: Copy constructs a list using the specified allocator.
   //!
   //! <b>Postcondition</b>: x == *this.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!
   //! <b>Complexity</b>: Linear to the elements x contains.
   slist(const slist& x, const allocator_type &a)
      : AllocHolder(a)
   { this->insert_after(this->cbefore_begin(), x.begin(), x.end()); }

   //! <b>Effects</b>: Move constructor using the specified allocator.
   //!                 Moves x's resources to *this.
   //!
   //! <b>Throws</b>: If allocation or value_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise.
   slist(BOOST_RV_REF(slist) x, const allocator_type &a)
      : AllocHolder(a)
   {
      slist & sr = x;
      if(this->node_alloc() == sr.node_alloc()){
         this->icont().swap(sr.icont());
      }
      else{
         this->insert_after(this->cbefore_begin(), boost::make_move_iterator(sr.begin()), boost::make_move_iterator(sr.end()));
      }
   }

   //! <b>Effects</b>: Destroys the list. All stored values are destroyed
   //!   and used memory is deallocated.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements.
   ~slist() BOOST_NOEXCEPT_OR_NOTHROW
   {} //AllocHolder clears the slist

   //! <b>Effects</b>: Makes *this contain the same elements as x.
   //!
   //! <b>Postcondition</b>: this->size() == x.size(). *this contains a copy
   //! of each of x's elements.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in x.
   slist& operator= (BOOST_COPY_ASSIGN_REF(slist) x)
   {
      if (BOOST_LIKELY(this != &x)) {
         NodeAlloc &this_alloc     = this->node_alloc();
         const NodeAlloc &x_alloc  = x.node_alloc();
         dtl::bool_<allocator_traits_type::
            propagate_on_container_copy_assignment::value> flag;
         if(flag && this_alloc != x_alloc){
            this->clear();
         }
         this->AllocHolder::copy_assign_alloc(x);
         this->assign(x.begin(), x.end());
      }
      return *this;
   }

   //! <b>Effects</b>: Makes *this contain the same elements as x.
   //!
   //! <b>Postcondition</b>: this->size() == x.size(). *this contains a copy
   //! of each of x's elements.
   //!
   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or value_type's move constructor throws)
   //!
   //! <b>Complexity</b>: Constant if allocator_traits_type::
   //!   propagate_on_container_move_assignment is true or
   //!   this->get>allocator() == x.get_allocator(). Linear otherwise.
   slist& operator=(BOOST_RV_REF(slist) x)
      BOOST_NOEXCEPT_IF(allocator_traits_type::propagate_on_container_move_assignment::value
                                  || allocator_traits_type::is_always_equal::value)
   {
      slist & sr = x;
      if (BOOST_LIKELY(this != &sr)) {
         NodeAlloc &this_alloc = this->node_alloc();
         NodeAlloc &x_alloc    = sr.node_alloc();
         const bool propagate_alloc = allocator_traits_type::
               propagate_on_container_move_assignment::value;
         const bool allocators_equal = this_alloc == x_alloc; (void)allocators_equal;
         //Resources can be transferred if both allocators are
         //going to be equal after this function (either propagated or already equal)
         if(propagate_alloc || allocators_equal){
            //Destroy
            this->clear();
            //Move allocator if needed
            this->AllocHolder::move_assign_alloc(sr);
            //Obtain resources
            this->icont() = boost::move(sr.icont());
         }
         //Else do a one by one move
         else{
            this->assign( boost::make_move_iterator(sr.begin())
                        , boost::make_move_iterator(sr.end()));
         }
      }
      return *this;
   }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Makes *this contain the same elements as in il.
   //!
   //! <b>Postcondition</b>: this->size() == il.size(). *this contains a copy
   //! of each of il's elements.
   //!
   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or value_type's move constructor throws)
   slist& operator=(std::initializer_list<value_type> il)
   {
       assign(il.begin(), il.end());
       return *this;
   }
#endif

   //! <b>Effects</b>: Assigns the n copies of val to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   void assign(size_type n, const T& val)
   {
      typedef constant_iterator<value_type> cvalue_iterator;
      return this->assign(cvalue_iterator(val, n), cvalue_iterator());
   }

   //! <b>Effects</b>: Assigns the range [first, last) to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's constructor from dereferencing InpIt throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   template <class InpIt>
   void assign(InpIt first, InpIt last
      #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , typename dtl::disable_if_convertible<InpIt, size_type>::type * = 0
      #endif
      )
   {
      iterator end_n(this->end());
      iterator prev(this->before_begin());
      iterator node(this->begin());
      while (node != end_n && first != last){
         *node = *first;
         prev = node;
         ++node;
         ++first;
      }
      if (first != last)
         this->insert_after(prev, first, last);
      else
         this->erase_after(prev, end_n);
   }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Assigns the range [il.begin(), il.end()) to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's constructor from dereferencing std::initializer_list iterator throws.
   //!
   //! <b>Complexity</b>: Linear to range [il.begin(), il.end()).

   void assign(std::initializer_list<value_type> il)
   {
       assign(il.begin(), il.end());
   }
#endif
   //! <b>Effects</b>: Returns a copy of the internal allocator.
   //!
   //! <b>Throws</b>: If allocator's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return allocator_type(this->node_alloc()); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      stored_allocator_type &get_stored_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->node_alloc(); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const stored_allocator_type &get_stored_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->node_alloc(); }

   //////////////////////////////////////////////
   //
   //                iterators
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns a non-dereferenceable iterator that,
   //! when incremented, yields begin().  This iterator may be used
   //! as the argument to insert_after, erase_after, etc.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator before_begin() BOOST_NOEXCEPT_OR_NOTHROW
   {  return iterator(end());  }

   //! <b>Effects</b>: Returns a non-dereferenceable const_iterator
   //! that, when incremented, yields begin().  This iterator may be used
   //! as the argument to insert_after, erase_after, etc.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator before_begin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->cbefore_begin();  }

   //! <b>Effects</b>: Returns an iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator begin() BOOST_NOEXCEPT_OR_NOTHROW
   { return iterator(this->icont().begin()); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->cbegin();   }

   //! <b>Effects</b>: Returns an iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator end() BOOST_NOEXCEPT_OR_NOTHROW
   { return iterator(this->icont().end()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->cend();   }

   //! <b>Effects</b>: Returns a non-dereferenceable const_iterator
   //! that, when incremented, yields begin().  This iterator may be used
   //! as the argument to insert_after, erase_after, etc.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator cbefore_begin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_iterator(end());  }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_iterator(this->non_const_icont().begin());   }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_iterator(this->non_const_icont().end());   }

   //! <b>Returns</b>: The iterator to the element before i in the sequence.
   //!   Returns the end-iterator, if either i is the begin-iterator or the
   //!   sequence is empty.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements before i.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator previous(iterator p) BOOST_NOEXCEPT_OR_NOTHROW
   {  return iterator(this->icont().previous(p.get())); }

   //! <b>Returns</b>: The const_iterator to the element before i in the sequence.
   //!   Returns the end-const_iterator, if either i is the begin-const_iterator or
   //!   the sequence is empty.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements before i.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator previous(const_iterator p)
   {  return const_iterator(this->icont().previous(p.get())); }

   //////////////////////////////////////////////
   //
   //                capacity
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns true if the list contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      bool empty() const
   {  return !this->size();   }

   //! <b>Effects</b>: Returns the number of the elements contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type size() const
   {  return this->icont().size(); }

   //! <b>Effects</b>: Returns the largest possible size of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type max_size() const
   {  return AllocHolder::max_size();  }

   //! <b>Effects</b>: Inserts or erases elements at the end such that
   //!   the size becomes n. New elements are value initialized.
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the difference between size() and new_size.
   void resize(size_type new_size)
   {
      const_iterator last_pos;
      if(!priv_try_shrink(new_size, last_pos)){
         typedef value_init_construct_iterator<value_type> value_init_iterator;
         this->insert_after(last_pos, value_init_iterator(new_size - this->size()), value_init_iterator());
      }
   }

   //! <b>Effects</b>: Inserts or erases elements at the end such that
   //!   the size becomes n. New elements are copy constructed from x.
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the difference between size() and new_size.
   void resize(size_type new_size, const T& x)
   {
      const_iterator last_pos;
      if(!priv_try_shrink(new_size, last_pos)){
         this->insert_after(last_pos, new_size, x);
      }
   }

   //////////////////////////////////////////////
   //
   //               element access
   //
   //////////////////////////////////////////////

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a reference to the first element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      reference front()
   {
      BOOST_ASSERT(!this->empty());
      return *this->begin();
   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a const reference to the first element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reference front() const
   {
      BOOST_ASSERT(!this->empty());
      return *this->begin();
   }

   //////////////////////////////////////////////
   //
   //                modifiers
   //
   //////////////////////////////////////////////

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the front of the list
   //!
   //! <b>Returns</b>: A reference to the created object.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   template <class... Args>
   reference emplace_front(BOOST_FWD_REF(Args)... args)
   {  return *this->emplace_after(this->cbefore_begin(), boost::forward<Args>(args)...); }

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... after prev
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's in-place constructor throws.
   //!
   //! <b>Complexity</b>: Constant
   template <class... Args>
   iterator emplace_after(const_iterator prev, BOOST_FWD_REF(Args)... args)
   {
      NodePtr pnode(AllocHolder::create_node(boost::forward<Args>(args)...));
      return iterator(this->icont().insert_after(prev.get(), *pnode));
   }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_SLIST_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   reference emplace_front(BOOST_MOVE_UREF##N)\
   {  return *this->emplace_after(this->cbefore_begin() BOOST_MOVE_I##N BOOST_MOVE_FWD##N);}\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace_after(const_iterator p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      NodePtr pnode (AllocHolder::create_node(BOOST_MOVE_FWD##N));\
      return iterator(this->icont().insert_after(p.get(), *pnode));\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_SLIST_EMPLACE_CODE)
   #undef BOOST_CONTAINER_SLIST_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts a copy of x at the beginning of the list.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void push_front(const T &x);

   //! <b>Effects</b>: Constructs a new element in the beginning of the list
   //!   and moves the resources of x to this new element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void push_front(T &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH(push_front, T, void, priv_push_front)
   #endif


   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts a copy of the value after prev_p.
   //!
   //! <b>Returns</b>: An iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references of
   //!   previous values.
   iterator insert_after(const_iterator prev_p, const T &x);

   //! <b>Requires</b>: prev_p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts a move constructed copy object from the value after the
   //!    element pointed by prev_p.
   //!
   //! <b>Returns</b>: An iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references of
   //!   previous values.
   iterator insert_after(const_iterator prev_p, T &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert_after, T, iterator, priv_insert_after, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: prev_p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts n copies of x after prev_p.
   //!
   //! <b>Returns</b>: an iterator to the last inserted element or prev_p if n is 0.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //!
   //! <b>Complexity</b>: Linear to n.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references of
   //!   previous values.
   iterator insert_after(const_iterator prev_p, size_type n, const value_type& x)
   {
      typedef constant_iterator<value_type> cvalue_iterator;
      return this->insert_after(prev_p, cvalue_iterator(x, n), cvalue_iterator());
   }

   //! <b>Requires</b>: prev_p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts the range pointed by [first, last) after prev_p.
   //!
   //! <b>Returns</b>: an iterator to the last inserted element or prev_p if first == last.
   //!
   //! <b>Throws</b>: If memory allocation throws, T's constructor from a
   //!   dereferenced InpIt throws.
   //!
   //! <b>Complexity</b>: Linear to the number of elements inserted.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references of
   //!   previous values.
   template <class InpIt>
   iterator insert_after(const_iterator prev_p, InpIt first, InpIt last
      #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
      , typename dtl::enable_if_c
         < !dtl::is_convertible<InpIt, size_type>::value
          && (dtl::is_input_iterator<InpIt>::value
                || dtl::is_same<alloc_version, version_1>::value
               )
         >::type * = 0
      #endif
      )
   {
      iterator ret_it(prev_p.get());
      for (; first != last; ++first){
         ret_it = iterator(this->icont().insert_after(ret_it.get(), *this->create_node_from_it(first)));
      }
      return ret_it;
   }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Requires</b>: prev_p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts the range pointed by [il.begin(), il.end()) after prev_p.
   //!
   //! <b>Returns</b>: an iterator to the last inserted element or prev_p if il.begin() == il.end().
   //!
   //! <b>Throws</b>: If memory allocation throws, T's constructor from a
   //!   dereferenced std::initializer_list iterator throws.
   //!
   //! <b>Complexity</b>: Linear to the number of elements inserted.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references of
   //!   previous values.
   iterator insert_after(const_iterator prev_p, std::initializer_list<value_type> il)
   {
       return insert_after(prev_p, il.begin(), il.end());
   }
#endif
   #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   template <class FwdIt>
   iterator insert_after(const_iterator prev, FwdIt first, FwdIt last
      , typename dtl::enable_if_c
         < !dtl::is_convertible<FwdIt, size_type>::value
            && !(dtl::is_input_iterator<FwdIt>::value
                || dtl::is_same<alloc_version, version_1>::value
               )
         >::type * = 0
      )
   {
      //Optimized allocation and construction
      insertion_functor func(this->icont(), prev.get());
      this->allocate_many_and_construct(first, boost::container::iterator_udistance(first, last), func);
      return iterator(func.inserted_first());
   }
   #endif

   //! <b>Effects</b>: Removes the first element from the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void pop_front()
   {
      BOOST_ASSERT(!this->empty());
      this->icont().pop_front_and_dispose(Destroyer(this->node_alloc()));
   }

   //! <b>Effects</b>: Erases the element after the element pointed by prev_p
   //!    of the list.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Does not invalidate iterators or references to non erased elements.
   iterator erase_after(const_iterator prev_p)
   {
      return iterator(this->icont().erase_after_and_dispose(prev_p.get(), Destroyer(this->node_alloc())));
   }

   //! <b>Effects</b>: Erases the range (before_first, last) from
   //!   the list.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of erased elements.
   //!
   //! <b>Note</b>: Does not invalidate iterators or references to non erased elements.
   iterator erase_after(const_iterator before_first, const_iterator last)
   {
      return iterator(this->icont().erase_after_and_dispose(before_first.get(), last.get(), Destroyer(this->node_alloc())));
   }

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements on *this and x.
   void swap(slist& x)
      BOOST_NOEXCEPT_IF( allocator_traits_type::propagate_on_container_swap::value
                                || allocator_traits_type::is_always_equal::value)
   {
      BOOST_ASSERT(allocator_traits_type::propagate_on_container_swap::value ||
                   allocator_traits_type::is_always_equal::value ||
                   this->get_stored_allocator() == x.get_stored_allocator());
      AllocHolder::swap(x);
   }

   //! <b>Effects</b>: Erases all the elements of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the list.
   void clear()
   {  this->icont().clear_and_dispose(Destroyer(this->node_alloc()));  }

   //////////////////////////////////////////////
   //
   //              slist operations
   //
   //////////////////////////////////////////////

   //! <b>Requires</b>: p must point to an element contained
   //!   by the list. x != *this
   //!
   //! <b>Effects</b>: Transfers all the elements of list x to this list, after the
   //!   the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: runtime_error if this' allocator and x's allocator
   //!   are not equal.
   //!
   //! <b>Complexity</b>: Linear to the elements in x.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p, slist& x) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this != &x);
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().splice_after(prev_p.get(), x.icont());
   }

   //! <b>Requires</b>: p must point to an element contained
   //!   by the list. x != *this
   //!
   //! <b>Effects</b>: Transfers all the elements of list x to this list, after the
   //!   the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: runtime_error if this' allocator and x's allocator
   //!   are not equal.
   //!
   //! <b>Complexity</b>: Linear to the elements in x.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p, BOOST_RV_REF(slist) x) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice_after(prev_p, BOOST_MOVE_TO_LV(x));  }

   //! <b>Requires</b>: prev_p must be a valid iterator of this.
   //!   i must point to an element contained in list x.
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Effects</b>: Transfers the value pointed by i, from list x to this list,
   //!   after the element pointed by prev_p.
   //!   If prev_p == prev or prev_p == ++prev, this function is a null operation.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p, slist& x, const_iterator prev) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().splice_after(prev_p.get(), x.icont(), prev.get());
   }

   //! <b>Requires</b>: prev_p must be a valid iterator of this.
   //!   i must point to an element contained in list x.
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Effects</b>: Transfers the value pointed by i, from list x to this list,
   //!   after the element pointed by prev_p.
   //!   If prev_p == prev or prev_p == ++prev, this function is a null operation.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p, BOOST_RV_REF(slist) x, const_iterator prev) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice_after(prev_p, BOOST_MOVE_TO_LV(x), prev);  }

   //! <b>Requires</b>: prev_p must be a valid iterator of this.
   //!   before_first and before_last must be valid iterators of x.
   //!   prev_p must not be contained in [before_first, before_last) range.
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Effects</b>: Transfers the range [before_first + 1, before_last + 1)
   //!   from list x to this list, after the element pointed by prev_p.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear to the number of transferred elements.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p,      slist& x,
      const_iterator before_first,  const_iterator before_last) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().splice_after
         (prev_p.get(), x.icont(), before_first.get(), before_last.get());
   }

   //! <b>Requires</b>: prev_p must be a valid iterator of this.
   //!   before_first and before_last must be valid iterators of x.
   //!   prev_p must not be contained in [before_first, before_last) range.
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Effects</b>: Transfers the range [before_first + 1, before_last + 1)
   //!   from list x to this list, after the element pointed by prev_p.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear to the number of transferred elements.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p,      BOOST_RV_REF(slist) x,
      const_iterator before_first,  const_iterator before_last) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice_after(prev_p, BOOST_MOVE_TO_LV(x), before_first, before_last);  }

   //! <b>Requires</b>: prev_p must be a valid iterator of this.
   //!   before_first and before_last must be valid iterators of x.
   //!   prev_p must not be contained in [before_first, before_last) range.
   //!   n == distance(before_first, before_last).
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Effects</b>: Transfers the range [before_first + 1, before_last + 1)
   //!   from list x to this list, after the element pointed by prev_p.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p,      slist& x,
                     const_iterator before_first,  const_iterator before_last,
                     size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().splice_after
         (prev_p.get(), x.icont(), before_first.get(), before_last.get(), n);
   }

   //! <b>Requires</b>: prev_p must be a valid iterator of this.
   //!   before_first and before_last must be valid iterators of x.
   //!   prev_p must not be contained in [before_first, before_last) range.
   //!   n == distance(before_first, before_last).
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Effects</b>: Transfers the range [before_first + 1, before_last + 1)
   //!   from list x to this list, after the element pointed by prev_p.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p,      BOOST_RV_REF(slist) x,
                     const_iterator before_first,  const_iterator before_last,
                     size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice_after(prev_p, BOOST_MOVE_TO_LV(x), before_first, before_last, n);  }

   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   void remove(const T& value)
   {  this->remove_if(equal_to_value_type(value));  }

   //! <b>Effects</b>: Removes all the elements for which a specified
   //!   predicate is satisfied.
   //!
   //! <b>Throws</b>: If pred throws.
   //!
   //! <b>Complexity</b>: Linear time. It performs exactly size() calls to the predicate.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template <class Pred>
   void remove_if(Pred pred)
   {
      typedef value_to_node_compare<Node, Pred> value_to_node_compare_type;
      this->icont().remove_and_dispose_if(value_to_node_compare_type(pred), Destroyer(this->node_alloc()));
   }

   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent
   //!   elements that are equal from the list.
   //!
   //! <b>Throws</b>: If comparison throws.
   //!
   //! <b>Complexity</b>: Linear time (size()-1 comparisons equality comparisons).
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   void unique()
   {  this->unique(value_equal_t());  }

   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent
   //!   elements that satisfy some binary predicate from the list.
   //!
   //! <b>Throws</b>: If pred throws.
   //!
   //! <b>Complexity</b>: Linear time (size()-1 comparisons calls to pred()).
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template <class Pred>
   void unique(Pred pred)
   {
      typedef value_to_node_compare<Node, Pred> value_to_node_compare_type;
      this->icont().unique_and_dispose(value_to_node_compare_type(pred), Destroyer(this->node_alloc()));
   }

   //! <b>Requires</b>: The lists x and *this must be distinct.
   //!
   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this according to std::less<value_type>. The merge is stable;
   //!   that is, if an element from *this is equivalent to one from x, then the element
   //!   from *this will precede the one from x.
   //!
   //! <b>Throws</b>: If comparison throws.
   //!
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   void merge(slist & x)
   {  this->merge(x, value_less_t()); }

   //! <b>Requires</b>: The lists x and *this must be distinct.
   //!
   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this according to std::less<value_type>. The merge is stable;
   //!   that is, if an element from *this is equivalent to one from x, then the element
   //!   from *this will precede the one from x.
   //!
   //! <b>Throws</b>: If comparison throws.
   //!
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   void merge(BOOST_RV_REF(slist) x)
   {  this->merge(BOOST_MOVE_TO_LV(x)); }

   //! <b>Requires</b>: p must be a comparison function that induces a strict weak
   //!   ordering and both *this and x must be sorted according to that ordering
   //!   The lists x and *this must be distinct.
   //!
   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this. The merge is stable; that is, if an element from *this is
   //!   equivalent to one from x, then the element from *this will precede the one from x.
   //!
   //! <b>Throws</b>: If comp throws.
   //!
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //!
   //! <b>Note</b>: Iterators and references to *this are not invalidated.
   template <class StrictWeakOrdering>
   void merge(slist& x, StrictWeakOrdering comp)
   {
      typedef value_to_node_compare<Node, StrictWeakOrdering> value_to_node_compare_type;
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().merge(x.icont(), value_to_node_compare_type(comp));
   }

   //! <b>Requires</b>: p must be a comparison function that induces a strict weak
   //!   ordering and both *this and x must be sorted according to that ordering
   //!   The lists x and *this must be distinct.
   //!
   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this. The merge is stable; that is, if an element from *this is
   //!   equivalent to one from x, then the element from *this will precede the one from x.
   //!
   //! <b>Throws</b>: If comp throws.
   //!
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //!
   //! <b>Note</b>: Iterators and references to *this are not invalidated.
   template <class StrictWeakOrdering>
   void merge(BOOST_RV_REF(slist) x, StrictWeakOrdering comp)
   {  this->merge(BOOST_MOVE_TO_LV(x), comp); }

   //! <b>Effects</b>: This function sorts the list *this according to std::less<value_type>.
   //!   The sort is stable, that is, the relative order of equivalent elements is preserved.
   //!
   //! <b>Throws</b>: If comparison throws.
   //!
   //! <b>Notes</b>: Iterators and references are not invalidated.
   //!
   //! <b>Complexity</b>: The number of comparisons is approximately N log N, where N
   //!   is the list's size.
   void sort()
   {  this->sort(value_less_t());  }

   //! <b>Effects</b>: This function sorts the list *this according to std::less<value_type>.
   //!   The sort is stable, that is, the relative order of equivalent elements is preserved.
   //!
   //! <b>Throws</b>: If comp throws.
   //!
   //! <b>Notes</b>: Iterators and references are not invalidated.
   //!
   //! <b>Complexity</b>: The number of comparisons is approximately N log N, where N
   //!   is the list's size.
   template <class StrictWeakOrdering>
   void sort(StrictWeakOrdering comp)
   {
      typedef value_to_node_compare<Node, StrictWeakOrdering> value_to_node_compare_type;
      // nothing if the slist has length 0 or 1.
      if (this->size() < 2)
         return;
      this->icont().sort(value_to_node_compare_type(comp));
   }

   //! <b>Effects</b>: Reverses the order of elements in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: This function is linear time.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated
   void reverse() BOOST_NOEXCEPT_OR_NOTHROW
   {  this->icont().reverse();  }

   //////////////////////////////////////////////
   //
   //       list compatibility interface
   //
   //////////////////////////////////////////////

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... before p
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's in-place constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the elements before p
   template <class... Args>
   iterator emplace(const_iterator p, BOOST_FWD_REF(Args)... args)
   {  return this->emplace_after(this->previous(p), boost::forward<Args>(args)...);  }

   #else

   #define BOOST_CONTAINER_SLIST_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace(const_iterator p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      return this->emplace_after(this->previous(p) BOOST_MOVE_I##N BOOST_MOVE_FWD##N);\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_SLIST_EMPLACE_CODE)
   #undef BOOST_CONTAINER_SLIST_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of x before p.
   //!
   //! <b>Returns</b>: an iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws or x's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the elements before p.
   iterator insert(const_iterator p, const T &x);

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a new element before p with x's resources.
   //!
   //! <b>Returns</b>: an iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Linear to the elements before p.
   iterator insert(const_iterator prev_p, T &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, T, iterator, priv_insert, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts n copies of x before p.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or p if n == 0.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n plus linear to the elements before p.
   iterator insert(const_iterator p, size_type n, const value_type& x)
   {
      const_iterator prev(this->previous(p));
      this->insert_after(prev, n, x);
      return ++iterator(prev.get());
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of the [first, last) range before p.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or p if first == last.
   //!
   //! <b>Throws</b>: If memory allocation throws, T's constructor from a
   //!   dereferenced InpIt throws.
   //!
   //! <b>Complexity</b>: Linear to distance [first, last) plus
   //!    linear to the elements before p.
   template <class InIter>
   iterator insert(const_iterator p, InIter first, InIter last)
   {
      const_iterator prev(this->previous(p));
      this->insert_after(prev, first, last);
      return ++iterator(prev.get());
   }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of the [il.begin(), il.end()) range before p.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or p if il.begin() == il.end().
   //!
   //! <b>Throws</b>: If memory allocation throws, T's constructor from a
   //!   dereferenced std::initializer_list iterator throws.
   //!
   //! <b>Complexity</b>: Linear to the range [il.begin(), il.end()) plus
   //!    linear to the elements before p.
   iterator insert(const_iterator p, std::initializer_list<value_type> il)
   {
       return insert(p, il.begin(), il.end());
   }
#endif

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Erases the element at p.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements before p.
   iterator erase(const_iterator p) BOOST_NOEXCEPT_OR_NOTHROW
   {  return iterator(this->erase_after(previous(p))); }

   //! <b>Requires</b>: first and last must be valid iterator to elements in *this.
   //!
   //! <b>Effects</b>: Erases the elements pointed by [first, last).
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the distance between first and last plus
   //!   linear to the elements before first.
   iterator erase(const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW
   {  return iterator(this->erase_after(previous(first), last)); }

   //! <b>Requires</b>: p must point to an element contained
   //!   by the list. x != *this. this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers all the elements of list x to this list, before the
   //!   the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear in distance(begin(), p), and linear in x.size().
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, slist& x) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice_after(this->previous(p), x);  }

   //! <b>Requires</b>: p must point to an element contained
   //!   by the list. x != *this. this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers all the elements of list x to this list, before the
   //!   the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear in distance(begin(), p), and linear in x.size().
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, BOOST_RV_REF(slist) x) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice(p, BOOST_MOVE_TO_LV(x));  }

   //! <b>Requires</b>: p must point to an element contained
   //!   by this list. i must point to an element contained in list x.
   //!   this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers the value pointed by i, from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!   If p == i or p == ++i, this function is a null operation.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear in distance(begin(), p), and in distance(x.begin(), i).
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, slist& x, const_iterator i) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice_after(this->previous(p), x, x.previous(i));  }

   //! <b>Requires</b>: p must point to an element contained
   //!   by this list. i must point to an element contained in list x.
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Effects</b>: Transfers the value pointed by i, from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!   If p == i or p == ++i, this function is a null operation.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear in distance(begin(), p), and in distance(x.begin(), i).
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, BOOST_RV_REF(slist) x, const_iterator i) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice(p, BOOST_MOVE_TO_LV(x), i);  }

   //! <b>Requires</b>: p must point to an element contained
   //!   by this list. first and last must point to elements contained in list x.
   //!
   //! <b>Effects</b>: Transfers the range pointed by first and last from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear in distance(begin(), p), in distance(x.begin(), first),
   //!   and in distance(first, last).
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, slist& x, const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice_after(this->previous(p), x, x.previous(first), x.previous(last));  }

   //! <b>Requires</b>: p must point to an element contained
   //!   by this list. first and last must point to elements contained in list x.
   //!   this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers the range pointed by first and last from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear in distance(begin(), p), in distance(x.begin(), first),
   //!   and in distance(first, last).
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, BOOST_RV_REF(slist) x, const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice(p, BOOST_MOVE_TO_LV(x), first, last);  }

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const slist& x, const slist& y)
   {  return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());  }

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator!=(const slist& x, const slist& y)
   {  return !(x == y); }

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator<(const slist& x, const slist& y)
   {  return ::boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator>(const slist& x, const slist& y)
   {  return y < x;  }

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator<=(const slist& x, const slist& y)
   {  return !(y < x);  }

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator>=(const slist& x, const slist& y)
   {  return !(x < y);  }

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(slist& x, slist& y)
       BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT(x.swap(y)))
   {  x.swap(y);  }

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:

   template<class U>
   void priv_push_front(BOOST_FWD_REF(U) x)
   {  this->icont().push_front(*this->create_node(::boost::forward<U>(x))); }

   bool priv_try_shrink(size_type new_size, const_iterator &last_pos)
   {
      typename Icont::iterator end_n(this->icont().end()), cur(this->icont().before_begin()), cur_next;
      while (++(cur_next = cur) != end_n && new_size > 0){
         --new_size;
         cur = cur_next;
      }
      last_pos = const_iterator(cur);
      if (cur_next != end_n){
         this->erase_after(last_pos, const_iterator(end_n));
         return true;
      }
      else{
         return false;
      }
   }

   template<class U>
   iterator priv_insert(const_iterator p, BOOST_FWD_REF(U) x)
   {  return this->insert_after(previous(p), ::boost::forward<U>(x)); }

   template<class U>
   iterator priv_insert_after(const_iterator prev_p, BOOST_FWD_REF(U) x)
   {  return iterator(this->icont().insert_after(prev_p.get(), *this->create_node(::boost::forward<U>(x)))); }

   class insertion_functor;
   friend class insertion_functor;

   class insertion_functor
   {
      Icont &icont_;
      typedef typename Icont::iterator       iiterator;
      typedef typename Icont::const_iterator iconst_iterator;
      const iconst_iterator prev_;
      iiterator   ret_;

      public:
      insertion_functor(Icont &icont, typename Icont::const_iterator prev)
         :  icont_(icont), prev_(prev), ret_(prev.unconst())
      {}

      void operator()(Node &n)
      {
         ret_ = this->icont_.insert_after(prev_, n);
      }

      iiterator inserted_first() const
      {  return ret_;   }
   };

   //Functors for member algorithm defaults
   typedef value_less<value_type>   value_less_t;
   typedef value_equal<value_type>  value_equal_t;

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InpIt>
slist(InpIt, InpIt) ->
   slist<typename iterator_traits<InpIt>::value_type>;

template <typename InpIt, typename Allocator>
slist(InpIt, InpIt, Allocator const&) ->
   slist<typename iterator_traits<InpIt>::value_type, Allocator>;

#endif

}}

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace boost {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class T, class Allocator>
struct has_trivial_destructor_after_move<boost::container::slist<T, Allocator> >
{
   typedef typename boost::container::slist<T, Allocator>::allocator_type allocator_type;
   typedef typename ::boost::container::allocator_traits<allocator_type>::pointer pointer;
   static const bool value = ::boost::has_trivial_destructor_after_move<allocator_type>::value &&
                             ::boost::has_trivial_destructor_after_move<pointer>::value;
};

namespace container {

}} //namespace boost{  namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

// Specialization of insert_iterator so that insertions will be constant
// time rather than linear time.

#include <boost/move/detail/std_ns_begin.hpp>
BOOST_CONTAINER_DOC1ST(namespace std {, BOOST_MOVE_STD_NS_BEG)

//! A specialization of insert_iterator
//! that works with slist
template <class T, class ValueAllocator>
class insert_iterator<boost::container::slist<T, ValueAllocator> >
{
   private:
   typedef boost::container::slist<T, ValueAllocator> Container;
   Container* container;
   typename Container::iterator iter;

   public:
   typedef Container           container_type;
   typedef output_iterator_tag iterator_category;
   typedef void                value_type;
   typedef void                difference_type;
   typedef void                pointer;
   typedef void                reference;

   insert_iterator(Container& x,
                   typename Container::iterator i,
                   bool is_previous = false)
      : container(&x), iter(is_previous ? i : x.previous(i)){ }

   insert_iterator<Container>&
      operator=(const typename Container::value_type& value)
   {
      iter = container->insert_after(iter, value);
      return *this;
   }
   insert_iterator<Container>& operator*(){ return *this; }
   insert_iterator<Container>& operator++(){ return *this; }
   insert_iterator<Container>& operator++(int){ return *this; }
};

BOOST_CONTAINER_DOC1ST( }, BOOST_MOVE_STD_NS_END)
#include <boost/move/detail/std_ns_end.hpp>

#include <boost/container/detail/config_end.hpp>

#endif // BOOST_CONTAINER_SLIST_HPP

/* slist.hpp
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
*/