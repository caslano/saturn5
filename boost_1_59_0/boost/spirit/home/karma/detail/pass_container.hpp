/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_KARMA_DETAIL_PASS_CONTAINER_HPP
#define BOOST_SPIRIT_KARMA_DETAIL_PASS_CONTAINER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/fusion/include/deduce_sequence.hpp>

namespace boost { namespace spirit { namespace karma { namespace detail
{
    // Helper meta-function allowing to evaluate weak substitutability and
    // negate the result if the predicate (Sequence) is not true
    template <typename Sequence, typename Attribute, typename ValueType>
    struct negate_weak_substitute_if_not
      : mpl::if_<
            Sequence
          , typename traits::is_weak_substitute<Attribute, ValueType>::type
          , typename mpl::not_<
                traits::is_weak_substitute<Attribute, ValueType>
            >::type>
    {};

    // pass_through_container: utility to check decide whether a provided
    // container attribute needs to be passed through to the current component
    // or of we need to split the container by passing along instances of its
    // value type

    // if the expected attribute of the current component is neither a Fusion
    // sequence nor a container, we will pass through the provided container
    // only if its value type is not compatible with the component
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence, typename Enable = void>
    struct pass_through_container_base
      : negate_weak_substitute_if_not<Sequence, ValueType, Attribute>
    {};

    // Specialization for fusion sequences, in this case we check whether all
    // the types in the sequence are convertible to the lhs attribute.
    //
    // We return false if the rhs attribute itself is a fusion sequence, which
    // is compatible with the LHS sequence (we want to pass through this
    // attribute without it being split apart).
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence = mpl::true_>
    struct not_compatible_element
      : mpl::and_<
            negate_weak_substitute_if_not<Sequence, Container, Attribute>
          , negate_weak_substitute_if_not<Sequence, ValueType, Attribute> >
    {};

    // If the value type of the container is not a Fusion sequence, we pass
    // through the container if each of the elements of the Attribute
    // sequence is compatible with either the container or its value type.
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence
      , bool IsSequence = fusion::traits::is_sequence<ValueType>::value>
    struct pass_through_container_fusion_sequence
    {
        typedef typename mpl::find_if<
            Attribute, not_compatible_element<Container, ValueType, mpl::_1>
        >::type iter;
        typedef typename mpl::end<Attribute>::type end;

        typedef typename is_same<iter, end>::type type;
    };

    // If both, the Attribute and the value type of the provided container
    // are Fusion sequences, we pass the container only if the two
    // sequences are not compatible.
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container_fusion_sequence<
            Container, ValueType, Attribute, Sequence, true>
    {
        typedef typename mpl::find_if<
            Attribute
          , not_compatible_element<Container, ValueType, mpl::_1, Sequence>
        >::type iter;
        typedef typename mpl::end<Attribute>::type end;

        typedef typename is_same<iter, end>::type type;
    };

    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container_base<Container, ValueType, Attribute
          , Sequence
          , typename enable_if<fusion::traits::is_sequence<Attribute> >::type>
      : pass_through_container_fusion_sequence<
            Container, ValueType, Attribute, Sequence>
    {};

    // Specialization for containers
    //
    // If the value type of the attribute of the current component is not
    // a Fusion sequence, we have to pass through the provided container if
    // both are compatible.
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence, typename AttributeValueType
      , bool IsSequence = fusion::traits::is_sequence<AttributeValueType>::value>
    struct pass_through_container_container
      : mpl::or_<
            traits::is_weak_substitute<Container, Attribute>
          , traits::is_weak_substitute<Container, AttributeValueType> >
    {};

    // If the value type of the exposed container attribute is a Fusion
    // sequence, we use the already existing logic for those.
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence, typename AttributeValueType>
    struct pass_through_container_container<
            Container, ValueType, Attribute, Sequence, AttributeValueType, true>
      : pass_through_container_fusion_sequence<
            Container, ValueType, AttributeValueType, Sequence>
    {};

    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container_base<Container, ValueType, Attribute
          , Sequence
          , typename enable_if<traits::is_container<Attribute> >::type>
      : detail::pass_through_container_container<
          Container, ValueType, Attribute, Sequence
        , typename traits::container_value<Attribute>::type>
    {};

    // Specialization for exposed optional attributes
    //
    // If the type embedded in the exposed optional is not a Fusion
    // sequence we pass through the container attribute if it is compatible
    // either to the optionals embedded type or to the containers value
    // type.
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence
      , bool IsSequence = fusion::traits::is_sequence<Attribute>::value>
    struct pass_through_container_optional
      : mpl::or_<
            traits::is_weak_substitute<Container, Attribute>
          , traits::is_weak_substitute<ValueType, Attribute> >
    {};

