//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_OPERATOR_ALTERNATIVE_HPP
#define BOOST_SPIRIT_KARMA_OPERATOR_ALTERNATIVE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/detail/alternative_function.hpp>
#include <boost/spirit/home/karma/detail/get_stricttag.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/support/detail/what_function.hpp>
#include <boost/fusion/include/any.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/mpl/accumulate.hpp>
#include <boost/mpl/bitor.hpp>
#include <boost/proto/tags.hpp>
#include <boost/config.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<karma::domain, proto::tag::bitwise_or>  // enables |
      : mpl::true_ {};

    template <>
    struct flatten_tree<karma::domain, proto::tag::bitwise_or>  // flattens |
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    // specialization for sequences
    template <typename Elements>
    struct alternative_properties
    {
        struct element_properties
        {
            template <typename T>
            struct result;

            template <typename F, typename Element>
            struct result<F(Element)>
            {
                typedef properties_of<Element> type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template <typename Element>
            typename result<element_properties(Element)>::type
            operator()(Element&&) const;
#endif
        };

        typedef typename mpl::accumulate<
            typename fusion::result_of::transform<
                Elements, element_properties>::type
          , mpl::int_<karma::generator_properties::countingbuffer>
          , mpl::bitor_<mpl::_2, mpl::_1>
        >::type type;
    };

}}}

namespace boost { namespace spirit { namespace karma
{
    template <typename Elements, typename Strict, typename Derived>
    struct base_alternative : nary_generator<Derived>
    {
        typedef typename traits::alternative_properties<Elements>::type 
            properties;

        template <typename Context, typename Iterator = unused_type>
        struct attribute
        {
            // Put all the element attributes in a tuple
            typedef typename traits::build_attribute_sequence<
                Elements, Context, traits::alternative_attribute_transform
              , Iterator, karma::domain
            >::type all_attributes;

            // Ok, now make a variant over the attribute sequence. Note that
            // build_variant makes sure that 1) all attributes in the variant
            // are unique 2) puts the unused attribute, if there is any, to
            // the front and 3) collapses single element variants, variant<T>
            // to T.
            typedef typename traits::build_variant<all_attributes>::type type;
        };

        base_alternative(Elements const& elements)
          : elements(elements) {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx
          , Delimiter const& d, Attribute const& attr) const
        {
            typedef detail::alternative_generate_function<
                OutputIterator, Context, Delimiter, Attribute, Strict
            > functor;

            // f return true if *any* of the parser succeeds
            functor f (sink, ctx, d, attr);
            return fusion::any(elements, f);
        }

        template <typename Context>
        info what(Context& context) const
        {
            info result("alternative");
            fusion::for_each(elements,
                spirit::detail::what_function<Context>(result, context));
            return result;
        }

        Elements elements;
    };

    template <typename Elements>
    struct alternative 
      : base_alternative<Elements, mpl::false_, alternative<Elements> >
    {
        typedef base_alternative<Elements, mpl::false_, alternative> 
            base_alternative_;

        alternative(Elements const& elements)
          : base_alternative_(elements) {}
    };

    template <typename Elements>
    struct strict_alternative 
      : base_alternative<Elements, mpl::true_, strict_alternative<Elements> >
    {
        typedef base_alternative<Elements, mpl::true_, strict_alternative> 
            base_alternative_;

        strict_alternative(Elements const& elements)
          : base_alternative_(elements) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Elements, bool strict_mode = false>
        struct make_alternative 
          : make_nary_composite<Elements, alternative>
        {};

        template <typename Elements>
        struct make_alternative<Elements, true> 
          : make_nary_composite<Elements, strict_alternative>
        {};
    }

    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::bitwise_or, Elements, Modifiers>
      : detail::make_alternative<Elements
          , detail::get_stricttag<Modifiers>::value>
    {};

}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements>
    struct has_semantic_action<karma::alternative<Elements> >
      : nary_has_semantic_action<Elements> {};

    template <typename Elements>
    struct has_semantic_action<karma::strict_alternative<Elements> >
      : nary_has_semantic_action<Elements> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::alternative<Elements>
          , Attribute, Context, Iterator>
      : nary_handles_container<Elements, Attribute, Context, Iterator> {};

    template <typename Elements, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::strict_alternative<Elements>
          , Attribute, Context, Iterator>
      : nary_handles_container<Elements, Attribute, Context, Iterator> {};
}}}

#endif

/* alternative.hpp
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
*/