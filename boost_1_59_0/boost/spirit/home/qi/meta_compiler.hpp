/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_META_COMPILER_OCTOBER_16_2008_0347PM)
#define BOOST_SPIRIT_META_COMPILER_OCTOBER_16_2008_0347PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/meta_compiler.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/proto/tags.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/at.hpp>

namespace boost { namespace spirit
{
    template <typename T>
    struct use_terminal<qi::domain, T
      , typename enable_if<traits::is_parser<T> >::type> // enables parsers
      : mpl::true_ {};

    namespace qi
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

    // Qi primitive meta-compiler
    template <>
    struct make_component<qi::domain, proto::tag::terminal>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename qi::make_primitive<
                typename remove_const<typename Elements::car_type>::type,
                typename remove_reference<Modifiers>::type>::result_type
            type;
        };

        template <typename Elements, typename Modifiers>
        typename result<make_component(Elements, Modifiers)>::type
        operator()(Elements const& elements, Modifiers const& modifiers) const
        {
            typedef typename remove_const<typename Elements::car_type>::type term;
            return qi::make_primitive<term, Modifiers>()(elements.car, modifiers);
        }
    };

    // Qi composite meta-compiler
    template <typename Tag>
    struct make_component<qi::domain, Tag>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename
                qi::make_composite<Tag, Elements,
                typename remove_reference<Modifiers>::type>::result_type
            type;
        };

        template <typename Elements, typename Modifiers>
        typename result<make_component(Elements, Modifiers)>::type
        operator()(Elements const& elements, Modifiers const& modifiers) const
        {
            return qi::make_composite<Tag, Elements, Modifiers>()(
                elements, modifiers);
        }
    };

    // Qi function meta-compiler
    template <>
    struct make_component<qi::domain, proto::tag::function>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename
                qi::make_composite<
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
            return qi::make_composite<
                typename remove_const<typename Elements::car_type>::type,
                typename Elements::cdr_type,
                Modifiers>()(elements.cdr, modifiers);
        }
    };

    // Qi directive meta-compiler
    template <>
    struct make_component<qi::domain, tag::directive>
    {
        template <typename Sig>
        struct result;

        template <typename This, typename Elements, typename Modifiers>
        struct result<This(Elements, Modifiers)>
        {
            typedef typename
                qi::make_directive<
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
            return qi::make_directive<
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