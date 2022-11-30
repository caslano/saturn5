//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_CONTAINER_SMALL_VECTOR_HPP
#define BOOST_CONTAINER_CONTAINER_SMALL_VECTOR_HPP

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
#include <boost/container/vector.hpp>
#include <boost/container/allocator_traits.hpp>
#include <boost/container/new_allocator.hpp> //new_allocator
// container/detail
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/version_type.hpp>

//move
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/iterator.hpp>

//move/detail
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/move/detail/fwd_macros.hpp>
#endif
#include <boost/move/detail/force_ptr.hpp>

//std
#if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
#include <initializer_list>   //for std::initializer_list
#endif

namespace boost {
namespace container {

namespace dtl{

template<class Options>
struct get_small_vector_opt
{
   typedef Options type;
};

template<>
struct get_small_vector_opt<void>
{
   typedef small_vector_null_opt type;
};

template<class Options>
struct get_vopt_from_svopt
   : get_small_vector_opt<Options>::type
{
   typedef typename get_small_vector_opt<Options>::type options_t;
   typedef vector_opt< typename options_t::growth_factor_type, void> type;
};

template<>
struct get_vopt_from_svopt<void>
{
   typedef void type;
};

template <class T, class SecondaryAllocator, class Options>
struct vector_for_small_vector
{
   typedef vector
      < T
      , small_vector_allocator
         < T 
         , typename allocator_traits<typename real_allocator<T, SecondaryAllocator>::type>::template portable_rebind_alloc<void>::type
         , Options>
      , typename dtl::get_vopt_from_svopt<Options>::type
      > type;
};

}  //namespace dtl

//! A non-standard allocator used to implement `small_vector`.
//! Users should never use it directly. It is described here
//! for documentation purposes.
//! 
//! This allocator inherits from a standard-conforming allocator
//! and forwards member functions to the standard allocator except
//! when internal storage is being used as memory source.
//!
//! This allocator is a "partially_propagable" allocator and
//! defines `is_partially_propagable` as true_type.
//! 
//! A partially propagable allocator means that not all storage
//! allocatod by an instance of `small_vector_allocator` can be
//! deallocated by another instance of this type, even if both
//! instances compare equal or an instance is propagated to another
//! one using the copy/move constructor or assignment. The storage that
//! can never be propagated is identified by `storage_is_unpropagable(p)`.
//!
//! `boost::container::vector` supports partially propagable allocators
//! fallbacking to deep copy/swap/move operations when internal storage
//! is being used to store vector elements.
//!
//! `small_vector_allocator` assumes that will be instantiated as
//! `boost::container::vector< T, small_vector_allocator<T, Allocator> >`
//! and internal storage can be obtained downcasting that vector
//! to `small_vector_base<T>`.
template<class T, class VoidAllocator BOOST_CONTAINER_DOCONLY(= void), class Options BOOST_CONTAINER_DOCONLY(= void)>
class small_vector_allocator
   : public allocator_traits<typename real_allocator<T, VoidAllocator>::type>::template portable_rebind_alloc<T>::type
{
   typedef unsigned int allocation_type;
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:

   typedef typename allocator_traits<typename real_allocator<T, VoidAllocator>::type>::template portable_rebind_alloc<T>::type allocator_type;

   BOOST_COPYABLE_AND_MOVABLE(small_vector_allocator)

   BOOST_CONTAINER_FORCEINLINE const allocator_type &as_base() const BOOST_NOEXCEPT
   {  return static_cast<const allocator_type&>(*this);  }

   BOOST_CONTAINER_FORCEINLINE allocator_type &as_base() BOOST_NOEXCEPT
   {  return static_cast<allocator_type&>(*this);  }

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef allocator_traits<allocator_type> allocator_traits_type;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   typedef typename allocator_traits<allocator_type>::value_type          value_type;
   typedef typename allocator_traits<allocator_type>::pointer             pointer;
   typedef typename allocator_traits<allocator_type>::const_pointer       const_pointer;
   typedef typename allocator_traits<allocator_type>::reference           reference;
   typedef typename allocator_traits<allocator_type>::const_reference     const_reference;
   typedef typename allocator_traits<allocator_type>::size_type           size_type;
   typedef typename allocator_traits<allocator_type>::difference_type     difference_type;
   typedef typename allocator_traits<allocator_type>::void_pointer        void_pointer;
   typedef typename allocator_traits<allocator_type>::const_void_pointer  const_void_pointer;

   typedef typename allocator_traits<allocator_type>::propagate_on_container_copy_assignment   propagate_on_container_copy_assignment;
   typedef typename allocator_traits<allocator_type>::propagate_on_container_move_assignment   propagate_on_container_move_assignment;
   typedef typename allocator_traits<allocator_type>::propagate_on_container_swap              propagate_on_container_swap;
   //! An integral constant with member `value == false`
   typedef BOOST_CONTAINER_IMPDEF(dtl::bool_<false>)                         is_always_equal;
   //! An integral constant with member `value == true`
   typedef BOOST_CONTAINER_IMPDEF(dtl::bool_<true>)                          is_partially_propagable;

   BOOST_CONTAINER_DOCIGN(typedef dtl::version_type<small_vector_allocator BOOST_CONTAINER_I 1>  version;)

   //!Obtains an small_vector_allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef typename allocator_traits<allocator_type>::template portable_rebind_alloc<T2>::type other;
   };

