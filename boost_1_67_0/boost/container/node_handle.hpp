//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2016-2016. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_NODE_HANDLE_HPP
#define BOOST_CONTAINER_NODE_HANDLE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/static_assert.hpp>
#include <boost/container/detail/placement_new.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/container/allocator_traits.hpp>
#include <boost/container/detail/mpl.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/move/adl_move_swap.hpp>

#include <boost/type_traits/aligned_storage.hpp>


//!\file

namespace boost {
namespace container {

///@cond

template<class Value, class KeyMapped>
struct node_handle_keymapped_traits
{
   typedef typename KeyMapped::key_type      key_type;
   typedef typename KeyMapped::mapped_type   mapped_type;
};

template<class Value>
struct node_handle_keymapped_traits<Value, void>
{
   typedef Value key_type;
   typedef Value mapped_type;
};

class node_handle_friend
{
   public:

   template<class NH>
   BOOST_CONTAINER_FORCEINLINE static void destroy_alloc(NH &nh) BOOST_NOEXCEPT
   {  nh.destroy_alloc();  }

   template<class NH>
   BOOST_CONTAINER_FORCEINLINE static typename NH::node_pointer &get_node_pointer(NH &nh) BOOST_NOEXCEPT
   {  return nh.get_node_pointer();  }
};


///@endcond

//! A node_handle is an object that accepts ownership of a single element from an associative container.
//! It may be used to transfer that ownership to another container with compatible nodes. Containers
//! with compatible nodes have the same node handle type. Elements may be transferred in either direction
//! between container types in the same row:.
//!
//! Container types with compatible nodes
//!
//! map<K, T, C1, A> <-> map<K, T, C2, A>
//!
//! map<K, T, C1, A> <-> multimap<K, T, C2, A>
//! 
//! set<K, C1, A> <-> set<K, C2, A>
//! 
//! set<K, C1, A> <-> multiset<K, C2, A>
//! 
//! If a node handle is not empty, then it contains an allocator that is equal to the allocator of the container
//! when the element was extracted. If a node handle is empty, it contains no allocator.
template <class NodeAllocator, class KeyMapped = void>
class node_handle
{
   typedef NodeAllocator                                          nallocator_type;
   typedef allocator_traits<NodeAllocator>                        nator_traits;
   typedef typename nator_traits::value_type                      priv_node_t;
   typedef typename priv_node_t::value_type                       priv_value_t;
   typedef node_handle_keymapped_traits<priv_value_t, KeyMapped>  keymapped_t;

   public:
   typedef priv_value_t                                           value_type;
   typedef typename keymapped_t::key_type                         key_type;
   typedef typename keymapped_t::mapped_type                      mapped_type;
   typedef typename nator_traits::template portable_rebind_alloc
      <value_type>::type                                          allocator_type;

   typedef priv_node_t                                            container_node_type;
   friend class node_handle_friend;

   ///@cond
   private:
   BOOST_MOVABLE_BUT_NOT_COPYABLE(node_handle)

   typedef typename nator_traits::pointer                         node_pointer;
   typedef ::boost::aligned_storage
      < sizeof(nallocator_type)
      , boost::alignment_of<nallocator_type>::value>              nalloc_storage_t;

   node_pointer      m_ptr;
   nalloc_storage_t  m_nalloc_storage;

   void move_construct_alloc(nallocator_type &al)
   {  ::new(m_nalloc_storage.address(), boost_container_new_t()) nallocator_type(::boost::move(al));   }

   void destroy_deallocate_node()
   {
      nator_traits::destroy(this->node_alloc(), boost::movelib::to_raw_pointer(m_ptr));
      nator_traits::deallocate(this->node_alloc(), m_ptr, 1u);
   }

   template<class OtherNodeHandle>
   void move_construct_end(OtherNodeHandle &nh)
   {
      if(m_ptr){
         ::new (m_nalloc_storage.address(), boost_container_new_t()) nallocator_type(::boost::move(nh.node_alloc()));
         node_handle_friend::destroy_alloc(nh);
         node_handle_friend::get_node_pointer(nh) = node_pointer();
      }
      BOOST_ASSERT(nh.empty());
   }

