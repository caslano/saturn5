//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/move/unique_ptr.hpp>

//!\file
//!This header provides utilities to define a unique_ptr that plays nicely with managed segments.

namespace boost{
namespace interprocess{

//For backwards compatibility
using ::boost::movelib::unique_ptr;

//!Returns the type of a unique pointer
//!of type T with boost::interprocess::deleter deleter
//!that can be constructed in the given managed segment type.
template<class T, class ManagedMemory>
struct managed_unique_ptr
{
   typedef boost::movelib::unique_ptr
   < T
   , typename ManagedMemory::template deleter<T>::type
   > type;
};

//!Returns an instance of a unique pointer constructed
//!with boost::interproces::deleter from a pointer
//!of type T that has been allocated in the passed managed segment
template<class T, class ManagedMemory>
inline typename managed_unique_ptr<T, ManagedMemory>::type
   make_managed_unique_ptr(T *constructed_object, ManagedMemory &managed_memory)
{
   return typename managed_unique_ptr<T, ManagedMemory>::type
      (constructed_object, managed_memory.template get_deleter<T>());
}

}  //namespace interprocess{
}  //namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_UNIQUE_PTR_HPP_INCLUDED

/* unique_ptr.hpp
lvJcm1l+zgeaFnXsfa6oOEC51R5yOyrJRXruPROgXGmAcuUBylUEIJem8zsAv8/s16xz1T14z9t+PBfbH2wFDuC9bWfwnr05vMfqIHAsmMtz1SPAq3nu+haeu17Ge1U+wHPVa3iv1nVgPu+FWQA+wf5Pcfzbea/WMk73LZ7jPsJ7vx7lPTl/5j0x6+vG3Hg6OBhsBw4Fx4CXg+PBaeBksBC8CpwOztON+A96zJHV+wCEK4DzPl8W3FzZqVdC82VVnS/b7PrfzZnV2/b/N2/WedvpmzvL3WbMnzm3nZ45tCXbQvNo1Z1HW/oB4oHbA3cCLu1D1DPcWDgX3Aa4crhTcI0+Qjk+Cs2phf5Cf6G/0F/o7385/z9tzulY/9+E5/9LL6a5/QHZo/OGD+3eJzsvN3tIv0G9WAXAmNuH6qm5NnChbp9j/wHxHC+nsVxbRDxHQXOi39fxOs+O8FWfZ0e8tnn2U150ECq85XNqkd85bvc8+9GLbfPsZv0Uhtnn2X9E/hJ2q9OlqfbA59pRbmt6y8NZV5cF/gL3M9LLMNIrwNi6LU2N2+MnH+2R4THOfSzZWMehKcfVrbJJmpDFYgn1WhKWle18QwDldbfzT0Y7m+OhIl8pnC/4cVrwo/St9XQdD8SmGoAMxjYRX+5u1kkoUNRTAP0216PsPybLNTpKG8eVyu4KouzfVyo70uL1K9a5pQzu8Ndy378GTk/DGFU5l3OWspw033Iyyf98C+Lh8nK9SDuVNMcxjs6PUJZfhlWvZc+m83NU/QZhg9tHwC1fH3UdReuEjDWk++BA/u1/LwD3mDzqRjUmz+1CdcB90Lq2SL0fwJkdqw92TF49Fh38WH3ddsL/lfgPWi2b+4vr2g/G3L3+zRUP/v+M1avnOLyN4YfG6nmsnsfP+ZkOJvke7+ZnsnpcvKGU42co7hd+4stgubp+5HJZLtWH3FzzXoJ7Kss54Ao95gF0XsNSl8fnm4AteZy3FdgVvIDXKmSwTa02vEYhE7wMbAvOBi8Er+Hx+K08nlpSYYypbq04vWsPQuOpVR9PDY2l/rZjqYcrztx4amgstXpjqdrHkIUbCOeEWw635eM/13jpmfv+z5854zTo/7u//wsHSt1+oXI6dNiQ7v1yhg3lAQD6/j/g5/s/Og3P8F30faGISOrZR6Z5/Y5C+KC+//t7fhuJePn738yn5kXPftNOL/kMUtd++UDvYwBOxRhATJp42feSdhX17d3ffFvDec6f32EyWN++dKfUt7elqQWuY0fxWHXuzW+2V+nc+Wod0p0KHXxS85ZyDinH331yT6FpicL5t5leZZ1zyotVV3FKhFqHPL28ejrk6eVV1xn2pkM+LFKtQ55RXj0d8ozywHVIM8qrrkMaiA65u4/HiJPiPOmQgqxDCoUe1iGtXh/X3gpcj5RkLf2aKnc2zpj7eHUjme/wfl+kHM+Q6dF9EX90Yzf1QHfT+Rws22lG15o4akf3yChT17QuyYxR6ppm07kL9G+0SKV+Zyo4jmRS9Xu1noYfjoaT3yHod95L+p2j0KlO4Cb6PulX1tAq61fWZ5lm0W79zovc+p2u+6HgqdTv5DC50W79zuFq/U6WK4LcQUN3s4F8PhgydXEcyTqZH1j0MQPTv2ywq2r6l5Z7Cbf/731cJ9jxm5x2NA7RdvSOB0f9cn0PR+uvzoq99aI/7vhNSAfTvw5mW986mHSdloLnwb0vf/OYEL/ngUkKO3+QkzqAO3lMSCHXVMrxOxWuZR/xZYlzHF9rlouUZaExGp3HZlJ5bKaZOM86e+1keniOB6brmBGA3BbzOUDPM+TLageyE+sSdgPrUzkM+7jdwQ6ss3cR2BMczvY=
*/