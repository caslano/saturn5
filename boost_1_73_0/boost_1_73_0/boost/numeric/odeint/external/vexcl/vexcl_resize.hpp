/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_resize.hpp

 [begin_description]
 Enable resizing for vexcl vector and multivector.
 [end_description]

 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky
 Copyright 2012 Denis Demidov

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost {
namespace numeric {
namespace odeint {



/*
 * specializations for vex::vector< T >
 */
template< typename T >
struct is_resizeable< vex::vector< T > > : boost::true_type { };

template< typename T >
struct resize_impl< vex::vector< T > , vex::vector< T > >
{
    static void resize( vex::vector< T > &x1 , const vex::vector< T > &x2 )
    {
        x1.resize( x2.queue_list() , x2.size() );
    }
};

template< typename T >
struct same_size_impl< vex::vector< T > , vex::vector< T > >
{
    static bool same_size( const vex::vector< T > &x1 , const vex::vector< T > &x2 )
    {
        return x1.size() == x2.size();
    }
};





/*
 * specializations for vex::multivector< T >
 */
template< typename T , size_t N >
struct is_resizeable< vex::multivector< T , N > > : boost::true_type { };

template< typename T , size_t N >
struct resize_impl< vex::multivector< T , N > , vex::multivector< T , N > >
{
    static void resize( vex::multivector< T , N > &x1 , const vex::multivector< T , N > &x2 )
    {
        x1.resize( x2.queue_list() , x2.size() );
    }
};

template< typename T , size_t N >
struct same_size_impl< vex::multivector< T , N > , vex::multivector< T , N > >
{
    static bool same_size( const vex::multivector< T , N > &x1 , const vex::multivector< T , N > &x2 )
    {
        return x1.size() == x2.size();
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_RESIZE_HPP_INCLUDED

/* vexcl_resize.hpp
UWp3kD1K3Wx6Wa16s+Vkuz35X1K9dN+wdV/ZUo+A6zN7Brw+s1dAfnSf2TsgfVmfgGvr7Zy/pf/rGPD6zNOYpq9G08NH059p5N4u2CXTnBGo/7goJwRxPInMcPp/ltb//7h82Las0tM0XNJ9uAwIyI+OSwbzm6n18SxfHzv7cBnENIM1mjQfzRCm6cy4DGWaYYF6+dfhYkkoNz0vfbgXFjedx44cre8jAol8WoVYoLJvSVNK5klhn3aOhus5Wt0=
*/