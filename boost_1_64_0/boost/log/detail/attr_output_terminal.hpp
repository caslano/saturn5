/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_output_terminal.hpp
 * \author Andrey Semashev
 * \date   06.11.2012
 *
 * The header contains implementation of a generic output manipulator in template expressions.
 */

#ifndef BOOST_LOG_DETAIL_ATTR_OUTPUT_TERMINAL_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTR_OUTPUT_TERMINAL_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/environment.hpp>
#include <boost/phoenix/core/terminal_fwd.hpp>
#include <boost/phoenix/core/is_nullary.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/custom_terminal_spec.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/value_visitation.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

//! Attribute stream output expression
template< typename LeftT, typename T, typename FallbackPolicyT, typename ImplT >
class attribute_output_terminal
{
private:
    //! Self type
    typedef attribute_output_terminal< LeftT, T, FallbackPolicyT, ImplT > this_type;
    //! Attribute value visitor invoker
    typedef value_visitor_invoker< T, FallbackPolicyT > visitor_invoker_type;
    //! Manipulator implementation
    typedef ImplT impl_type;

public:
    //! Internal typedef for type categorization
    typedef void _is_boost_log_terminal;

    //! Result type definition
    template< typename >
    struct result;

    template< typename ThisT, typename ContextT >
    struct result< ThisT(ContextT) >
    {
        typedef typename remove_cv< typename remove_reference< ContextT >::type >::type context_type;
        typedef typename phoenix::evaluator::impl<
            typename LeftT::proto_base_expr&,
            context_type,
            phoenix::unused
        >::result_type type;
    };

private:
    //! Left argument actor
    LeftT m_left;
    //! Attribute name
    const attribute_name m_name;
    //! Attribute value visitor invoker
    visitor_invoker_type m_visitor_invoker;
    //! Manipulator implementation
    impl_type m_impl;

public:
    //! Initializing constructor
    attribute_output_terminal(LeftT const& left, attribute_name const& name) : m_left(left), m_name(name)
    {
    }

    //! Initializing constructor
    attribute_output_terminal(LeftT const& left, attribute_name const& name, impl_type const& impl) : m_left(left), m_name(name), m_impl(impl)
    {
    }

    //! Initializing constructor
    template< typename U >
    attribute_output_terminal(LeftT const& left, attribute_name const& name, impl_type const& impl, U const& arg) :
        m_left(left), m_name(name), m_visitor_invoker(arg), m_impl(impl)
    {
    }

    //! Copy constructor
    attribute_output_terminal(attribute_output_terminal const& that) :
        m_left(that.m_left), m_name(that.m_name), m_visitor_invoker(that.m_visitor_invoker), m_impl(that.m_impl)
    {
    }

    //! Invokation operator
    template< typename ContextT >
    typename result< this_type(ContextT const&) >::type operator() (ContextT const& ctx)
    {
        typedef typename result< this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        m_visitor_invoker(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()), binder1st< impl_type&, result_type >(m_impl, strm));
        return strm;
    }

    //! Invokation operator
    template< typename ContextT >
    typename result< const this_type(ContextT const&) >::type operator() (ContextT const& ctx) const
    {
        typedef typename result< const this_type(ContextT const&) >::type result_type;
        result_type strm = phoenix::eval(m_left, ctx);
        m_visitor_invoker(m_name, fusion::at_c< 0 >(phoenix::env(ctx).args()), binder1st< impl_type const&, result_type >(m_impl, strm));
        return strm;
    }

    BOOST_DELETED_FUNCTION(attribute_output_terminal())
};

} // namespace aux

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

namespace result_of {

template< typename LeftT, typename T, typename FallbackPolicyT, typename ImplT >
struct is_nullary< custom_terminal< boost::log::expressions::aux::attribute_output_terminal< LeftT, T, FallbackPolicyT, ImplT > > > :
    public mpl::false_
{
};

} // namespace result_of

} // namespace phoenix

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTR_OUTPUT_TERMINAL_HPP_INCLUDED_

