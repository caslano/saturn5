// (C) Copyright 2005-2007 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_BINARY_BUFFER_OPRIMITIVE_HPP
#define BOOST_MPI_BINARY_BUFFER_OPRIMITIVE_HPP

#include <mpi.h>
#include <iostream>
#include <cstddef> // size_t
#include <boost/config.hpp>

#include <boost/serialization/array.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <vector>
#include <boost/mpi/allocator.hpp>
#include <boost/mpl/always.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace mpi {

/// serialization using binary copy into a buffer

class BOOST_MPI_DECL binary_buffer_oprimitive
{
public:
    /// the type of the buffer into which the data is packed upon serialization
    typedef std::vector<char, allocator<char> > buffer_type;

    binary_buffer_oprimitive(buffer_type & b, MPI_Comm const &)
     : buffer_(b)
    {
    }

    void const * address() const
    {
      return &buffer_.front();
    }

    const std::size_t& size() const
    {
      return size_ = buffer_.size();
    }
    
    const std::size_t* size_ptr() const
    {
      return &size();
    }
    
    void save_binary(void const *address, std::size_t count)
    {
      save_impl(address,count);
    }

    // fast saving of arrays
    template<class T>
    void save_array(serialization::array_wrapper<T> const& x, unsigned int /* file_version */)
    {
    
      BOOST_MPL_ASSERT((serialization::is_bitwise_serializable<BOOST_DEDUCED_TYPENAME remove_const<T>::type>));
      if (x.count())
        save_impl(x.address(), x.count()*sizeof(T));
    }

    template<class T>
    void save(serialization::array_wrapper<T> const& x)
    {
      save_array(x,0u);
    }

    typedef serialization::is_bitwise_serializable<mpl::_1> use_array_optimization;

    // default saving of primitives.
    template<class T>
    void save(const T & t)
    {
      BOOST_MPL_ASSERT((serialization::is_bitwise_serializable<BOOST_DEDUCED_TYPENAME remove_const<T>::type>));
      save_impl(&t, sizeof(T));
    }

    template<class CharType>
    void save(const std::basic_string<CharType> &s)
    {
      unsigned int l = static_cast<unsigned int>(s.size());
      save(l);
      save_impl(s.data(),s.size());
    }

private:

    void save_impl(void const * p, int l)
    {
      char const* ptr = reinterpret_cast<char const*>(p);
      buffer_.insert(buffer_.end(),ptr,ptr+l);
    }

  buffer_type& buffer_;
  mutable std::size_t size_;
};

} } // end namespace boost::mpi

#endif // BOOST_MPI_BINARY_BUFFER_OPRIMITIVE_HPP

/* binary_buffer_oprimitive.hpp
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
*/