/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002 Juan Carlos Arevalo-Baeza
    Copyright (c) 2002-2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_IF_HPP
#define BOOST_SPIRIT_IF_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/dynamic/impl/conditions.ipp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    namespace impl {

    //////////////////////////////////
    // if-else-parser, holds two alternative parsers and a conditional functor
    // that selects between them.
    template <typename ParsableTrueT, typename ParsableFalseT, typename CondT>
    struct if_else_parser
        : public condition_evaluator<typename as_parser<CondT>::type>
        , public binary
        <
            typename as_parser<ParsableTrueT>::type,
            typename as_parser<ParsableFalseT>::type,
            parser< if_else_parser<ParsableTrueT, ParsableFalseT, CondT> >
        >
    {
        typedef if_else_parser<ParsableTrueT, ParsableFalseT, CondT>  self_t;

        typedef as_parser<ParsableTrueT>            as_parser_true_t;
        typedef as_parser<ParsableFalseT>           as_parser_false_t;
        typedef typename as_parser_true_t::type     parser_true_t;
        typedef typename as_parser_false_t::type    parser_false_t;
        typedef as_parser<CondT>                    cond_as_parser_t;
        typedef typename cond_as_parser_t::type     condition_t;

        typedef binary<parser_true_t, parser_false_t, parser<self_t> > base_t;
        typedef condition_evaluator<condition_t>                       eval_t;

        if_else_parser
        (
            ParsableTrueT  const& p_true,
            ParsableFalseT const& p_false,
            CondT          const& cond_
        )
            : eval_t(cond_as_parser_t::convert(cond_))
            , base_t
                (
                    as_parser_true_t::convert(p_true),
                    as_parser_false_t::convert(p_false)
                )
        { }

        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, nil_t>::type type;
        };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result
                <parser_true_t, ScannerT>::type   then_result_t;
            typedef typename parser_result
                <parser_false_t, ScannerT>::type  else_result_t;

            typename ScannerT::iterator_t const  save(scan.first);

            std::ptrdiff_t length = this->evaluate(scan);
            if (length >= 0)
            {
                then_result_t then_result(this->left().parse(scan));
                if (then_result)
                {
                    length += then_result.length();
                    return scan.create_match(std::size_t(length), nil_t(), save, scan.first);
                }
            }
            else
            {
                else_result_t else_result(this->right().parse(scan));
                if (else_result)
                {
                    length = else_result.length();
                    return scan.create_match(std::size_t(length), nil_t(), save, scan.first);
                }
            }
            return scan.no_match();
        }
    };

    //////////////////////////////////
    // if-else-parser generator, takes the false-parser in brackets
    // and returns the if-else-parser.
    template <typename ParsableTrueT, typename CondT>
    struct if_else_parser_gen
    {
        if_else_parser_gen(ParsableTrueT const& p_true_, CondT const& cond_)
            : p_true(p_true_)
            , cond(cond_) {}

        template <typename ParsableFalseT>
        if_else_parser
        <
            ParsableTrueT,
            ParsableFalseT,
            CondT
        >
        operator[](ParsableFalseT const& p_false) const
        {
            return if_else_parser<ParsableTrueT, ParsableFalseT, CondT>
                (
                    p_true,
                    p_false,
                    cond
                );
        }

        ParsableTrueT const &p_true;
        CondT const &cond;
    };

    //////////////////////////////////
    // if-parser, conditionally runs a parser is a functor condition is true.
    // If the condition is false, it fails the parse.
    // It can optionally become an if-else-parser through the member else_p.
    template <typename ParsableT, typename CondT>
    struct if_parser
        : public condition_evaluator<typename as_parser<CondT>::type>
        , public unary
        <
            typename as_parser<ParsableT>::type,
            parser<if_parser<ParsableT, CondT> > >
    {
        typedef if_parser<ParsableT, CondT>           self_t;
        typedef as_parser<ParsableT>                  as_parser_t;
        typedef typename as_parser_t::type            parser_t;

        typedef as_parser<CondT>                      cond_as_parser_t;
        typedef typename cond_as_parser_t::type       condition_t;
        typedef condition_evaluator<condition_t>      eval_t;
        typedef unary<parser_t, parser<self_t> >      base_t;

        if_parser(ParsableT const& p, CondT const& cond_)
            : eval_t(cond_as_parser_t::convert(cond_))
            , base_t(as_parser_t::convert(p))
            , else_p(p, cond_)
        {}

        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, nil_t>::type type;
        };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<parser_t, ScannerT>::type t_result_t;
            typename ScannerT::iterator_t const save(scan.first);

            std::ptrdiff_t length = this->evaluate(scan);
            if (length >= 0)
            {
                t_result_t then_result(this->subject().parse(scan));
                if (then_result)
                {
                    length += then_result.length();
                    return scan.create_match(std::size_t(length), nil_t(), save, scan.first);
                }
                return scan.no_match();
            }
            return scan.empty_match();
        }

        if_else_parser_gen<ParsableT, CondT> else_p;
    };

    //////////////////////////////////
    // if-parser generator, takes the true-parser in brackets and returns the
    // if-parser.
    template <typename CondT>
    struct if_parser_gen
    {
        if_parser_gen(CondT const& cond_) : cond(cond_) {}

        template <typename ParsableT>
        if_parser
        <
            ParsableT,
            CondT
        >
        operator[](ParsableT const& subject) const
        {
            return if_parser<ParsableT, CondT>(subject, cond);
        }

        CondT const &cond;
    };

} // namespace impl

//////////////////////////////////
// if_p function, returns "if" parser generator

template <typename CondT>
impl::if_parser_gen<CondT>
if_p(CondT const& cond)
{
    return impl::if_parser_gen<CondT>(cond);
}

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_IF_HPP

/* if.hpp
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
*/