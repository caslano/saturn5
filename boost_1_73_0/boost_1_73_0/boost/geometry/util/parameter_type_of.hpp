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
UfTz24FTVzbW+dvbhspo7/qVoZZZ0CCzLc6O/9wdQtliATC2/UuiRnH2uIR7NZsjCrkFOMyXJUD36GNS7rRUsZzP80X5YNvpT481TeG+FTiWntW7QTc67f3UO+k/d5cwzp5zrWSaTgB5TWBR4x2s/Euv/93zCOq3tg521XyRl3l5Nwd8BrMj4LxNM6gAPURlHsXFKE1hUgDEl3k+bawxgvsPa7qOF2o3zdry2y4srHUo64AnY9edrvIvBnQ8jssYb4X9CCexGMlF0d9gorNqzVk6S/wvN+W0OMB/+Z+v86JM5/63chFnxSRZ+F8LmPbE/wTbdYXowv86yvOPaTA6oKdRXFQ/Ehj4X+FliefVmmX+MfgGe5qEI2fwupVRko0AsWdXwVLhxYjG6VVSlDUFWXKVl2lchiMnUyASgs1dTss0DfYiiYu78FsxT5Lx6DoZBVMHtJ1NK/uW5dkegY//Ge9fNC/hWfQ+XyEenOT+R4AaQCh7aRbMGC5lmcwYUoO1FyVNA6G/A29Ylt8S7OPTQ7dhlE8LhE0H4soAXsZpuENlMiWs4X2rtMN9r34JJkjvnn/KeOngdgRtb4ri+gD+CXZvFtZDeiGEmqxyxrTrWZnXTBA+T2c1U1qUs6D2VT6/Dq/R7J9lHfjBXn+6
*/