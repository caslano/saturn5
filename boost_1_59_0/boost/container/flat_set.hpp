//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_FLAT_SET_HPP
#define BOOST_CONTAINER_FLAT_SET_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

// container
#include <boost/container/allocator_traits.hpp>
#include <boost/container/container_fwd.hpp>
#include <boost/container/new_allocator.hpp> //new_allocator
// container/detail
#include <boost/container/detail/flat_tree.hpp>
#include <boost/container/detail/mpl.hpp>
// move
#include <boost/move/traits.hpp>
#include <boost/move/utility_core.hpp>
// move/detail
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
#include <boost/move/detail/move_helpers.hpp>
// intrusive/detail
#include <boost/intrusive/detail/minimal_pair_header.hpp>      //pair
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>//less, equal
// std
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace boost {
namespace container {

#if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
template <class Key, class Compare, class AllocatorOrContainer>
class flat_multiset;
#endif

//! flat_set is a Sorted Associative Container that stores objects of type Key.
//! It is also a Unique Associative Container, meaning that no two elements are the same.
//!
//! flat_set is similar to std::set but it's implemented by as an ordered sequence container.
//! The underlying sequence container is by default <i>vector</i> but it can also work
//! user-provided vector-like SequenceContainers (like <i>static_vector</i> or <i>small_vector</i>).
//!
//! Using vector-like sequence containers means that inserting a new element into a flat_set might invalidate
//! previous iterators and references (unless that sequence container is <i>stable_vector</i> or a similar
//! container that offers stable pointers and references). Similarly, erasing an element might invalidate
//! iterators and references pointing to elements that come after (their keys are bigger) the erased element.
//!
//! This container provides random-access iterators.
//!
//! \tparam Key is the type to be inserted in the set, which is also the key_type
//! \tparam Compare is the comparison functor used to order keys
//! \tparam AllocatorOrContainer is either:
//!   - The allocator to allocate <code>value_type</code>s (e.g. <i>allocator< std::pair<Key, T> > </i>).
//!     (in this case <i>sequence_type</i> will be vector<value_type, AllocatorOrContainer>)
//!   - The SequenceContainer to be used as the underlying <i>sequence_type</i>. It must be a vector-like
//!     sequence container with random-access iterators.
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template <class Key, class Compare = std::less<Key>, class AllocatorOrContainer = new_allocator<Key> >
#else
template <class Key, class Compare, class AllocatorOrContainer>
#endif
class flat_set
   ///@cond
   : public dtl::flat_tree<Key, dtl::identity<Key>, Compare, AllocatorOrContainer>
   ///@endcond
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(flat_set)
   typedef dtl::flat_tree<Key, dtl::identity<Key>, Compare, AllocatorOrContainer> tree_t;

   public:
   tree_t &tree()
   {  return *this;  }

   const tree_t &tree() const
   {  return *this;  }

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef Key                                                                      key_type;
   typedef Compare                                                                  key_compare;
   typedef Key                                                                      value_type;
   typedef typename BOOST_CONTAINER_IMPDEF(tree_t::sequence_type)                   sequence_type;
   typedef typename sequence_type::allocator_type                                   allocator_type;
   typedef ::boost::container::allocator_traits<allocator_type>                     allocator_traits_type;
   typedef typename sequence_type::pointer                                          pointer;
   typedef typename sequence_type::const_pointer                                    const_pointer;
   typedef typename sequence_type::reference                                        reference;
   typedef typename sequence_type::const_reference                                  const_reference;
   typedef typename sequence_type::size_type                                        size_type;
   typedef typename sequence_type::difference_type                                  difference_type;
   typedef typename BOOST_CONTAINER_IMPDEF(tree_t::stored_allocator_type)           stored_allocator_type;
   typedef typename BOOST_CONTAINER_IMPDEF(tree_t::value_compare)                   value_compare;

   typedef typename sequence_type::iterator                                         iterator;
   typedef typename sequence_type::const_iterator                                   const_iterator;
   typedef typename sequence_type::reverse_iterator                                 reverse_iterator;
   typedef typename sequence_type::const_reverse_iterator                           const_reverse_iterator;

   public:
   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs an empty container.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE
   flat_set() BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<AllocatorOrContainer>::value &&
                                dtl::is_nothrow_default_constructible<Compare>::value)
      : tree_t()
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified
   //! comparison object.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE
   explicit flat_set(const Compare& comp)
      : tree_t(comp)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE
   explicit flat_set(const allocator_type& a)
      : tree_t(a)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified
   //! comparison object and allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE
   flat_set(const Compare& comp, const allocator_type& a)
      : tree_t(comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty container and
   //! inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! comp and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_set(InputIterator first, InputIterator last)
      : tree_t(true, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! comp and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_set(InputIterator first, InputIterator last, const allocator_type& a)
      : tree_t(true, first, last, a)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! comp and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_set(InputIterator first, InputIterator last, const Compare& comp)
      : tree_t(true, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! comp and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_set(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : tree_t(true, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty container and
   //! inserts elements from the ordered unique range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_set(ordered_unique_range_t, InputIterator first, InputIterator last)
      : tree_t(ordered_unique_range, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! inserts elements from the ordered unique range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_set(ordered_unique_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : tree_t(ordered_unique_range, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! allocator, and inserts elements from the ordered unique range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_set(ordered_unique_range_t, InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : tree_t(ordered_unique_range, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified allocator and
   //! inserts elements from the ordered unique range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
      flat_set(ordered_unique_range_t, InputIterator first, InputIterator last, const allocator_type& a)
      : tree_t(ordered_unique_range, first, last, Compare(), a)
   {}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs an empty container and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! comp and otherwise N logN, where N is il.begin() - il.end().
   BOOST_CONTAINER_FORCEINLINE flat_set(std::initializer_list<value_type> il)
      : tree_t(true, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! comp and otherwise N logN, where N is il.begin() - il.end().
   BOOST_CONTAINER_FORCEINLINE flat_set(std::initializer_list<value_type> il, const allocator_type& a)
      : tree_t(true, il.begin(), il.end(), a)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! comp and otherwise N logN, where N is il.begin() - il.end().
   BOOST_CONTAINER_FORCEINLINE flat_set(std::initializer_list<value_type> il, const Compare& comp)
      : tree_t(true, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! comp and otherwise N logN, where N is il.begin() - il.end().
   BOOST_CONTAINER_FORCEINLINE flat_set(std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : tree_t(true, il.begin(), il.end(), comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_set(ordered_unique_range_t, std::initializer_list<value_type> il)
      : tree_t(ordered_unique_range, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_set(ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp)
      : tree_t(ordered_unique_range, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! allocator, and inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_set(ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : tree_t(ordered_unique_range, il.begin(), il.end(), comp, a)
   {}
#endif

   //! <b>Effects</b>: Copy constructs the container.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE flat_set(const flat_set& x)
      : tree_t(static_cast<const tree_t&>(x))
   {}

   //! <b>Effects</b>: Move constructs thecontainer. Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Postcondition</b>: x is emptied.
   BOOST_CONTAINER_FORCEINLINE flat_set(BOOST_RV_REF(flat_set) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      : tree_t(BOOST_MOVE_BASE(tree_t, x))
   {}

   //! <b>Effects</b>: Copy constructs a container using the specified allocator.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE flat_set(const flat_set& x, const allocator_type &a)
      : tree_t(static_cast<const tree_t&>(x), a)
   {}

   //! <b>Effects</b>: Move constructs a container using the specified allocator.
   //!                 Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise
   BOOST_CONTAINER_FORCEINLINE flat_set(BOOST_RV_REF(flat_set) x, const allocator_type &a)
      : tree_t(BOOST_MOVE_BASE(tree_t, x), a)
   {}

   //! <b>Effects</b>: Makes *this a copy of x.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE flat_set& operator=(BOOST_COPY_ASSIGN_REF(flat_set) x)
   {  return static_cast<flat_set&>(this->tree_t::operator=(static_cast<const tree_t&>(x)));  }

   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or value_type's move constructor throws)
   //!
   //! <b>Complexity</b>: Constant if allocator_traits_type::
   //!   propagate_on_container_move_assignment is true or
   //!   this->get>allocator() == x.get_allocator(). Linear otherwise.
   BOOST_CONTAINER_FORCEINLINE flat_set& operator=(BOOST_RV_REF(flat_set) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {  return static_cast<flat_set&>(this->tree_t::operator=(BOOST_MOVE_BASE(tree_t, x)));  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Copy all elements from il to *this.
   //!
   //! <b>Complexity</b>: Linear in il.size().
   flat_set& operator=(std::initializer_list<value_type> il)
   {
       this->clear();
       this->insert(il.begin(), il.end());
       return *this;
   }
#endif

   #ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
   //! <b>Effects</b>: Returns a copy of the allocator that
   //!   was passed to the object's constructor.
   //!
   //! <b>Complexity</b>: Constant.
   allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   stored_allocator_type &get_stored_allocator() BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   const stored_allocator_type &get_stored_allocator() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns an iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator begin() BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns an iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator end() BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns true if the container contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   bool empty() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns the number of the elements contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type size() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns the largest possible size of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Number of elements for which memory has been allocated.
   //!   capacity() is always greater than or equal to size().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type capacity() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: If n is less than or equal to capacity(), or the
   //!   underlying container has no `reserve` member, this call has no
   //!   effect. Otherwise, it is a request for allocation of additional memory.
   //!   If the request is successful, then capacity() is greater than or equal to
   //!   n; otherwise, capacity() is unchanged. In either case, size() is unchanged.
   //!
   //! <b>Throws</b>: If memory allocation allocation throws or T's copy constructor throws.
   //!
   //! <b>Note</b>: If capacity() is less than "cnt", iterators and references to
   //!   to values might be invalidated.
   void reserve(size_type cnt);

   //! <b>Effects</b>: Tries to deallocate the excess of memory created
   //    with previous allocations. The size of the vector is unchanged
   //!
   //! <b>Throws</b>: If memory allocation throws, or Key's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to size().
   void shrink_to_fit();

   #endif   //   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //////////////////////////////////////////////
   //
   //                modifiers
   //
   //////////////////////////////////////////////

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object x of type Key constructed with
   //!   std::forward<Args>(args)... if and only if there is no element in the container
   //!   with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> emplace(BOOST_FWD_REF(Args)... args)
   {  return this->tree_t::emplace_unique(boost::forward<Args>(args)...); }

   //! <b>Effects</b>: Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)... in the container if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant if x is inserted
   //!   right before p) plus insertion linear to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator p, BOOST_FWD_REF(Args)... args)
   {  return this->tree_t::emplace_hint_unique(p, boost::forward<Args>(args)...); }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_FLAT_SET_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> emplace(BOOST_MOVE_UREF##N)\
   {  return this->tree_t::emplace_unique(BOOST_MOVE_FWD##N);  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->tree_t::emplace_hint_unique(hint BOOST_MOVE_I##N BOOST_MOVE_FWD##N); }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_FLAT_SET_EMPLACE_CODE)
   #undef BOOST_CONTAINER_FLAT_SET_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts x if and only if there is no element in the container
   //!   with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   std::pair<iterator, bool> insert(const value_type &x);

   //! <b>Effects</b>: Inserts a new value_type move constructed from the pair if and
   //! only if there is no element in the container with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   std::pair<iterator, bool> insert(value_type &&x);
   #else
   private:
   typedef std::pair<iterator, bool> insert_return_pair;
   public:
   BOOST_MOVE_CONVERSION_AWARE_CATCH(insert, value_type, insert_return_pair, this->tree_t::insert_unique)
   #endif

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts a copy of x in the container if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant if x is inserted
   //!   right before p) plus insertion linear to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   iterator insert(const_iterator p, const value_type &x);

   //! <b>Effects</b>: Inserts an element move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant if x is inserted
   //!   right before p) plus insertion linear to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   iterator insert(const_iterator p, value_type &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, value_type, iterator, this->tree_t::insert_unique, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: N log(N).
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
      {  this->tree_t::insert_unique(first, last);  }

   //! <b>Requires</b>: first, last are not iterators into *this and
   //! must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Complexity</b>: Linear.
   //!
   //! <b>Note</b>: Non-standard extension. If an element is inserted it might invalidate elements.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(ordered_unique_range_t, InputIterator first, InputIterator last)
      {  this->tree_t::insert_unique(ordered_unique_range, first, last);  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: N log(N).
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->tree_t::insert_unique(il.begin(), il.end()); }

   //! <b>Requires</b>: Range [il.begin(), il.end()) must be ordered according to the predicate
   //! and must be unique values.
   //!
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()) .This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Complexity</b>: Linear.
   //!
   //! <b>Note</b>: Non-standard extension. If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE void insert(ordered_unique_range_t, std::initializer_list<value_type> il)
   {  this->tree_t::insert_unique(ordered_unique_range, il.begin(), il.end()); }
#endif

   //! @copydoc ::boost::container::flat_map::merge(flat_map<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(flat_set<Key, C2, AllocatorOrContainer>& source)
   {  this->tree_t::merge_unique(source.tree());   }

   //! @copydoc ::boost::container::flat_set::merge(flat_set<Key, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG flat_set<Key, C2, AllocatorOrContainer> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<flat_set<Key, C2, AllocatorOrContainer>&>(source));   }

   //! @copydoc ::boost::container::flat_map::merge(flat_multimap<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(flat_multiset<Key, C2, AllocatorOrContainer>& source)
   {  this->tree_t::merge_unique(source.tree());   }

   //! @copydoc ::boost::container::flat_set::merge(flat_multiset<Key, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG flat_multiset<Key, C2, AllocatorOrContainer> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<flat_multiset<Key, C2, AllocatorOrContainer>&>(source));   }

   //! <b>Effects</b>: If present, erases the element in the container with key equivalent to x.
   //!
   //! <b>Returns</b>: Returns the number of erased elements (0/1).
   //!
   //! <b>Complexity</b>: Logarithmic search time plus erasure time
   //!   linear to the elements with bigger keys.
   BOOST_CONTAINER_FORCEINLINE size_type erase(const key_type& x)
   {  return this->tree_t::erase_unique(x);   }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Erases the element pointed to by p.
   //!
   //! <b>Returns</b>: Returns an iterator pointing to the element immediately
   //!   following q prior to the element being erased. If no such element exists,
   //!   returns end().
   //!
   //! <b>Complexity</b>: Linear to the elements with keys bigger than p
   //!
   //! <b>Note</b>: Invalidates elements with keys
   //!   not less than the erased element.
   iterator erase(const_iterator p);

   //! <b>Effects</b>: Erases all the elements in the range [first, last).
   //!
   //! <b>Returns</b>: Returns last.
   //!
   //! <b>Complexity</b>: size()*N where N is the distance from first to last.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus erasure time
   //!   linear to the elements with bigger keys.
   iterator erase(const_iterator first, const_iterator last);

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   void swap(flat_set& x)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   //! <b>Effects</b>: erase(begin(),end()).
   //!
   //! <b>Postcondition</b>: size() == 0.
   //!
   //! <b>Complexity</b>: linear in size().
   void clear() BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Returns the comparison object out
   //!   of which a was constructed.
   //!
   //! <b>Complexity</b>: Constant.
   key_compare key_comp() const;

   //! <b>Effects</b>: Returns an object of value_compare constructed out
   //!   of the comparison object.
   //!
   //! <b>Complexity</b>: Constant.
   value_compare value_comp() const;

   //! <b>Returns</b>: An iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   iterator find(const key_type& x);

   //! <b>Returns</b>: A const_iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   const_iterator find(const key_type& x) const;

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<typename K>
   iterator find(const K& x);

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: A const_iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<typename K>
   const_iterator find(const K& x) const;

   //! <b>Requires</b>: size() >= n.
   //!
   //! <b>Effects</b>: Returns an iterator to the nth element
   //!   from the beginning of the container. Returns end()
   //!   if n == size().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension
   iterator nth(size_type n) BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Requires</b>: size() >= n.
   //!
   //! <b>Effects</b>: Returns a const_iterator to the nth element
   //!   from the beginning of the container. Returns end()
   //!   if n == size().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension
   const_iterator nth(size_type n) const BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Requires</b>: begin() <= p <= end().
   //!
   //! <b>Effects</b>: Returns the index of the element pointed by p
   //!   and size() if p == end().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension
   size_type index_of(iterator p) BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Requires</b>: begin() <= p <= end().
   //!
   //! <b>Effects</b>: Returns the index of the element pointed by p
   //!   and size() if p == end().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension
   size_type index_of(const_iterator p) const BOOST_NOEXCEPT_OR_NOTHROW;

   #else
   using tree_t::erase;
   #endif   //   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   BOOST_CONTAINER_FORCEINLINE size_type count(const key_type& x) const
   {  return static_cast<size_type>(this->tree_t::find(x) != this->tree_t::cend());  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   template<typename K>
   BOOST_CONTAINER_FORCEINLINE size_type count(const K& x) const
      //Don't use find() != end optimization here as transparent comparators with key K might
      //return a different range than key_type (which can only return a single element range)
   {  return this->tree_t::count(x);  }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Returns</b>: Returns true if there is an element with key
   //!   equivalent to key in the container, otherwise false.
   //!
   //! <b>Complexity</b>: log(size()).
   bool contains(const key_type& x) const;

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: Returns true if there is an element with key
   //!   equivalent to key in the container, otherwise false.
   //!
   //! <b>Complexity</b>: log(size()).
   template<typename K>
   bool contains(const K& x) const;

   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   iterator lower_bound(const key_type& x);

   //! <b>Returns</b>: A const iterator pointing to the first element with key not
   //!   less than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   const_iterator lower_bound(const key_type& x) const;

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   iterator lower_bound(const K& x);

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: A const iterator pointing to the first element with key not
   //!   less than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   const_iterator lower_bound(const K& x) const;

   //! <b>Returns</b>: An iterator pointing to the first element with key greater
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   iterator upper_bound(const key_type& x);

   //! <b>Returns</b>: A const iterator pointing to the first element with key 
   //!   greater than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   const_iterator upper_bound(const key_type& x) const;

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to the first element with key greater
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   iterator upper_bound(const K& x);

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: A const iterator pointing to the first element with key
   //!   greater than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   const_iterator upper_bound(const K& x) const;

   #endif   //   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_FORCEINLINE std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const
   {  return this->tree_t::lower_bound_range(x);  }

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,iterator> equal_range(const key_type& x)
   {  return this->tree_t::lower_bound_range(x);  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   std::pair<iterator,iterator> equal_range(const K& x)
      //Don't use lower_bound_range optimization here as transparent comparators with key K might
      //return a different range than key_type (which can only return a single element range)
   {  return this->tree_t::equal_range(x);  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   std::pair<const_iterator,const_iterator> equal_range(const K& x) const
      //Don't use lower_bound_range optimization here as transparent comparators with key K might
      //return a different range than key_type (which can only return a single element range)
   {  return this->tree_t::equal_range(x);  }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const flat_set& x, const flat_set& y);

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const flat_set& x, const flat_set& y);

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const flat_set& x, const flat_set& y);

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const flat_set& x, const flat_set& y);

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const flat_set& x, const flat_set& y);

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const flat_set& x, const flat_set& y);

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(flat_set& x, flat_set& y)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   //! <b>Effects</b>: Extracts the internal sequence container.
   //!
   //! <b>Complexity</b>: Same as the move constructor of sequence_type, usually constant.
   //!
   //! <b>Postcondition</b>: this->empty()
   //!
   //! <b>Throws</b>: If secuence_type's move constructor throws 
   sequence_type extract_sequence();

   #endif   //#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

   //! <b>Effects</b>: Discards the internally hold sequence container and adopts the
   //!   one passed externally using the move assignment. Erases non-unique elements.
   //!
   //! <b>Complexity</b>: Assuming O(1) move assignment, O(NlogN) with N = seq.size()
   //!
   //! <b>Throws</b>: If the comparison or the move constructor throws
   BOOST_CONTAINER_FORCEINLINE void adopt_sequence(BOOST_RV_REF(sequence_type) seq)
   {  this->tree_t::adopt_sequence_unique(boost::move(seq));  }

   //! <b>Requires</b>: seq shall be ordered according to this->compare()
   //!   and shall contain unique elements.
   //!
   //! <b>Effects</b>: Discards the internally hold sequence container and adopts the
   //!   one passed externally using the move assignment.
   //!
   //! <b>Complexity</b>: Assuming O(1) move assignment, O(1)
   //!
   //! <b>Throws</b>: If the move assignment throws
   BOOST_CONTAINER_FORCEINLINE void adopt_sequence(ordered_unique_range_t, BOOST_RV_REF(sequence_type) seq)
   {  this->tree_t::adopt_sequence_unique(ordered_unique_range_t(), boost::move(seq));  }
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
flat_set(InputIterator, InputIterator) ->
   flat_set< it_based_value_type_t<InputIterator> >;

template < typename InputIterator, typename AllocatorOrCompare>
    flat_set(InputIterator, InputIterator, AllocatorOrCompare const&) ->
    flat_set< it_based_value_type_t<InputIterator>
            , typename dtl::if_c< // Compare
                dtl::is_allocator<AllocatorOrCompare>::value
                , std::less<it_based_value_type_t<InputIterator>>
                , AllocatorOrCompare
            >::type
            , typename dtl::if_c< // Allocator
                dtl::is_allocator<AllocatorOrCompare>::value
                , AllocatorOrCompare
                , new_allocator<it_based_value_type_t<InputIterator>>
                >::type
            >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
flat_set(InputIterator, InputIterator, Compare const&, Allocator const&) ->
   flat_set< it_based_value_type_t<InputIterator>
           , Compare
           , Allocator>;

template <typename InputIterator>
flat_set(ordered_unique_range_t, InputIterator, InputIterator) ->
   flat_set< it_based_value_type_t<InputIterator>>;


template < typename InputIterator, typename AllocatorOrCompare>
    flat_set(ordered_unique_range_t, InputIterator, InputIterator, AllocatorOrCompare const&) ->
    flat_set< it_based_value_type_t<InputIterator>
            , typename dtl::if_c< // Compare
                dtl::is_allocator<AllocatorOrCompare>::value
                , std::less<it_based_value_type_t<InputIterator>>
                , AllocatorOrCompare
            >::type
            , typename dtl::if_c< // Allocator
                dtl::is_allocator<AllocatorOrCompare>::value
                , AllocatorOrCompare
                , new_allocator<it_based_value_type_t<InputIterator>>
                >::type
            >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
flat_set(ordered_unique_range_t, InputIterator, InputIterator, Compare const&, Allocator const&) ->
   flat_set< it_based_value_type_t<InputIterator>
           , Compare
           , Allocator>;

#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class Compare, class AllocatorOrContainer>
struct has_trivial_destructor_after_move<boost::container::flat_set<Key, Compare, AllocatorOrContainer> >
{
   typedef ::boost::container::dtl::flat_tree<Key, ::boost::container::dtl::identity<Key>, Compare, AllocatorOrContainer> tree;
   static const bool value = ::boost::has_trivial_destructor_after_move<tree>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! flat_multiset is a Sorted Associative Container that stores objects of type Key and
//! can store multiple copies of the same key value.
//!
//! flat_multiset is similar to std::multiset but it's implemented by as an ordered sequence container.
//! The underlying sequence container is by default <i>vector</i> but it can also work
//! user-provided vector-like SequenceContainers (like <i>static_vector</i> or <i>small_vector</i>).
//!
//! Using vector-like sequence containers means that inserting a new element into a flat_multiset might invalidate
//! previous iterators and references (unless that sequence container is <i>stable_vector</i> or a similar
//! container that offers stable pointers and references). Similarly, erasing an element might invalidate
//! iterators and references pointing to elements that come after (their keys are bigger) the erased element.
//!
//! This container provides random-access iterators.
//!
//! \tparam Key is the type to be inserted in the multiset, which is also the key_type
//! \tparam Compare is the comparison functor used to order keys
//! \tparam AllocatorOrContainer is either:
//!   - The allocator to allocate <code>value_type</code>s (e.g. <i>allocator< std::pair<Key, T> > </i>).
//!     (in this case <i>sequence_type</i> will be vector<value_type, AllocatorOrContainer>)
//!   - The SequenceContainer to be used as the underlying <i>sequence_type</i>. It must be a vector-like
//!     sequence container with random-access iterators.
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template <class Key, class Compare = std::less<Key>, class AllocatorOrContainer = new_allocator<Key> >
#else
template <class Key, class Compare, class AllocatorOrContainer>
#endif
class flat_multiset
   ///@cond
   : public dtl::flat_tree<Key, dtl::identity<Key>, Compare, AllocatorOrContainer>
   ///@endcond
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(flat_multiset)
   typedef dtl::flat_tree<Key, dtl::identity<Key>, Compare, AllocatorOrContainer> tree_t;

   public:
   tree_t &tree()
   {  return *this;  }

   const tree_t &tree() const
   {  return *this;  }
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef Key                                                                      key_type;
   typedef Compare                                                                  key_compare;
   typedef Key                                                                      value_type;
   typedef typename BOOST_CONTAINER_IMPDEF(tree_t::sequence_type)                   sequence_type;
   typedef typename sequence_type::allocator_type                                   allocator_type;
   typedef ::boost::container::allocator_traits<allocator_type>                     allocator_traits_type;
   typedef typename sequence_type::pointer                                          pointer;
   typedef typename sequence_type::const_pointer                                    const_pointer;
   typedef typename sequence_type::reference                                        reference;
   typedef typename sequence_type::const_reference                                  const_reference;
   typedef typename sequence_type::size_type                                        size_type;
   typedef typename sequence_type::difference_type                                  difference_type;
   typedef typename BOOST_CONTAINER_IMPDEF(tree_t::stored_allocator_type)           stored_allocator_type;
   typedef typename BOOST_CONTAINER_IMPDEF(tree_t::value_compare)                   value_compare;

   typedef typename sequence_type::iterator                                         iterator;
   typedef typename sequence_type::const_iterator                                   const_iterator;
   typedef typename sequence_type::reverse_iterator                                 reverse_iterator;
   typedef typename sequence_type::const_reverse_iterator                           const_reverse_iterator;

   //! @copydoc ::boost::container::flat_set::flat_set()
   BOOST_CONTAINER_FORCEINLINE flat_multiset() BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<AllocatorOrContainer>::value &&
                                                                 dtl::is_nothrow_default_constructible<Compare>::value)
      : tree_t()
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(const Compare&)
   BOOST_CONTAINER_FORCEINLINE explicit flat_multiset(const Compare& comp)
      : tree_t(comp)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE explicit flat_multiset(const allocator_type& a)
      : tree_t(a)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(const Compare&, const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(const Compare& comp, const allocator_type& a)
      : tree_t(comp, a)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(InputIterator, InputIterator)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_multiset(InputIterator first, InputIterator last)
      : tree_t(false, first, last)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(InputIterator, InputIterator, const allocator_type&)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_multiset(InputIterator first, InputIterator last, const allocator_type& a)
      : tree_t(false, first, last, a)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(InputIterator, InputIterator, const Compare& comp)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_multiset(InputIterator first, InputIterator last, const Compare& comp)
      : tree_t(false, first, last, comp)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(InputIterator, InputIterator, const Compare& comp, const allocator_type&)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_multiset(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : tree_t(false, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multiset and
   //! inserts elements from the ordered range [first ,last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_multiset(ordered_range_t, InputIterator first, InputIterator last)
      : tree_t(ordered_range, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multiset using the specified comparison object and
   //! inserts elements from the ordered range [first ,last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_multiset(ordered_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : tree_t(ordered_range, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multiset using the specified comparison object and
   //! allocator, and inserts elements from the ordered range [first, last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_multiset(ordered_range_t, InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : tree_t(ordered_range, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multiset using the specified allocator and
   //! inserts elements from the ordered range [first ,last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_multiset(ordered_range_t, InputIterator first, InputIterator last, const allocator_type &a)
      : tree_t(ordered_range, first, last, Compare(), a)
   {}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::boost::container::flat_set::flat_set(std::initializer_list<value_type)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(std::initializer_list<value_type> il)
      : tree_t(false, il.begin(), il.end())
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(std::initializer_list<value_type>, const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(std::initializer_list<value_type> il, const allocator_type& a)
      : tree_t(false, il.begin(), il.end(), a)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(std::initializer_list<value_type>, const Compare& comp)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(std::initializer_list<value_type> il, const Compare& comp)
      : tree_t(false, il.begin(), il.end(), comp)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(std::initializer_list<value_type>, const Compare& comp, const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : tree_t(false, il.begin(), il.end(), comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty containerand
   //! inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_multiset(ordered_range_t, std::initializer_list<value_type> il)
      : tree_t(ordered_range, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_multiset(ordered_range_t, std::initializer_list<value_type> il, const Compare& comp)
      : tree_t(ordered_range, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty container using the specified comparison object and
   //! allocator, and inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_multiset(ordered_range_t, std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : tree_t(ordered_range, il.begin(), il.end(), comp, a)
   {}
#endif

   //! @copydoc ::boost::container::flat_set::flat_set(const flat_set &)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(const flat_multiset& x)
      : tree_t(static_cast<const tree_t&>(x))
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(flat_set &&)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(BOOST_RV_REF(flat_multiset) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      : tree_t(boost::move(static_cast<tree_t&>(x)))
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(const flat_set &, const allocator_type &)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(const flat_multiset& x, const allocator_type &a)
      : tree_t(static_cast<const tree_t&>(x), a)
   {}

   //! @copydoc ::boost::container::flat_set::flat_set(flat_set &&, const allocator_type &)
   BOOST_CONTAINER_FORCEINLINE flat_multiset(BOOST_RV_REF(flat_multiset) x, const allocator_type &a)
      : tree_t(BOOST_MOVE_BASE(tree_t, x), a)
   {}

   //! @copydoc ::boost::container::flat_set::operator=(const flat_set &)
   BOOST_CONTAINER_FORCEINLINE flat_multiset& operator=(BOOST_COPY_ASSIGN_REF(flat_multiset) x)
   {  return static_cast<flat_multiset&>(this->tree_t::operator=(static_cast<const tree_t&>(x)));  }

   //! @copydoc ::boost::container::flat_set::operator=(flat_set &&)
   BOOST_CONTAINER_FORCEINLINE flat_multiset& operator=(BOOST_RV_REF(flat_multiset) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {  return static_cast<flat_multiset&>(this->tree_t::operator=(BOOST_MOVE_BASE(tree_t, x)));  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::boost::container::flat_set::operator=(std::initializer_list<value_type>)
   flat_multiset& operator=(std::initializer_list<value_type> il)
   {
       this->clear();
       this->insert(il.begin(), il.end());
       return *this;
   }
#endif

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! @copydoc ::boost::container::flat_set::get_allocator()
   allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::get_stored_allocator()
   stored_allocator_type &get_stored_allocator() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::get_stored_allocator() const
   const stored_allocator_type &get_stored_allocator() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::begin()
   iterator begin() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::begin() const
   const_iterator begin() const;

   //! @copydoc ::boost::container::flat_set::cbegin() const
   const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::end()
   iterator end() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::end() const
   const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::cend() const
   const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::rbegin() const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::crbegin() const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::rend()
   reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::rend() const
   const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::crend() const
   const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::empty() const
   bool empty() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::size() const
   size_type size() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::max_size() const
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::capacity() const
   size_type capacity() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::reserve(size_type)
   void reserve(size_type cnt);

   //! @copydoc ::boost::container::flat_set::shrink_to_fit()
   void shrink_to_fit();

   #endif   //   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //////////////////////////////////////////////
   //
   //                modifiers
   //
   //////////////////////////////////////////////

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)... and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace(BOOST_FWD_REF(Args)... args)
   {  return this->tree_t::emplace_equal(boost::forward<Args>(args)...); }

   //! <b>Effects</b>: Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)... in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant if x is inserted
   //!   right before p) plus insertion linear to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator p, BOOST_FWD_REF(Args)... args)
   {  return this->tree_t::emplace_hint_equal(p, boost::forward<Args>(args)...); }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_FLAT_MULTISET_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace(BOOST_MOVE_UREF##N)\
   {  return this->tree_t::emplace_equal(BOOST_MOVE_FWD##N);  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->tree_t::emplace_hint_equal(hint BOOST_MOVE_I##N BOOST_MOVE_FWD##N); }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_FLAT_MULTISET_EMPLACE_CODE)
   #undef BOOST_CONTAINER_FLAT_MULTISET_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts x and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   iterator insert(const value_type &x);

   //! <b>Effects</b>: Inserts a new value_type move constructed from x
   //!   and returns the iterator pointing to the newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   iterator insert(value_type &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH(insert, value_type, iterator, this->tree_t::insert_equal)
   #endif

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant if x is inserted
   //!   right before p) plus insertion linear to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   iterator insert(const_iterator p, const value_type &x);

   //! <b>Effects</b>: Inserts a new value move constructed  from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant if x is inserted
   //!   right before p) plus insertion linear to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   iterator insert(const_iterator p, value_type &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, value_type, iterator, this->tree_t::insert_equal, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .
   //!
   //! <b>Complexity</b>: N log(N).
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
      {  this->tree_t::insert_equal(first, last);  }

   //! <b>Requires</b>: first, last are not iterators into *this and
   //! must be ordered according to the predicate.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Complexity</b>: Linear.
   //!
   //! <b>Note</b>: Non-standard extension. If an element is inserted it might invalidate elements.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(ordered_range_t, InputIterator first, InputIterator last)
      {  this->tree_t::insert_equal(ordered_range, first, last);  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: N log(N).
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->tree_t::insert_equal(il.begin(), il.end()); }

   //! <b>Requires</b>: Range [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Complexity</b>: Linear.
   //!
   //! <b>Note</b>: Non-standard extension. If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE void insert(ordered_range_t, std::initializer_list<value_type> il)
   {  this->tree_t::insert_equal(ordered_range, il.begin(), il.end()); }
#endif

   //! @copydoc ::boost::container::flat_multimap::merge(flat_multimap<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(flat_multiset<Key, C2, AllocatorOrContainer>& source)
   {  this->tree_t::merge_equal(source.tree());   }

   //! @copydoc ::boost::container::flat_multiset::merge(flat_multiset<Key, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG flat_multiset<Key, C2, AllocatorOrContainer> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<flat_multiset<Key, C2, AllocatorOrContainer>&>(source));   }

   //! @copydoc ::boost::container::flat_multimap::merge(flat_map<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(flat_set<Key, C2, AllocatorOrContainer>& source)
   {  this->tree_t::merge_equal(source.tree());   }

   //! @copydoc ::boost::container::flat_multiset::merge(flat_set<Key, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG flat_set<Key, C2, AllocatorOrContainer> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<flat_set<Key, C2, AllocatorOrContainer>&>(source));   }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! @copydoc ::boost::container::flat_set::erase(const_iterator)
   iterator erase(const_iterator p);

   //! @copydoc ::boost::container::flat_set::erase(const key_type&)
   size_type erase(const key_type& x);

   //! @copydoc ::boost::container::flat_set::erase(const_iterator,const_iterator)
   iterator erase(const_iterator first, const_iterator last);

   //! @copydoc ::boost::container::flat_set::swap
   void swap(flat_multiset& x)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   //! @copydoc ::boost::container::flat_set::clear
   void clear() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::key_comp
   key_compare key_comp() const;

   //! @copydoc ::boost::container::flat_set::value_comp
   value_compare value_comp() const;

   //! @copydoc ::boost::container::flat_set::find(const key_type& )
   iterator find(const key_type& x);

   //! @copydoc ::boost::container::flat_set::find(const key_type& ) const
   const_iterator find(const key_type& x) const;

   //! @copydoc ::boost::container::flat_set::nth(size_type)
   iterator nth(size_type n) BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::nth(size_type) const
   const_iterator nth(size_type n) const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::index_of(iterator)
   size_type index_of(iterator p) BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::index_of(const_iterator) const
   size_type index_of(const_iterator p) const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::flat_set::count(const key_type& ) const
   size_type count(const key_type& x) const;

   //! @copydoc ::boost::container::flat_set::contains(const key_type& ) const
   bool contains(const key_type& x) const;

   //! @copydoc ::boost::container::flat_set::contains(const K& ) const
   template<typename K>
   bool contains(const K& x) const;

   //! @copydoc ::boost::container::flat_set::lower_bound(const key_type& )
   iterator lower_bound(const key_type& x);

   //! @copydoc ::boost::container::flat_set::lower_bound(const key_type& ) const
   const_iterator lower_bound(const key_type& x) const;

   //! @copydoc ::boost::container::flat_set::upper_bound(const key_type& )
   iterator upper_bound(const key_type& x);

   //! @copydoc ::boost::container::flat_set::upper_bound(const key_type& ) const
   const_iterator upper_bound(const key_type& x) const;

   //! @copydoc ::boost::container::flat_set::equal_range(const key_type& ) const
   std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const;

   //! @copydoc ::boost::container::flat_set::equal_range(const key_type& )
   std::pair<iterator,iterator> equal_range(const key_type& x);

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const flat_multiset& x, const flat_multiset& y);

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const flat_multiset& x, const flat_multiset& y);

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const flat_multiset& x, const flat_multiset& y);

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const flat_multiset& x, const flat_multiset& y);

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const flat_multiset& x, const flat_multiset& y);

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const flat_multiset& x, const flat_multiset& y);

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(flat_multiset& x, flat_multiset& y)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   //! <b>Effects</b>: Extracts the internal sequence container.
   //!
   //! <b>Complexity</b>: Same as the move constructor of sequence_type, usually constant.
   //!
   //! <b>Postcondition</b>: this->empty()
   //!
   //! <b>Throws</b>: If secuence_type's move constructor throws 
   sequence_type extract_sequence();

   #endif   //#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

   //! <b>Effects</b>: Discards the internally hold sequence container and adopts the
   //!   one passed externally using the move assignment.
   //!
   //! <b>Complexity</b>: Assuming O(1) move assignment, O(NlogN) with N = seq.size()
   //!
   //! <b>Throws</b>: If the comparison or the move constructor throws
   BOOST_CONTAINER_FORCEINLINE void adopt_sequence(BOOST_RV_REF(sequence_type) seq)
   {  this->tree_t::adopt_sequence_equal(boost::move(seq));  }

   //! <b>Requires</b>: seq shall be ordered according to this->compare()
   //!
   //! <b>Effects</b>: Discards the internally hold sequence container and adopts the
   //!   one passed externally using the move assignment.
   //!
   //! <b>Complexity</b>: Assuming O(1) move assignment, O(1)
   //!
   //! <b>Throws</b>: If the move assignment throws
   BOOST_CONTAINER_FORCEINLINE void adopt_sequence(ordered_range_t, BOOST_RV_REF(sequence_type) seq)
   {  this->tree_t::adopt_sequence_equal(ordered_range_t(), boost::move(seq));  }
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
flat_multiset(InputIterator, InputIterator) ->
   flat_multiset< it_based_value_type_t<InputIterator> >;


template < typename InputIterator, typename AllocatorOrCompare>
flat_multiset(InputIterator, InputIterator, AllocatorOrCompare const&) ->
    flat_multiset < it_based_value_type_t<InputIterator>
                  , typename dtl::if_c< // Compare
                      dtl::is_allocator<AllocatorOrCompare>::value
                      , std::less<it_based_value_type_t<InputIterator>>
                      , AllocatorOrCompare
                  >::type
                  , typename dtl::if_c< // Allocator
                      dtl::is_allocator<AllocatorOrCompare>::value
                      , AllocatorOrCompare
                      , new_allocator<it_based_value_type_t<InputIterator>>
                      >::type
                  >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
flat_multiset(InputIterator, InputIterator, Compare const&, Allocator const&) ->
   flat_multiset< it_based_value_type_t<InputIterator>
           , Compare
           , Allocator>;

template <typename InputIterator>
flat_multiset(ordered_range_t, InputIterator, InputIterator) ->
   flat_multiset< it_based_value_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
flat_multiset(ordered_range_t, InputIterator, InputIterator, AllocatorOrCompare const&) ->
    flat_multiset < it_based_value_type_t<InputIterator>
                  , typename dtl::if_c< // Compare
                      dtl::is_allocator<AllocatorOrCompare>::value
                      , std::less<it_based_value_type_t<InputIterator>>
                      , AllocatorOrCompare
                  >::type
                  , typename dtl::if_c< // Allocator
                      dtl::is_allocator<AllocatorOrCompare>::value
                      , AllocatorOrCompare
                      , new_allocator<it_based_value_type_t<InputIterator>>
                      >::type
                  >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
flat_multiset(ordered_range_t, InputIterator, InputIterator, Compare const&, Allocator const&) ->
   flat_multiset< it_based_value_type_t<InputIterator>
           , Compare
           , Allocator>;

#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class Compare, class AllocatorOrContainer>
struct has_trivial_destructor_after_move<boost::container::flat_multiset<Key, Compare, AllocatorOrContainer> >
{
   typedef ::boost::container::dtl::flat_tree<Key, ::boost::container::dtl::identity<Key>, Compare, AllocatorOrContainer> tree;
   static const bool value = ::boost::has_trivial_destructor_after_move<tree>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}}

#include <boost/container/detail/config_end.hpp>

#endif   // BOOST_CONTAINER_FLAT_SET_HPP

/* flat_set.hpp
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
*/