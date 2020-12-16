/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/spirit_qi.hpp
 * \author Andrey Semashev
 * \date   19.07.2009
 *
 * This header enables Boost.Spirit.Qi support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_SPIRIT_QI_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_SPIRIT_QI_HPP_INCLUDED_

#include <boost/core/enable_if.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_domain.hpp>
#include <boost/spirit/include/support_unused.hpp>
#include <boost/spirit/home/support/meta_compiler.hpp> // spirit::compile()
#include <boost/spirit/home/qi/nonterminal/nonterminal_fwd.hpp> // rule forward declaration
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/matches.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! This tag type is used if an expression is recognized as a Boost.Spirit.Qi expression
struct boost_spirit_qi_expression_tag;

//! The metafunction detects the matching expression kind and returns a tag that is used to specialize \c match_traits
template< typename ExpressionT >
struct matching_expression_kind< ExpressionT, typename boost::enable_if_c< spirit::traits::matches< spirit::qi::domain, ExpressionT >::value >::type >
{
    typedef boost_spirit_qi_expression_tag type;
};

//! The matching function implementation
template< typename ExpressionT >
struct match_traits< ExpressionT, boost_spirit_qi_expression_tag >
{
    typedef typename spirit::result_of::compile< spirit::qi::domain, ExpressionT, spirit::unused_type >::type compiled_type;

    static compiled_type compile(ExpressionT const& expr)
    {
        return spirit::compile< spirit::qi::domain >(expr);
    }

    template< typename StringT >
    static bool matches(StringT const& str, ExpressionT const& expr)
    {
        typedef typename StringT::const_iterator const_iterator;
        const_iterator it = str.begin(), end = str.end();
        return (spirit::qi::parse(it, end, expr) && it == end);
    }
};

//! The matching function implementation
template< typename IteratorT, typename T1, typename T2, typename T3, typename T4 >
struct match_traits< spirit::qi::rule< IteratorT, T1, T2, T3, T4 >, boost_spirit_qi_expression_tag >
{
    typedef spirit::qi::rule< IteratorT, T1, T2, T3, T4 > compiled_type;
    static compiled_type compile(compiled_type const& expr) { return expr; }

    template< typename StringT >
    static bool matches(StringT const& str, compiled_type const& expr)
    {
        typedef typename StringT::const_iterator const_iterator;
        const_iterator it = str.begin(), end = str.end();
        return (spirit::qi::parse(it, end, expr) && it == end);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_SPIRIT_QI_HPP_INCLUDED_

/* spirit_qi.hpp
7A5iRa6YGXc5bjWnRWR7Z55hirjrYvqhxuKminmm20UeJenSnmcqkmeq6n/YTXCtY1/q7+XirgHlt4r5ZporZgWesa9GGk4orvVNfgyS/EiVMdA0ws0XtzE+M/ZFy/AKJhHjXyY9mol/jd3Gzn4107pMWg9x7jX1srWYjXaDYdrGykLt4RPy3NWOOla2VvybTMxrOCd4xso+EvMW+F3XqaXl43B8ukvefC3fUdJWSRjZyC1jaCbf2kr6lKZtc/GroduQsdHJ1PVot4ruCQw9d1u3Bz5PRH6D05ResZHJ0w4iH+4m8L/le8bMx64Re2tUr3lETuTThzWQPqwC42p6Rnp76B1T64AeORQ9/Zf8bYiS/qqjznW9eQzjZ4Pij/1u/2Ppr2xjZJhJHpKvmEm+hn0HzG7pyG+w9l9p2n9NTYjsvxbNWVA4n3wI68PMnMPNYt/vN/MUoq/jH+rrYv9OSCjbRyXqmPGtIjvkm01Juctt5Jo5ODHvb/82QGabWyvEv9tF9qMv1C+9WkfaGrNHcYPI73GW8s52Cb5ZvxewY5tjK8b/u0T2d1+ozl8n+vd8LXwrzZjJyrqyH9z+DZFg7ZfMfNF9Iv/GF+qTLhZ9uu9DN2DqwFLxv5n9GyPhyP1QbG3ZV8rTVy99n65bOmc1nzg8Jn587vN+MyTq/EWWuJ/ty3Brch7TDmv/EiNpnuZmOc+a/mWXmA0z/cvww3qe6nP2KaVa526ixU6c8SNO4plp2rdEkefIPExk2ido+UoQOxtof5uX2x9tlGfqbPqjUeLGj17bUZHXFD9Pxs/vJX3u9s1zk47YH70o7upJfxSaJ3Pr6LhLmN+r8P0kp4HOa94iZo7PRy7VRtLMqVvunMvJ4t9w19aP8CzyG1q7Yv3Ik+LXlDJzLil1PXMuWg4WHa5X7pH6ixnizle6P1jcNHfPcM4jz9Uck6pi7xJ8b80eLMaINZ2nif1s90j9w8463v5B85+UnEL/kFjB/sHbJ3ydKGbQ9An8bYgqnU/Zegz9wcq6v31/EGz7B+r567M7OvKr7yO/YV2Yh92VidL2Dx/ZP3fAhJzcfmMHDx+Q229kzsTcgaNHDs/NGT2g74kDw/qBPFNeqiZJ2SUnx7lT3ERb24//4e2Rq+PSoTq9sp7Ms1vbea/bFDlbW4bv9ZsiJK9PPVzoab9tYc6ZsRSGzp4eKvEe4YbKUEvR32DOK3hW9C+w/qXE1oYb/xOM/6bum7K+Tuxcy5tKFF9bo/X7oTTOI91bPO228TO8PdU24xaJz8u0fGeYOYdMMRto6sET4n6amdddKukar/KQvoEZT98h7j+1truvi1+Z5tvuBbG7nfigN+nzEvm7XdJ4RjcZC5qWN38mdnQcX/x4n5F0xmE8beSM4tmld0aInY5uSujMFhPPxuhDYx3Tpk/33KnyqrjJMWcJ7BX9LsrgzW6pm2WdHc+dG/dJfD9wPPI0ketY5VSRd/O0M0sXFRfNmTHT0292FDtD3Bec4zQuobg2MuM0XcXONG880vnPjHOtFHl9rzxD5DpOtFnk30Y+u5lXeU7kd7D/NVnNQnnxpOPDvNbhMqZmr1IWh8fP553vi7bMOaRSN2pMjfHFO2I+G7NPUPOSws1XYvYhan7QPGpWDEd5eMd3TT/2vqR7NScBN1difx9qQdCNbyFxGRHvVckajwvaaTz8K/8e40+M8VWN8VXHr6B8P+7XIic+ZeQNkMchW42aL/JVNVXojZtJpzR5/lMoVQMlfmnt5CBhjd+qJuXFr3l7jZ9v5Zcx/kBMVCyPr/Fbh/sU5MQvUi7ptgN5o/ahdFvlIPHGzdStAolbosRrL27qtTfxqlFevB4pjdc=
*/