   BOOST_CONTAINER_FORCEINLINE small_vector_allocator() BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<allocator_type>::value)
   {}

   //!Constructor from other small_vector_allocator.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator
      (const small_vector_allocator &other) BOOST_NOEXCEPT_OR_NOTHROW
      : allocator_type(other.as_base())
   {}

   //!Move constructor from small_vector_allocator.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator
      (BOOST_RV_REF(small_vector_allocator) other) BOOST_NOEXCEPT_OR_NOTHROW
      : allocator_type(::boost::move(other.as_base()))
   {}

   //!Constructor from related small_vector_allocator.
   //!Never throws
   template<class U, class OtherVoidAllocator, class OtherOptions>
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator
      (const small_vector_allocator<U, OtherVoidAllocator, OtherOptions> &other) BOOST_NOEXCEPT_OR_NOTHROW
      : allocator_type(other.as_base())
   {}

   //!Move constructor from related small_vector_allocator.
   //!Never throws
   template<class U, class OtherVoidAllocator, class OtherOptions>
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator
      (BOOST_RV_REF(small_vector_allocator<U BOOST_MOVE_I OtherVoidAllocator BOOST_MOVE_I OtherOptions>) other) BOOST_NOEXCEPT_OR_NOTHROW
      : allocator_type(::boost::move(other.as_base()))
   {}

   //!Constructor from allocator_type.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE explicit small_vector_allocator
      (const allocator_type &other) BOOST_NOEXCEPT_OR_NOTHROW
      : allocator_type(other)
   {}

   //!Assignment from other small_vector_allocator.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator &
      operator=(BOOST_COPY_ASSIGN_REF(small_vector_allocator) other) BOOST_NOEXCEPT_OR_NOTHROW
   {  return static_cast<small_vector_allocator&>(this->allocator_type::operator=(other.as_base()));  }

   //!Move assignment from other small_vector_allocator.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator &
      operator=(BOOST_RV_REF(small_vector_allocator) other) BOOST_NOEXCEPT_OR_NOTHROW
   {  return static_cast<small_vector_allocator&>(this->allocator_type::operator=(::boost::move(other.as_base())));  }

   //!Assignment from related small_vector_allocator.
   //!Never throws
   template<class U, class OtherVoidAllocator>
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator &
      operator=(BOOST_COPY_ASSIGN_REF(small_vector_allocator<U BOOST_MOVE_I OtherVoidAllocator BOOST_MOVE_I Options>) other) BOOST_NOEXCEPT_OR_NOTHROW
   {  return static_cast<small_vector_allocator&>(this->allocator_type::operator=(other.as_base()));  }

   //!Move assignment from related small_vector_allocator.
   //!Never throws
   template<class U, class OtherVoidAllocator>
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator &
      operator=(BOOST_RV_REF(small_vector_allocator<U BOOST_MOVE_I OtherVoidAllocator BOOST_MOVE_I Options>) other) BOOST_NOEXCEPT_OR_NOTHROW
   {  return static_cast<small_vector_allocator&>(this->allocator_type::operator=(::boost::move(other.as_base())));  }

