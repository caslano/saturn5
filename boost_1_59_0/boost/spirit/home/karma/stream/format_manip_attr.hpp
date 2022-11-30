//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_PP_IS_ITERATING)

#if !defined(BOOST_SPIRIT_KARMA_FORMAT_MANIP_ATTR_APR_24_2009_0734AM)
#define BOOST_SPIRIT_KARMA_FORMAT_MANIP_ATTR_APR_24_2009_0734AM

#include <boost/spirit/home/karma/stream/format_manip.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1                                                   \
    <boost/spirit/home/karma/stream/format_manip_attr.hpp>
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

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma 
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline detail::format_manip<Expr, mpl::false_, mpl::true_, unused_type
      , fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE, A)
        > > 
    format(Expr const& xpr, BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        using karma::detail::format_manip;

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);

        typedef fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE, A)
        > vector_type;

        vector_type attr (BOOST_PP_ENUM_PARAMS(N, attr));
        return format_manip<Expr, mpl::false_, mpl::true_, unused_type, vector_type>(
            xpr, unused, attr);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Delimiter
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline detail::format_manip<Expr, mpl::false_, mpl::true_, Delimiter
      , fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE, A)
        > > 
    format_delimited(Expr const& xpr, Delimiter const& d
      , BOOST_SCOPED_ENUM(delimit_flag) pre_delimit
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        using karma::detail::format_manip;

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Delimiter);

        typedef fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE, A)
        > vector_type;

        vector_type attr (BOOST_PP_ENUM_PARAMS(N, attr));
        return format_manip<Expr, mpl::false_, mpl::true_, Delimiter, vector_type>(
            xpr, d, pre_delimit, attr);
    }

    template <typename Expr, typename Delimiter
      , BOOST_PP_ENUM_PARAMS(N, typename A)>
    inline detail::format_manip<Expr, mpl::false_, mpl::true_, Delimiter
      , fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE, A)
        > > 
    format_delimited(Expr const& xpr, Delimiter const& d
      , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& attr))
    {
        using karma::detail::format_manip;

        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here,
        // then the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Delimiter);

        typedef fusion::vector<
            BOOST_PP_ENUM(N, BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE, A)
        > vector_type;

        vector_type attr (BOOST_PP_ENUM_PARAMS(N, attr));
        return format_manip<Expr, mpl::false_, mpl::true_, Delimiter, vector_type>(
            xpr, d, delimit_flag::dont_predelimit, attr);
    }
}}}

#undef BOOST_SPIRIT_KARMA_ATTRIBUTE_REFERENCE
#undef N

#endif 


/* format_manip_attr.hpp
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
*/