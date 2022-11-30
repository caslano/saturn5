/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_FOR_HPP
#define BOOST_SPIRIT_FOR_HPP
////////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/dynamic/impl/conditions.ipp>

////////////////////////////////////////////////////////////////////////////////

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    namespace impl
    {

        template <typename FuncT>
        struct for_functor
        {
            typedef typename boost::call_traits<FuncT>::param_type  param_t;

            for_functor(param_t f) : func(f) {}
            for_functor() {}
            FuncT func;
        };

        template <typename InitF>
        struct for_init_functor : for_functor<InitF>
        {
            typedef for_functor<InitF>          base_t;
            typedef typename base_t::param_t    param_t;

            for_init_functor(param_t f) : base_t(f) {}
            for_init_functor() : base_t() {}
            void init() const { /*return*/ this->func(); }
        };

        template <typename StepF>
        struct for_step_functor : for_functor<StepF>
        {
            typedef for_functor<StepF>          base_t;
            typedef typename base_t::param_t    param_t;

            for_step_functor(param_t f) : base_t(f) {}
            for_step_functor() : base_t() {}
            void step() const { /*return*/ this->func(); }
        };

        //////////////////////////////////
        // for_parser
        template
        <
            typename InitF, typename CondT, typename StepF,
            typename ParsableT
        >
        struct for_parser
            : private for_init_functor<InitF>
            , private for_step_functor<StepF>
            , private condition_evaluator<typename as_parser<CondT>::type>
            , public unary
            <
                typename as_parser<ParsableT>::type,
                parser< for_parser<InitF, CondT, StepF, ParsableT> >
            >
        {
            typedef for_parser<InitF, CondT, StepF, ParsableT> self_t;
            typedef as_parser<CondT>                           cond_as_parser_t;
            typedef typename cond_as_parser_t::type            condition_t;
            typedef condition_evaluator<condition_t>           eval_t;
            typedef as_parser<ParsableT>                       as_parser_t;
            typedef typename as_parser_t::type                 parser_t;
            typedef unary< parser_t, parser< self_t > >        base_t;


            //////////////////////////////
            // constructor, saves init, condition and step functors
            // for later use the parse member function
            for_parser
            (
                InitF const &i, CondT const &c, StepF const &s,
                ParsableT const &p
            )
                : for_init_functor<InitF>(i)
                , for_step_functor<StepF>(s)
                , eval_t(cond_as_parser_t::convert(c))
                , base_t(as_parser_t::convert(p))
            { }

            for_parser()
                : for_init_functor<InitF>()
                , for_step_functor<StepF>()
                , eval_t()
                , base_t()
            {}

            //////////////////////////////
            // parse member function
            template <typename ScannerT>
            typename parser_result<self_t, ScannerT>::type
            parse(ScannerT const &scan) const
            {
                typedef typename parser_result<parser_t, ScannerT>::type
                    body_result_t;

                typename ScannerT::iterator_t save(scan.first);

                std::size_t length = 0;
                std::ptrdiff_t eval_length = 0;

                this->init();
                while ((eval_length = this->evaluate(scan))>=0)
                {
                    length += eval_length;
                    body_result_t tmp(this->subject().parse(scan));
                    if (tmp)
                    {
                        length+=tmp.length();
                    }
                    else
                    {
                        return scan.no_match();
                    }
                    this->step();
                }

                BOOST_SPIRIT_CLASSIC_NS::nil_t attr;
                return scan.create_match
                    (length, attr, save, scan.first);
            }
        };

        //////////////////////////////////
        // for_parser_gen generates takes the body parser in brackets
        // and returns the for_parser
        template <typename InitF, typename CondT, typename StepF>
        struct for_parser_gen
        {
            for_parser_gen(InitF const &i, CondT const &c, StepF const &s)
                : init(i)
                , condition(c)
                , step(s)
            {}

            template <typename ParsableT>
            for_parser<InitF, CondT, StepF, ParsableT>
            operator[](ParsableT const &p) const
            {
                return for_parser<InitF, CondT, StepF, ParsableT>
                    (init, condition, step, p);
            }

            InitF const &init;
            CondT const &condition;
            StepF const &step;
        };
    } // namespace impl

    //////////////////////////////
    // for_p, returns for-parser generator
    // Usage: spirit::for_p(init-ftor, condition, step-ftor)[body]
    template
    <
        typename InitF, typename ConditionT, typename StepF
    >
    impl::for_parser_gen<InitF, ConditionT, StepF>
    for_p(InitF const &init_f, ConditionT const &condition, StepF const &step_f)
    {
        return impl::for_parser_gen<InitF, ConditionT, StepF>
            (init_f, condition, step_f);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_FOR_HPP

/* for.hpp
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
*/