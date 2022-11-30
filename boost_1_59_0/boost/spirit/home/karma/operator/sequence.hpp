//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_OPERATOR_SEQUENCE_HPP
#define BOOST_SPIRIT_KARMA_OPERATOR_SEQUENCE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/detail/fail_function.hpp>
#include <boost/spirit/home/karma/detail/pass_container.hpp>
#include <boost/spirit/home/karma/detail/get_stricttag.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/detail/what_function.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/karma/detail/indirect_iterator.hpp>
#include <boost/spirit/home/support/algorithm/any_if.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/sequence_base_id.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/support/attributes.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bitor.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/mpl/accumulate.hpp>
#include <boost/proto/operators.hpp>
#include <boost/proto/tags.hpp>
#include <boost/config.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<karma::domain, proto::tag::shift_left> // enables <<
      : mpl::true_ {};

    template <>
    struct flatten_tree<karma::domain, proto::tag::shift_left> // flattens <<
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    // specialization for sequences
    template <typename Elements>
    struct sequence_properties
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
          , mpl::int_<karma::generator_properties::no_properties>
          , mpl::bitor_<mpl::_2, mpl::_1>
        >::type type;
    };
}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    template <typename Elements, typename Strict, typename Derived>
    struct base_sequence : nary_generator<Derived>
    {
        typedef typename traits::sequence_properties<Elements>::type properties;

        base_sequence(Elements const& elements)
          : elements(elements) {}

        typedef Elements elements_type;
        struct sequence_base_id;

        template <typename Context, typename Iterator = unused_type>
        struct attribute
        {
            // Put all the element attributes in a tuple
            typedef typename traits::build_attribute_sequence<
                Elements, Context, traits::sequence_attribute_transform
              , Iterator, karma::domain
            >::type all_attributes;

            // Now, build a fusion vector over the attributes. Note
            // that build_fusion_vector 1) removes all unused attributes
            // and 2) may return unused_type if all elements have
            // unused_type(s).
            typedef typename
                traits::build_fusion_vector<all_attributes>::type
            type_;

            // Finally, strip single element vectors into its
            // naked form: vector1<T> --> T
            typedef typename
                traits::strip_single_element_vector<type_>::type
            type;
        };

        // standard case. Attribute is a fusion tuple
        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute, typename Pred1, typename Pred2>
        bool generate_impl(OutputIterator& sink, Context& ctx
          , Delimiter const& d, Attribute& attr_, Pred1, Pred2) const
        {
            typedef detail::fail_function<
                OutputIterator, Context, Delimiter> fail_function;
            typedef traits::attribute_not_unused<Context> predicate;

            // wrap the attribute in a tuple if it is not a tuple or if the
            // attribute of this sequence is a single element tuple
            typedef typename attribute<Context>::type_ attr_type_;
            typename traits::wrap_if_not_tuple<Attribute
              , typename mpl::and_<
                    traits::one_element_sequence<attr_type_>
                  , mpl::not_<traits::one_element_sequence<Attribute> >
                >::type
            >::type attr(attr_);

            // return false if *any* of the generators fail
            bool r = spirit::any_if(elements, attr
                          , fail_function(sink, ctx, d), predicate());

            typedef typename traits::attribute_size<Attribute>::type size_type;

            // fail generating if sequences have not the same (logical) length
            return !r && (!Strict::value ||
                // This ignores container element count (which is not good),
                // but allows valid attributes to succeed. This will lead to
                // false positives (failing generators, even if they shouldn't)
                // if the embedded component is restricting the number of
                // container elements it consumes (i.e. repeat). This solution
                // is not optimal but much better than letting _all_ repetitive
                // components fail.
                Pred1::value ||
                size_type(traits::sequence_size<attr_type_>::value) == traits::size(attr_));
        }

        // Special case when Attribute is an stl container and the sequence's
        // attribute is not a one element sequence
        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate_impl(OutputIterator& sink, Context& ctx
          , Delimiter const& d, Attribute const& attr_
          , mpl::true_, mpl::false_) const
        {
            // return false if *any* of the generators fail
            typedef detail::fail_function<
                OutputIterator, Context, Delimiter> fail_function;

            typedef typename traits::container_iterator<
                typename add_const<Attribute>::type
            >::type iterator_type;

            typedef
                typename traits::make_indirect_iterator<iterator_type>::type
            indirect_iterator_type;
            typedef detail::pass_container<
                fail_function, Attribute, indirect_iterator_type, mpl::true_>
            pass_container;

            iterator_type begin = traits::begin(attr_);
            iterator_type end = traits::end(attr_);

            pass_container pass(fail_function(sink, ctx, d),
                indirect_iterator_type(begin), indirect_iterator_type(end));
            bool r = fusion::any(elements, pass);

            // fail generating if sequences have not the same (logical) length
            return !r && (!Strict::value || begin == end);
        }

        // main generate function. Dispatches to generate_impl depending
        // on the Attribute type.
        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            typedef typename traits::is_container<Attribute>::type
                is_container;

            typedef typename attribute<Context>::type_ attr_type_;
            typedef typename traits::one_element_sequence<attr_type_>::type
                is_one_element_sequence;

            return generate_impl(sink, ctx, d, attr, is_container()
              , is_one_element_sequence());
        }

        template <typename Context>
        info what(Context& context) const
        {
            info result("sequence");
            fusion::for_each(elements,
                spirit::detail::what_function<Context>(result, context));
            return result;
        }

        Elements elements;
    };

    template <typename Elements>
    struct sequence
      : base_sequence<Elements, mpl::false_, sequence<Elements> >
    {
        typedef base_sequence<Elements, mpl::false_, sequence> base_sequence_;

        sequence(Elements const& subject)
          : base_sequence_(subject) {}
    };

    template <typename Elements>
    struct strict_sequence
      : base_sequence<Elements, mpl::true_, strict_sequence<Elements> >
    {
        typedef base_sequence<Elements, mpl::true_, strict_sequence>
            base_sequence_;

        strict_sequence(Elements const& subject)
          : base_sequence_(subject) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Elements, bool strict_mode = false>
        struct make_sequence
          : make_nary_composite<Elements, sequence>
        {};

        template <typename Elements>
        struct make_sequence<Elements, true>
          : make_nary_composite<Elements, strict_sequence>
        {};
    }

    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::shift_left, Elements, Modifiers>
      : detail::make_sequence<Elements, detail::get_stricttag<Modifiers>::value>
    {};

    ///////////////////////////////////////////////////////////////////////////
    // Helper template allowing to get the required container type for a rule
    // attribute, which is part of a sequence.
    template <typename Iterator>
    struct make_sequence_iterator_range
    {
        typedef iterator_range<detail::indirect_iterator<Iterator> > type;
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements>
    struct has_semantic_action<karma::sequence<Elements> >
      : nary_has_semantic_action<Elements> {};

    template <typename Elements>
    struct has_semantic_action<karma::strict_sequence<Elements> >
      : nary_has_semantic_action<Elements> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Elements, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::sequence<Elements>, Attribute, Context
          , Iterator>
      : mpl::true_ {};

    template <typename Elements, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::strict_sequence<Elements>, Attribute
          , Context, Iterator>
      : mpl::true_ {};
}}}

#endif

/* sequence.hpp
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
*/