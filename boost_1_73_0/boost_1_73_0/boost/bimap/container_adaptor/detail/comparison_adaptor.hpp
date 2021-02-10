// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/comparison_adaptor.hpp
/// \brief Comparison adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief Comparison adaptor
/**

A simple comparison adaptor.
                                                                                    **/

template < class Compare, class NewType, class Converter >
struct comparison_adaptor
{
    typedef NewType first_argument_type;
    typedef NewType second_argument_type;
    typedef bool result_type;

    comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}

    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x,
                     BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type y) const
    {
        return compare( converter(x), converter(y) );
    }

    private:
    Compare     compare;
    Converter   converter;
};

template < class Compare, class NewType, class Converter >
struct compatible_comparison_adaptor
{
    typedef NewType first_argument_type;
    typedef NewType second_argument_type;
    typedef bool result_type;

    compatible_comparison_adaptor( const Compare & comp, const Converter & conv)
        : compare(comp), converter(conv) {}

    template< class CompatibleTypeLeft, class CompatibleTypeRight >
    bool operator()( const CompatibleTypeLeft  & x,
                     const CompatibleTypeRight & y) const
    {
        return compare( converter(x), converter(y) );
    }

    private:
    Compare     compare;
    Converter   converter;
};


/// \brief Unary Check adaptor
/**

A simple unary check adaptor.
                                                                                    **/

template < class Compare, class NewType, class Converter >
struct unary_check_adaptor
{
    typedef BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type argument_type;
    typedef bool result_type;

    unary_check_adaptor( const Compare & comp, const Converter & conv ) :
        compare(comp), converter(conv) {}

    bool operator()( BOOST_DEDUCED_TYPENAME call_traits<NewType>::param_type x) const
    {
        return compare( converter(x) );
    }

    private:
    Compare   compare;
    Converter converter;
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_COMPARISON_ADAPTOR_HPP



/* comparison_adaptor.hpp
SlKYJqkJzgMAAJkIAAAlAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9wb3AzLWRlbGUuY1VUBQABtkgkYK1V8W/iNhj9nb/iG9M0QDnS9qRtd+WqMWBbdT1gBFQhVYpM8qXxlsQ524Gi9f73fZ9JBqfbxmm6QOvE8Xvv8/Oz8Xtf7mpBD85eofsL6aLWIeZa/Y6R/efRYfgMhw+hHqg9J+LDEfIcduE85Bk6DhLWKgO+D8NzQg9cG//zGfkQ8i31EIyRI1XutXxMLXRGXbh89eoHeAFXF1cXHoxFITGDwGKxQf3owSB2PT+m4umpb/DGA7Qgsn5NtUylAaMSuxMage4zGWFhMAZhIEYTabmhB1mATRESmSGMZvP17fQXD3apjFIm2asKTKqqLIZUbBE0Rii3B45SaAsqITiRx9JYIqysVEWftBEs6twwB8uLzCgQWyEzsSEhYSG1tjSvfT+qdEbV+7GKjB810++nNv97JmsqIhd7UKUFq6Ay6AGP9CBXsUy4JUOos6w2mTSpd6yGpIrYVxoMZhlzEU6iOZSNENT2eDwMSqpYWm6MKgxL7VKVfzSQfGSWpNIFCZEPNChWZLMHVRGjdoPdzBuJ2lNn8L8uzbHeGFRBxUB7GMBt0IaNMNJ4cH+7/HW2
*/