   //!Move assignment from allocator_type.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE small_vector_allocator &
      operator=(const allocator_type &other) BOOST_NOEXCEPT_OR_NOTHROW
   {  return static_cast<small_vector_allocator&>(this->allocator_type::operator=(other));  }

   //!Allocates storage from the standard-conforming allocator
   BOOST_CONTAINER_FORCEINLINE pointer allocate(size_type count, const_void_pointer hint = const_void_pointer())
   {  return allocator_traits_type::allocate(this->as_base(), count, hint);  }

   //!Deallocates previously allocated memory.
   //!Never throws
   void deallocate(pointer ptr, size_type n) BOOST_NOEXCEPT_OR_NOTHROW
   {
      if(!this->is_internal_storage(ptr))
         allocator_traits_type::deallocate(this->as_base(), ptr, n);
   }

   //!Returns the maximum number of elements that could be allocated.
   //!Never throws
   BOOST_CONTAINER_FORCEINLINE size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return allocator_traits_type::max_size(this->as_base());   }

   small_vector_allocator select_on_container_copy_construction() const
   {  return small_vector_allocator(allocator_traits_type::select_on_container_copy_construction(this->as_base())); }

   bool storage_is_unpropagable(pointer p) const
   {  return this->is_internal_storage(p) || allocator_traits_type::storage_is_unpropagable(this->as_base(), p);  }

   //!Swaps two allocators, does nothing
   //!because this small_vector_allocator is stateless
   BOOST_CONTAINER_FORCEINLINE friend void swap(small_vector_allocator &l, small_vector_allocator &r) BOOST_NOEXCEPT_OR_NOTHROW
   {  boost::adl_move_swap(l.as_base(), r.as_base());  }

   //!An small_vector_allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance (except for unpropagable storage)
   BOOST_CONTAINER_FORCEINLINE friend bool operator==(const small_vector_allocator &l, const small_vector_allocator &r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return allocator_traits_type::equal(l.as_base(), r.as_base());  }

   //!An small_vector_allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   BOOST_CONTAINER_FORCEINLINE friend bool operator!=(const small_vector_allocator &l, const small_vector_allocator &r) BOOST_NOEXCEPT_OR_NOTHROW
   {  return !(l == r);   }

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   /*
   //!An advanced function that offers in-place expansion shrink to fit and new allocation
   //!capabilities. Memory allocated with this function can only be deallocated with deallocate()
   //!or deallocate_many().
   //!This function is available only with Version == 2
   pointer allocation_command(allocation_type command,
                         size_type limit_size,
                         size_type &prefer_in_recvd_out_size,
                         pointer &reuse)
   {  return allocator_traits_type::allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse);  }

   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold.
   //!Memory must not have been allocated with
   //!allocate_one or allocate_individual.
   //!This function is available only with Version == 2
   size_type size(pointer p) const BOOST_NOEXCEPT_OR_NOTHROW
   {  return allocator_traits_type::size(p);  }
   */
   private:
   /*
   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws bad_alloc if there is no enough memory
   //!This function is available only with Version == 2
   using allocator_type::allocate_one;
   using allocator_type::allocate_individual;
   using allocator_type::deallocate_one;
   using allocator_type::deallocate_individual;
   using allocator_type::allocate_many;
   using allocator_type::deallocate_many;*/

   typedef vector_alloc_holder< small_vector_allocator, size_type >  vector_alloc_holder_t;
   typedef typename dtl::vector_for_small_vector<T, allocator_type, Options>::type vector_base;
   typedef small_vector_base<value_type, allocator_type, Options>    derived_type;

   BOOST_CONTAINER_FORCEINLINE bool is_internal_storage(const_pointer p) const
   {  return this->internal_storage() == p;  }

   BOOST_CONTAINER_FORCEINLINE
   const_pointer internal_storage() const
   {
      const vector_alloc_holder_t &v_holder = static_cast<const vector_alloc_holder_t &>(*this);
      const vector_base &v_base = *move_detail::force_ptr<const vector_base *>(&v_holder);
      const derived_type &d_base = static_cast<const derived_type &>(v_base);
      return d_base.internal_storage();
   }

   BOOST_CONTAINER_FORCEINLINE
   pointer internal_storage()
   {
      vector_alloc_holder_t &v_holder = static_cast<vector_alloc_holder_t &>(*this);
      vector_base &v_base = *move_detail::force_ptr<vector_base *>(&v_holder);
      derived_type &d_base = static_cast<derived_type &>(v_base);
      return d_base.internal_storage();
   }
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
};

