//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_NEW_ALLOCATOR_HPP
#define BOOST_CONTAINER_NEW_ALLOCATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/throw_exception.hpp>
#include <cstddef>

//!\file

namespace boost {
namespace container {

/// @cond

template<bool Value>
struct new_allocator_bool
{  static const bool value = Value;  };

template<class T>
class new_allocator;

/// @endcond

//! Specialization of new_allocator for void types
template<>
class new_allocator<void>
{
   public:
   typedef void                                 value_type;
   typedef void *                               pointer;
   typedef const void*                          const_pointer;
   //!A integral constant of type bool with value true
   typedef BOOST_CONTAINER_IMPDEF(new_allocator_bool<true>) propagate_on_container_move_assignment;
   //!A integral constant of type bool with value true
   typedef BOOST_CONTAINER_IMPDEF(new_allocator_bool<true>) is_always_equal;
   // reference-to-void members are impossible

   //!Obtains an new_allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef new_allocator< T2> other;
   };

   //!Default constructor
   //!Never throws
   new_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Constructor from other new_allocator.
   //!Never throws
   new_allocator(const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy assignment operator from other new_allocator.
   //!Never throws
   new_allocator& operator=(const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {
       return *this;
   }

   //!Constructor from related new_allocator.
   //!Never throws
   template<class T2>
   new_allocator(const new_allocator<T2> &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Swaps two allocators, does nothing
   //!because this new_allocator is stateless
   friend void swap(new_allocator &, new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An new_allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator==(const new_allocator &, const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An new_allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator!=(const new_allocator &, const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }
};


//! This class is a reduced STL-compatible allocator that allocates memory using operator new
template<class T>
class new_allocator
{
   public:
   typedef T                                    value_type;
   typedef T *                                  pointer;
   typedef const T *                            const_pointer;
   typedef T &                                  reference;
   typedef const T &                            const_reference;
   typedef std::size_t                          size_type;
   typedef std::ptrdiff_t                       difference_type;
   //!A integral constant of type bool with value true
   typedef BOOST_CONTAINER_IMPDEF(new_allocator_bool<true>) propagate_on_container_move_assignment;
   //!A integral constant of type bool with value true
   typedef BOOST_CONTAINER_IMPDEF(new_allocator_bool<true>) is_always_equal;

   //!Obtains an new_allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef new_allocator<T2> other;
   };

   //!Default constructor
   //!Never throws
   new_allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Constructor from other new_allocator.
   //!Never throws
   new_allocator(const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Copy assignment operator from other new_allocator.
   //!Never throws
   new_allocator& operator=(const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {
       return *this;
   }

   //!Constructor from related new_allocator.
   //!Never throws
   template<class T2>
   new_allocator(const new_allocator<T2> &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Allocates memory for an array of count elements.
   //!Throws std::bad_alloc if there is no enough memory
   pointer allocate(size_type count)
   {
      const std::size_t max_count = std::size_t(-1)/(2*sizeof(T));
      if(BOOST_UNLIKELY(count > max_count))
         throw_bad_alloc();
      return static_cast<T*>(::operator new(count*sizeof(T)));
   }

   //!Deallocates previously allocated memory.
   //!Never throws
   void deallocate(pointer ptr, size_type) BOOST_NOEXCEPT_OR_NOTHROW
     { ::operator delete((void*)ptr); }

   //!Returns the maximum number of elements that could be allocated.
   //!Never throws
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return std::size_t(-1)/(2*sizeof(T));   }

   //!Swaps two allocators, does nothing
   //!because this new_allocator is stateless
   friend void swap(new_allocator &, new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An new_allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator==(const new_allocator &, const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An new_allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator!=(const new_allocator &, const new_allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }
};

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_NEW_ALLOCATOR_HPP

/* new_allocator.hpp
jPjn7nWyCNoSYQ9m1NTIAuUccEFY8idVk8nC5R2wVdi9t1bcJAtVcECmsC/3r+hO5qnogHzC2l1cU4DMi2ZWZwBtlEW32RPWrea4yg7oLuKalK4e5/7QonK8NgX2k0WrOKC3sOoT9u3mnFUd8JcwgI+WkvmqmcfF0DoIKxLLf5R7r+6AiLDhm+tdInPXMI8Loj0nLHph6B6yONpsYR02vt6RLOTGY0KYPCYiCospDGqam0thHoX5FBZQWEhhEVMbCjG0VglLszaEI398epjMU8sBJYWdOrv0ApkfraKwQgU/H0AWRpsi7L2hWS3JfM84YLmw7+5NH0Lmro3XJWH/1PPFyLx1HDDCqpvn+/fbcc76Dugr4lYmjVjC/aEtENbn5LfjyUINHPC5sP1Lmp4nCzR0wO/CGrQo+ydZsJED9gnrHxjnYXsWz1thUVedVmQRtBzClk7t/QtZ1GD8O2ZoMUVOrbF5TpfB+D0emhutubB+z+X5jHtAq2zRbc6oIvd5vKbZj4lCP1ZtT+ZBKypsX8WRX5H5FBYw5Mzz5bSxZGFDHL+nRIsqLI5WXBjf06K5PA7QRH8fz9w/jWtpljhXEibPlZDCIqbWH2JoPyasKM5tzw83KcPW3AFBYRtr9ynF7xha6Pdnxaxj9PsztLDCIgqLKiymsLip+QFaOngOt7i1v5jD7Q8+tLSElUCLtF/YgiyAVk5Yn2+WnyYLoxUV1mTI1hBZVGFxhWmtzM2tMK/C/AoLGuxW9RrJ3B+a7H3PF7PnkcUMcfw7z2jQ2txcCvMozKewgMJCCosY7NOhzWdyf2iyd8/FxX3JtDbZ48Ze+yKNzK0wr8L8CgsqLKywqKmNhzhatYSVtA6EJtFOu8ncbbPbnJwLu5P5DZZz9pw8ZGG0Z4Td/qJvPx4Prb6wZyqN2UHmaYef78JeaDPMSRZCqyOsbXL8bc6Jlims9P4hz5MF22eP27b/5GyyGNrzwp62Oz2QzNvBAXZhX35V2M69G2z94TucM4iWJIznvdFCaGnC1qbWGEQWQesh7OWf714gc3d0QF1hBTpnVSULoCVZdLv8eelqZNHnHNBYxF3Y0zWDzNXJAcnCeM4fzY22S+Q8YUnzc+9eBxwQNtr5+d/cwwsOuCjjbp1dxDm74Hkk7FpylU/JQl0d8DHoNq7Qyi48Xjd8RhBxY0//vZF76OGAl4X1b/jl92Sxng64Crod7tttCpnW2wFuETf/TmZTsmAf/T4ETbzrwToNxut70MIG498wRYsYjH8vFi1qMF6HhBYzGP/2KVrcYLxmCA36ZrcNq1N+5N7RigprNeriPjK3IY7vwdA8BuN7PjSvwfh3ZtF8Btta41ABMr/BeE0UWsBgvDYNLYhWQlg0fc19sgjaX8J6vFT7Flk0I3vv/PveaPEMw7a+tOocGfgM/fneqEamGazzm30DZC6DObo+e5PMbbANo7cMJvMYrP2BCn4yL5pL2EfNzncgC/jM923IZ957xGfYR/f7rSeLGqxN3hltyWIGK3b8XEOyuMGat3yyhQz6mdfiUpinn+H8S2tlJfMarOSCZdy7D83seAmiNRe2JE+ZNtwDWqowvk9G0142N7fCvArzKyyosLDCogqLK0zrr+hPYV6F+RUWVFhYYVGFxRWmDVD0pzAv2gvCMmvtfUAWQStq0S2jeqGs/ywTXIPwszHpP0u3ZkDdpFATMm24/vyHpj//oXnQUoVxLWg+UxsFAbSGiVpc1lfgi/c+n0mmvZKIS5icT3ajlU1YKTT+rh6aD62asAOPvBPIQgqLKcw1EnsX9o72UiaZF+0DYfs7PClEpo1yQFxYjUNpVcg8ftwPwvg7d2g+tIrCyvU=
*/