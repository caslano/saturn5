// (C) Copyright 2005-2007 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_BINARY_BUFFER_IPRIMITIVE_HPP
#define BOOST_MPI_BINARY_BUFFER_IPRIMITIVE_HPP

#include <mpi.h>
#include <iostream>
#include <cstddef> // size_t
#include <boost/config.hpp>
#include <boost/mpi/exception.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <vector>
#include <boost/mpi/allocator.hpp>
#include <cstring> // for memcpy
#include <cassert>

namespace boost { namespace mpi {

/// deserialization using MPI_Unpack

class BOOST_MPI_DECL binary_buffer_iprimitive
{
public:
    /// the type of the buffer from which the data is unpacked upon deserialization
    typedef std::vector<char, allocator<char> > buffer_type;

    binary_buffer_iprimitive(buffer_type & b, MPI_Comm const &, int position = 0)
     : buffer_(b),
       position(position)
    {
    }

    void* address ()
    {
      return &buffer_.front();
    }

    void const* address () const
    {
      return &buffer_.front();
    }

    const std::size_t& size() const
    {
      return size_ = buffer_.size();
    }

    void resize(std::size_t s)
    {
      buffer_.resize(s);
    }

    void load_binary(void *address, std::size_t count)
    {
      load_impl(address,count);
    }

    // fast saving of arrays of fundamental types
    template<class T>
    void load_array(serialization::array_wrapper<T> const& x, unsigned int /* file_version */)
    {
      BOOST_MPL_ASSERT((serialization::is_bitwise_serializable<BOOST_DEDUCED_TYPENAME remove_const<T>::type>));
      if (x.count())
        load_impl(x.address(), sizeof(T)*x.count());
    }

    typedef serialization::is_bitwise_serializable<mpl::_1> use_array_optimization;

    template<class T>
    void load(serialization::array_wrapper<T> const& x)
    {
      load_array(x,0u);
    }

    // default saving of primitives.
    template<class T>
    void load( T & t)
    {
      BOOST_MPL_ASSERT((serialization::is_bitwise_serializable<BOOST_DEDUCED_TYPENAME remove_const<T>::type>));
      load_impl(&t, sizeof(T));
    }

    template<class CharType>
    void load(std::basic_string<CharType> & s)
    {
      unsigned int l;
      load(l);
      // borland de-allocator fixup
      #if BOOST_WORKAROUND(_RWSTD_VER, BOOST_TESTED_AT(20101))
      if(NULL != s.data())
      #endif
      s.resize(l);
      // note breaking a rule here - could be a problem on some platform
      load_impl(const_cast<char *>(s.data()),l);
    }

private:

    void load_impl(void * p, int l)
    {
      assert(position+l<=static_cast<int>(buffer_.size()));
      if (l)
        std::memcpy(p,&buffer_[position],l);
      position += l;
    }

    buffer_type & buffer_;
    mutable std::size_t size_;
    int position;
};

} } // end namespace boost::mpi

#endif // BOOST_MPI_PACKED_IPRIMITIVE_HPP

/* binary_buffer_iprimitive.hpp
+Yw6T2to9kKkBjWYDJuxQiYq2KCV4VeZMrbCS4N1Hhidl6XQlqRif1qV0XQ1gt50cT97tBKgkwLvfif993AW1OooconMuXcmCo/auqYbjEecl60LxzX1yFxVhsN/Znnkh50Gvd1adXYbDrpgvefZ+ul++eh1+8Shz/oe+dc5j3i2kXPxkJ1ksvP/+RdQSwMECgAAAAgALWdKUv4pm/CCAgAAaAQAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDU2VVQFAAG2SCRgbVRhT9swFPxuqf/hKQwN2IKbUro1yiqhjgEb0KpkaJP2xSQvTURqZ7ZTyL/fc9LSTUNKYsU+n+/dvSSyaGwiDE5YVMhM0fCIzZPSqZmwyzietw+4OI9ZpdVzw3LRjVfz9YhFfAeOeLd/j+3BHeo1at8UKbJIY1U2tJ4KK0CqJMfk8ZPXoPG6E3hwHMCg34fZN/ZZWAwhrvE99Mdwq9a0EPQhGIbDcUiQi5uYdeQhOOW+aV94Jh6RXQuauFFpkRWYbliCE/haS0dPLIMw6G9ZzmOxDMEbBP3BqZ8mH/yT8XA0GI4/euwsSbCy/kLIJZoQHho6iU2VtCitf41yafMQRm5GYmILJUNISmXwBRM3FTp9z5bndlWyL7WU
*/