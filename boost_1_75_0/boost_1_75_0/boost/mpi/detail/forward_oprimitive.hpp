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
hvrOnmmGRK/2cqgXegHTRCJ7smLjHX7xOJoMoZxYYm41h2InO2Lr7LkvFbBWVk/SOw0vUesWYmKWAMnMME+AFy4sK0M0OYkV58GuyPt4uyZx5PplaEeMRa7+d6ezYbmblySetSzZF4DhLtRN8w8Dno8fzvqolIBPL8Lia9vEqClIUQCkwUc/nRExVrGSNJ7TwBxZMd3k3ifDbZ56NpSqnpsz0f2X3U0JqfRhUf9TfRwtq+s075bWbI2SC/rNL4/8bRrjbeSR04e0WQWaUtgriej/OUxJWw84hqE5iWH/d7XyH3jndBvTsec3C7ZHE816sXiXRw+st9s6DvahteeDvU9LEfepp6WADZ/IUytjorvM1La4VW0ql78hPLNTIZF3UWwew21zMu2aYVktDA3x7VV70B9qN6ryvjYbuScr7XGGfV6SvN7sm3wbAg0hGvyJzKaFbD/+XH8+cyHwqW2c5pldK4sgig94L+GFyqlhOhq/eHkrmJMTwWmh9NTnUxOtke016bcQNcvkL/Qt0jWXkNG8LMmfe49Hg+Sye2G0/SRgu1KBFTFzhXeFd4mHjkXFXsaiVVAqVzXiDsbuxvY5FZztqutWx0qnIyesh6xHrKelh7WX/Ff8l/zoelT9lfBtph+GX5CftF+PH71fvh/ID+733i/R79j6eLImf0c+I1aA2kF4CTLjMgN239jfmIzPz5cfiN0K5HgMVYXI
*/