/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_PARSER_OCTOBER_16_2008_0254PM)
#define BOOST_SPIRIT_PARSER_OCTOBER_16_2008_0254PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/has_xxx.hpp>
#include <boost/spirit/home/qi/domain.hpp>

namespace boost { namespace spirit { namespace qi
{

    //[parser_base_parser
    template <typename Derived>
    struct parser
    {
        struct parser_id;
        typedef Derived derived_type;
        typedef qi::domain domain;

        // Requirement: p.parse(f, l, context, skip, attr) -> bool
        //
        //  p:          a parser
        //  f, l:       first/last iterator pair
        //  context:    enclosing rule context (can be unused_type)
        //  skip:       skipper (can be unused_type)
        //  attr:       attribute (can be unused_type)

        // Requirement: p.what(context) -> info
        //
        //  p:          a parser
        //  context:    enclosing rule context (can be unused_type)

        // Requirement: P::template attribute<Ctx, Iter>::type
        //
        //  P:          a parser type
        //  Ctx:        A context type (can be unused_type)
        //  Iter:       An iterator type (can be unused_type)

        Derived const& derived() const
        {
            return *static_cast<Derived const*>(this);
        }
    };
    //]

    template <typename Derived>
    struct primitive_parser : parser<Derived>
    {
        struct primitive_parser_id;
    };

    template <typename Derived>
    struct nary_parser : parser<Derived>
    {
        struct nary_parser_id;

        // Requirement: p.elements -> fusion sequence
        //
        // p:   a composite parser

        // Requirement: P::elements_type -> fusion sequence
        //
        // P:   a composite parser type
    };

    template <typename Derived>
    struct unary_parser : parser<Derived>
    {
        struct unary_parser_id;

        // Requirement: p.subject -> subject parser
        //
        // p:   a unary parser

        // Requirement: P::subject_type -> subject parser type
        //
        // P:   a unary parser type
    };

    template <typename Derived>
    struct binary_parser : parser<Derived>
    {
        struct binary_parser_id;

        // Requirement: p.left -> left parser
        //
        // p:   a binary parser

        // Requirement: P::left_type -> left parser type
        //
        // P:   a binary parser type

        // Requirement: p.right -> right parser
        //
        // p:   a binary parser

        // Requirement: P::right_type -> right parser type
        //
        // P:   a binary parser type
    };
}}}

namespace boost { namespace spirit { namespace traits // classification
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(parser_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(primitive_parser_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(nary_parser_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(unary_parser_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(binary_parser_id)
    }

    // parser type identification
    template <typename T>
    struct is_parser : detail::has_parser_id<T> {};

    template <typename T>
    struct is_primitive_parser : detail::has_primitive_parser_id<T> {};

    template <typename T>
    struct is_nary_parser : detail::has_nary_parser_id<T> {};

    template <typename T>
    struct is_unary_parser : detail::has_unary_parser_id<T> {};

    template <typename T>
    struct is_binary_parser : detail::has_binary_parser_id<T> {};

}}}

#endif

/* parser.hpp
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
*/