//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_META_COMPILER_APR_20_2009_0756PM)
#define BOOST_SPIRIT_LEX_META_COMPILER_APR_20_2009_0756PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/meta_compiler.hpp>
#include <boost/spirit/home/lex/domain.hpp>
#include <boost/spirit/home/lex/lexer_type.hpp>
#include <boost/proto/tags.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace spirit
{
    template <typename T>
    struct use_terminal<lex::domain, T
      , typename enable_if<traits::is_lexer<T> >::type> // enables lexers
      : mpl::true_ {};

    namespace lex
    {
        template <typename T, typename Modifiers, typename Enable = void>
        struct make_primitive // by default, return it as-is
        {
            typedef T result_type;

            template <typename T_>
            T_& operator()(T_& val, unused_type) const
            {
                return val;
            }

            template <typename T_>
            T_ const& operator()(T_ const& val, unused_type) const
            {
                return val;
            }
        };

        template <typename Tag, typename Elements
          , typename Modifiers, typename Enable = void>
        struct make_composite;
    }

    // Lex primitive meta-compiler
    template <>
    struct make_component<lex::domain, proto::tag::terminal>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename lex::make_primitive<
                typename remove_const<typename Elements::car_type>::type,
                typename remove_reference<Modifiers>::type>::result_type
            type;
        };

        template <typename Elements, typename Modifiers>
        typename result<make_component(Elements, Modifiers)>::type
        operator()(Elements const& elements, Modifiers const& modifiers) const
        {
            typedef typename remove_const<typename Elements::car_type>::type term;
            return lex::make_primitive<term, Modifiers>()(elements.car, modifiers);
        }
    };

    // Lex composite meta-compiler
    template <typename Tag>
    struct make_component<lex::domain, Tag>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename
                lex::make_composite<Tag, Elements
                  , typename remove_reference<Modifiers>::type>::result_type
            type;
        };

        template <typename Elements, typename Modifiers>
        typename result<make_component(Elements, Modifiers)>::type
        operator()(Elements const& elements, Modifiers const& modifiers) const
        {
            return lex::make_composite<Tag, Elements, Modifiers>()(
                elements, modifiers);
        }
    };

}}

#endif

/* meta_compiler.hpp
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
*/