// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_FORWARD_OPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_FORWARD_OPRIMITIVE_HPP

#include <boost/config.hpp>
#include <boost/serialization/array.hpp>

namespace boost { namespace mpi { namespace detail {

/// @brief a minimal output archive, which forwards saving to another archive
///
/// This class template is designed to use the saving facilities of another
/// output archive (the "implementation archive", whose type is specified by 
/// the template argument, to handle serialization of primitive types, 
/// while serialization for specific types can be overriden independently 
/// of that archive.

template <class ImplementationArchive>
class forward_oprimitive
{
public:

    /// the type of the archive to which the saving of primitive types will be forwarded
    typedef ImplementationArchive implementation_archive_type;
    
    /// the constructor takes a reference to the implementation archive used for saving primitve types
    forward_oprimitive(implementation_archive_type& ar)
     : implementation_archive(ar)
    {}

    /// binary saving is forwarded to the implementation archive
    void save_binary(const void * address, std::size_t count)
    {
      implementation_archive.save_binary(address,count);
    }
    
    /// saving of arrays is forwarded to the implementation archive
    template<class T>
    void save_array(serialization::array_wrapper<T> const& x, unsigned int file_version )
    {
      implementation_archive.save_array(x,file_version);
    }

    typedef typename ImplementationArchive::use_array_optimization use_array_optimization;

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class archive::save_access;
protected:
#else
public:
#endif

    ///  saving of primitives is forwarded to the implementation archive
    template<class T>
    void save(const T & t)
    {
      implementation_archive << t;
    }

private:
    implementation_archive_type& implementation_archive;
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_FORWARD_OPRIMITIVE_HPP

/* forward_oprimitive.hpp
SSaG0qGPL2xpU7ZdhcnAOs+y0fPbe/Gyno8C5fptU2RhLZEyfWPZsxrrBhyIy0u4YnbZIEtpw/iqhXJoKcyGc8POLquJS/uBVtc9xA9L1R5tXFD4aKFRDraIBhLXkE+EPMbcsNMPZQ1PYw7pBT6OL00t7slj2qCq0KYBB0plDHlWYpT9VhusboVEa8mWVDHQlJH+cv+jJTYuaDK7/m+/AVBLAwQKAAAACAAtZ0pSsqCvTHgCAAC8BAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NjFVVAUAAbZIJGBVVE1v2zAMvftXEOllA+pk58IzUAzrVmBDCzTdDsMOqk03QmXRk+R0+fd7lOW2C4LE/HjkE/nkJnFMnYncVo31g+DviU/PEvrYVnV9YDdVze7V1eyWrOqsOqM7DkcOdbQ9V03gyZ00oTzkjE/Osk8lo8sGUmLGtZUXD/duNanxZgSRbg6O7DhJSMYnKiyo2S1hajoZR+P7NwRfPHgsXXL/HxzscKLeJENmSBwoHZj0zHQwkR6YPW3iQdKmao45FyU4BAmd9Oj1AQXfmE1MvcyJRlgfN4n/pk1b3UfzyBeUWf+SKVnxcbvd/qYGHtCt+3OcIVNo9Lcloq/7/S3d3tztMzXkDJoz
*/