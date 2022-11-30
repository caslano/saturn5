// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_PARAMETER_TYPE_OF_HPP
#define BOOST_GEOMETRY_UTIL_PARAMETER_TYPE_OF_HPP


#include <type_traits>

#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <boost/mpl/at.hpp>


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

    typedef std::conditional_t
        <
            boost::function_types::is_member_function_pointer<Method>::value,
            std::integral_constant<int, 1>,
            std::integral_constant<int, 0>
        > base_index_type;

    typedef std::conditional_t
        <
            Index == 0,
            base_index_type,
            std::integral_constant
                <
                    int,
                    (base_index_type::value + Index)
                >            
        > indexed_type;

    typedef typename std::remove_reference
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
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
*/