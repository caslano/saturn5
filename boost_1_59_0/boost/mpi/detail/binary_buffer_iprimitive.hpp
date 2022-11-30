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
      return detail::c_data(buffer_);
    }

    void const* address () const
    {
      return detail::c_data(buffer_);
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