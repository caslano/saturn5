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
    BOOST_INLINE_VARIABLE const BOOST_PP_CAT(keyword_, _type) keyword_ = {};

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