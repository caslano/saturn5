// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_PARAMETER_TYPE_OF_HPP
#define BOOST_GEOMETRY_UTIL_PARAMETER_TYPE_OF_HPP


#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace boost { namespace geometry
{


/*!
\brief Meta-function selecting a parameter type of a (member) function, by index
\ingroup utility
 */
template <typename Method, std::size_t Index>
struct parameter_type_of
{
    typedef typename boost::function_types::parameter_types
        <
            Method
        >::type parameter_types;

    typedef typename boost::mpl::if_
        <
            boost::function_types::is_member_function_pointer<Method>,
            boost::mpl::int_<1>,
            boost::mpl::int_<0>
        >::type base_index_type;

    typedef typename boost::mpl::if_c
        <
            Index == 0,
            base_index_type,
            typename boost::mpl::plus
                <
                    base_index_type,
                    boost::mpl::int_<Index>
                >::type
        >::type indexed_type;

    typedef typename boost::remove_reference
        <
            typename boost::mpl::at
                <
                    parameter_types,
                    indexed_type
                >::type
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_PARAMETER_TYPE_OF_HPP

/* parameter_type_of.hpp
GDYjMjJ3xPaxY3Wj84ZFKr1hv2+Y+V06Hjew4CK1+fwzprLEAeOnlpgfIpy8H/4dkZczIjdn5HY4It8tnJofikSn4PODdUhBNCRHKqjxlaVOJVRbhsOTJ/hypN7yKp/hHl4dCoamhdzDzYyAYNA9PFBVg6xjm7PjP/fwUG3UwUJGKVThYOGX9S33oeiPjvjD3vsB+LYN/myehPJt6N5R4XUDb85BhsLrLbwtXQpvM/BqblZ5WQbo3HSFt5XImKfysqXsRLXsMBkfH6j6jZR8k9R824NX+rOq307gdX9Q5e0m6yNfqXL3kLIPqTImiX7XqPmKwct9MU3h7S9ll6llD5Y429+qPI/wHlF5PmnHJqqMgOgXUttWLXKjKi8i/faGqkud8GrV9h4jcj9Q850gcndQ5Z4qdl6uyjhL/F7e7qDwzhP96lUZF4mMuD6/XPJ9qfLmyDrzZirveuGtUXW5Rdp7jirjTpGxtVr2XllD7aOWfUj6/Bm1vQvELivUsk9K24KqjEVS1q3me0Ha0VflvSJlN1bPjzekbNx4eVd0nqqW/VB0XqXm+wS84kfVsbFC1k23V/VbJXLjxu73Mv7i7PyztDeklv1dZDyslu2QBp3j5G4ovPROCq9rGnT+QpXRCzxjjVo2E7yGHqpd+oNXeoyqywDwag5ReduAN+daVcZQ8OpHqTqPkPrmqLzRkm+eWnZHkfGryhsnMlarZSdKfXHXsL3AW3KZ2ra9RUbcOVMivN3U9h4kclerZQ8T3g8qr1xk3KnWVwleY4ZaXxV4TV+qZcNi+9/VMT5T2vakWt/R4BU/qJY9Xvr3WNX2pwivpyr3TLHLnqpdGqR/DZV3IXjz5qv1XSZlT1b1u1ryxdlgrrRjC7W+m8HL/Vxtxx3grVqi5rvH7F+1vgfFpher16tHxX5x16YnJN8BKu8ZyRc3DhZLvrjz42XpoztU/V4X+/VT5b4DnvsqtWyT8CKqXT6WMXS0ar/Pxc6vqGW/kv69SdXvOzkvL1br+0lsOl/V7zexVdw10ZWOssWqjM7glcZdmzYBr+ZGtW0909GXb6i69AHP/Zvajn7g5b6i8raUfO+pugxKR3sfV/Ntm4729lZl5ErZuHZsJ/o9ppYdK+2Is9WuwntKbdsE8Joa1foKwFtyt2qXIvCKr1Lz7Qde90Uqb4rIiOvLQ8FDpyi8Mik7U9VvmpQ9W9UvKLq4Vd4R4K1aoJ6rM8QGcdfno6SPXMp13PpoY52a72Tpo7jniDOkP15Q5Z4LXuNolTdbeOerZS8VW8WNjaukvXHn4HVi+zy1HTeJ3BLV9reLfnHXiLulvXH3lAdkPK9Uy84XuWF17D4uOvdSeU+LLv1VGc+LLgNU3hJp2y2qDV6TfBur+d4WuS+pbftA+iOu7DLJd4JadrmMA5+a70vp803VfN/K2HhLzbda2va9aoNfpW3bqfnSXahvkFpfJ+EdppbtAl53Q83XA7zSndU+zwCvcYTaH5tLfVWqnd3g5caNZzzS4SOfan1DwFvyjarLcCn7kFo2D7yGuOvzDlI2rj92Mdum6jde2hZ3ruaDV7yRWnayyHhalbsveHMWqrwDwWtaoPKmStm489LrkmdlNV+F8C5XbTVdyi5Q21YjtnpVHVe1YpdtVBlHin73q207DryaPmq+kyRfqVrf6WKD3VXeOeAZce8kF4j94t5xLhEZS1XelVK2q1r2WsnXQ23vjeCNu0XNd5vYZYHajrtEv9PVfPfL+Iu7HjwibRuntqNRxsY8Vb+npL671P54TuqLuz6/JP3xkFrfUskXd117S/J9pcp4X/I9orb3I+m3uGvOZ3Jufary/mDv/OOqrs44fkEwbFo=
*/