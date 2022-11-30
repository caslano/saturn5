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
      boost::movelib::to_raw_pointer(m_ptr)->destructor(this->node_alloc());
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
   insert_return_type_base(bool insert, RelatedIt it, BOOST_RV_REF(RelatedNode) n)
      : inserted(insert), position(it), node(boost::move(n))
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