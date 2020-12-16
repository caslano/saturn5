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
vcpKdtZTE+e/iptuVi+t85MkDts8k8jBi5GH6NUbPLkmTe0mcp+QpI2YuC1kTmSAqdNB9TU/0I+Xaf6kaXrXyfk6QjsjNK2mHF6U+IzwpDn3d6qpsTVpxM1BnjdX3DR7QvoxkzfnyP2xtIiOpPPkzhvpV2YnqX0VT+Ot3qQUcJ03iet+/RrWdouIbRD1U5+ktkHiGpu97TqH2QYZoO5acNeeNha/NikxI74jRlgSvPEpid3jxySe483oov2paZfSFiXPXOK+QPKjE+HHRypXeXaaPjsjWePYfq0nNH7aH9CPB/cH7R39gTeSPRPtDygf7Q9a6+Npa+59gdl/b40qfL2k7fVFxO7fmyY6+wLnlqKR+/qbxc9vWBuZ4NYXEObh+/qn5P43rQnu+1riP6yvN/X6xEn2vb7mvepjcTue/m2gXmNXRHEzTDQsXft89btJ/C4J8Xe6+HOrIxnwCfGzxZrM87Qdqb8BxibF+9la3q56m+5l3X1S2/t+5+93gu7XvotAOsAH4GuU73YJt7Gad1nz+/3qCOmfCThgNylvithYcStPwgh9t62ocu5RGid+E035viruT+L3uMq1fDU8k8eekDy+T+7/xPN1j0f6c6/fD6kb7ulvwgpc97juQ98N3i/3t3uu8cRbjndZU5dfl/szPJ9b/fWax8qV9BSSduyM6PNfm2xfuxpX/axSct6l35W03ynulmpe+MM6kZASHL8pZg9ak4dvi79MPfdYM8VfKrXqDMm/pBzZF1ckWf/uAKljMLo6dtaU8Dr2qvQnUheC38W1jNOC9yzWOHMtwnv3IX3wYo+Pp8GXecb+KVoP3b+pTN3Jn4o7dv3ZasW71UXCcf/OytK6c0jup3gK7FIn1/dbXrc6SDiuddDtmwq3rt9UZp/psRLnl62hfJV+i1h20npUJtfb6/7I4e8S6fBacXM2JX+i+d1vkWupDn/YslKP/nfe9uImzdOP3N+DuNX/znCKuMvhPNH8ptXLtQ2UXSG9XzdXvxnwLnFXSC5mmr4ufhrXuGL/BibR52RS3ik55FO7xiv8v4F/9f+Wq5spnHtzkORzvMmZgd/9sgwRcesPbwVuO9puOzQ+7Q/vgIantjxMne+EQDnfmw2j7GtJg7aDtn2PahsI268+VxUX/4J4kLeRNwivaZqp80G/rW572/bSPL9B/LzBOVaVkEakGdE9ODXMO0z91Gtu/bOpA0OnS39MnMeb374/iJ94t7ZBeO5tI0vb6P1yv9nqRYhnIjdb7VzbjYbjqMdkgQQVeJcYKHGbxTtte2f/bOr5qxLGTVY+ca2WOuzod4try1aWVFQxyKN1G701CW8YsYojfikm30bI9WnmO426IvJhtlDkmCj60fD9PqPvN512ejamh9sietMen5jutEXEmzc2kyoxhmHaVhR2g5w2j0ZnuNtl2jP9i9ll2jP96Ntl2ucSxz/hdv/0kP1Drej2Dt0fHEf6mOjjWBkhjs1dwuP4Z9y2BMexoW5FdHHEX9B7C79j9bXuY0rGrekP25DnleG2o7Tu8ryQNG7t6m4fy5rxxexjWTOit49lzfjX2sc6CA8R8GzRVY67vaJPv0s+GJN1KKtzl58sfTGyTu8nokt8y4oHMua9fdPOlKs/uuhHvQv/3Hbd5rbq+rrrEkfSAY6sY7xf4tnz+WUpleecdPkfkq+s6Td43m1ttwvlrmsdWfd7iOTDHTeVz9+R8M7LP799wOebNq6/ve062O6631/MntNshz2n3caek/mb95jA3x0df3sDf8v3ex78DaL7E+qYu8wjcC94f8Kv6H5rl8JU2AjHwavheHg5nAnXwaXwClgKr4I1cD1sgM79TJv1ecU=
*/