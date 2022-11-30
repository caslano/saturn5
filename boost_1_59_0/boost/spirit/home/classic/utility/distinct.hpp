/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2003 Vaclav Vesely
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_DISTINCT_HPP)
#define BOOST_SPIRIT_DISTINCT_HPP

#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/operators.hpp>
#include <boost/spirit/home/classic/core/composite/directives.hpp>
#include <boost/spirit/home/classic/core/composite/epsilon.hpp>
#include <boost/spirit/home/classic/core/non_terminal/rule.hpp>
#include <boost/spirit/home/classic/utility/chset.hpp>

#include <boost/spirit/home/classic/utility/distinct_fwd.hpp>

namespace boost {
    namespace spirit {
    BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

//-----------------------------------------------------------------------------
// distinct_parser class

template <typename CharT, typename TailT>
class distinct_parser
{
public:
    typedef
        contiguous<
            sequence<
                chseq<CharT const*>,
                negated_empty_match_parser<
                    TailT
                >
            >
        >
            result_t;

    distinct_parser()
    :   tail(chset<CharT>())
    {
    }

    explicit distinct_parser(parser<TailT> const & tail_)
    :   tail(tail_.derived())
    {
    }

    explicit distinct_parser(CharT const* letters)
    :   tail(chset_p(letters))
    {
    }

    result_t operator()(CharT const* str) const
    {
        return lexeme_d[chseq_p(str) >> ~epsilon_p(tail)];
    }

    TailT tail;
};

//-----------------------------------------------------------------------------
// distinct_directive class

template <typename CharT, typename TailT>
class distinct_directive
{
public:
    template<typename ParserT>
    struct result {
        typedef
            contiguous<
                sequence<
                    ParserT,
                    negated_empty_match_parser<
                        TailT
                    >
                >
            >
                type;
    };

    distinct_directive()
    :   tail(chset<CharT>())
    {
    }

    explicit distinct_directive(CharT const* letters)
    :   tail(chset_p(letters))
    {
    }

    explicit distinct_directive(parser<TailT> const & tail_)
    :   tail(tail_.derived())
    {
    }

    template<typename ParserT>
    typename result<typename as_parser<ParserT>::type>::type
        operator[](ParserT const &subject) const
    {
        return
            lexeme_d[as_parser<ParserT>::convert(subject) >> ~epsilon_p(tail)];
    }

    TailT tail;
};

//-----------------------------------------------------------------------------
// dynamic_distinct_parser class

template <typename ScannerT>
class dynamic_distinct_parser
{
public:
    typedef typename ScannerT::value_t char_t;

    typedef
        rule<
            typename no_actions_scanner<
                typename lexeme_scanner<ScannerT>::type
            >::type
        >
            tail_t;

    typedef
        contiguous<
            sequence<
                chseq<char_t const*>,
                negated_empty_match_parser<
                    tail_t
                >
            >
        >
            result_t;

    dynamic_distinct_parser()
    :   tail(nothing_p)
    {
    }

    template<typename ParserT>
    explicit dynamic_distinct_parser(parser<ParserT> const & tail_)
    :   tail(tail_.derived())
    {
    }

    explicit dynamic_distinct_parser(char_t const* letters)
    :   tail(chset_p(letters))
    {
    }

    result_t operator()(char_t const* str) const
    {
        return lexeme_d[chseq_p(str) >> ~epsilon_p(tail)];
    }

    tail_t tail;
};

//-----------------------------------------------------------------------------
// dynamic_distinct_directive class

template <typename ScannerT>
class dynamic_distinct_directive
{
public:
    typedef typename ScannerT::value_t char_t;

    typedef
        rule<
            typename no_actions_scanner<
                typename lexeme_scanner<ScannerT>::type
            >::type
        >
            tail_t;

    template<typename ParserT>
    struct result {
        typedef
            contiguous<
                sequence<
                    ParserT,
                    negated_empty_match_parser<
                        tail_t
                    >
                >
            >
                type;
    };

    dynamic_distinct_directive()
    :   tail(nothing_p)
    {
    }

    template<typename ParserT>
    explicit dynamic_distinct_directive(parser<ParserT> const & tail_)
    :   tail(tail_.derived())
    {
    }

    explicit dynamic_distinct_directive(char_t const* letters)
    :   tail(chset_p(letters))
    {
    }

    template<typename ParserT>
    typename result<typename as_parser<ParserT>::type>::type
        operator[](ParserT const &subject) const
    {
        return
            lexeme_d[as_parser<ParserT>::convert(subject) >> ~epsilon_p(tail)];
    }

    tail_t tail;
};

//-----------------------------------------------------------------------------
    BOOST_SPIRIT_CLASSIC_NAMESPACE_END
    } // namespace spirit
} // namespace boost

#endif // !defined(BOOST_SPIRIT_DISTINCT_HPP)

/* distinct.hpp
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
*/