/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_copy.hpp

 [begin_description]
 copy_impl specializations for vexcl
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< typename T1, typename T2 >
struct copy_impl< vex::vector<T1>, vex::vector<T2> >
{
    static void copy( const vex::vector<T1> &from , vex::vector<T2> &to )
    {
        to = from;
    }
};

template< typename T1, typename T2, size_t N >
struct copy_impl< vex::multivector<T1, N>, vex::multivector<T2, N> >
{
    static void copy( const vex::multivector<T1, N> &from , vex::multivector<T2, N> &to )
    {
        to = from;
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED

/* vexcl_copy.hpp
cfx2q3ICz5FImd5C/A7LhCyyoMv01jjGq+OqU/X5vi1uGSAPNcHfzm1eNuPB4++weDGMvzNuxrzvpA38vPr2u+J2vxkw+8ZPgqO9O0728qDSVPHfE3c65cBeDKTa4r3Cz1HQOOVt9e8z+Br6meEKqMbP++O4NnM2Qa1R033yAU0rVJHoaR+ME4fAWYuPLOg0H4o3Ko3y6UJFzZ0Px8k+b/Yx3KDCoCTOR+Iki7XWUaqij5VK
*/