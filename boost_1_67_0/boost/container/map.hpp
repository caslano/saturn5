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
   typedef std::pair<key_type, mapped_type>                                               nonconst_value_type;
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
   const T& at(const key_type& k) const
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
   { return this->base_t::insert_unique(x); }

   //! <b>Effects</b>: Inserts a new value_type created from the pair if and only if
   //! there is no element in the container  with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> insert(const nonconst_value_type& x)
   { return this->try_emplace(x.first, x.second); }

   //! <b>Effects</b>: Inserts a new value_type move constructed from the pair if and
   //! only if there is no element in the container with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> insert(BOOST_RV_REF(nonconst_value_type) x)
   { return this->try_emplace(boost::move(x.first), boost::move(x.second)); }

   //! <b>Effects</b>: Inserts a new value_type move constructed from the pair if and
   //! only if there is no element in the container with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> insert(BOOST_RV_REF(movable_value_type) x)
   { return this->try_emplace(boost::move(x.first), boost::move(x.second)); }

   //! <b>Effects</b>: Move constructs a new value from x if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!
   //! <b>Returns</b>: The bool component of the returned pair is true if and only
   //!   if the insertion takes place, and the iterator component of the pair
   //!   points to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> insert(BOOST_RV_REF(value_type) x)
   { return this->base_t::insert_unique(boost::move(x)); }

   //! <b>Effects</b>: Inserts a copy of x in the container if and only if there is
   //!   no element in the container with key equivalent to the key of x.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, const value_type& x)
   { return this->base_t::insert_unique(p, x); }

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
   iterator insert(const_iterator p, const nonconst_value_type& x)
   { return this->try_emplace(p, x.first, x.second); }

   //! <b>Effects</b>: Inserts an element move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, BOOST_RV_REF(value_type) x)
   { return this->base_t::insert_unique(p, boost::move(x)); }

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
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from il.begin() to il.end())
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_unique(il.begin(), il.end()); }
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

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Erases the element pointed to by p.
   //!
   //! <b>Returns</b>: Returns an iterator pointing to the element immediately
   //!   following q prior to the element being erased. If no such element exists,
   //!   returns end().
   //!
   //! <b>Complexity</b>: Amortized constant time
   iterator erase(const_iterator p) BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Erases all elements in the container with key equivalent to x.
   //!
   //! <b>Returns</b>: Returns the number of erased elements.
   //!
   //! <b>Complexity</b>: log(size()) + count(k)
   size_type erase(const key_type& x) BOOST_NOEXCEPT_OR_NOTHROW;

   //! <b>Effects</b>: Erases all the elements in the range [first, last).
   //!
   //! <b>Returns</b>: Returns last.
   //!
   //! <b>Complexity</b>: log(size())+N where N is the distance from first to last.
   iterator erase(const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW;

   #endif

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
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value )

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
   BOOST_CONTAINER_FORCEINLINE size_type count(const key_type& x) const
   {  return static_cast<size_type>(this->find(x) != this->cend());  }

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
   friend void swap(map& x, map& y);

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
   typedef std::pair<key_type, mapped_type>                                               nonconst_value_type;
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
   { return this->base_t::insert_equal(x); }

   //! <b>Effects</b>: Inserts a new value constructed from x and returns
   //!   the iterator pointing to the newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const nonconst_value_type& x)
   { return this->base_t::emplace_equal(x); }

   //! <b>Effects</b>: Inserts a new value move-constructed from x and returns
   //!   the iterator pointing to the newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_FORCEINLINE iterator insert(BOOST_RV_REF(nonconst_value_type) x)
   { return this->base_t::emplace_equal(boost::move(x)); }

   //! <b>Effects</b>: Inserts a new value move-constructed from x and returns
   //!   the iterator pointing to the newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic.
   iterator insert(BOOST_RV_REF(movable_value_type) x)
   { return this->base_t::emplace_equal(boost::move(x)); }

   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, const value_type& x)
   { return this->base_t::insert_equal(p, x); }

   //! <b>Effects</b>: Inserts a new value constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, const nonconst_value_type& x)
   { return this->base_t::emplace_hint_equal(p, x); }

   //! <b>Effects</b>: Inserts a new value move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, BOOST_RV_REF(nonconst_value_type) x)
   { return this->base_t::emplace_hint_equal(p, boost::move(x)); }

   //! <b>Effects</b>: Inserts a new value move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic in general, but amortized constant if t
   //!   is inserted right before p.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, BOOST_RV_REF(movable_value_type) x)
   { return this->base_t::emplace_hint_equal(p, boost::move(x)); }

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from first to last)
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
   {  this->base_t::insert_equal(first, last); }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end().
   //!
   //! <b>Complexity</b>: At most N log(size()+N) (N is the distance from il.begin() to il.end())
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {  this->base_t::insert_equal(il.begin(), il.end()); }
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
   friend void swap(multimap& x, multimap& y);

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