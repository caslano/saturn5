//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEXER_TYPE_APR_20_2009_0759PM)
#define BOOST_SPIRIT_LEXER_TYPE_APR_20_2009_0759PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/has_xxx.hpp>
#include <boost/spirit/home/lex/domain.hpp>

namespace boost { namespace spirit { namespace lex
{
    template <typename Derived>
    struct lexer_type
    {
        struct lexer_id;
        typedef Derived derived_type;
        typedef lex::domain domain;

        // Requirement: l.collect(def, state, targetstate) -> void
        //
        //  l:           a lexer component
        //  def:         token definition container
        //  state:       lexer state this token definition needs to be added to
        //  targetstate: an optional lexer state the lexer should be switched 
        //               into after matching this token 

        Derived const& derived() const
        {
            return *static_cast<Derived const*>(this);
        }
    };

    template <typename Derived>
    struct primitive_lexer : lexer_type<Derived>
    {
        struct primitive_lexer_id;
    };

    template <typename Derived>
    struct unary_lexer : lexer_type<Derived>
    {
        struct unary_lexer_id;

        // Requirement: l.subject -> subject lexer component
        //
        // l:   a unary lexer component

        // Requirement: L::subject_type -> subject lexer component type
        //
        // L:   a unary lexer component type
    };

    template <typename Derived>
    struct nary_lexer : lexer_type<Derived>
    {
        struct nary_lexer_id;

        // Requirement: l.elements -> fusion sequence
        //
        // l:   a composite lexer component

        // Requirement: L::elements_type -> fusion sequence
        //
        // L:   a composite lexer component type
    };

}}}

namespace boost { namespace spirit { namespace traits // classification
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(lexer_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(primitive_lexer_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(unary_lexer_id)
        BOOST_MPL_HAS_XXX_TRAIT_DEF(nary_lexer_id)
    }

    template <typename T>
    struct is_lexer : detail::has_lexer_id<T> {};

    template <typename T>
    struct is_primitive_lexer : detail::has_primitive_lexer_id<T> {};

    template <typename T>
    struct is_unary_lexer : detail::has_unary_lexer_id<T> {};

    template <typename T>
    struct is_nary_lexer : detail::has_nary_lexer_id<T> {};

}}}

#endif

/* lexer_type.hpp
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
*/