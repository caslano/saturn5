//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2008-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
// Stable vector.
//
// Copyright 2008 Joaquin M Lopez Munoz.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_STABLE_VECTOR_HPP
#define BOOST_CONTAINER_STABLE_VECTOR_HPP

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
#include <boost/container/detail/addressof.hpp>
#include <boost/container/detail/algorithm.hpp> //algo_equal(), algo_lexicographical_compare
#include <boost/container/detail/alloc_helpers.hpp>
#include <boost/container/detail/allocator_version_traits.hpp>
#include <boost/container/detail/construct_in_place.hpp>
#include <boost/container/detail/iterator.hpp>
#include <boost/container/detail/iterators.hpp>
#include <boost/container/detail/placement_new.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/container/detail/type_traits.hpp>
// intrusive
#include <boost/intrusive/pointer_traits.hpp>
// intrusive/detail
#include <boost/intrusive/detail/minimal_pair_header.hpp>   //pair
// move
#include <boost/move/utility_core.hpp>
#include <boost/move/iterator.hpp>
#include <boost/move/adl_move_swap.hpp>
// move/detail
#include <boost/move/detail/move_helpers.hpp>
// other
#include <boost/assert.hpp>
#include <boost/core/no_exceptions_support.hpp>
// std
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>
#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   #include <boost/container/vector.hpp>
   //#define STABLE_VECTOR_ENABLE_INVARIANT_CHECKING
#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace boost {
namespace container {

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

namespace stable_vector_detail{

template <class C>
class clear_on_destroy
{
   public:
   BOOST_CONTAINER_FORCEINLINE clear_on_destroy(C &c)
      :  c_(c), do_clear_(true)
   {}

   BOOST_CONTAINER_FORCEINLINE void release()
   {  do_clear_ = false; }

   BOOST_CONTAINER_FORCEINLINE ~clear_on_destroy()
   {
      if(do_clear_){
         c_.clear();
         c_.priv_clear_pool();
      }
   }

   private:
   clear_on_destroy(const clear_on_destroy &);
   clear_on_destroy &operator=(const clear_on_destroy &);
   C &c_;
   bool do_clear_;
};

template<typename Pointer>
struct node;

template<class VoidPtr>
struct node_base
{
   private:
   typedef typename boost::intrusive::
      pointer_traits<VoidPtr>                   void_ptr_traits;
   typedef typename void_ptr_traits::
      template rebind_pointer
         <node_base>::type                      node_base_ptr;

   public:
   typedef typename void_ptr_traits::
      template rebind_pointer
         <node_base_ptr>::type                  node_base_ptr_ptr;

   public:
   BOOST_CONTAINER_FORCEINLINE explicit node_base(const node_base_ptr_ptr &n)
      : up(n)
   {}

   BOOST_CONTAINER_FORCEINLINE node_base()
      : up()
   {}

   node_base_ptr_ptr up;
};


template<typename Pointer>
struct node
   : public node_base
      <typename ::boost::intrusive::pointer_traits<Pointer>::template
         rebind_pointer<void>::type
      >
{
   public:
   typedef typename ::boost::intrusive::pointer_traits<Pointer>::element_type T;
   typedef node_base
      <typename ::boost::intrusive::pointer_traits<Pointer>::template
         rebind_pointer<void>::type
      > hook_type;

   typedef typename boost::container::dtl::aligned_storage
      <sizeof(T), boost::container::dtl::alignment_of<T>::value>::type storage_t;
   storage_t m_storage;

   BOOST_CONTAINER_FORCEINLINE explicit node(const typename hook_type::node_base_ptr_ptr &n)
      : hook_type(n)
   {}

   BOOST_CONTAINER_FORCEINLINE node()
   {}

   #if defined(BOOST_GCC) && (BOOST_GCC >= 40600) && (BOOST_GCC < 80000)
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wstrict-aliasing"
      #define BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif

   BOOST_CONTAINER_FORCEINLINE T &get_data()
   {  return *reinterpret_cast<T*>(this->m_storage.data);   }

   BOOST_CONTAINER_FORCEINLINE const T &get_data() const
   {  return *reinterpret_cast<const T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE T *get_data_ptr()
   {  return reinterpret_cast<T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE const T *get_data_ptr() const
   {  return reinterpret_cast<T*>(this->m_storage.data);  }

   BOOST_CONTAINER_FORCEINLINE ~node()
   {  reinterpret_cast<T*>(this->m_storage.data)->~T();  }

   #if defined(BOOST_CONTAINER_DISABLE_ALIASING_WARNING)
      #pragma GCC diagnostic pop
      #undef BOOST_CONTAINER_DISABLE_ALIASING_WARNING
   #  endif

   BOOST_CONTAINER_FORCEINLINE void destroy_header()
   {  static_cast<hook_type*>(this)->~hook_type();  }
};

template<class VoidPtr, class VoidAllocator>
struct index_traits
{
   typedef boost::intrusive::
      pointer_traits
         <VoidPtr>                                    void_ptr_traits;
   typedef stable_vector_detail::
      node_base<VoidPtr>                              node_base_type;
   typedef typename void_ptr_traits::template
         rebind_pointer<node_base_type>::type         node_base_ptr;
   typedef typename void_ptr_traits::template
         rebind_pointer<node_base_ptr>::type          node_base_ptr_ptr;
   typedef boost::intrusive::
      pointer_traits<node_base_ptr>                   node_base_ptr_traits;
   typedef boost::intrusive::
      pointer_traits<node_base_ptr_ptr>               node_base_ptr_ptr_traits;
   typedef typename allocator_traits<VoidAllocator>::
         template portable_rebind_alloc
            <node_base_ptr>::type                     node_base_ptr_allocator;
   typedef ::boost::container::vector
      <node_base_ptr, node_base_ptr_allocator>        index_type;
   typedef typename index_type::iterator              index_iterator;
   typedef typename index_type::const_iterator        const_index_iterator;
   typedef typename index_type::size_type             size_type;

   static const size_type ExtraPointers = 3;
   //Stable vector stores metadata at the end of the index (node_base_ptr vector) with additional 3 pointers:
   //    back() is this->index.back() - ExtraPointers;
   //    end node index is    *(this->index.end() - 3)
   //    Node cache first is  *(this->index.end() - 2);
   //    Node cache last is   this->index.back();

   BOOST_CONTAINER_FORCEINLINE static node_base_ptr_ptr ptr_to_node_base_ptr(node_base_ptr &n)
   {  return node_base_ptr_ptr_traits::pointer_to(n);   }

   static void fix_up_pointers(index_iterator first, index_iterator last)
   {
      while(first != last){
         typedef typename index_type::reference node_base_ptr_ref;
         node_base_ptr_ref nbp = *first;
         nbp->up = index_traits::ptr_to_node_base_ptr(nbp);
         ++first;
      }
   }

   BOOST_CONTAINER_FORCEINLINE static index_iterator get_fix_up_end(index_type &index)
   {  return index.end() - (ExtraPointers - 1); }

   BOOST_CONTAINER_FORCEINLINE static void fix_up_pointers_from(index_type & index, index_iterator first)
   {  index_traits::fix_up_pointers(first, index_traits::get_fix_up_end(index));   }

   static void readjust_end_node(index_type &index, node_base_type &end_node)
   {
      if(!index.empty()){
         index_iterator end_node_it(index_traits::get_fix_up_end(index));
         node_base_ptr &end_node_idx_ref = *(--end_node_it);
         end_node_idx_ref = node_base_ptr_traits::pointer_to(end_node);
         end_node.up      = node_base_ptr_ptr_traits::pointer_to(end_node_idx_ref);
      }
      else{
         end_node.up = node_base_ptr_ptr();
      }
   }

   static void initialize_end_node(index_type &index, node_base_type &end_node, const size_type index_capacity_if_empty)
   {
      if(index.empty()){
         index.reserve(index_capacity_if_empty + ExtraPointers);
         index.resize(ExtraPointers);
         node_base_ptr &end_node_ref = *index.data();
         end_node_ref = node_base_ptr_traits::pointer_to(end_node);
         end_node.up = index_traits::ptr_to_node_base_ptr(end_node_ref);
      }
   }

   #ifdef STABLE_VECTOR_ENABLE_INVARIANT_CHECKING
   static bool invariants(index_type &index)
   {
      for( index_iterator it = index.begin()
         , it_end = index_traits::get_fix_up_end(index)
         ; it != it_end
         ; ++it){
         if((*it)->up != index_traits::ptr_to_node_base_ptr(*it)){
            return false;
         }
      }
      return true;
   }
   #endif   //STABLE_VECTOR_ENABLE_INVARIANT_CHECKING
};

} //namespace stable_vector_detail

template<typename Pointer, bool IsConst>
class stable_vector_iterator
{
   typedef boost::intrusive::pointer_traits<Pointer>                                non_const_ptr_traits;
   public:
   typedef std::random_access_iterator_tag                                          iterator_category;
   typedef typename non_const_ptr_traits::element_type                              value_type;
   typedef typename non_const_ptr_traits::difference_type                           difference_type;
   typedef typename ::boost::container::dtl::if_c
      < IsConst
      , typename non_const_ptr_traits::template
         rebind_pointer<const value_type>::type
      , Pointer
      >::type                                                                       pointer;
   typedef boost::intrusive::pointer_traits<pointer>                                ptr_traits;
   typedef typename ptr_traits::reference                                           reference;

   typedef typename non_const_ptr_traits::template
         rebind_pointer<void>::type             void_ptr;
   typedef stable_vector_detail::node<Pointer>         node_type;
   typedef stable_vector_detail::node_base<void_ptr>   node_base_type;
   typedef typename non_const_ptr_traits::template
         rebind_pointer<node_type>::type        node_ptr;
   typedef boost::intrusive::
      pointer_traits<node_ptr>                  node_ptr_traits;
   typedef typename non_const_ptr_traits::template
         rebind_pointer<node_base_type>::type   node_base_ptr;
   typedef typename non_const_ptr_traits::template
         rebind_pointer<node_base_ptr>::type    node_base_ptr_ptr;

   class nat
   {
      public:
      node_base_ptr node_pointer() const
      { return node_base_ptr();  }
   };
   typedef typename dtl::if_c< IsConst
                             , stable_vector_iterator<Pointer, false>
                             , nat>::type                                           nonconst_iterator;

   node_base_ptr m_pn;

   public:

   BOOST_CONTAINER_FORCEINLINE explicit stable_vector_iterator(node_base_ptr p) BOOST_NOEXCEPT_OR_NOTHROW
      : m_pn(p)
   {}

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator() BOOST_NOEXCEPT_OR_NOTHROW
      : m_pn() //Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator(const stable_vector_iterator& other) BOOST_NOEXCEPT_OR_NOTHROW
      :  m_pn(other.node_pointer())
   {}

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator(const nonconst_iterator& other) BOOST_NOEXCEPT_OR_NOTHROW
      :  m_pn(other.node_pointer())
   {}

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator & operator=(const stable_vector_iterator& other) BOOST_NOEXCEPT_OR_NOTHROW
   {  m_pn = other.node_pointer(); return *this;   }

   BOOST_CONTAINER_FORCEINLINE node_ptr node_pointer() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return node_ptr_traits::static_cast_from(m_pn);  }

   public:
   //Pointer like operators
   BOOST_CONTAINER_FORCEINLINE reference operator*()  const BOOST_NOEXCEPT_OR_NOTHROW
   {  return  node_pointer()->get_data();  }

   BOOST_CONTAINER_FORCEINLINE pointer operator->() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return ptr_traits::pointer_to(this->operator*());  }

