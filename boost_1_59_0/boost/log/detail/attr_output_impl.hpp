/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attr_output_impl.hpp
 * \author Andrey Semashev
 * \date   12.08.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_ATTR_OUTPUT_IMPL_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTR_OUTPUT_IMPL_HPP_INCLUDED_

#include <boost/mpl/is_sequence.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/utility/functional/bind_to_log.hpp>
#include <boost/log/detail/attr_output_terminal.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace aux {

template< typename LeftT, typename T, typename FallbackPolicyT, typename TagT >
struct make_output_expression
{
    //! Resulting expression
    typedef attribute_output_terminal< LeftT, T, FallbackPolicyT, to_log_fun< TagT > > type;

    //! Creates the output expression
    template< typename RightT >
    static BOOST_FORCEINLINE type make(LeftT const& left, RightT const& right)
    {
        return type(left, right.get_name(), to_log_fun< TagT >(), right.get_fallback_policy());
    }
};

template< typename LeftT, typename RightT, typename ValueT = typename RightT::value_type, bool IsSequenceV = mpl::is_sequence< ValueT >::value >
struct make_output_actor;

template< template< typename > class ActorT, typename LeftExprT, typename RightT, typename ValueT >
struct make_output_actor< ActorT< LeftExprT >, RightT, ValueT, false >
{
    typedef make_output_expression<
        ActorT< LeftExprT >,
        ValueT,
        typename RightT::fallback_policy,
        typename RightT::tag_type
    > make_expression;

    typedef ActorT< typename make_expression::type > type;

    static BOOST_FORCEINLINE type make(ActorT< LeftExprT > const& left, RightT const& right)
    {
        type res = {{ make_expression::make(left, right) }};
        return res;
    }
};

template< template< typename > class ActorT, typename LeftExprT, typename RightT, typename ValueT >
struct make_output_actor< ActorT< LeftExprT >, RightT, ValueT, true >
{
    typedef attribute_output_terminal< ActorT< LeftExprT >, ValueT, typename RightT::fallback_policy, to_log_fun< typename RightT::tag_type > > expression_type;

    typedef ActorT< expression_type > type;

    static BOOST_FORCEINLINE type make(ActorT< LeftExprT > const& left, RightT const& right)
    {
        type res = {{ expression_type(left, right.get_name(), to_log_fun< typename RightT::tag_type >(), right.get_fallback_policy()) }};
        return res;
    }
};

} // namespace aux

#define BOOST_LOG_AUX_OVERLOAD(left_ref, right_ref)\
    template< typename LeftExprT, typename T, typename FallbackPolicyT, typename TagT >\
    BOOST_FORCEINLINE typename aux::make_output_actor< phoenix::actor< LeftExprT >, attribute_actor< T, FallbackPolicyT, TagT, phoenix::actor > >::type\
    operator<< (phoenix::actor< LeftExprT > left_ref left, attribute_actor< T, FallbackPolicyT, TagT, phoenix::actor > right_ref right)\
    {\
        return aux::make_output_actor< phoenix::actor< LeftExprT >, attribute_actor< T, FallbackPolicyT, TagT, phoenix::actor > >::make(left, right);\
    }

#include <boost/log/detail/generate_overloads.hpp>

#undef BOOST_LOG_AUX_OVERLOAD

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTR_OUTPUT_IMPL_HPP_INCLUDED_

/* attr_output_impl.hpp
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
*/