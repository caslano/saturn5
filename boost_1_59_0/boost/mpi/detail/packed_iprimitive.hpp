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