   //Increment / Decrement
   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator& operator++() BOOST_NOEXCEPT_OR_NOTHROW
   {
      node_base_ptr_ptr p(this->m_pn->up);
      this->m_pn = *(++p);
      return *this;
   }

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator operator++(int) BOOST_NOEXCEPT_OR_NOTHROW
   {  stable_vector_iterator tmp(*this);  ++*this; return stable_vector_iterator(tmp); }

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator& operator--() BOOST_NOEXCEPT_OR_NOTHROW
   {
      node_base_ptr_ptr p(this->m_pn->up);
      this->m_pn = *(--p);
      return *this;
   }

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator operator--(int) BOOST_NOEXCEPT_OR_NOTHROW
   {  stable_vector_iterator tmp(*this);  --*this; return stable_vector_iterator(tmp);  }

   BOOST_CONTAINER_FORCEINLINE reference operator[](difference_type off) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return node_ptr_traits::static_cast_from(this->m_pn->up[off])->get_data();  }

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator& operator+=(difference_type off) BOOST_NOEXCEPT_OR_NOTHROW
   {
      if(off) this->m_pn = this->m_pn->up[off];
      return *this;
   }

   BOOST_CONTAINER_FORCEINLINE friend stable_vector_iterator operator+(const stable_vector_iterator &left, difference_type off) BOOST_NOEXCEPT_OR_NOTHROW
   {
      stable_vector_iterator tmp(left);
      tmp += off;
      return tmp;
   }

   BOOST_CONTAINER_FORCEINLINE friend stable_vector_iterator operator+(difference_type off, const stable_vector_iterator& right) BOOST_NOEXCEPT_OR_NOTHROW
   {
      stable_vector_iterator tmp(right);
      tmp += off;
      return tmp;
   }

   BOOST_CONTAINER_FORCEINLINE stable_vector_iterator& operator-=(difference_type off) BOOST_NOEXCEPT_OR_NOTHROW
   {  *this += -off; return *this;   }

   BOOST_CONTAINER_FORCEINLINE friend stable_vector_iterator operator-(const stable_vector_iterator &left, difference_type off) BOOST_NOEXCEPT_OR_NOTHROW
   {
      stable_vector_iterator tmp(left);
      tmp -= off;
      return tmp;
   }

   BOOST_CONTAINER_FORCEINLINE friend difference_type operator-(const stable_vector_iterator &left, const stable_vector_iterator &right) BOOST_NOEXCEPT_OR_NOTHROW
   {  return left.m_pn->up - right.m_pn->up;  }

