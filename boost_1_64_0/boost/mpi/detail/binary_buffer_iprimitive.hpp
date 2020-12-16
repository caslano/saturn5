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
EOIpDdgBN9DVRXvQo/vS7rrPhBAgCM8qCJ/TuPewUrBruSUW08wK46jCWlXhRajAd2qIhNYXqqEdOcrvjesT1nraWY7U5SYfehPmagDu1P0D9gTz9sNEEB3ZeX3evrXe0HFxbMEqH3gvMcvt8ngT9BOke6gf4AaXyHyvBCkrlwu69H5ShN4cp623SZHbElXdc/W/yODj/x/8OOs3LYOLBqhr/MzSb4IUVGj6jO3U9Izp9PXQ1pboN/H7U3ew6JU4YsbnJBHAx1GKG2YMus5SVnbun3Hw4boGpXB5xyNRZoV3Uqy5AyRG1mG/zLhHRP+9TZvSvNVi10wvNl9ujE/sb/b/wodt/R/K/S9Ddfqsay1Fvib0Kbo/bL530INJtzLohigCwZzuoD5rSGoHcDvV8OJ6v2qnfopwoRQB4BZVWJQDjIIFdQ1xPTtZ9q+blD5vK5ymUJY5tun3R67NPdbaNAVvtMDrJD2FQT11Oz/xHY+P/V6G9+V9DI+Hzmnrbo/3Oc/Eh9cecng/qn4wAjO6+EcwWrj9lwJajLvL+UXoXXhksl6EQGYUH2pE6veMfkjwAwheBx6j2O9T2pg1tidFVnJpXh3Hhv+/tvD/oahRni7IPwdGef6dzqP8260Ro6y7L65R8n30gfS7j9NiyTuKR2Mu+sLfdlNdAxUlxbZU/EteTFnVApRHBEDU+2EmBd3lccyF/9oaN98h4+go8gG66YKjBlQltADF8H/zoDlf/l9H0Qs8umXK/NBU9h2N6cUd10bQi90b4poumz5nO5t2n6+hgpQB4i2vxSxvyX+AgE0DrWscTw9zPKf5FyH9u13G87OIy2vfXzXS2jwPGFMK3M3RPdvZdRIzoRckmgZFlvR5P0qmMKNu+0pk0Uok1gD7EBxiOvELPUWoclSxLyx8+DLBwof5MKji22RQQ5Sfp3qzxDwqcbFZQjMlSuOfEB2K5t7/gaRHTNbfH47arzCwGapvmkw4oM8CaPmTW6Xlk/UOZt58ynuV8xC27j3IMhpdgz/8HqN0TUv9WFjzs882P1fi+5fZhy4yDpsacR/YhSK2cIZ3xAbvCoDXoUl46QIv1v4bdL+5/w7fH7X/3red14uhqU2/ciZZvpURJOu0u+Pbg47re/d96nzyGh3LUADgFUzP9xCFsrq3jbtH7PdCfP8xu5fY7Blr+iNt6LidNRBx0swvVNXZ/9UGmC9PQ8edXFDQDrBEuYU4czjr43EPmh3vlg18Poq+ZldcioaO2wS8RQIyabtbfYT+xx+tFdojTxfGHPx15Sr4tfQWSx3Kwofu0B+9HNC+kbpnN/1D3DLZkEcqxrfRIe6jkD/Gi3PRoOiek2Hs1GvTukffA+WNEs5IRLluvR4SOGxvO8Wo4fccbolHeyaTqcmGDpDZHOjkdVRKVdL3S0cKmFxyk/nYICsujeb0FuFhc/rZPif97Nj622O1qO9e67sctdG7MzofQDQr7wQe7s+ki6w1Gxk3sr/pjfvDSTHxHzb3fZnAMYATCXEpsyKrNBWTIDA2J4nrr8tb09fQ66rG5Zy9Owm/JsSBto3586K7I/lz5VvJkP3T0eYF8eANcjRQVlvaSj2A20MRaCc9A4m7iipilcQyacbmi+saGPIN2E3hNk5ZbjNEZkS90nLkIUIY8qDwXKrpyON0QEdWy/tDqlgZMwGtQTVyFkgxKa1MplVUerorU8kHkQtl8dWh1qG749rrR/Ox7n93mfMbGRYVUMw9N9o3BS1Be+PvIKKxfJCfF2oFYyGrQtO2IG+FBKbtS5aXWqCbsXuxUhpDOZ7POGUWtlxLuNtZrh20waeWiC4031x0WBMmIHTe3MscO7WzsYi62II=
*/