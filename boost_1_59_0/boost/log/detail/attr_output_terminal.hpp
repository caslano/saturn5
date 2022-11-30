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
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
*/