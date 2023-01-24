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
AeW3zSTqVvUmrtOvPTmSPqHBSxa5EPcA9HH73Jty9aNufYdtULBurg5TglLBcfUXJqMVseZoBSrva6oEJb/7HcZq6+Kn5RWJ9wELKMx5lmVoU21jcvL+0piYmZ7Q2KzwmMSkJWDwq63lKFY0ihigxA4TTgzc/Ix8APc2KDBIaioLaNBu18uletu5QtPnVUhlBxxR0gpRAjU+kl7AQWmhtA9B324/PQDQe8JPc/QiMFouv7SgcSM/vM58QUy6xiCkVzWPRbllij2R2Ujw3+LQDIniw1cAsc5b6UxSrtQT2yFcJUj0pxyRd0tQ/5uHMVI1mAaeacRl/qh5nHdIeE2dD0qnhpZ0zl95FGvVLTOorrBSCO9CWwtwxyzkp8nr844HcSxYhMAf57FEDLJN5fPIyxrED/tg2jsIrAFBS4Y7H7PVBwMMKY2ikhybi20dmEQOvD1c7CaTugMCbC912n43gkwLqiNA61/Cdrwfwbw915b6QYubp+2yyCCrezF1atcC2WNvASy6bfm2oO/3Ymhuj2xBnkr7F8eV8VoC9uSuacq+2eJC87R6og/WEVxFA5UQXkVLW+edfW1bOWQ38cY6DvNmX97W9/eU8vk6lxNz0kzy06iXeMZpOAcv/1jUynUZ0Q2Jf1ey/iJLIKmB0QNRqkEFQctL1HJDHmb3Ab6Arj/WvPyqQ/mmXM6PEyKXKiDddf/oFYuoYqt0dQ0S
*/