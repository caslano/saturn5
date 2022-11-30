//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_FLAT_MAP_HPP
#define BOOST_CONTAINER_FLAT_MAP_HPP

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
#include <boost/container/throw_exception.hpp>
// container/detail
#include <boost/container/detail/flat_tree.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/algorithm.hpp> //equal()
#include <boost/container/detail/container_or_allocator_rebind.hpp>
// move
#include <boost/move/utility_core.hpp>
#include <boost/move/traits.hpp>
// move/detail
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
#include <boost/move/detail/move_helpers.hpp>
#include <boost/move/detail/force_ptr.hpp>
// intrusive
#include <boost/intrusive/detail/minimal_pair_header.hpp>      //pair
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>//less, equal
//others
#include <boost/core/no_exceptions_support.hpp>

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

template <class Key, class T, class Compare, class AllocatorOrContainer>
class flat_multimap;

namespace dtl{

template<class D, class S>
BOOST_CONTAINER_FORCEINLINE static D &force(S &s)
{  return *move_detail::force_ptr<D*>(&s); }

template<class D, class S>
BOOST_CONTAINER_FORCEINLINE static D force_copy(const S &s)
{
   const D *const vp = move_detail::force_ptr<const D *>(&s);
   D ret_val(*vp);
   return ret_val;
}

}  //namespace dtl{

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! A flat_map is a kind of associative container that supports unique keys (contains at
//! most one of each key value) and provides for fast retrieval of values of another
//! type T based on the keys.
//!
//! A flat_map satisfies all of the requirements of a container, a reversible
//! container and an associative container. A flat_map also provides
//! most operations described for unique keys. For a
//! flat_map<Key,T> the key_type is Key and the value_type is std::pair<Key,T>
//! (unlike std::map<Key, T> which value_type is std::pair<<b>const</b> Key, T>).
//!
//! flat_map is similar to std::map but it's implemented by as an ordered sequence container.
//! The underlying sequence container is by default <i>vector</i> but it can also work
//! user-provided vector-like SequenceContainers (like <i>static_vector</i> or <i>small_vector</i>).
//!
//! Using vector-like sequence containers means that inserting a new element into a flat_map might invalidate
//! previous iterators and references (unless that sequence container is <i>stable_vector</i> or a similar
//! container that offers stable pointers and references). Similarly, erasing an element might invalidate
//! iterators and references pointing to elements that come after (their keys are bigger) the erased element.
//!
//! This container provides random-access iterators.
//!
//! \tparam Key is the key_type of the map
//! \tparam Value is the <code>mapped_type</code>
//! \tparam Compare is the ordering function for Keys (e.g. <i>std::less<Key></i>).
//! \tparam AllocatorOrContainer is either:
//!   - The allocator to allocate <code>value_type</code>s (e.g. <i>allocator< std::pair<Key, T> > </i>).
//!     (in this case <i>sequence_type</i> will be vector<value_type, AllocatorOrContainer>)
//!   - The SequenceContainer to be used as the underlying <i>sequence_type</i>. It must be a vector-like
//!     sequence container with random-access iterators..
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template <class Key, class T, class Compare = std::less<Key>, class AllocatorOrContainer = new_allocator< std::pair< Key, T> > >
#else
template <class Key, class T, class Compare, class AllocatorOrContainer>
#endif
class flat_map
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(flat_map)
   //This is the tree that we should store if pair was movable
   typedef dtl::flat_tree<
                           std::pair<Key, T>,
                           dtl::select1st<Key>,
                           Compare,
                           AllocatorOrContainer> tree_t;

   //This is the real tree stored here. It's based on a movable pair
   typedef dtl::flat_tree<
                           dtl::pair<Key, T>,
                           dtl::select1st<Key>,
                           Compare,
                           typename dtl::container_or_allocator_rebind<AllocatorOrContainer, dtl::pair<Key, T> >::type
                           > impl_tree_t;
   impl_tree_t m_flat_tree;  // flat tree representing flat_map

   typedef typename impl_tree_t::value_type              impl_value_type;
   typedef typename impl_tree_t::const_iterator          impl_const_iterator;
   typedef typename impl_tree_t::iterator                impl_iterator;
   typedef typename impl_tree_t::allocator_type          impl_allocator_type;
   #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   typedef std::initializer_list<impl_value_type>        impl_initializer_list;
   #endif

   typedef dtl::flat_tree_value_compare
      < Compare
      , dtl::select1st<Key>
      , std::pair<Key, T> >                              value_compare_t;
   typedef typename tree_t::iterator                     iterator_t;
   typedef typename tree_t::const_iterator               const_iterator_t;
   typedef typename tree_t::reverse_iterator             reverse_iterator_t;
   typedef typename tree_t::const_reverse_iterator       const_reverse_iterator_t;

   public:
   typedef typename impl_tree_t::stored_allocator_type   impl_stored_allocator_type;
   typedef typename impl_tree_t::sequence_type           impl_sequence_type;

   BOOST_CONTAINER_FORCEINLINE impl_tree_t &tree()
   {  return m_flat_tree;  }

   BOOST_CONTAINER_FORCEINLINE const impl_tree_t &tree() const
   {  return m_flat_tree;  }

   private:
   typedef typename tree_t::get_stored_allocator_const_return_t         get_stored_allocator_const_return_t;
   typedef typename tree_t::get_stored_allocator_noconst_return_t       get_stored_allocator_noconst_return_t;
   typedef typename impl_tree_t::get_stored_allocator_const_return_t    impl_get_stored_allocator_const_return_t;
   typedef typename impl_tree_t::get_stored_allocator_noconst_return_t  impl_get_stored_allocator_noconst_return_t;

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:

   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef Key                                                                      key_type;
   typedef T                                                                        mapped_type;
   typedef Compare                                                                  key_compare;
   typedef std::pair<Key, T>                                                        value_type;
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
   typedef BOOST_CONTAINER_IMPDEF(impl_value_type)                                  movable_value_type;

   //AllocatorOrContainer::value_type must be std::pair<Key, T>
   BOOST_STATIC_ASSERT((dtl::is_same<std::pair<Key, T>, value_type>::value));

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs an empty flat_map.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE flat_map() BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<AllocatorOrContainer>::value &&
                                                            dtl::is_nothrow_default_constructible<Compare>::value)
      : m_flat_tree()
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit flat_map(const allocator_type& a)
      : m_flat_tree(dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified
   //! comparison object.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit flat_map(const Compare& comp)
      : m_flat_tree(comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified
   //! comparison object and allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE flat_map(const Compare& comp, const allocator_type& a)
      : m_flat_tree(comp, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_map and
   //! and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_map(InputIterator first, InputIterator last)
      : m_flat_tree(true, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_map(InputIterator first, InputIterator last, const allocator_type& a)
      : m_flat_tree(true, first, last, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_map(InputIterator first, InputIterator last, const Compare& comp)
      : m_flat_tree(true, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE flat_map(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : m_flat_tree(true, first, last, comp, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_map
   //! and inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_map(ordered_unique_range_t, InputIterator first, InputIterator last)
      : m_flat_tree(ordered_range, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_map(ordered_unique_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : m_flat_tree(ordered_range, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! allocator, and inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_map(ordered_unique_range_t, InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : m_flat_tree(ordered_range, first, last, comp, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified allocator and
   //! inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
      flat_map(ordered_unique_range_t, InputIterator first, InputIterator last, const allocator_type& a)
      : m_flat_tree(ordered_range, first, last, Compare(), a)
   {}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs an empty flat_map and
   //! inserts elements from the range [il.begin() ,il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   BOOST_CONTAINER_FORCEINLINE flat_map(std::initializer_list<value_type> il)
     : m_flat_tree( true
                  , dtl::force<impl_initializer_list>(il).begin()
                  , dtl::force<impl_initializer_list>(il).end())
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified
   //! allocator, and inserts elements from the range [il.begin() ,il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   BOOST_CONTAINER_FORCEINLINE flat_map(std::initializer_list<value_type> il, const allocator_type& a)
     : m_flat_tree( true
                  , dtl::force<impl_initializer_list>(il).begin()
                  , dtl::force<impl_initializer_list>(il).end()
                  , dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! inserts elements from the range [il.begin() ,il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   BOOST_CONTAINER_FORCEINLINE flat_map(std::initializer_list<value_type> il, const Compare& comp)
     : m_flat_tree(true
                  , dtl::force<impl_initializer_list>(il).begin()
                  , dtl::force<impl_initializer_list>(il).end()
                  , comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! allocator, and inserts elements from the range [il.begin() ,il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   BOOST_CONTAINER_FORCEINLINE flat_map(std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
     : m_flat_tree(true
                  , dtl::force<impl_initializer_list>(il).begin()
                  , dtl::force<impl_initializer_list>(il).end()
                  , comp
                  , dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using and
   //! inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_map(ordered_unique_range_t, std::initializer_list<value_type> il)
     : m_flat_tree(ordered_unique_range
                  , dtl::force<impl_initializer_list>(il).begin()
                  , dtl::force<impl_initializer_list>(il).end())
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_map(ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp)
     : m_flat_tree(ordered_unique_range
                  , dtl::force<impl_initializer_list>(il).begin()
                  , dtl::force<impl_initializer_list>(il).end()
                  , comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! allocator, and inserts elements from the ordered unique range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE flat_map(ordered_unique_range_t, std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
     : m_flat_tree( ordered_unique_range
                  , dtl::force<impl_initializer_list>(il).begin()
                  , dtl::force<impl_initializer_list>(il).end()
                  , comp
                  , dtl::force<const impl_allocator_type>(a))
   {}
#endif

   //! <b>Effects</b>: Copy constructs a flat_map.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE flat_map(const flat_map& x)
      : m_flat_tree(x.m_flat_tree)
   {}

   //! <b>Effects</b>: Move constructs a flat_map.
   //!   Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Postcondition</b>: x is emptied.
   BOOST_CONTAINER_FORCEINLINE flat_map(BOOST_RV_REF(flat_map) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      : m_flat_tree(boost::move(x.m_flat_tree))
   {}

   //! <b>Effects</b>: Copy constructs a flat_map using the specified allocator.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE flat_map(const flat_map& x, const allocator_type &a)
      : m_flat_tree(x.m_flat_tree, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Move constructs a flat_map using the specified allocator.
   //!   Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant if x.get_allocator() == a, linear otherwise.
   BOOST_CONTAINER_FORCEINLINE flat_map(BOOST_RV_REF(flat_map) x, const allocator_type &a)
      : m_flat_tree(boost::move(x.m_flat_tree), dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Makes *this a copy of x.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE flat_map& operator=(BOOST_COPY_ASSIGN_REF(flat_map) x)
   {  m_flat_tree = x.m_flat_tree;   return *this;  }

   //! <b>Effects</b>: Move constructs a flat_map.
   //!   Constructs *this using x's resources.
   //!
   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or value_type's move constructor throws)
   //!
   //! <b>Complexity</b>: Constant if allocator_traits_type::
   //!   propagate_on_container_move_assignment is true or
   //!   this->get>allocator() == x.get_allocator(). Linear otherwise.
   BOOST_CONTAINER_FORCEINLINE flat_map& operator=(BOOST_RV_REF(flat_map) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
   {  m_flat_tree = boost::move(x.m_flat_tree);   return *this;  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Assign elements from il to *this
   flat_map& operator=(std::initializer_list<value_type> il)
   {
      this->clear();
      this->insert(il.begin(), il.end());
      return *this;
   }
#endif

   //! <b>Effects</b>: Returns a copy of the allocator that
   //!   was passed to the object's constructor.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<allocator_type>(m_flat_tree.get_allocator()); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      get_stored_allocator_noconst_return_t get_stored_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {
      impl_get_stored_allocator_noconst_return_t r = m_flat_tree.get_stored_allocator();
      return dtl::force<stored_allocator_type>(r);
   }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      get_stored_allocator_const_return_t get_stored_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
   {
      impl_get_stored_allocator_const_return_t r = m_flat_tree.get_stored_allocator();
      return dtl::force<const stored_allocator_type>(r);
   }

   //////////////////////////////////////////////
   //
   //                iterators
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns an iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator begin() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<iterator>(m_flat_tree.begin()); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_iterator>(m_flat_tree.begin()); }

   //! <b>Effects</b>: Returns an iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator end() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<iterator>(m_flat_tree.end()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_iterator>(m_flat_tree.end()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<reverse_iterator>(m_flat_tree.rbegin()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_reverse_iterator>(m_flat_tree.rbegin()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<reverse_iterator>(m_flat_tree.rend()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_reverse_iterator>(m_flat_tree.rend()); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_iterator>(m_flat_tree.cbegin()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_iterator>(m_flat_tree.cend()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_reverse_iterator>(m_flat_tree.crbegin()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_reverse_iterator>(m_flat_tree.crend()); }

   //////////////////////////////////////////////
   //
   //                capacity
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns true if the container contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      bool empty() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_flat_tree.empty(); }

   //! <b>Effects</b>: Returns the number of the elements contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type size() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_flat_tree.size(); }

   //! <b>Effects</b>: Returns the largest possible size of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_flat_tree.max_size(); }

   //! <b>Effects</b>: Number of elements for which memory has been allocated.
   //!   capacity() is always greater than or equal to size().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type capacity() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_flat_tree.capacity(); }

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
   BOOST_CONTAINER_FORCEINLINE void reserve(size_type cnt)
      { m_flat_tree.reserve(cnt);   }

   //! <b>Effects</b>: Tries to deallocate the excess of memory created
   //    with previous allocations. The size of the vector is unchanged
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to size().
   BOOST_CONTAINER_FORCEINLINE void shrink_to_fit()
      { m_flat_tree.shrink_to_fit(); }

   //////////////////////////////////////////////
   //
   //               element access
   //
   //////////////////////////////////////////////

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! Effects: If there is no key equivalent to x in the flat_map, inserts
   //!   value_type(x, T()) into the flat_map.
   //!
   //! Returns: A reference to the mapped_type corresponding to x in *this.
   //!
   //! Complexity: Logarithmic search time plus linear insertion time in case no equivalent key is present.
   mapped_type &operator[](const key_type& k);

   //! Effects: If there is no key equivalent to x in the flat_map, inserts
   //! value_type(move(x), T()) into the flat_map (the key is move-constructed)
   //!
   //! Returns: A reference to the mapped_type corresponding to x in *this.
   //!
   //! Complexity: Logarithmic search time plus linear insertion time in case no equivalent key is present.
   mapped_type &operator[](key_type &&k);
   #elif defined(BOOST_MOVE_HELPERS_RETURN_SFINAE_BROKEN)
      //in compilers like GCC 3.4, we can't catch temporaries
      BOOST_CONTAINER_FORCEINLINE mapped_type& operator[](const key_type &k)         {  return this->priv_subscript(k);  }
      BOOST_CONTAINER_FORCEINLINE mapped_type& operator[](BOOST_RV_REF(key_type) k)  {  return this->priv_subscript(::boost::move(k));  }
   #else
      BOOST_MOVE_CONVERSION_AWARE_CATCH( operator[] , key_type, mapped_type&, this->priv_subscript)
   #endif

   //! Effects: If a key equivalent to k already exists in the container, assigns forward<M>(obj)
   //! to the mapped_type corresponding to the key k. If the key does not exist, inserts the new value
   //! as if by insert, constructing it from value_type(k, forward<M>(obj)).
   //! 
   //! No iterators or references are invalidated. If the insertion is successful, pointers and references
   //! to the element obtained while it is held in the node handle are invalidated, and pointers and
   //! references obtained to that element before it was extracted become valid.
   //!
   //! Returns: The bool component is true if the insertion took place and false if the assignment
   //!   took place. The iterator component is pointing at the element that was inserted or updated.
   //!
   //! Complexity: Logarithmic search time plus linear insertion time in case no equivalent key is present.
   template <class M>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> insert_or_assign(const key_type& k, BOOST_FWD_REF(M) obj)
   {
      return dtl::force_copy< std::pair<iterator, bool> >
         (this->m_flat_tree.insert_or_assign
            ( impl_const_iterator(), k, ::boost::forward<M>(obj))
         );
   }

   //! Effects: If a key equivalent to k already exists in the container, assigns forward<M>(obj)
   //! to the mapped_type corresponding to the key k. If the key does not exist, inserts the new value
   //! as if by insert, constructing it from value_type(k, move(obj)).
   //! 
   //! No iterators or references are invalidated. If the insertion is successful, pointers and references
   //! to the element obtained while it is held in the node handle are invalidated, and pointers and
   //! references obtained to that element before it was extracted become valid.
   //!
   //! Returns: The bool component is true if the insertion took place and false if the assignment
   //!   took place. The iterator component is pointing at the element that was inserted or updated.
   //!
   //! Complexity: Logarithmic in the size of the container.
   template <class M>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> insert_or_assign(BOOST_RV_REF(key_type) k, BOOST_FWD_REF(M) obj)
   {
      return dtl::force_copy< std::pair<iterator, bool> >
         (this->m_flat_tree.insert_or_assign
            ( impl_const_iterator(), ::boost::move(k), ::boost::forward<M>(obj))
         );
   }

   //! Effects: If a key equivalent to k already exists in the container, assigns forward<M>(obj)
   //! to the mapped_type corresponding to the key k. If the key does not exist, inserts the new value
   //! as if by insert, constructing it from value_type(k, forward<M>(obj)) and the new element
   //! to the container as close as possible to the position just before hint.
   //! 
   //! No iterators or references are invalidated. If the insertion is successful, pointers and references
   //! to the element obtained while it is held in the node handle are invalidated, and pointers and
   //! references obtained to that element before it was extracted become valid.
   //!
   //! Returns: The bool component is true if the insertion took place and false if the assignment
   //!   took place. The iterator component is pointing at the element that was inserted or updated.
   //!
   //! Complexity: Logarithmic in the size of the container in general, but amortized constant if
   //! the new element is inserted just before hint.
   template <class M>
   BOOST_CONTAINER_FORCEINLINE iterator insert_or_assign(const_iterator hint, const key_type& k, BOOST_FWD_REF(M) obj)
   {
      return dtl::force_copy<iterator>
         (this->m_flat_tree.insert_or_assign
            ( dtl::force_copy<impl_const_iterator>(hint)
            , k, ::boost::forward<M>(obj)).first
         );
   }

   //! Effects: If a key equivalent to k already exists in the container, assigns forward<M>(obj)
   //! to the mapped_type corresponding to the key k. If the key does not exist, inserts the new value
   //! as if by insert, constructing it from value_type(k, move(obj)) and the new element
   //! to the container as close as possible to the position just before hint.
   //! 
   //! No iterators or references are invalidated. If the insertion is successful, pointers and references
   //! to the element obtained while it is held in the node handle are invalidated, and pointers and
   //! references obtained to that element before it was extracted become valid.
   //!
   //! Returns: The bool component is true if the insertion took place and false if the assignment
   //!   took place. The iterator component is pointing at the element that was inserted or updated.
   //!
   //! Complexity: Logarithmic in the size of the container in general, but amortized constant if
   //! the new element is inserted just before hint.
   template <class M>
   BOOST_CONTAINER_FORCEINLINE iterator insert_or_assign(const_iterator hint, BOOST_RV_REF(key_type) k, BOOST_FWD_REF(M) obj)
   {
      return dtl::force_copy<iterator>
         (this->m_flat_tree.insert_or_assign
            ( dtl::force_copy<impl_const_iterator>(hint)
            , ::boost::move(k), ::boost::forward<M>(obj)).first
         );
   }

   //! @copydoc ::boost::container::flat_set::nth(size_type)
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator nth(size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {  return dtl::force_copy<iterator>(m_flat_tree.nth(n));  }

   //! @copydoc ::boost::container::flat_set::nth(size_type) const
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator nth(size_type n) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return dtl::force_copy<iterator>(m_flat_tree.nth(n));  }

   //! @copydoc ::boost::container::flat_set::index_of(iterator)
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type index_of(iterator p) BOOST_NOEXCEPT_OR_NOTHROW
   {  return m_flat_tree.index_of(dtl::force_copy<impl_iterator>(p));  }

   //! @copydoc ::boost::container::flat_set::index_of(const_iterator) const
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type index_of(const_iterator p) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return m_flat_tree.index_of(dtl::force_copy<impl_const_iterator>(p));  }

   //! Returns: A reference to the element whose key is equivalent to x.
   //!
   //! Throws: An exception object of type out_of_range if no such element is present.
   //!
   //! Complexity: logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD T& at(const key_type& k)
   {
      iterator i = this->find(k);
      if(i == this->end()){
         throw_out_of_range("flat_map::at key not found");
      }
      return i->second;
   }

   //! Returns: A reference to the element whose key is equivalent to x.
   //!
   //! Throws: An exception object of type out_of_range if no such element is present.
   //!
   //! Complexity: logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD const T& at(const key_type& k) const
   {
      const_iterator i = this->find(k);
      if(i == this->end()){
         throw_out_of_range("flat_map::at key not found");
      }
      return i->second;
   }

   //////////////////////////////////////////////
   //
   //                modifiers
   //
   //////////////////////////////////////////////

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object x of type T constructed with
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
   {  return dtl::force_copy< std::pair<iterator, bool> >(m_flat_tree.emplace_unique(boost::forward<Args>(args)...)); }

   //! <b>Effects</b>: Inserts an object of type T constructed with
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
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint, BOOST_FWD_REF(Args)... args)
   {
      return dtl::force_copy<iterator>
         (m_flat_tree.emplace_hint_unique( dtl::force_copy<impl_const_iterator>(hint)
                                         , boost::forward<Args>(args)...));
   }

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
   {
      return dtl::force_copy< std::pair<iterator, bool> >(
         m_flat_tree.try_emplace(impl_const_iterator(), k, boost::forward<Args>(args)...));
   }

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
   {
      return dtl::force_copy<iterator>(m_flat_tree.try_emplace
         (dtl::force_copy<impl_const_iterator>(hint), k, boost::forward<Args>(args)...).first);
   }

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
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion time in case the key is not present.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace(BOOST_RV_REF(key_type) k, BOOST_FWD_REF(Args)... args)
   {
      return dtl::force_copy< std::pair<iterator, bool> >
         (m_flat_tree.try_emplace(impl_const_iterator(), boost::move(k), boost::forward<Args>(args)...));
   }

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
   //!   is inserted right before p. Linear insertion time in case no equivalent key is present.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE iterator try_emplace(const_iterator hint, BOOST_RV_REF(key_type) k, BOOST_FWD_REF(Args)... args)
   {
      return dtl::force_copy<iterator>
         (m_flat_tree.try_emplace(dtl::force_copy
            <impl_const_iterator>(hint), boost::move(k), boost::forward<Args>(args)...).first);
   }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_FLAT_MAP_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> emplace(BOOST_MOVE_UREF##N)\
   {\
      return dtl::force_copy< std::pair<iterator, bool> >\
         (m_flat_tree.emplace_unique(BOOST_MOVE_FWD##N));\
   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      return dtl::force_copy<iterator>(m_flat_tree.emplace_hint_unique\
         (dtl::force_copy<impl_const_iterator>(hint) BOOST_MOVE_I##N BOOST_MOVE_FWD##N));\
   }\
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace(const key_type& k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      return dtl::force_copy< std::pair<iterator, bool> >\
         (m_flat_tree.try_emplace(impl_const_iterator(), k BOOST_MOVE_I##N BOOST_MOVE_FWD##N));\
   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator try_emplace(const_iterator hint, const key_type &k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return dtl::force_copy<iterator>(m_flat_tree.try_emplace\
         (dtl::force_copy<impl_const_iterator>(hint), k BOOST_MOVE_I##N BOOST_MOVE_FWD##N).first); }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator, bool> try_emplace(BOOST_RV_REF(key_type) k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      return dtl::force_copy< std::pair<iterator, bool> >\
         (m_flat_tree.try_emplace(impl_const_iterator(), boost::move(k) BOOST_MOVE_I##N BOOST_MOVE_FWD##N));\
   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator try_emplace(const_iterator hint, BOOST_RV_REF(key_type) k BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {  return dtl::force_copy<iterator>(m_flat_tree.try_emplace\
      (dtl::force_copy<impl_const_iterator>(hint), boost::move(k) BOOST_MOVE_I##N BOOST_MOVE_FWD##N).first); }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_FLAT_MAP_EMPLACE_CODE)
   #undef BOOST_CONTAINER_FLAT_MAP_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

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
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> insert(const value_type& x)
   {  return dtl::force_copy<std::pair<iterator,bool> >(
         m_flat_tree.insert_unique(dtl::force<const impl_value_type>(x))); }

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
   BOOST_CONTAINER_FORCEINLINE std::pair<iterator,bool> insert(BOOST_RV_REF(value_type) x)
   {
      return dtl::force_copy<std::pair<iterator,bool> >(
         m_flat_tree.insert_unique(boost::move(dtl::force<impl_value_type>(x))));
   }

   //! <b>Effects</b>: Inserts a new value_type constructed from the pair if and
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
   template <class Pair>
   BOOST_CONTAINER_FORCEINLINE BOOST_CONTAINER_DOC1ST
         ( std::pair<iterator BOOST_MOVE_I bool>
         , typename dtl::enable_if_c<dtl::is_convertible<Pair BOOST_MOVE_I impl_value_type>::value
            BOOST_MOVE_I std::pair<iterator BOOST_MOVE_I bool> >::type)
      insert(BOOST_FWD_REF(Pair) x)
   {
      return dtl::force_copy<std::pair<iterator,bool> >
         (m_flat_tree.emplace_unique(boost::forward<Pair>(x)));
   }

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
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, const value_type& x)
   {
      return dtl::force_copy<iterator>(
         m_flat_tree.insert_unique( dtl::force_copy<impl_const_iterator>(p)
                                  , dtl::force<const impl_value_type>(x)));
   }

   //! <b>Effects</b>: Inserts an element move constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant if x is inserted
   //!   right before p) plus insertion linear to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, BOOST_RV_REF(value_type) x)
   {
      return dtl::force_copy<iterator>
         (m_flat_tree.insert_unique( dtl::force_copy<impl_const_iterator>(p)
                                   , boost::move(dtl::force<impl_value_type>(x))));
   }

   //! <b>Effects</b>: Inserts an element constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant if x is inserted
   //!   right before p) plus insertion linear to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class Pair>
   BOOST_CONTAINER_FORCEINLINE BOOST_CONTAINER_DOC1ST
         ( iterator
         , typename dtl::enable_if_c<dtl::is_convertible<Pair BOOST_MOVE_I impl_value_type>::value
            BOOST_MOVE_I iterator>::type)
      insert(const_iterator p, BOOST_FWD_REF(Pair) x)
   {
      return dtl::force_copy<iterator>(
         m_flat_tree.emplace_hint_unique(dtl::force_copy<impl_const_iterator>(p), boost::forward<Pair>(x)));
   }

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: N log(size()+N).
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
   {  m_flat_tree.insert_unique(first, last);  }

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) if and only
   //!   if there is no element with key equivalent to the key of that element. This
   //!   function is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Complexity</b>: Linear.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(ordered_unique_range_t, InputIterator first, InputIterator last)
      {  m_flat_tree.insert_unique(ordered_unique_range, first, last); }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element.
   //!
   //! <b>Complexity</b>: N log(N).
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {
      m_flat_tree.insert_unique( dtl::force<impl_initializer_list>(il).begin()
                               , dtl::force<impl_initializer_list>(il).end());
   }

   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate and must be
   //! unique values.
   //!
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element. This
   //!   function is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Complexity</b>: Linear.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE void insert(ordered_unique_range_t, std::initializer_list<value_type> il)
   {
      m_flat_tree.insert_unique(ordered_unique_range
                               , dtl::force<impl_initializer_list>(il).begin()
                               , dtl::force<impl_initializer_list>(il).end());
   }
#endif

   //! <b>Requires</b>: this->get_allocator() == source.get_allocator().
   //!
   //! <b>Effects</b>: Move-inserts each element from source into *this a using
   //!   the comparison object of *this. If there is an element in a with key equivalent to the
   //!   key of an element from source, then that element is not moved from source.
   //!
   //! <b>Complexity</b>: Linear in this->size() + source.size().
   //!
   //! <b>Note</b>: Invalidates all iterators and references.
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(flat_map<Key, T, C2, AllocatorOrContainer>& source)
   {  m_flat_tree.merge_unique(source.tree());   }

   //! @copydoc ::boost::container::flat_map::merge(flat_map<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG flat_map<Key, T, C2, AllocatorOrContainer> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<flat_map<Key, T, C2, AllocatorOrContainer>&>(source)); }

   //! @copydoc ::boost::container::flat_map::merge(flat_map<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(flat_multimap<Key, T, C2, AllocatorOrContainer>& source)
   {  m_flat_tree.merge_unique(source.tree());   }

   //! @copydoc ::boost::container::flat_map::merge(flat_map<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG flat_multimap<Key, T, C2, AllocatorOrContainer> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<flat_multimap<Key, T, C2, AllocatorOrContainer>&>(source));  }

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
   BOOST_CONTAINER_FORCEINLINE iterator erase(const_iterator p)
   {
      return dtl::force_copy<iterator>
         (m_flat_tree.erase(dtl::force_copy<impl_const_iterator>(p)));
   }

   //! <b>Effects</b>: If present, erases the element in the container with key equivalent to x.
   //!
   //! <b>Returns</b>: Returns the number of erased elements (0/1).
   //!
   //! <b>Complexity</b>: Logarithmic search time plus erasure time
   //!   linear to the elements with bigger keys.
   BOOST_CONTAINER_FORCEINLINE size_type erase(const key_type& x)
      { return m_flat_tree.erase_unique(x); }

   //! <b>Effects</b>: Erases all the elements in the range [first, last).
   //!
   //! <b>Returns</b>: Returns last.
   //!
   //! <b>Complexity</b>: size()*N where N is the distance from first to last.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus erasure time
   //!   linear to the elements with bigger keys.
   BOOST_CONTAINER_FORCEINLINE iterator erase(const_iterator first, const_iterator last)
   {
      return dtl::force_copy<iterator>(
         m_flat_tree.erase( dtl::force_copy<impl_const_iterator>(first)
                          , dtl::force_copy<impl_const_iterator>(last)));
   }

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE void swap(flat_map& x)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value )
   { m_flat_tree.swap(x.m_flat_tree); }

   //! <b>Effects</b>: erase(begin(),end()).
   //!
   //! <b>Postcondition</b>: size() == 0.
   //!
   //! <b>Complexity</b>: linear in size().
   BOOST_CONTAINER_FORCEINLINE void clear() BOOST_NOEXCEPT_OR_NOTHROW
      { m_flat_tree.clear(); }

   //////////////////////////////////////////////
   //
   //                observers
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns the comparison object out
   //!   of which a was constructed.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      key_compare key_comp() const
      { return dtl::force_copy<key_compare>(m_flat_tree.key_comp()); }

   //! <b>Effects</b>: Returns an object of value_compare constructed out
   //!   of the comparison object.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      value_compare value_comp() const
      { return value_compare(dtl::force_copy<key_compare>(m_flat_tree.key_comp())); }

   //////////////////////////////////////////////
   //
   //              map operations
   //
   //////////////////////////////////////////////

   //! <b>Returns</b>: An iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator find(const key_type& x)
      { return dtl::force_copy<iterator>(m_flat_tree.find(x)); }

   //! <b>Returns</b>: A const_iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator find(const key_type& x) const
      { return dtl::force_copy<const_iterator>(m_flat_tree.find(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator find(const K& x)
      { return dtl::force_copy<iterator>(m_flat_tree.find(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: A const_iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator find(const K& x) const
      { return dtl::force_copy<const_iterator>(m_flat_tree.find(x)); }

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type count(const key_type& x) const
      {  return static_cast<size_type>(m_flat_tree.find(x) != m_flat_tree.end());  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type count(const K& x) const
      //Don't use find() != end optimization here as transparent comparators with key K might
      //return a different range than key_type (which can only return a single element range)
      {  return m_flat_tree.count(x);  }

   //! <b>Returns</b>: Returns true if there is an element with key
   //!   equivalent to key in the container, otherwise false.
   //!
   //! <b>Complexity</b>: log(size()).
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      bool contains(const key_type& x) const
      {  return m_flat_tree.find(x) != m_flat_tree.end();  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: Returns true if there is an element with key
   //!   equivalent to key in the container, otherwise false.
   //!
   //! <b>Complexity</b>: log(size()).
   template<typename K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      bool contains(const K& x) const
      {  return m_flat_tree.find(x) != m_flat_tree.end();  }

   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator lower_bound(const key_type& x)
      {  return dtl::force_copy<iterator>(m_flat_tree.lower_bound(x)); }

   //! <b>Returns</b>: A const iterator pointing to the first element with key not
   //!   less than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator lower_bound(const key_type& x) const
      {  return dtl::force_copy<const_iterator>(m_flat_tree.lower_bound(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator lower_bound(const K& x)
      {  return dtl::force_copy<iterator>(m_flat_tree.lower_bound(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: A const iterator pointing to the first element with key not
   //!   less than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator lower_bound(const K& x) const
      {  return dtl::force_copy<const_iterator>(m_flat_tree.lower_bound(x)); }

   //! <b>Returns</b>: An iterator pointing to the first element with key greater
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator upper_bound(const key_type& x)
      {  return dtl::force_copy<iterator>(m_flat_tree.upper_bound(x)); }

   //! <b>Returns</b>: A const iterator pointing to the first element with key
   //!   greater than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator upper_bound(const key_type& x) const
      {  return dtl::force_copy<const_iterator>(m_flat_tree.upper_bound(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to the first element with key greater
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator upper_bound(const K& x)
      {  return dtl::force_copy<iterator>(m_flat_tree.upper_bound(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: A const iterator pointing to the first element with key
   //!   greater than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator upper_bound(const K& x) const
      {  return dtl::force_copy<const_iterator>(m_flat_tree.upper_bound(x)); }

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<iterator,iterator> equal_range(const key_type& x)
      {  return dtl::force_copy<std::pair<iterator,iterator> >(m_flat_tree.lower_bound_range(x)); }

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const
      {  return dtl::force_copy<std::pair<const_iterator,const_iterator> >(m_flat_tree.lower_bound_range(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<iterator,iterator> equal_range(const K& x)
      //Don't use lower_bound_range optimization here as transparent comparators with key K might
      //return a different range than key_type (which can only return a single element range)
      {  return dtl::force_copy<std::pair<iterator,iterator> >(m_flat_tree.equal_range(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<const_iterator, const_iterator> equal_range(const K& x) const
      //Don't use lower_bound_range optimization here as transparent comparators with key K might
      //return a different range than key_type (which can only return a single element range)
      {  return dtl::force_copy<std::pair<const_iterator,const_iterator> >(m_flat_tree.equal_range(x)); }

   //! <b>Effects</b>: Extracts the internal sequence container.
   //!
   //! <b>Complexity</b>: Same as the move constructor of sequence_type, usually constant.
   //!
   //! <b>Postcondition</b>: this->empty()
   //!
   //! <b>Throws</b>: If secuence_type's move constructor throws 
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE sequence_type extract_sequence()
   {
      return boost::move(dtl::force<sequence_type>(m_flat_tree.get_sequence_ref()));
   }

   //! <b>Effects</b>: Discards the internally hold sequence container and adopts the
   //!   one passed externally using the move assignment. Erases non-unique elements.
   //!
   //! <b>Complexity</b>: Assuming O(1) move assignment, O(NlogN) with N = seq.size()
   //!
   //! <b>Throws</b>: If the comparison or the move constructor throws
   BOOST_CONTAINER_FORCEINLINE void adopt_sequence(BOOST_RV_REF(sequence_type) seq)
   {  this->m_flat_tree.adopt_sequence_unique(boost::move(dtl::force<impl_sequence_type>(seq)));  }

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
   {  this->m_flat_tree.adopt_sequence_unique(ordered_unique_range_t(), boost::move(dtl::force<impl_sequence_type>(seq)));  }

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator==(const flat_map& x, const flat_map& y)
   {  return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());  }

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator!=(const flat_map& x, const flat_map& y)
   {  return !(x == y); }

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator<(const flat_map& x, const flat_map& y)
   {  return ::boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator>(const flat_map& x, const flat_map& y)
   {  return y < x;  }

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator<=(const flat_map& x, const flat_map& y)
   {  return !(y < x);  }

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator>=(const flat_map& x, const flat_map& y)
   {  return !(x < y);  }

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE friend void swap(flat_map& x, flat_map& y)
       BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT(x.swap(y)))
   {  x.swap(y);  }

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   mapped_type &priv_subscript(const key_type& k)
   {
      iterator i = this->lower_bound(k);
      // i->first is greater than or equivalent to k.
      if (i == end() || key_comp()(k, (*i).first)){
         dtl::value_init<mapped_type> m;
         impl_value_type v(k, ::boost::move(m.m_t));
         i = this->insert(i, ::boost::move(v));
      }
      return (*i).second;
   }
   mapped_type &priv_subscript(BOOST_RV_REF(key_type) mk)
   {
      key_type &k = mk;
      iterator i = this->lower_bound(k);
      // i->first is greater than or equivalent to k.
      if (i == end() || key_comp()(k, (*i).first)){
         dtl::value_init<mapped_type> m;
         impl_value_type v(::boost::move(k), ::boost::move(m.m_t));
         i = this->insert(i, ::boost::move(v));
      }
      return (*i).second;
   }
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
flat_map(InputIterator, InputIterator) ->
   flat_map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
    flat_map(InputIterator, InputIterator, AllocatorOrCompare const&) ->
    flat_map< it_based_non_const_first_type_t<InputIterator>
            , it_based_second_type_t<InputIterator>
            , typename dtl::if_c< // Compare
                dtl::is_allocator<AllocatorOrCompare>::value
                , std::less<it_based_non_const_first_type_t<InputIterator>>
                , AllocatorOrCompare
            >::type
            , typename dtl::if_c< // Allocator
                dtl::is_allocator<AllocatorOrCompare>::value
                , AllocatorOrCompare
                , new_allocator<std::pair<it_based_non_const_first_type_t<InputIterator>, it_based_second_type_t<InputIterator>>>
                >::type
            >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
flat_map(InputIterator, InputIterator, Compare const&, Allocator const&) ->
   flat_map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>
           , Compare
           , Allocator>;

template <typename InputIterator>
flat_map(ordered_unique_range_t, InputIterator, InputIterator) ->
   flat_map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
flat_map(ordered_unique_range_t, InputIterator, InputIterator, AllocatorOrCompare const&) ->
   flat_map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>
           , typename dtl::if_c<   // Compare
               dtl::is_allocator<AllocatorOrCompare>::value
               , std::less<it_based_non_const_first_type_t<InputIterator>>
               , AllocatorOrCompare
               >::type
           , typename dtl::if_c<   // Allocator
               dtl::is_allocator<AllocatorOrCompare>::value
               , AllocatorOrCompare
               , new_allocator<std::pair<it_based_non_const_first_type_t<InputIterator>, it_based_second_type_t<InputIterator>>>
               >::type
           >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
flat_map(ordered_unique_range_t, InputIterator, InputIterator, Compare const&, Allocator const&) ->
   flat_map< it_based_non_const_first_type_t<InputIterator>
           , it_based_second_type_t<InputIterator>
           , Compare
           , Allocator>;

#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class T, class Compare, class AllocatorOrContainer>
struct has_trivial_destructor_after_move<boost::container::flat_map<Key, T, Compare, AllocatorOrContainer> >
{
   typedef ::boost::container::dtl::pair<Key, T> value_t;
   typedef typename ::boost::container::dtl::container_or_allocator_rebind<AllocatorOrContainer, value_t>::type alloc_or_cont_t;
   typedef ::boost::container::dtl::flat_tree<value_t,::boost::container::dtl::select1st<Key>, Compare, alloc_or_cont_t> tree;
   static const bool value = ::boost::has_trivial_destructor_after_move<tree>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! A flat_multimap is a kind of associative container that supports equivalent keys
//! (possibly containing multiple copies of the same key value) and provides for
//! fast retrieval of values of another type T based on the keys. 
//!
//! A flat_multimap satisfies all of the requirements of a container and of a reversible
//! container and of an associative container. For a
//! flat_multimap<Key,T> the key_type is Key and the value_type is std::pair<Key,T>
//! (unlike std::multimap<Key, T> which value_type is std::pair<<b>const</b> Key, T>).
//!
//! flat_multimap is similar to std::multimap but it's implemented by as an ordered sequence container.
//! The underlying sequence container is by default <i>vector</i> but it can also work
//! user-provided vector-like SequenceContainers (like <i>static_vector</i> or <i>small_vector</i>).
//!
//! Using vector-like sequence containers means that inserting a new element into a flat_multimap might invalidate
//! previous iterators and references (unless that sequence container is <i>stable_vector</i> or a similar
//! container that offers stable pointers and references). Similarly, erasing an element might invalidate
//! iterators and references pointing to elements that come after (their keys are bigger) the erased element.
//!
//! This container provides random-access iterators.
//!
//! \tparam Key is the key_type of the map
//! \tparam Value is the <code>mapped_type</code>
//! \tparam Compare is the ordering function for Keys (e.g. <i>std::less<Key></i>).
//! \tparam AllocatorOrContainer is either:
//!   - The allocator to allocate <code>value_type</code>s (e.g. <i>allocator< std::pair<Key, T> > </i>).
//!     (in this case <i>sequence_type</i> will be vector<value_type, AllocatorOrContainer>)
//!   - The SequenceContainer to be used as the underlying <i>sequence_type</i>. It must be a vector-like
//!     sequence container with random-access iterators.
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template <class Key, class T, class Compare = std::less<Key>, class AllocatorOrContainer = new_allocator< std::pair< Key, T> > >
#else
template <class Key, class T, class Compare, class AllocatorOrContainer>
#endif
class flat_multimap
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(flat_multimap)
   typedef dtl::flat_tree<
                           std::pair<Key, T>,
                           dtl::select1st<Key>,
                           Compare,
                           AllocatorOrContainer> tree_t;
   //This is the real tree stored here. It's based on a movable pair
   typedef dtl::flat_tree<
                           dtl::pair<Key, T>,
                           dtl::select1st<Key>,
                           Compare,
                           typename dtl::container_or_allocator_rebind<AllocatorOrContainer, dtl::pair<Key, T> >::type
                           > impl_tree_t;
   impl_tree_t m_flat_tree;  // flat tree representing flat_map

   typedef typename impl_tree_t::value_type              impl_value_type;
   typedef typename impl_tree_t::const_iterator          impl_const_iterator;
   typedef typename impl_tree_t::iterator                impl_iterator;
   typedef typename impl_tree_t::allocator_type          impl_allocator_type;
   #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   typedef std::initializer_list<impl_value_type>        impl_initializer_list;
   #endif

   typedef dtl::flat_tree_value_compare
      < Compare
      , dtl::select1st<Key>
      , std::pair<Key, T> >                                 value_compare_t;
   typedef typename tree_t::iterator                        iterator_t;
   typedef typename tree_t::const_iterator                  const_iterator_t;
   typedef typename tree_t::reverse_iterator                reverse_iterator_t;
   typedef typename tree_t::const_reverse_iterator          const_reverse_iterator_t;

   public:
   typedef typename impl_tree_t::stored_allocator_type      impl_stored_allocator_type;
   typedef typename impl_tree_t::sequence_type              impl_sequence_type;

   BOOST_CONTAINER_FORCEINLINE impl_tree_t &tree()
   {  return m_flat_tree;  }

   BOOST_CONTAINER_FORCEINLINE const impl_tree_t &tree() const
   {  return m_flat_tree;  }

   private:
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:

   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef Key                                                                      key_type;
   typedef T                                                                        mapped_type;
   typedef Compare                                                                  key_compare;
   typedef std::pair<Key, T>                                                        value_type;
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
   typedef BOOST_CONTAINER_IMPDEF(impl_value_type)                                  movable_value_type;

   //AllocatorOrContainer::value_type must be std::pair<Key, T>
   BOOST_STATIC_ASSERT((dtl::is_same<std::pair<Key, T>, value_type>::value));

   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs an empty flat_map.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE flat_multimap()
      BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<AllocatorOrContainer>::value &&
                        dtl::is_nothrow_default_constructible<Compare>::value)
      : m_flat_tree()
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit flat_multimap(const allocator_type& a)
      : m_flat_tree(dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison
   //!   object .
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit flat_multimap(const Compare& comp)
      : m_flat_tree(comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison
   //!   object and allocator.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(const Compare& comp, const allocator_type& a)
      : m_flat_tree(comp, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap
   //!   and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(InputIterator first, InputIterator last)
      : m_flat_tree(false, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified
   //!   allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(InputIterator first, InputIterator last, const allocator_type& a)
      : m_flat_tree(false, first, last, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison object
   //!   and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(InputIterator first, InputIterator last, const Compare& comp)
      : m_flat_tree(false, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison object
   //!   and allocator, and inserts elements from the range [first ,last ).
   //!
   //! <b>Complexity</b>: Linear in N if the range [first ,last ) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : m_flat_tree(false, first, last, comp, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap
   //! and inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(ordered_range_t, InputIterator first, InputIterator last)
      : m_flat_tree(ordered_range, first, last)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison object and
   //! inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(ordered_range_t, InputIterator first, InputIterator last, const Compare& comp)
      : m_flat_tree(ordered_range, first, last, comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison object and
   //! allocator, and inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(ordered_range_t, InputIterator first, InputIterator last, const Compare& comp, const allocator_type& a)
      : m_flat_tree(ordered_range, first, last, comp, a)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison object and
   //! inserts elements from the ordered range [first ,last). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE
      flat_multimap(ordered_range_t, InputIterator first, InputIterator last, const allocator_type &a)
      : m_flat_tree(ordered_range, first, last, Compare(), a)
   {}

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs an empty flat_map and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(std::initializer_list<value_type> il)
      : m_flat_tree( false
                   , dtl::force<impl_initializer_list>(il).begin()
                   , dtl::force<impl_initializer_list>(il).end())
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(std::initializer_list<value_type> il, const allocator_type& a)
      : m_flat_tree(false
                   , dtl::force<impl_initializer_list>(il).begin()
                   , dtl::force<impl_initializer_list>(il).end()
                   , dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(std::initializer_list<value_type> il, const Compare& comp)
      : m_flat_tree(false
                   , dtl::force<impl_initializer_list>(il).begin()
                   , dtl::force<impl_initializer_list>(il).end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_map using the specified comparison object and
   //! allocator, and inserts elements from the range [il.begin(), il.end()).
   //!
   //! <b>Complexity</b>: Linear in N if the range [il.begin(), il.end()) is already sorted using
   //! the predicate and otherwise N logN, where N is last - first.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : m_flat_tree( false
                   , dtl::force<impl_initializer_list>(il).begin()
                   , dtl::force<impl_initializer_list>(il).end()
                   , comp, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap and
   //! inserts elements from the ordered range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(ordered_range_t, std::initializer_list<value_type> il)
      : m_flat_tree( ordered_range
                   , dtl::force<impl_initializer_list>(il).begin()
                   , dtl::force<impl_initializer_list>(il).end())
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison object and
   //! inserts elements from the ordered range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(ordered_range_t, std::initializer_list<value_type> il, const Compare& comp)
      : m_flat_tree( ordered_range
                   , dtl::force<impl_initializer_list>(il).begin()
                   , dtl::force<impl_initializer_list>(il).end(), comp)
   {}

   //! <b>Effects</b>: Constructs an empty flat_multimap using the specified comparison object and
   //! allocator, and inserts elements from the ordered range [il.begin(), il.end()). This function
   //! is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Complexity</b>: Linear in N.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(ordered_range_t, std::initializer_list<value_type> il, const Compare& comp, const allocator_type& a)
      : m_flat_tree( ordered_range
                   , dtl::force<impl_initializer_list>(il).begin()
                   , dtl::force<impl_initializer_list>(il).end()
                   , comp, dtl::force<const impl_allocator_type>(a))
   {}
#endif

   //! <b>Effects</b>: Copy constructs a flat_multimap.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(const flat_multimap& x)
      : m_flat_tree(x.m_flat_tree)
   {}

   //! <b>Effects</b>: Move constructs a flat_multimap. Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Postcondition</b>: x is emptied.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(BOOST_RV_REF(flat_multimap) x)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<Compare>::value)
      : m_flat_tree(boost::move(x.m_flat_tree))
   {}

   //! <b>Effects</b>: Copy constructs a flat_multimap using the specified allocator.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(const flat_multimap& x, const allocator_type &a)
      : m_flat_tree(x.m_flat_tree, dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Move constructs a flat_multimap using the specified allocator.
   //!                 Constructs *this using x's resources.
   //!
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap(BOOST_RV_REF(flat_multimap) x, const allocator_type &a)
      : m_flat_tree(boost::move(x.m_flat_tree), dtl::force<const impl_allocator_type>(a))
   {}

   //! <b>Effects</b>: Makes *this a copy of x.
   //!
   //! <b>Complexity</b>: Linear in x.size().
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap& operator=(BOOST_COPY_ASSIGN_REF(flat_multimap) x)
      {  m_flat_tree = x.m_flat_tree;   return *this;  }

   //! <b>Effects</b>: this->swap(x.get()).
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap& operator=(BOOST_RV_REF(flat_multimap) x)
      BOOST_NOEXCEPT_IF( (allocator_traits_type::propagate_on_container_move_assignment::value ||
                          allocator_traits_type::is_always_equal::value) &&
                           boost::container::dtl::is_nothrow_move_assignable<Compare>::value)
      {  m_flat_tree = boost::move(x.m_flat_tree);   return *this;  }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Assign content of il to *this
   //!
   //! <b>Complexity</b>: Linear in il.size().
   BOOST_CONTAINER_FORCEINLINE
   flat_multimap& operator=(std::initializer_list<value_type> il)
   {
      this->clear();
      this->insert(il.begin(), il.end());
      return *this;
   }
#endif

   //! <b>Effects</b>: Returns a copy of the allocator that
   //!   was passed to the object's constructor.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   allocator_type get_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<allocator_type>(m_flat_tree.get_allocator()); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   stored_allocator_type &get_stored_allocator() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force<stored_allocator_type>(m_flat_tree.get_stored_allocator()); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const stored_allocator_type &get_stored_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force<const stored_allocator_type>(m_flat_tree.get_stored_allocator()); }

   //////////////////////////////////////////////
   //
   //                iterators
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns an iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   iterator begin() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<iterator>(m_flat_tree.begin()); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_iterator>(m_flat_tree.begin()); }

   //! <b>Effects</b>: Returns an iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   iterator end() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<iterator>(m_flat_tree.end()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_iterator>(m_flat_tree.end()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<reverse_iterator>(m_flat_tree.rbegin()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_reverse_iterator>(m_flat_tree.rbegin()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<reverse_iterator>(m_flat_tree.rend()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_reverse_iterator>(m_flat_tree.rend()); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_iterator>(m_flat_tree.cbegin()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_iterator>(m_flat_tree.cend()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_reverse_iterator>(m_flat_tree.crbegin()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_reverse_iterator crend() const BOOST_NOEXCEPT_OR_NOTHROW
      { return dtl::force_copy<const_reverse_iterator>(m_flat_tree.crend()); }

   //////////////////////////////////////////////
   //
   //                capacity
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns true if the container contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   bool empty() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_flat_tree.empty(); }

   //! <b>Effects</b>: Returns the number of the elements contained in the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   size_type size() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_flat_tree.size(); }

   //! <b>Effects</b>: Returns the largest possible size of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_flat_tree.max_size(); }

   //! <b>Effects</b>: Number of elements for which memory has been allocated.
   //!   capacity() is always greater than or equal to size().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   size_type capacity() const BOOST_NOEXCEPT_OR_NOTHROW
      { return m_flat_tree.capacity(); }

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
   BOOST_CONTAINER_FORCEINLINE
   void reserve(size_type cnt)
      { m_flat_tree.reserve(cnt);   }

   //! <b>Effects</b>: Tries to deallocate the excess of memory created
   //    with previous allocations. The size of the vector is unchanged
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to size().
   BOOST_CONTAINER_FORCEINLINE
   void shrink_to_fit()
      { m_flat_tree.shrink_to_fit(); }

   //! @copydoc ::boost::container::flat_set::nth(size_type)
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   iterator nth(size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {  return dtl::force_copy<iterator>(m_flat_tree.nth(n));  }

   //! @copydoc ::boost::container::flat_set::nth(size_type) const
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   const_iterator nth(size_type n) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return dtl::force_copy<iterator>(m_flat_tree.nth(n));  }

   //! @copydoc ::boost::container::flat_set::index_of(iterator)
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   size_type index_of(iterator p) BOOST_NOEXCEPT_OR_NOTHROW
   {  return m_flat_tree.index_of(dtl::force_copy<impl_iterator>(p));  }

   //! @copydoc ::boost::container::flat_set::index_of(const_iterator) const
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
   size_type index_of(const_iterator p) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return m_flat_tree.index_of(dtl::force_copy<impl_const_iterator>(p));  }

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE
   iterator emplace(BOOST_FWD_REF(Args)... args)
   {  return dtl::force_copy<iterator>(m_flat_tree.emplace_equal(boost::forward<Args>(args)...)); }

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant time if the value
   //!   is to be inserted before p) plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class... Args>
   BOOST_CONTAINER_FORCEINLINE
   iterator emplace_hint(const_iterator hint, BOOST_FWD_REF(Args)... args)
   {
      return dtl::force_copy<iterator>(m_flat_tree.emplace_hint_equal
         (dtl::force_copy<impl_const_iterator>(hint), boost::forward<Args>(args)...));
   }

   #else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #define BOOST_CONTAINER_FLAT_MULTIMAP_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace(BOOST_MOVE_UREF##N)\
   {  return dtl::force_copy<iterator>(m_flat_tree.emplace_equal(BOOST_MOVE_FWD##N));  }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   BOOST_CONTAINER_FORCEINLINE iterator emplace_hint(const_iterator hint BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      return dtl::force_copy<iterator>(m_flat_tree.emplace_hint_equal\
         (dtl::force_copy<impl_const_iterator>(hint) BOOST_MOVE_I##N BOOST_MOVE_FWD##N));\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_FLAT_MULTIMAP_EMPLACE_CODE)
   #undef BOOST_CONTAINER_FLAT_MULTIMAP_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   //! <b>Effects</b>: Inserts x and returns the iterator pointing to the
   //!   newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const value_type& x)
   {
      return dtl::force_copy<iterator>(
         m_flat_tree.insert_equal(dtl::force<const impl_value_type>(x)));
   }

   //! <b>Effects</b>: Inserts a new value constructed from x and returns
   //!   the iterator pointing to the newly inserted element.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template<class Pair>
   BOOST_CONTAINER_FORCEINLINE BOOST_CONTAINER_DOC1ST
         ( iterator
         , typename dtl::enable_if_c<dtl::is_convertible<Pair BOOST_MOVE_I impl_value_type>::value
            BOOST_MOVE_I iterator >::type)
      insert(BOOST_FWD_REF(Pair) x)
   { return dtl::force_copy<iterator>(m_flat_tree.emplace_equal(boost::forward<Pair>(x))); }

   //! <b>Effects</b>: Inserts a copy of x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant time if the value
   //!   is to be inserted before p) plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, const value_type& x)
   {
      return dtl::force_copy<iterator>
         (m_flat_tree.insert_equal( dtl::force_copy<impl_const_iterator>(p)
                                  , dtl::force<const impl_value_type>(x)));
   }

   //! <b>Effects</b>: Inserts a value constructed from x in the container.
   //!   p is a hint pointing to where the insert should start to search.
   //!
   //! <b>Returns</b>: An iterator pointing to the element with key equivalent
   //!   to the key of x.
   //!
   //! <b>Complexity</b>: Logarithmic search time (constant time if the value
   //!   is to be inserted before p) plus linear insertion
   //!   to the elements with bigger keys than x.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template<class Pair>
   BOOST_CONTAINER_FORCEINLINE BOOST_CONTAINER_DOC1ST
         ( iterator
         , typename dtl::enable_if_c<dtl::is_convertible<Pair BOOST_MOVE_I impl_value_type>::value
            BOOST_MOVE_I iterator>::type)
      insert(const_iterator p, BOOST_FWD_REF(Pair) x)
   {
      return dtl::force_copy<iterator>(
         m_flat_tree.emplace_hint_equal(dtl::force_copy<impl_const_iterator>(p), boost::forward<Pair>(x)));
   }

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) .
   //!
   //! <b>Complexity</b>: N log(N).
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(InputIterator first, InputIterator last)
      {  m_flat_tree.insert_equal(first, last); }

   //! <b>Requires</b>: first, last are not iterators into *this.
   //!
   //! <b>Requires</b>: [first ,last) must be ordered according to the predicate.
   //!
   //! <b>Effects</b>: inserts each element from the range [first,last) if and only
   //!   if there is no element with key equivalent to the key of that element. This
   //!   function is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Complexity</b>: Linear.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   //!
   //! <b>Note</b>: Non-standard extension.
   template <class InputIterator>
   BOOST_CONTAINER_FORCEINLINE void insert(ordered_range_t, InputIterator first, InputIterator last)
      {  m_flat_tree.insert_equal(ordered_range, first, last); }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()) .
   //!
   //! <b>Complexity</b>: N log(N).
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   BOOST_CONTAINER_FORCEINLINE void insert(std::initializer_list<value_type> il)
   {
      m_flat_tree.insert_equal( dtl::force<impl_initializer_list>(il).begin()
                              , dtl::force<impl_initializer_list>(il).end());
   }

   //! <b>Requires</b>: [il.begin(), il.end()) must be ordered according to the predicate.
   //!
   //! <b>Effects</b>: inserts each element from the range [il.begin(), il.end()) if and only
   //!   if there is no element with key equivalent to the key of that element. This
   //!   function is more efficient than the normal range creation for ordered ranges.
   //!
   //! <b>Complexity</b>: Linear.
   //!
   //! <b>Note</b>: If an element is inserted it might invalidate elements.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE void insert(ordered_range_t, std::initializer_list<value_type> il)
   {
      m_flat_tree.insert_equal( ordered_range
                              , dtl::force<impl_initializer_list>(il).begin()
                              , dtl::force<impl_initializer_list>(il).end());
   }
#endif

   //! <b>Requires</b>: this->get_allocator() == source.get_allocator().
   //!
   //! <b>Effects</b>: Move-inserts each element from source into *this a using
   //!   the comparison object of *this.
   //!
   //! <b>Complexity</b>: Linear in this->size() + source.size().
   //!
   //! <b>Note</b>: Invalidates all iterators and references.
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(flat_multimap<Key, T, C2, AllocatorOrContainer>& source)
   {  m_flat_tree.merge_equal(source.tree());   }

   //! @copydoc ::boost::container::flat_multimap::merge(flat_multimap<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG flat_multimap<Key, T, C2, AllocatorOrContainer> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<flat_multimap<Key, T, C2, AllocatorOrContainer>&>(source)); }

   //! @copydoc ::boost::container::flat_multimap::merge(flat_multimap<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(flat_map<Key, T, C2, AllocatorOrContainer>& source)
   {  m_flat_tree.merge_equal(source.tree());   }

   //! @copydoc ::boost::container::flat_multimap::merge(flat_map<Key, T, C2, AllocatorOrContainer>&)
   template<class C2>
   BOOST_CONTAINER_FORCEINLINE void merge(BOOST_RV_REF_BEG flat_map<Key, T, C2, AllocatorOrContainer> BOOST_RV_REF_END source)
   {  return this->merge(static_cast<flat_map<Key, T, C2, AllocatorOrContainer>&>(source)); }

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
   BOOST_CONTAINER_FORCEINLINE iterator erase(const_iterator p)
   {
      return dtl::force_copy<iterator>(
         m_flat_tree.erase(dtl::force_copy<impl_const_iterator>(p)));
   }

   //! <b>Effects</b>: Erases all elements in the container with key equivalent to x.
   //!
   //! <b>Returns</b>: Returns the number of erased elements.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus erasure time
   //!   linear to the elements with bigger keys.
   BOOST_CONTAINER_FORCEINLINE size_type erase(const key_type& x)
      { return m_flat_tree.erase(x); }

   //! <b>Effects</b>: Erases all the elements in the range [first, last).
   //!
   //! <b>Returns</b>: Returns last.
   //!
   //! <b>Complexity</b>: size()*N where N is the distance from first to last.
   //!
   //! <b>Complexity</b>: Logarithmic search time plus erasure time
   //!   linear to the elements with bigger keys.
   BOOST_CONTAINER_FORCEINLINE iterator erase(const_iterator first, const_iterator last)
   {
      return dtl::force_copy<iterator>
         (m_flat_tree.erase( dtl::force_copy<impl_const_iterator>(first)
                           , dtl::force_copy<impl_const_iterator>(last)));
   }

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE void swap(flat_multimap& x)
      BOOST_NOEXCEPT_IF(  allocator_traits_type::is_always_equal::value
                                 && boost::container::dtl::is_nothrow_swappable<Compare>::value )
   { m_flat_tree.swap(x.m_flat_tree); }

   //! <b>Effects</b>: erase(begin(),end()).
   //!
   //! <b>Postcondition</b>: size() == 0.
   //!
   //! <b>Complexity</b>: linear in size().
   BOOST_CONTAINER_FORCEINLINE void clear() BOOST_NOEXCEPT_OR_NOTHROW
      { m_flat_tree.clear(); }

   //////////////////////////////////////////////
   //
   //                observers
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns the comparison object out
   //!   of which a was constructed.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      key_compare key_comp() const
      { return dtl::force_copy<key_compare>(m_flat_tree.key_comp()); }

   //! <b>Effects</b>: Returns an object of value_compare constructed out
   //!   of the comparison object.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      value_compare value_comp() const
      { return value_compare(dtl::force_copy<key_compare>(m_flat_tree.key_comp())); }

   //////////////////////////////////////////////
   //
   //              map operations
   //
   //////////////////////////////////////////////

   //! <b>Returns</b>: An iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator find(const key_type& x)
      { return dtl::force_copy<iterator>(m_flat_tree.find(x)); }

   //! <b>Returns</b>: An const_iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator find(const key_type& x) const
      { return dtl::force_copy<const_iterator>(m_flat_tree.find(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator find(const K& x)
      { return dtl::force_copy<iterator>(m_flat_tree.find(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An const_iterator pointing to an element with the key
   //!   equivalent to x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic.
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator find(const K& x) const
      { return dtl::force_copy<const_iterator>(m_flat_tree.find(x)); }

   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type count(const key_type& x) const
      { return m_flat_tree.count(x); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: The number of elements with key equivalent to x.
   //!
   //! <b>Complexity</b>: log(size())+count(k)
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      size_type count(const K& x) const
      { return m_flat_tree.count(x); }

   //! <b>Returns</b>: Returns true if there is an element with key
   //!   equivalent to key in the container, otherwise false.
   //!
   //! <b>Complexity</b>: log(size()).
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD  BOOST_CONTAINER_FORCEINLINE
      bool contains(const key_type& x) const
      {  return m_flat_tree.find(x) != m_flat_tree.end();  }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: Returns true if there is an element with key
   //!   equivalent to key in the container, otherwise false.
   //!
   //! <b>Complexity</b>: log(size()).
   template<typename K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      bool contains(const K& x) const
      {  return m_flat_tree.find(x) != m_flat_tree.end();  }

   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator lower_bound(const key_type& x)
      {  return dtl::force_copy<iterator>(m_flat_tree.lower_bound(x)); }

   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator lower_bound(const key_type& x) const
      {  return dtl::force_copy<const_iterator>(m_flat_tree.lower_bound(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator lower_bound(const K& x)
      {  return dtl::force_copy<iterator>(m_flat_tree.lower_bound(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to the first element with key not less
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator lower_bound(const K& x) const
      {  return dtl::force_copy<const_iterator>(m_flat_tree.lower_bound(x)); }

   //! <b>Returns</b>: An iterator pointing to the first element with key greater
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator upper_bound(const key_type& x)
      {return dtl::force_copy<iterator>(m_flat_tree.upper_bound(x)); }

   //! <b>Returns</b>: A const iterator pointing to the first element with key
   //!   greater than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator upper_bound(const key_type& x) const
      {  return dtl::force_copy<const_iterator>(m_flat_tree.upper_bound(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: An iterator pointing to the first element with key greater
   //!   than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      iterator upper_bound(const K& x)
      {return dtl::force_copy<iterator>(m_flat_tree.upper_bound(x)); }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Returns</b>: A const iterator pointing to the first element with key
   //!   greater than x, or end() if such an element is not found.
   //!
   //! <b>Complexity</b>: Logarithmic
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      const_iterator upper_bound(const K& x) const
      {  return dtl::force_copy<const_iterator>(m_flat_tree.upper_bound(x)); }

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<iterator,iterator> equal_range(const key_type& x)
      {  return dtl::force_copy<std::pair<iterator,iterator> >(m_flat_tree.equal_range(x));   }

   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<const_iterator, const_iterator> equal_range(const key_type& x) const
      {  return dtl::force_copy<std::pair<const_iterator,const_iterator> >(m_flat_tree.equal_range(x));   }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<iterator,iterator> equal_range(const K& x)
      {  return dtl::force_copy<std::pair<iterator,iterator> >(m_flat_tree.equal_range(x));   }

   //! <b>Requires</b>: This overload is available only if
   //! key_compare::is_transparent exists.
   //!
   //! <b>Effects</b>: Equivalent to std::make_pair(this->lower_bound(k), this->upper_bound(k)).
   //!
   //! <b>Complexity</b>: Logarithmic
   template<class K>
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      std::pair<const_iterator, const_iterator> equal_range(const K& x) const
      {  return dtl::force_copy<std::pair<const_iterator,const_iterator> >(m_flat_tree.equal_range(x));   }

   //! <b>Effects</b>: Extracts the internal sequence container.
   //!
   //! <b>Complexity</b>: Same as the move constructor of sequence_type, usually constant.
   //!
   //! <b>Postcondition</b>: this->empty()
   //!
   //! <b>Throws</b>: If secuence_type's move constructor throws 
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      sequence_type extract_sequence()
   {
      return boost::move(dtl::force<sequence_type>(m_flat_tree.get_sequence_ref()));
   }

   //! <b>Effects</b>: Discards the internally hold sequence container and adopts the
   //!   one passed externally using the move assignment.
   //!
   //! <b>Complexity</b>: Assuming O(1) move assignment, O(NlogN) with N = seq.size()
   //!
   //! <b>Throws</b>: If the comparison or the move constructor throws
   BOOST_CONTAINER_FORCEINLINE void adopt_sequence(BOOST_RV_REF(sequence_type) seq)
   {  this->m_flat_tree.adopt_sequence_equal(boost::move(dtl::force<impl_sequence_type>(seq)));  }

   //! <b>Requires</b>: seq shall be ordered according to this->compare().
   //!
   //! <b>Effects</b>: Discards the internally hold sequence container and adopts the
   //!   one passed externally using the move assignment.
   //!
   //! <b>Complexity</b>: Assuming O(1) move assignment, O(1)
   //!
   //! <b>Throws</b>: If the move assignment throws
   BOOST_CONTAINER_FORCEINLINE void adopt_sequence(ordered_range_t, BOOST_RV_REF(sequence_type) seq)
   {  this->m_flat_tree.adopt_sequence_equal(ordered_range_t(), boost::move(dtl::force<impl_sequence_type>(seq)));  }

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator==(const flat_multimap& x, const flat_multimap& y)
   {  return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());  }

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator!=(const flat_multimap& x, const flat_multimap& y)
   {  return !(x == y); }

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator<(const flat_multimap& x, const flat_multimap& y)
   {  return ::boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator>(const flat_multimap& x, const flat_multimap& y)
   {  return y < x;  }

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator<=(const flat_multimap& x, const flat_multimap& y)
   {  return !(y < x);  }

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_ATTRIBUTE_NODISCARD BOOST_CONTAINER_FORCEINLINE
      friend bool operator>=(const flat_multimap& x, const flat_multimap& y)
   {  return !(x < y);  }

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE friend void swap(flat_multimap& x, flat_multimap& y)
       BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT(x.swap(y)))
   {  x.swap(y);  }
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
flat_multimap(InputIterator, InputIterator) ->
   flat_multimap< it_based_non_const_first_type_t<InputIterator>
                , it_based_second_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
flat_multimap(InputIterator, InputIterator, AllocatorOrCompare const&) ->
   flat_multimap< it_based_non_const_first_type_t<InputIterator>
                , it_based_second_type_t<InputIterator>
                , typename dtl::if_c<   // Compare
                    dtl::is_allocator<AllocatorOrCompare>::value
                    , std::less<it_based_non_const_first_type_t<InputIterator>>
                    , AllocatorOrCompare
                    >::type
                , typename dtl::if_c<   // Allocator
                    dtl::is_allocator<AllocatorOrCompare>::value
                    , AllocatorOrCompare
                    , new_allocator<std::pair<it_based_non_const_first_type_t<InputIterator>, it_based_second_type_t<InputIterator>>>
                    >::type
                >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
flat_multimap(InputIterator, InputIterator, Compare const&, Allocator const&) ->
   flat_multimap< it_based_non_const_first_type_t<InputIterator>
                , it_based_second_type_t<InputIterator>
                , Compare
                , Allocator>;

template <typename InputIterator>
flat_multimap(ordered_range_t, InputIterator, InputIterator) ->
   flat_multimap< it_based_non_const_first_type_t<InputIterator>
                , it_based_second_type_t<InputIterator>>;

template < typename InputIterator, typename AllocatorOrCompare>
flat_multimap(ordered_range_t, InputIterator, InputIterator, AllocatorOrCompare const&) ->
   flat_multimap< it_based_non_const_first_type_t<InputIterator>
                , it_based_second_type_t<InputIterator>
                , typename dtl::if_c<   // Compare
                    dtl::is_allocator<AllocatorOrCompare>::value
                    , std::less<it_based_non_const_first_type_t<InputIterator>>
                    , AllocatorOrCompare
                    >::type
                , typename dtl::if_c<   // Allocator
                    dtl::is_allocator<AllocatorOrCompare>::value
                    , AllocatorOrCompare
                    , new_allocator<std::pair<it_based_non_const_first_type_t<InputIterator>, it_based_second_type_t<InputIterator>>>
                    >::type
                >;

template < typename InputIterator, typename Compare, typename Allocator
         , typename = dtl::require_nonallocator_t<Compare>
         , typename = dtl::require_allocator_t<Allocator>>
flat_multimap(ordered_range_t, InputIterator, InputIterator, Compare const&, Allocator const&) ->
   flat_multimap< it_based_non_const_first_type_t<InputIterator>
                , it_based_second_type_t<InputIterator>
                , Compare
                , Allocator>;

#endif

}}

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace boost {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class Key, class T, class Compare, class AllocatorOrContainer>
struct has_trivial_destructor_after_move< boost::container::flat_multimap<Key, T, Compare, AllocatorOrContainer> >
{
   typedef ::boost::container::dtl::pair<Key, T> value_t;
   typedef typename ::boost::container::dtl::container_or_allocator_rebind<AllocatorOrContainer, value_t>::type alloc_or_cont_t;
   typedef ::boost::container::dtl::flat_tree<value_t,::boost::container::dtl::select1st<Key>, Compare, alloc_or_cont_t> tree;
   static const bool value = ::boost::has_trivial_destructor_after_move<tree>::value;
};

}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

#include <boost/container/detail/config_end.hpp>

#endif   // BOOST_CONTAINER_FLAT_MAP_HPP

/* flat_map.hpp
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
*/