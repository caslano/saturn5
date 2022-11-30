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
      return detail::c_data(buffer_);
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