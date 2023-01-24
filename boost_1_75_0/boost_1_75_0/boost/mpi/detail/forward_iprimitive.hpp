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
rcFxdK4Oe1unC5/O1ngQpYvmRsltwplMZyu6tS399tcOcYQeYdC65HPytX2dw8EGg2L6ykf1ejmTKMLNs4qGDv4Xl8LZ0lOnYLLKPaG+Q24VMjVkQ/dqf6RO4zIpIjPSs3wudRk47p+Z4CJW082eEVThbLvalHWkwriiV+n8+UYmexYyc+iCty1VYB3nzWQwVGtT6EQpCxA5fTYPHt639UtyomRnXd3R6af9Q92awzGcN2eVDLBrslDPtuhq9RslUin3qTol230DlRhOfDoUEYDsM8A8VnUqnTeazv/GCKz3Xxqf90h2Hmjrzi27sxC62aM3ODGwgQ8vZU2NJ9dLtHbEopfOH4XWtJ3ogqAj59miiG9bhh6tTHGiXRauQLwTTJ9soTuBUKHA3uyDXBpwSiCPRuRLUrYrwO/0DtTYuQG1o9kPdFlo2/2j8bGe8uwHGKSwEjAPr+BYaxhoQUQ3oYPM9Db8dEcvzvrbkHZ4P9pbspOrqFBOAqwfvgFYzb8diMY9jtGK+q/jPyyLfh7ntDryz9uor/GXTjtdJ/fhJqX9rFA6W22r0+OpaT8784Gd0A23JW02IYfaReIreKJWmZIXTDFo9TVonE7C588a6+CT+LAylp+e9woW4TRHJDRlNrEpbWrCZd1jm+JJ511huj3/NjS0/HdjUp2y+SF4wRZ5dLUjMX4UoQMj/yjO6pfLhjsTSCA3AKohaEtB
*/