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
il0x9h6gP6LG4oxqouJM1LvgX8UQc1zE6ifb4ul4JGQMB5EBUws4SB0aXd9W7BUrUfEbplbQFadqrDqYWAhvgwGQ+Jvba5Dgg5iA9ogonR95siw6/FSohfTnHJZCu84i0UTs5xryEBG+AUUi4gzd5M/BFdY/UxottAh93Z3at8ZHdJgTSWDt9XHhT/bW2Rh6XU+9hFU9TeUj0AIP/7aRu48/zwtHzqtbRwNhxc/JMJORgWX3V3jImMD6CDbAFHaRjzvukrIEuHAXWma+/qFFuLKlf6AZN99EffikvNn9Fz+XV9P0Gs0awqv2RZB7RIuMMmGYAwVoVitEgElHMN1u79a/Xr4VGB+TB1g+Xoe5lD4YhPl53sElJpZkr/64cZSv+9JVTHSrrcRAkHWyJvNPq8/2TKqLq+TJkPNuQUHIZqskOgHMjwZj0DYAD+0t4vXlsx4pS+aROL+01uJEVCv/MBDywzo+UVAFkX9GA6ZmBn5JOEfyBmaYDQBGGBrwMHClozvM5V9CfDGgFHEkHpBio9L5hp763wgYOYH5QqyJBd9BcX9xExVkdcdEcA==
*/