//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#if !defined(BOOST_SPIRIT_KARMA_GENERATE_ATTR_APR_23_2009_0541PM)
#define BOOST_SPIRIT_KARMA_GENERATE_ATTR_APR_23_2009_0541PM

#include <boost/spirit/home/karma/generate.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 <boost/spirit/home/karma/generate_attr.hpp>
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
#define BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE(z, n, A)                       \
    BOOST_PP_CAT(A, n) const&

namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Properties, typename Expr
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    generate(
        detail::output_iterator<OutputIterator, Properties>& sink
      , Expr const& expr
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);

        typedef fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE, A)
        > vector_type;

        vector_type attr (BOOST_PP_ENUM_PARAMS(N, attr));
        return compile<karma::domain>(expr).generate(sink, unused, unused, attr);
    }

    template <typename OutputIterator, typename Expr
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    generate(
        OutputIterator& sink_
      , Expr const& expr
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        typedef traits::properties_of<
            typename result_of::compile<karma::domain, Expr>::type
        > properties;

        // wrap user supplied iterator into our own output iterator
        detail::output_iterator<OutputIterator
          , mpl::int_<properties::value> > sink(sink_);
        return karma::generate(sink, expr, BOOST_PP_ENUM_PARAMS(N, attr));
    }

    template <typename OutputIterator, typename Expr
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    generate(
        OutputIterator const& sink_
      , Expr const& expr
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        OutputIterator sink = sink_;
        return karma::generate(sink, expr, BOOST_PP_ENUM_PARAMS(N, attr));
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Properties, typename Expr
      , typename Delimiter, BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    generate_delimited(
        detail::output_iterator<OutputIterator, Properties>& sink
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then either the expression (expr) or skipper is not a valid
        // spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Delimiter);

        typename result_of::compile<karma::domain, Delimiter>::type const 
            delimiter_ = compile<karma::domain>(delimiter);

        if (pre_delimit == delimit_flag::predelimit &&
            !karma::delimit_out(sink, delimiter_))
        {
            return false;
        }

        typedef fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE, A)
        > vector_type;

        vector_type attr (BOOST_PP_ENUM_PARAMS(N, attr));
        return compile<karma::domain>(expr).
            generate(sink, unused, delimiter_, attr);
    }

    template <typename OutputIterator, typename Expr, typename Delimiter
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    generate_delimited(
        OutputIterator& sink_
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        typedef traits::properties_of<
            typename result_of::compile<karma::domain, Expr>::type
        > properties;
        typedef traits::properties_of<
            typename result_of::compile<karma::domain, Delimiter>::type
        > delimiter_properties;

        // wrap user supplied iterator into our own output iterator
        detail::output_iterator<OutputIterator
          , mpl::int_<properties::value | delimiter_properties::value>
        > sink(sink_);
        return karma::generate_delimited(sink, expr, delimiter, pre_delimit
          , BOOST_PP_ENUM_PARAMS(N, attr));
    }

    template <typename OutputIterator, typename Expr, typename Delimiter
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    generate_delimited(
        OutputIterator const& sink_
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        OutputIterator sink = sink_;
        return karma::generate_delimited(sink, expr, delimiter, pre_delimit
          , BOOST_PP_ENUM_PARAMS(N, attr));
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename OutputIterator, typename Expr, typename Delimiter
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    generate_delimited(
        OutputIterator& sink_
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        typedef traits::properties_of<
            typename result_of::compile<karma::domain, Expr>::type
        > properties;
        typedef traits::properties_of<
            typename result_of::compile<karma::domain, Delimiter>::type
        > delimiter_properties;

        // wrap user supplied iterator into our own output iterator
        detail::output_iterator<OutputIterator
          , mpl::int_<properties::value | delimiter_properties::value>
        > sink(sink_);
        return karma::generate_delimited(sink, expr, delimiter
          , delimit_flag::dont_predelimit, BOOST_PP_ENUM_PARAMS(N, attr));
    }

    template <typename OutputIterator, typename Expr, typename Delimiter
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline bool
    generate_delimited(
        OutputIterator const& sink_
      , Expr const& expr
      , Delimiter const& delimiter
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        OutputIterator sink = sink_;
        return karma::generate_delimited(sink, expr, delimiter 
          , delimit_flag::dont_predelimit, BOOST_PP_ENUM_PARAMS(N, attr));
    }

}}}

#undef BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE
#undef N

#endif // defined(BOOST_PP_IS_ITERATING)


/* generate_attr.hpp
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
*/