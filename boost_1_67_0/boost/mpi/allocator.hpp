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