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
   BOOST_MOVE_CONVERSION_AWARE_CATCH(insert, value_type, insert_return_pair, this->priv_insert)
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
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, value_type, iterator, this->priv_insert, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from first to last)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
   {  this->base_t::insert_unique(first, last);  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(),il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from il.begin() to il.end())
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_unique(il.begin(), il.end()); }
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

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Erases the element pointed to by p.
   //!
   //! <b>Returns</b>: Returns an iterator pointing to the element immediately
   //!   following q prior to the element being erased. If no such element exists,
   //!   returns end().
   //!
   //! <b>Complexity</b>: Amortized constant time
   iterator erase(const_iterator p);

   //! <b>Effects</b>: Erases all elements in the container with key equivalent to x.
   //!
   //! <b>Returns</b>: Returns the number of erased elements.
   //!
   //! <b>Complexity</b>: log(size()) + count(k)
   size_type erase(const key_type& x);

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

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   BOOST_CONTAINER_FORCEINLINE size_type count(const key_type& x) const
   {  return static_cast<size_type>(this->base_t::find(x) != this->base_t::cend());  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   template<typename K>
   BOOST_CONTAINER_FORCEINLINE size_type count(const K& x) const
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
   friend void swap(set& x, set& y);

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   template <class KeyType>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> priv_insert(BOOST_FWD_REF(KeyType) x)
   {  return this->base_t::insert_unique(::boost::forward<KeyType>(x));  }

   template <class KeyType>
   BOOST_CONTAINER_FORCEINLINE iterator priv_insert(const_iterator p, BOOST_FWD_REF(KeyType) x)
   {  return this->base_t::insert_unique(p, ::boost::forward<KeyType>(x)); }
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
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
   BOOST_MOVE_CONVERSION_AWARE_CATCH(insert, value_type, iterator, this->priv_insert)
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
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, value_type, iterator, this->priv_insert, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from first to last)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
   {  this->base_t::insert_equal(first, last);  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! @copydoc ::boost::container::set::insert(std::initializer_list<value_type>)
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_equal(il.begin(), il.end());  }
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
   friend void swap(multiset& x, multiset& y);

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   template <class KeyType>
   BOOST_CONTAINER_FORCEINLINE iterator priv_insert(BOOST_FWD_REF(KeyType) x)
   {  return this->base_t::insert_equal(::boost::forward<KeyType>(x));  }

   template <class KeyType>
   BOOST_CONTAINER_FORCEINLINE iterator priv_insert(const_iterator p, BOOST_FWD_REF(KeyType) x)
   {  return this->base_t::insert_equal(p, ::boost::forward<KeyType>(x)); }

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
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