//! This class consists of common code from all small_vector<T, N> types that don't depend on the
//! "N" template parameter. This class is non-copyable and non-destructible, so this class typically
//! used as reference argument to functions that read or write small vectors. Since `small_vector<T, N>`
//! derives from `small_vector_base<T>`, the conversion to `small_vector_base` is implicit
//! <pre>
//!
//! //Clients can pass any small_vector<Foo, N>.
//! void read_any_small_vector_of_foo(const small_vector_base<Foo> &in_parameter);
//!
//! void modify_any_small_vector_of_foo(small_vector_base<Foo> &in_out_parameter);
//!
//! void some_function()
//! {
//! 
//!    small_vector<Foo, 8> myvector;
//!
//!    read_any_small_vector_of_foo(myvector);   // Reads myvector
//!
//!    modify_any_small_vector_of_foo(myvector); // Modifies myvector
//! 
//! }
//! </pre>
//!
//! All `boost::container:vector` member functions are inherited. See `vector` documentation for details.
//!
template <class T, class SecondaryAllocator, class Options>
class small_vector_base
   : public dtl::vector_for_small_vector<T, SecondaryAllocator, Options>::type
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKEDVECTOR
   public:
   //Make it public as it will be inherited by small_vector and container
   //must have this public member
   typedef typename real_allocator<T, SecondaryAllocator>::type                  secondary_allocator_t;
   typedef typename allocator_traits<secondary_allocator_t>::
      template portable_rebind_alloc<void>::type                                 void_allocator_t;
   typedef typename dtl::get_small_vector_opt<Options>::type                     options_t;
   typedef typename dtl::vector_for_small_vector
      <T, SecondaryAllocator, Options>::type                                     base_type;
   typedef typename allocator_traits<secondary_allocator_t>::pointer             pointer;
   typedef typename allocator_traits<secondary_allocator_t>::const_pointer       const_pointer;
   typedef typename allocator_traits<secondary_allocator_t>::void_pointer        void_pointer;
   typedef typename allocator_traits<secondary_allocator_t>::const_void_pointer  const_void_pointer;
   typedef small_vector_allocator<T, void_allocator_t, Options>                  allocator_type;

   private: 
   BOOST_COPYABLE_AND_MOVABLE(small_vector_base)

   friend class small_vector_allocator<T, void_allocator_t, Options>;

   BOOST_CONTAINER_FORCEINLINE
   const_pointer internal_storage() const BOOST_NOEXCEPT_OR_NOTHROW
   {
      typedef typename boost::intrusive::pointer_traits<const_pointer>::template
         rebind_pointer<const unsigned char>::type const_char_pointer;
      const_void_pointer void_p = boost::intrusive::pointer_traits<const_char_pointer>::
         pointer_to(*m_storage_start.data);
      return boost::intrusive::pointer_traits<const_pointer>::static_cast_from(void_p);
   }

   BOOST_CONTAINER_FORCEINLINE
   pointer internal_storage() BOOST_NOEXCEPT_OR_NOTHROW
   {
      typedef typename boost::intrusive::pointer_traits<pointer>::template
         rebind_pointer<unsigned char>::type char_pointer;
      void_pointer void_p = boost::intrusive::pointer_traits<char_pointer>::
         pointer_to(*m_storage_start.data);
      return boost::intrusive::pointer_traits<pointer>::static_cast_from(void_p);
   }

         base_type &as_base()       { return static_cast<base_type&>(*this); }
   const base_type &as_base() const { return static_cast<const base_type&>(*this); }

   static const std::size_t final_alignment =
      options_t::inplace_alignment ? options_t::inplace_alignment : dtl::alignment_of<T>::value;
   public:

   typedef typename dtl::aligned_storage
      <sizeof(T), final_alignment>::type storage_type;

   protected:

   BOOST_CONTAINER_FORCEINLINE explicit small_vector_base(initial_capacity_t, std::size_t initial_capacity)
      : base_type(initial_capacity_t(), this->internal_storage(), initial_capacity)
   {}

   template<class AllocFwd>
   BOOST_CONTAINER_FORCEINLINE explicit small_vector_base(initial_capacity_t, std::size_t capacity, BOOST_FWD_REF(AllocFwd) a)
      : base_type(initial_capacity_t(), this->internal_storage(), capacity, ::boost::forward<AllocFwd>(a))
   {}

   //~small_vector_base(){}

   private:
   //The only member
   storage_type m_storage_start;

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   BOOST_CONTAINER_FORCEINLINE small_vector_base& operator=(BOOST_COPY_ASSIGN_REF(small_vector_base) other)
   {  return static_cast<small_vector_base&>(this->base_type::operator=(static_cast<base_type const&>(other)));  }

   BOOST_CONTAINER_FORCEINLINE small_vector_base& operator=(BOOST_RV_REF(small_vector_base) other)
   {  return static_cast<small_vector_base&>(this->base_type::operator=(BOOST_MOVE_BASE(base_type, other))); }

   BOOST_CONTAINER_FORCEINLINE void swap(small_vector_base &other)
   {  return this->base_type::swap(other);  }

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   protected:
   void move_construct_impl(base_type &x, const allocator_type &a)
   {
      if(base_type::is_propagable_from(x.get_stored_allocator(), x.data(), a, true)){
         this->steal_resources(x);
      }
      else{
         this->assign( boost::make_move_iterator(boost::movelib::iterator_to_raw_pointer(x.begin()))
                     , boost::make_move_iterator(boost::movelib::iterator_to_raw_pointer(x.end  ()))
                     );
         x.clear();
      }
   }
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
};

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

