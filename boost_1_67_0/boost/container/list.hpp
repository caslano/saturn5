//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_LIST_HPP
#define BOOST_CONTAINER_LIST_HPP

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
#include <boost/container/detail/algorithm.hpp>
#include <boost/container/detail/compare_functors.hpp>
#include <boost/container/detail/iterator.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/node_alloc_holder.hpp>
#include <boost/container/detail/version_type.hpp>
#include <boost/container/detail/value_functors.hpp>
// move
#include <boost/move/utility_core.hpp>
#include <boost/move/iterator.hpp>
#include <boost/move/traits.hpp>
// move/detail
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#  include <boost/move/detail/fwd_macros.hpp>
#endif
#include <boost/move/detail/move_helpers.hpp>

// intrusive
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/list.hpp>
// other
#include <boost/assert.hpp>
// std
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
namespace dtl {

template<class VoidPointer>
struct list_hook
{
   typedef typename dtl::bi::make_list_base_hook
      <dtl::bi::void_pointer<VoidPointer>, dtl::bi::link_mode<dtl::bi::normal_link> >::type type;
};

template <class T, class VoidPointer>
struct list_node
   :  public list_hook<VoidPointer>::type
{
   public:
   typedef T value_type;
   typedef T internal_type;
   typedef typename list_hook<VoidPointer>::type hook_type;

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

   BOOST_CONTAINER_FORCEINLINE ~list_node()
   {  reinterpret_cast<T*>(this->m_storage.data)->~T();  }

   #if defined(BOOST_CONTAINER_DISABLE_ALIASING_WARNING)
      #pragma GCC diagnostic pop
      #undef BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif

   BOOST_CONTAINER_FORCEINLINE void destroy_header()
   {  static_cast<hook_type*>(this)->~hook_type();  }
};

template <class T, class VoidPointer>
struct iiterator_node_value_type< list_node<T,VoidPointer> > {
  typedef T type;
};

template<class Allocator>
struct intrusive_list_type
{
   typedef boost::container::allocator_traits<Allocator>   allocator_traits_type;
   typedef typename allocator_traits_type::value_type value_type;
   typedef typename boost::intrusive::pointer_traits
      <typename allocator_traits_type::pointer>::template
         rebind_pointer<void>::type
            void_pointer;
   typedef typename dtl::list_node
         <value_type, void_pointer>             node_type;
   typedef typename dtl::bi::make_list
      < node_type
      , dtl::bi::base_hook<typename list_hook<void_pointer>::type>
      , dtl::bi::constant_time_size<true>
      , dtl::bi::size_type
         <typename allocator_traits_type::size_type>
      >::type                                   container_type;
   typedef container_type                       type ;
};

}  //namespace dtl {
#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! A list is a doubly linked list. That is, it is a Sequence that supports both
//! forward and backward traversal, and (amortized) constant time insertion and
//! removal of elements at the beginning or the end, or in the middle. Lists have
//! the important property that insertion and splicing do not invalidate iterators
//! to list elements, and that even removal invalidates only the iterators that point
//! to the elements that are removed. The ordering of iterators may be changed
//! (that is, list<T>::iterator might have a different predecessor or successor
//! after a list operation than it did before), but the iterators themselves will
//! not be invalidated or made to point to different elements unless that invalidation
//! or mutation is explicit.
//!
//! \tparam T The type of object that is stored in the list
//! \tparam Allocator The allocator used for all internal memory management, use void
//!   for the default allocator
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template <class T, class Allocator = void >
#else
template <class T, class Allocator>
#endif
class list
   : protected dtl::node_alloc_holder
      < typename real_allocator<T, Allocator>::type
      , typename dtl::intrusive_list_type<typename real_allocator<T, Allocator>::type>::type>
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef typename real_allocator<T, Allocator>::type            ValueAllocator;
   typedef typename
      dtl::intrusive_list_type<ValueAllocator>::type Icont;
   typedef dtl::node_alloc_holder<ValueAllocator, Icont>          AllocHolder;
   typedef typename AllocHolder::NodePtr                          NodePtr;
   typedef typename AllocHolder::NodeAlloc                        NodeAlloc;
   typedef typename AllocHolder::ValAlloc                         ValAlloc;
   typedef typename AllocHolder::Node                             Node;
   typedef dtl::allocator_destroyer<NodeAlloc>                    Destroyer;
   typedef typename AllocHolder::alloc_version                    alloc_version;
   typedef boost::container::allocator_traits<ValueAllocator>     allocator_traits_type;
   typedef boost::container::equal_to_value
      <typename allocator_traits_type::value_type>                equal_to_value_type;

   BOOST_COPYABLE_AND_MOVABLE(list)

   typedef dtl::iterator_from_iiterator<typename Icont::iterator, false>  iterator_impl;
   typedef dtl::iterator_from_iiterator<typename Icont::iterator, true>   const_iterator_impl;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////

   typedef T                                                                              value_type;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::pointer         pointer;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::const_pointer   const_pointer;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::reference       reference;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::const_reference const_reference;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::size_type       size_type;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::difference_type difference_type;
   typedef ValueAllocator                                                                 allocator_type;
   typedef BOOST_CONTAINER_IMPDEF(NodeAlloc)                                              stored_allocator_type;
   typedef BOOST_CONTAINER_IMPDEF(iterator_impl)                                          iterator;
   typedef BOOST_CONTAINER_IMPDEF(const_iterator_impl)                                    const_iterator;
   typedef BOOST_CONTAINER_IMPDEF(boost::container::reverse_iterator<iterator>)           reverse_iterator;
   typedef BOOST_CONTAINER_IMPDEF(boost::container::reverse_iterator<const_iterator>)     const_reverse_iterator;

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs a list.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   list() BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<ValueAllocator>::value)
      : AllocHolder()
   {}

   //! <b>Effects</b>: Constructs a list taking the allocator as parameter.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   explicit list(const allocator_type &a) BOOST_NOEXCEPT_OR_NOTHROW
      : AllocHolder(a)
   {}

   //! <b>Effects</b>: Constructs a list
   //!   and inserts n value-initialized value_types.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   explicit list(size_type n)
      : AllocHolder(ValueAllocator())
   {  this->resize(n);  }

   //! <b>Effects</b>: Constructs a list that will use a copy of allocator a
   //!   and inserts n copies of value.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   list(size_type n, const allocator_type &a)
      : AllocHolder(a)
   {  this->resize(n);  }

   //! <b>Effects</b>: Constructs a list that will use a copy of allocator a
   //!   and inserts n copies of value.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   list(size_type n, const T& value, const ValueAllocator& a = ValueAllocator())
      : AllocHolder(a)
   {  this->insert(this->cbegin(), n, value);  }

   //! <b>Effects</b>: Copy constructs a list.
   //!
   //! <b>Postcondition</b>: x == *this.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the elements x contains.
   list(const list& x)
      : AllocHolder(x)
   {  this->insert(this->cbegin(), x.begin(), x.end());   }

   //! <b>Effects</b>: Move constructor. Moves x's resources to *this.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   list(BOOST_RV_REF(list) x) BOOST_NOEXCEPT_OR_NOTHROW
      : AllocHolder(BOOST_MOVE_BASE(AllocHolder, x))
   {}

   //! <b>Effects</b>: Copy constructs a list using the specified allocator.
   //!
   //! <b>Postcondition</b>: x == *this.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the elements x contains.
   list(const list& x, const allocator_type &a)
      : AllocHolder(a)
   {  this->insert(this->cbegin(), x.begin(), x.end());   }

   //! <b>Effects</b>: Move constructor sing the specified allocator.
   //!                 Moves x's resources to *this.
   //!
   //! <b>Throws</b>: If allocation or value_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise.
   list(BOOST_RV_REF(list) x, const allocator_type &a)
      : AllocHolder(a)
   {
      if(this->node_alloc() == x.node_alloc()){
         this->icont().swap(x.icont());
      }
      else{
         this->insert(this->cbegin(), boost::make_move_iterator(x.begin()), boost::make_move_iterator(x.end()));
      }
   }

   //! <b>Effects</b>: Constructs a list that will use a copy of allocator a
   //!   and inserts a copy of the range [first, last) in the list.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's constructor taking a dereferenced InIt throws.
   //!
   //! <b>Complexity</b>: Linear to the range [first, last).
   template <class InpIt>
   list(InpIt first, InpIt last, const ValueAllocator &a = ValueAllocator())
      : AllocHolder(a)
   {  this->insert(this->cbegin(), first, last);  }


