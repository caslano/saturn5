// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_PACKED_IPRIMITIVE_HPP
#define BOOST_MPI_PACKED_IPRIMITIVE_HPP

#include <boost/mpi/config.hpp>
#include <cstddef> // size_t
#include <boost/config.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/mpi/exception.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/serialization/array.hpp>
#include <vector>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/mpi/allocator.hpp>

namespace boost { namespace mpi {

/// deserialization using MPI_Unpack

class BOOST_MPI_DECL packed_iprimitive
{
public:
    /// the type of the buffer from which the data is unpacked upon deserialization
    typedef std::vector<char, allocator<char> > buffer_type;

    packed_iprimitive(buffer_type & b, MPI_Comm const & comm, int position = 0)
         : buffer_(b),
           comm(comm),
           position(position)
        {
        }

    void* address ()
    {
      return &buffer_[0];
    }

    void const* address () const
    {
      return &buffer_[0];
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
          load_impl(address,MPI_BYTE,count);
        }

    // fast saving of arrays of fundamental types
    template<class T>
    void load_array(serialization::array_wrapper<T> const& x, unsigned int /* file_version */)
    {
      if (x.count())
        load_impl(x.address(), get_mpi_datatype(*x.address()), x.count());
    }

/*
    template<class T>
    void load(serialization::array_wrapper<T> const& x)
    {
      load_array(x,0u);
    }
*/

    typedef is_mpi_datatype<mpl::_1> use_array_optimization;

    // default saving of primitives.
    template<class T>
    void load( T & t)
    {
      load_impl(&t, get_mpi_datatype(t), 1);
    }

    template<class CharType>
    void load(std::basic_string<CharType> & s)
    {
        unsigned int l;
        load(l);
        s.resize(l);
        // note breaking a rule here - could be a problem on some platform
        if (l)
          load_impl(const_cast<CharType *>(s.data()),
                    get_mpi_datatype(CharType()),l);
    }

private:

    void load_impl(void * p, MPI_Datatype t, int l)
    {
      BOOST_MPI_CHECK_RESULT(MPI_Unpack,
                             (const_cast<char*>(detail::c_data(buffer_)), buffer_.size(), &position, p, l, t, comm));
    }

    buffer_type & buffer_;
    mutable std::size_t size_;
    MPI_Comm comm;
    int position;
};

} } // end namespace boost::mpi

#endif // BOOST_MPI_PACKED_IPRIMITIVE_HPP

/* packed_iprimitive.hpp
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
*/