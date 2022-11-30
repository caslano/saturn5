/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_LIST_HPP
#define BOOST_INTRUSIVE_LIST_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <boost/intrusive/circular_list_algorithms.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>
#include <boost/intrusive/detail/default_header_holder.hpp>
#include <boost/intrusive/detail/reverse_iterator.hpp>
#include <boost/intrusive/detail/uncast.hpp>
#include <boost/intrusive/detail/list_iterator.hpp>
#include <boost/intrusive/detail/array_initializer.hpp>
#include <boost/intrusive/detail/exception_disposer.hpp>
#include <boost/intrusive/detail/equal_to_value.hpp>
#include <boost/intrusive/detail/key_nodeptr_comp.hpp>
#include <boost/intrusive/detail/simple_disposers.hpp>
#include <boost/intrusive/detail/size_holder.hpp>
#include <boost/intrusive/detail/algorithm.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#include <boost/intrusive/detail/value_functors.hpp>
#include <cstddef>   //std::size_t, etc.

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond

struct default_list_hook_applier
{  template <class T> struct apply{ typedef typename T::default_list_hook type;  };  };

template<>
struct is_default_hook_tag<default_list_hook_applier>
{  static const bool value = true;  };

struct list_defaults
{
   typedef default_list_hook_applier proto_value_traits;
   static const bool constant_time_size = true;
   typedef std::size_t size_type;
   typedef void header_holder_type;
};

/// @endcond

//! The class template list is an intrusive container that mimics most of the
//! interface of std::list as described in the C++ standard.
//!
//! The template parameter \c T is the type to be managed by the container.
//! The user can specify additional options and if no options are provided
//! default options are used.
//!
//! The container supports the following options:
//! \c base_hook<>/member_hook<>/value_traits<>,
//! \c constant_time_size<> and \c size_type<>.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
template<class T, class ...Options>
#else
template <class ValueTraits, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
#endif
class list_impl
{
   //Public typedefs
   public:
   typedef ValueTraits                                               value_traits;
   typedef typename value_traits::pointer                            pointer;
   typedef typename value_traits::const_pointer                      const_pointer;
   typedef typename pointer_traits<pointer>::element_type            value_type;
   typedef typename pointer_traits<pointer>::reference               reference;
   typedef typename pointer_traits<const_pointer>::reference         const_reference;
   typedef typename pointer_traits<pointer>::difference_type         difference_type;
   typedef SizeType                                                  size_type;
   typedef list_iterator<value_traits, false>                        iterator;
   typedef list_iterator<value_traits, true>                         const_iterator;
   typedef boost::intrusive::reverse_iterator<iterator>              reverse_iterator;
   typedef boost::intrusive::reverse_iterator<const_iterator>        const_reverse_iterator;
   typedef typename value_traits::node_traits                        node_traits;
   typedef typename node_traits::node                                node;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef circular_list_algorithms<node_traits>                     node_algorithms;
   typedef typename detail::get_header_holder_type
      < value_traits, HeaderHolder >::type                           header_holder_type;

   static const bool constant_time_size = ConstantTimeSize;
   static const bool stateful_value_traits = detail::is_stateful_value_traits<value_traits>::value;
   static const bool has_container_from_iterator =
        detail::is_same< header_holder_type, detail::default_header_holder< node_traits > >::value;

   /// @cond

   private:
   typedef detail::size_holder<constant_time_size, size_type>          size_traits;

   //noncopyable
   BOOST_MOVABLE_BUT_NOT_COPYABLE(list_impl)

   static const bool safemode_or_autounlink = is_safe_autounlink<value_traits::link_mode>::value;

   //Constant-time size is incompatible with auto-unlink hooks!
   BOOST_STATIC_ASSERT(!(constant_time_size &&
                        ((int)value_traits::link_mode == (int)auto_unlink)
                      ));

   node_ptr get_root_node()
   { return data_.root_plus_size_.m_header.get_node(); }

   const_node_ptr get_root_node() const
   { return data_.root_plus_size_.m_header.get_node(); }

   struct root_plus_size : public size_traits
   {
      header_holder_type m_header;
   };

   struct data_t : public value_traits
   {
      typedef typename list_impl::value_traits value_traits;
      explicit data_t(const value_traits &val_traits)
         :  value_traits(val_traits)
      {}

      root_plus_size root_plus_size_;
   } data_;

   BOOST_INTRUSIVE_FORCEINLINE size_traits &priv_size_traits() BOOST_NOEXCEPT
   {  return data_.root_plus_size_;  }

   BOOST_INTRUSIVE_FORCEINLINE const size_traits &priv_size_traits() const BOOST_NOEXCEPT
   {  return data_.root_plus_size_;  }

   BOOST_INTRUSIVE_FORCEINLINE const value_traits &priv_value_traits() const BOOST_NOEXCEPT
   {  return data_;  }

   BOOST_INTRUSIVE_FORCEINLINE value_traits &priv_value_traits() BOOST_NOEXCEPT
   {  return data_;  }

   typedef typename boost::intrusive::value_traits_pointers
      <ValueTraits>::const_value_traits_ptr const_value_traits_ptr;