/* attr_output_terminal.hpp
A7aHvSDlkHrZ7dL9Lt2TWwQ7Itu0XtpTL9GwC6wFu8J2sBvsCBfCrvAi2B12h31hDzgS9oLjYW+YCvvCybAfvApeDPPhAFgEB8Lr4CWwGA6G8+FQeD0cBm+Hl8IlcCR8HF6mdndGwTfhaPiO5m8vHAcPwPHwH3AiPAUvh2GUNRXWhJNgHTgZ1oPpsDHMgK1gJmwDp8D2cCrsALNgV3gFHA6vhFfBXFgEr4KlsADeAYvgE3AGXAdnwlfgLPg5vBZ+BefCX2ExDKF95sEEuACmwBtgT3gj7AcX6nhz0NxzYV9Hr8t4i03EVJJ0w8mwFsyAdWEmbAKnwGZwGkyGWTAFXqHX7ZVwPMyGE2EOzIO5sBDm6XVLG0t7FsASiJ+0XxF8EBJGroO58GV4HXwNFvP/W2q3Yw+cB/fCWfADeA38TN2PSjvrnoHunSyCrZE52o9LvfUHb4fy25n248WwM9wBu8D7YBq8H2bC5dpPV8AC+ABcAFfCm+Cd2h/vguvh3XAjXApfg/fAnfDP8HO4Ch6Dq+EJ+CAMdTE+wij4V+2HD2s/fAS2g4/CQXAHHAyfhGPgU3ACfBpOhuvgNPgMzIHrtf9tgLPhc7AEPg/nw43wFrgJLoYvwHvgS3A53AxXwy3wEbgNroevwtcgInYxtsMDmj+dF/S+nn0Hh3lhp7bHblgTvg2Hwr1wrOrj4Qda7x/CGfAjeBvcr9f/F/BO+ClcDj+Da+Dn8DH1f1zdN6n7FnHX+dHtv7+UMVjy2ROJdWs+9TrZBSPhO9AD39Xr433YCrbVef9D9N7wI53X9sPJ8GM4VcNNg1/o9fAlnA//pvPbV3Ah/Bougt/CO+Bh+Kjay3kG/gQ3QfqQlOdnvW5+ga/Dk3An/A3uhr/DdyAF5foB8DPohl/CKvArGAGPwFDtnx5IHPF3w2gdLz2wkrp7YFXtt9VgbVhdx89YHT9rwBYwDibCmtqva8MuMB52g3Vgd1gX9oIJsA9sCPvCptr/m8MRsAUcC1vCVNgKToGJMBsmwQLYGs6CF8Bi2AZeD9vCG+D3amfnB/gkPAafVX+1n6L3iFxL0p/t9lOu13XOjTAKLoTnw5tgY3ifjqs3w/awFHZV9wvhLXAgvBUOgbfBKXARvELDXal2iGbAxbBU7Q4thUvhMg2HGH+Ga+EyuF7d67oZR0ZHed/xPut74PuRnYTdUOJ797su8iV6HixGliEbEP/73kcQy3ve+n63/d3uPeb73ea73Y7vdW9CIsfw3jAMfJ97ErJ2AO8r3xsp73WvRQ6gH0H873U3J27gu92FSCmyDOmBv/V97tAeZe90D9L3us/0TndoT8pHGv73t3sg2cgk3JIHlr27vQnZh/jf3455jnQJ4/Tu9kJkqe3d7bO/s71C39v2v6+9hLQ3IHuQY0jM2CgjEemPZCBzkGXIZmQ/cgKJHcc72ciYccF3YoNH8Age5R+hyBX/+ef/r55e4H36/9979t/7bP+xBj77czH/h3ubwT3M/+0eJvdnFV4H6frn31r7VHTdU86aR9c65hrnTOubf3ttY1/XlLue+Y+tY4JH8AgewSN4BI/gETyCR/AIHv/747/0/r9G+GP2AI4H9wCCewDBPYDgHkDwCB7BI3gEj+ARPIJH8AgeweOcjv/S7//ZWZP//Xt/r+2/89vwXPVEsf2XOSWNl/RSMeEnNgB9tv9OsDfQwW/7T285igzzO4Ni36fHbNP2n8W6z+nvVsapDbQ+Ev5KoyVnSDEaOtsZkzCOtn3M9xkHSZhEScHpfUpNQ/JxiDTUpov5zuZM8a9r2uxZp+EttgpUzm7D8OzvCNrt51wt5+LeOkXt52gdPxqi38DWxNl6kfc=
*/