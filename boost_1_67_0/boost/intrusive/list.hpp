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

#include <boost/intrusive/detail/minimal_less_equal_header.hpp>//std::less
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

   size_traits &priv_size_traits()
   {  return data_.root_plus_size_;  }

   const size_traits &priv_size_traits() const
   {  return data_.root_plus_size_;  }

   const value_traits &priv_value_traits() const
   {  return data_;  }

   value_traits &priv_value_traits()
   {  return data_;  }

   typedef typename boost::intrusive::value_traits_pointers
      <ValueTraits>::const_value_traits_ptr const_value_traits_ptr;

   const_value_traits_ptr priv_value_traits_ptr() const
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
   //! <b>Complexity</b>: Linear to the number of elements in the list, if
   //!   it's a safe-mode or auto-unlink value . Otherwise constant.
   ~list_impl()
   {
      if(is_safe_autounlink<ValueTraits::link_mode>::value){
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
   void push_back(reference value)
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
   void push_front(reference value)
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
   void pop_back()
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
   void pop_back_and_dispose(Disposer disposer)
   {
      node_ptr to_erase = node_traits::get_previous(this->get_root_node());
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      if(safemode_or_autounlink)
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
   void pop_front()
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
   void pop_front_and_dispose(Disposer disposer)
   {
      node_ptr to_erase = node_traits::get_next(this->get_root_node());
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(priv_value_traits().to_value_ptr(to_erase));
   }

   //! <b>Effects</b>: Returns a reference to the first element of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reference front()
   { return *priv_value_traits().to_value_ptr(node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_reference to the first element of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reference front() const
   { return *priv_value_traits().to_value_ptr(node_traits::get_next(this->get_root_node())); }

   //! <b>Effects</b>: Returns a reference to the last element of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reference back()
   { return *priv_value_traits().to_value_ptr(node_traits::get_previous(this->get_root_node())); }

   //! <b>Effects</b>: Returns a const_reference to the last element of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reference back() const
   { return *priv_value_traits().to_value_ptr(detail::uncast(node_traits::get_previous(this->get_root_node()))); }

   //! <b>Effects</b>: Returns an iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator begin()
   { return iterator(node_traits::get_next(this->get_root_node()), this->priv_value_traits_ptr()); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator begin() const
   { return this->cbegin(); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cbegin() const
   { return const_iterator(node_traits::get_next(this->get_root_node()), this->priv_value_traits_ptr()); }

   //! <b>Effects</b>: Returns an iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   iterator end()
   { return iterator(this->get_root_node(), this->priv_value_traits_ptr()); }

   //! <b>Effects</b>: Returns a const_iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator end() const
   { return this->cend(); }

   //! <b>Effects</b>: Returns a constant iterator to the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_iterator cend() const
   { return const_iterator(detail::uncast(this->get_root_node()), this->priv_value_traits_ptr()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rbegin()
   { return reverse_iterator(this->end()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rbegin() const
   { return this->crbegin(); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crbegin() const
   { return const_reverse_iterator(end()); }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   reverse_iterator rend()
   { return reverse_iterator(begin()); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator rend() const
   { return this->crend(); }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reverse_iterator crend() const
   { return const_reverse_iterator(this->begin()); }

   //! <b>Precondition</b>: end_iterator must be a valid end iterator
   //!   of list.
   //!
   //! <b>Effects</b>: Returns a const reference to the list associated to the end iterator
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   static list_impl &container_from_end_iterator(iterator end_iterator)
   {  return list_impl::priv_container_from_end_iterator(end_iterator);   }

   //! <b>Precondition</b>: end_iterator must be a valid end const_iterator
   //!   of list.
   //!
   //! <b>Effects</b>: Returns a const reference to the list associated to the end iterator
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   static const list_impl &container_from_end_iterator(const_iterator end_iterator)
   {  return list_impl::priv_container_from_end_iterator(end_iterator);   }

   //! <b>Effects</b>: Returns the number of the elements contained in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements contained in the list.
   //!   if constant-time size option is disabled. Constant time otherwise.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   size_type size() const
   {
      if(constant_time_size)
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
   bool empty() const
   {  return node_algorithms::unique(this->get_root_node());   }

   //! <b>Effects</b>: Swaps the elements of x and *this.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Does not affect the validity of iterators and references.
   void swap(list_impl& other)
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
   void shift_backwards(size_type n = 1)
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
   void shift_forward(size_type n = 1)
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
   iterator erase(const_iterator i)
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
   iterator erase(const_iterator b, const_iterator e)
   {
      if(safemode_or_autounlink || constant_time_size){
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
   iterator erase(const_iterator b, const_iterator e, size_type n)
   {
      BOOST_INTRUSIVE_INVARIANT_ASSERT(node_algorithms::distance(b.pointed_node(), e.pointed_node()) == n);
      if(safemode_or_autounlink || constant_time_size){
         return this->erase_and_dispose(b, e, detail::null_disposer());
      }
      else{
         if(constant_time_size){
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
   iterator erase_and_dispose(const_iterator i, Disposer disposer)
   {
      node_ptr to_erase(i.pointed_node());
      ++i;
      node_algorithms::unlink(to_erase);
      this->priv_size_traits().decrement();
      if(safemode_or_autounlink)
         node_algorithms::init(to_erase);
      disposer(this->priv_value_traits().to_value_ptr(to_erase));
      return i.unconst();
   }

   #if !defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)
   template<class Disposer>
   iterator erase_and_dispose(iterator i, Disposer disposer)
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
   iterator erase_and_dispose(const_iterator b, const_iterator e, Disposer disposer)
   {
      node_ptr bp(b.pointed_node()), ep(e.pointed_node());
      node_algorithms::unlink(bp, ep);
      while(bp != ep){
         node_ptr to_erase(bp);
         bp = node_traits::get_next(bp);
         if(safemode_or_autounlink)
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
   void clear()
   {
      if(safemode_or_autounlink){
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
   void clear_and_dispose(Disposer disposer)
   {
      const_iterator it(this->begin()), itend(this->end());
      while(it != itend){
         node_ptr to_erase(it.pointed_node());
         ++it;
         if(safemode_or_autounlink)
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
   iterator insert(const_iterator p, reference value)
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
   void insert(const_iterator p, Iterator b, Iterator e)
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
   void assign(Iterator b, Iterator e)
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
   void dispose_and_assign(Disposer disposer, Iterator b, Iterator e)
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
   void splice(const_iterator p, list_impl& x)
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
   void splice(const_iterator p, list_impl&x, const_iterator new_ele)
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
   void splice(const_iterator p, list_impl&x, const_iterator f, const_iterator e)
   {
      if(constant_time_size)
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
   void splice(const_iterator p, list_impl&x, const_iterator f, const_iterator e, size_type n)
   {
      if(n){
         if(constant_time_size){
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

   //! <b>Effects</b>: This function sorts the list *this according to std::less<value_type>.
   //!   The sort is stable, that is, the relative order of equivalent elements is preserved.
   //!
   //! <b>Throws</b>: If value_traits::node_traits::node
   //!   constructor throws (this does not happen with predefined Boost.Intrusive hooks)
   //!   or std::less<value_type> throws. Basic guarantee.
   //!
   //! <b>Notes</b>: Iterators and references are not invalidated.
   //!
   //! <b>Complexity</b>: The number of comparisons is approximately N log N, where N
   //!   is the list's size.
   void sort()
   {  this->sort(std::less<value_type>());  }

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
   //!   in order into *this according to std::less<value_type>. The merge is stable;
   //!   that is, if an element from *this is equivalent to one from x, then the element
   //!   from *this will precede the one from x.
   //!
   //! <b>Throws</b>: If std::less<value_type> throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: This function is linear time: it performs at most
   //!   size() + x.size() - 1 comparisons.
   //!
   //! <b>Note</b>: Iterators and references are not invalidated
   void merge(list_impl& x)
   { this->merge(x, std::less<value_type>()); }

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
   void reverse()
   {  node_algorithms::reverse(this->get_root_node());   }

   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!   No destructors are called.
   //!
   //! <b>Throws</b>: If std::equal_to<value_type> throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   void remove(const_reference value)
   {  this->remove_if(detail::equal_to_value<const_reference>(value));  }

   //! <b>Requires</b>: Disposer::operator()(pointer) shouldn't throw.
   //!
   //! <b>Effects</b>: Removes all the elements that compare equal to value.
   //!   Disposer::operator()(pointer) is called for every removed element.
   //!
   //! <b>Throws</b>: If std::equal_to<value_type> throws. Basic guarantee.
   //!
   //! <b>Complexity</b>: Linear time. It performs exactly size() comparisons for equality.
   //!
   //! <b>Note</b>: The relative order of elements that are not removed is unchanged,
   //!   and iterators to elements that are not removed remain valid.
   template<class Disposer>
   void remove_and_dispose(const_reference value, Disposer disposer)
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
   static iterator s_iterator_to(reference value)
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
   static const_iterator s_iterator_to(const_reference value)
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
   iterator iterator_to(reference value)
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
   const_iterator iterator_to(const_reference value) const
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
         if (constant_time_size)
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
      if (constant_time_size)
         BOOST_INTRUSIVE_INVARIANT_ASSERT(this->priv_size_traits().get_size() == node_count);
   }

   friend bool operator==(const list_impl &x, const list_impl &y)
   {
      if(constant_time_size && x.size() != y.size()){
         return false;
      }
      return ::boost::intrusive::algo_equal(x.cbegin(), x.cend(), y.cbegin(), y.cend());
   }

   friend bool operator!=(const list_impl &x, const list_impl &y)
   {  return !(x == y); }

   friend bool operator<(const list_impl &x, const list_impl &y)
   {  return ::boost::intrusive::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   friend bool operator>(const list_impl &x, const list_impl &y)
   {  return y < x;  }

   friend bool operator<=(const list_impl &x, const list_impl &y)
   {  return !(y < x);  }

   friend bool operator>=(const list_impl &x, const list_impl &y)
   {  return !(x < y);  }

   friend void swap(list_impl &x, list_impl &y)
   {  x.swap(y);  }

   /// @cond

   private:
   static list_impl &priv_container_from_end_iterator(const const_iterator &end_iterator)
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

   BOOST_INTRUSIVE_FORCEINLINE static list &container_from_end_iterator(iterator end_iterator)
   {  return static_cast<list &>(Base::container_from_end_iterator(end_iterator));   }

   BOOST_INTRUSIVE_FORCEINLINE static const list &container_from_end_iterator(const_iterator end_iterator)
   {  return static_cast<const list &>(Base::container_from_end_iterator(end_iterator));   }
};

#endif

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_LIST_HPP

/* list.hpp
75eY7vvRNanveB7RDjGlLBnEr/riIdHaAu7dtGnar7/84jHWKh/EF3j9pGDr8OIp0ap8GoYv0otwvdGodflMU6LT/qlNY9YPK55gj6NZac8CGhOEQTP1gAF7ighfUho3BCzIvDhmFKCniXk0T2DrG3QJq3mmnAW2epOtzP46xUFnT7HVTv6dmoH7xFff1wgH9p88x0v93FbHu8KWpr8ykrsYR+wMBJ2fB6e9UKYk4wCnvffnun0vouMeLB7oVr3pl/oMRHRWI84sOkithd/rzKNMRsuAqAr7zOv8onTg6j73un0ka15beP0t9Av3+piURCoYeHar/Rw+FjhSE+yvo6LbpP5LuN+bpyWpmVOWXpYe7g+Aj4ZuZYBHyE6y/6P7UwRvjmiOHe5EyuJCdslvWtKhmgtiLN4VmI/K5iXBrg6cJ2TrurQcnhSgXvHTJYAr8mez/1az/1XeqwNh57/vbaEex+vfs5ZdoR6gq/dExHfFj+F4iL1aW5OKWIV3pVbYnjVZHmi8HVr5XPz6vnTTMJdpuikYh+sryBjjGrezMeCdHx/TL+zNw63ZGPvzHGCeT3o4jJrtqbppGPq9sCvKH0/XjHbDWRJ2I/LRoKtk+wjw9LVTBmBhVlz+ttMJp9lz6PyWQ14SoAmbkuKaFZMYebjwAXenG4NEWoPm5zfCPbVq1VPXBtX2zIj7gK6NjdUo31r+xSlRp0j65tM18/4TVSV+eH96wD5h9n+6xp27l/jkfuNlbgx3+s3SBPImt6CxU5md8ry3W5cQPxt124azLqwwbBjaRU3KHehfRZuvRP8OMqWBxqbHZ5QkcqDx/EHLv/Uzn+g1JS90c7r6nUQgtneELQpFiw2YQwg0CxpKpLdkEWutLjNsxfiuJq3uOoDc9OeOJ6Ky7WucP2cZy4LWqOXlhGBsfGKP2I+jPH6AGch8CvBVV5IfAu1yjviY89hx9/5r/cVOOAp1Sx1NnKHty/r2FWSc/C/nAfkB86IzawLXF/0FfzZkg7PGSHBTXHDnJb5jUnlVhji1VLd269ooqa68IqNQyq8Grz23EcrRB6s1StzvtgEQ5Y5aay04q74NwRhVmEm4CMEYfrS+Y1J75qEpM+7C77UYfY9dEIAvvBsAgUOiG2+ufnBnZjBxNT86Ukk5+1vmllVA17gfUSBb2bewhvZcz2Fmq/A0A2IoZK11+XW0E20FXkPeuzDy+L5hKuEzpNFJLjucWTAZ3e2uIcTRNTOjd2VKxW3UdgQd+N/z1bEEA4WFp0PmVx6oN9Ji57InyDL0zfNlVnh87haV0JkypiYCOOAvUH4OHQTrEaXNNttJsLgq2OWVBW4+AoU8YfxNv1mdqi/6hQmOXjp9Dh2/zDM6urDLjSykICMrdzRezwqcG/5tJLEZ46TjThz4qQ+A495BJNCrj9M8cPEcvgeiqyQeyDy6cyRYqDyW/e50hLvzzGzkIWsE2Gpo5IW/Q2LIKvpiJpoSuE7Ctin8TdkSv4glMIrsWI4D2WTHuR0DgHbd6RlPbTm47ZZNTK8uqHgJZ4wjj4fbAHKzHiwIwGExC7cxAqjVwrgbgyCAIovV2mStHK1B6/LTAu1Dnm9hd11Cl0Kd4SmAL+CrmJDGR3EzekKKlginVKdZ6qHECSfBiGLBh2DSPl6N3nNQYY5aUyJ89ngo/iQ1brp87mNn52AyQgkPTwEO4TUkYg3sNsgQxhZBD9lxPntmGLeXmf6bEX5dRIp7049rXxCJiKnaUbUwKg5WoVeiN2zMg7rsomhoIsOkddhbu1S1k0W/sf3uYMMKDR4RZddC1BTushDZ+oPzv+L6n0XBk+mPNdCgcHVDgqHyKosiWnrp6ByPkkkRGZ93ehSnk67qgR31TjC8hefRYG9tN9JST6fOQbTZ+22UrmfeLkQv2FVbMY0PfoiWH3914STlWuzUyOGPlhxzpJ5ajLTwDjxHSQx6q+MZQydPxbFL9siPrp+RhhIhInnvKrvGj+GCBH7xJoxyflYWHUxe7Dx+YyxZjJhJas56Ht2yFk5FDQcKszduLUHTlbaQujLlQmzSzAeh/KDFV3BbgmYVEUitOLZZ7tuHaQxQzB0s6XmhSZiiLvconIS5N2dUaNVB8fJSPbOoguLTJWAs+QzUN7tjv1kcdFdTaHFSPxGsi273STAvpKYg3k1AY7NoEGxhiwyGdiSx/Tk+1KKRWZIDMr2JpJVaooJ2c0+lUiAF85zd6H1mzppVv5OhwB8yHAfe7autB9ELcaUbU+ouVGniDWL9lS/LL8Xu8QJ5068XdXh+72maQbWqiN7yHRkHXaWvqi52v8pn/gQQH/8fn4hCLyVFJ2W8WzUsvT5qjkvFfNByZfoS8miA2rzFLUNkr9+COW62xSTqxXFfB6mzRQFKzUquT/ba4BAd6fE3tWnWkm2k7ftXMtg3444PEpQuWGL0sBdDzi/zx1M8FGRWNQVYcZZharx0nsdsrIrMbLPrVDCeC+QTvTus8gtUBG2j9pxml/804cHFH5yMrawHmdjRNGUxasRORR6+92Ja8rfcw26aNOAXfmW3mqzCyC0jQrkSPCvQ28+Nv6xYH0q6dAV0sGIyncKJ38BzX6np3Uz7tF9iMdxwte0oYPEecInwGKYxjNeFHoVungPm3qDNiJHJgLND52cS0KTNzd7ESYA8dxPPEbOuzadQqfCTaV05joNMQ2b9WCeyZ14sli4v5sTd10M9ToIM82jtTEeovrsmfF2BPVm289xX9jZP8HMzHi0Vv7a2pbpUTQrwEvLJwmizFgtMzm1Q+YAXekD5ud7G+39QMyct7vU0zTWzUO9rbRh9r8YuFzsFSGCDlHLHJu8U2XF2zcr89WuygwIGV8XZlRprKrSlBpwxQZcXB7u0odZ+OsioaSKO/V9Vg3N6UUWdDY286VOM9IN3kqZ656LtmrEHhLHhkm3Lca3fJ9dbaD+tMJKFH/C/u5haRhVl1XQyC03m7wHCoibLZim6z51wAphmW7w3h1DwnEokcc+PnT3UFbaK4YbzK7PqzQi2O8Fm6Reec5QqpfB5B9bVc63IGLtrDlqtHdjOazhpVRu9YLFcuDu961cPpJ3c1SewQrZNEp+fewRVpLzCaODDqg8pFknE2lTgPsE1H6HuHd5GX5HtUmf6gC0Y6l3uw5Gt6Q8GF/em07HeXbz4L0Lv4tYPeXpRYWdo8Ns6WO4vOcLruzGj/QThWupE5nJLM4/6XL/iPysQcjdeq/YI9HwNbOxMY/T8qGYsg0sbuBgV1MI2UjUocc3TlqS0XH0ZE7gME4AXZ5LPQUvi1saUk74Algf7ox23mIwEezspXl+vGwKzT1p8OijYyicw+MooHaTaF+cKb7MOOTb6jn2ziPtn32wjzeB25ozlWTTkcJXBk9hw3d3DDWZSDTQuKkiizJlKsdfYDwLVSOsBfpOrXhVEnYjydVXHlq86yJdorz+ZAqdg+1S0re4iAdegtrZJCOeKP13HmpZgg4ZUEEDfaZcHd+L2ow3XMSxD18exEMPvV9KXg6O/wXkkxa8iUotq+L6ev6yDnCeEva4yaiN7HK9gkExyUq2OsXP0Gr6wKHP0lXta5sSfYJo2Uf9ztdQVbuKpHO2VGTHBFauxkGtcfeOU27xZ6xHisW3G5MyyAnJZF7ZivmWdr8WVuzlqwwu7hEy/lZGxnyZvoK+j59cwoAH3r5MHRhhZLUecpw8oSjqrYdcENmilC5PRZUPermGAu0N5uWJq5DVeP3yd5WAG7DhowBD04rlE2H5jaO8YOgPvIXTog/IbRrfLE8D5Z3dRJQotiCtIveClub7HMIuTW75X447SJEjowLV4cw28yM+hknl1CzlJrOF0IbYrfwxn7EO/Emf1McDLz2uwVjDDAD2G6FiU2crWly2xa67OLo/PUK7WIzYiO7RoPuVQljvQI8gf9RPssWiU4zu61hejQuR3VOCFYb71i/ZSB3u2WlNJfOGiTfIFUCczMlbujrgugZ0h9jw5Ni1hrr8YE0JO0JIQitmDNLhrmV77tD2ksRJEazndLkX2JGr2o7oR4OUEIMNErLFHxxGeRXgGwf8fqq3om+O2PghFUwGq3VwoP7KjS3qZCOzcuk6aH4Jbsn8HD5bc85tXJJsXUZYjeC5zxNI+56bkoY8PoorX9Q04aH8d5sbn+r4D9lrsafQ0kAFm32CM4zNTEz3WMjyxDLc/TRYEczBPyGVDYFtbF6GIXwhiiZ0aqDYkedbAv5e9AT85DMCwiv5ZDNKQxf3/eCPsqiCYc67610CaF4FJZ+72RRf44CjHogxDlA7qVHsZRfYd5XIdzCZjxiNZA+GWIz+k6BPE6/rn/uvzQHLycNDoqUNREj+S4sdGqyF8creP8tTq7RT6il7TFodUQK5fSVryN5zkDYKIJzyW4BtEMX1nTg7Q5rucr8b+OmtEOavuHp0GuOwMlqwrxkhcV5YglwEHA2EpmPF7n6JHTLQeZznZOeS2FBUR3IHCUyIFaV+kz17Ns73EI6MSwO0laggbPTp8StkPZsOUDI4J33aUYFTHNkayixOwQMGKogdRy7cuFKkJwR1JYxPViN/OKH1kwpHeMpjy7zyLsGHu1/KYtwfn/EE+GkpXUr6JEaw/rB91Xwo+gBlDtJlKMIAei7c9SjGAnsc0Rq2KY1Qw84+ZGR1+YO0UxmwjbBRtlM8dkssx3nDLNZCwaFeTfUI0t27/m5ZJu1RLEdFDvXhvVzETjKLF9E22mj/VUTcIb5i+B211w48kbGLnMaiGwMeoqgJ44itzxQTLzOJEPazhn/vPUO10SN4n2mAsA2nupc5RbXTQ/Kq/Mng6QM0LAhgBAQL/BP0J/hPyJ/RP2J/wP//+RPyJ/BP1J/pPzJ/YP3F/4v8k/En8k/Qn+U/Kn9Q/aX/S/2T8yfyT9Sf7T86f3D95f/L/FPwp/FP0p/hPyZ/SP2V/yv9U/Kn8U/Wn+k/Nn9o/dX/q/zT8afzT9Kf5T8uf1j9tf9r/dPzp/NP1p/tPz5/eP31/+v8M/Bn8M/Rn+M/In9E/Y3/G/0z8mfwz9Wf6z8yf2T9zf+b/LPxZ/LP0Z/nPyp/VP2t/1v9s/Nn8s/Vn+8/On90/e3/2/xz8Ofxz9Of4z8mf0z9nf87/XPy5/HP15/rPzZ/bP3d/7v88/Hn88/Tn+c/Ln9c/b3/e/3z8+fzz9ef7z8+f3z+ATIAA6rF6go8qcoXquWjzKPfFFn6oPyE34fajJCYLrbc7IXbeYUdi3P2Og17m0nzaR8QPhsoraT3/+LyDGrpTeI6ScFTuE5d/0OBgXah91iA+wK7u5u0cFhh91O9xqgj554BcKk0GN7vMumvhjX5Q80nzde83FqFWe5iyjADxdpbxjYXaWcZUL8as7PxbQI55fMJGg0zdC9YRrZzhOMK26OGtJzcnbGZbd2dBXKF9NCyPB1CBW2/XAssleebXiG/x2gGVEw1lNnIXxtrT52Lm/WH04jwtNUnOsCJrciIn54I5KxrMZk/qggrBHelUOI6n5yvgNDbzUOc7Z7sByw1TYRezHGYUNFDiqfdlmvcIE0KLiK9gugRwe/7O3f7UCeJP43ruYRaV2qyyt/rQ3h4fkVy3LLphjlXkfTmUiuJ7kl11qIbSP/8KEBb/M9BYFG/xoLtJ/wbPtns+ZKzdiThLdLzR5gChqQcrAMABZ1rfFfeL/cALVptoYQhn2oQC/5nWME9emAEm/nWTFCgCy7eWGxherYpzLgD/xnZglb75166A2gOdZ6RiWiFBrsTOXZYt/RQGJ940NP51jLST4HGTPuss0xHgkGz5PUX/C6ObNkCZf7xkVXs0o4E2clr3HynApxQ54OdEuz++r6cQSpCKcAvlHkyDAkoM+c1UUxxhYMwWkqL0XLp9DJWR+IFktwFxoPzDv3p/PF9u5oMz6iEhvG0ZLNnL8KI0VHneocxaX/GXVTIiX6GyxLZQn9mL/Th+5AfXEE9ejTRiA/FbSPcY76/TljtR+0IsH4KYOOLHK53wmK3F4HyXXQPz7WOwe8XI+UBU4Sbquy45BwxVjBzy6IOmrp1olO6B88TPMqkPeKxbRgp0YsarqlND1fOFSpBDRlMHrOLUKg78k8A8BU4i9Zf0mji8c/L5LbcNRWvT86F/4B7XYAgRTNVn66UK8OfguvNwTSI9nMtZnoIPvYtN+dhi50U/AkGeBZptBUJP5kJGqjuhPQCUVw9dkDdf0Fyxu8Nk5usI+eRnV8WWSvNqrVN3Z7rKeLsVxu6dirJ+wdQ6/EOWvr3E5oT4uYsTvsJ7QW4pi5XvWk0m4/rTOk6h8pwIdFVDncX9nTYr7Y3eJbVOz56Kuvdpw2tqs+0TFr3FdFWh+iAKecE+nQBJBioCsQJCnoxZDEhpnZyestNYt9SBuWIZYqNh1AUksdcC4kOifbvy/Rt+WBknY8KsCZ9fXEZF8cG6SRmYirN9NycGLZ23R91PsqfVI1RoqIxIFBa2HKqBa8ieJxQ0wmOIbmK6aVC7IYbpvrrrYNYrnYg7qE7PLjAB7J1BL6aWAc6CfuQAtMFwtaSPIjp9MWuovik0VcJvkPzoNFfu8Xkx/sR3R5oKMRSwbqJnkPx+iBbCH4Z6a4jrxB9Hughz1Go0UYgB5K8iH/SyK3F/vS28KRvxi8CvjfBDJCsysssf1S9cR7QP8fcVCTaeRWSn6xEr/vckcOZ9cH7tn31xlgUancgCgnNRLi70dpybca7NA2aJho8M6AdNeZqGNjXV2Gkt0+X1C0juO5RHCbk8/EXpx9aJYtqjUV26mLung/lhTs/yduaVenyL0wn26arARkqdYLeWyXWnJ8ZrNbx65kKH6mU+Z2EJkVvAvrnzYBG4UyyrGfYBhEmia/jGb5/pqVa+bf9rQI0PuEGu5qed9AXw7E7RK4HFCCxwJ9o64ObmqzaweWi9wA7FSEiF6PU1nzSw2lvw1eOOLOC6dohS5X8yaa1wR/7t11lCDV0AvXE/V2O1xXpWN8ZqAbLnpj4yHga9E58EVqOtYUSrvbRm+hi7WLDarFejC99TEtWbL7KNPU/3+s4/8OS+1CIcfgD+wtLJX8BxFLJzdBCxNpst1cwt08wtf8H/18tUzuvP/ffriJj1kK2bM5+upqq8qZm6qpu4mLOTScXB+HvekrQsV1lLl65txg8eigR1T7yD6jneLHxQdsRrSoPg8pQvfB3sRPmHSjXnBSqa0bU9nblZGF4TrFT8wRvsQoqj3XtjP5nEJQLf3HSub3bl5pcZsu3cigtvGm3mjxUA7JLsQYsS4PJ+NokaAayaPG/nVl8FjF1HCw3gm+Xb7EI3fByEn21Ei1eghOlJ+otb4JjYtS8uCdzvcU9F/YuMgXGvVHA1doDRsiR0nHosjzt3ur881bvSAmugrw4GWp/6T6WtfS1JMrpv7eaQcyFoHQiIYG8PpwHSdwgzhNAcEGAvAVNjE2XaPR9xIosygSHWWNK+SfKH9DQfBRc6+X9WLs3XJxlyLdX7oTMQ0rjXMzmLNLM6JWdBmyu7u8p2vtpAi5mrVdObL4s4szq2nNBKVTgjT0tcxglROGIG7xL7mRTUy5Cq/4gSif3BJckRFQ08B62Lrt29cng0imzTwMaoS+05+KnzZGUry8JF9H5Qo/TCUh2eBzbGXXYRaeyyMfFpJslh54TsA0M1qZ51vRStK1x6f0kvr8RXVC4v4QsvKmEV4lsWF/e5vSbi3ZlZCSasG1BMB6vlOKGckFb94WO7RnrKHo1MsChqixaKvdWu3gJ7IU8GKzC+UcTzNRWikxZcoPoOjKME4ytG8/CmqieC7SoIHmC+pteMZZvF6mNLfx1jxVytizmDjl8uG2IzWQCoO86qq7ziLc5RjsQ79h0Tp6Atqnbwa8jRgV3MOIUvn49JsnnVbbwQfyoRieewErIA3vc6SOpY0kmy087HrasTiYYnHkaWM8cIrSPk2E5uE5mBcqMmytgWghgC2RhBfxRo29oHEPNEwNbHwulCpMUXAC0UyidQT2z7fBPrKpBtWYfD6J2gDVgIzGZ0ispkY8SwvRhxrWTkUtwLuLVyCRLdA3GVbWTEqXbsQdJcR7hs9ZFpVMf+Vbn2cdnW8POjubRalM/5YhW8DW1l5EiyXn6s9DLmyDLbl0vTNky8p6yd2+UBzTfdRb+roKNXNh++qlBJdN04xz6urPALMc0pD7eF1oySn2usnSNnLBRlDbpIMqk1cvwCWtXJoxUXVlQZzNNYlsnRnRH1fmwLe/9Dztn2B39Iky3A3pMmuAYiQdW7JH3uezXAOJPkRY50Mk2SQrv74QFKk2BcnGm2vOdPUQq18W+GQvb9eptoYqUiWdbBxzX7j0lWLS25/oNc2UbvKPFxtLXWf1A7Z/fbRlaIWoD74T9VjsZSZvMTx7cV0vP2Zygp/mZxM1i+8fptmyi7/Gg+bOv1B2/SiJgYAD4U6B/7Gn2LXhAofKi2OUkT5GlVk386xXLz07tOUoB5EeyCmNkrp8Ss4Hr3ZQtTqaPZPfKKM62/wJUQ+yvEKBV6wGpFlxYyecytd7j85E8dhiR24U4dvUtF6Onpi85ibPvEo+QA8EqyEGJnz4YDyyDZhuvGj/0gmcR8SY+zv3lk5zJscmYTZMdTP/hbJLnTSM5guuQ5hKPnMGcjinMLZhcyVyQKc4tBsyFE/YE12Pr3xOMAVdjyjOVHxcjOpriRjXvYxWwnxKpBVYVqkOgEUctfqkTHA2xKVnsiCwHmeXriULWAWurlCZRjX4eBULT7Q3xq/ylR3YPcw8uR5vQd9jA7U5zSQ/JpcotCeQLX1t2cRep/1dTpLQSre6/UsugDBet7c3zrFSUBYtGt/rwD9Nx4i+LSvY+GtCpitcPMmDcrcuuw9kVgZ0oBelcVKzJ2CeeRKpCtw3hOFdd886PXrf60A7TAcYty88vOYeLLLATYDe3USXz0c5v+dzcLWuGXR3YPwm763wLVj8g7PI8kH0C01qWYJJacPCAPCtTD7mqtivYTFAEkV6JD4tTYiA6WpSQLIVZD6VoD4gqwcxWNISSzlvYlMeELsR6mZ2GtMqE5eK0FjTYIG79SuS72Vrwzweydjmfweq5jZYuYC/KUjl99DKCyStkpVK98+R62e3ZAVyMXyjYwC51GLIqjDISDYOL7pVJ2SkXnCFWdAJ977M74PNI=
*/