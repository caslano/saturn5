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