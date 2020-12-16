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
bwL0frfZ9fUB+nembr8mx1TXbyEilZDPkBrkK2+B5Zr0Wmc1TlvXmHZMrpawHxpvGKHOa+UFuv4155Np5lwyV/y2G1uIafZ9Kb+Oqf61k4R7nZmMflO2njHnj5ni/4GxU22l76Z0OxlkFsq6o7jEco9hszfcvb6uJyztt0zEvrZw/i5NWNW466VeM/PzHdpV226p5I33pHS87HS98/j4aA39pr/L1xYHYBPSWrTQ0hbTM/Onnj4+mvU06yZv2LewChPi2BakZV9bSl0X5GWmtzHHkrslzOc8DlpESpUd15blp9PWHNvqSV5auppxh/Ki4TbzuEriTqM+4xz3IDRtS3+QQmdYx83vJEyJqxX7EQuM99ReuctYJ+6xRjxxR8ucb5ZPL6iyNfQyCfu2qyU1c6Er1CFOW1ucWHiPxHnflcy/vV0uozX9qJL/+lf5roGI2Ze+b1DxPnX29apZHt3LCnRva1u3FqoRrK36TPoWpJ63T91o6VPeSy01PTfn6sz8wgrOvcR3aH+5Zs36vVvCbDBu5syrEKd+ZKZjzk+F+Wk5BVO4LzPitc4/lTD5RiVK1pe/LkfitG9o+GyWhGb/kCJLOw0zGhGnGxI4/1XRcPdI2pXUNnnZGHCkgchp7eX5l9pL6kWu/Wf0/mK8jgXbAvR3Td1+DzopXr8Z58ZdOZYwKxaZ7aid1duCRoXaUOI6t6E5N950O2E4Y1OtrwclTgN3Y9wmIV9g8+8ULTnX5ea9Zcc2Ns9T39wrSSsoKKLLZacVFKZmFaRmZJFlpz1oex4npqjdrazCrNwcw/yO+HmSx2ddF7jijbJvLXgTlzCyxm8rYRa7PBIGN7RkLVvgWq++9rs1cu567kbenQ/kWherRRfjmI4TgWu0WvCAxPmbqwn9vTf1Uci4Yr1/fRCBOjacvX9V4XcMmTHvIF2LPkb1asxBj0o5jMaDhvCRZnXLLnNL8bsNKnNra5xj320oY43uPTm3H+lFaBsNGJI6ZGifvhY3l9etT99RA3r3Nd3cXrd+Awb1DdiT3FNHv02s9kXW65pk0fWWvl6UI6uSwH5eX/vpnRL2KaMB/3ZAMpG7nfdbNF2XdV1hjmHvi18u5edZa8S7j5XBtZhIHo+KvdgLPSGVDMuerO5raLhhdfz7I02c9kckTGEdc51SGrhO0XHJtvex7F/c9/COL79a1x5qK6u5u3ybUs42ls7dhtaCEK/7X0a9Glr5hpOPN1y3t2Hz+wdeVL6NriYLXbh3Lz0eM2XFoWvTlvTdfqhd/tHybWU5274q3xbXJspM+gmZx6+dMLVVyNVTo+d8k/ku+zzi/v7tX+zolZm1vOSHayY/1fCvYedu++qPsnHlbGOsfFtizjbDyrPFde42wI57xx5DDtnH3QezOech/XtdmPR3Wbtejl5i+Xuh+bdcO/q37z5tEfwG3XwPT/cQwg38At6nu0zfpxsFw+Bo6I+3WeO1RfYFxHsyzBdvHWwDn4VH/eXRvd82er5IZJDG+4pBR8oL4+EheL7qzeHfYSv4HUyC38Jk1f12k3po+mGyrrfbTaIOzHDDKhhuUgXD5VUgnLyvb5b/9Hr7IdxX/l9gMvwdHoUr/HvMcK/WW1VkicZbgbcLPgTj4SOwJXxU38ffCC+GT8AJcC2cBJ+Ec9T/WrjOexr4DPwTfBYuh+vhBg33HFwD34Z/he+q+1G5bnW/VPdvF8EGSKj+5v+7tme022d/xAPlG2rwUlgFXga7wWxYFc6B1WExjIU3whqwFMbBW2EDeBdMgA/AhvBx2Ag+DRvD52ET+B5sCj+AreD3MFHt6STBX2Fr6HLRt2EV2BEmwM6wGewCW8OusC1sBzvDFNg=
*/