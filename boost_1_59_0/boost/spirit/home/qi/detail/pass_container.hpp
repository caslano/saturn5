/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_QI_DETAIL_PASS_CONTAINER_HPP
#define BOOST_SPIRIT_QI_DETAIL_PASS_CONTAINER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost { namespace spirit { namespace qi { namespace detail
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
      : negate_weak_substitute_if_not<Sequence, Attribute, ValueType>
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
            negate_weak_substitute_if_not<Sequence, Attribute, Container>
          , negate_weak_substitute_if_not<Sequence, Attribute, ValueType> >
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
            traits::is_weak_substitute<Attribute, Container>
          , traits::is_weak_substitute<AttributeValueType, Container> >
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
    struct pass_through_container_base<
            Container, ValueType, Attribute, Sequence
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
            traits::is_weak_substitute<Attribute, Container>
          , traits::is_weak_substitute<Attribute, ValueType> >
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
      : mpl::not_<traits::is_weak_substitute<Attribute, ValueType> >
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
    // forwarding customization point for domain qi::domain
    template <typename Container, typename ValueType, typename Attribute
      , typename Sequence>
    struct pass_through_container<
            Container, ValueType, Attribute, Sequence, qi::domain>
      : qi::detail::pass_through_container<
            Container, ValueType, Attribute, Sequence>
    {};
}}}

namespace boost { namespace spirit { namespace qi { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    // This function handles the case where the attribute (Attr) given
    // the sequence is an STL container. This is a wrapper around F.
    // The function F does the actual parsing.
    template <typename F, typename Attr, typename Sequence>
    struct pass_container
    {
        typedef typename F::context_type context_type;
        typedef typename F::iterator_type iterator_type;

        pass_container(F const& f_, Attr& attr_)
          : f(f_), attr(attr_) {}

        // this is for the case when the current element exposes an attribute
        // which is pushed back onto the container
        template <typename Component>
        bool dispatch_container(Component const& component, mpl::false_) const
        {
            // synthesized attribute needs to be default constructed
            typename traits::container_value<Attr>::type val =
                typename traits::container_value<Attr>::type();

            iterator_type save = f.first;
            bool r = f(component, val);
            if (!r)
            {
                // push the parsed value into our attribute
                r = !traits::push_back(attr, val);
                if (r)
                    f.first = save;
            }
            return r;
        }

        // this is for the case when the current element is able to handle an
        // attribute which is a container itself, this element will push its
        // data directly into the attribute container
        template <typename Component>
        bool dispatch_container(Component const& component, mpl::true_) const
        {
            return f(component, attr);
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
            typedef typename traits::attribute_of<
                Component, context_type, iterator_type>::type
            rhs_attribute;

            // this predicate detects, whether the attribute of the current
            // element is a substitute for the value type of the container
            // attribute
            typedef mpl::and_<
                traits::handles_container<
                    Component, Attr, context_type, iterator_type>
              , traits::pass_through_container<
                    Attr, value_type, rhs_attribute, Sequence, qi::domain>
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
            // we shouldn't pass an attribute at all.
            typedef typename traits::not_is_unused<
                typename traits::attribute_of<
                    Component, context_type, iterator_type
                >::type
            >::type predicate;

            // ensure the attribute is actually a container type
            traits::make_container(attr);

            return dispatch_attribute(component, predicate());
        }

        F f;
        Attr& attr;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(pass_container& operator= (pass_container const&))
    };

    ///////////////////////////////////////////////////////////////////////////
    // Utility function to make a pass_container for container components
    // (kleene, list, plus, repeat)
    template <typename F, typename Attr>
    inline pass_container<F, Attr, mpl::false_>
    make_pass_container(F const& f, Attr& attr)
    {
        return pass_container<F, Attr, mpl::false_>(f, attr);
    }

    // Utility function to make a pass_container for sequences
    template <typename F, typename Attr>
    inline pass_container<F, Attr, mpl::true_>
    make_sequence_pass_container(F const& f, Attr& attr)
    {
        return pass_container<F, Attr, mpl::true_>(f, attr);
    }
}}}}

#endif


/* pass_container.hpp
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
*/