   BOOST_INTRUSIVE_FORCEINLINE const_value_traits_ptr priv_value_traits_ptr() const BOOST_NOEXCEPT
   {  return pointer_traits<const_value_traits_ptr>::pointer_to(this->priv_value_traits());  }

   /// @endcond

   public:

   //! <b>Effects</b>: constructs an empty list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks).
   list_impl()
      :  data_(value_traits())
   {
      this->priv_size_traits().set_size(size_type(0));
      node_algorithms::init_header(this->get_root_node());
   }

   //! <b>Effects</b>: constructs an empty list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks).
   explicit list_impl(const value_traits &v_traits)
      :  data_(v_traits)
   {
      this->priv_size_traits().set_size(size_type(0));
      node_algorithms::init_header(this->get_root_node());
   }

   //! <b>Requires</b>: Dereferencing iterator must yield an lvalue of type value_type.
   //!
   //! <b>Effects</b>: Constructs a list equal to the range [first,last).
   //!
   //! <b>Complexity</b>: Linear in distance(b, e). No copy constructors are called.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks).
   template<class Iterator>
   list_impl(Iterator b, Iterator e, const value_traits &v_traits = value_traits())
      :  data_(v_traits)
   {
      //nothrow, no need to rollback to release elements on exception
      this->priv_size_traits().set_size(size_type(0));
      node_algorithms::init_header(this->get_root_node());
      //nothrow, no need to rollback to release elements on exception
      this->insert(this->cend(), b, e);
   }

   //! <b>Effects</b>: Constructs a container moving resources from another container.
   //!   Internal value traits are move constructed and
   //!   nodes belonging to x (except the node representing the "end") are linked to *this.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node's
   //!   move constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the move constructor of value traits throws.
   list_impl(BOOST_RV_REF(list_impl) x)
      : data_(::boost::move(x.priv_value_traits()))
   {
      this->priv_size_traits().set_size(size_type(0));
      node_algorithms::init_header(this->get_root_node());
      //nothrow, no need to rollback to release elements on exception
      this->swap(x);
   }

   //! <b>Effects</b>: Equivalent to swap
   //!
   list_impl& operator=(BOOST_RV_REF(list_impl) x)
   {  this->swap(x); return *this;  }

   //! <b>Effects</b>: If it's not a safe-mode or an auto-unlink value_type
   //!   the destructor does nothing
   //!   (ie. no code is generated). Otherwise it detaches all elements from this.
   //!   In this case the objects in the list are not deleted (i.e. no destructors
   //!   are called), but the hooks according to the ValueTraits template parameter
   //!   are set to their default value.
   //!
   //! <b>Throws</b>: Nothing.
   //! 
   //! <b>Complexity</b>: Linear to the number of elements in the list, if
   //!   it's a safe-mode or auto-unlink value . Otherwise constant.
   ~list_impl()
   {
      BOOST_IF_CONSTEXPR(is_safe_autounlink<ValueTraits::link_mode>::value){
         this->clear();
         node_algorithms::init(this->get_root_node());
      }
   }