#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs a list that will use a copy of allocator a
   //!   and inserts a copy of the range [il.begin(), il.end()) in the list.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's constructor taking a dereferenced
   //!   std::initializer_list iterator throws.
   //!
   //! <b>Complexity</b>: Linear to the range [il.begin(), il.end()).
   list(std::initializer_list<value_type> il, const ValueAllocator &a = ValueAllocator())
      : AllocHolder(a)
   {  this->insert(this->cbegin(), il.begin(), il.end()); }
#endif

   //! <b>Effects</b>: Destroys the list. All stored values are destroyed
   //!   and used memory is deallocated.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements.
   ~list() BOOST_NOEXCEPT_OR_NOTHROW
   {} //AllocHolder clears the list

   //! <b>Effects</b>: Makes *this contain the same elements as x.
   //!
   //! <b>Postcondition</b>: this->size() == x.size(). *this contains a copy
   //! of each of x's elements.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in x.
   list& operator=(BOOST_COPY_ASSIGN_REF(list) x)
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

   //! <b>Effects</b>: Move assignment. All x's values are transferred to *this.
   //!
   //! <b>Postcondition</b>: x.empty(). *this contains a the elements x had
   //!   before the function.
   //!
   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or value_type's move constructor throws)
   //!
   //! <b>Complexity</b>: Constant if allocator_traits_type::
   //!   propagate_on_container_move_assignment is true or
   //!   this->get>allocator() == x.get_allocator(). Linear otherwise.
   list& operator=(BOOST_RV_REF(list) x)
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
   //! <b>Effects</b>: Makes *this contain the same elements as il.
   //!
   //! <b>Postcondition</b>: this->size() == il.size(). *this contains a copy
   //! of each of x's elements.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in x.
   list& operator=(std::initializer_list<value_type> il)
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
      iterator first1      = this->begin();
      const iterator last1 = this->end();
      for ( ; first1 != last1 && first != last; ++first1, ++first)
         *first1 = *first;
      if (first == last)
         this->erase(first1, last1);
      else{
         this->insert(last1, first, last);
      }
   }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Assigns the range [il.begin(), il.end()) to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's constructor from dereferencing std::initializer_list iterator throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   void assign(std::initializer_list<value_type> il)
   { assign(il.begin(), il.end()); }
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
   {  return iterator(this->icont().end());  }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->cend();  }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW
   {  return reverse_iterator(end());  }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->crbegin();  }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW
   {  return reverse_iterator(begin());   }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->crend();   }

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
   {  return const_iterator(this->non_const_icont().end());  }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_reverse_iterator(this->cend());  }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_reverse_iterator(this->cbegin());   }

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
   bool empty() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return !this->size();  }

   //! <b>Effects</b>: Returns the number of the elements contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type size() const BOOST_NOEXCEPT_OR_NOTHROW
   {   return this->icont().size();   }

   //! <b>Effects</b>: Returns the largest possible size of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return AllocHolder::max_size();  }

   //! <b>Effects</b>: Inserts or erases elements at the end such that
   //!   the size becomes n. New elements are value initialized.
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the difference between size() and new_size.
   void resize(size_type new_size)
   {
      if(!priv_try_shrink(new_size)){
         typedef value_init_construct_iterator<value_type, difference_type> value_init_iterator;
         this->insert(this->cend(), value_init_iterator(new_size - this->size()), value_init_iterator());
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
      if(!priv_try_shrink(new_size)){
         this->insert(this->cend(), new_size - this->size(), x);
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
   reference front() BOOST_NOEXCEPT_OR_NOTHROW
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
   const_reference front() const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      return *this->begin();
   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a reference to the first element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reference back() BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      return *(--this->end());
   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a const reference to the first element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reference back() const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      return *(--this->end());
   }

   //////////////////////////////////////////////
   //
   //                modifiers
   //
   //////////////////////////////////////////////

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the end of the list.
   //!
   //! <b>Returns</b>: A reference to the created object.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's in-place constructor throws.
   //!
   //! <b>Complexity</b>: Constant
   template <class... Args>
   reference emplace_back(BOOST_FWD_REF(Args)... args)
   {  return *this->emplace(this->cend(), boost::forward<Args>(args)...); }

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the beginning of the list.
   //!
   //! <b>Returns</b>: A reference to the created object.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's in-place constructor throws.
   //!
   //! <b>Complexity</b>: Constant
   template <class... Args>
   reference emplace_front(BOOST_FWD_REF(Args)... args)
   {  return *this->emplace(this->cbegin(), boost::forward<Args>(args)...);  }

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... before p.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's in-place constructor throws.
   //!
   //! <b>Complexity</b>: Constant
   template <class... Args>
   iterator emplace(const_iterator position, BOOST_FWD_REF(Args)... args)
   {
      BOOST_ASSERT((priv_is_linked)(position));
      NodePtr pnode(AllocHolder::create_node(boost::forward<Args>(args)...));
      return iterator(this->icont().insert(position.get(), *pnode));
   }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_LIST_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   reference emplace_back(BOOST_MOVE_UREF##N)\
   {  return *this->emplace(this->cend() BOOST_MOVE_I##N BOOST_MOVE_FWD##N);  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   reference emplace_front(BOOST_MOVE_UREF##N)\
   {  return *this->emplace(this->cbegin() BOOST_MOVE_I##N BOOST_MOVE_FWD##N);}\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace(const_iterator position BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      BOOST_ASSERT(position == this->cend() || (--(++position) == position) );\
      NodePtr pnode (AllocHolder::create_node(BOOST_MOVE_FWD##N));\
      return iterator(this->icont().insert(position.get(), *pnode));\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_LIST_EMPLACE_CODE)
   #undef BOOST_CONTAINER_LIST_EMPLACE_CODE

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
   //! <b>Effects</b>: Inserts a copy of x at the end of the list.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void push_back(const T &x);

   //! <b>Effects</b>: Constructs a new element in the end of the list
   //!   and moves the resources of x to this new element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void push_back(T &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH(push_back, T, void, priv_push_back)
   #endif

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of x before p.
   //!
   //! <b>Returns</b>: an iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws or x's copy constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   iterator insert(const_iterator p, const T &x);

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a new element before p with x's resources.
   //!
   //! <b>Returns</b>: an iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   iterator insert(const_iterator p, T &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, T, iterator, priv_insert, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts n copies of x before p.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or p if n is 0.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   iterator insert(const_iterator position, size_type n, const T& x)
   {
      //range check is done by insert
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
      return this->insert(position, cvalue_iterator(x, n), cvalue_iterator());
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
   //! <b>Complexity</b>: Linear to distance [first, last).
   template <class InpIt>
   iterator insert(const_iterator p, InpIt first, InpIt last
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
      BOOST_ASSERT((priv_is_linked)(p));
      const typename Icont::iterator ipos(p.get());
      iterator ret_it(ipos);
      if(first != last){
         ret_it = iterator(this->icont().insert(ipos, *this->create_node_from_it(first)));
         ++first;
      }
      for (; first != last; ++first){
         this->icont().insert(ipos, *this->create_node_from_it(first));
      }
      return ret_it;
   }

   #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   template <class FwdIt>
   iterator insert(const_iterator position, FwdIt first, FwdIt last
      , typename dtl::enable_if_c
         < !dtl::is_convertible<FwdIt, size_type>::value
            && !(dtl::is_input_iterator<FwdIt>::value
                || dtl::is_same<alloc_version, version_1>::value
               )
         >::type * = 0
      )
   {
      BOOST_ASSERT((priv_is_linked)(position));
      //Optimized allocation and construction
      insertion_functor func(this->icont(), position.get());
      iterator before_p(position.get());
      --before_p;
      this->allocate_many_and_construct(first, boost::container::iterator_distance(first, last), func);
      return ++before_p;
   }
   #endif

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of the [il.begin(), il.end()) range before p.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or p if if.begin() == il.end().
   //!
   //! <b>Throws</b>: If memory allocation throws, T's constructor from a
   //!   dereferenced std::initializer_list iterator throws.
   //!
   //! <b>Complexity</b>: Linear to distance [il.begin(), il.end()).
   iterator insert(const_iterator p, std::initializer_list<value_type> il)
   {
      //position range check is done by insert()
      return insert(p, il.begin(), il.end());
   }
#endif

   //! <b>Effects</b>: Removes the first element from the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void pop_front() BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      this->erase(this->cbegin());
   }

   //! <b>Effects</b>: Removes the last element from the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void pop_back() BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      const_iterator tmp = this->cend();
      this->erase(--tmp);
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Erases the element at p.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   iterator erase(const_iterator p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(p != this->cend() && (priv_is_linked)(p));
      return iterator(this->icont().erase_and_dispose(p.get(), Destroyer(this->node_alloc())));
   }

   //! <b>Requires</b>: first and last must be valid iterator to elements in *this.
   //!
   //! <b>Effects</b>: Erases the elements pointed by [first, last).
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the distance between first and last.
   iterator erase(const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(first == last || (first != this->cend() && (priv_is_linked)(first)));
      BOOST_ASSERT(first == last || (priv_is_linked)(last));
      return iterator(AllocHolder::erase_range(first.get(), last.get(), alloc_version()));
   }

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   void swap(list& x)
      BOOST_NOEXCEPT_IF(allocator_traits_type::propagate_on_container_swap::value
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
   void clear() BOOST_NOEXCEPT_OR_NOTHROW
   {  AllocHolder::clear(alloc_version());  }

   //////////////////////////////////////////////
   //
   //              slist operations
   //
   //////////////////////////////////////////////

   //! <b>Requires</b>: p must point to an element contained
   //!   by the list. x != *this. this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers all the elements of list x to this list, before the
   //!   the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, list& x) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT((priv_is_linked)(p));
      BOOST_ASSERT(this != &x);
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().splice(p.get(), x.icont());
   }

   //! <b>Requires</b>: p must point to an element contained
   //!   by the list. x != *this. this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers all the elements of list x to this list, before the
   //!   the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, BOOST_RV_REF(list) x) BOOST_NOEXCEPT_OR_NOTHROW
   {
      //Checks done in splice
      this->splice(p, static_cast<list&>(x));
   }

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
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, list &x, const_iterator i) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT((priv_is_linked)(p));
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().splice(p.get(), x.icont(), i.get());
   }

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
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, BOOST_RV_REF(list) x, const_iterator i) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this != &x);
      //Additional checks done in splice()
      this->splice(p, static_cast<list&>(x), i);
   }

   //! <b>Requires</b>: p must point to an element contained
   //!   by this list. first and last must point to elements contained in list x.
   //!   this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers the range pointed by first and last from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear to the number of elements transferred.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, list &x, const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT((priv_is_linked)(p));
      BOOST_ASSERT(first == last || (first != x.cend() && x.priv_is_linked(first)));
      BOOST_ASSERT(first == last || x.priv_is_linked(last));
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().splice(p.get(), x.icont(), first.get(), last.get());
   }

   //! <b>Requires</b>: p must point to an element contained
   //!   by this list. first and last must point to elements contained in list x.
   //!   this' allocator and x's allocator shall compare equal.
   //!
   //! <b>Effects</b>: Transfers the range pointed by first and last from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Linear to the number of elements transferred.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, BOOST_RV_REF(list) x, const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this != &x);
      //Additional checks done in splice()
      this->splice(p, static_cast<list&>(x), first, last);
   }

   //! <b>Requires</b>: p must point to an element contained
   //!   by this list. first and last must point to elements contained in list x.
   //!   n == distance(first, last). this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers the range pointed by first and last from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>:  Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   //!
   //! <b>Note</b>: Non-standard extension
   void splice(const_iterator p, list &x, const_iterator first, const_iterator last, size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      this->icont().splice(p.get(), x.icont(), first.get(), last.get(), n);
   }

   //! <b>Requires</b>: p must point to an element contained
   //!   by this list. first and last must point to elements contained in list x.
   //!   n == distance(first, last). this' allocator and x's allocator shall compare equal
   //!
   //! <b>Effects</b>: Transfers the range pointed by first and last from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   //!
   //! <b>Note</b>: Non-standard extension
   void splice(const_iterator p, BOOST_RV_REF(list) x, const_iterator first, const_iterator last, size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {  this->splice(p, static_cast<list&>(x), first, last, n);  }

   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!
   //! <b>Throws</b>: If comparison throws.
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
   template <class BinaryPredicate>
   void unique(BinaryPredicate binary_pred)
   {
      typedef value_to_node_compare<Node, BinaryPredicate> value_to_node_compare_type;
      this->icont().unique_and_dispose(value_to_node_compare_type(binary_pred), Destroyer(this->node_alloc()));
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
   void merge(list &x)
   {  this->merge(x, value_less_t());  }

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
   void merge(BOOST_RV_REF(list) x)
   {  this->merge(static_cast<list&>(x)); }

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
   void merge(list &x, const StrictWeakOrdering &comp)
   {
      BOOST_ASSERT(this->node_alloc() == x.node_alloc());
      typedef value_to_node_compare<Node, StrictWeakOrdering> value_to_node_compare_type;
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
   void merge(BOOST_RV_REF(list) x, StrictWeakOrdering comp)
   {  this->merge(static_cast<list&>(x), comp); }

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
      // nothing if the list has length 0 or 1.
      if (this->size() < 2)
         return;
      typedef value_to_node_compare<Node, StrictWeakOrdering> value_to_node_compare_type;
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
   {  this->icont().reverse(); }

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const list& x, const list& y)
   {  return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());  }

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const list& x, const list& y)
   {  return !(x == y); }

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const list& x, const list& y)
   {  return boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const list& x, const list& y)
   {  return y < x;  }

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const list& x, const list& y)
   {  return !(y < x);  }

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const list& x, const list& y)
   {  return !(x < y);  }

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(list& x, list& y)
   {  x.swap(y);  }

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:

   static bool priv_is_linked(const_iterator const position)
   {
      const_iterator cur(position);
      //This list is circular including end nodes
      return (--(++cur)) == position && (++(--cur)) == position;
   }

   bool priv_try_shrink(size_type new_size)
   {
      const size_type len = this->size();
      if(len > new_size){
         const const_iterator iend = this->cend();
         size_type to_erase = len - new_size;
         const_iterator ifirst;
         if(to_erase < len/2u){
            ifirst = iend;
            while(to_erase--){
               --ifirst;
            }
         }
         else{
            ifirst = this->cbegin();
            size_type to_skip = len - to_erase;
            while(to_skip--){
               ++ifirst;
            }
         }
         this->erase(ifirst, iend);
         return true;
      }
      else{
         return false;
      }
   }

   iterator priv_insert(const_iterator p, const T &x)
   {
      BOOST_ASSERT((priv_is_linked)(p));
      NodePtr tmp = AllocHolder::create_node(x);
      return iterator(this->icont().insert(p.get(), *tmp));
   }

   iterator priv_insert(const_iterator p, BOOST_RV_REF(T) x)
   {
      BOOST_ASSERT((priv_is_linked)(p));
      NodePtr tmp = AllocHolder::create_node(boost::move(x));
      return iterator(this->icont().insert(p.get(), *tmp));
   }

   void priv_push_back (const T &x)
   {  this->insert(this->cend(), x);    }

   void priv_push_back (BOOST_RV_REF(T) x)
   {  this->insert(this->cend(), boost::move(x));    }

   void priv_push_front (const T &x)
   {  this->insert(this->cbegin(), x);  }

   void priv_push_front (BOOST_RV_REF(T) x)
   {  this->insert(this->cbegin(), boost::move(x));  }

   class insertion_functor;
   friend class insertion_functor;

   class insertion_functor
   {
      Icont &icont_;
      typedef typename Icont::const_iterator iconst_iterator;
      const iconst_iterator pos_;

      public:
      insertion_functor(Icont &icont, typename Icont::const_iterator pos)
         :  icont_(icont), pos_(pos)
      {}

      void operator()(Node &n)
      {
         this->icont_.insert(pos_, n);
      }
   };

   typedef value_less<value_type>   value_less_t;
   typedef value_equal<value_type>  value_equal_t;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD
template <typename InputIterator>
list(InputIterator, InputIterator) ->
   list<typename iterator_traits<InputIterator>::value_type>;

template <typename InputIterator, typename ValueAllocator>
list(InputIterator, InputIterator, ValueAllocator const&) ->
   list<typename iterator_traits<InputIterator>::value_type, ValueAllocator>;
#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class T, class Allocator>
struct has_trivial_destructor_after_move<boost::container::list<T, Allocator> >
{
   typedef typename boost::container::list<T, Allocator>::allocator_type allocator_type;
   typedef typename ::boost::container::allocator_traits<allocator_type>::pointer pointer;
   static const bool value = ::boost::has_trivial_destructor_after_move<allocator_type>::value &&
                             ::boost::has_trivial_destructor_after_move<pointer>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}}

#include <boost/container/detail/config_end.hpp>

#endif // BOOST_CONTAINER_LIST_HPP

/* list.hpp
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
*/