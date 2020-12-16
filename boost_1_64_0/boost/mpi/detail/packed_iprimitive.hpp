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
YoJrinAqxz36pploH34s+/SONOY/1c1mPDot66lKh/XAT7sFvBCPmOmuGemyxiXKpHQR++yXM81LdIeCqZjOfQDuCer1EfrvE1zLDo+JvDvVtIi6M3wQn8zF6wp6ZYzta+kBDrOWc3iW7LVTNbBwbNYzPQ1sYDNBQxB+koaBB8lVeVAax1gMkv1EaSz9Ak0EjHF/7QOb6EsJGDAg70CbhnnMAZNjw0gjAi4PgXHjbnWAfQ7+MUitRSf5ygNej9m8SQ6wl8DLvpprclyhIx1oc0YH/BrtEAf8PW6zj3MJnnslKFsIuRWBPI/ZWp8D/iqIIF/N1DxyDt1FPUndKQ0D6HNhdGegSNc1axPY3D7UYsdwYetf4bD8jMb5whK3P5pBD5/sqt1SdXJg/G/7SuVFhEAmoSxUhQOkpqHxAqlNVlp6L8NNzSssz+eBb01d1hcD3zqW0ZW1ihElD65GmdTTq7b2lWb27m6P8K1MTnylcNCNZqCqQnCzjwB4ITjHZfZyAZ9Ds3u5YHSgVH/5S+/rXvOEv48upkNrA6Op79fv2NRnjA6M0WWvpylWarMsqFmBc92WoFAVwfE09wzoQBX72Vr67fuJtpf01PYStUxWzWFDW0vUcc1Iod6Jb/9N5fP7PleoL+zuo94A9zuNPzkOU6GXdi5Ubqqp5Xh59eXdK9uEVd9zKVyf0Vl1KHiIeDSeRZIiMoFOveXwFyLqO6tTGwWZ+lgTESEgAPSdR0cBbIVANYhDH9WgOQKaU6E6v3CC3qcBcgUgt0K9FgVQxzx+syY9mCPzytXg90zC9W4ozhMvFO+GYfl4EukQOj2wQJcCfeePhmDJq1CbhNk4oADxYomXwKWzDyV8aEx+fXF+2KffjPpiY6/6+av+0PjUVNOp90NVShObkH287eKjbRfaTMS938ezKTacQ0Ceqv78GTQmybJ/SYAbGMYFyD2aYu35Malf1Hm8rZ7o94LofDWWbBDlUXsVddhDIaC4+L3Qf5Ni96fU4a9HOh02LdHLbONi3ucRp9rYC+uDQ0QHJOhXQFk0H5PZxMu98IUfWUwXdPqXLxGCJllf7JVH0kzri3P0M9nmffrZV1+cS8QOsTgFKUaDl6prKGaygKpoNAChUV+RD+uEgezk+mEFOntDkVeYRl7L1WzZiKL97pHJ/QxJH61ulIkC22QGbBpX6PwKNVlntu9H+lK5xFXR47cx6UvGTwXe4PHWFuPXDoqx+cZf70x2w97bUEqLga3gVR88MbykAEikeZrZccOCF3PXMEoBsw5m5p+W75qRT/oYd6kwurhHEu+S61kjrmDCawG5qDXyYe9mFlvNpp4mEaSXYtrzdqkr+Xu9n3c6vve93nG+N47/gwv6Zbz1Xaspiza4QPYbnnMa0rZ4TNv3IMSZkrufztoE6W/vpC/3mKr6CZIjayDOuYVy0GN8RGaUm/AXv0fDJT1ersa9qtc2GSz6DoSV1VdvhENUyNpT85FdVQNOz2BJ56nZ6IX0CZ9lbZd7mVisXTOf7MEv22RrZKke0zZ24y5ty+sRhUz8Yugvo6MJYCC42UAAw4irWpaV/GiVM1DOakION0Gmo1YxGPzmFbv+6yFAWstVmqN++epsfDU1HOplDhcVEqQF2yt6C0tXWoRKW+5m7vTonmzdpMEKgn6z89RnryNRFrCd1IQkfEBbOuFi2VzzDM8b9Wnh84MpuqfvshCdGkyTzyFTbSyix1xAlBTqRX+7Ebqo0dOvyXgNgoLor4ls+8FR3eoJT0GfagpwC44xJtlUnSXlxDWmthUNga442B6vdtIEY7H2AVbdFA+wEgvwrMPEHfKDrlOfjVh0PWwLnr/xqDb778fa75o=
*/