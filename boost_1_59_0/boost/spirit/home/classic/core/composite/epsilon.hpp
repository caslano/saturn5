/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2002-2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_EPSILON_HPP
#define BOOST_SPIRIT_EPSILON_HPP

////////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/meta/parser_traits.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/core/composite/no_actions.hpp>

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4800) // forcing value to bool 'true' or 'false'
#endif

////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  condition_parser class
//
//      handles expressions of the form
//
//          epsilon_p(cond)
//
//      where cond is a function or a functor that returns a value suitable
//      to be used in boolean context. The expression returns a parser that
//      returns an empty match when the condition evaluates to true.
//
///////////////////////////////////////////////////////////////////////////////
    template <typename CondT, bool positive_ = true>
    struct condition_parser : parser<condition_parser<CondT, positive_> >
    {
        typedef condition_parser<CondT, positive_> self_t;

        // not explicit! (needed for implementation of if_p et al.)
        condition_parser(CondT const& cond_) : cond(cond_) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            if (positive_ == bool(cond())) // allow cond to return int
                return scan.empty_match();
            else
                return scan.no_match();
        }

        condition_parser<CondT, !positive_>
        negate() const
        { return condition_parser<CondT, !positive_>(cond); }

    private:

        CondT cond;
    };

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) || \
    BOOST_WORKAROUND(BOOST_MSVC, == 1400) || \
    BOOST_WORKAROUND(__SUNPRO_CC, <= 0x580)
// VC 7.1, VC8 and Sun CC <= 5.8 do not support general
// expressions of non-type template parameters in instantiations
    template <typename CondT>
    inline condition_parser<CondT, false>
    operator~(condition_parser<CondT, true> const& p)
    { return p.negate(); }

    template <typename CondT>
    inline condition_parser<CondT, true>
    operator~(condition_parser<CondT, false> const& p)
    { return p.negate(); }
#else // BOOST_WORKAROUND(BOOST_MSVC, == 1310) || == 1400
    template <typename CondT, bool positive>
    inline condition_parser<CondT, !positive>
    operator~(condition_parser<CondT, positive> const& p)
    { return p.negate(); }
#endif // BOOST_WORKAROUND(BOOST_MSVC, == 1310) || == 1400

///////////////////////////////////////////////////////////////////////////////
//
//  empty_match_parser class
//
//      handles expressions of the form
//          epsilon_p(subject)
//      where subject is a parser. The expression returns a composite
//      parser that returns an empty match if the subject parser matches.
//
///////////////////////////////////////////////////////////////////////////////
    struct empty_match_parser_gen;
    struct negated_empty_match_parser_gen;

    template <typename SubjectT>
    struct negated_empty_match_parser; // Forward declaration

    template<typename SubjectT>
    struct empty_match_parser
    : unary<SubjectT, parser<empty_match_parser<SubjectT> > >
    {
        typedef empty_match_parser<SubjectT>        self_t;
        typedef unary<SubjectT, parser<self_t> >    base_t;
        typedef unary_parser_category               parser_category_t;
        typedef empty_match_parser_gen              parser_genererator_t;
        typedef self_t embed_t;

        explicit empty_match_parser(SubjectT const& p) : base_t(p) {}

        template <typename ScannerT>
        struct result
        { typedef typename match_result<ScannerT, nil_t>::type type; };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typename ScannerT::iterator_t save(scan.first);
            
            typedef typename no_actions_scanner<ScannerT>::policies_t
                policies_t;

            bool matches = this->subject().parse(
                scan.change_policies(policies_t(scan)));
            if (matches)
            {
                scan.first = save; // reset the position
                return scan.empty_match();
            }
            else
            {
                return scan.no_match();
            }
        }

        negated_empty_match_parser<SubjectT>
        negate() const
        { return negated_empty_match_parser<SubjectT>(this->subject()); }
    };

    template<typename SubjectT>
    struct negated_empty_match_parser
    : public unary<SubjectT, parser<negated_empty_match_parser<SubjectT> > >
    {
        typedef negated_empty_match_parser<SubjectT>    self_t;
        typedef unary<SubjectT, parser<self_t> >        base_t;
        typedef unary_parser_category                   parser_category_t;
        typedef negated_empty_match_parser_gen          parser_genererator_t;

        explicit negated_empty_match_parser(SubjectT const& p) : base_t(p) {}

        template <typename ScannerT>
        struct result
        { typedef typename match_result<ScannerT, nil_t>::type type; };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typename ScannerT::iterator_t save(scan.first);

            typedef typename no_actions_scanner<ScannerT>::policies_t
                policies_t;

            bool matches = this->subject().parse(
                scan.change_policies(policies_t(scan)));
            if (!matches)
            {
                scan.first = save; // reset the position
                return scan.empty_match();
            }
            else
            {
                return scan.no_match();
            }
        }

        empty_match_parser<SubjectT>
        negate() const
        { return empty_match_parser<SubjectT>(this->subject()); }
    };

    struct empty_match_parser_gen
    {
        template <typename SubjectT>
        struct result
        { typedef empty_match_parser<SubjectT> type; };

        template <typename SubjectT>
        static empty_match_parser<SubjectT>
        generate(parser<SubjectT> const& subject)
        { return empty_match_parser<SubjectT>(subject.derived()); }
    };

    struct negated_empty_match_parser_gen
    {
        template <typename SubjectT>
        struct result
        { typedef negated_empty_match_parser<SubjectT> type; };

        template <typename SubjectT>
        static negated_empty_match_parser<SubjectT>
        generate(parser<SubjectT> const& subject)
        { return negated_empty_match_parser<SubjectT>(subject.derived()); }
    };

    //////////////////////////////
    template <typename SubjectT>
    inline negated_empty_match_parser<SubjectT>
    operator~(empty_match_parser<SubjectT> const& p)
    { return p.negate(); }

    template <typename SubjectT>
    inline empty_match_parser<SubjectT>
    operator~(negated_empty_match_parser<SubjectT> const& p)
    { return p.negate(); }

///////////////////////////////////////////////////////////////////////////////
//
//  epsilon_ parser and parser generator class
//
//      Operates as primitive parser that always matches an empty sequence.
//
//      Also operates as a parser generator. According to the type of the
//      argument an instance of empty_match_parser<> (when the argument is
//      a parser) or condition_parser<> (when the argument is not a parser)
//      is returned by operator().
//
///////////////////////////////////////////////////////////////////////////////
    namespace impl
    {
        template <typename SubjectT>
        struct epsilon_selector
        {
            typedef typename as_parser<SubjectT>::type subject_t;
            typedef typename
                mpl::if_<
                    is_parser<subject_t>
                    ,empty_match_parser<subject_t>
                    ,condition_parser<subject_t>
                >::type type;
        };
    }

    struct epsilon_parser : public parser<epsilon_parser>
    {
        typedef epsilon_parser self_t;

        epsilon_parser() {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        { return scan.empty_match(); }

        template <typename SubjectT>
        typename impl::epsilon_selector<SubjectT>::type
        operator()(SubjectT const& subject) const
        {
            typedef typename impl::epsilon_selector<SubjectT>::type result_t;
            return result_t(subject);
        }
    };

    epsilon_parser const epsilon_p = epsilon_parser();
    epsilon_parser const eps_p = epsilon_parser();

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#ifdef BOOST_MSVC
# pragma warning (pop)
#endif

#endif

/* epsilon.hpp
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
*/