   //Comparison operators
   BOOST_CONTAINER_FORCEINLINE friend bool operator==   (const stable_vector_iterator& l, const stable_vector_iterator& r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return l.m_pn == r.m_pn;  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator!=   (const stable_vector_iterator& l, const stable_vector_iterator& r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return l.m_pn != r.m_pn;  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<    (const stable_vector_iterator& l, const stable_vector_iterator& r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return l.m_pn->up < r.m_pn->up;  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator<=   (const stable_vector_iterator& l, const stable_vector_iterator& r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return l.m_pn->up <= r.m_pn->up;  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>    (const stable_vector_iterator& l, const stable_vector_iterator& r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return l.m_pn->up > r.m_pn->up;  }

   BOOST_CONTAINER_FORCEINLINE friend bool operator>=   (const stable_vector_iterator& l, const stable_vector_iterator& r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return l.m_pn->up >= r.m_pn->up;  }
};

   #if defined(STABLE_VECTOR_ENABLE_INVARIANT_CHECKING)

      #define STABLE_VECTOR_CHECK_INVARIANT \
               invariant_checker BOOST_JOIN(check_invariant_,__LINE__)(*this); \
               BOOST_JOIN(check_invariant_,__LINE__).touch();

   #else //STABLE_VECTOR_ENABLE_INVARIANT_CHECKING

      #define STABLE_VECTOR_CHECK_INVARIANT

   #endif   //#if defined(STABLE_VECTOR_ENABLE_INVARIANT_CHECKING)

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! Originally developed by Joaquin M. Lopez Munoz, stable_vector is a std::vector
//! drop-in replacement implemented as a node container, offering iterator and reference
//! stability.
//!
//! Here are the details taken from the author's blog
//! (<a href="http://bannalia.blogspot.com/2008/09/introducing-stablevector.html" >
//! Introducing stable_vector</a>):
//!
//! We present stable_vector, a fully STL-compliant stable container that provides
//! most of the features of std::vector except element contiguity.
//!
//! General properties: stable_vector satisfies all the requirements of a container,
//! a reversible container and a sequence and provides all the optional operations
//! present in std::vector. Like std::vector, iterators are random access.
//! stable_vector does not provide element contiguity; in exchange for this absence,
//! the container is stable, i.e. references and iterators to an element of a stable_vector
//! remain valid as long as the element is not erased, and an iterator that has been
//! assigned the return value of end() always remain valid until the destruction of
//! the associated  stable_vector.
//!
//! Operation complexity: The big-O complexities of stable_vector operations match
//! exactly those of std::vector. In general, insertion/deletion is constant time at
//! the end of the sequence and linear elsewhere. Unlike std::vector, stable_vector
//! does not internally perform any value_type destruction, copy or assignment
//! operations other than those exactly corresponding to the insertion of new
//! elements or deletion of stored elements, which can sometimes compensate in terms
//! of performance for the extra burden of doing more pointer manipulation and an
//! additional allocation per element.
//!
//! Exception safety: As stable_vector does not internally copy elements around, some
//! operations provide stronger exception safety guarantees than in std::vector.
//!
//! \tparam T The type of object that is stored in the stable_vector
//! \tparam Allocator The allocator used for all internal memory management
#ifdef BOOST_CONTAINER_DOXYGEN_INVOKED
template <class T, class Allocator = void >
#else
template <class T, class Allocator>
#endif
class stable_vector
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef typename real_allocator<T, Allocator>::type     ValueAllocator;
   typedef allocator_traits<ValueAllocator>                allocator_traits_type;
   typedef boost::intrusive::
      pointer_traits
         <typename allocator_traits_type::pointer>    ptr_traits;
   typedef typename ptr_traits::
         template rebind_pointer<void>::type          void_ptr;
   typedef typename allocator_traits_type::
      template portable_rebind_alloc
         <void>::type                                 void_allocator_type;
   typedef stable_vector_detail::index_traits
      <void_ptr, void_allocator_type>                 index_traits_type;
   typedef typename index_traits_type::node_base_type node_base_type;
   typedef typename index_traits_type::node_base_ptr  node_base_ptr;
   typedef typename index_traits_type::
      node_base_ptr_ptr                               node_base_ptr_ptr;
   typedef typename index_traits_type::
      node_base_ptr_traits                            node_base_ptr_traits;
   typedef typename index_traits_type::
      node_base_ptr_ptr_traits                        node_base_ptr_ptr_traits;
   typedef typename index_traits_type::index_type     index_type;
   typedef typename index_traits_type::index_iterator index_iterator;
   typedef typename index_traits_type::
      const_index_iterator                            const_index_iterator;
   typedef stable_vector_detail::node
      <typename ptr_traits::pointer>                  node_type;
   typedef typename ptr_traits::template
      rebind_pointer<node_type>::type                 node_ptr;
   typedef boost::intrusive::
      pointer_traits<node_ptr>                        node_ptr_traits;
   typedef typename ptr_traits::template
      rebind_pointer<const node_type>::type           const_node_ptr;
   typedef boost::intrusive::
      pointer_traits<const_node_ptr>                  const_node_ptr_traits;
   typedef typename node_ptr_traits::reference        node_reference;
   typedef typename const_node_ptr_traits::reference  const_node_reference;

   typedef ::boost::container::dtl::integral_constant
      <unsigned, boost::container::dtl::
      version<ValueAllocator>::value>                              alloc_version;
   typedef typename allocator_traits_type::
      template portable_rebind_alloc
         <node_type>::type                            node_allocator_type;

   typedef ::boost::container::dtl::
      allocator_version_traits<node_allocator_type>                    allocator_version_traits_t;
   typedef typename allocator_version_traits_t::multiallocation_chain  multiallocation_chain;

   BOOST_CONTAINER_FORCEINLINE node_ptr allocate_one()
   {  return allocator_version_traits_t::allocate_one(this->priv_node_alloc());   }

   BOOST_CONTAINER_FORCEINLINE void deallocate_one(const node_ptr &p)
   {  allocator_version_traits_t::deallocate_one(this->priv_node_alloc(), p);   }

   BOOST_CONTAINER_FORCEINLINE void allocate_individual(typename allocator_traits_type::size_type n, multiallocation_chain &m)
   {  allocator_version_traits_t::allocate_individual(this->priv_node_alloc(), n, m);   }

   BOOST_CONTAINER_FORCEINLINE void deallocate_individual(multiallocation_chain &holder)
   {  allocator_version_traits_t::deallocate_individual(this->priv_node_alloc(), holder);   }

   friend class stable_vector_detail::clear_on_destroy<stable_vector>;
   typedef stable_vector_iterator
      < typename allocator_traits<ValueAllocator>::pointer
      , false>                                           iterator_impl;
   typedef stable_vector_iterator
      < typename allocator_traits<ValueAllocator>::pointer
      , true>                                            const_iterator_impl;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   public:

   //////////////////////////////////////////////
   //
   //                    types
   //
   //////////////////////////////////////////////
   typedef T                                                                           value_type;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::pointer           pointer;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::const_pointer     const_pointer;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::reference         reference;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::const_reference   const_reference;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::size_type         size_type;
   typedef typename ::boost::container::allocator_traits<ValueAllocator>::difference_type   difference_type;
   typedef ValueAllocator                                                                   allocator_type;
   typedef node_allocator_type                                                         stored_allocator_type;
   typedef BOOST_CONTAINER_IMPDEF(iterator_impl)                                       iterator;
   typedef BOOST_CONTAINER_IMPDEF(const_iterator_impl)                                 const_iterator;
   typedef BOOST_CONTAINER_IMPDEF(boost::container::reverse_iterator<iterator>)        reverse_iterator;
   typedef BOOST_CONTAINER_IMPDEF(boost::container::reverse_iterator<const_iterator>)  const_reverse_iterator;

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:
   BOOST_COPYABLE_AND_MOVABLE(stable_vector)
   static const size_type ExtraPointers = index_traits_type::ExtraPointers;

   class insert_rollback;
   friend class insert_rollback;

   class push_back_rollback;
   friend class push_back_rollback;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   //////////////////////////////////////////////
   //
   //          construct/copy/destroy
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Default constructs a stable_vector.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE stable_vector() BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<ValueAllocator>::value)
      : internal_data(), index()
   {
      STABLE_VECTOR_CHECK_INVARIANT;
   }

   //! <b>Effects</b>: Constructs a stable_vector taking the allocator as parameter.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE explicit stable_vector(const allocator_type& al) BOOST_NOEXCEPT_OR_NOTHROW
      : internal_data(al), index(al)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
   }

   //! <b>Effects</b>: Constructs a stable_vector
   //!   and inserts n value initialized values.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   explicit stable_vector(size_type n)
      : internal_data(), index()
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->resize(n);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Constructs a stable_vector
   //!   and inserts n default initialized values.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   //!
   //! <b>Note</b>: Non-standard extension
   stable_vector(size_type n, default_init_t)
      : internal_data(), index()
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->resize(n, default_init);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Constructs a stable_vector that will use a copy of allocator a
   //!   and inserts n value initialized values.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   explicit stable_vector(size_type n, const allocator_type &a)
      : internal_data(), index(a)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->resize(n);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Constructs a stable_vector that will use a copy of allocator a
   //!   and inserts n default initialized values.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   //!
   //! <b>Note</b>: Non-standard extension
   stable_vector(size_type n, default_init_t, const allocator_type &a)
      : internal_data(), index(a)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->resize(n, default_init);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Constructs a stable_vector that will use a copy of allocator a
   //!   and inserts n copies of value.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's default or copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   stable_vector(size_type n, const T& t, const allocator_type& al = allocator_type())
      : internal_data(al), index(al)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->insert(this->cend(), n, t);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Constructs a stable_vector that will use a copy of allocator a
   //!   and inserts a copy of the range [first, last) in the stable_vector.
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's constructor taking a dereferenced InIt throws.
   //!
   //! <b>Complexity</b>: Linear to the range [first, last).
   template <class InputIterator>
   stable_vector(InputIterator first,InputIterator last, const allocator_type& al = allocator_type())
      : internal_data(al), index(al)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->insert(this->cend(), first, last);
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Copy constructs a stable_vector.
   //!
   //! <b>Postcondition</b>: x == *this.
   //!
   //! <b>Complexity</b>: Linear to the elements x contains.
   stable_vector(const stable_vector& x)
      : internal_data(allocator_traits<node_allocator_type>::
         select_on_container_copy_construction(x.priv_node_alloc()))
      , index(allocator_traits<allocator_type>::
         select_on_container_copy_construction(x.index.get_stored_allocator()))
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->insert(this->cend(), x.begin(), x.end());
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Constructs a stable_vector that will use a copy of allocator a
   //!  and inserts a copy of the range [il.begin(), il.last()) in the stable_vector
   //!
   //! <b>Throws</b>: If allocator_type's default constructor
   //!   throws or T's constructor taking a dereferenced initializer_list iterator throws.
   //!
   //! <b>Complexity</b>: Linear to the range [il.begin(), il.end()).
   stable_vector(std::initializer_list<value_type> il, const allocator_type& l = allocator_type())
      : internal_data(l), index(l)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      insert(cend(), il.begin(), il.end());
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }
#endif

   //! <b>Effects</b>: Move constructor. Moves x's resources to *this.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE stable_vector(BOOST_RV_REF(stable_vector) x) BOOST_NOEXCEPT_OR_NOTHROW
      : internal_data(boost::move(x.priv_node_alloc())), index(boost::move(x.index))
   {
      this->priv_swap_members(x);
   }

