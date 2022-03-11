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