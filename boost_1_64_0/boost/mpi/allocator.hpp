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
nJPeaUlyMAaNjUBSBQAEWfjumv/xFL7z+Dn49qWzyT4qJAenzc9R1KPmVgNiXWXJSJy1TCZ+5qvzA3A0aydFSisYcWJojxbye8nCmTCnrqGd12tvMA8io/psxZQie9f4obKKKSNiEfjXZ+eFT9EpXtmelLFzMxUMgrVjRWC4bHYsGxhREc5WhDOUvW0LfosGRuwWNTGMz+VhI+QPB7kuZf9zlkOfbDGA1VCMzX81SbD5mbXjaszDgbB6rac+p1FfjMm9L6dMr7mNSW5qNos2X/KBpO11zDVeCJgoLm/wwid8T1zn47DejUPg38LGMbXlXNEMqei7dkWHQ0b7Pg3j1S1spIOoMg6SGpGHXo5cXCPQokiDuB1n/mgwq6Qr7gMI61GuJmbYTfwSqqdKDpslEnPtsZSX9WzV1k/OcXX7BFe33z2Vq1rs1RUMQT4NwmOPrH3QTHR8D9p7qZZ5Xm9lxCpp3ouFZUxHitQLKolvUY+zE6r66iahJQ4fpujFri0GabQzMwGPXNLJIeSSgrYs216fCvyQaV/KiJeZA7YAkC929f4kG+ROeGVbH4Cy7mCik3FoFA8E+8DI9xpXueF2ufuoXE/J4whXxh9OLTUBOCK8KWRq36PTuZRf9Ll7klwbhAtG+vwIMx/qxBv3rl3gamHVLGbbjkm8DOwwz8HUcOr6MTV4tbIr80I78zDSxaaiyFEkS2uikpMkZ4uV5v9+35d/xY/jC4GOu7LKbERTRQgRD9KHb67NUx6Z3MNDfoFG81S4DJ/FLLjapZpEH+YGDc6Tz3Wn3F4wNo3Rh3oP5L5DPS57zOOA/WZjPeDFcs5sg2QRGGxAhEki3obAUlJEv5HHBHF70JloEIuHTTo5hmczOicIKexSybyn2fyiDz5Fq01ag83ksAKA51f/TMg5SLrJi/qcTwnfPa4GY4gKWljBi3PLyWLHWcFzJMcbMA/W0gTNAbVlSoiuzSwj5TUxLnsWffxn4vivm0vyOuwh+E+fI4Z9i4VJkqZ+NFYEDDJu+c5YlxT/BT9RAxYyts+VzsKRgyVmLkQxKBo+XcAERgwH+zWv6o16obgUinOhuCqUEdeT+eMEk4+2b6D9LDtbAJpLvGI7UFj3MqqGasuo1FLn3bAxaeI7kNfGuo6y7CuHCzSAPVPE+6eSmyWZavKx/MkA9wrApO6m6xAE4JMJlBRYAdQdhVj7RqAxQ+VAZQ9FBLJ0pysdfPcgR2ksmQFrBHC1JrVnKND5PtC+s3iz4A9M4m162+sqon/J4g54oFE5YqyM04HUtYSMABRCn4durL+bK+uG5hJ3e3k8dGX3oslqPAR5w3joV0v85QJtPLpkPLq4mi41gUdBEo5pr7duKrkz83h08Hhohhbo7GESI9qBnHMkXfJ4qIXGJJKmgYR+HwpNSw2b3DVk7Ro2gQC0rRNOz5Ll5P7G2ds5uwjKfIG94SU7ivZoZD0MssxVq3uuMjRXdMC2fkK4tbnXV4cEdNtrMH62N7By8Po9DbjJA7NWBmYt77O10TAPjC+5L5HmNVCGcN8aEsHX2H57iQmwPWnvPbkPzR8VGroGN22yIOn/j2lxPj6/SAxGMogqgtE1r6C2qLWizCQqNoJYCkMNz2D0ienRY+AyU/OC1FBrWPFqXdUEKHwDJxIKv51R+LgTBIX781QSKPpXRfSPras2eH3MaAnBIrffOUGscZDy78/OKe/d1fLruDysdm/9KBdXWoSXjpfSxTpDOQ+sOjG8KbRNt/LrMLZXRvav0B4QGmZzTU/9cKt5f/SDRZY9GjbpG2qG9kMHMfR9RnxDpv+kITJIHhgO0JQ8HVyysT6Q7Em+Ti4tPD0joecbpgVsOpY=
*/