/////////////////////////////////////////////////////
//
//          small_vector_storage_calculator
//
/////////////////////////////////////////////////////
template<std::size_t Needed, std::size_t Hdr, std::size_t SSize, bool NeedsZero = (0u == Needed || Needed <= Hdr)>
struct small_vector_storage_calculator_helper
{
   static const std::size_t value = (Needed - Hdr - 1u)/SSize + 1u;
};

template<std::size_t Needed, std::size_t Hdr, std::size_t SSize>
struct small_vector_storage_calculator_helper<Needed, Hdr, SSize, true>
{
   static const std::size_t value = 0u;
};

template<class Storage, class Allocator, class T, std::size_t N, class Options>
struct small_vector_storage_calculator
{
   typedef small_vector_base<T, Allocator, Options> svh_type;
   typedef typename real_allocator<T, Allocator>::type value_allocator_t;
   typedef typename allocator_traits<value_allocator_t>::template portable_rebind_alloc<void>::type void_allocator_t;
   typedef typename dtl::vector_for_small_vector<T, void_allocator_t, Options>::type  svhb_type;

   static const std::size_t s_align = dtl::alignment_of<Storage>::value;
   static const std::size_t s_size = sizeof(Storage);
   static const std::size_t svh_sizeof = sizeof(svh_type);
   static const std::size_t svhb_sizeof = sizeof(svhb_type);
   static const std::size_t s_start = ((svhb_sizeof-1)/s_align+1)*s_align;
   static const std::size_t header_bytes = svh_sizeof-s_start;
   static const std::size_t needed_bytes = sizeof(T)*N;
   static const std::size_t needed_extra_storages =
      small_vector_storage_calculator_helper<needed_bytes, header_bytes, s_size>::value;
};

/////////////////////////////////////////////////////
//
//          small_vector_storage_definer
//
/////////////////////////////////////////////////////
template<class Storage, std::size_t N>
struct small_vector_storage
{
   Storage m_rest_of_storage[N];
};

template<class Storage>
struct small_vector_storage<Storage, 0>
{};

template<class T, class Allocator, std::size_t N, class Options>
struct small_vector_storage_definer
{
   typedef T value_type;
   typedef typename small_vector_base<value_type, Allocator, Options>::storage_type storage_type;
   static const std::size_t needed_extra_storages =
      small_vector_storage_calculator<storage_type, Allocator, value_type, N, Options>::needed_extra_storages;
   typedef small_vector_storage<storage_type, needed_extra_storages> type;
};

#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