   void destroy_alloc() BOOST_NOEXCEPT
   {  static_cast<nallocator_type*>(m_nalloc_storage.address())->~nallocator_type();  }

   node_pointer &get_node_pointer() BOOST_NOEXCEPT
   {  return m_ptr;  }

   ///@endcond

   public:
   //! <b>Effects</b>: Initializes m_ptr to nullptr.
   //!
   //! <b>Postcondition</b>: this->empty()
   BOOST_CXX14_CONSTEXPR node_handle() BOOST_NOEXCEPT
      :  m_ptr()
   { }

   //! <b>Effects</b>: Constructs a node_handle object initializing internal pointer with p.
   //!   If p != nullptr copy constructs internal allocator from al.
   node_handle(node_pointer p, const nallocator_type &al) BOOST_NOEXCEPT
      :  m_ptr(p)
   {
      if(m_ptr){
         ::new (m_nalloc_storage.address(), boost_container_new_t()) nallocator_type(al);
      }
   }

   //! <b>Effects</b>: Constructs a node_handle object initializing internal pointer with a related nh's internal pointer
   //!   and assigns nullptr to the later. If nh's internal pointer was not nullptr, move constructs internal
   //!   allocator with nh's internal allocator and destroy nh's internal allocator.
   //!
   //! <b>Postcondition</b>: nh.empty()
   //!
   //! <b>Note</b>: Two node_handle's are related if only one of KeyMapped template parameter
   //!   of a node handle is void.
   template<class KeyMapped2>
   node_handle( BOOST_RV_REF_BEG node_handle<NodeAllocator, KeyMapped2> BOOST_RV_REF_END nh
               , typename dtl::enable_if_c
                  < ((unsigned)dtl::is_same<KeyMapped,  void>::value +
                     (unsigned)dtl::is_same<KeyMapped2, void>::value) == 1u
                  >::type* = 0) BOOST_NOEXCEPT
      :  m_ptr(nh.get())
   {  this->move_construct_end(nh);  }

   //! <b>Effects</b>: Constructs a node_handle object initializing internal pointer with nh's internal pointer
   //!   and assigns nullptr to the later. If nh's internal pointer was not nullptr, move constructs internal
   //!   allocator with nh's internal allocator and destroy nh's internal allocator.
   //!
   //! <b>Postcondition</b>: nh.empty()
   node_handle (BOOST_RV_REF(node_handle) nh) BOOST_NOEXCEPT
      : m_ptr(nh.m_ptr)
   {  this->move_construct_end(nh);  }

   //! <b>Effects</b>: If !this->empty(), destroys the value_type subobject in the container_node_type object
   //!   pointed to by c by calling allocator_traits<impl_defined>::destroy, then deallocates m_ptr by calling
   //!   nator_traits::rebind_traits<container_node_type>::deallocate.
   ~node_handle() BOOST_NOEXCEPT
   {
      if(!this->empty()){
         this->destroy_deallocate_node();
         this->destroy_alloc();
      }
   }

