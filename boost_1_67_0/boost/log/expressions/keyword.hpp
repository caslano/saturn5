/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keyword.hpp
 * \author Andrey Semashev
 * \date   29.01.2012
 *
 * The header contains attribute keyword declaration.
 */

#ifndef BOOST_LOG_EXPRESSIONS_KEYWORD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_KEYWORD_HPP_INCLUDED_

#include <boost/ref.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/make_expr.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/expressions/is_keyword_descriptor.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/value_extraction.hpp>
#include <boost/log/attributes/fallback_policy.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * This class implements an expression template keyword. It is used to start template expressions involving attribute values.
 */
template< typename DescriptorT, template< typename > class ActorT >
struct attribute_keyword
{
    //! Self type
    typedef attribute_keyword this_type;
    //! Attribute descriptor type
    typedef DescriptorT descriptor_type;

    BOOST_PROTO_BASIC_EXTENDS(typename proto::terminal< descriptor_type >::type, this_type, phoenix::phoenix_domain)

    //! Attribute value type
    typedef typename descriptor_type::value_type value_type;

    //! Returns attribute name
    static attribute_name get_name() { return descriptor_type::get_name(); }

    //! Expression with cached attribute name
    typedef attribute_actor<
        value_type,
        fallback_to_none,
        descriptor_type,
        ActorT
    > or_none_result_type;

    //! Generates an expression that extracts the attribute value or a default value
    static or_none_result_type or_none()
    {
        typedef typename or_none_result_type::terminal_type result_terminal;
        typename or_none_result_type::base_type act = {{ result_terminal(get_name()) }};
        return or_none_result_type(act);
    }

    //! Expression with cached attribute name
    typedef attribute_actor<
        value_type,
        fallback_to_throw,
        descriptor_type,
        ActorT
    > or_throw_result_type;

    //! Generates an expression that extracts the attribute value or throws an exception
    static or_throw_result_type or_throw()
    {
        typedef typename or_throw_result_type::terminal_type result_terminal;
        typename or_throw_result_type::base_type act = {{ result_terminal(get_name()) }};
        return or_throw_result_type(act);
    }

    //! Generates an expression that extracts the attribute value or a default value
    template< typename DefaultT >
    static attribute_actor<
        value_type,
        fallback_to_default< DefaultT >,
        descriptor_type,
        ActorT
    > or_default(DefaultT const& def_val)
    {
        typedef attribute_actor<
            value_type,
            fallback_to_default< DefaultT >,
            descriptor_type,
            ActorT
        > or_default_result_type;
        typedef typename or_default_result_type::terminal_type result_terminal;
        typename or_default_result_type::base_type act = {{ result_terminal(get_name(), def_val) }};
        return or_default_result_type(act);
    }
};

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace proto {

namespace detail {

// This hack is needed in order to cache attribute name into the expression terminal when the template
// expression is constructed. The standard way through a custom domain doesn't work because phoenix::actor
// is bound to phoenix_domain.
template< typename DescriptorT, template< typename > class ActorT, typename DomainT >
struct protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT >, DomainT >
{
    typedef boost::log::expressions::attribute_keyword< DescriptorT, ActorT > keyword_type;
    typedef typename keyword_type::or_none_result_type result_type;

    result_type operator() (keyword_type const& keyword) const
    {
        return keyword.or_none();
    }
};

template< typename DescriptorT, template< typename > class ActorT, typename DomainT >
struct protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT >&, DomainT > :
    public protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT >, DomainT >
{
};

template< typename DescriptorT, template< typename > class ActorT, typename DomainT >
struct protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT > const&, DomainT > :
    public protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT >, DomainT >
{
};

template< typename DescriptorT, template< typename > class ActorT, typename DomainT >
struct protoify< boost::reference_wrapper< boost::log::expressions::attribute_keyword< DescriptorT, ActorT > >, DomainT > :
    public protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT >, DomainT >
{
};

template< typename DescriptorT, template< typename > class ActorT, typename DomainT >
struct protoify< boost::reference_wrapper< boost::log::expressions::attribute_keyword< DescriptorT, ActorT > > const, DomainT > :
    public protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT >, DomainT >
{
};

template< typename DescriptorT, template< typename > class ActorT, typename DomainT >
struct protoify< boost::reference_wrapper< const boost::log::expressions::attribute_keyword< DescriptorT, ActorT > >, DomainT > :
    public protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT >, DomainT >
{
};

template< typename DescriptorT, template< typename > class ActorT, typename DomainT >
struct protoify< boost::reference_wrapper< const boost::log::expressions::attribute_keyword< DescriptorT, ActorT > > const, DomainT > :
    public protoify< boost::log::expressions::attribute_keyword< DescriptorT, ActorT >, DomainT >
{
};

} // namespace detail

} // namespace proto

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

} // namespace boost

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_ATTRIBUTE_KEYWORD_TYPE_IMPL(keyword_, name_, value_type_, tag_ns_)\
    namespace tag_ns_\
    {\
        struct keyword_ :\
            public ::boost::log::expressions::keyword_descriptor\
        {\
            typedef value_type_ value_type;\
            static ::boost::log::attribute_name get_name() { return ::boost::log::attribute_name(name_); }\
        };\
    }\
    typedef ::boost::log::expressions::attribute_keyword< tag_ns_::keyword_ > BOOST_PP_CAT(keyword_, _type);

