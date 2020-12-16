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
SEjN8POpwKYbvwkC0mcgCou/A2f9y7MR61XBO6igl0V3aOyy0kvuheFkU5zkS6StmIrFwf6c1WpoEH/18La5X4FKSxEfFF2k+N5ktZMyWrqTmrN/uEOdvz1Rosaz7F/ivwrO14dvUOcrBTDgJSZlgX4wCyzs6klB6fFUvZQPDyBHKaZXhdC7yjcS5E/6APLFpQ28KZB9AEgPS14u7MC+VPwJDQXpbMEZmoPbDSABBhgk5uxEK3/iYCXSqy+b4G6AdOpOT5hwZJEjOwGZXPV9tNKGeR7A5wguAjcklo9JpdBiNw7fomRhIrKrr0o5llewps/nXLjB+11G5c9FJdmR/73Non+jM9SF7i+Aqg/gF07i95KXcZMcTpA1zDC+udtG5KgMOaATezD9MylLenvPcmkK/IczjHYk45HjwEtEPkdA9KByy+cRm7H9aqpGJ7i1GRZ4xRxpqB62lSflj7+uYh2PrySD+KiXOTUubq7lH8v//60w6ScCMgPTNZZxUhieFJISe0FQG0oj6v/7QYq9qW3sEV025uzWpiHzCNsErGttEX4O0M9iYdgJUwFJWd2HEM8T+k0L7hmN76dXNWWfqL5ooP9FfwbzNX29cGNijHD2Sl6PX0mGKFScrDJulQw6srI4tWUdtuIBTJ/Jukg/i+7GnhXc2nKrG1D8iRVxtWb5/1pP9jou6yATaVRfgetPNxbeFmWjk+yybYz+LvvG2HCHbWPoA6w8kMmuseV5ySSHiTNvlgAdF1d7sQG8zCszpEBfFQVT2ZU1VDASqsMQcRFDZhaPzqS9PcgY44Htjl8kqas+mrtBd6ElQKu/XctaB7kEtiMWAwUvqCfO2E6LqrBXVUinxyUNqB0a/5+BHHZoIak6IHNFZDhNdVXkJXQBmqSf44ra162LeAGnuqx9TUpdny7njALJIGZxP6cW7/kh6GtLP6a9V+rNMfghfRV2XLxiLF4TcYNJMeZNr0O9GHjMwpMM2RhgoDqcS/JgQbM2AOoKJCMX6WuFfs65iThMPou4yCIsMkq/TSZqghRRGqA1llPsP37V0GCxj0ANiHGcwBr05/FGO2CR+dop/kJY+wo6cdKxk/pmEX1cwKKPG5e0VPQR18fy/3qTXR+f5BCzQKXRFuIPjvN01GzoLGJamvDzyQ7FJ4VyyDmjp3CAfr8MD6QtS2Fwn5fQALAij8ltbFssmFa1SsXWFNj0Uvj7b3gWWZt15QUK9lR9iwl7AcG+VWBXTtZ1TE6l54C/z6ZlxicAfZHCEn3Pq91sE9vKGE6dyIS6rMT4yc3fpxKj6f/+0ib839/p4P/+Vufykl99a/P2UmkrmraXmjo3tv3W5tmx+7v4jsb9PS2O/qwsaro/T6+P3Z8Pf9U8/EKp7yj/BaYZZUNluD0H9yXZEJ7UbBZmF/Tg6xHQirHGqeubf2UheX4fJP6gVNLP6FcKt5RtgEHG51OgvcHQd6Q3j+WzvVMSlmwuHlJ0qdjvj4em42mScZH1/ogp0N5CtgzUx86gr7PuaNH7I8e/KUP5Lt4LSAeiBjQ2EpwiJIZzcrUlQBpqE4nZB84pMRf+8A59M21rbkPKi6BLEqqAP+PcU9C+0/rLNVTf+FeQYp26jPa1v1NDx328bP7Eho574E+s63x+vLbOTt+KR2fTgT0CLjcdl71/nFDqQLqeBS0AsQY2dDmkP4DlpHTy7iT8owE+nNQQSGnoiH9UvZeQAJDCCIllEhwRFa1+ykBmRi6UUMUFLkO1UAgWC2rOgr+Kw9cEqCi6clkNZxZc9pZiAoeKs0QZYXDtBqoglOI2lsJ+CF6GJgBk7R0myRwFnnKjgENaYUcK4yzXprBwH3zHC/emMfQ=
*/