   //! <b>Requires</b>: value must be an lvalue.
   //!
   //! <b>Effects</b>: Inserts the value in the back of the list.
   //!   No copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void push_back(reference value) BOOST_NOEXCEPT
   {
      node_ptr to_insert = priv_value_traits().to_node_ptr(value);
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::inited(to_insert));
      node_algorithms::link_before(this->get_root_node(), to_insert);
      this->priv_size_traits().increment();
   }

   //! <b>Requires</b>: value must be an lvalue.
   //!
   //! <b>Effects</b>: Inserts the value in the front of the list.
   //!   No copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void push_front(reference value) BOOST_NOEXCEPT
   {
      node_ptr to_insert = priv_value_traits().to_node_ptr(value);
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::inited(to_insert));
      node_algorithms::link_before(node_traits::get_next(this->get_root_node()), to_insert);
      this->priv_size_traits().increment();
   }

   //! <b>Effects</b>: Erases the last element of the list.
   //!   No destructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the erased element.
   void pop_back() BOOST_NOEXCEPT
   {  return this->pop_back_and_dispose(detail::null_disposer());   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the last element of the list.
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Invalidates the iterators to the erased element.
   template<class Disposer>
   void pop_back_and_dispose(Disposer disposer) BOOST_NOEXCEPT
   {
      node_ptr to_erase = node_traits::get_previous(this->get_root_node());
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      BOOST_IF_CONSTEXPR(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(priv_value_traits().to_value_ptr(to_erase));
   }

   //! <b>Effects</b>: Erases the first element of the list.
   //!   No destructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the erased element.
   void pop_front() BOOST_NOEXCEPT
   {  return this->pop_front_and_dispose(detail::null_disposer());   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the first element of the list.
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Invalidates the iterators to the erased element.
   template<class Disposer>
   void pop_front_and_dispose(Disposer disposer) BOOST_NOEXCEPT
   {
      node_ptr to_erase = node_traits::get_next(this->get_root_node());
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      BOOST_IF_CONSTEXPR(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(priv_value_traits().to_value_ptr(to_erase));
   }

   //! <b>Effects</b>: Returns a reference to the first element of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE reference front() BOOST_NOEXCEPT
   { return *priv_value_traits().to_value_ptr(node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_reference to the first element of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_reference front() const BOOST_NOEXCEPT
   { return *priv_value_traits().to_value_ptr(node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns a reference to the last element of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE reference back() BOOST_NOEXCEPT
   { return *priv_value_traits().to_value_ptr(node_traits::get_previous(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_reference to the last element of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_reference back() const BOOST_NOEXCEPT
   { return *priv_value_traits().to_value_ptr(detail::uncast(node_traits::get_previous(this->get_root_node()))); }

   //! <b>Effects</b>: Returns an iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE iterator begin() BOOST_NOEXCEPT
   { return iterator(node_traits::get_next(this->get_root_node()), this->priv_value_traits_ptr()); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_iterator begin() const BOOST_NOEXCEPT
   { return this->cbegin(); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_iterator cbegin() const BOOST_NOEXCEPT
   { return const_iterator(node_traits::get_next(this->get_root_node()), this->priv_value_traits_ptr()); }

   //! <b>Effects</b>: Returns an iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE iterator end() BOOST_NOEXCEPT
   { return iterator(this->get_root_node(), this->priv_value_traits_ptr()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_iterator end() const BOOST_NOEXCEPT
   { return this->cend(); }

   //! <b>Effects</b>: Returns a constant iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_iterator cend() const BOOST_NOEXCEPT
   { return const_iterator(detail::uncast(this->get_root_node()), this->priv_value_traits_ptr()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE reverse_iterator rbegin() BOOST_NOEXCEPT
   { return reverse_iterator(this->end()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator rbegin() const BOOST_NOEXCEPT
   { return this->crbegin(); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator crbegin() const BOOST_NOEXCEPT
   { return const_reverse_iterator(end()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE reverse_iterator rend() BOOST_NOEXCEPT
   { return reverse_iterator(begin()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator rend() const BOOST_NOEXCEPT
   { return this->crend(); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE const_reverse_iterator crend() const BOOST_NOEXCEPT
   { return const_reverse_iterator(this->begin()); }

   //! <b>Precondition</b>: end_iterator must be a valid end iterator
   //!   of list.
   //!
   //! <b>Effects</b>: Returns a const reference to the list associated to the end iterator
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE static list_impl &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return list_impl::priv_container_from_end_iterator(end_iterator);   }

   //! <b>Precondition</b>: end_iterator must be a valid end const_iterator
   //!   of list.
   //!
   //! <b>Effects</b>: Returns a const reference to the list associated to the end iterator
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_INTRUSIVE_FORCEINLINE static const list_impl &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return list_impl::priv_container_from_end_iterator(end_iterator);   }

   //! <b>Effects</b>: Returns the number of the elements contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements contained in the list.
   //!   if constant-time size option is disabled. Constant time otherwise.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   BOOST_INTRUSIVE_FORCEINLINE size_type size() const BOOST_NOEXCEPT
   {
      BOOST_IF_CONSTEXPR(constant_time_size)
         return this->priv_size_traits().get_size();
      else
         return node_algorithms::count(this->get_root_node()) - 1;
   }

   //! <b>Effects</b>: Returns true if the list contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   BOOST_INTRUSIVE_FORCEINLINE bool empty() const BOOST_NOEXCEPT
   {  return node_algorithms::unique(this->get_root_node());   }

   //! <b>Effects</b>: Swaps the elements of x and *this.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void swap(list_impl& other) BOOST_NOEXCEPT
   {
      node_algorithms::swap_nodes(this->get_root_node(), other.get_root_node());
      this->priv_size_traits().swap(other.priv_size_traits());
   }

   //! <b>Effects</b>: Moves backwards all the elements, so that the first
   //!   element becomes the second, the second becomes the third...
   //!   the last element becomes the first one.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of shifts.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   BOOST_INTRUSIVE_FORCEINLINE void shift_backwards(size_type n = 1) BOOST_NOEXCEPT
   {  node_algorithms::move_forward(this->get_root_node(), n);  }

   //! <b>Effects</b>: Moves forward all the elements, so that the second
   //!   element becomes the first, the third becomes the second...
   //!   the first element becomes the last one.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of shifts.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   BOOST_INTRUSIVE_FORCEINLINE void shift_forward(size_type n = 1) BOOST_NOEXCEPT
   {  node_algorithms::move_backwards(this->get_root_node(), n);  }

   //! <b>Effects</b>: Erases the element pointed by i of the list.
   //!   No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed element,
   //!   or end() if no such element exists.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased element.
   BOOST_INTRUSIVE_FORCEINLINE iterator erase(const_iterator i) BOOST_NOEXCEPT
   {  return this->erase_and_dispose(i, detail::null_disposer());  }

   //! <b>Requires</b>: b and e must be valid iterators to elements in *this.
   //!
   //! <b>Effects</b>: Erases the element range pointed by b and e
   //! No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of erased elements if it's a safe-mode
   //!   or auto-unlink value, or constant-time size is enabled. Constant-time otherwise.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased elements.
   BOOST_INTRUSIVE_FORCEINLINE iterator erase(const_iterator b, const_iterator e) BOOST_NOEXCEPT
   {
      BOOST_IF_CONSTEXPR(safemode_or_autounlink || constant_time_size){
         return this->erase_and_dispose(b, e, detail::null_disposer());
      }
      else{
         node_algorithms::unlink(b.pointed_node(), e.pointed_node());
         return e.unconst();
      }
   }

   //! <b>Requires</b>: b and e must be valid iterators to elements in *this.
   //!   n must be distance(b, e).
   //!
   //! <b>Effects</b>: Erases the element range pointed by b and e
   //! No destructors are called.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of erased elements if it's a safe-mode
   //!   or auto-unlink value is enabled. Constant-time otherwise.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the
   //!   erased elements.
   iterator erase(const_iterator b, const_iterator e, size_type n) BOOST_NOEXCEPT
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(node_algorithms::distance(b.pointed_node(), e.pointed_node()) == n);
      (void)n;
      BOOST_IF_CONSTEXPR(safemode_or_autounlink){
         return this->erase_and_dispose(b, e, detail::null_disposer());
      }
      else{
         BOOST_IF_CONSTEXPR(constant_time_size){
            this->priv_size_traits().decrease(n);
         }
         node_algorithms::unlink(b.pointed_node(), e.pointed_node());
         return e.unconst();
      }
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element pointed by i of the list.
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed element.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed element,
   //!   or end() if no such element exists.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Invalidates the iterators to the erased element.
   template <class Disposer>
   iterator erase_and_dispose(const_iterator i, Disposer disposer) BOOST_NOEXCEPT
   {
      node_ptr to_erase(i.pointed_node());
      ++i;
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      BOOST_IF_CONSTEXPR(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(this->priv_value_traits().to_value_ptr(to_erase));
      return i.unconst();
   }

   #if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   template<class Disposer>
   iterator erase_and_dispose(iterator i, Disposer disposer) BOOST_NOEXCEPT
   {  return this->erase_and_dispose(const_iterator(i), disposer);   }
   #endif

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases the element range pointed by b and e
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Returns</b>: the first element remaining beyond the removed elements,
   //!   or end() if no such element exists.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements erased.
   //!
   //! <b>Note</b>: Invalidates the iterators to the erased elements.
   template <class Disposer>
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer) BOOST_NOEXCEPT
   {
      node_ptr bp(b.pointed_node()), ep(e.pointed_node());
      node_algorithms::unlink(bp, ep);
      while(bp != ep){
         node_ptr to_erase(bp);
         bp = node_traits::get_next(bp);
         BOOST_IF_CONSTEXPR(safemode_or_autounlink)
            node_algorithms::init(to_erase);
         disposer(priv_value_traits().to_value_ptr(to_erase));
         this->priv_size_traits().decrement();
      }
      return e.unconst();
   }

   //! <b>Effects</b>: Erases all the elements of the container.
   //!   No destructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements of the list.
   //!   if it's a safe-mode or auto-unlink value_type. Constant time otherwise.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references) to the erased elements.
   void clear() BOOST_NOEXCEPT
   {
      BOOST_IF_CONSTEXPR(safemode_or_autounlink){
         this->clear_and_dispose(detail::null_disposer());
      }
      else{
         node_algorithms::init_header(this->get_root_node());
         this->priv_size_traits().set_size(size_type(0));
      }
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Erases all the elements of the container.
   //!   No destructors are called.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements of the list.
   //!
   //! <b>Note</b>: Invalidates the iterators to the erased elements.
   template <class Disposer>
   void clear_and_dispose(Disposer disposer) BOOST_NOEXCEPT
   {
      const_iterator it(this->begin()), itend(this->end());
      while(it != itend){
         node_ptr to_erase(it.pointed_node());
         ++it;
         BOOST_IF_CONSTEXPR(safemode_or_autounlink)
            node_algorithms::init(to_erase);
         disposer(priv_value_traits().to_value_ptr(to_erase));
      }
      node_algorithms::init_header(this->get_root_node());
      this->priv_size_traits().set_size(0);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!   Cloner should yield to nodes equivalent to the original nodes.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Disposer::operator()(pointer), clones all the
   //!   elements from src calling Cloner::operator()(const_reference )
   //!   and inserts them on *this.
   //!
   //!   If cloner throws, all cloned elements are unlinked and disposed
   //!   calling Disposer::operator()(pointer).
   //!
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //!
   //! <b>Throws</b>: If cloner throws. Basic guarantee.
   template <class Cloner, class Disposer>
   void clone_from(const list_impl &src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      detail::exception_disposer<list_impl, Disposer>
         rollback(*this, disposer);
      const_iterator b(src.begin()), e(src.end());
      for(; b != e; ++b){
         this->push_back(*cloner(*b));
      }
      rollback.release();
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!   Cloner should yield to nodes equivalent to the original nodes.
   //!
   //! <b>Effects</b>: Erases all the elements from *this
   //!   calling Disposer::operator()(pointer), clones all the
   //!   elements from src calling Cloner::operator()(reference)
   //!   and inserts them on *this.
   //!
   //!   If cloner throws, all cloned elements are unlinked and disposed
   //!   calling Disposer::operator()(pointer).
   //!
   //! <b>Complexity</b>: Linear to erased plus inserted elements.
   //!
   //! <b>Throws</b>: If cloner throws. Basic guarantee.
   template <class Cloner, class Disposer>
   void clone_from(BOOST_RV_REF(list_impl) src, Cloner cloner, Disposer disposer)
   {
      this->clear_and_dispose(disposer);
      detail::exception_disposer<list_impl, Disposer>
         rollback(*this, disposer);
      iterator b(src.begin()), e(src.end());
      for(; b != e; ++b){
         this->push_back(*cloner(*b));
      }
      rollback.release();
   }

   //! <b>Requires</b>: value must be an lvalue and p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts the value before the position pointed by p.
   //!
   //! <b>Returns</b>: An iterator to the inserted element.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant time. No copy constructors are called.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   iterator insert(const_iterator p, reference value) BOOST_NOEXCEPT
   {
      node_ptr to_insert = this->priv_value_traits().to_node_ptr(value);
      BOOST_INTRUSIVE_SAFE_HOOK_DEFAULT_ASSERT(!safemode_or_autounlink || node_algorithms::inited(to_insert));
      node_algorithms::link_before(p.pointed_node(), to_insert);
      this->priv_size_traits().increment();
      return iterator(to_insert, this->priv_value_traits_ptr());
   }

   //! <b>Requires</b>: Dereferencing iterator must yield
   //!   an lvalue of type value_type and p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts the range pointed by b and e before the position p.
   //!   No copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements inserted.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   template<class Iterator>
   void insert(const_iterator p, Iterator b, Iterator e) BOOST_NOEXCEPT
   {
      for (; b != e; ++b)
         this->insert(p, *b);
   }

   //! <b>Requires</b>: Dereferencing iterator must yield
   //!   an lvalue of type value_type.
   //!
   //! <b>Effects</b>: Clears the list and inserts the range pointed by b and e.
   //!   No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements inserted plus
   //!   linear to the elements contained in the list if it's a safe-mode
   //!   or auto-unlink value.
   //!   Linear to the number of elements inserted in the list otherwise.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!   to the erased elements.
   template<class Iterator>
   void assign(Iterator b, Iterator e) BOOST_NOEXCEPT
   {
      this->clear();
      this->insert(this->cend(), b, e);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Requires</b>: Dereferencing iterator must yield
   //!   an lvalue of type value_type.
   //!
   //! <b>Effects</b>: Clears the list and inserts the range pointed by b and e.
   //!   No destructors or copy constructors are called.
   //!   Disposer::operator()(pointer) is called for the removed elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements inserted plus
   //!   linear to the elements contained in the list.
   //!
   //! <b>Note</b>: Invalidates the iterators (but not the references)
   //!   to the erased elements.
   template<class Iterator, class Disposer>
   void dispose_and_assign(Disposer disposer, Iterator b, Iterator e) BOOST_NOEXCEPT
   {
      this->clear_and_dispose(disposer);
      this->insert(this->cend(), b, e);
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Transfers all the elements of list x to this list, before the
   //!   the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of
   //!    this list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, list_impl& x) BOOST_NOEXCEPT
   {
      if(!x.empty()){
         node_algorithms::transfer
            (p.pointed_node(), x.begin().pointed_node(), x.end().pointed_node());
         size_traits &thist = this->priv_size_traits();
         size_traits &xt = x.priv_size_traits();
         thist.increase(xt.get_size());
         xt.set_size(size_type(0));
      }
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!   new_ele must point to an element contained in list x.
   //!
   //! <b>Effects</b>: Transfers the value pointed by new_ele, from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!   If p == new_ele or p == ++new_ele, this function is a null operation.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, list_impl&x, const_iterator new_ele) BOOST_NOEXCEPT
   {
      node_algorithms::transfer(p.pointed_node(), new_ele.pointed_node());
      x.priv_size_traits().decrement();
      this->priv_size_traits().increment();
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!   f and e must point to elements contained in list x.
   //!
   //! <b>Effects</b>: Transfers the range pointed by f and e from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements transferred
   //!   if constant-time size option is enabled. Constant-time otherwise.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, list_impl&x, const_iterator f, const_iterator e) BOOST_NOEXCEPT
   {
      BOOST_IF_CONSTEXPR(constant_time_size)
         this->splice(p, x, f, e, node_algorithms::distance(f.pointed_node(), e.pointed_node()));
      else
         this->splice(p, x, f, e, 1);//intrusive::iterator_distance is a dummy value
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!   f and e must point to elements contained in list x.
   //!   n == distance(f, e)
   //!
   //! <b>Effects</b>: Transfers the range pointed by f and e from list x to this list,
   //!   before the element pointed by p. No destructors or copy constructors are called.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Iterators of values obtained from list x now point to elements of this
   //!   list. Iterators of this list and all the references are not invalidated.
   void splice(const_iterator p, list_impl&x, const_iterator f, const_iterator e, size_type n) BOOST_NOEXCEPT
   {
      if(n){
         BOOST_IF_CONSTEXPR(constant_time_size){
            BOOST_INTRUSIVE_INVARIANT_ASSERT(n == node_algorithms::distance(f.pointed_node(), e.pointed_node()));
            node_algorithms::transfer(p.pointed_node(), f.pointed_node(), e.pointed_node());
            size_traits &thist = this->priv_size_traits();
            size_traits &xt = x.priv_size_traits();
            thist.increase(n);
            xt.decrease(n);
         }
         else{
            node_algorithms::transfer(p.pointed_node(), f.pointed_node(), e.pointed_node());
         }
      }
   }

   //! <b>Effects</b>: This function sorts the list *this according to operator <.
   //!   The sort is stable, that is, the relative order of equivalent elements is preserved.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or operator < throws. Basic guarantee.
   //!
   //! <b>Notes</b>: Iterators and references are not invalidated.
   //!
   //! <b>Complexity</b>: The number of comparisons is approximately N log N, where N
   //!   is the list's size.
   void sort()
   {  this->sort(value_less<value_type>());  }

   //! <b>Requires</b>: p must be a comparison function that induces a strict weak ordering
   //!
   //! <b>Effects</b>: This function sorts the list *this according to p. The sort is
   //!   stable, that is, the relative order of equivalent elements is preserved.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or the predicate throws. Basic guarantee.
   //!
   //! <b>Notes</b>: This won't throw if list_base_hook<> or
   //!   list_member_hook are used.
   //!   Iterators and references are not invalidated.
   //!
   //! <b>Complexity</b>: The number of comparisons is approximately N log N, where N
   //!   is the list's size.
   template<class Predicate>
   void sort(Predicate p)
   {
      if(node_traits::get_next(this->get_root_node())
         != node_traits::get_previous(this->get_root_node())){
         list_impl carry(this->priv_value_traits());
         detail::array_initializer<list_impl, 64> counter(this->priv_value_traits());
         int fill = 0;
         while(!this->empty()){
            carry.splice(carry.cbegin(), *this, this->cbegin());
            int i = 0;
            while(i < fill && !counter[i].empty()) {
               counter[i].merge(carry, p);
               carry.swap(counter[i++]);
            }
            carry.swap(counter[i]);
            if(i == fill)
               ++fill;
         }
         for (int i = 1; i < fill; ++i)
            counter[i].merge(counter[i-1], p);
         this->swap(counter[fill-1]);
      }
   }

   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this according to operator <. The merge is stable;
   //!   that is, if an element from *this is equivalent to one from x, then the element
   //!   from *this will precede the one from x.
   //!
   //! <b>Throws</b>: If operator < throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated
   void merge(list_impl& x)
   { this->merge(x, value_less<value_type>()); }

   //! <b>Requires</b>: p must be a comparison function that induces a strict weak
   //!   ordering and both *this and x must be sorted according to that ordering
   //!   The lists x and *this must be distinct.
   //!
   //! <b>Effects</b>: This function removes all of x's elements and inserts them
   //!   in order into *this. The merge is stable; that is, if an element from *this is
   //!   equivalent to one from x, then the element from *this will precede the one from x.
   //!
   //! <b>Throws</b>: If the predicate throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated.
   template<class Predicate>
   void merge(list_impl& x, Predicate p)
   {
      const_iterator e(this->cend()), ex(x.cend());
      const_iterator b(this->cbegin());
      while(!x.empty()){
         const_iterator ix(x.cbegin());
         while (b != e && !p(*ix, *b)){
            ++b;
         }
         if(b == e){
            //Now transfer the rest to the end of the container
            this->splice(e, x);
            break;
         }
         else{
            size_type n(0);
            do{
               ++ix; ++n;
            } while(ix != ex && p(*ix, *b));
            this->splice(b, x, x.begin(), ix, n);
         }
      }
   }

   //! <b>Effects</b>: Reverses the order of elements in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: This function is linear time.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated
   void reverse() BOOST_NOEXCEPT
   {  node_algorithms::reverse(this->get_root_node());   }

   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!   No destructors are called.
   //!
   //! <b>Throws</b>: If operator == throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   void remove(const_reference value) BOOST_NOEXCEPT
   {  this->remove_if(detail::equal_to_value<const_reference>(value));  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //!
   //! <b>Throws</b>: If operator == throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Disposer>
   void remove_and_dispose(const_reference value, Disposer disposer) BOOST_NOEXCEPT
   {  this->remove_and_dispose_if(detail::equal_to_value<const_reference>(value), disposer);  }

   //! <b>Effects</b>: Removes all the elements for which a specified
   //!   predicate is satisfied. No destructors are called.
   //!
   //! <b>Throws</b>: If pred throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time. It performs exactly size() calls to the predicate.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Pred>
   void remove_if(Pred pred)
   {
      const node_ptr root_node = this->get_root_node();
      typename node_algorithms::stable_partition_info info;
      node_algorithms::stable_partition
         (node_traits::get_next(root_node), root_node, detail::key_nodeptr_comp<Pred, value_traits>(pred, &this->priv_value_traits()), info);
      //Invariants preserved by stable_partition so erase can be safely called
      //The first element might have changed so calculate it again
      this->erase( const_iterator(node_traits::get_next(root_node), this->priv_value_traits_ptr())
                 , const_iterator(info.beg_2st_partition, this->priv_value_traits_ptr())
                 , info.num_1st_partition);
   }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes all the elements for which a specified
   //!   predicate is satisfied.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //!
   //! <b>Throws</b>: If pred throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Pred, class Disposer>
   void remove_and_dispose_if(Pred pred, Disposer disposer)
   {
      const node_ptr root_node = this->get_root_node();
      typename node_algorithms::stable_partition_info info;
      node_algorithms::stable_partition
         (node_traits::get_next(root_node), root_node, detail::key_nodeptr_comp<Pred, value_traits>(pred, &this->priv_value_traits()), info);
      //Invariants preserved by stable_partition so erase can be safely called
      //The first element might have changed so calculate it again
      this->erase_and_dispose( const_iterator(node_traits::get_next(root_node), this->priv_value_traits_ptr())
                             , const_iterator(info.beg_2st_partition, this->priv_value_traits_ptr())
                             , disposer);
   }

   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent
   //!   elements that are equal from the list. No destructors are called.
   //!
   //! <b>Throws</b>: If std::equal_to<value_type throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time (size()-1 comparisons calls to pred()).
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   void unique()
   {  this->unique_and_dispose(std::equal_to<value_type>(), detail::null_disposer());  }

   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent
   //!   elements that satisfy some binary predicate from the list.
   //!   No destructors are called.
   //!
   //! <b>Throws</b>: If pred throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time (size()-1 comparisons equality comparisons).
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class BinaryPredicate>
   void unique(BinaryPredicate pred)
   {  this->unique_and_dispose(pred, detail::null_disposer());  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent
   //!   elements that are equal from the list.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //!
   //! <b>Throws</b>: If std::equal_to<value_type throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time (size()-1) comparisons equality comparisons.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Disposer>
   void unique_and_dispose(Disposer disposer)
   {  this->unique_and_dispose(std::equal_to<value_type>(), disposer);  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes adjacent duplicate elements or adjacent
   //!   elements that satisfy some binary predicate from the list.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //!
   //! <b>Throws</b>: If pred throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time (size()-1) comparisons equality comparisons.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class BinaryPredicate, class Disposer>
   void unique_and_dispose(BinaryPredicate pred, Disposer disposer)
   {
      const_iterator itend(this->cend());
      const_iterator cur(this->cbegin());

      if(cur != itend){
         const_iterator after(cur);
         ++after;
         while(after != itend){
            if(pred(*cur, *after)){
               after = this->erase_and_dispose(after, disposer);
            }
            else{
               cur = after;
               ++after;
            }
         }
      }
   }

   //! <b>Requires</b>: value must be a reference to a value inserted in a list.
   //!
   //! <b>Effects</b>: This function returns a const_iterator pointing to the element
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated.
   //!   This static function is available only if the <i>value traits</i>
   //!   is stateless.
   static iterator s_iterator_to(reference value) BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!stateful_value_traits));
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_algorithms::inited(value_traits::to_node_ptr(value)));
      return iterator(value_traits::to_node_ptr(value), const_value_traits_ptr());
   }

   //! <b>Requires</b>: value must be a const reference to a value inserted in a list.
   //!
   //! <b>Effects</b>: This function returns an iterator pointing to the element.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated.
   //!   This static function is available only if the <i>value traits</i>
   //!   is stateless.
   static const_iterator s_iterator_to(const_reference value) BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!stateful_value_traits));
      reference r =*detail::uncast(pointer_traits<const_pointer>::pointer_to(value));
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_algorithms::inited(value_traits::to_node_ptr(r)));
      return const_iterator(value_traits::to_node_ptr(r), const_value_traits_ptr());
   }

   //! <b>Requires</b>: value must be a reference to a value inserted in a list.
   //!
   //! <b>Effects</b>: This function returns a const_iterator pointing to the element
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated.
   iterator iterator_to(reference value) BOOST_NOEXCEPT
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_algorithms::inited(this->priv_value_traits().to_node_ptr(value)));
      return iterator(this->priv_value_traits().to_node_ptr(value), this->priv_value_traits_ptr());
   }

   //! <b>Requires</b>: value must be a const reference to a value inserted in a list.
   //!
   //! <b>Effects</b>: This function returns an iterator pointing to the element.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant time.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated.
   const_iterator iterator_to(const_reference value) const BOOST_NOEXCEPT
   {
      reference r = *detail::uncast(pointer_traits<const_pointer>::pointer_to(value));
      BOOST_INTRUSIVE_INVARIANT_ASSERT(!node_algorithms::inited(this->priv_value_traits().to_node_ptr(r)));
      return const_iterator(this->priv_value_traits().to_node_ptr(r), this->priv_value_traits_ptr());
   }

   //! <b>Effects</b>: Asserts the integrity of the container.
   //!
   //! <b>Complexity</b>: Linear time.
   //!
   //! <b>Note</b>: The method has no effect when asserts are turned off (e.g., with NDEBUG).
   //!   Experimental function, interface might change in future versions.
   void check() const
   {
      const_node_ptr header_ptr = get_root_node();
      // header's next and prev are never null
      BOOST_INTRUSIVE_INVARIANT_ASSERT(node_traits::get_next(header_ptr));
      BOOST_INTRUSIVE_INVARIANT_ASSERT(node_traits::get_previous(header_ptr));
      // header's next and prev either both point to header (empty list) or neither does
      BOOST_INTRUSIVE_INVARIANT_ASSERT((node_traits::get_next(header_ptr) == header_ptr)
         == (node_traits::get_previous(header_ptr) == header_ptr));
      if (node_traits::get_next(header_ptr) == header_ptr)
      {
         BOOST_IF_CONSTEXPR(constant_time_size)
            BOOST_INTRUSIVE_INVARIANT_ASSERT(this->priv_size_traits().get_size() == 0);
         return;
      }
      size_t node_count = 0;
      const_node_ptr p = header_ptr;
      while (true)
      {
         const_node_ptr next_p = node_traits::get_next(p);
         BOOST_INTRUSIVE_INVARIANT_ASSERT(next_p);
         BOOST_INTRUSIVE_INVARIANT_ASSERT(node_traits::get_previous(next_p) == p);
         p = next_p;
         if (p == header_ptr) break;
         ++node_count;
      }
      BOOST_IF_CONSTEXPR(constant_time_size)
         BOOST_INTRUSIVE_INVARIANT_ASSERT(this->priv_size_traits().get_size() == node_count);
   }

   friend bool operator==(const list_impl &x, const list_impl &y)
   {
      if(constant_time_size && x.size() != y.size()){
         return false;
      }
      return ::boost::intrusive::algo_equal(x.cbegin(), x.cend(), y.cbegin(), y.cend());
   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator!=(const list_impl &x, const list_impl &y)
   {  return !(x == y); }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator<(const list_impl &x, const list_impl &y)
   {  return ::boost::intrusive::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator>(const list_impl &x, const list_impl &y)
   {  return y < x;  }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator<=(const list_impl &x, const list_impl &y)
   {  return !(y < x);  }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator>=(const list_impl &x, const list_impl &y)
   {  return !(x < y);  }

   BOOST_INTRUSIVE_FORCEINLINE friend void swap(list_impl &x, list_impl &y) BOOST_NOEXCEPT
   {  x.swap(y);  }

   /// @cond

   private:
   static list_impl &priv_container_from_end_iterator(const const_iterator &end_iterator) BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((has_container_from_iterator));
      node_ptr p = end_iterator.pointed_node();
      header_holder_type* h = header_holder_type::get_holder(p);
      root_plus_size* r = detail::parent_from_member
         < root_plus_size, header_holder_type>(h, &root_plus_size::m_header);
      data_t *d = detail::parent_from_member<data_t, root_plus_size>
         ( r, &data_t::root_plus_size_);
      list_impl *s  = detail::parent_from_member<list_impl, data_t>(d, &list_impl::data_);
      return *s;
   }
   /// @endcond
};


//! Helper metafunction to define a \c list that yields to the same type when the
//! same options (either explicitly or implicitly) are used.
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_list
{
   /// @cond
   typedef typename pack_options
      < list_defaults,
         #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4
         #else
         Options...
         #endif
      >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;
   typedef list_impl
      <
         value_traits,
         typename packed_options::size_type,
         packed_options::constant_time_size,
         typename packed_options::header_holder_type
      > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};


#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4>
#else
template<class T, class ...Options>
#endif
class list
   :  public make_list<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
   >::type
{
   typedef typename make_list
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type      Base;
   //Assert if passed value traits are compatible with the type
   BOOST_STATIC_ASSERT((detail::is_same<typename Base::value_traits::value_type, T>::value));
   BOOST_MOVABLE_BUT_NOT_COPYABLE(list)

   public:
   typedef typename Base::value_traits          value_traits;
   typedef typename Base::iterator              iterator;
   typedef typename Base::const_iterator        const_iterator;

   BOOST_INTRUSIVE_FORCEINLINE list()
      :  Base()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit list(const value_traits &v_traits)
      :  Base(v_traits)
   {}

   template<class Iterator>
   BOOST_INTRUSIVE_FORCEINLINE list(Iterator b, Iterator e, const value_traits &v_traits = value_traits())
      :  Base(b, e, v_traits)
   {}

   BOOST_INTRUSIVE_FORCEINLINE list(BOOST_RV_REF(list) x)
      :  Base(BOOST_MOVE_BASE(Base, x))
   {}

   BOOST_INTRUSIVE_FORCEINLINE list& operator=(BOOST_RV_REF(list) x)
   {  return static_cast<list &>(this->Base::operator=(BOOST_MOVE_BASE(Base, x)));  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(const list &src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(src, cloner, disposer);  }

   template <class Cloner, class Disposer>
   BOOST_INTRUSIVE_FORCEINLINE void clone_from(BOOST_RV_REF(list) src, Cloner cloner, Disposer disposer)
   {  Base::clone_from(BOOST_MOVE_BASE(Base, src), cloner, disposer);  }

   BOOST_INTRUSIVE_FORCEINLINE static list &container_from_end_iterator(iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<list &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const list &container_from_end_iterator(const_iterator end_iterator) BOOST_NOEXCEPT
   {  return static_cast<const list &>(Base::container_from_end_iterator(end_iterator));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_LIST_HPP

/* list.hpp
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
*/