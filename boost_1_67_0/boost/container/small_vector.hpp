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
      const vector_base &v_base = reinterpret_cast<const vector_base &>(v_holder);
      const derived_type &d_base = static_cast<const derived_type &>(v_base);
      return d_base.internal_storage();
   }

   BOOST_CONTAINER_FORCEINLINE
   pointer internal_storage()
   {
      vector_alloc_holder_t &v_holder = static_cast<vector_alloc_holder_t &>(*this);
      vector_base &v_base = reinterpret_cast<vector_base &>(v_holder);
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
      BOOST_NOEXCEPT_IF(boost::container::dtl::is_nothrow_move_assignable<value_type>::value)
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