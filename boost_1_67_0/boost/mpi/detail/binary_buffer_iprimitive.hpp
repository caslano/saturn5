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
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
*/