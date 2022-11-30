// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file allocator.hpp
 *
 *  This header provides an STL-compliant allocator that uses the
 *  MPI-2 memory allocation facilities.
 */
#ifndef BOOST_MPI_ALLOCATOR_HPP
#define BOOST_MPI_ALLOCATOR_HPP

#include <boost/mpi/config.hpp>
#include <boost/mpi/exception.hpp>
#include <cstddef>
#include <memory>
#include <boost/limits.hpp>

namespace boost { namespace mpi {

#if defined(BOOST_MPI_HAS_MEMORY_ALLOCATION)
template<typename T> class allocator;

/** @brief Allocator specialization for @c void value types.
 *
 *  The @c void specialization of @c allocator is useful only for
 *  rebinding to another, different value type.
 */
template<> 
class BOOST_MPI_DECL allocator<void> 
{ 
public: 
  typedef void* pointer; 
  typedef const void* const_pointer; 
  typedef void value_type; 

  template <class U> 
  struct rebind 
  { 
    typedef allocator<U> other; 
  }; 
};

/** @brief Standard Library-compliant allocator for the MPI-2 memory
 *  allocation routines.
 *
 *  This allocator provides a standard C++ interface to the @c
 *  MPI_Alloc_mem and @c MPI_Free_mem routines of MPI-2. It is
 *  intended to be used with the containers in the Standard Library
 *  (@c vector, in particular) in cases where the contents of the
 *  container will be directly transmitted via MPI. This allocator is
 *  also used internally by the library for character buffers that
 *  will be used in the transmission of data.
 *
 *  The @c allocator class template only provides MPI memory
 *  allocation when the underlying MPI implementation is either MPI-2
 *  compliant or is known to provide @c MPI_Alloc_mem and @c
 *  MPI_Free_mem as extensions. When the MPI memory allocation
 *  routines are not available, @c allocator is brought in directly
 *  from namespace @c std, so that standard allocators are used
 *  throughout. The macro @c BOOST_MPI_HAS_MEMORY_ALLOCATION will be
 *  defined when the MPI-2 memory allocation facilities are available.
 */
template<typename T> 
class BOOST_MPI_DECL allocator 
{
public:
  /// Holds the size of objects
  typedef std::size_t     size_type;

  /// Holds the number of elements between two pointers
  typedef std::ptrdiff_t  difference_type;

  /// A pointer to an object of type @c T
  typedef T*              pointer;

  /// A pointer to a constant object of type @c T
  typedef const T*        const_pointer;

  /// A reference to an object of type @c T
  typedef T&              reference;

  /// A reference to a constant object of type @c T
  typedef const T&        const_reference;

  /// The type of memory allocated by this allocator
  typedef T               value_type;

  /** @brief Retrieve the type of an allocator similar to this
   * allocator but for a different value type.
   */
  template <typename U> 
  struct rebind 
  { 
    typedef allocator<U> other; 
  };

  /** Default-construct an allocator. */
  allocator() throw() { }

  /** Copy-construct an allocator. */
  allocator(const allocator&) throw() { }

  /** 
   * Copy-construct an allocator from another allocator for a
   * different value type.
   */
  template <typename U> 
  allocator(const allocator<U>&) throw() { }

  /** Destroy an allocator. */
  ~allocator() throw() { }

  /** Returns the address of object @p x. */
  pointer address(reference x) const
  {
    return &x;
  }

  /** Returns the address of object @p x. */
  const_pointer address(const_reference x) const
  {
    return &x;
  }

  /** 
   *  Allocate enough memory for @p n elements of type @c T.
   *
   *  @param n The number of elements for which memory should be
   *  allocated.
   *
   *  @return a pointer to the newly-allocated memory
   */
  pointer allocate(size_type n, allocator<void>::const_pointer /*hint*/ = 0)
  {
    pointer result;
    BOOST_MPI_CHECK_RESULT(MPI_Alloc_mem,
                           (static_cast<MPI_Aint>(n * sizeof(T)), 
                            MPI_INFO_NULL, 
                            &result));
    return result;
  }

  /**
   *  Deallocate memory referred to by the pointer @c p.
   *
   *  @param p The pointer whose memory should be deallocated. This
   *  pointer shall have been returned from the @c allocate() function
   *  and not have already been freed.
   */
  void deallocate(pointer p, size_type /*n*/)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Free_mem, (p));
  }

  /** 
   * Returns the maximum number of elements that can be allocated
   * with @c allocate().
   */
  size_type max_size() const throw()
  {
    return (std::numeric_limits<std::size_t>::max)() / sizeof(T);
  }

  /** Construct a copy of @p val at the location referenced by @c p. */
  void construct(pointer p, const T& val)
  {
    new ((void *)p) T(val);
  }

  /** Destroy the object referenced by @c p. */
  void destroy(pointer p)
  {
    ((T*)p)->~T();
  }
};

/** @brief Compare two allocators for equality.
 *
 *  Since MPI allocators have no state, all MPI allocators are equal.
 *
 *  @returns @c true
 */
template<typename T1, typename T2>
inline bool operator==(const allocator<T1>&, const allocator<T2>&) throw()
{
  return true;
}

/** @brief Compare two allocators for inequality.
 *
 *  Since MPI allocators have no state, all MPI allocators are equal.
 *
 *  @returns @c false
 */
template<typename T1, typename T2>
inline bool operator!=(const allocator<T1>&, const allocator<T2>&) throw()
{
  return false;
}
#else
// Bring in the default allocator from namespace std.
using std::allocator;
#endif

} } /// end namespace boost::mpi

#endif // BOOST_MPI_ALLOCATOR_HPP

/* allocator.hpp
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
*/