#define BOOST_LOG_ATTRIBUTE_KEYWORD_IMPL(keyword_, name_, value_type_, tag_ns_)\
    BOOST_LOG_ATTRIBUTE_KEYWORD_TYPE_IMPL(keyword_, name_, value_type_, tag_ns_)\
    const BOOST_PP_CAT(keyword_, _type) keyword_ = {};

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief The macro declares an attribute keyword type
 *
 * The macro should be used at a namespace scope. It expands into an attribute keyword type definition, including the
 * \c tag namespace and the keyword tag type within which has the following layout:
 *
 * \code
 * namespace tag
 * {
 *   struct keyword_ :
 *     public boost::log::expressions::keyword_descriptor
 *   {
 *     typedef value_type_ value_type;
 *     static boost::log::attribute_name get_name();
 *   };
 * }
 *
 * typedef boost::log::expressions::attribute_keyword< tag::keyword_ > keyword_type;
 * \endcode
 *
 * The \c get_name method returns the attribute name.
 *
 * \note This macro only defines the type of the keyword. To also define the keyword object, use
 *       the \c BOOST_LOG_ATTRIBUTE_KEYWORD macro instead.
 *
 * \param keyword_ Keyword name
 * \param name_ Attribute name string
 * \param value_type_ Attribute value type
 */
#define BOOST_LOG_ATTRIBUTE_KEYWORD_TYPE(keyword_, name_, value_type_)\
    BOOST_LOG_ATTRIBUTE_KEYWORD_TYPE_IMPL(keyword_, name_, value_type_, tag)

/*!
 * \brief The macro declares an attribute keyword
 *
 * The macro provides definitions similar to \c BOOST_LOG_ATTRIBUTE_KEYWORD_TYPE and additionally
 * defines the keyword object.
 *
 * \param keyword_ Keyword name
 * \param name_ Attribute name string
 * \param value_type_ Attribute value type
 */
#define BOOST_LOG_ATTRIBUTE_KEYWORD(keyword_, name_, value_type_)\
    BOOST_LOG_ATTRIBUTE_KEYWORD_IMPL(keyword_, name_, value_type_, tag)

#include <boost/log/detail/footer.hpp>

#if defined(BOOST_LOG_TRIVIAL_HPP_INCLUDED_)
#include <boost/log/detail/trivial_keyword.hpp>
#endif

#endif // BOOST_LOG_EXPRESSIONS_KEYWORD_HPP_INCLUDED_

/* keyword.hpp
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
*/