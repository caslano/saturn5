/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_WHILE_HPP
#define BOOST_SPIRIT_WHILE_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/dynamic/impl/conditions.ipp>

////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    namespace impl {

    //////////////////////////////////
    // while parser
    // object are created by while_parser_gen and do_parser_gen
    template <typename ParsableT, typename CondT, bool is_do_parser>
    struct while_parser
        : public condition_evaluator< typename as_parser<CondT>::type >
        , public unary // the parent stores a copy of the body parser
        <
            typename as_parser<ParsableT>::type,
            parser<while_parser<ParsableT, CondT, is_do_parser> >
        >
    {
        typedef while_parser<ParsableT, CondT, is_do_parser> self_t;

        typedef as_parser<ParsableT>            as_parser_t;
        typedef typename as_parser_t::type      parser_t;
        typedef as_parser<CondT>                cond_as_parser_t;
        typedef typename cond_as_parser_t::type condition_t;

        typedef unary<parser_t, parser<self_t> > base_t;
        typedef condition_evaluator<condition_t> eval_t;


        //////////////////////////////
        // constructor, saves condition and body parser
        while_parser(ParsableT const &body, CondT const &cond)
            : eval_t(cond_as_parser_t::convert(cond))
            , base_t(as_parser_t::convert(body))
        {}

        //////////////////////////////
        // result type computer.
        template <typename ScannerT>
        struct result
        {
            typedef typename match_result
                <ScannerT, nil_t>::type type;
        };

        //////////////////////////////
        // parse member function
        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<parser_t, ScannerT>::type sresult_t;
            typedef typename ScannerT::iterator_t                    iterator_t;

            iterator_t save(scan.first);
            std::size_t length = 0;
            std::ptrdiff_t eval_length = 0;

            bool dont_check_condition = is_do_parser;

            while (dont_check_condition || (eval_length=this->evaluate(scan))>=0)
            {
                dont_check_condition = false;
                length += eval_length;
                sresult_t tmp(this->subject().parse(scan));
                if (tmp)
                {
                    length+=tmp.length();
                }
                else
                {
                    return scan.no_match();
                }
            }
            return scan.create_match(length, nil_t(), save, scan.first);
        }
    };

    //////////////////////////////////
    // while-parser generator, takes the body-parser in brackets
    // and returns the actual while-parser.
    template <typename CondT>
    struct while_parser_gen
    {
        //////////////////////////////
        // constructor, saves the condition for use by operator[]
        while_parser_gen(CondT const& cond_) : cond(cond_) {}

        //////////////////////////////
        // operator[] returns the actual while-parser object
        template <typename ParsableT>
        while_parser<ParsableT, CondT, false>
        operator[](ParsableT const &subject) const
        {
            return while_parser<ParsableT, CondT, false>(subject, cond);
        }
    private:

        //////////////////////////////
        // the condition is stored by reference here.
        // this should not cause any harm since object of type
        // while_parser_gen<> are only used as temporaries
        // the while-parser object constructed by the operator[]
        // stores a copy of the condition.
        CondT const &cond;
    };

    //////////////////////////////////
    // do-while-parser generator, takes the condition as
    // parameter to while_p member function and returns the
    // actual do-while-parser.
    template <typename ParsableT>
    struct do_while_parser_gen
    {
        //////////////////////////////
        // constructor. saves the body parser for use by while_p.
        explicit do_while_parser_gen(ParsableT const &body_parser)
            : body(body_parser)
        {}

        //////////////////////////////
        // while_p returns the actual while-parser object
        template <typename CondT>
        while_parser<ParsableT, CondT, true>
        while_p(CondT cond) const
        {
            return while_parser<ParsableT, CondT, true>(body, cond);
        }
    private:

        //////////////////////////////
        // the body is stored by reference here
        // this should not cause any harm since object of type
        // do_while_parser_gen<> are only used as temporaries
        // the while-parser object constructed by the while_p
        // member function stores a copy of the body parser.
        ParsableT const &body;
    };

    struct do_parser_gen
    {
        inline do_parser_gen() {}

        template <typename ParsableT>
        impl::do_while_parser_gen<ParsableT>
        operator[](ParsableT const& body) const
        {
            return impl::do_while_parser_gen<ParsableT>(body);
        }
    };
} // namespace impl

//////////////////////////////////
// while_p function, while-parser generator
// Usage: spirit::while_p(Condition)[Body]
template <typename CondT>
impl::while_parser_gen<CondT>
while_p(CondT const& cond)
{
    return impl::while_parser_gen<CondT>(cond);
}

//////////////////////////////////
// do_p functor, do-while-parser generator
// Usage: spirit::do_p[Body].while_p(Condition)
impl::do_parser_gen const do_p = impl::do_parser_gen();

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_WHILE_HPP

/* while.hpp
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
*/