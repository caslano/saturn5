//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2009 Carl Barron
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#if !defined(BOOST_SPIRIT_PARSE_ATTR_APRIL_24_2009_1043AM)
#define BOOST_SPIRIT_PARSE_ATTR_APRIL_24_2009_1043AM

#include <boost/spirit/home/qi/parse.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 <boost/spirit/home/qi/parse_attr.hpp>
#define BOOST_PP_ITERATION_LIMITS (2, SPIRIT_ARGUMENTS_LIMIT)
#include BOOST_PP_ITERATE()

#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()
#define BOOST_SPIRIT_QI_ATTRIBUTE_REFERENCE(z, n, A) BOOST_PP_CAT(A, n)&

namespace boost { namespace spirit { namespace qi
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    parse(
        Iterator& first
      , Iterator last
      , Expr const& expr
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, & attr))
    {
        // Make sure the iterator is at least a forward_iterator. If you got an 
        // compilation error here, then you are using an input_iterator while
        // calling this function, you need to supply at least a 
        // forward_iterator instead.
        BOOST_CONCEPT_ASSERT((ForwardIterator<Iterator>));

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit qi expression.
        BOOST_SPIRIT_ASSERT_MATCH(qi::domain, Expr);

        typedef fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_QI_ATTRIBUTE_REFERENCE, A)
        > vector_type;

        vector_type lattr (BOOST_PP_ENUM_PARAMS(N, attr));
        return compile<qi::domain>(expr).parse(first, last, unused, unused, lattr);
    }

    template <typename Iterator, typename Expr
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    parse(
        Iterator const& first_
      , Iterator last
      , Expr const& expr
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, & attr))
    {
        Iterator first = first_;
        return qi::parse(first, last, expr, BOOST_PP_ENUM_PARAMS(N, attr));
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr, typename Skipper
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    phrase_parse(
        Iterator& first
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , BOOST_SCOPED_ENUM(skip_flag) post_skip
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, & attr))
    {
        // Make sure the iterator is at least a forward_iterator. If you got an 
        // compilation error here, then you are using an input_iterator while
        // calling this function, you need to supply at least a 
        // forward_iterator instead.
        BOOST_CONCEPT_ASSERT((ForwardIterator<Iterator>));

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

        typedef fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_QI_ATTRIBUTE_REFERENCE, A)
        > vector_type;

        vector_type lattr (BOOST_PP_ENUM_PARAMS(N, attr));
        if (!compile<qi::domain>(expr).parse(
                first, last, unused, skipper_, lattr))
            return false;

        if (post_skip == skip_flag::postskip)
            qi::skip_over(first, last, skipper_);
        return true;
    }

    template <typename Iterator, typename Expr, typename Skipper
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    phrase_parse(
        Iterator const& first_
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , BOOST_SCOPED_ENUM(skip_flag) post_skip
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, & attr))
    {
        Iterator first = first_;
        return qi::phrase_parse(first, last, expr, skipper, post_skip
          , BOOST_PP_ENUM_PARAMS(N, attr));
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator, typename Expr, typename Skipper
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    phrase_parse(
        Iterator& first
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, & attr))
    {
        return qi::phrase_parse(first, last, expr, skipper, skip_flag::postskip
          , BOOST_PP_ENUM_PARAMS(N, attr));
    }

    template <typename Iterator, typename Expr, typename Skipper
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    phrase_parse(
        Iterator const& first_
      , Iterator last
      , Expr const& expr
      , Skipper const& skipper
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, & attr))
    {
        Iterator first = first_;
        return qi::phrase_parse(first, last, expr, skipper, skip_flag::postskip
          , BOOST_PP_ENUM_PARAMS(N, attr));
    }
}}}

#undef BOOST_SPIRIT_QI_ATTRIBUTE_REFERENCE
#undef N

#endif


/* parse_attr.hpp
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
*/