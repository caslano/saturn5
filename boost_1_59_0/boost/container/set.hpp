//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_SET_HPP
#define BOOST_CONTAINER_SET_HPP

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
// container/detail
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/tree.hpp>
#include <boost/container/new_allocator.hpp> //new_allocator
// intrusive/detail
#include <boost/intrusive/detail/minimal_pair_header.hpp>      //pair
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>//less, equal
// move
#include <boost/move/traits.hpp>
#include <boost/move/utility_core.hpp>
// move/detail
#include <boost/move/detail/move_helpers.hpp>
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
// std
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace boost {
namespace container {

#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

//! A set is a kind of associative container that supports unique keys (contains at
//! most one of each key value) and provides for fast retrieval of the keys themselves.
//! Class set supports bidirectional iterators.
//!
//! A set satisfies all of the requirements of a container and of a reversible container
//! , and of an associative container. A set also provides most operations described in
//! for unique keys.
//!
//! \tparam Key is the type to be inserted in the set, which is also the key_type
//! \tparam Compare is the comparison functor used to order keys
//! \tparam Allocator is the allocator to be used to allocate memory for this container
//! \tparam Options is an packed option type generated using using boost::container::tree_assoc_options.
template <class Key, class Compare = std::less<Key>, class Allocator = new_allocator<Key>, class Options = void>
#else
template <class Key, class Compare, class Allocator, class Options>
#endif
class set
   ///@cond
   : public dtl::tree
      < Key, void, Compare, Allocator, Options>
   ///@endcond
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(set)
   typedef dtl::tree
      < Key, void, Compare, Allocator, Options> base_t;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef Key                                                                            key_type;
   typedef Key                                                                            value_type;
   typedef Compare                                                                        key_compare;
   typedef key_compare                                                                    value_compare;
   typedef typename base_t::allocator_type                                                allocator_type;
   typedef ::boost::container::allocator_traits<allocator_type>                           allocator_traits_type;
   typedef typename ::boost::container::allocator_traits<allocator_type>::pointer         pointer;
   typedef typename ::boost::container::allocator_traits<allocator_type>::const_pointer   const_pointer;
   typedef typename ::boost::container::allocator_traits<allocator_type>::reference       reference;
   typedef typename ::boost::container::allocator_traits<allocator_type>::const_reference const_reference;
   typedef typename ::boost::container::allocator_traits<allocator_type>::size_type       size_type;
   typedef typename ::boost::container::allocator_traits<allocator_type>::difference_type difference_type;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::stored_allocator_type)                 stored_allocator_type;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::iterator)                              iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::const_iterator)                        const_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::reverse_iterator)                      reverse_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::const_reverse_iterator)                const_reverse_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::node_type)                             node_type;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::insert_return_type)                    insert_return_type;

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs an empty set.
   //!
   //! <b>Complexity</b>: Constant.
   
   BOOST_CONTAINER_FORCEINLINE set()
      BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<allocator_type>::value &&
                        dtl::is_nothrow_default_constructible<Compare>::value)
      : base_t()
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified allocator object.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit set(const allocator_type& a)
      : base_t(a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit set(const Compare& comp)
      : base_t(comp)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object
   //! and allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE set(const Compare& comp, const allocator_type& a)
      : base_t(comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty set using and
   //! inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE set(InputIterator first, InputIterator last)
      : base_t(true, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE set(InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(true, first, last, key_compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE set(InputIterator first, InputIterator last, const Compare& comp)
      : base_t(true, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE set(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : base_t(true, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty set and
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
   BOOST_CONTAINER_FORCEINLINE set( ordered_unique_range_t, InputIterator first, InputIterator last)
      : base_t(ordered_range, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
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
   BOOST_CONTAINER_FORCEINLINE set( ordered_unique_range_t, InputIterator first, InputIterator last, const Compare& comp )
      : base_t(ordered_range, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
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
   BOOST_CONTAINER_FORCEINLINE set( ordered_unique_range_t, InputIterator first, InputIterator last
      , const Compare& comp, const allocator_type& a)
      : base_t(ordered_range, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified allocator and
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
   BOOST_CONTAINER_FORCEINLINE set(ordered_unique_range_t, InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(ordered_range, first, last, Compare(), a)
   {}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs an empty set and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is il.begin() - il.end().
   BOOST_CONTAINER_FORCEINLINE set(std::initializer_list<value_type> il)
      : base_t(true, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is il.begin() - il.end().
   BOOST_CONTAINER_FORCEINLINE set(std::initializer_list<value_type> il, const allocator_type& a)
      : base_t(true, il.begin(), il.end(), Compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is il.begin() - il.end().
   BOOST_CONTAINER_FORCEINLINE set(std::initializer_list<value_type> il, const Compare& comp )
      : base_t(true, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is il.begin() - il.end().
   BOOST_CONTAINER_FORCEINLINE set(std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : base_t(true, il.begin(), il.end(), comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty set and
   //! inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE set( ordered_unique_range_t, std::initializer_list<value_type> il)
      : base_t(ordered_range, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE set( ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp)
      : base_t(ordered_range, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty set using the specified comparison object and
   //! allocator, and inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE set( ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : base_t(ordered_range, il.begin(), il.end(), comp, a)
   {}
#endif

   //! <b>Effects</b>: Copy constructs a set.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE set(const set& x)
      : base_t(static_cast<const base_t&>(x))
   {}

   //! <b>Effects</b>: Move constructs a set. Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Postcondition</b>: x is emptied.
   BOOST_CONTAINER_FORCEINLINE set(BOOST_RV_REF(set) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      : base_t(BOOST_MOVE_BASE(base_t, x))
   {}

   //! <b>Effects</b>: Copy constructs a set using the specified allocator.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE set(const set& x, const allocator_type &a)
      : base_t(static_cast<const base_t&>(x), a)
   {}

   //! <b>Effects</b>: Move constructs a set using the specified allocator.
   //!                 Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise.
   BOOST_CONTAINER_FORCEINLINE set(BOOST_RV_REF(set) x, const allocator_type &a)
      : base_t(BOOST_MOVE_BASE(base_t, x), a)
   {}

   //! <b>Effects</b>: Makes *this a copy of x.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE set& operator=(BOOST_COPY_ASSIGN_REF(set) x)
   {  return static_cast<set&>(this->base_t::operator=(static_cast<const base_t&>(x)));  }

   //! <b>Effects</b>: this->swap(x.get()).
   //!
   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or value_type's move constructor throws)
   //!
   //! <b>Complexity</b>: Constant if allocator_traits_type::
   //!   propagate_on_container_move_assignment is true or
   //!   this->get>allocator() == x.get_allocator(). Linear otherwise.
   BOOST_CONTAINER_FORCEINLINE set& operator=(BOOST_RV_REF(set) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {  return static_cast<set&>(this->base_t::operator=(BOOST_MOVE_BASE(base_t, x)));  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Copy all elements from il to *this.
   //!
   //! <b>Complexity</b>: Linear in il.size().
   set& operator=(std::initializer_list<value_type> il)
   {
      this->clear();
      insert(il.begin(), il.end());
      return *this;
   }
#endif

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Returns a copy of the allocator that
   //!   was passed to the object's constructor.
   //!
   //! <b>Complexity</b>: Constant.
   allocator_type get_allocator() const;

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   stored_allocator_type &get_stored_allocator();

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   const stored_allocator_type &get_stored_allocator() const;

   //! <b>Effects</b>: Returns an iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant
   iterator begin();

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator begin() const;

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cbegin() const;

   //! <b>Effects</b>: Returns an iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator end();

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator end() const;

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cend() const;

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rbegin();

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rbegin() const;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crbegin() const;

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rend();

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rend() const;

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crend() const;

   //! <b>Effects</b>: Returns true if the container contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   bool empty() const;

   //! <b>Effects</b>: Returns the number of the elements contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type size() const;

   //! <b>Effects</b>: Returns the largest possible size of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type max_size() const;
   #endif   //   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>:  Inserts an object x of type Key constructed with
   //!   std::forward<Args>(args)... if and only if there is
   //!   no element in the container with equivalent value.
   //!   and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   Key's in-place constructor throws.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> emplace(BOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_unique(boost::forward<Args>(args)...); }

   //! <b>Effects</b>:  Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)... if and only if there is
   //!   no element in the container with equivalent value.
   //!   p is a hint pointing to where the insert
   //!   should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator p, BOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_hint_unique(p, boost::forward<Args>(args)...); }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_SET_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> emplace(BOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_unique(BOOST_MOVE_FWD##N);  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_hint_unique(hint BOOST_MOVE_I##N BOOST_MOVE_FWD##N); }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_SET_EMPLACE_CODE)
   #undef BOOST_CONTAINER_SET_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts x if and only if there is no element in the container
   //!   with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   std::pair<iterator, bool> insert(const value_type &x);

   //! <b>Effects</b>: Move constructs a new value from x if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   std::pair<iterator, bool> insert(value_type &&x);
   #else
   private:
   typedef std::pair<iterator, bool> insert_return_pair;
   public:
   BOOST_MOVE_CONVERSION_AWARE_CATCH
      (insert, value_type, insert_return_pair, this->base_t::insert_unique_convertible)
   #endif

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts a copy of x in the container if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   iterator insert(const_iterator p, const value_type &x);

   //! <b>Effects</b>: Inserts an element move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   iterator insert(const_iterator p, value_type &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG
      (insert, value_type, iterator, this->base_t::insert_unique_hint_convertible, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from first to last)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
   {  this->base_t::insert_unique_range(first, last);  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(),il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from il.begin() to il.end())
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_unique_range(il.begin(), il.end()); }
#endif

   //! @copydoc ::boost::container::map::insert(node_type&&)
   BOOST_CONTAINER_FORCEINLINE insert_return_type insert(BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {  return this->base_t::insert_unique_node(boost::move(nh));  }

   //! @copydoc ::boost::container::map::insert(const_iterator, node_type&&)
   BOOST_CONTAINER_FORCEINLINE insert_return_type insert(const_iterator hint, BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {  return this->base_t::insert_unique_node(hint, boost::move(nh));  }

   //! @copydoc ::boost::container::map::merge(map<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(set<Key, C2, Allocator, Options>& source)
   {
      typedef dtl::tree
         <Key, void, C2, Allocator, Options> base2_t;
      this->base_t::merge_unique(static_cast<base2_t&>(source));
   }

   //! @copydoc ::boost::container::set::merge(set<Key, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG set<Key, C2, Allocator, Options> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<set<Key, C2, Allocator, Options>&>(source));   }

   //! @copydoc ::boost::container::map::merge(multimap<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(multiset<Key, C2, Allocator, Options>& source)
   {
      typedef dtl::tree
         <Key, void, C2, Allocator, Options> base2_t;
      this->base_t::merge_unique(static_cast<base2_t&>(source));
   }

   //! @copydoc ::boost::container::set::merge(multiset<Key, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG multiset<Key, C2, Allocator, Options> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<multiset<Key, C2, Allocator, Options>&>(source));   }

   //! <b>Effects</b>: If present, erases the element in the container with key equivalent to x.
   //!
   //! <b>Returns</b>: Returns the number of erased elements (0/1).
   //!
   //! <b>Complexity</b>: log(size()) + count(k)
   BOOST_CONTAINER_FORCEINLINE size_type erase(const key_type& x)
   {  return this->base_t::erase_unique(x);   }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Erases the element pointed to by p.
   //!
   //! <b>Returns</b>: Returns an iterator pointing to the element immediately
   //!   following q prior to the element being erased. If no such element exists,
   //!   returns end().
   //!
   //! <b>Complexity</b>: Amortized constant time
   iterator erase(const_iterator p);

   //! <b>Effects</b>: Erases all the elements in the range [first, last).
   //!
   //! <b>Returns</b>: Returns last.
   //!
   //! <b>Complexity</b>: log(size())+N where N is the distance from first to last.
   iterator erase(const_iterator first, const_iterator last);

   //! @copydoc ::boost::container::map::extract(const_iterator)
   node_type extract(const_iterator p);

   //! @copydoc ::boost::container::map::extract(const key_type&)
   node_type extract(const key_type& x);

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   void swap(set& x)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   //! <b>Effects</b>: erase(begin(),end()).
   //!
   //! <b>Postcondition</b>: size() == 0.
   //!
   //! <b>Complexity</b>: linear in size().
   void clear();

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

   #else
   using base_t::erase;
   #endif   //   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type count(const key_type& x) const
   {  return static_cast<size_type>(this->base_t::find(x) != this->base_t::cend());  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   template<typename K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type count(const K& x) const
   {  return static_cast<size_type>(this->find(x) != this->cend());  }

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

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,iterator> equal_range(const key_type& x)
   {  return this->base_t::lower_bound_range(x);  }

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_FORCEINLINE std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const
   {  return this->base_t::lower_bound_range(x);  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,iterator> equal_range(const K& x)
   {  return this->base_t::lower_bound_range(x);  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   BOOST_CONTAINER_FORCEINLINE std::pair<const_iterator,const_iterator> equal_range(const K& x) const
   {  return this->base_t::lower_bound_range(x);  }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Rebalances the tree. It's a no-op for Red-Black and AVL trees.
   //!
   //! <b>Complexity</b>: Linear
   void rebalance();

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const set& x, const set& y);

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const set& x, const set& y);

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(set& x, set& y)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
set(InputIterator, InputIterator) ->
   set< it_based_value_type_t<InputIterator> >;

template < typename InputIterator, typename AllocatorOrCompare>
    set(InputIterator, InputIterator, AllocatorOrCompare const&) ->
    set< it_based_value_type_t<InputIterator>
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
set(InputIterator, InputIterator, Compare const&, Allocator const&) ->
   set< it_based_value_type_t<InputIterator>
           , Compare
           , Allocator>;

template <typename InputIterator>
set(ordered_unique_range_t, InputIterator, InputIterator) ->
   set< it_based_value_type_t<InputIterator>>;


template < typename InputIterator, typename AllocatorOrCompare>
    set(ordered_unique_range_t, InputIterator, InputIterator, AllocatorOrCompare const&) ->
    set< it_based_value_type_t<InputIterator>
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
set(ordered_unique_range_t, InputIterator, InputIterator, Compare const&, Allocator const&) ->
   set< it_based_value_type_t<InputIterator>
           , Compare
           , Allocator>;

#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class Compare, class Allocator, class Options>
struct has_trivial_destructor_after_move<boost::container::set<Key, Compare, Allocator, Options> >
{
   typedef ::boost::container::dtl::tree<Key, void, Compare, Allocator, Options> tree;
   static const bool value = ::boost::has_trivial_destructor_after_move<tree>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

//! A multiset is a kind of associative container that supports equivalent keys
//! (possibly contains multiple copies of the same key value) and provides for
//! fast retrieval of the keys themselves. Class multiset supports bidirectional iterators.
//!
//! A multiset satisfies all of the requirements of a container and of a reversible
//! container, and of an associative container). multiset also provides most operations
//! described for duplicate keys.
//!
//! \tparam Key is the type to be inserted in the set, which is also the key_type
//! \tparam Compare is the comparison functor used to order keys
//! \tparam Allocator is the allocator to be used to allocate memory for this container
//! \tparam Options is an packed option type generated using using boost::container::tree_assoc_options.
template <class Key, class Compare = std::less<Key>, class Allocator = new_allocator<Key>, class Options = tree_assoc_defaults >
#else
template <class Key, class Compare, class Allocator, class Options>
#endif
class multiset
   /// @cond
   : public dtl::tree
      <Key, void, Compare, Allocator, Options>
   /// @endcond
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(multiset)
   typedef dtl::tree
      <Key, void, Compare, Allocator, Options> base_t;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:

   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef Key                                                                            key_type;
   typedef Key                                                                            value_type;
   typedef Compare                                                                        key_compare;
   typedef key_compare                                                                    value_compare;
   typedef typename base_t::allocator_type                                                allocator_type;
   typedef ::boost::container::allocator_traits<allocator_type>                           allocator_traits_type;
   typedef typename ::boost::container::allocator_traits<allocator_type>::pointer         pointer;
   typedef typename ::boost::container::allocator_traits<allocator_type>::const_pointer   const_pointer;
   typedef typename ::boost::container::allocator_traits<allocator_type>::reference       reference;
   typedef typename ::boost::container::allocator_traits<allocator_type>::const_reference const_reference;
   typedef typename ::boost::container::allocator_traits<allocator_type>::size_type       size_type;
   typedef typename ::boost::container::allocator_traits<allocator_type>::difference_type difference_type;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::stored_allocator_type)                 stored_allocator_type;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::iterator)                              iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::const_iterator)                        const_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::reverse_iterator)                      reverse_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::const_reverse_iterator)                const_reverse_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::node_type)                             node_type;

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! @copydoc ::boost::container::set::set()
   BOOST_CONTAINER_FORCEINLINE multiset()
      BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<allocator_type>::value &&
                        dtl::is_nothrow_default_constructible<Compare>::value)
      : base_t()
   {}

   //! @copydoc ::boost::container::set::set(const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE explicit multiset(const allocator_type& a)
      : base_t(a)
   {}

   //! @copydoc ::boost::container::set::set(const Compare&)
   BOOST_CONTAINER_FORCEINLINE explicit multiset(const Compare& comp)
      : base_t(comp)
   {}

   //! @copydoc ::boost::container::set::set(const Compare&, const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE multiset(const Compare& comp, const allocator_type& a)
      : base_t(comp, a)
   {}

   //! @copydoc ::boost::container::set::set(InputIterator, InputIterator)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multiset(InputIterator first, InputIterator last)
      : base_t(false, first, last)
   {}

   //! @copydoc ::boost::container::set::set(InputIterator, InputIterator, const allocator_type&)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multiset(InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(false, first, last, key_compare(), a)
   {}

   //! @copydoc ::boost::container::set::set(InputIterator, InputIterator, const Compare&)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multiset(InputIterator first, InputIterator last, const Compare& comp)
      : base_t(false, first, last, comp)
   {}

   //! @copydoc ::boost::container::set::set(InputIterator, InputIterator, const Compare&, const allocator_type&)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multiset(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : base_t(false, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty multiset and
   //! and inserts elements from the ordered range [first ,last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multiset( ordered_range_t, InputIterator first, InputIterator last )
      : base_t(ordered_range, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty multiset using the specified comparison object and
   //! inserts elements from the ordered range [first ,last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multiset( ordered_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : base_t(ordered_range, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty multiset using the specified comparison object and
   //! allocator, and inserts elements from the ordered range [first ,last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multiset( ordered_range_t, InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : base_t(ordered_range, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty multiset using the specified allocator and
   //! inserts elements from the ordered range [first ,last ). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multiset(ordered_range_t, InputIterator first, InputIterator last, const allocator_type &a)
      : base_t(ordered_range, first, last, Compare(), a)
   {}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::boost::container::set::set(std::initializer_list<value_type>)
   BOOST_CONTAINER_FORCEINLINE multiset(std::initializer_list<value_type> il)
      : base_t(false, il.begin(), il.end())
   {}

   //! @copydoc ::boost::container::set::set(std::initializer_list<value_type>, const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE multiset(std::initializer_list<value_type> il, const allocator_type& a)
      : base_t(false, il.begin(), il.end(), Compare(), a)
   {}

   //! @copydoc ::boost::container::set::set(std::initializer_list<value_type>, const Compare&)
   BOOST_CONTAINER_FORCEINLINE multiset(std::initializer_list<value_type> il, const Compare& comp)
      : base_t(false, il.begin(), il.end(), comp)
   {}

   //! @copydoc ::boost::container::set::set(std::initializer_list<value_type>, const Compare&, const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE multiset(std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : base_t(false, il.begin(), il.end(), comp, a)
   {}

   //! @copydoc ::boost::container::set::set(ordered_unique_range_t, std::initializer_list<value_type>)
   BOOST_CONTAINER_FORCEINLINE multiset(ordered_range_t, std::initializer_list<value_type> il)
      : base_t(ordered_range, il.begin(), il.end())
   {}

   //! @copydoc ::boost::container::set::set(ordered_unique_range_t, std::initializer_list<value_type>, const Compare&)
   BOOST_CONTAINER_FORCEINLINE multiset(ordered_range_t, std::initializer_list<value_type> il, const Compare& comp)
      : base_t(ordered_range, il.begin(), il.end(), comp)
   {}

   //! @copydoc ::boost::container::set::set(ordered_unique_range_t, std::initializer_list<value_type>, const Compare&, const allocator_type&)
   BOOST_CONTAINER_FORCEINLINE multiset(ordered_range_t, std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : base_t(ordered_range, il.begin(), il.end(), comp, a)
   {}
#endif

   //! @copydoc ::boost::container::set::set(const set &)
   BOOST_CONTAINER_FORCEINLINE multiset(const multiset& x)
      : base_t(static_cast<const base_t&>(x))
   {}

   //! @copydoc ::boost::container::set::set(set &&)
   BOOST_CONTAINER_FORCEINLINE multiset(BOOST_RV_REF(multiset) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      : base_t(BOOST_MOVE_BASE(base_t, x))
   {}

   //! @copydoc ::boost::container::set::set(const set &, const allocator_type &)
   BOOST_CONTAINER_FORCEINLINE multiset(const multiset& x, const allocator_type &a)
      : base_t(static_cast<const base_t&>(x), a)
   {}

   //! @copydoc ::boost::container::set::set(set &&, const allocator_type &)
   BOOST_CONTAINER_FORCEINLINE multiset(BOOST_RV_REF(multiset) x, const allocator_type &a)
      : base_t(BOOST_MOVE_BASE(base_t, x), a)
   {}

   //! @copydoc ::boost::container::set::operator=(const set &)
   BOOST_CONTAINER_FORCEINLINE multiset& operator=(BOOST_COPY_ASSIGN_REF(multiset) x)
   {  return static_cast<multiset&>(this->base_t::operator=(static_cast<const base_t&>(x)));  }

   //! @copydoc ::boost::container::set::operator=(set &&)
   BOOST_CONTAINER_FORCEINLINE multiset& operator=(BOOST_RV_REF(multiset) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {  return static_cast<multiset&>(this->base_t::operator=(BOOST_MOVE_BASE(base_t, x)));  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::boost::container::set::operator=(std::initializer_list<value_type>)
   multiset& operator=(std::initializer_list<value_type> il)
   {
       this->clear();
       insert(il.begin(), il.end());
       return *this;
   }
#endif
   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! @copydoc ::boost::container::set::get_allocator()
   allocator_type get_allocator() const;

   //! @copydoc ::boost::container::set::get_stored_allocator()
   stored_allocator_type &get_stored_allocator();

   //! @copydoc ::boost::container::set::get_stored_allocator() const
   const stored_allocator_type &get_stored_allocator() const;

   //! @copydoc ::boost::container::set::begin()
   iterator begin();

   //! @copydoc ::boost::container::set::begin() const
   const_iterator begin() const;

   //! @copydoc ::boost::container::set::cbegin() const
   const_iterator cbegin() const;

   //! @copydoc ::boost::container::set::end()
   iterator end() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::end() const
   const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::cend() const
   const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::rbegin()
   reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::rbegin() const
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::crbegin() const
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::rend()
   reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::rend() const
   const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::crend() const
   const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::empty() const
   bool empty() const;

   //! @copydoc ::boost::container::set::size() const
   size_type size() const;

   //! @copydoc ::boost::container::set::max_size() const
   size_type max_size() const;

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)... and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace(BOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_equal(boost::forward<Args>(args)...); }

   //! <b>Effects</b>: Inserts an object of type Key constructed with
   //!   std::forward<Args>(args)...
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator p, BOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_hint_equal(p, boost::forward<Args>(args)...); }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_MULTISET_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace(BOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_equal(BOOST_MOVE_FWD##N);  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_hint_equal(hint BOOST_MOVE_I##N BOOST_MOVE_FWD##N); }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_MULTISET_EMPLACE_CODE)
   #undef BOOST_CONTAINER_MULTISET_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts x and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   iterator insert(const value_type &x);

   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   iterator insert(value_type &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH(insert, value_type, iterator, this->base_t::insert_equal_convertible)
   #endif

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   iterator insert(const_iterator p, const value_type &x);

   //! <b>Effects</b>: Inserts a value move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   iterator insert(const_iterator p, value_type &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG
      (insert, value_type, iterator, this->base_t::insert_equal_hint_convertible, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from first to last)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
   {  this->base_t::insert_equal_range(first, last);  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::boost::container::set::insert(std::initializer_list<value_type>)
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_equal_range(il.begin(), il.end());  }
#endif

   //! @copydoc ::boost::container::multimap::insert(node_type&&)
   BOOST_CONTAINER_FORCEINLINE iterator insert(BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {  return this->base_t::insert_equal_node(boost::move(nh));  }

   //! @copydoc ::boost::container::multimap::insert(const_iterator, node_type&&)
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator hint, BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {  return this->base_t::insert_equal_node(hint, boost::move(nh));  }

   //! @copydoc ::boost::container::multimap::merge(multimap<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(multiset<Key, C2, Allocator, Options>& source)
   {
      typedef dtl::tree
         <Key, void, C2, Allocator, Options> base2_t;
      this->base_t::merge_equal(static_cast<base2_t&>(source));
   }

   //! @copydoc ::boost::container::multiset::merge(multiset<Key, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG multiset<Key, C2, Allocator, Options> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<multiset<Key, C2, Allocator, Options>&>(source));   }

   //! @copydoc ::boost::container::multimap::merge(map<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(set<Key, C2, Allocator, Options>& source)
   {
      typedef dtl::tree
         <Key, void, C2, Allocator, Options> base2_t;
      this->base_t::merge_equal(static_cast<base2_t&>(source));
   }

   //! @copydoc ::boost::container::multiset::merge(set<Key, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG set<Key, C2, Allocator, Options> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<set<Key, C2, Allocator, Options>&>(source));   }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! @copydoc ::boost::container::set::erase(const_iterator)
   iterator erase(const_iterator p);

   //! @copydoc ::boost::container::set::erase(const key_type&)
   size_type erase(const key_type& x);

   //! @copydoc ::boost::container::set::erase(const_iterator,const_iterator)
   iterator erase(const_iterator first, const_iterator last);

   //! @copydoc ::boost::container::multimap::extract(const_iterator)
   node_type extract(const_iterator p);

   //! @copydoc ::boost::container::multimap::extract(const key_type&)
   node_type extract(const key_type& x);

   //! @copydoc ::boost::container::set::swap
   void swap(multiset& x)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   //! @copydoc ::boost::container::set::clear
   void clear() BOOST_NOEXCEPT_OR_NOTHROW;

   //! @copydoc ::boost::container::set::key_comp
   key_compare key_comp() const;

   //! @copydoc ::boost::container::set::value_comp
   value_compare value_comp() const;

   //! @copydoc ::boost::container::set::find(const key_type& )
   iterator find(const key_type& x);

   //! @copydoc ::boost::container::set::find(const key_type& ) const
   const_iterator find(const key_type& x) const;

   //! @copydoc ::boost::container::set::find(const K& )
   template<typename K>
   iterator find(const K& x);

   //! @copydoc ::boost::container::set::find(const K& )
   template<typename K>
   const_iterator find(const K& x) const;

   //! @copydoc ::boost::container::set::count(const key_type& ) const
   size_type count(const key_type& x) const;

   //! @copydoc ::boost::container::set::count(const K& ) const
   template<typename K>
   size_type count(const K& x) const;

   //! @copydoc ::boost::container::set::contains(const key_type& ) const
   bool contains(const key_type& x) const;

   //! @copydoc ::boost::container::set::contains(const K& ) const
   template<typename K>
   bool contains(const K& x) const;

   //! @copydoc ::boost::container::set::lower_bound(const key_type& )
   iterator lower_bound(const key_type& x);

   //! @copydoc ::boost::container::set::lower_bound(const key_type& ) const
   const_iterator lower_bound(const key_type& x) const;

   //! @copydoc ::boost::container::set::lower_bound(const K& )
   template<typename K>
   iterator lower_bound(const K& x);

   //! @copydoc ::boost::container::set::lower_bound(const K& ) const
   template<typename K>
   const_iterator lower_bound(const K& x) const;

   //! @copydoc ::boost::container::set::upper_bound(const key_type& )
   iterator upper_bound(const key_type& x);

   //! @copydoc ::boost::container::set::upper_bound(const key_type& ) const
   const_iterator upper_bound(const key_type& x) const;

   //! @copydoc ::boost::container::set::upper_bound(const K& )
   template<typename K>
   iterator upper_bound(const K& x);

   //! @copydoc ::boost::container::set::upper_bound(const K& ) const
   template<typename K>
   const_iterator upper_bound(const K& x) const;

   //! @copydoc ::boost::container::set::equal_range(const key_type& ) const
   std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const;

   //! @copydoc ::boost::container::set::equal_range(const key_type& )
   std::pair<iterator,iterator> equal_range(const key_type& x);

   //! @copydoc ::boost::container::set::equal_range(const K& ) const
   template<typename K>
   std::pair<const_iterator, const_iterator> equal_range(const K& x) const;

   //! @copydoc ::boost::container::set::equal_range(const K& )
   template<typename K>
   std::pair<iterator,iterator> equal_range(const K& x);

   //! @copydoc ::boost::container::set::rebalance()
   void rebalance();

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const multiset& x, const multiset& y);

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const multiset& x, const multiset& y);

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(multiset& x, multiset& y)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
multiset(InputIterator, InputIterator) ->
   multiset< it_based_value_type_t<InputIterator> >;


template < typename InputIterator, typename AllocatorOrCompare>
multiset(InputIterator, InputIterator, AllocatorOrCompare const&) ->
    multiset < it_based_value_type_t<InputIterator>
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
multiset(InputIterator, InputIterator, Compare const&, Allocator const&) ->
   multiset< it_based_value_type_t<InputIterator>
           , Compare
           , Allocator>;

template <typename InputIterator>
multiset(ordered_range_t, InputIterator, InputIterator) ->
   multiset< it_based_value_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
multiset(ordered_range_t, InputIterator, InputIterator, AllocatorOrCompare const&) ->
    multiset < it_based_value_type_t<InputIterator>
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
multiset(ordered_range_t, InputIterator, InputIterator, Compare const&, Allocator const&) ->
   multiset< it_based_value_type_t<InputIterator>
           , Compare
           , Allocator>;

#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class Compare, class Allocator, class Options>
struct has_trivial_destructor_after_move<boost::container::multiset<Key, Compare, Allocator, Options> >
{
   typedef ::boost::container::dtl::tree<Key, void, Compare, Allocator, Options> tree;
   static const bool value = ::boost::has_trivial_destructor_after_move<tree>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}}

#include <boost/container/detail/config_end.hpp>

#endif   // BOOST_CONTAINER_SET_HPP

/* set.hpp
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
*/