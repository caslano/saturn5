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
struct slist_node
   :  public slist_hook<VoidPointer>::type
{
   public:
   typedef T value_type;
   typedef T internal_type;
   typedef typename slist_hook<VoidPointer>::type hook_type;

   typedef typename dtl::aligned_storage<sizeof(T), dtl::alignment_of<T>::value>::type storage_t;
   storage_t m_storage;

   #if defined(BOOST_GCC) && (BOOST_GCC >= 40600) && (BOOST_GCC < 80000)
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wstrict-aliasing"
      #define BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif

   BOOST_CONTAINER_FORCEINLINE T &get_data()
   {  return *reinterpret_cast<T*>(this->m_storage.data);   }

   BOOST_CONTAINER_FORCEINLINE const T &get_data() const
   {  return *reinterpret_cast<const T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE T *get_data_ptr()
   {  return reinterpret_cast<T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE const T *get_data_ptr() const
   {  return reinterpret_cast<T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE internal_type &get_real_data()
   {  return *reinterpret_cast<internal_type*>(this->m_storage.data);   }

   BOOST_CONTAINER_FORCEINLINE const internal_type &get_real_data() const
   {  return *reinterpret_cast<const internal_type*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE internal_type *get_real_data_ptr()
   {  return reinterpret_cast<internal_type*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE const internal_type *get_real_data_ptr() const
   {  return reinterpret_cast<internal_type*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE ~slist_node()
   {  reinterpret_cast<T*>(this->m_storage.data)->~T();  }

   #if defined(BOOST_CONTAINER_DISABLE_ALIASING_WARNING)
      #pragma GCC diagnostic pop
      #undef BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif

   BOOST_CONTAINER_FORCEINLINE void destroy_header()
   {  static_cast<hook_type*>(this)->~hook_type();  }
};


template <class T, class VoidPointer>
struct iiterator_node_value_type< slist_node<T,VoidPointer> > {
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
   typedef typename dtl::slist_node
         <value_type, void_pointer>             node_type;

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
   typedef dtl::allocator_destroyer<NodeAlloc> Destroyer;
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
   //          construct/copy/destroy
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
      if(this->node_alloc() == x.node_alloc()){
         this->icont().swap(x.icont());
      }
      else{
         this->insert_after(this->cbefore_begin(), boost::make_move_iterator(x.begin()), boost::make_move_iterator(x.end()));
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
      if (BOOST_LIKELY(this != &x)) {
         NodeAlloc &this_alloc = this->node_alloc();
         NodeAlloc &x_alloc    = x.node_alloc();
         const bool propagate_alloc = allocator_traits_type::
               propagate_on_container_move_assignment::value;
         const bool allocators_equal = this_alloc == x_alloc; (void)allocators_equal;
         //Resources can be transferred if both allocators are
         //going to be equal after this function (either propagated or already equal)
         if(propagate_alloc || allocators_equal){
            //Destroy
            this->clear();
            //Move allocator if needed
            this->AllocHolder::move_assign_alloc(x);
            //Obtain resources
            this->icont() = boost::move(x.icont());
         }
         //Else do a one by one move
         else{
            this->assign( boost::make_move_iterator(x.begin())
                        , boost::make_move_iterator(x.end()));
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
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
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
   allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return allocator_type(this->node_alloc()); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   stored_allocator_type &get_stored_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->node_alloc(); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
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
   iterator before_begin() BOOST_NOEXCEPT_OR_NOTHROW
   {  return iterator(end());  }

   //! <b>Effects</b>: Returns a non-dereferenceable const_iterator
   //! that, when incremented, yields begin().  This iterator may be used
   //! as the argument to insert_after, erase_after, etc.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator before_begin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->cbefore_begin();  }

   //! <b>Effects</b>: Returns an iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator begin() BOOST_NOEXCEPT_OR_NOTHROW
   { return iterator(this->icont().begin()); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->cbegin();   }

   //! <b>Effects</b>: Returns an iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator end() BOOST_NOEXCEPT_OR_NOTHROW
   { return iterator(this->icont().end()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->cend();   }

   //! <b>Effects</b>: Returns a non-dereferenceable const_iterator
   //! that, when incremented, yields begin().  This iterator may be used
   //! as the argument to insert_after, erase_after, etc.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cbefore_begin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_iterator(end());  }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_iterator(this->non_const_icont().begin());   }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
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
   bool empty() const
   {  return !this->size();   }

   //! <b>Effects</b>: Returns the number of the elements contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type size() const
   {  return this->icont().size(); }

   //! <b>Effects</b>: Returns the largest possible size of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
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
         typedef value_init_construct_iterator<value_type, difference_type> value_init_iterator;
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
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
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
      this->allocate_many_and_construct(first, boost::container::iterator_distance(first, last), func);
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
   //! <b>Throws</b>: std::runtime_error if this' allocator and x's allocator
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
   //! <b>Throws</b>: std::runtime_error if this' allocator and x's allocator
   //!   are not equal.
   //!
   //! <b>Complexity</b>: Linear to the elements in x.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice_after(const_iterator prev_p, BOOST_RV_REF(slist) x) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice_after(prev_p, static_cast<slist&>(x));  }

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
   {  this->splice_after(prev_p, static_cast<slist&>(x), prev);  }

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
   {  this->splice_after(prev_p, static_cast<slist&>(x), before_first, before_last);  }

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
   {  this->splice_after(prev_p, static_cast<slist&>(x), before_first, before_last, n);  }

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
   {  this->merge(static_cast<slist&>(x)); }

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
   {  this->merge(static_cast<slist&>(x), comp); }

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
   {  this->splice(p, static_cast<slist&>(x));  }

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
   {  this->splice(p, static_cast<slist&>(x), i);  }

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
   {  this->splice(p, static_cast<slist&>(x), first, last);  }

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const slist& x, const slist& y)
   {  return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());  }

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const slist& x, const slist& y)
   {  return !(x == y); }

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const slist& x, const slist& y)
   {  return ::boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const slist& x, const slist& y)
   {  return y < x;  }

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const slist& x, const slist& y)
   {  return !(y < x);  }

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const slist& x, const slist& y)
   {  return !(x < y);  }

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(slist& x, slist& y)
   {  x.swap(y);  }

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:

   void priv_push_front (const T &x)
   {  this->insert_after(this->cbefore_begin(), x);  }

   void priv_push_front (BOOST_RV_REF(T) x)
   {  this->insert_after(this->cbefore_begin(), ::boost::move(x));  }

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