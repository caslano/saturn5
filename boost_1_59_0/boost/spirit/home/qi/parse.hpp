/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2001-2011 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_PARSE_APRIL_16_2006_0442PM)
#define BOOST_SPIRIT_PARSE_APRIL_16_2006_0442PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/context.hpp>
#include <boost/spirit/home/support/nonterminal/locals.hpp>
#include <boost/spirit/home/qi/detail/parse.hpp>
#include <boost/iterator/iterator_concepts.hpp>

namespace boost { namespace spirit { namespace qi
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr>
    inline bool
    parse(
        Iterator& first
      , Iterator last
      , Expr const& expr)
    {
        // Make sure the iterator is at least a readable forward traversal iterator.
        // If you got a compilation error here, then you are using a weaker iterator
        // while calling this function, you need to supply a readable forward traversal
        // iterator instead.
        BOOST_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<Iterator>));

        return detail::parse_impl<Expr>::call(first, last, expr);
    }

    template <typename Iterator, typename Expr>
    inline bool
    parse(
        Iterator const& first_
      , Iterator last
      , Expr const& expr)
    {
        Iterator first = first_;
        return qi::parse(first, last, expr);
    }

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T>
        struct make_context
        {
            typedef context<fusion::cons<T&>, locals<> > type;
        };

        template <>
        struct make_context<unused_type>
        {
            typedef unused_type type;
        };
    }

    template <typename Iterator, typename Expr, typename Attr>
    inline bool
    parse(
        Iterator& first
      , Iterator last
      , Expr const& expr
      , Attr& attr)
    {
        // Make sure the iterator is at least a readable forward traversal iterator.
        // If you got a compilation error here, then you are using a weaker iterator
        // while calling this function, you need to supply a readable forward traversal
        // iterator instead.
        BOOST_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<Iterator>));

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit qi expression.
        BOOST_SPIRIT_ASSERT_MATCH(qi::domain, Expr);

        typename detail::make_context<Attr>::type context(attr);
        return compile<qi::domain>(expr).parse(first, last, context, unused, attr);
    }

    template <typename Iterator, typename Expr, typename Attr>
    inline bool
    parse(
        Iterator const& first_
      , Iterator last
      , Expr const& expr
      , Attr& attr)
    {
        Iterator first = first_;
        return qi::parse(first, last, expr, attr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr, typename Skipper>
    inline bool
    phrase_parse(
        Iterator& first
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , BOOST_SCOPED_ENUM(skip_flag) post_skip = skip_flag::postskip)
    {
        // Make sure the iterator is at least a readable forward traversal iterator.
        // If you got a compilation error here, then you are using a weaker iterator
        // while calling this function, you need to supply a readable forward traversal
        // iterator instead.
        BOOST_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<Iterator>));

        return detail::phrase_parse_impl<Expr>::call(
            first, last, expr, skipper, post_skip);
    }

    template <typename Iterator, typename Expr, typename Skipper>
    inline bool
    phrase_parse(
        Iterator const& first_
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , BOOST_SCOPED_ENUM(skip_flag) post_skip = skip_flag::postskip)
    {
        Iterator first = first_;
        return qi::phrase_parse(first, last, expr, skipper, post_skip);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr, typename Skipper, typename Attr>
    inline bool
    phrase_parse(
        Iterator& first
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , BOOST_SCOPED_ENUM(skip_flag) post_skip
      , Attr& attr)
    {
        // Make sure the iterator is at least a readable forward traversal iterator.
        // If you got a compilation error here, then you are using a weaker iterator
        // while calling this function, you need to supply a readable forward traversal
        // iterator instead.
        BOOST_CONCEPT_ASSERT((boost_concepts::ReadableIteratorConcept<Iterator>));
        BOOST_CONCEPT_ASSERT((boost_concepts::ForwardTraversalConcept<Iterator>));

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then either the expression (expr) or skipper is not a valid
        // spirit qi expression.
        BOOST_SPIRIT_ASSERT_MATCH(qi::domain, Expr);
        BOOST_SPIRIT_ASSERT_MATCH(qi::domain, Skipper);

        typedef
            typename result_of::compile<qi::domain, Skipper>::type
        skipper_type;
        skipper_type const skipper_ = compile<qi::domain>(skipper);

        typename detail::make_context<Attr>::type context(attr);
        if (!compile<qi::domain>(expr).parse(
                first, last, context, skipper_, attr))
            return false;

        if (post_skip == skip_flag::postskip)
            qi::skip_over(first, last, skipper_);
        return true;
    }

    template <typename Iterator, typename Expr, typename Skipper, typename Attr>
    inline bool
    phrase_parse(
        Iterator const& first_
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , BOOST_SCOPED_ENUM(skip_flag) post_skip
      , Attr& attr)
    {
        Iterator first = first_;
        return qi::phrase_parse(first, last, expr, skipper, post_skip, attr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr, typename Skipper, typename Attr>
    inline bool
    phrase_parse(
        Iterator& first
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , Attr& attr)
    {
        return qi::phrase_parse(first, last, expr, skipper, skip_flag::postskip, attr);
    }

    template <typename Iterator, typename Expr, typename Skipper, typename Attr>
    inline bool
    phrase_parse(
        Iterator const& first_
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , Attr& attr)
    {
        Iterator first = first_;
        return qi::phrase_parse(first, last, expr, skipper, skip_flag::postskip, attr);
    }
}}}

#endif


/* parse.hpp
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
*/