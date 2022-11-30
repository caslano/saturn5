/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_QI_DETAIL_ALTERNATIVE_FUNCTION_HPP
#define BOOST_SPIRIT_QI_DETAIL_ALTERNATIVE_FUNCTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
{
    template <typename Variant, typename T>
    struct find_substitute
    {
        // Get the type from the Variant that can be a substitute for T.
        // If none is found, just return T

        typedef Variant variant_type;
        typedef typename variant_type::types types;
        typedef typename mpl::end<types>::type end;

        typedef typename mpl::find<types, T>::type iter_1;

        typedef typename
            mpl::eval_if<
                is_same<iter_1, end>,
                mpl::find_if<types, traits::is_substitute<T, mpl::_1> >,
                mpl::identity<iter_1>
            >::type
        iter;

        typedef typename
            mpl::eval_if<
                is_same<iter, end>,
                mpl::identity<T>,
                mpl::deref<iter>
            >::type
        type;
    };

    template <typename Iterator, typename Context, typename Skipper,
        typename Attribute>
    struct alternative_function
    {
        alternative_function(
            Iterator& first_, Iterator const& last_, Context& context_,
            Skipper const& skipper_, Attribute& attr_)
          : first(first_), last(last_), context(context_), skipper(skipper_),
            attr(attr_)
        {
        }

        template <typename Component>
        bool call(Component const& component, mpl::true_) const
        {
            // if Attribute is not a variant, then pass it as-is
            return component.parse(first, last, context, skipper, attr);
        }

        template <typename Component>
        bool call_optional_or_variant(Component const& component, mpl::true_) const
        {
            // If Attribute is an optional, then create an attribute for the Component
            // with the type optional::value_type. If the expected attribute is unused type,
            // use it instead.
            typedef typename
                traits::attribute_of<Component, Context, Iterator>::type
            expected_type;

            typename mpl::if_<
                is_same<expected_type, unused_type>,
                unused_type,
                typename Attribute::value_type>::type
            val;

            if (component.parse(first, last, context, skipper, val))
            {
                traits::assign_to(val, attr);
                return true;
            }
            return false;
        }

        template <typename Component>
        bool call_variant(Component const& component, mpl::false_) const
        {
            // If Attribute is a variant, then search the variant types for a
            // suitable substitute type.

            typename
                find_substitute<Attribute,
                    typename traits::attribute_of<Component, Context, Iterator>::type
                >::type
            val;

            if (component.parse(first, last, context, skipper, val))
            {
                traits::assign_to(val, attr);
                return true;
            }
            return false;
        }

        template <typename Component>
        bool call_variant(Component const& component, mpl::true_) const
        {
            // If Attribute is a variant and the expected attribute is
            // the same type (pass the variant as-is).

            return component.parse(first, last, context, skipper, attr);
        }

        template <typename Component>
        bool call_optional_or_variant(Component const& component, mpl::false_) const
        {
            // Attribute is a variant...

            typedef typename
                traits::attribute_of<Component, Context, Iterator>::type
            expected;
            return call_variant(component,
                is_same<Attribute, expected>());
        }

        template <typename Component>
        bool call(Component const& component, mpl::false_) const
        {
            return call_optional_or_variant(
                component, spirit::traits::not_is_variant<Attribute, qi::domain>());
        }

        template <typename Component>
        bool call_unused(Component const& component, mpl::true_) const
        {
            // return true if the parser succeeds
            return call(component,
                mpl::and_<
                    spirit::traits::not_is_variant<Attribute, qi::domain>,
                    spirit::traits::not_is_optional<Attribute, qi::domain>
                >());
        }

        template <typename Component>
        bool call_unused(Component const& component, mpl::false_) const
        {
            return component.parse(first, last, context, skipper, unused);
        }

        template <typename Component>
        bool operator()(Component const& component) const
        {
            // return true if the parser succeeds
            typedef typename traits::not_is_unused<
                typename traits::attribute_of<Component, Context, Iterator>::type
            >::type predicate;

            return call_unused(component, predicate());
        }

        Iterator& first;
        Iterator const& last;
        Context& context;
        Skipper const& skipper;
        Attribute& attr;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(alternative_function& operator= (alternative_function const&))
    };

    template <typename Iterator, typename Context, typename Skipper>
    struct alternative_function<Iterator, Context, Skipper, unused_type const>
    {
        alternative_function(
            Iterator& first_, Iterator const& last_, Context& context_,
            Skipper const& skipper_, unused_type)
          : first(first_), last(last_), context(context_), skipper(skipper_)
        {
        }

        template <typename Component>
        bool operator()(Component const& component) const
        {
            // return true if the parser succeeds
            return component.parse(first, last, context, skipper,
                unused);
        }

        Iterator& first;
        Iterator const& last;
        Context& context;
        Skipper const& skipper;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(alternative_function& operator= (alternative_function const&))
    };

}}}}

#endif

/* alternative_function.hpp
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
*/