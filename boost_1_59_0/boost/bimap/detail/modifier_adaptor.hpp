// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file detail/modifier_adaptor.hpp
/// \brief A binary to unary functor relation modifier adaptor.

#ifndef BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP
#define BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

namespace boost {
namespace bimaps {
namespace detail {

/// \brief A binary to unary functor relation modifier adaptor.

template
<
    class Modifier,
    class NewArgument,
    class FirstExtractor,
    class SecondExtractor 
>
struct relation_modifier_adaptor :
    Modifier,
    FirstExtractor,
    SecondExtractor
{
    typedef NewArgument argument_type;
    typedef void result_type;

    relation_modifier_adaptor( const Modifier & m ) : Modifier(m) {}
    relation_modifier_adaptor( const Modifier & m,
                               const FirstExtractor & fe,
                               const SecondExtractor & se ) :
        Modifier(m), FirstExtractor(fe), SecondExtractor(se) {}

    void operator()( NewArgument & x ) const
    {
        Modifier::operator()(
            FirstExtractor ::operator()( x ),
            SecondExtractor::operator()( x )
        );
    }
};

/// \brief A simple unary modifier adaptor.
// This modifier is equivalent to bind( Modifier, bind( Extractor, _1 ) )
// It may be a good idea to start using Boost.Bind instead of it.

template
<
    class Modifier,
    class NewArgument,
    class Extractor
>
struct unary_modifier_adaptor :
    Modifier,
    Extractor
{
    typedef NewArgument argument_type;
    typedef void result_type;

    unary_modifier_adaptor( const Modifier & m ) : Modifier(m) {}
    unary_modifier_adaptor( const Modifier & m,
                            const Extractor & fe) :
        Modifier(m), Extractor(fe) {}

    void operator()( NewArgument & x ) const
    {
        Modifier::operator()( Extractor::operator()( x ) );
    }
};


} // namespace detail
} // namespace bimap
} // namespace boost


#endif // BOOST_BIMAP_DETAIL_MODIFIER_ADAPTOR_HPP

/* modifier_adaptor.hpp
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
*/