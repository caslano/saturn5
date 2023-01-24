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
1cXAqoeitbmDQ3R+QxLObJHpxzXNZ5vdWDXtzYiXp7zHdBHtyXfHewFCDlXy+NuMBRApdrrnUjNzd0jMVqa1dOIWA+0xQm1/9G8+W3WjlQbOK+/WapurrReQGzc1fZfnM70iup9j9p0b0P2gfFHTgy9l4ccx3HVe16Hfz9y087aJ5YMHpX1vMXctuu0sDW3YdWZ5kjR1PQu34I1OPZg7Ed1m5o5Fd+vz+kmhE+xILr7I50tn+eM9Tb4hzJ1JOv1zOj7v/7fx3vW6alXOWGIIKWccHhiyYUkizfc0ywDHhSjCFaqIhqr87BZtk1zVfLZBxmZv/1XbnAnTktByWElqiFKaznl96JwntzjnoJESSvKIbD5btUNJ676/qlaj0ooqXW5/c4iumX+BuYkALq7XmpFu4id+panHJmXj40uayu1tEQPxoUnJ+NVU0lhi5gCYbmdhgU3Cu4fNB36n2R1D5YWzUd9CKUp/oXy8+JHcy6Uu6QX6eDbwoDWxqk7ivVRawneE1BStLuFpKzNwCQ8F4rSBK3gohS248VGghhq4z29iSlHC6bnBTClGiDw2OIR6MIgPN6npaLbFCkboLfb6lAi1qawlFyl+DWHz7OLglpiPLRGltsQbN2vKjKCWMDVsiUBlRmBTNFJGVtwY0BSPp/2D2jej71iiciYhNGe65caQYhotPT5fflEzhnjppC67Dt2gmzquOHmxOSPT
*/