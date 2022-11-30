//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_REFERENCE_APR_20_2009_0827AM)
#define BOOST_SPIRIT_LEX_REFERENCE_APR_20_2009_0827AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/lex/meta_compiler.hpp>
#include <boost/spirit/home/lex/lexer_type.hpp>
#include <boost/spirit/home/qi/reference.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/ref.hpp>

namespace boost { namespace spirit { namespace lex
{
    ///////////////////////////////////////////////////////////////////////////
    // reference is a lexer that references another lexer (its Subject)
    // all lexer components are at the same time
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename IdType = unused_type>
    struct reference; 

    template <typename Subject>
    struct reference<Subject, unused_type>
      : qi::reference<Subject>
      , lexer_type<reference<Subject> >
    {
        reference(Subject& subject)
          : qi::reference<Subject>(subject) {}

        template <typename LexerDef, typename String>
        void collect(LexerDef& lexdef, String const& state
          , String const& targetstate) const
        {
            this->ref.get().collect(lexdef, state, targetstate);
        }

        template <typename LexerDef>
        void add_actions(LexerDef& lexdef) const 
        {
            this->ref.get().add_actions(lexdef);
        }
    };

    template <typename Subject, typename IdType>
    struct reference : reference<Subject>
    {
        reference(Subject& subject)
          : reference<Subject>(subject) {}

        IdType id() const 
        { 
            return this->ref.get().id(); 
        }
        std::size_t unique_id() const 
        { 
            return this->ref.get().unique_id(); 
        }
        std::size_t state() const 
        { 
            return this->ref.get().state(); 
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename IdType
      , typename Attribute, typename Context, typename Iterator>
    struct handles_container<lex::reference<Subject, IdType>
          , Attribute, Context, Iterator>
      : handles_container<
            typename remove_const<Subject>::type, Attribute, Context, Iterator> 
    {};
}}}

#endif

/* reference.hpp
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
*/