//! small_vector is a vector-like container optimized for the case when it contains few elements.
//! It contains some preallocated elements in-place, which can avoid the use of dynamic storage allocation
//! when the actual number of elements is below that preallocated threshold.
//!
//! `small_vector<T, N, Allocator, Options>` is convertible to `small_vector_base<T, Allocator, Options>` that is independent
//! from the preallocated element capacity, so client code does not need to be templated on that N argument.
//!
//! All `boost::container::vector` member functions are inherited. See `vector` documentation for details.
//!
//! \tparam T The type of object that is stored in the small_vector
//! \tparam N The number of preallocated elements stored inside small_vector. It shall be less than Allocator::max_size();
//! \tparam Allocator The allocator used for memory management when the number of elements exceeds N. Use void
//!   for the default allocator
//! |tparam Options A type produced from \c boost::container::small_vector_options.
template <class T, std::size_t N, class Allocator BOOST_CONTAINER_DOCONLY(= void), class Options BOOST_CONTAINER_DOCONLY(= void) >
class small_vector : public small_vector_base<T, Allocator, Options>
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   , private small_vector_storage_definer<T, Allocator, N, Options>::type
   #endif
{
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef small_vector_base<T, Allocator, Options>   base_type;
   typedef typename small_vector_storage_definer
      <T, Allocator, N, Options>::type                remaining_storage_holder;

   BOOST_COPYABLE_AND_MOVABLE(small_vector)

   typedef allocator_traits<typename base_type::allocator_type> allocator_traits_type;

   public:
   typedef small_vector_storage_calculator
      < typename small_vector_base<T, Allocator, Options>::storage_type
      , Allocator, T, N, Options> storage_test;

   static const std::size_t needed_extra_storages =  storage_test::needed_extra_storages;
   static const std::size_t needed_bytes =  storage_test::needed_bytes;
   static const std::size_t header_bytes =  storage_test::header_bytes;
   static const std::size_t s_start =  storage_test::s_start;

   typedef typename base_type::allocator_type   allocator_type;
   typedef typename base_type::size_type        size_type;
   typedef typename base_type::value_type       value_type;

   BOOST_CONTAINER_FORCEINLINE static std::size_t internal_capacity()
   {  return (sizeof(small_vector) - storage_test::s_start)/sizeof(T);  }

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   //! @brief The capacity/max size of the container
   static const size_type static_capacity = N;

   public:
   BOOST_CONTAINER_FORCEINLINE small_vector()
      BOOST_NOEXCEPT_IF(dtl::is_nothrow_default_constructible<allocator_type>::value)
      : base_type(initial_capacity_t(), internal_capacity())
   {}

   BOOST_CONTAINER_FORCEINLINE explicit small_vector(const allocator_type &a)
      : base_type(initial_capacity_t(), internal_capacity(), a)
   {}

   BOOST_CONTAINER_FORCEINLINE explicit small_vector(size_type n)
      : base_type(initial_capacity_t(), internal_capacity())
   {  this->resize(n); }

   BOOST_CONTAINER_FORCEINLINE small_vector(size_type n, const allocator_type &a)
      : base_type(initial_capacity_t(), internal_capacity(), a)
   {  this->resize(n); }

   BOOST_CONTAINER_FORCEINLINE small_vector(size_type n, default_init_t)
      : base_type(initial_capacity_t(), internal_capacity())
   {  this->resize(n, default_init_t()); }

   BOOST_CONTAINER_FORCEINLINE small_vector(size_type n, default_init_t, const allocator_type &a)
      : base_type(initial_capacity_t(), internal_capacity(), a)
   {  this->resize(n, default_init_t()); }

   BOOST_CONTAINER_FORCEINLINE small_vector(size_type n, const value_type &v)
      : base_type(initial_capacity_t(), internal_capacity())
   {  this->resize(n, v); }

   BOOST_CONTAINER_FORCEINLINE small_vector(size_type n, const value_type &v, const allocator_type &a)
      : base_type(initial_capacity_t(), internal_capacity(), a)
   {  this->resize(n, v); }

   template <class InIt>
   BOOST_CONTAINER_FORCEINLINE small_vector(InIt first, InIt last
      BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I typename dtl::disable_if_c
         < dtl::is_convertible<InIt BOOST_MOVE_I size_type>::value
         BOOST_MOVE_I dtl::nat >::type * = 0)
      )
      : base_type(initial_capacity_t(), internal_capacity())
   {  this->assign(first, last); }

   template <class InIt>
   BOOST_CONTAINER_FORCEINLINE small_vector(InIt first, InIt last, const allocator_type& a
      BOOST_CONTAINER_DOCIGN(BOOST_MOVE_I typename dtl::disable_if_c
         < dtl::is_convertible<InIt BOOST_MOVE_I size_type>::value
         BOOST_MOVE_I dtl::nat >::type * = 0)
      )
      : base_type(initial_capacity_t(), internal_capacity(), a)
   {  this->assign(first, last); }

   BOOST_CONTAINER_FORCEINLINE small_vector(const small_vector &other)
      : base_type( initial_capacity_t(), internal_capacity()
                 , allocator_traits_type::select_on_container_copy_construction(other.get_stored_allocator()))
   {  this->assign(other.cbegin(), other.cend());  }

   BOOST_CONTAINER_FORCEINLINE small_vector(const small_vector &other, const allocator_type &a)
      : base_type(initial_capacity_t(), internal_capacity(), a)
   {  this->assign(other.cbegin(), other.cend());  }

   BOOST_CONTAINER_FORCEINLINE explicit small_vector(const base_type &other)
      : base_type( initial_capacity_t(), internal_capacity()
                 , allocator_traits_type::select_on_container_copy_construction(other.get_stored_allocator()))
   {  this->assign(other.cbegin(), other.cend());  }

   BOOST_CONTAINER_FORCEINLINE explicit small_vector(BOOST_RV_REF(base_type) other)
      : base_type(initial_capacity_t(), internal_capacity(), ::boost::move(other.get_stored_allocator()))
   {  this->move_construct_impl(other, other.get_stored_allocator());   }

   BOOST_CONTAINER_FORCEINLINE small_vector(BOOST_RV_REF(small_vector) other)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_constructible<value_type>::value)
      : base_type(initial_capacity_t(), internal_capacity(), ::boost::move(other.get_stored_allocator()))
   {  this->move_construct_impl(other, other.get_stored_allocator());   }

   BOOST_CONTAINER_FORCEINLINE small_vector(BOOST_RV_REF(small_vector) other, const allocator_type &a)
      : base_type(initial_capacity_t(), internal_capacity(), a)
   {  this->move_construct_impl(other, a);   }

   #if !defined(BOOST_NO_CXX11_HDR_INITIALIZER_LIST)
   BOOST_CONTAINER_FORCEINLINE small_vector(std::initializer_list<value_type> il, const allocator_type& a = allocator_type())
      : base_type(initial_capacity_t(), internal_capacity(), a)
   {
      this->assign(il.begin(), il.end());
   }
   #endif

   BOOST_CONTAINER_FORCEINLINE small_vector& operator=(BOOST_COPY_ASSIGN_REF(small_vector) other)
   {  return static_cast<small_vector&>(this->base_type::operator=(static_cast<base_type const&>(other)));  }

   BOOST_CONTAINER_FORCEINLINE small_vector& operator=(BOOST_RV_REF(small_vector) other)
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_assignable<value_type>::value
         && (allocator_traits_type::propagate_on_container_move_assignment::value
             || allocator_traits_type::is_always_equal::value))
   {  return static_cast<small_vector&>(this->base_type::operator=(BOOST_MOVE_BASE(base_type, other))); }

   BOOST_CONTAINER_FORCEINLINE small_vector& operator=(const base_type &other)
   {  return static_cast<small_vector&>(this->base_type::operator=(other));  }

   BOOST_CONTAINER_FORCEINLINE small_vector& operator=(BOOST_RV_REF(base_type) other)
   {  return static_cast<small_vector&>(this->base_type::operator=(boost::move(other))); }

   BOOST_CONTAINER_FORCEINLINE void swap(small_vector &other)
   {  return this->base_type::swap(other);  }
};

}}

#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
/*
namespace boost {

//!has_trivial_destructor_after_move<> == true_type
//!specialization for optimizations
template <class T, class Allocator>
struct has_trivial_destructor_after_move<boost::container::vector<T, Allocator> >
{
   typedef typename ::boost::container::allocator_traits<Allocator>::pointer pointer;
   static const bool value = ::boost::has_trivial_destructor_after_move<Allocator>::value &&
                             ::boost::has_trivial_destructor_after_move<pointer>::value;
};

}
*/
#endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

#include <boost/container/detail/config_end.hpp>

#endif //   #ifndef  BOOST_CONTAINER_CONTAINER_SMALL_VECTOR_HPP

/* small_vector.hpp
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
*/