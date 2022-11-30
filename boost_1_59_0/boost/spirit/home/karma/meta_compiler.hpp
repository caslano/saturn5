//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_META_COMPILER_JANUARY_13_2009_1011AM)
#define BOOST_SPIRIT_KARMA_META_COMPILER_JANUARY_13_2009_1011AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/meta_compiler.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/proto/tags.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/at.hpp>

namespace boost { namespace spirit
{
    template <typename T>
    struct use_terminal<karma::domain, T
      , typename enable_if<traits::is_generator<T> >::type> // enables generators
      : mpl::true_ {};

    namespace karma
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

        template <typename Directive, typename Body
          , typename Modifiers, typename Enable = void>
        struct make_directive
        {
            typedef Body result_type;
            result_type operator()(unused_type, Body const& body, unused_type) const
            {
                return body; // By default, a directive simply returns its subject
            }
        };
    }

    // Karma primitive meta-compiler
    template <>
    struct make_component<karma::domain, proto::tag::terminal>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename karma::make_primitive<
                typename remove_const<typename Elements::car_type>::type
              , typename remove_reference<Modifiers>::type
            >::result_type type;
        };

        template <typename Elements, typename Modifiers>
        typename result<make_component(Elements, Modifiers)>::type
        operator()(Elements const& elements, Modifiers const& modifiers) const
        {
            typedef typename remove_const<typename Elements::car_type>::type term;
            return karma::make_primitive<term, Modifiers>()(elements.car, modifiers);
        }
    };

    // Karma composite meta-compiler
    template <typename Tag>
    struct make_component<karma::domain, Tag>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename
                karma::make_composite<Tag, Elements
                  , typename remove_reference<Modifiers>::type>::result_type
            type;
        };

        template <typename Elements, typename Modifiers>
        typename result<make_component(Elements, Modifiers)>::type
        operator()(Elements const& elements, Modifiers const& modifiers) const
        {
            return karma::make_composite<Tag, Elements, Modifiers>()(
                elements, modifiers);
        }
    };

    // Karma function meta-compiler
    template <>
    struct make_component<karma::domain, proto::tag::function>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename
                karma::make_composite<
                    typename remove_const<typename Elements::car_type>::type,
                    typename Elements::cdr_type,
                    typename remove_reference<Modifiers>::type
                >::result_type
            type;
        };

        template <typename Elements, typename Modifiers>
        typename result<make_component(Elements, Modifiers)>::type
        operator()(Elements const& elements, Modifiers const& modifiers) const
        {
            return karma::make_composite<
                typename remove_const<typename Elements::car_type>::type,
                typename Elements::cdr_type,
                Modifiers>()(elements.cdr, modifiers);
        }
    };

    // Karma directive meta-compiler
    template <>
    struct make_component<karma::domain, tag::directive>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename
                karma::make_directive<
                    typename remove_const<typename Elements::car_type>::type,
                    typename remove_const<typename Elements::cdr_type::car_type>::type,
                    typename remove_reference<Modifiers>::type
                >::result_type
            type;
        };

        template <typename Elements, typename Modifiers>
        typename result<make_component(Elements, Modifiers)>::type
        operator()(Elements const& elements, Modifiers const& modifiers) const
        {
            return karma::make_directive<
                typename remove_const<typename Elements::car_type>::type,
                typename remove_const<typename Elements::cdr_type::car_type>::type,
                Modifiers>()(elements.car, elements.cdr.car, modifiers);
        }
    };

}}

#endif

/* meta_compiler.hpp
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
*/