   //! <b>Requires</b>: Either this->empty(), or nator_traits::propagate_on_container_move_assignment is true, or
   //!   node_alloc() == nh.node_alloc().
   //!
   //! <b>Effects</b>: If m_ptr != nullptr, destroys the value_type subobject in the container_node_type object
   //!   pointed to by m_ptr by calling nator_traits::destroy, then deallocates m_ptr by calling
   //!   nator_traits::deallocate. Assigns nh.m_ptr to m_ptr. If this->empty()
   //!   or nator_traits::propagate_on_container_move_assignment is true, move assigns nh.node_alloc() to
   //!   node_alloc(). Assigns nullptr to nh.m_ptr and assigns nullopt to nh.node_alloc().
   //!
   //! <b>Returns</b>: *this.
   //!
   //! <b>Throws</b>: Nothing.
   node_handle & operator=(BOOST_RV_REF(node_handle) nh) BOOST_NOEXCEPT
   {
      BOOST_ASSERT(this->empty() || nator_traits::propagate_on_container_move_assignment::value 
                   || nator_traits::equal(node_alloc(), nh.node_alloc()));

      bool const was_this_non_null = !this->empty();
      bool const was_nh_non_null   = !nh.empty();

      if(was_nh_non_null){
         if(was_this_non_null){
            this->destroy_deallocate_node();
            if(nator_traits::propagate_on_container_move_assignment::value){
               this->node_alloc() = ::boost::move(nh.node_alloc());
            }
         }
         else{
            this->move_construct_alloc(nh.node_alloc());
         }
         m_ptr = nh.m_ptr;
         nh.m_ptr = node_pointer();
         nh.destroy_alloc();
      }
      else if(was_this_non_null){
         this->destroy_deallocate_node();
         this->destroy_alloc();
         m_ptr = node_pointer();
      }
      return *this;
   }

   //! <b>Requires</b>: empty() == false.
   //!
   //! <b>Returns</b>: A reference to the value_type subobject in the container_node_type object pointed to by m_ptr
   //!
   //! <b>Throws</b>: Nothing.
   value_type& value() const BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((dtl::is_same<KeyMapped, void>::value));
      BOOST_ASSERT(!empty());
      return m_ptr->get_data();
   }

