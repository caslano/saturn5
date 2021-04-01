// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#include <boost/serialization/array.hpp>

#ifndef BOOST_MPI_DETAIL_FORWARD_IPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_FORWARD_IPRIMITIVE_HPP

namespace boost { namespace mpi { namespace detail {

/// @brief a minimal input archive, which forwards reading to another archive
///
/// This class template is designed to use the loading facilities of another
/// input archive (the "implementation archive", whose type is specified by 
/// the template argument, to handle serialization of primitive types, 
/// while serialization for specific types can be overriden independently 
/// of that archive.

template <class ImplementationArchive>
class forward_iprimitive
{
public:

    /// the type of the archive to which the loading of primitive types will be forwarded
    typedef ImplementationArchive implementation_archive_type;

    /// the constructor takes a reference to the implementation archive used for loading primitve types
    forward_iprimitive(implementation_archive_type& ar)
     : implementation_archive(ar)
    {}

    /// binary loading is forwarded to the implementation archive
    void load_binary(void * address, std::size_t count )
    {
      implementation_archive.load_binary(address,count);
    }
    
    /// loading of arrays is forwarded to the implementation archive
    template<class T>
    void load_array(serialization::array_wrapper<T> & x, unsigned int file_version )
    {
      implementation_archive.load_array(x,file_version);
    }

    typedef typename ImplementationArchive::use_array_optimization use_array_optimization;    

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class archive::load_access;
protected:
#else
public:
#endif

    ///  loading of primitives is forwarded to the implementation archive
    template<class T>
    void load(T & t)
    {
      implementation_archive >> t;
    }

private:
    implementation_archive_type& implementation_archive;
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_FORWARD_IPRIMITIVE_HPP

/* forward_iprimitive.hpp
ReWPd6FCaCmDVxI2yf6D390KDPypLSE+YNY/EBofaMbhaMRaKbXMz7on7dEBlCRcJmUoy0nMsFDDN5JWlNk43/mayEPCE/5H/D/I+o/YuZ7y48v3ANT0kpBjaEYT+kNOxnB2Tgm9bTtONCzHjshGUcK6MPMLtwJ2fzbl5XXSS6cj+dYnrLsLKmI1A+r3fKGoXxFka47mWGZIiQuLQhjgaUWerXauV2o5MKmLOse8BhmrvJGxanVZprH4LYA87GtgzU+pn9y0bL384LparheTjyzO8bYhZkSsxkI+/+TKqGufBsS6i/q4JvR3lGtnZtEPzvwCKOjyHPJDQPuIWZNfevqCUSx6yTU8poHE7rkD+IcHscOK5JdwV73PyTAdVzwshWA5SBcNhqHDAqz0ZPo0Hj/twjyU4oX28RYsjI2IyUhCqzFOJceuAZXs1511MTfNG1shFOajW1fjZ4qKLyMKkwOD68KDT1ybkCdf/dXJbcgWMxT70BKgLaQO9Z7f4tuwRq3Bx35enCdt8BYyskfLeCqux7UGQuxBwxo74FoAPM5plFXhns8KycxQaQ==
*/