   //! <b>Effects</b>: Copy constructs a stable_vector using the specified allocator.
   //!
   //! <b>Postcondition</b>: x == *this.
   //!
   //! <b>Complexity</b>: Linear to the elements x contains.
   stable_vector(const stable_vector& x, const allocator_type &a)
      : internal_data(a), index(a)
   {
      stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
      this->insert(this->cend(), x.begin(), x.end());
      STABLE_VECTOR_CHECK_INVARIANT;
      cod.release();
   }

   //! <b>Effects</b>: Move constructor using the specified allocator.
   //!                 Moves x's resources to *this.
   //!
   //! <b>Throws</b>: If allocator_type's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant if a == x.get_allocator(), linear otherwise
   stable_vector(BOOST_RV_REF(stable_vector) x, const allocator_type &a)
      : internal_data(a), index(a)
   {
      if(this->priv_node_alloc() == x.priv_node_alloc()){
         this->index.swap(x.index);         
         this->priv_swap_members(x);
      }
      else{
         stable_vector_detail::clear_on_destroy<stable_vector> cod(*this);
         this->insert(this->cend(), boost::make_move_iterator(x.begin()), boost::make_move_iterator(x.end()));
         STABLE_VECTOR_CHECK_INVARIANT;
         cod.release();
      }
   }

   //! <b>Effects</b>: Destroys the stable_vector. All stored values are destroyed
   //!   and used memory is deallocated.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements.
   ~stable_vector()
   {
      this->clear();
      this->priv_clear_pool();
   }

   //! <b>Effects</b>: Makes *this contain the same elements as x.
   //!
   //! <b>Postcondition</b>: this->size() == x.size(). *this contains a copy
   //! of each of x's elements.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in x.
   stable_vector& operator=(BOOST_COPY_ASSIGN_REF(stable_vector) x)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      if (BOOST_LIKELY(this != &x)) {
         node_allocator_type &this_alloc     = this->priv_node_alloc();
         const node_allocator_type &x_alloc  = x.priv_node_alloc();
         dtl::bool_<allocator_traits_type::
            propagate_on_container_copy_assignment::value> flag;
         if(flag && this_alloc != x_alloc){
            this->clear();
            this->shrink_to_fit();
         }
         dtl::assign_alloc(this->priv_node_alloc(), x.priv_node_alloc(), flag);
         dtl::assign_alloc(this->index.get_stored_allocator(), x.index.get_stored_allocator(), flag);
         this->assign(x.begin(), x.end());
      }
      return *this;
   }

   //! <b>Effects</b>: Move assignment. All x's values are transferred to *this.
   //!
   //! <b>Postcondition</b>: x.empty(). *this contains a the elements x had
   //!   before the function.
   //!
   //! <b>Throws</b>: If allocator_traits_type::propagate_on_container_move_assignment
   //!   is false and (allocation throws or T's move constructor throws)
   //!
   //! <b>Complexity</b>: Constant if allocator_traits_type::
   //!   propagate_on_container_move_assignment is true or
   //!   this->get>allocator() == x.get_allocator(). Linear otherwise.
   stable_vector& operator=(BOOST_RV_REF(stable_vector) x)
      BOOST_NOEXCEPT_IF(allocator_traits_type::propagate_on_container_move_assignment::value
                                  || allocator_traits_type::is_always_equal::value)
   {
      //for move constructor, no aliasing (&x != this) is assumed.
      if (BOOST_LIKELY(this != &x)) {
         node_allocator_type &this_alloc = this->priv_node_alloc();
         node_allocator_type &x_alloc    = x.priv_node_alloc();
         const bool propagate_alloc = allocator_traits_type::
               propagate_on_container_move_assignment::value;
         dtl::bool_<propagate_alloc> flag;
         const bool allocators_equal = this_alloc == x_alloc; (void)allocators_equal;
         //Resources can be transferred if both allocators are
         //going to be equal after this function (either propagated or already equal)
         if(propagate_alloc || allocators_equal){
            STABLE_VECTOR_CHECK_INVARIANT
            //Destroy objects but retain memory in case x reuses it in the future
            this->clear();
            //Move allocator if needed
            dtl::move_alloc(this_alloc, x_alloc, flag);
            //Take resources
            this->index.swap(x.index);
            this->priv_swap_members(x);
         }
         //Else do a one by one move
         else{
            this->assign( boost::make_move_iterator(x.begin())
                        , boost::make_move_iterator(x.end()));
         }
      }
      return *this;
   }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Make *this container contains elements from il.
   //!
   //! <b>Complexity</b>: Linear to the range [il.begin(), il.end()).
   stable_vector& operator=(std::initializer_list<value_type> il)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      assign(il.begin(), il.end());
      return *this;
   }
#endif

   //! <b>Effects</b>: Assigns the n copies of val to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   BOOST_CONTAINER_FORCEINLINE void assign(size_type n, const T& t)
   {
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
      this->assign(cvalue_iterator(t, n), cvalue_iterator());
   }

   //! <b>Effects</b>: Assigns the the range [first, last) to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's constructor from dereferencing InpIt throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   template<typename InputIterator>
   #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   typename dtl::disable_if_convertible<InputIterator, size_type>::type
   #else
   void
   #endif
      assign(InputIterator first,InputIterator last)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      iterator first1   = this->begin();
      iterator last1    = this->end();
      for ( ; first1 != last1 && first != last; ++first1, ++first)
         *first1 = *first;
      if (first == last){
         this->erase(first1, last1);
      }
      else{
         this->insert(last1, first, last);
      }
   }

#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Effects</b>: Assigns the the range [il.begin(), il.end()) to *this.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's constructor from dereferencing initializer_list iterator throws.
   //!
   BOOST_CONTAINER_FORCEINLINE void assign(std::initializer_list<value_type> il)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      assign(il.begin(), il.end());
   }