    // If the embedded type of the exposed optional attribute is a Fusion
    // sequence, we use the already existing logic for those.
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container_optional<
            Container, ValueType, Attribute, Sequence, true>
      : pass_through_container_fusion_sequence<
            Container, ValueType, Attribute, Sequence>
    {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container
      : pass_through_container_base<Container, ValueType, Attribute, Sequence>
    {};

    // Handle optional attributes
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container<
            Container, ValueType, boost::optional<Attribute>, Sequence>
      : pass_through_container_optional<
            Container, ValueType, Attribute, Sequence>
    {};

    // If both, the containers value type and the exposed attribute type are
    // optionals we are allowed to pass through the container only if the
    // embedded types of those optionals are not compatible.
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container<
            Container, boost::optional<ValueType>, boost::optional<Attribute>
          , Sequence>
      : mpl::not_<traits::is_weak_substitute<ValueType, Attribute> >
    {};

    // Specialization for exposed variant attributes
    //
    // We pass through the container attribute if at least one of the embedded
    // types in the variant requires to pass through the attribute

#if !defined(BOOST_VARIANT_DO_NOT_USE_VARIADIC_TEMPLATES)
    template <typename Container, typename ValueType, typename Sequence
      , typename T>
    struct pass_through_container<Container, ValueType, boost::variant<T>
          , Sequence>
      : pass_through_container<Container, ValueType, T, Sequence>
    {};

    template <typename Container, typename ValueType, typename Sequence
      , typename T0, typename ...TN>
    struct pass_through_container<Container, ValueType
          , boost::variant<T0, TN...>, Sequence>
      : mpl::bool_<pass_through_container<
            Container, ValueType, T0, Sequence
            >::type::value || pass_through_container<
                Container, ValueType, boost::variant<TN...>, Sequence
            >::type::value>
    {};
#else
#define BOOST_SPIRIT_PASS_THROUGH_CONTAINER(z, N, _)                          \
    pass_through_container<Container, ValueType,                              \
        BOOST_PP_CAT(T, N), Sequence>::type::value ||                         \
    /***/

    // make sure unused variant parameters do not affect the outcome
    template <typename Container, typename ValueType, typename Sequence>
    struct pass_through_container<Container, ValueType
          , boost::detail::variant::void_, Sequence>
      : mpl::false_
    {};

    template <typename Container, typename ValueType, typename Sequence
      , BOOST_VARIANT_ENUM_PARAMS(typename T)>
    struct pass_through_container<Container, ValueType
          , boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Sequence>
      : mpl::bool_<BOOST_PP_REPEAT(BOOST_VARIANT_LIMIT_TYPES
          , BOOST_SPIRIT_PASS_THROUGH_CONTAINER, _) false>
    {};

#undef BOOST_SPIRIT_PASS_THROUGH_CONTAINER
#endif
}}}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    // forwarding customization point for domain karma::domain
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container<
            Container, ValueType, Attribute, Sequence, karma::domain>
      : karma::detail::pass_through_container<
            Container, ValueType, Attribute, Sequence>
    {};
}}}

namespace boost { namespace spirit { namespace karma { namespace detail
{
    template <typename Iterator>
    struct pass_container_base
    {
        pass_container_base(Iterator begin, Iterator end)
          : iter(begin), end(end)
        {}

        mutable Iterator iter;
        mutable Iterator end;
    };

    template <typename Iterator>
    struct pass_container_base<Iterator&>
    {
        pass_container_base(Iterator& begin, Iterator& end)
          : iter(begin), end(end)
        {}

        Iterator& iter;
        Iterator& end;
    };

    ///////////////////////////////////////////////////////////////////////////
    // This function handles the case where the attribute (Attr) given
    // to the sequence is an STL container. This is a wrapper around F.
    // The function F does the actual generating.
    template <typename F, typename Attr, typename Iterator, typename Sequence>
    struct pass_container : pass_container_base<Iterator>
    {
        typedef pass_container_base<Iterator> base_type;
        typedef typename F::context_type context_type;

        pass_container(F const& f, Iterator begin, Iterator end)
          : base_type(begin, end)
          , f(f)
        {}

        bool is_at_end() const
        {
            return traits::compare(this->iter, this->end);
        }

        void next()
        {
            traits::next(this->iter);
        }

        // this is for the case when the current element expects an attribute
        // which is taken from the next entry in the container
        template <typename Component>
        bool dispatch_container(Component const& component, mpl::false_) const
        {
            // get the next value to generate from container
            if (!is_at_end() && !f(component, traits::deref(this->iter)))
            {
                // needs to return false as long as everything is ok
                traits::next(this->iter);
                return false;
            }

            // either no elements available any more or generation failed
            return true;
        }

        // this is for the case when the current element is able to handle an
        // attribute which is a container itself, this element will push its
        // data directly into the attribute container
        template <typename Component>
        bool dispatch_container(Component const& component, mpl::true_) const
        {
            return f(component, make_iterator_range(this->iter, this->end));
        }

        ///////////////////////////////////////////////////////////////////////
        // this is for the case when the current element doesn't expect an
        // attribute
        template <typename Component>
        bool dispatch_attribute(Component const& component, mpl::false_) const
        {
            return f(component, unused);
        }

        // the current element expects an attribute
        template <typename Component>
        bool dispatch_attribute(Component const& component, mpl::true_) const
        {
            typedef typename traits::container_value<Attr>::type value_type;
            typedef typename
                traits::attribute_of<Component, context_type>::type
            lhs_attribute;

            // this predicate detects, whether the value type of the container
            // attribute is a substitute for the attribute of the current
            // element
            typedef mpl::and_<
                traits::handles_container<Component, Attr, context_type>
              , traits::pass_through_container<
                    Attr, value_type, lhs_attribute, Sequence, karma::domain>
            > predicate;

            return dispatch_container(component, predicate());
        }

        // Dispatches to dispatch_main depending on the attribute type
        // of the Component
        template <typename Component>
        bool operator()(Component const& component) const
        {
            // we need to dispatch depending on the type of the attribute
            // of the current element (component). If this is has no attribute
            // we shouldn't use an element of the container but unused_type
            // instead
            typedef traits::not_is_unused<
                typename traits::attribute_of<Component, context_type>::type
            > predicate;

            return dispatch_attribute(component, predicate());
        }

        F f;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(pass_container& operator= (pass_container const&))
    };
}}}}

#endif

/* pass_container.hpp
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
*/