   //! <b>Requires</b>: empty() == false.
   //!
   //! <b>Returns</b>: A non-const reference to the key_type member of the value_type subobject in the 
   //!   container_node_type object pointed to by m_ptr.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Requires</b>: Modifying the key through the returned reference is permitted.
   key_type& key() const BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!dtl::is_same<KeyMapped, void>::value));
      BOOST_ASSERT(!empty());
      return const_cast<key_type &>(KeyMapped().key_of_value(m_ptr->get_data()));
   }

   //! <b>Requires</b>: empty() == false.
   //!
   //! <b>Returns</b>: A reference to the mapped_type member of the value_type subobject
   //!   in the container_node_type object pointed to by m_ptr
   //!
   //! <b>Throws</b>: Nothing.
   mapped_type& mapped() const BOOST_NOEXCEPT
   {
      BOOST_STATIC_ASSERT((!dtl::is_same<KeyMapped, void>::value));
      BOOST_ASSERT(!empty());
      return KeyMapped().mapped_of_value(m_ptr->get_data());
   }

   //! <b>Requires</b>: empty() == false.
   //!
   //! <b>Returns</b>: A copy of the internally hold allocator.
   //!
   //! <b>Throws</b>: Nothing.
   allocator_type get_allocator() const
   {
      BOOST_ASSERT(!empty());
      return this->node_alloc();
   }

   //! <b>Returns</b>: m_ptr != nullptr.
   //!
   #ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
   BOOST_CONTAINER_FORCEINLINE explicit operator bool
   #else
   private: struct bool_conversion {int for_bool; int for_arg(); }; typedef int bool_conversion::* explicit_bool_arg;
   public: BOOST_CONTAINER_FORCEINLINE operator explicit_bool_arg
   #endif
      ()const BOOST_NOEXCEPT
   {  return m_ptr ? &bool_conversion::for_bool  : explicit_bool_arg(0);  }

   //! <b>Returns</b>: m_ptr == nullptr.
   //!
   bool empty() const BOOST_NOEXCEPT
   {
      return !this->m_ptr;
   }

   //! <b>Requires</b>: this->empty(), or nh.empty(), or nator_traits::propagate_on_container_swap is true, or
   //!   node_alloc() == nh.node_alloc().
   //!
   //! <b>Effects</b>: Calls swap(m_ptr, nh.m_ptr). If this->empty(), or nh.empty(), or nator_traits::propagate_on_-
   //!   container_swap is true calls swap(node_alloc(), nh.node_alloc()).
   void swap(node_handle &nh)
      BOOST_NOEXCEPT_IF(nator_traits::propagate_on_container_swap::value || nator_traits::is_always_equal::value)
   {
      BOOST_ASSERT(this->empty() || nh.empty() || nator_traits::propagate_on_container_swap::value
                   || nator_traits::equal(node_alloc(), nh.node_alloc()));

      bool const was_this_non_null = !this->empty();
      bool const was_nh_non_null   = !nh.empty();

      if(was_nh_non_null){
         if(was_this_non_null){
            if(nator_traits::propagate_on_container_swap::value){
               ::boost::adl_move_swap(this->node_alloc(), nh.node_alloc());
            }
         }
         else{
            this->move_construct_alloc(nh.node_alloc());
            nh.destroy_alloc();
         }
      }
      else if(was_this_non_null){
         nh.move_construct_alloc(this->node_alloc());
         this->destroy_alloc();
      }
      ::boost::adl_move_swap(m_ptr, nh.m_ptr);
   }

   //! <b>Effects</b>: If this->empty() returns nullptr, otherwise returns m_ptr
   //!   resets m_ptr to nullptr and destroys the internal allocator.
   //!
   //! <b>Postcondition</b>: this->empty()
   //!
   //! <b>Note</b>: Non-standard extensions
   node_pointer release() BOOST_NOEXCEPT
   {
      node_pointer p(m_ptr);
      m_ptr = node_pointer();
      if(p)
         this->destroy_alloc();
      return p;
   }

   //! <b>Effects</b>: Returns m_ptr.
   //!
   //! <b>Note</b>: Non-standard extensions
   node_pointer get() const BOOST_NOEXCEPT
   {
      return m_ptr;
   }

   //! <b>Effects</b>: Returns a reference to the internal node allocator.
   //!
   //! <b>Note</b>: Non-standard extensions
   nallocator_type &node_alloc() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(!empty());
      return *static_cast<nallocator_type*>(m_nalloc_storage.address());
   }


   //! <b>Effects</b>: Returns a reference to the internal node allocator.
   //!
   //! <b>Note</b>: Non-standard extensions
   const nallocator_type &node_alloc() const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(!empty());
      return *static_cast<const nallocator_type*>(m_nalloc_storage.address());
   }

   //! <b>Effects</b>: x.swap(y).
   //!
   friend void swap(node_handle & x, node_handle & y) BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT(x.swap(y)))
   {  x.swap(y);  }
};

//! A class template used to describe the results of inserting a
//! Container::node_type in a Container with unique keys.
//! Includes at least the following non-static public data members:
//!
//! <ul><li>bool inserted</li>;
//! <li>Iterator position</li>;
//! <li>NodeType node</li></ul>
//!
//! This type is MoveConstructible, MoveAssignable, DefaultConstructible,
//! Destructible, and lvalues of that type are swappable
template<class Iterator, class NodeType>
struct insert_return_type_base
{
   private:
   BOOST_MOVABLE_BUT_NOT_COPYABLE(insert_return_type_base)

   public:
   insert_return_type_base()
      : inserted(false), position(), node()
   {}

   insert_return_type_base(BOOST_RV_REF(insert_return_type_base) other)
      : inserted(other.inserted), position(other.position), node(boost::move(other.node))
   {}

   template<class RelatedIt, class RelatedNode>
   insert_return_type_base(bool insert, RelatedIt it, BOOST_RV_REF(RelatedNode) node)
      : inserted(insert), position(it), node(boost::move(node))
   {}

   insert_return_type_base & operator=(BOOST_RV_REF(insert_return_type_base) other)
   {
      inserted = other.inserted;
      position = other.position;
      node = boost::move(other.node);
      return *this;
   }

   bool  inserted;
   Iterator position;
   NodeType node;
};

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_NODE_HANDLE_HPP

/* node_handle.hpp
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
*/