#endif

   //! <b>Effects</b>: Returns a copy of the internal allocator.
   //!
   //! <b>Throws</b>: If allocator's copy constructor throws.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE allocator_type get_allocator() const
   {  return this->priv_node_alloc();  }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE const stored_allocator_type &get_stored_allocator() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->priv_node_alloc(); }

   //! <b>Effects</b>: Returns a reference to the internal allocator.
   //!
   //! <b>Throws</b>: Nothing
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Note</b>: Non-standard extension.
   BOOST_CONTAINER_FORCEINLINE stored_allocator_type &get_stored_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->priv_node_alloc(); }

   //////////////////////////////////////////////
   //
   //                iterators
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns an iterator to the first element contained in the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE iterator begin() BOOST_NOEXCEPT_OR_NOTHROW
   {   return (this->index.empty()) ? this->end(): iterator(node_ptr_traits::static_cast_from(this->index.front())); }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_iterator begin() const BOOST_NOEXCEPT_OR_NOTHROW
   {   return (this->index.empty()) ? this->cend() : const_iterator(node_ptr_traits::static_cast_from(this->index.front())) ;   }

   //! <b>Effects</b>: Returns an iterator to the end of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE iterator end() BOOST_NOEXCEPT_OR_NOTHROW
   {  return iterator(this->priv_get_end_node());  }

   //! <b>Effects</b>: Returns a const_iterator to the end of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_iterator end() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_iterator(this->priv_get_end_node());  }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the beginning
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE reverse_iterator rbegin() BOOST_NOEXCEPT_OR_NOTHROW
   {  return reverse_iterator(this->end());  }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator rbegin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_reverse_iterator(this->end());  }

   //! <b>Effects</b>: Returns a reverse_iterator pointing to the end
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE reverse_iterator rend() BOOST_NOEXCEPT_OR_NOTHROW
   {  return reverse_iterator(this->begin());   }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator rend() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return const_reverse_iterator(this->begin());   }

   //! <b>Effects</b>: Returns a const_iterator to the first element contained in the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_iterator cbegin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->begin();   }

   //! <b>Effects</b>: Returns a const_iterator to the end of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_iterator cend() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->end();  }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the beginning
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator crbegin() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->rbegin();  }

   //! <b>Effects</b>: Returns a const_reverse_iterator pointing to the end
   //! of the reversed stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_reverse_iterator crend()const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->rend(); }

   //////////////////////////////////////////////
   //
   //                capacity
   //
   //////////////////////////////////////////////

   //! <b>Effects</b>: Returns true if the stable_vector contains no elements.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE bool empty() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->index.size() <= ExtraPointers;  }

   //! <b>Effects</b>: Returns the number of the elements contained in the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE size_type size() const BOOST_NOEXCEPT_OR_NOTHROW
   {
      const size_type index_size = this->index.size();
      return (index_size - ExtraPointers) & (size_type(0u) -size_type(index_size != 0));
   }

   //! <b>Effects</b>: Returns the largest possible size of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->index.max_size() - ExtraPointers;  }

   //! <b>Effects</b>: Inserts or erases elements at the end such that
   //!   the size becomes n. New elements are value initialized.
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's value initialization throws.
   //!
   //! <b>Complexity</b>: Linear to the difference between size() and new_size.
   void resize(size_type n)
   {
      typedef value_init_construct_iterator<value_type, difference_type> value_init_iterator;
      STABLE_VECTOR_CHECK_INVARIANT;
      if(n > this->size())
         this->insert(this->cend(), value_init_iterator(n - this->size()), value_init_iterator());
      else if(n < this->size())
         this->erase(this->cbegin() + n, this->cend());
   }

   //! <b>Effects</b>: Inserts or erases elements at the end such that
   //!   the size becomes n. New elements are default initialized.
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's default initialization throws.
   //!
   //! <b>Complexity</b>: Linear to the difference between size() and new_size.
   //!
   //! <b>Note</b>: Non-standard extension
   void resize(size_type n, default_init_t)
   {
      typedef default_init_construct_iterator<value_type, difference_type> default_init_iterator;
      STABLE_VECTOR_CHECK_INVARIANT;
      if(n > this->size())
         this->insert(this->cend(), default_init_iterator(n - this->size()), default_init_iterator());
      else if(n < this->size())
         this->erase(this->cbegin() + n, this->cend());
   }

   //! <b>Effects</b>: Inserts or erases elements at the end such that
   //!   the size becomes n. New elements are copy constructed from x.
   //!
   //! <b>Throws</b>: If memory allocation throws, or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to the difference between size() and new_size.
   void resize(size_type n, const T& t)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      if(n > this->size())
         this->insert(this->cend(), n - this->size(), t);
      else if(n < this->size())
         this->erase(this->cbegin() + n, this->cend());
   }

   //! <b>Effects</b>: Number of elements for which memory has been allocated.
   //!   capacity() is always greater than or equal to size().
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   size_type capacity() const BOOST_NOEXCEPT_OR_NOTHROW
   {
      const size_type index_size             = this->index.size();
      BOOST_ASSERT(!index_size || index_size >= ExtraPointers);
      const size_type node_extra_capacity   = this->internal_data.pool_size;
      //Pool count must be less than index capacity, as index is a vector
      BOOST_ASSERT(node_extra_capacity <= (this->index.capacity()- index_size));
      const size_type index_offset =
         (node_extra_capacity - ExtraPointers) & (size_type(0u) - size_type(index_size != 0));
      return index_size + index_offset;
   }

   //! <b>Effects</b>: If n is less than or equal to capacity(), this call has no
   //!   effect. Otherwise, it is a request for allocation of additional memory.
   //!   If the request is successful, then capacity() is greater than or equal to
   //!   n; otherwise, capacity() is unchanged. In either case, size() is unchanged.
   //!
   //! <b>Throws</b>: If memory allocation allocation throws.
   void reserve(size_type n)
   {
      STABLE_VECTOR_CHECK_INVARIANT;
      if(n > this->max_size()){
         throw_length_error("stable_vector::reserve max_size() exceeded");
      }

      size_type sz         = this->size();
      size_type old_capacity = this->capacity();
      if(n > old_capacity){
         index_traits_type::initialize_end_node(this->index, this->internal_data.end_node, n);
         const void * old_ptr = &index[0];
         this->index.reserve(n + ExtraPointers);
         bool realloced = &index[0] != old_ptr;
         //Fix the pointers for the newly allocated buffer
         if(realloced){
            index_traits_type::fix_up_pointers_from(this->index, this->index.begin());
         }
         //Now fill pool if data is not enough
         if((n - sz) > this->internal_data.pool_size){
            this->priv_increase_pool((n - sz) - this->internal_data.pool_size);
         }
      }
   }

   //! <b>Effects</b>: Tries to deallocate the excess of memory created
   //!   with previous allocations. The size of the stable_vector is unchanged
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Linear to size().
   void shrink_to_fit()
   {
      if(this->capacity()){
         //First empty allocated node pool
         this->priv_clear_pool();
         //If empty completely destroy the index, let's recover default-constructed state
         if(this->empty()){
            this->index.clear();
            this->index.shrink_to_fit();
            this->internal_data.end_node.up = node_base_ptr_ptr();
         }
         //Otherwise, try to shrink-to-fit the index and readjust pointers if necessary
         else{
            const void* old_ptr = &index[0];
            this->index.shrink_to_fit();
            bool realloced = &index[0] != old_ptr;
            //Fix the pointers for the newly allocated buffer
            if(realloced){
               index_traits_type::fix_up_pointers_from(this->index, this->index.begin());
            }
         }
      }
   }

   //////////////////////////////////////////////
   //
   //               element access
   //
   //////////////////////////////////////////////

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a reference to the first
   //!   element of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE reference front() BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      return static_cast<node_reference>(*this->index.front()).get_data();
   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a const reference to the first
   //!   element of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_reference front() const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      return static_cast<const_node_reference>(*this->index.front()).get_data();
   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a reference to the last
   //!   element of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE reference back() BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      return static_cast<node_reference>(*this->index[this->size()-1u]).get_data();
   }

   //! <b>Requires</b>: !empty()
   //!
   //! <b>Effects</b>: Returns a const reference to the last
   //!   element of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   const_reference back() const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      return static_cast<const_node_reference>(*this->index[this->size()-1u]).get_data();
   }

   //! <b>Requires</b>: size() > n.
   //!
   //! <b>Effects</b>: Returns a reference to the nth element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE reference operator[](size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->size() > n);
      return static_cast<node_reference>(*this->index[n]).get_data();
   }

   //! <b>Requires</b>: size() > n.
   //!
   //! <b>Effects</b>: Returns a const reference to the nth element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE const_reference operator[](size_type n) const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->size() > n);
      return static_cast<const_node_reference>(*this->index[n]).get_data();
   }

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
   BOOST_CONTAINER_FORCEINLINE iterator nth(size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->size() >= n);
      return (this->index.empty()) ? this->end() : iterator(node_ptr_traits::static_cast_from(this->index[n]));
   }

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
   BOOST_CONTAINER_FORCEINLINE const_iterator nth(size_type n) const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->size() >= n);
      return (this->index.empty()) ? this->cend() : iterator(node_ptr_traits::static_cast_from(this->index[n]));
   }

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
   BOOST_CONTAINER_FORCEINLINE size_type index_of(iterator p) BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->priv_index_of(p.node_pointer());  }

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
   BOOST_CONTAINER_FORCEINLINE size_type index_of(const_iterator p) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return this->priv_index_of(p.node_pointer());  }

   //! <b>Requires</b>: size() > n.
   //!
   //! <b>Effects</b>: Returns a reference to the nth element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: std::range_error if n >= size()
   //!
   //! <b>Complexity</b>: Constant.
   reference at(size_type n)
   {
      if(n >= this->size()){
         throw_out_of_range("vector::at invalid subscript");
      }
      return operator[](n);
   }

   //! <b>Requires</b>: size() > n.
   //!
   //! <b>Effects</b>: Returns a const reference to the nth element
   //!   from the beginning of the container.
   //!
   //! <b>Throws</b>: std::range_error if n >= size()
   //!
   //! <b>Complexity</b>: Constant.
   const_reference at(size_type n)const
   {
      if(n >= this->size()){
         throw_out_of_range("vector::at invalid subscript");
      }
      return operator[](n);
   }

   //////////////////////////////////////////////
   //
   //                modifiers
   //
   //////////////////////////////////////////////

   #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) || defined(BOOST_CONTAINER_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... in the end of the stable_vector.
   //!
   //! <b>Returns</b>: A reference to the created object.
   //!
   //! <b>Throws</b>: If memory allocation throws or the in-place constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   template<class ...Args>
   reference emplace_back(Args &&...args)
   {
      typedef emplace_functor<Args...>         EmplaceFunctor;
      typedef emplace_iterator<value_type, EmplaceFunctor, difference_type> EmplaceIterator;
      EmplaceFunctor &&ef = EmplaceFunctor(boost::forward<Args>(args)...);
      return *this->insert(this->cend(), EmplaceIterator(ef), EmplaceIterator());
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Inserts an object of type T constructed with
   //!   std::forward<Args>(args)... before p
   //!
   //! <b>Throws</b>: If memory allocation throws or the in-place constructor throws.
   //!
   //! <b>Complexity</b>: If p is end(), amortized constant time
   //!   Linear time otherwise.
   template<class ...Args>
   iterator emplace(const_iterator p, Args && ...args)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(p));
      size_type pos_n = p - cbegin();
      typedef emplace_functor<Args...>         EmplaceFunctor;
      typedef emplace_iterator<value_type, EmplaceFunctor, difference_type> EmplaceIterator;
      EmplaceFunctor &&ef = EmplaceFunctor(boost::forward<Args>(args)...);
      this->insert(p, EmplaceIterator(ef), EmplaceIterator());
      return iterator(this->begin() + pos_n);
   }

   #else

   #define BOOST_CONTAINER_STABLE_VECTOR_EMPLACE_CODE(N) \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   reference emplace_back(BOOST_MOVE_UREF##N)\
   {\
      typedef emplace_functor##N\
         BOOST_MOVE_LT##N BOOST_MOVE_TARG##N BOOST_MOVE_GT##N EmplaceFunctor;\
      typedef emplace_iterator<value_type, EmplaceFunctor, difference_type>  EmplaceIterator;\
      EmplaceFunctor ef BOOST_MOVE_LP##N BOOST_MOVE_FWD##N BOOST_MOVE_RP##N;\
      return *this->insert(this->cend() , EmplaceIterator(ef), EmplaceIterator());\
   }\
   \
   BOOST_MOVE_TMPL_LT##N BOOST_MOVE_CLASS##N BOOST_MOVE_GT##N \
   iterator emplace(const_iterator p BOOST_MOVE_I##N BOOST_MOVE_UREF##N)\
   {\
      BOOST_ASSERT(this->priv_in_range_or_end(p));\
      typedef emplace_functor##N\
         BOOST_MOVE_LT##N BOOST_MOVE_TARG##N BOOST_MOVE_GT##N EmplaceFunctor;\
      typedef emplace_iterator<value_type, EmplaceFunctor, difference_type>  EmplaceIterator;\
      EmplaceFunctor ef BOOST_MOVE_LP##N BOOST_MOVE_FWD##N BOOST_MOVE_RP##N;\
      const size_type pos_n = p - this->cbegin();\
      this->insert(p, EmplaceIterator(ef), EmplaceIterator());\
      return this->begin() += pos_n;\
   }\
   //
   BOOST_MOVE_ITERATE_0TO9(BOOST_CONTAINER_STABLE_VECTOR_EMPLACE_CODE)
   #undef BOOST_CONTAINER_STABLE_VECTOR_EMPLACE_CODE

   #endif   // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Effects</b>: Inserts a copy of x at the end of the stable_vector.
   //!
   //! <b>Throws</b>: If memory allocation throws or
   //!   T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void push_back(const T &x);

   //! <b>Effects</b>: Constructs a new element in the end of the stable_vector
   //!   and moves the resources of x to this new element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: Amortized constant time.
   void push_back(T &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH(push_back, T, void, priv_push_back)
   #endif

   #if defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of x before p.
   //!
   //! <b>Returns</b>: An iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws or x's copy constructor throws.
   //!
   //! <b>Complexity</b>: If p is end(), amortized constant time
   //!   Linear time otherwise.
   iterator insert(const_iterator p, const T &x);

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a new element before p with x's resources.
   //!
   //! <b>Returns</b>: an iterator to the inserted element.
   //!
   //! <b>Throws</b>: If memory allocation throws.
   //!
   //! <b>Complexity</b>: If p is end(), amortized constant time
   //!   Linear time otherwise.
   iterator insert(const_iterator p, T &&x);
   #else
   BOOST_MOVE_CONVERSION_AWARE_CATCH_1ARG(insert, T, iterator, priv_insert, const_iterator, const_iterator)
   #endif

   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert n copies of x before p.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or p if n is 0.
   //!
   //! <b>Throws</b>: If memory allocation throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to n.
   iterator insert(const_iterator p, size_type n, const T& t)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(p));
      STABLE_VECTOR_CHECK_INVARIANT;
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
      return this->insert(p, cvalue_iterator(t, n), cvalue_iterator());
   }

   //! <b>Requires</b>: p must be a valid iterator of *this.
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   //! <b>Requires</b>: p must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of the [il.begin(), il.end()) range before p.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or p if first == last.
   //!
   //! <b>Complexity</b>: Linear to distance [il.begin(), il.end()).
   BOOST_CONTAINER_FORCEINLINE iterator insert(const_iterator p, std::initializer_list<value_type> il)
   {
      //Position checks done by insert()
      STABLE_VECTOR_CHECK_INVARIANT;
      return insert(p, il.begin(), il.end());
   }
