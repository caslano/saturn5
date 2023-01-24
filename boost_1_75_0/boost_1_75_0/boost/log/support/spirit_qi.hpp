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
Zsm5/sPyRor3KHrjtWOL4TRf+RyM0K/refKqyhqESENoZYcQb0pPKj63ki29hQNeWq7mPpIL3nQtCi/y13pQ1cd7HWyGqT4gEpJQrhUK4ZtngZsh47c9Kz7JsMpL/FchYbLO+Y9guXsxIljKb3ND544sMRaxwOcnbCbzdCHs5xstA9M80AxSt86dbRPZ+sc+TMjzUQf57Pzr8eQVaFr7kVwk9OA5F3H9FiSmXJ5bFXat0ir1V4TFiM94xvxbZeG1g6sK+iuU/+fLc37B/5ExR7LoI+nXKsP9Fo2Y4kNKaiM6BdovRmngh4+Ir9lDFhFYQJUqitZI/mknxaJcdJuIFmVVI6GNcWFmVyPgSevM/paaC1g9XdB3XdB1tsJ1LTa9QslIjNmHXkmn637lu0f3/YX1p4Ruo695F87p3LBg+/3pnoMNaEeD1/m5l7kBfACT3vyZUU1FrDrCDDI/0/2Nt0Lzu8LL6MdQieyJvQQvKTUp/SNMafydhe8jTcQAyX29PicL/EYyA8wCwtpP3uXaXrk/iiuQxY5Syygp3jg6NIDYkUoAuu0s8Z8ctQGSiufOBdzjxZnzT8OtKRLe9rD29YPclEXuNNtMfmlsKnSKCJjbRw88YpFvQ0y49/6Uzycfu1wgnVS5AIw7J95N6oCDeofN/T7g6PyJScF++kjHSHChCSdyvY804wBUczBv4Xd4dVlwDzFC4vedRzx3
*/