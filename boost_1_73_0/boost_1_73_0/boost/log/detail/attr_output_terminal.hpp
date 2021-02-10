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
OfwmG7vPGrsdi1KXVCoCT/iNnDODkWGVjiQG3sYpjebW2hKQAYesTxP0ng1jXhcy7typoeSOQxwHXZAVcBElU2MkYifT3OsqwdN0uqWiwS4C9CvP0bhSV+Tq/G1vsztcmrPAXncPT9wDtw/V6r+O6M56OCxn9BiedMapmDexocwyLYnT0SWvdV0CRuWsKLMJqy5EyFtgblXfRSmy0B9dW52E6S2TJZ34BXpuI+OtEbxj6d4Z4wuy4o64L2+keFFmHUoI72OXyUvC9yVVeIcI0ySrNlXaHsCrtt/Rf5/xG7tGa/4C9mm389J6ANt3e7fZy9da/w3vwMp7tPJq3n26Ge+7B7uCre7fF/rMk97AC6PA12V2ubbOr2nwO+1it8D7QnT9p7zAuXMvtkMnK5QZV+TDFamM2IvO0VH35f7Z0R7bsVvwGb3gSwjxynG03uZmRX5iIj2kc+FmMDjqaMrvcUv3QEisk2dQXzKO2gm53GB2oVLPrft5nc3px5e2hD9WYjb/0fjEM2K8XDLTC+iGlJhzHe6DJR1K4P+edKuaW293mbhmU7Yw5rtwsu6WDV1rl8VKl2rXL0SqawBrRSZ269K94HULWJzJbMSzjXDfnWRlJFjGi2lWJYvlVa/NOe9ceO/JaX7ZRXbtVt+j
*/