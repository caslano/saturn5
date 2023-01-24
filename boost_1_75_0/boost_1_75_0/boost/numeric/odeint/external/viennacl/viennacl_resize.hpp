/*
 [auto_generated]
 boost/numeric/odeint/external/viennacl/viennacl_resize.hpp

 [begin_description]
 Enable resizing for viennacl vector.
 [end_description]

 Copyright 2012 Denis Demidov
 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED

#include <viennacl/vector.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost {
namespace numeric {
namespace odeint {



/*
 * specializations for viennacl::vector< T >
 */
template< typename T >
struct is_resizeable< viennacl::vector< T > > : boost::true_type { };

template< typename T >
struct resize_impl< viennacl::vector< T > , viennacl::vector< T > >
{
    static void resize( viennacl::vector< T > &x1 , const viennacl::vector< T > &x2 )
    {
        x1.resize( x2.size() , false );
    }
};

template< typename T >
struct same_size_impl< viennacl::vector< T > , viennacl::vector< T > >
{
    static bool same_size( const viennacl::vector< T > &x1 , const viennacl::vector< T > &x2 )
    {
        return x1.size() == x2.size();
    }
};



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED

/* viennacl_resize.hpp
lTI3TbDPVDWn7w95eU9ll5ByNfVrSlNFWFp0CG1KqCJYU/A3MLxvI9jSjkbOkbjgkcOepwggw49G1mvGARtG6tPxi8yNj/j6Flyjn/id+ZFOth261mvCpZCsaIPqUhednGuYmw5lffMvRSPtw130naO9XbTj3L4pwxXl7+Zf2/CAw7P0xYDhiob15EzdGLULC6fh3y4gTRhzM7tZu47RhdP6TRS/Mzdhd5ClobJ2s3vyqPa3ZJK6mcwtBjA3penN3DRIu2SSeprMQtoxN5mXLHurVjOFPDf6kua+4wG8XJq14ncsnGTPg6N11fxOlobqUjo6QIe+CmYtbBnfxgWKsjcgOF5+aQEOiAb3KrHEyjw1Mbt52SDF0nvhQFPxDm/MRpdCUrqE50UycmTLPJZTMsuJvsDbm4zq7U2BJSxZGC+4OjqkjAIm6PM8piwMwEYfDh6cdZEroBwQBU4ItScuTc2d/eBxZ3SlHVsd3333XyPPW4FtAAk8USx5dpQ8HcM8cfLvK1juwRO0hspMvgDJJnI6EtAwwRyl4WzD3xhdMuQnB0xKzg6iFPOFAx8Q+dyMrxjvd0SwAVmhptunpfvYEcE3vXcaixul26Slez0g3csB6dhbQUuGvEApAbvuqyhlW+QZbdgXorsnYDGXf0XP9vD8XVr+UwLyv7tR/pCgJyrQpTujlszvLLhucKAo5DW3u4teS4kEIE/7Ce88
*/