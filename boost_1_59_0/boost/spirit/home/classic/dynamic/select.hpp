/*=============================================================================
    Copyright (c) 2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_SELECT_HPP
#define BOOST_SPIRIT_SELECT_HPP

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/enum_params_with_defaults.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>

#include <boost/spirit/home/classic/phoenix/tuples.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit predefined maximum number of possible embedded select_p parsers.
//  It should NOT be greater than PHOENIX_LIMIT!
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SPIRIT_SELECT_LIMIT)
#define BOOST_SPIRIT_SELECT_LIMIT PHOENIX_LIMIT
#endif // !defined(BOOST_SPIRIT_SELECT_LIMIT)

///////////////////////////////////////////////////////////////////////////////
//
// ensure   BOOST_SPIRIT_SELECT_LIMIT <= PHOENIX_LIMIT and 
//          BOOST_SPIRIT_SELECT_LIMIT > 0
//          BOOST_SPIRIT_SELECT_LIMIT <= 15
//
//  [Pushed this down a little to make CW happy with BOOST_STATIC_ASSERT]
//  [Otherwise, it complains: 'boost_static_assert_test_42' redefined]
//
///////////////////////////////////////////////////////////////////////////////
BOOST_STATIC_ASSERT(BOOST_SPIRIT_SELECT_LIMIT <= PHOENIX_LIMIT);
BOOST_STATIC_ASSERT(BOOST_SPIRIT_SELECT_LIMIT > 0);
BOOST_STATIC_ASSERT(BOOST_SPIRIT_SELECT_LIMIT <= 15);

///////////////////////////////////////////////////////////////////////////////
//
//  Calculate the required amount of tuple members rounded up to the nearest 
//  integer dividable by 3
//
///////////////////////////////////////////////////////////////////////////////
#if BOOST_SPIRIT_SELECT_LIMIT > 12
#define BOOST_SPIRIT_SELECT_LIMIT_A     15
#elif BOOST_SPIRIT_SELECT_LIMIT > 9
#define BOOST_SPIRIT_SELECT_LIMIT_A     12
#elif BOOST_SPIRIT_SELECT_LIMIT > 6
#define BOOST_SPIRIT_SELECT_LIMIT_A     9
#elif BOOST_SPIRIT_SELECT_LIMIT > 3
#define BOOST_SPIRIT_SELECT_LIMIT_A     6
#else
#define BOOST_SPIRIT_SELECT_LIMIT_A     3
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  The select_default_no_fail and select_default_fail structs are used to 
//  distinguish two different behaviours for the select_parser in case that not
//  any of the given sub-parsers match.
//
//  If the select_parser is used with the select_default_no_fail behaviour,
//  then in case of no matching sub-parser the whole select_parser returns an
//  empty match and the value -1.
//
//  If the select_parser is used with the select_default_fail behaviour, then
//  in case of no matching sub-parser the whole select_parser fails to match at 
//  all.
//
///////////////////////////////////////////////////////////////////////////////
struct select_default_no_fail {};
struct select_default_fail {};

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}  // namespace BOOST_SPIRIT_CLASSIC_NS

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/dynamic/impl/select.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
template <typename TupleT, typename BehaviourT, typename T>
struct select_parser
:   public parser<select_parser<TupleT, BehaviourT, T> >
{
    typedef select_parser<TupleT, BehaviourT, T> self_t;

    select_parser(TupleT const &t_)
    :   t(t_)
    {}
    
    template <typename ScannerT>
    struct result
    {
        typedef typename match_result<ScannerT, T>::type type;
    };

    template <typename ScannerT>
    typename parser_result<self_t, ScannerT>::type
    parse(ScannerT const& scan) const
    {
        typedef typename parser_result<self_t, ScannerT>::type result_t;
        
        if (!scan.at_end()) {
            return impl::parse_tuple_element<
                TupleT::length, result_t, TupleT, BehaviourT>::do_(t, scan);
        }
        return impl::select_match_gen<result_t, BehaviourT>::do_(scan);
    }
        
    TupleT const t;
};

///////////////////////////////////////////////////////////////////////////////
template <typename BehaviourT, typename T = int>
struct select_parser_gen {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  This generates different select_parser_gen::operator()() functions with 
    //  an increasing number of parser parameters:
    //
    //      template <typename ParserT0, ...>
    //      select_parser<
    //          ::phoenix::tuple<
    //              typename impl::as_embedded_parser<ParserT0>::type,
    //              ...
    //          >,
    //          BehaviourT,
    //          T
    //      >
    //      operator()(ParserT0 const &p0, ...) const
    //      {
    //          typedef impl::as_embedded_parser<ParserT0> parser_t0;
    //          ...
    //
    //          typedef ::phoenix::tuple< 
    //                  parser_t0::type,
    //                  ...
    //              > tuple_t; 
    //          typedef select_parser<tuple_t, BehaviourT, T> result_t;
    //
    //          return result_t(tuple_t(
    //                  parser_t0::convert(p0),
    //                  ...
    //              ));
    //      }
    //
    //  The number of generated functions depends on the maximum tuple member 
    //  limit defined by the PHOENIX_LIMIT pp constant. 
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_SELECT_EMBEDDED(z, N, _)                           \
        typename impl::as_embedded_parser<BOOST_PP_CAT(ParserT, N)>::type   \
        /**/
    #define BOOST_SPIRIT_SELECT_EMBEDDED_TYPEDEF(z, N, _)                   \
        typedef impl::as_embedded_parser<BOOST_PP_CAT(ParserT, N)>          \
            BOOST_PP_CAT(parser_t, N);                                      \
        /**/
    #define BOOST_SPIRIT_SELECT_CONVERT(z, N, _)                            \
        BOOST_PP_CAT(parser_t, N)::convert(BOOST_PP_CAT(p, N))              \
        /**/
        
    #define BOOST_SPIRIT_SELECT_PARSER(z, N, _)                             \
        template <                                                          \
            BOOST_PP_ENUM_PARAMS_Z(z, BOOST_PP_INC(N), typename ParserT)    \
        >                                                                   \
        select_parser<                                                      \
            ::phoenix::tuple<                                                 \
                BOOST_PP_ENUM_ ## z(BOOST_PP_INC(N),                        \
                    BOOST_SPIRIT_SELECT_EMBEDDED, _)                        \
            >,                                                              \
            BehaviourT,                                                     \
            T                                                               \
        >                                                                   \
        operator()(                                                         \
            BOOST_PP_ENUM_BINARY_PARAMS_Z(z, BOOST_PP_INC(N),               \
                ParserT, const &p)                                          \
        ) const                                                             \
        {                                                                   \
            BOOST_PP_REPEAT_ ## z(BOOST_PP_INC(N),                          \
                BOOST_SPIRIT_SELECT_EMBEDDED_TYPEDEF, _)                    \
                                                                            \
            typedef ::phoenix::tuple<                                         \
                    BOOST_PP_ENUM_BINARY_PARAMS_Z(z, BOOST_PP_INC(N),       \
                        typename parser_t, ::type BOOST_PP_INTERCEPT)       \
                > tuple_t;                                                  \
            typedef select_parser<tuple_t, BehaviourT, T> result_t;         \
                                                                            \
            return result_t(tuple_t(                                        \
                    BOOST_PP_ENUM_ ## z(BOOST_PP_INC(N),                    \
                        BOOST_SPIRIT_SELECT_CONVERT, _)                     \
                ));                                                         \
        }                                                                   \
        /**/
        
    BOOST_PP_REPEAT(BOOST_SPIRIT_SELECT_LIMIT_A, 
        BOOST_SPIRIT_SELECT_PARSER, _)
        
    #undef BOOST_SPIRIT_SELECT_PARSER
    #undef BOOST_SPIRIT_SELECT_CONVERT
    #undef BOOST_SPIRIT_SELECT_EMBEDDED_TYPEDEF
    #undef BOOST_SPIRIT_SELECT_EMBEDDED
    ///////////////////////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////////////////////////
//
//  Predefined parser generator helper objects
//
///////////////////////////////////////////////////////////////////////////////
select_parser_gen<select_default_no_fail> const select_p = 
    select_parser_gen<select_default_no_fail>();

select_parser_gen<select_default_fail> const select_fail_p = 
    select_parser_gen<select_default_fail>();

#undef BOOST_SPIRIT_SELECT_LIMIT_A

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}}  // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_SELECT_HPP

/* select.hpp
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
*/