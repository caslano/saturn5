//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_MAP_HPP
#define BOOST_CONTAINER_MAP_HPP

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
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/tree.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/value_init.hpp>
#include <boost/container/detail/pair.hpp>
#include <boost/container/detail/pair_key_mapped_of_value.hpp>

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
// other
#include <boost/static_assert.hpp>
#include <boost/core/no_exceptions_support.hpp>
// std
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace boost {
namespace container {

#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

//! A map is a kind of associative container that supports unique keys (contains at
//! most one of each key value) and provides for fast retrieval of values of another
//! type T based on the keys. The map class supports bidirectional iterators.
//!
//! A map satisfies all of the requirements of a container and of a reversible
//! container and of an associative container. The <code>value_type</code> stored
//! by this container is the value_type is std::pair<const Key, T>.
//!
//! \tparam Key is the key_type of the map
//! \tparam T is the <code>mapped_type</code>
//! \tparam Compare is the ordering function for Keys (e.g. <i>std::less<Key></i>).
//! \tparam Allocator is the allocator to allocate the <code>value_type</code>s
//!   (e.g. <i>allocator< std::pair<const Key, T> > </i>).
//! \tparam Options is an packed option type generated using using boost::container::tree_assoc_options.
template < class Key, class T, class Compare = std::less<Key>
         , class Allocator = void, class Options = tree_assoc_defaults >
#else
template <class Key, class T, class Compare, class Allocator, class Options>
#endif
class map
   ///@cond
   : public dtl::tree
      < std::pair<const Key, T>
      , int
      , Compare, Allocator, Options>
   ///@endcond
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(map)

   typedef int                                                             select_1st_t;
   typedef std::pair<const Key, T>                                         value_type_impl;
   typedef dtl::tree
      <value_type_impl, select_1st_t, Compare, Allocator, Options>         base_t;
   typedef dtl::pair <Key, T>                                              movable_value_type_impl;
   typedef typename base_t::value_compare                                  value_compare_impl;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////

   typedef Key                                                                            key_type;
   typedef T                                                                              mapped_type;
   typedef typename base_t::allocator_type                                                allocator_type;
   typedef ::boost::container::allocator_traits<allocator_type>                           allocator_traits_type;
   typedef typename boost::container::allocator_traits<allocator_type>::value_type        value_type;
   typedef typename boost::container::allocator_traits<allocator_type>::pointer           pointer;
   typedef typename boost::container::allocator_traits<allocator_type>::const_pointer     const_pointer;
   typedef typename boost::container::allocator_traits<allocator_type>::reference         reference;
   typedef typename boost::container::allocator_traits<allocator_type>::const_reference   const_reference;
   typedef typename boost::container::allocator_traits<allocator_type>::size_type         size_type;
   typedef typename boost::container::allocator_traits<allocator_type>::difference_type   difference_type;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::stored_allocator_type)                 stored_allocator_type;
   typedef BOOST_CONTAINER_IMPDEF(value_compare_impl)                                     value_compare;
   typedef Compare                                                                        key_compare;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::iterator)                              iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::const_iterator)                        const_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::reverse_iterator)                      reverse_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::const_reverse_iterator)                const_reverse_iterator;
   //typedef std::pair<key_type, mapped_type>                                               nonconst_value_type;
   typedef BOOST_CONTAINER_IMPDEF(movable_value_type_impl)                                movable_value_type;
   typedef BOOST_CONTAINER_IMPDEF(node_handle<
      typename base_t::stored_allocator_type
      BOOST_MOVE_I pair_key_mapped_of_value
         <key_type BOOST_MOVE_I mapped_type> >)                                     node_type;
   typedef BOOST_CONTAINER_IMPDEF
      (insert_return_type_base<iterator BOOST_MOVE_I node_type>)                    insert_return_type;

   //allocator_type::value_type type must be std::pair<CONST Key, T>
   BOOST_STATIC_ASSERT((dtl::is_same<typename allocator_type::value_type, std::pair<const Key, T> >::value));

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs an empty map.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE 
   map() BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<allocator_type>::value &&
                           dtl::is_nothrow_default_constructible<Compare>::value)
      : base_t()
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object
   //! and allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE map(const Compare& comp, const allocator_type& a)
      : base_t(comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit map(const Compare& comp)
      : base_t(comp)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit map(const allocator_type& a)
      : base_t(a)
   {}

   //! <b>Effects</b>: Constructs an empty map and
   //! inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE map(InputIterator first, InputIterator last)
      : base_t(true, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified 
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE map(InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(true, first, last, Compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object and
   //! inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE map(InputIterator first, InputIterator last, const Compare& comp)
      : base_t(true, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object and
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE map(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : base_t(true, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty map and
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
   BOOST_CONTAINER_FORCEINLINE map( ordered_unique_range_t, InputIterator first, InputIterator last)
      : base_t(ordered_range, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object and
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
   BOOST_CONTAINER_FORCEINLINE map( ordered_unique_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : base_t(ordered_range, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object and
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
   BOOST_CONTAINER_FORCEINLINE map( ordered_unique_range_t, InputIterator first, InputIterator last
      , const Compare& comp, const allocator_type& a)
      : base_t(ordered_range, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified allocator object and
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
   BOOST_CONTAINER_FORCEINLINE map(ordered_unique_range_t, InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(ordered_range, first, last, Compare(), a)
   {}


#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs an empty map and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted according
   //! to the predicate and otherwise N logN, where N is il.first() - il.end().
   BOOST_CONTAINER_FORCEINLINE map(std::initializer_list<value_type> il)
      : base_t(true, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is il.first() - il.end().
   BOOST_CONTAINER_FORCEINLINE map(std::initializer_list<value_type> il, const Compare& comp)
      : base_t(true, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is il.first() - il.end().
   BOOST_CONTAINER_FORCEINLINE map(std::initializer_list<value_type> il, const allocator_type& a)
      : base_t(true, il.begin(), il.end(), Compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object and
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is il.first() - il.end().
   BOOST_CONTAINER_FORCEINLINE map(std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : base_t(true, il.begin(), il.end(), comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty map and inserts elements from the ordered unique range [il.begin(), il.end()).
   //! This function is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE map(ordered_unique_range_t, std::initializer_list<value_type> il)
      : base_t(ordered_range, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object,
   //!  and inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE map(ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp)
      : base_t(ordered_range, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object and
   //! allocator, and inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE map( ordered_unique_range_t, std::initializer_list<value_type> il
                                  , const Compare& comp, const allocator_type& a)
      : base_t(ordered_range, il.begin(), il.end(), comp, a)
   {} 

#endif

   //! <b>Effects</b>: Copy constructs a map.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE map(const map& x)
      : base_t(static_cast<const base_t&>(x))
   {}

   //! <b>Effects</b>: Move constructs a map. Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Postcondition</b>: x is emptied.
   BOOST_CONTAINER_FORCEINLINE map(BOOST_RV_REF(map) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      : base_t(BOOST_MOVE_BASE(base_t, x))
   {}

   //! <b>Effects</b>: Copy constructs a map using the specified allocator.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE map(const map& x, const allocator_type &a)
      : base_t(static_cast<const base_t&>(x), a)
   {}

   //! <b>Effects</b>: Move constructs a map using the specified allocator.
   //!                 Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant if x == x.get_allocator(), linear otherwise.
   //!
   //! <b>Postcondition</b>: x is emptied.
   BOOST_CONTAINER_FORCEINLINE map(BOOST_RV_REF(map) x, const allocator_type &a)
      : base_t(BOOST_MOVE_BASE(base_t, x), a)
   {}

   //! <b>Effects</b>: Makes *this a copy of x.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE map& operator=(BOOST_COPY_ASSIGN_REF(map) x)
   {  return static_cast<map&>(this->base_t::operator=(static_cast<const base_t&>(x)));  }

   //! <b>Effects</b>: this->swap(x.get()).
   //!
   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or value_type's move constructor throws)
   //!
   //! <b>Complexity</b>: Constant if allocator_traits_type::
   //!   propagate_on_container_move_assignment is true or
   //!   this->get>allocator() == x.get_allocator(). Linear otherwise.
   BOOST_CONTAINER_FORCEINLINE map& operator=(BOOST_RV_REF(map) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {  return static_cast<map&>(this->base_t::operator=(BOOST_MOVE_BASE(base_t, x)));  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Assign content of il to *this.
   //!
   BOOST_CONTAINER_FORCEINLINE map& operator=(std::initializer_list<value_type> il)
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

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

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

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW;

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

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW;

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

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: If there is no key equivalent to x in the map, inserts
   //! value_type(x, T()) into the map.
   //!
   //! <b>Returns</b>: A reference to the mapped_type corresponding to x in *this.
   //!
   //! <b>Complexity</b>: Logarithmic.
   mapped_type& operator[](const key_type &k);

   //! <b>Effects</b>: If there is no key equivalent to x in the map, inserts
   //! value_type(boost::move(x), T()) into the map (the key is move-constructed)
   //!
   //! <b>Returns</b>: A reference to the mapped_type corresponding to x in *this.
   //!
   //! <b>Complexity</b>: Logarithmic.
   mapped_type& operator[](key_type &&k);
   #elif defined(BOOST_MOVE_HELPERS_RETURN_SFINAE_BROKEN)
      //in compilers like GCC 3.4, we can't catch temporaries
      BOOST_CONTAINER_FORCEINLINE mapped_type& operator[](const key_type &k)         {  return this->priv_subscript(k);  }
      BOOST_CONTAINER_FORCEINLINE mapped_type& operator[](BOOST_RV_REF(key_type) k)  {  return this->priv_subscript(::boost::move(k));  }
   #else
      BOOST_MOVE_CONVERSION_AWARE_CATCH( operator[] , key_type, mapped_type&, this->priv_subscript)
   #endif

   //! <b>Effects</b>: If a key equivalent to k already exists in the container, assigns forward<M>(obj)
   //! to the mapped_type corresponding to the key k. If the key does not exist, inserts the new value
   //! as if by insert, constructing it from value_type(k, forward<M>(obj)).
   //! 
   //! No iterators or references are invalidated. If the insertion is successful, pointers and references
   //! to the element obtained while it is held in the node handle are invalidated, and pointers and
   //! references obtained to that element before it was extracted become valid.
   //!
   //! <b>Returns</b>: The bool component is true if the insertion took place and false if the assignment
   //!   took place. The iterator component is pointing at the element that was inserted or updated.
   //!
   //! <b>Complexity</b>: Logarithmic in the size of the container.
   template <class M>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> insert_or_assign(const key_type& k, BOOST_FWD_REF(M) obj)
   {  return this->base_t::insert_or_assign(const_iterator(), k, ::boost::forward<M>(obj));  }

   //! <b>Effects</b>: If a key equivalent to k already exists in the container, assigns forward<M>(obj)
   //! to the mapped_type corresponding to the key k. If the key does not exist, inserts the new value
   //! as if by insert, constructing it from value_type(k, move(obj)).
   //! 
   //! No iterators or references are invalidated. If the insertion is successful, pointers and references
   //! to the element obtained while it is held in the node handle are invalidated, and pointers and
   //! references obtained to that element before it was extracted become valid.
   //!
   //! <b>Returns</b>: The bool component is true if the insertion took place and false if the assignment
   //!   took place. The iterator component is pointing at the element that was inserted or updated.
   //!
   //! <b>Complexity</b>: Logarithmic in the size of the container.
   template <class M>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> insert_or_assign(BOOST_RV_REF(key_type) k, BOOST_FWD_REF(M) obj)
   {  return this->base_t::insert_or_assign(const_iterator(), ::boost::move(k), ::boost::forward<M>(obj));  }

   //! <b>Effects</b>: If a key equivalent to k already exists in the container, assigns forward<M>(obj)
   //! to the mapped_type corresponding to the key k. If the key does not exist, inserts the new value
   //! as if by insert, constructing it from value_type(k, forward<M>(obj)) and the new element
   //! to the container as close as possible to the position just before hint.
   //! 
   //! No iterators or references are invalidated. If the insertion is successful, pointers and references
   //! to the element obtained while it is held in the node handle are invalidated, and pointers and
   //! references obtained to that element before it was extracted become valid.
   //!
   //! <b>Returns</b>: The bool component is true if the insertion took place and false if the assignment
   //!   took place. The iterator component is pointing at the element that was inserted or updated.
   //!
   //! <b>Complexity</b>: Logarithmic in the size of the container in general, but amortized constant if
   //! the new element is inserted just before hint.
   template <class M>
   BOOST_CONTAINER_FORCEINLINE iterator insert_or_assign(const_iterator hint, const key_type& k, BOOST_FWD_REF(M) obj)
   {  return this->base_t::insert_or_assign(hint, k, ::boost::forward<M>(obj)).first;  }

   //! <b>Effects</b>: If a key equivalent to k already exists in the container, assigns forward<M>(obj)
   //! to the mapped_type corresponding to the key k. If the key does not exist, inserts the new value
   //! as if by insert, constructing it from value_type(k, move(obj)) and the new element
   //! to the container as close as possible to the position just before hint.
   //! 
   //! No iterators or references are invalidated. If the insertion is successful, pointers and references
   //! to the element obtained while it is held in the node handle are invalidated, and pointers and
   //! references obtained to that element before it was extracted become valid.
   //!
   //! <b>Returns</b>: The bool component is true if the insertion took place and false if the assignment
   //!   took place. The iterator component is pointing at the element that was inserted or updated.
   //!
   //! <b>Complexity</b>: Logarithmic in the size of the container in general, but amortized constant if
   //! the new element is inserted just before hint.
   template <class M>
   BOOST_CONTAINER_FORCEINLINE iterator insert_or_assign(const_iterator hint, BOOST_RV_REF(key_type) k, BOOST_FWD_REF(M) obj)
   {  return this->base_t::insert_or_assign(hint, ::boost::move(k), ::boost::forward<M>(obj)).first;  }

   //! <b>Returns</b>: A reference to the element whose key is equivalent to x.
   //! Throws: An exception object of type out_of_range if no such element is present.
   //! <b>Complexity</b>: logarithmic.
   T& at(const key_type& k)
   {
      iterator i = this->find(k);
      if(i == this->end()){
         throw_out_of_range("map::at key not found");
      }
      return i->second;
   }

   //! <b>Returns</b>: A reference to the element whose key is equivalent to x.
   //! Throws: An exception object of type out_of_range if no such element is present.
   //! <b>Complexity</b>: logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD const T& at(const key_type& k) const
   {
      const_iterator i = this->find(k);
      if(i == this->end()){
         throw_out_of_range("map::at key not found");
      }
      return i->second;
   }

   //////////////////////////////////////////////
   //
   //                modifiers
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Inserts x if and only if there is no element in the container
   //!   with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> insert(const value_type& x)
   { return this->base_t::insert_unique_convertible(x); }

   //! <b>Effects</b>: Move constructs a new value from x if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> insert(BOOST_RV_REF(value_type) x)
   { return this->base_t::insert_unique_convertible(boost::move(x)); }

   //! <b>Effects</b>: Inserts a new value_type created from the pair if and only if
   //! there is no element in the container  with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template <class Pair>
   BOOST_CONTAINER_FORCEINLINE BOOST_CONTAINER_DOC1ST
         ( std::pair<iterator BOOST_MOVE_I bool>
         , typename dtl::enable_if_c<
               dtl::is_convertible<Pair BOOST_MOVE_I value_type>::value ||
               dtl::is_convertible<Pair BOOST_MOVE_I movable_value_type>::value
            BOOST_MOVE_I std::pair<iterator BOOST_MOVE_I bool> >::type)
      insert(BOOST_FWD_REF(Pair) x)
   {  return this->base_t::emplace_unique(boost::forward<Pair>(x)); }

   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, const value_type& x)
   { return this->base_t::insert_unique_hint_convertible(p, x); }

   //! <b>Effects</b>: Inserts a copy of x in the container if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, BOOST_RV_REF(value_type) x)
   { return this->base_t::insert_unique_hint_convertible(p, boost::move(x)); }

   //! <b>Effects</b>: Inserts a copy of x in the container if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   template <class Pair>
   BOOST_CONTAINER_FORCEINLINE BOOST_CONTAINER_DOC1ST
         ( iterator
         , typename dtl::enable_if_c<
            dtl::is_convertible<Pair BOOST_MOVE_I value_type>::value  ||
            dtl::is_convertible<Pair BOOST_MOVE_I movable_value_type>::value
            BOOST_MOVE_I iterator >::type)
      insert(const_iterator p, BOOST_FWD_REF(Pair) x)
   {  return this->base_t::emplace_hint_unique(p, boost::forward<Pair>(x));  }


/*
   //! <b>Effects</b>: Move constructs a new value from x if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, BOOST_RV_REF(nonconst_value_type) x)
   { return this->try_emplace(p, boost::move(x.first), boost::move(x.second)); }

   //! <b>Effects</b>: Move constructs a new value from x if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, BOOST_RV_REF(movable_value_type) x)
   { return this->try_emplace(p, boost::move(x.first), boost::move(x.second)); }

   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, const nonconst_value_type& x)
   { return this->try_emplace(p, x.first, x.second); }


*/
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
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from il.begin() to il.end())
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_unique_range(il.begin(), il.end()); }
#endif

   //! <b>Requires</b>: nh is empty or this->get_allocator() == nh.get_allocator().
   //!
   //! <b>Effects</b>: If nh is empty, has no effect. Otherwise, inserts the element owned
   //!   by nh if and only if there is no element in the container with a key equivalent to nh.key().
   //!
   //! <b>Returns</b>: If nh is empty, insert_return_type.inserted is false, insert_return_type.position
   //!   is end(), and insert_return_type.node is empty. Otherwise if the insertion took place,
   //!   insert_return_type.inserted is true, insert_return_type.position points to the inserted element,
   //!   and insert_return_type.node is empty; if the insertion failed, insert_return_type.inserted is
   //!   false, insert_return_type.node has the previous value of nh, and insert_return_type.position
   //!   points to an element with a key equivalent to nh.key().
   //!
   //! <b>Complexity</b>: Logarithmic
   insert_return_type insert(BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {
      typename base_t::node_type  n(boost::move(nh));
      typename base_t::insert_return_type base_ret(this->base_t::insert_unique_node(boost::move(n)));
      return insert_return_type (base_ret.inserted, base_ret.position, boost::move(base_ret.node));
   }

   //! <b>Effects</b>: Same as `insert(node_type && nh)` but the element is inserted as close as possible
   //!   to the position just prior to "hint".
   //!
   //! <b>Complexity</b>: logarithmic in general, but amortized constant if the element is inserted
   //!   right before "hint".
   insert_return_type insert(const_iterator hint, BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {
      typename base_t::node_type  n(boost::move(nh));
      typename base_t::insert_return_type base_ret(this->base_t::insert_unique_node(hint, boost::move(n)));
      return insert_return_type (base_ret.inserted, base_ret.position, boost::move(base_ret.node));
   }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object x of type T constructed with
   //!   std::forward<Args>(args)... in the container if and only if there is
   //!   no element in the container with an equivalent key.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> emplace(BOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_unique(boost::forward<Args>(args)...); }

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the container if and only if there is
   //!   no element in the container with an equivalent key.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator p, BOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_hint_unique(p, boost::forward<Args>(args)...); }

   //! <b>Requires</b>: value_type shall be EmplaceConstructible into map from piecewise_construct, 
   //! forward_as_tuple(k), forward_as_tuple(forward<Args>(args)...).
   //! 
   //! <b>Effects</b>: If the map already contains an element whose key is equivalent to k, there is no effect. Otherwise
   //! inserts an object of type value_type constructed with piecewise_construct, forward_as_tuple(k),
   //! forward_as_tuple(forward<Args>(args)...).
   //! 
   //! <b>Returns</b>: The bool component of the returned pair is true if and only if the
   //! insertion took place. The returned iterator points to the map element whose key is equivalent to k.
   //! 
   //! <b>Complexity</b>: Logarithmic.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace(const key_type& k, BOOST_FWD_REF(Args)... args)
   {  return this->base_t::try_emplace(const_iterator(), k, boost::forward<Args>(args)...); }

   //! <b>Requires</b>: value_type shall be EmplaceConstructible into map from piecewise_construct, 
   //! forward_as_tuple(k), forward_as_tuple(forward<Args>(args)...).
   //! 
   //! <b>Effects</b>: If the map already contains an element whose key is equivalent to k, there is no effect. Otherwise
   //! inserts an object of type value_type constructed with piecewise_construct, forward_as_tuple(k),
   //! forward_as_tuple(forward<Args>(args)...).
   //! 
   //! <b>Returns</b>: The returned iterator points to the map element whose key is equivalent to k.
   //! 
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if value
   //!   is inserted right before p.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator try_emplace(const_iterator hint, const key_type &k, BOOST_FWD_REF(Args)... args)
   {  return this->base_t::try_emplace(hint, k, boost::forward<Args>(args)...).first; }

   //! <b>Requires</b>: value_type shall be EmplaceConstructible into map from piecewise_construct, 
   //! forward_as_tuple(move(k)), forward_as_tuple(forward<Args>(args)...).
   //! 
   //! <b>Effects</b>: If the map already contains an element whose key is equivalent to k, there is no effect. Otherwise
   //! inserts an object of type value_type constructed with piecewise_construct, forward_as_tuple(move(k)),
   //! forward_as_tuple(forward<Args>(args)...).
   //! 
   //! <b>Returns</b>: The bool component of the returned pair is true if and only if the
   //! insertion took place. The returned iterator points to the map element whose key is equivalent to k.
   //! 
   //! <b>Complexity</b>: Logarithmic.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace(BOOST_RV_REF(key_type) k, BOOST_FWD_REF(Args)... args)
   {  return this->base_t::try_emplace(const_iterator(), boost::move(k), boost::forward<Args>(args)...); }

   //! <b>Requires</b>: value_type shall be EmplaceConstructible into map from piecewise_construct, 
   //! forward_as_tuple(move(k)), forward_as_tuple(forward<Args>(args)...).
   //! 
   //! <b>Effects</b>: If the map already contains an element whose key is equivalent to k, there is no effect. Otherwise
   //! inserts an object of type value_type constructed with piecewise_construct, forward_as_tuple(move(k)),
   //! forward_as_tuple(forward<Args>(args)...).
   //! 
   //! <b>Returns</b>: The returned iterator points to the map element whose key is equivalent to k.
   //! 
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if value
   //!   is inserted right before p.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator try_emplace(const_iterator hint, BOOST_RV_REF(key_type) k, BOOST_FWD_REF(Args)... args)
   {  return this->base_t::try_emplace(hint, boost::move(k), boost::forward<Args>(args)...).first; }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_MAP_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> emplace(BOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_unique(BOOST_MOVE_FWD##N);   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_hint_unique(hint BOOST_MOVE_I##N BOOST_MOVE_FWD##N);  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace(const key_type& k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->base_t::try_emplace(const_iterator(), k BOOST_MOVE_I##N BOOST_MOVE_FWD##N); }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator try_emplace(const_iterator hint, const key_type &k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->base_t::try_emplace(hint, k BOOST_MOVE_I##N BOOST_MOVE_FWD##N).first; }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace(BOOST_RV_REF(key_type) k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->base_t::try_emplace(const_iterator(), boost::move(k) BOOST_MOVE_I##N BOOST_MOVE_FWD##N); }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator try_emplace(const_iterator hint, BOOST_RV_REF(key_type) k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->base_t::try_emplace(hint, boost::move(k) BOOST_MOVE_I##N BOOST_MOVE_FWD##N).first; }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_MAP_EMPLACE_CODE)
   #undef BOOST_CONTAINER_MAP_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   //! <b>Effects</b>: If present, erases the element in the container with key equivalent to x.
   //!
   //! <b>Returns</b>: Returns the number of erased elements (0/1).
   //!
   //! <b>Complexity</b>: log(size()) + count(k)
   BOOST_CONTAINER_FORCEINLINE size_type erase(const key_type& x)
      { return this->base_t::erase_unique(x); }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Erases the element pointed to by p.
   //!
   //! <b>Returns</b>: Returns an iterator pointing to the element immediately
   //!   following q prior to the element being erased. If no such element exists,
   //!   returns end().
   //!
   //! <b>Complexity</b>: Amortized constant time
   iterator erase(const_iterator p) BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Erases all the elements in the range [first, last).
   //!
   //! <b>Returns</b>: Returns last.
   //!
   //! <b>Complexity</b>: log(size())+N where N is the distance from first to last.
   iterator erase(const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW;

   #else
   using base_t::erase;
   #endif   //   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Removes the first element in the container with key equivalent to k.
   //!
   //! <b>Returns</b>: A node_type owning the element if found, otherwise an empty node_type.
   //!
   //! <b>Complexity</b>: log(size()).
   node_type extract(const key_type& k)
   {
      typename base_t::node_type base_nh(this->base_t::extract(k));
      node_type nh(boost::move(base_nh));
      return BOOST_MOVE_RET(node_type, nh);
   }

   //! <b>Effects</b>: Removes the element pointed to by "position".
   //!
   //! <b>Returns</b>: A node_type owning the element, otherwise an empty node_type.
   //!
   //! <b>Complexity</b>: Amortized constant.
   node_type extract(const_iterator position)
   {
      typename base_t::node_type base_nh(this->base_t::extract(position));
      node_type nh(boost::move(base_nh));
      return BOOST_MOVE_RET(node_type, nh);
   }

   //! <b>Requires</b>: this->get_allocator() == source.get_allocator().
   //!
   //! <b>Effects</b>: Attempts to extract each element in source and insert it into a using
   //!   the comparison object of *this. If there is an element in a with key equivalent to the
   //!   key of an element from source, then that element is not extracted from source.
   //! 
   //! <b>Postcondition</b>: Pointers and references to the transferred elements of source refer
   //!   to those same elements but as members of *this. Iterators referring to the transferred
   //!   elements will continue to refer to their elements, but they now behave as iterators into *this,
   //!   not into source.
   //!
   //! <b>Throws</b>: Nothing unless the comparison object throws.
   //!
   //! <b>Complexity</b>: N log(size() + N) (N has the value source.size())
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(map<Key, T, C2, Allocator, Options>& source)
   {
      typedef dtl::tree
         <value_type_impl, select_1st_t, C2, Allocator, Options> base2_t;
      this->merge_unique(static_cast<base2_t&>(source));
   }

   //! @copydoc ::boost::container::map::merge(map<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG map<Key, T, C2, Allocator, Options> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<map<Key, T, C2, Allocator, Options>&>(source)); }

   //! @copydoc ::boost::container::map::merge(map<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(multimap<Key, T, C2, Allocator, Options>& source)
   {
      typedef dtl::tree
         <value_type_impl, select_1st_t, C2, Allocator, Options> base2_t;
      this->base_t::merge_unique(static_cast<base2_t&>(source));
   }

   //! @copydoc ::boost::container::map::merge(map<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG multimap<Key, T, C2, Allocator, Options> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<multimap<Key, T, C2, Allocator, Options>&>(source)); }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   void swap(map& x)
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

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type count(const key_type& x) const
   {  return static_cast<size_type>(this->find(x) != this->cend());  }

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

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   std::pair<iterator,iterator> equal_range(const key_type& x);

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   std::pair<const_iterator,const_iterator> equal_range(const key_type& x) const;

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   std::pair<iterator,iterator> equal_range(const K& x);

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   std::pair<const_iterator,const_iterator> equal_range(const K& x) const;

   //! <b>Effects</b>: Rebalances the tree. It's a no-op for Red-Black and AVL trees.
   //!
   //! <b>Complexity</b>: Linear
   void rebalance();

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const map& x, const map& y);

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const map& x, const map& y);

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const map& x, const map& y);

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const map& x, const map& y);

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const map& x, const map& y);

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const map& x, const map& y);

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(map& x, map& y)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   template<class KeyConvertible>
   BOOST_CONTAINER_FORCEINLINE mapped_type& priv_subscript(BOOST_FWD_REF(KeyConvertible) k)
   {
      return this->try_emplace(boost::forward<KeyConvertible>(k)).first->second;
   }
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
map(InputIterator, InputIterator) ->
   map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
    map(InputIterator, InputIterator, AllocatorOrCompare const&) ->
    map< it_based_non_const_first_type_t<InputIterator>
            , it_based_second_type_t<InputIterator>
            , typename dtl::if_c< // Compare
                dtl::is_allocator<AllocatorOrCompare>::value
                , std::less<it_based_non_const_first_type_t<InputIterator>>
                , AllocatorOrCompare
            >::type
            , typename dtl::if_c< // Allocator
                dtl::is_allocator<AllocatorOrCompare>::value
                , AllocatorOrCompare
                , new_allocator<std::pair<it_based_const_first_type_t<InputIterator>, it_based_second_type_t<InputIterator>>>
                >::type
            >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
map(InputIterator, InputIterator, Compare const&, Allocator const&) ->
   map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>
           , Compare
           , Allocator>;

template <typename InputIterator>
map(ordered_unique_range_t, InputIterator, InputIterator) ->
   map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
map(ordered_unique_range_t, InputIterator, InputIterator, AllocatorOrCompare const&) ->
   map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>
           , typename dtl::if_c<   // Compare
               dtl::is_allocator<AllocatorOrCompare>::value
               , std::less<it_based_non_const_first_type_t<InputIterator>>
               , AllocatorOrCompare
               >::type
           , typename dtl::if_c<   // Allocator
               dtl::is_allocator<AllocatorOrCompare>::value
               , AllocatorOrCompare
               , new_allocator<std::pair<it_based_const_first_type_t<InputIterator>, it_based_second_type_t<InputIterator>>>
               >::type
           >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
map(ordered_unique_range_t, InputIterator, InputIterator, Compare const&, Allocator const&) ->
   map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>
           , Compare
           , Allocator>;

#endif


#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class T, class Compare, class Allocator, class Options>
struct has_trivial_destructor_after_move<boost::container::map<Key, T, Compare, Allocator, Options> >
{
   typedef ::boost::container::dtl::tree<std::pair<const Key, T>, int, Compare, Allocator, Options> tree;
   static const bool value = ::boost::has_trivial_destructor_after_move<tree>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED

//! A multimap is a kind of associative container that supports equivalent keys
//! (possibly containing multiple copies of the same key value) and provides for
//! fast retrieval of values of another type T based on the keys. The multimap class
//! supports bidirectional iterators.
//!
//! A multimap satisfies all of the requirements of a container and of a reversible
//! container and of an associative container. The <code>value_type</code> stored
//! by this container is the value_type is std::pair<const Key, T>.
//!
//! \tparam Key is the key_type of the map
//! \tparam Value is the <code>mapped_type</code>
//! \tparam Compare is the ordering function for Keys (e.g. <i>std::less<Key></i>).
//! \tparam Allocator is the allocator to allocate the <code>value_type</code>s
//!   (e.g. <i>allocator< std::pair<const Key, T> > </i>).
//! \tparam Options is an packed option type generated using using boost::container::tree_assoc_options.
template < class Key, class T, class Compare = std::less<Key>
         , class Allocator = new_allocator< std::pair< const Key, T> >, class Options = tree_assoc_defaults>
#else
template <class Key, class T, class Compare, class Allocator, class Options>
#endif
class multimap
   ///@cond
   : public dtl::tree
      < std::pair<const Key, T>
      , int
      , Compare, Allocator, Options>
   ///@endcond
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(multimap)

   typedef int                                                                   select_1st_t;
   typedef std::pair<const Key, T>                                               value_type_impl;
   typedef dtl::tree
      <value_type_impl, select_1st_t, Compare, Allocator, Options>               base_t;
   typedef dtl::pair <Key, T>                                       movable_value_type_impl;
   typedef typename base_t::value_compare                                        value_compare_impl;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////

   typedef Key                                                                            key_type;
   typedef T                                                                              mapped_type;
   typedef typename base_t::allocator_type                                                allocator_type;
   typedef ::boost::container::allocator_traits<allocator_type>                           allocator_traits_type;
   typedef typename boost::container::allocator_traits<allocator_type>::value_type        value_type;
   typedef typename boost::container::allocator_traits<allocator_type>::pointer           pointer;
   typedef typename boost::container::allocator_traits<allocator_type>::const_pointer     const_pointer;
   typedef typename boost::container::allocator_traits<allocator_type>::reference         reference;
   typedef typename boost::container::allocator_traits<allocator_type>::const_reference   const_reference;
   typedef typename boost::container::allocator_traits<allocator_type>::size_type         size_type;
   typedef typename boost::container::allocator_traits<allocator_type>::difference_type   difference_type;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::stored_allocator_type)                 stored_allocator_type;
   typedef BOOST_CONTAINER_IMPDEF(value_compare_impl)                                     value_compare;
   typedef Compare                                                                        key_compare;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::iterator)                              iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::const_iterator)                        const_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::reverse_iterator)                      reverse_iterator;
   typedef typename BOOST_CONTAINER_IMPDEF(base_t::const_reverse_iterator)                const_reverse_iterator;
   //typedef std::pair<key_type, mapped_type>                                               nonconst_value_type;
   typedef BOOST_CONTAINER_IMPDEF(movable_value_type_impl)                                movable_value_type;
   typedef BOOST_CONTAINER_IMPDEF(node_handle<
      typename base_t::stored_allocator_type
      BOOST_MOVE_I pair_key_mapped_of_value
         <key_type BOOST_MOVE_I mapped_type> >)                                     node_type;

   //allocator_type::value_type type must be std::pair<CONST Key, T>
   BOOST_STATIC_ASSERT((dtl::is_same<typename allocator_type::value_type, std::pair<const Key, T> >::value));

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs an empty multimap.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE multimap()
      BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<allocator_type>::value &&
                        dtl::is_nothrow_default_constructible<Compare>::value)
      : base_t()
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified allocator
   //!   object and allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit multimap(const allocator_type& a)
      : base_t(a)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified comparison.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit multimap(const Compare& comp)
      : base_t(comp)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified comparison and allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE multimap(const Compare& comp, const allocator_type& a)
      : base_t(comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty multimap and
   //! inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multimap(InputIterator first, InputIterator last)
      : base_t(false, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified 
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multimap(InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(false, first, last, Compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified comparison object and
   //! inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multimap(InputIterator first, InputIterator last, const Compare& comp)
      : base_t(false, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified comparison object
   //!   and allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multimap(InputIterator first, InputIterator last,
            const Compare& comp, const allocator_type& a)
      : base_t(false, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty multimap and
   //! inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multimap(ordered_range_t, InputIterator first, InputIterator last)
      : base_t(ordered_range, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified comparison object and
   //! inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multimap(ordered_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : base_t(ordered_range, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified comparison object and
   //! allocator, and inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multimap(ordered_range_t, InputIterator first, InputIterator last, const Compare& comp,
         const allocator_type& a)
      : base_t(ordered_range, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified allocator and
   //! inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE multimap(ordered_range_t, InputIterator first, InputIterator last, const allocator_type& a)
      : base_t(ordered_range, first, last, Compare(), a)
   {}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs an empty multimap and
   //! and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is il.first() - il.end().
   BOOST_CONTAINER_FORCEINLINE multimap(std::initializer_list<value_type> il)
      : base_t(false, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is il.first() - il.end().
   BOOST_CONTAINER_FORCEINLINE multimap(std::initializer_list<value_type> il, const allocator_type& a)
      : base_t(false, il.begin(), il.end(), Compare(), a)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified comparison object and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is il.first() - il.end().
   BOOST_CONTAINER_FORCEINLINE multimap(std::initializer_list<value_type> il, const Compare& comp)
      : base_t(false, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty multimap using the specified comparison object and
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is il.first() - il.end().
   BOOST_CONTAINER_FORCEINLINE multimap(std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : base_t(false, il.begin(), il.end(), comp, a)
   {}


   //! <b>Effects</b>: Constructs an empty map and
   //! inserts elements from the ordered range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE multimap(ordered_range_t, std::initializer_list<value_type> il)
      : base_t(ordered_range, il.begin(), il.end())
   {}

   //! <b>Effects</b>: Constructs an empty map using the specified comparison object and
   //! inserts elements from the ordered range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE multimap(ordered_range_t, std::initializer_list<value_type> il, const Compare& comp)
      : base_t(ordered_range, il.begin(), il.end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty map and
   //! inserts elements from the ordered range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE multimap(ordered_range_t, std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : base_t(ordered_range, il.begin(), il.end(), comp, a)
   {}

#endif

   //! <b>Effects</b>: Copy constructs a multimap.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE multimap(const multimap& x)
      : base_t(static_cast<const base_t&>(x))
   {}

   //! <b>Effects</b>: Move constructs a multimap. Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Postcondition</b>: x is emptied.
   BOOST_CONTAINER_FORCEINLINE multimap(BOOST_RV_REF(multimap) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      : base_t(BOOST_MOVE_BASE(base_t, x))
   {}

   //! <b>Effects</b>: Copy constructs a multimap.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE multimap(const multimap& x, const allocator_type &a)
      : base_t(static_cast<const base_t&>(x), a)
   {}

   //! <b>Effects</b>: Move constructs a multimap using the specified allocator.
   //!                 Constructs *this using x's resources.
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise.
   //!
   //! <b>Postcondition</b>: x is emptied.
   BOOST_CONTAINER_FORCEINLINE multimap(BOOST_RV_REF(multimap) x, const allocator_type &a)
      : base_t(BOOST_MOVE_BASE(base_t, x), a)
   {}

   //! <b>Effects</b>: Makes *this a copy of x.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE multimap& operator=(BOOST_COPY_ASSIGN_REF(multimap) x)
   {  return static_cast<multimap&>(this->base_t::operator=(static_cast<const base_t&>(x)));  }

   //! <b>Effects</b>: this->swap(x.get()).
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE multimap& operator=(BOOST_RV_REF(multimap) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {  return static_cast<multimap&>(this->base_t::operator=(BOOST_MOVE_BASE(base_t, x)));  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Assign content of il to *this.
   //!
   BOOST_CONTAINER_FORCEINLINE multimap& operator=(std::initializer_list<value_type> il)
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

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator emplace(BOOST_FWD_REF(Args)... args)
   {  return this->base_t::emplace_equal(boost::forward<Args>(args)...); }

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the container.
   //!   p is a hint pointing to where the insert should start to search.
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

   #define BOOST_CONTAINER_MULTIMAP_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace(BOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_equal(BOOST_MOVE_FWD##N);   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return this->base_t::emplace_hint_equal(hint BOOST_MOVE_I##N BOOST_MOVE_FWD##N);  }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_MULTIMAP_EMPLACE_CODE)
   #undef BOOST_CONTAINER_MULTIMAP_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   //! <b>Effects</b>: Inserts x and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const value_type& x)
   { return this->base_t::insert_equal_convertible(x); }

   //! <b>Effects</b>: Inserts a new value move-constructed from x and returns
   //!   the iterator pointing to the newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE iterator insert(BOOST_RV_REF(value_type) x)
   { return this->base_t::insert_equal_convertible(boost::move(x)); }

   //! <b>Effects</b>: Inserts a new value constructed from x and returns
   //!   the iterator pointing to the newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class Pair>
   BOOST_CONTAINER_FORCEINLINE BOOST_CONTAINER_DOC1ST
         ( iterator
         , typename dtl::enable_if_c<
            dtl::is_convertible<Pair BOOST_MOVE_I value_type>::value  ||
            dtl::is_convertible<Pair BOOST_MOVE_I movable_value_type>::value
            BOOST_MOVE_I iterator >::type)
      insert(BOOST_FWD_REF(Pair) x)
   { return this->base_t::emplace_equal(boost::forward<Pair>(x)); }

   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, const value_type& x)
   { return this->base_t::insert_equal_hint_convertible(p, x); }

   //! <b>Effects</b>: Inserts a new value move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, BOOST_RV_REF(movable_value_type) x)
   { return this->base_t::insert_equal_hint_convertible(p, boost::move(x)); }

   //! <b>Effects</b>: Inserts a new value constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   template<class Pair>
   BOOST_CONTAINER_FORCEINLINE BOOST_CONTAINER_DOC1ST
         ( iterator
         , typename dtl::enable_if_c<
            dtl::is_convertible<Pair BOOST_MOVE_I value_type>::value  ||
            dtl::is_convertible<Pair BOOST_MOVE_I movable_value_type>::value
            BOOST_MOVE_I iterator>::type)
      insert(const_iterator p, BOOST_FWD_REF(Pair) x)
   { return this->base_t::emplace_hint_equal(p, boost::forward<Pair>(x)); }

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from first to last)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
   {  this->base_t::insert_equal_range(first, last); }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end().
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from il.begin() to il.end())
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_equal_range(il.begin(), il.end()); }
#endif

   //! <b>Requires</b>: nh is empty or this->get_allocator() == nh.get_allocator().
   //!
   //! <b>Effects/Returns</b>: If nh is empty, has no effect and returns end(). Otherwise, inserts 
   //!   the element owned by nh and returns an iterator pointing to the newly inserted element.
   //!   If a range containing elements with keys equivalent to nh.key() exists, 
   //!   the element is inserted at the end of that range. nh is always emptied.
   //!
   //! <b>Complexity</b>: Logarithmic
   iterator insert(BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {
      typename base_t::node_type n(boost::move(nh));
      return this->base_t::insert_equal_node(boost::move(n));
   }

   //! <b>Effects</b>: Same as `insert(node_type && nh)` but the element is inserted as close as possible
   //!   to the position just prior to "hint".
   //!
   //! <b>Complexity</b>: logarithmic in general, but amortized constant if the element is inserted
   //!   right before "hint".
   iterator insert(const_iterator hint, BOOST_RV_REF_BEG_IF_CXX11 node_type BOOST_RV_REF_END_IF_CXX11 nh)
   {
      typename base_t::node_type n(boost::move(nh));
      return this->base_t::insert_equal_node(hint, boost::move(n));
   }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! @copydoc ::boost::container::set::erase(const_iterator)
   iterator erase(const_iterator p);

   //! @copydoc ::boost::container::set::erase(const key_type&)
   size_type erase(const key_type& x);

   //! @copydoc ::boost::container::set::erase(const_iterator,const_iterator)
   iterator erase(const_iterator first, const_iterator last);
   #endif

   //! @copydoc ::boost::container::map::extract(const key_type&)
   node_type extract(const key_type& k)
   {
      typename base_t::node_type base_nh(this->base_t::extract(k));
      return node_type(boost::move(base_nh));
   }

   //! @copydoc ::boost::container::map::extract(const_iterator)
   node_type extract(const_iterator position)
   {
      typename base_t::node_type base_nh(this->base_t::extract(position));
      return node_type (boost::move(base_nh));
   }

   //! <b>Requires</b>: this->get_allocator() == source.get_allocator().
   //!
   //! <b>Effects</b>: Extracts each element in source and insert it into a using
   //!   the comparison object of *this.
   //! 
   //! <b>Postcondition</b>: Pointers and references to the transferred elements of source refer
   //!   to those same elements but as members of *this. Iterators referring to the transferred
   //!   elements will continue to refer to their elements, but they now behave as iterators into *this,
   //!   not into source.
   //!
   //! <b>Throws</b>: Nothing unless the comparison object throws.
   //!
   //! <b>Complexity</b>: N log(size() + N) (N has the value source.size())
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(multimap<Key, T, C2, Allocator, Options>& source)
   {
      typedef dtl::tree
         <value_type_impl, select_1st_t, C2, Allocator, Options> base2_t;
      this->base_t::merge_equal(static_cast<base2_t&>(source));
   }

   //! @copydoc ::boost::container::multimap::merge(multimap<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG multimap<Key, T, C2, Allocator, Options> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<multimap<Key, T, C2, Allocator, Options>&>(source)); }

   //! @copydoc ::boost::container::multimap::merge(multimap<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(map<Key, T, C2, Allocator, Options>& source)
   {
      typedef dtl::tree
         <value_type_impl, select_1st_t, C2, Allocator, Options> base2_t;
      this->base_t::merge_equal(static_cast<base2_t&>(source));
   }

   //! @copydoc ::boost::container::multimap::merge(multimap<Key, T, C2, Allocator, Options>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG map<Key, T, C2, Allocator, Options> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<map<Key, T, C2, Allocator, Options>&>(source)); }

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
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

   //! <b>Returns</b>: An iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   iterator find(const key_type& x);

   //! <b>Returns</b>: A const iterator pointing to an element with the key
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

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   size_type count(const key_type& x) const;

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   template<typename K>
   size_type count(const K& x) const;

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

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   std::pair<iterator,iterator> equal_range(const key_type& x);

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   std::pair<const_iterator,const_iterator> equal_range(const key_type& x) const;

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   std::pair<iterator,iterator> equal_range(const K& x);

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<typename K>
   std::pair<const_iterator,const_iterator> equal_range(const K& x) const;

   //! <b>Effects</b>: Rebalances the tree. It's a no-op for Red-Black and AVL trees.
   //!
   //! <b>Complexity</b>: Linear
   void rebalance();

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator==(const multimap& x, const multimap& y);

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator!=(const multimap& x, const multimap& y);

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<(const multimap& x, const multimap& y);

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>(const multimap& x, const multimap& y);

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator<=(const multimap& x, const multimap& y);

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   friend bool operator>=(const multimap& x, const multimap& y);

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   friend void swap(multimap& x, multimap& y)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value );

   #endif   //#if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
multimap(InputIterator, InputIterator) ->
   multimap< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
multimap(InputIterator, InputIterator, AllocatorOrCompare const&) ->
   multimap< it_based_non_const_first_type_t<InputIterator>
                , it_based_second_type_t<InputIterator>
                , typename dtl::if_c<   // Compare
                    dtl::is_allocator<AllocatorOrCompare>::value
                    , std::less<it_based_non_const_first_type_t<InputIterator>>
                    , AllocatorOrCompare
                    >::type
                , typename dtl::if_c<   // Allocator
                    dtl::is_allocator<AllocatorOrCompare>::value
                    , AllocatorOrCompare
                    , new_allocator<std::pair<it_based_const_first_type_t<InputIterator>, it_based_second_type_t<InputIterator>>>
                    >::type
                >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
multimap(InputIterator, InputIterator, Compare const&, Allocator const&) ->
   multimap< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>
           , Compare
           , Allocator>;

template <typename InputIterator>
multimap(ordered_range_t, InputIterator, InputIterator) ->
   multimap< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
multimap(ordered_range_t, InputIterator, InputIterator, AllocatorOrCompare const&) ->
   multimap< it_based_non_const_first_type_t<InputIterator>
                , it_based_second_type_t<InputIterator>
                , typename dtl::if_c<   // Compare
                    dtl::is_allocator<AllocatorOrCompare>::value
                    , std::less<it_based_const_first_type_t<InputIterator>>
                    , AllocatorOrCompare
                    >::type
                , typename dtl::if_c<   // Allocator
                    dtl::is_allocator<AllocatorOrCompare>::value
                    , AllocatorOrCompare
                    , new_allocator<std::pair<it_based_const_first_type_t<InputIterator>, it_based_second_type_t<InputIterator>>>
                    >::type
                >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
multimap(ordered_range_t, InputIterator, InputIterator, Compare const&, Allocator const&) ->
   multimap< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>
           , Compare
           , Allocator>;
#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class T, class Compare, class Allocator, class Options>
struct has_trivial_destructor_after_move<boost::container::multimap<Key, T, Compare, Allocator, Options> >
{
   typedef ::boost::container::dtl::tree<std::pair<const Key, T>, int, Compare, Allocator, Options> tree;
   static const bool value = ::boost::has_trivial_destructor_after_move<tree>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}}

#include <boost/container/detail/config_end.hpp>

#endif   // BOOST_CONTAINER_MAP_HPP


/* map.hpp
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
*/