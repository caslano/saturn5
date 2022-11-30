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
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
*/