#endif

   //! <b>Requires</b>: pos must be a valid iterator of *this.
   //!
   //! <b>Effects</b>: Insert a copy of the [first, last) range before p.
   //!
   //! <b>Returns</b>: an iterator to the first inserted element or p if first == last.
   //!
   //! <b>Throws</b>: If memory allocation throws, T's constructor from a
   //!   dereferenced InpIt throws or T's copy constructor throws.
   //!
   //! <b>Complexity</b>: Linear to distance [first, last).
   template <class InputIterator>
   iterator insert(const_iterator p, InputIterator first, InputIterator last
         #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
         //Put this as argument instead of the return type as old GCC's like 3.4
         //detect this and the next disable_if_or as overloads
         ,  typename dtl::disable_if_or
               < void
               , dtl::is_convertible<InputIterator, size_type>
               , dtl::is_not_input_iterator<InputIterator>
               >::type* = 0
         #endif
         )
   {
      BOOST_ASSERT(this->priv_in_range_or_end(p));
      STABLE_VECTOR_CHECK_INVARIANT;
      const size_type pos_n = p - this->cbegin();
      for(; first != last; ++first){
         this->emplace(p, *first);
      }
      return this->begin() + pos_n;
   }

   #if !defined(BOOST_CONTAINER_DOXYGEN_INVOKED)
   template <class FwdIt>
   typename dtl::disable_if_or
      < iterator
      , dtl::is_convertible<FwdIt, size_type>
      , dtl::is_input_iterator<FwdIt>
      >::type
      insert(const_iterator p, FwdIt first, FwdIt last)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(p));
      const size_type num_new = static_cast<size_type>(boost::container::iterator_distance(first, last));
      const size_type idx     = static_cast<size_type>(p - this->cbegin());
      if(num_new){
         //Fills the node pool and inserts num_new null pointers in idx.
         //If a new buffer was needed fixes up pointers up to idx so
         //past-new nodes are not aligned until the end of this function
         //or in a rollback in case of exception
         index_iterator it_past_newly_constructed(this->priv_insert_forward_non_templated(idx, num_new));
         const index_iterator it_past_new(it_past_newly_constructed + num_new);
         {
            //Prepare rollback
            insert_rollback rollback(*this, it_past_newly_constructed, it_past_new);
            while(first != last){
               const node_ptr n = this->priv_get_from_pool();
               BOOST_ASSERT(!!n);
               //Put it in the index so rollback can return it in pool if construct_in_place throws
               *it_past_newly_constructed = n;
               //Constructs and fixes up pointers This can throw
               this->priv_build_node_from_it(n, it_past_newly_constructed, first);
               ++first;
               ++it_past_newly_constructed;
            }
            //rollback.~insert_rollback() called in case of exception
         }
         //Fix up pointers for past-new nodes (new nodes were fixed during construction) and
         //nodes before insertion p in priv_insert_forward_non_templated(...)
         index_traits_type::fix_up_pointers_from(this->index, it_past_newly_constructed);
      }
      return this->begin() + idx;
   }
   #endif

   //! <b>Effects</b>: Removes the last element from the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant time.
   BOOST_CONTAINER_FORCEINLINE void pop_back() BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(!this->empty());
      this->erase(--this->cend());
   }

   //! <b>Effects</b>: Erases the element at p.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the elements between p and the
   //!   last element. Constant if p is the last element.
   BOOST_CONTAINER_FORCEINLINE iterator erase(const_iterator p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(this->priv_in_range(p));
      STABLE_VECTOR_CHECK_INVARIANT;
      const size_type d = p - this->cbegin();
      index_iterator it = this->index.begin() + d;
      this->priv_delete_node(p.node_pointer());
      it = this->index.erase(it);
      index_traits_type::fix_up_pointers_from(this->index, it);
      return iterator(node_ptr_traits::static_cast_from(*it));
   }

   //! <b>Effects</b>: Erases the elements pointed by [first, last).
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the distance between first and last
   //!   plus linear to the elements between p and the last element.
   iterator erase(const_iterator first, const_iterator last) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_ASSERT(first == last ||
         (first < last && this->priv_in_range(first) && this->priv_in_range_or_end(last)));
      STABLE_VECTOR_CHECK_INVARIANT;
      const const_iterator cbeg(this->cbegin());
      const size_type d1 = static_cast<size_type>(first - cbeg),
                      d2 = static_cast<size_type>(last  - cbeg);
      size_type d_dif = d2 - d1;
      if(d_dif){
         multiallocation_chain holder;
         const index_iterator it1(this->index.begin() + d1);
         const index_iterator it2(it1 + d_dif);
         index_iterator it(it1);
         while(d_dif--){
            node_base_ptr &nb = *it;
            ++it;
            node_type &n = *node_ptr_traits::static_cast_from(nb);
            this->priv_destroy_node(n);
            holder.push_back(node_ptr_traits::pointer_to(n));
         }
         this->priv_put_in_pool(holder);
         const index_iterator e = this->index.erase(it1, it2);
         index_traits_type::fix_up_pointers_from(this->index, e);
      }
      return iterator(last.node_pointer());
   }

   //! <b>Effects</b>: Swaps the contents of *this and x.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Constant.
   void swap(stable_vector & x)
      BOOST_NOEXCEPT_IF( allocator_traits_type::propagate_on_container_swap::value
                                || allocator_traits_type::is_always_equal::value)
   {
      BOOST_ASSERT(allocator_traits_type::propagate_on_container_swap::value ||
                   allocator_traits_type::is_always_equal::value ||
                   this->get_stored_allocator() == x.get_stored_allocator());
      STABLE_VECTOR_CHECK_INVARIANT;
      dtl::bool_<allocator_traits_type::propagate_on_container_swap::value> flag;
      dtl::swap_alloc(this->priv_node_alloc(), x.priv_node_alloc(), flag);
      //vector's allocator is swapped here
      this->index.swap(x.index);
      this->priv_swap_members(x);
   }

   //! <b>Effects</b>: Erases all the elements of the stable_vector.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the stable_vector.
   BOOST_CONTAINER_FORCEINLINE void clear() BOOST_NOEXCEPT_OR_NOTHROW
   {   this->erase(this->cbegin(),this->cend()); }

   //! <b>Effects</b>: Returns true if x and y are equal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_FORCEINLINE friend bool operator==(const stable_vector& x, const stable_vector& y)
   {  return x.size() == y.size() && ::boost::container::algo_equal(x.begin(), x.end(), y.begin());  }

   //! <b>Effects</b>: Returns true if x and y are unequal
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_FORCEINLINE friend bool operator!=(const stable_vector& x, const stable_vector& y)
   {  return !(x == y); }

   //! <b>Effects</b>: Returns true if x is less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_FORCEINLINE friend bool operator<(const stable_vector& x, const stable_vector& y)
   {  return ::boost::container::algo_lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());  }

   //! <b>Effects</b>: Returns true if x is greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_FORCEINLINE friend bool operator>(const stable_vector& x, const stable_vector& y)
   {  return y < x;  }

   //! <b>Effects</b>: Returns true if x is equal or less than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_FORCEINLINE friend bool operator<=(const stable_vector& x, const stable_vector& y)
   {  return !(y < x);  }

   //! <b>Effects</b>: Returns true if x is equal or greater than y
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the container.
   BOOST_CONTAINER_FORCEINLINE friend bool operator>=(const stable_vector& x, const stable_vector& y)
   {  return !(x < y);  }

   //! <b>Effects</b>: x.swap(y)
   //!
   //! <b>Complexity</b>: Constant.
   BOOST_CONTAINER_FORCEINLINE friend void swap(stable_vector& x, stable_vector& y)
   {  x.swap(y);  }

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:

   bool priv_in_range(const_iterator pos) const
   {
      return (this->begin() <= pos) && (pos < this->end());
   }

   BOOST_CONTAINER_FORCEINLINE bool priv_in_range_or_end(const_iterator pos) const
   {
      return (this->begin() <= pos) && (pos <= this->end());
   }

   BOOST_CONTAINER_FORCEINLINE size_type priv_index_of(node_ptr p) const
   {
      //Check range
      BOOST_ASSERT(this->index.empty() || (this->index.data() <= p->up));
      BOOST_ASSERT(this->index.empty() || p->up <= (this->index.data() + this->index.size()));
      return this->index.empty() ? 0 : p->up - this->index.data();
   }

   class insert_rollback
   {
      public:

      insert_rollback(stable_vector &sv, index_iterator &it_past_constructed, const index_iterator &it_past_new)
         : m_sv(sv), m_it_past_constructed(it_past_constructed), m_it_past_new(it_past_new)
      {}

      ~insert_rollback()
      {
         if(m_it_past_constructed != m_it_past_new){
            m_sv.priv_put_in_pool(node_ptr_traits::static_cast_from(*m_it_past_constructed));
            index_iterator e = m_sv.index.erase(m_it_past_constructed, m_it_past_new);
            index_traits_type::fix_up_pointers_from(m_sv.index, e);
         }
      }

      private:
      stable_vector &m_sv;
      index_iterator &m_it_past_constructed;
      const index_iterator &m_it_past_new;
   };

   class push_back_rollback
   {
      public:
      BOOST_CONTAINER_FORCEINLINE push_back_rollback(stable_vector &sv, const node_ptr &p)
         : m_sv(sv), m_p(p)
      {}

      BOOST_CONTAINER_FORCEINLINE ~push_back_rollback()
      {
         if(m_p){
            m_sv.priv_put_in_pool(m_p);
         }
      }

      BOOST_CONTAINER_FORCEINLINE void release()
      {  m_p = node_ptr();  }

      private:
      stable_vector &m_sv;
      node_ptr m_p;
   };

   index_iterator priv_insert_forward_non_templated(size_type idx, size_type num_new)
   {
      index_traits_type::initialize_end_node(this->index, this->internal_data.end_node, num_new);

      //Now try to fill the pool with new data
      if(this->internal_data.pool_size < num_new){
         this->priv_increase_pool(num_new - this->internal_data.pool_size);
      }

      //Now try to make room in the vector
      const node_base_ptr_ptr old_buffer = this->index.data();
      this->index.insert(this->index.begin() + idx, num_new, node_ptr());
      bool new_buffer = this->index.data() != old_buffer;

      //Fix the pointers for the newly allocated buffer
      const index_iterator index_beg = this->index.begin();
      if(new_buffer){
         index_traits_type::fix_up_pointers(index_beg, index_beg + idx);
      }
      return index_beg + idx;
   }

   BOOST_CONTAINER_FORCEINLINE bool priv_capacity_bigger_than_size() const
   {
      return this->index.capacity() > this->index.size() &&
             this->internal_data.pool_size > 0;
   }

   template <class U>
   void priv_push_back(BOOST_MOVE_CATCH_FWD(U) x)
   {
      if(BOOST_LIKELY(this->priv_capacity_bigger_than_size())){
         //Enough memory in the pool and in the index
         const node_ptr p = this->priv_get_from_pool();
         BOOST_ASSERT(!!p);
         {
            push_back_rollback rollback(*this, p);
            //This might throw
            this->priv_build_node_from_convertible(p, ::boost::forward<U>(x));
            rollback.release();
         }
         //This can't throw as there is room for a new elements in the index
         index_iterator new_index = this->index.insert(this->index.end() - ExtraPointers, p);
         index_traits_type::fix_up_pointers_from(this->index, new_index);
      }
      else{
         this->insert(this->cend(), ::boost::forward<U>(x));
      }
   }

   iterator priv_insert(const_iterator p, const value_type &t)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(p));
      typedef constant_iterator<value_type, difference_type> cvalue_iterator;
      return this->insert(p, cvalue_iterator(t, 1), cvalue_iterator());
   }

   iterator priv_insert(const_iterator p, BOOST_RV_REF(T) x)
   {
      BOOST_ASSERT(this->priv_in_range_or_end(p));
      typedef repeat_iterator<T, difference_type>  repeat_it;
      typedef boost::move_iterator<repeat_it>      repeat_move_it;
      //Just call more general insert(p, size, value) and return iterator
      return this->insert(p, repeat_move_it(repeat_it(x, 1)), repeat_move_it(repeat_it()));
   }

   void priv_clear_pool()
   {
      if(!this->index.empty() && this->index.back()){
         node_base_ptr &pool_first_ref = *(this->index.end() - 2);
         node_base_ptr &pool_last_ref  = this->index.back();

         multiallocation_chain holder;
         holder.incorporate_after( holder.before_begin()
                                 , node_ptr_traits::static_cast_from(pool_first_ref)
                                 , node_ptr_traits::static_cast_from(pool_last_ref)
                                 , internal_data.pool_size);
         this->deallocate_individual(holder);
         pool_first_ref = pool_last_ref = 0;
         this->internal_data.pool_size = 0;
      }
   }

   void priv_increase_pool(size_type n)
   {
      node_base_ptr &pool_first_ref = *(this->index.end() - 2);
      node_base_ptr &pool_last_ref  = this->index.back();
      multiallocation_chain holder;
      holder.incorporate_after( holder.before_begin()
                              , node_ptr_traits::static_cast_from(pool_first_ref)
                              , node_ptr_traits::static_cast_from(pool_last_ref)
                              , internal_data.pool_size);
      multiallocation_chain m;
      this->allocate_individual(n, m);
      holder.splice_after(holder.before_begin(), m, m.before_begin(), m.last(), n);
      this->internal_data.pool_size += n;
      std::pair<node_ptr, node_ptr> data(holder.extract_data());
      pool_first_ref = data.first;
      pool_last_ref = data.second;
   }

   void priv_put_in_pool(const node_ptr &p)
   {
      node_base_ptr &pool_first_ref = *(this->index.end()-2);
      node_base_ptr &pool_last_ref  = this->index.back();
      multiallocation_chain holder;
      holder.incorporate_after( holder.before_begin()
                              , node_ptr_traits::static_cast_from(pool_first_ref)
                              , node_ptr_traits::static_cast_from(pool_last_ref)
                              , internal_data.pool_size);
      holder.push_front(p);
      ++this->internal_data.pool_size;
      std::pair<node_ptr, node_ptr> ret(holder.extract_data());
      pool_first_ref = ret.first;
      pool_last_ref  = ret.second;
   }

   void priv_put_in_pool(multiallocation_chain &ch)
   {
      node_base_ptr &pool_first_ref = *(this->index.end()-(ExtraPointers-1));
      node_base_ptr &pool_last_ref  = this->index.back();
      ch.incorporate_after( ch.before_begin()
                          , node_ptr_traits::static_cast_from(pool_first_ref)
                          , node_ptr_traits::static_cast_from(pool_last_ref)
                          , internal_data.pool_size);
      this->internal_data.pool_size = ch.size();
      const std::pair<node_ptr, node_ptr> ret(ch.extract_data());
      pool_first_ref = ret.first;
      pool_last_ref  = ret.second;
   }

   node_ptr priv_get_from_pool()
   {
      //Precondition: index is not empty
      BOOST_ASSERT(!this->index.empty());
      node_base_ptr &pool_first_ref = *(this->index.end() - (ExtraPointers-1));
      node_base_ptr &pool_last_ref  = this->index.back();
      multiallocation_chain holder;
      holder.incorporate_after( holder.before_begin()
                              , node_ptr_traits::static_cast_from(pool_first_ref)
                              , node_ptr_traits::static_cast_from(pool_last_ref)
                              , internal_data.pool_size);
      node_ptr ret = holder.pop_front();
      --this->internal_data.pool_size;
      if(!internal_data.pool_size){
         pool_first_ref = pool_last_ref = node_ptr();
      }
      else{
         const std::pair<node_ptr, node_ptr> data(holder.extract_data());
         pool_first_ref = data.first;
         pool_last_ref  = data.second;
      }
      return ret;
   }

   BOOST_CONTAINER_FORCEINLINE node_base_ptr priv_get_end_node() const
   {  return node_base_ptr_traits::pointer_to(const_cast<node_base_type&>(this->internal_data.end_node));  }

   BOOST_CONTAINER_FORCEINLINE void priv_destroy_node(const node_type &n)
   {
      allocator_traits<node_allocator_type>::
         destroy(this->priv_node_alloc(), &n);
   }

   BOOST_CONTAINER_FORCEINLINE void priv_delete_node(const node_ptr &n)
   {
      this->priv_destroy_node(*n);
      this->priv_put_in_pool(n);
   }

   template<class Iterator>
   void priv_build_node_from_it(const node_ptr &p, const index_iterator &up_index, const Iterator &it)
   {
      node_type *praw = ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t())
         node_type(index_traits_type::ptr_to_node_base_ptr(*up_index));
      BOOST_TRY{
         //This can throw
         boost::container::construct_in_place
            ( this->priv_node_alloc()
            , praw->get_data_ptr()
            , it);
      }
      BOOST_CATCH(...) {
         praw->destroy_header();
         this->priv_node_alloc().deallocate(p, 1);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }

   template<class ValueConvertible>
   void priv_build_node_from_convertible(const node_ptr &p, BOOST_FWD_REF(ValueConvertible) value_convertible)
   {
      node_type *praw = ::new(boost::movelib::iterator_to_raw_pointer(p), boost_container_new_t()) node_type;
      BOOST_TRY{
         //This can throw
         boost::container::allocator_traits<node_allocator_type>::construct
            ( this->priv_node_alloc()
            , p->get_data_ptr()
            , ::boost::forward<ValueConvertible>(value_convertible));
      }
      BOOST_CATCH(...) {
         praw->destroy_header();
         this->priv_node_alloc().deallocate(p, 1);
         BOOST_RETHROW
      }
      BOOST_CATCH_END
   }

   void priv_swap_members(stable_vector &x)
   {
      boost::adl_move_swap(this->internal_data.pool_size, x.internal_data.pool_size);
      index_traits_type::readjust_end_node(this->index, this->internal_data.end_node);
      index_traits_type::readjust_end_node(x.index, x.internal_data.end_node);
   }

   #if defined(STABLE_VECTOR_ENABLE_INVARIANT_CHECKING)
   bool priv_invariant()const
   {
      index_type & index_ref =  const_cast<index_type&>(this->index);

      const size_type index_size = this->index.size();
      if(!index_size)
         return !this->capacity() && !this->size();

      if(index_size < ExtraPointers)
         return false;

      const size_type bucket_extra_capacity = this->index.capacity()- index_size;
      const size_type node_extra_capacity   = this->internal_data.pool_size;
      if(bucket_extra_capacity < node_extra_capacity){
         return false;
      }

      if(this->priv_get_end_node() != *(index.end() - ExtraPointers)){
         return false;
      }

      if(!index_traits_type::invariants(index_ref)){
         return false;
      }

      size_type n = this->capacity() - this->size();
      node_base_ptr &pool_first_ref = *(index_ref.end() - (ExtraPointers-1));
      node_base_ptr &pool_last_ref  = index_ref.back();
      multiallocation_chain holder;
      holder.incorporate_after( holder.before_begin()
                              , node_ptr_traits::static_cast_from(pool_first_ref)
                              , node_ptr_traits::static_cast_from(pool_last_ref)
                              , internal_data.pool_size);
      typename multiallocation_chain::iterator beg(holder.begin()), end(holder.end());
      size_type num_pool = 0;
      while(beg != end){
         ++num_pool;
         ++beg;
      }
      return n >= num_pool && num_pool == internal_data.pool_size;
   }

   class invariant_checker
   {
      invariant_checker(const invariant_checker &);
      invariant_checker & operator=(const invariant_checker &);
      const stable_vector* p;

      public:
      invariant_checker(const stable_vector& v):p(&v){}
      ~invariant_checker(){BOOST_ASSERT(p->priv_invariant());}
      void touch(){}
   };
   #endif

   class ebo_holder
      : public node_allocator_type
   {
      private:
      BOOST_MOVABLE_BUT_NOT_COPYABLE(ebo_holder)

      public:
      template<class AllocatorRLValue>
      explicit ebo_holder(BOOST_FWD_REF(AllocatorRLValue) a)
         : node_allocator_type(boost::forward<AllocatorRLValue>(a))
         , pool_size(0)
         , end_node()
      {}

      ebo_holder()
         : node_allocator_type()
         , pool_size(0)
         , end_node()
      {}

      size_type pool_size;
      node_base_type end_node;
   } internal_data;

   node_allocator_type &priv_node_alloc()              { return internal_data;  }
   const node_allocator_type &priv_node_alloc() const  { return internal_data;  }

   index_type                           index;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template <typename InputIterator>
stable_vector(InputIterator, InputIterator) ->
   stable_vector<typename iterator_traits<InputIterator>::value_type>;

template <typename InputIterator, typename Allocator>
stable_vector(InputIterator, InputIterator, Allocator const&) ->
   stable_vector<typename iterator_traits<InputIterator>::value_type, Allocator>;

#endif

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

#undef STABLE_VECTOR_CHECK_INVARIANT

}  //namespace container {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class T, class Allocator>
struct has_trivial_destructor_after_move<boost::container::stable_vector<T, Allocator> >
{
   typedef typename boost::container::stable_vector<T, Allocator>::allocator_type allocator_type;
   typedef typename ::boost::container::allocator_traits<allocator_type>::pointer pointer;
   static const bool value = ::boost::has_trivial_destructor_after_move<allocator_type>::value &&
                             ::boost::has_trivial_destructor_after_move<pointer>::value;
};

namespace container {

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

}} //namespace boost{  namespace container {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_STABLE_VECTOR_HPP

/* stable_vector.hpp
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
*/