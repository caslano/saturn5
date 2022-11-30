/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_DIRECTIVES_HPP)
#define BOOST_SPIRIT_DIRECTIVES_HPP

///////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/scanner/skipper.hpp> 
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/core/composite/impl/directives.ipp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  contiguous class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct lexeme_parser_gen;

    template <typename ParserT>
    struct contiguous
    :   public unary<ParserT, parser<contiguous<ParserT> > >
    {
        typedef contiguous<ParserT>             self_t;
        typedef unary_parser_category           parser_category_t;
        typedef lexeme_parser_gen               parser_generator_t;
        typedef unary<ParserT, parser<self_t> > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };

        contiguous(ParserT const& p)
        : base_t(p) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            return impl::contiguous_parser_parse<result_t>
                (this->subject(), scan, scan);
        }
    };

    struct lexeme_parser_gen
    {
        template <typename ParserT>
        struct result {

            typedef contiguous<ParserT> type;
        };

        template <typename ParserT>
        static contiguous<ParserT>
        generate(parser<ParserT> const& subject)
        {
            return contiguous<ParserT>(subject.derived());
        }

        template <typename ParserT>
        contiguous<ParserT>
        operator[](parser<ParserT> const& subject) const
        {
            return contiguous<ParserT>(subject.derived());
        }
    };

    //////////////////////////////////
    const lexeme_parser_gen lexeme_d = lexeme_parser_gen();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  lexeme_scanner
    //
    //      Given a Scanner, return the correct scanner type that
    //      the lexeme_d uses. Scanner is assumed to be a phrase
    //      level scanner (see skipper.hpp)
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ScannerT>
    struct lexeme_scanner
    {
        typedef scanner_policies<
            no_skipper_iteration_policy<
                typename ScannerT::iteration_policy_t>,
            typename ScannerT::match_policy_t,
            typename ScannerT::action_policy_t
        > policies_t;

        typedef typename
            rebind_scanner_policies<ScannerT, policies_t>::type type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  inhibit_case_iteration_policy class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename BaseT>
    struct inhibit_case_iteration_policy : public BaseT
    {
        typedef BaseT base_t;

        inhibit_case_iteration_policy()
        : BaseT() {}

        template <typename PolicyT>
        inhibit_case_iteration_policy(PolicyT const& other)
        : BaseT(other) {}

        template <typename CharT>
        CharT filter(CharT ch) const
        { return impl::tolower_(ch); }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  inhibit_case class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct inhibit_case_parser_gen;

    template <typename ParserT>
    struct inhibit_case
    :   public unary<ParserT, parser<inhibit_case<ParserT> > >
    {
        typedef inhibit_case<ParserT>           self_t;
        typedef unary_parser_category           parser_category_t;
        typedef inhibit_case_parser_gen         parser_generator_t;
        typedef unary<ParserT, parser<self_t> > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };

        inhibit_case(ParserT const& p)
        : base_t(p) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            return impl::inhibit_case_parser_parse<result_t>
                (this->subject(), scan, scan);
        }
    };

    template <int N>
    struct inhibit_case_parser_gen_base
    {
        //  This hack is needed to make borland happy.
        //  If these member operators were defined in the
        //  inhibit_case_parser_gen class, or if this class
        //  is non-templated, borland ICEs.

        static inhibit_case<strlit<char const*> >
        generate(char const* str)
        { return inhibit_case<strlit<char const*> >(str); }

        static inhibit_case<strlit<wchar_t const*> >
        generate(wchar_t const* str)
        { return inhibit_case<strlit<wchar_t const*> >(str); }

        static inhibit_case<chlit<char> >
        generate(char ch)
        { return inhibit_case<chlit<char> >(ch); }

        static inhibit_case<chlit<wchar_t> >
        generate(wchar_t ch)
        { return inhibit_case<chlit<wchar_t> >(ch); }

        template <typename ParserT>
        static inhibit_case<ParserT>
        generate(parser<ParserT> const& subject)
        { return inhibit_case<ParserT>(subject.derived()); }

        inhibit_case<strlit<char const*> >
        operator[](char const* str) const
        { return inhibit_case<strlit<char const*> >(str); }

        inhibit_case<strlit<wchar_t const*> >
        operator[](wchar_t const* str) const
        { return inhibit_case<strlit<wchar_t const*> >(str); }

        inhibit_case<chlit<char> >
        operator[](char ch) const
        { return inhibit_case<chlit<char> >(ch); }

        inhibit_case<chlit<wchar_t> >
        operator[](wchar_t ch) const
        { return inhibit_case<chlit<wchar_t> >(ch); }

        template <typename ParserT>
        inhibit_case<ParserT>
        operator[](parser<ParserT> const& subject) const
        { return inhibit_case<ParserT>(subject.derived()); }
    };

    //////////////////////////////////
    struct inhibit_case_parser_gen : public inhibit_case_parser_gen_base<0>
    {
        inhibit_case_parser_gen() {}
    };

    //////////////////////////////////
    //  Depracated
    const inhibit_case_parser_gen nocase_d = inhibit_case_parser_gen();

    //  Preferred syntax
    const inhibit_case_parser_gen as_lower_d = inhibit_case_parser_gen();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  as_lower_scanner
    //
    //      Given a Scanner, return the correct scanner type that
    //      the as_lower_d uses. Scanner is assumed to be a scanner
    //      with an inhibit_case_iteration_policy.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ScannerT>
    struct as_lower_scanner
    {
        typedef scanner_policies<
            inhibit_case_iteration_policy<
                typename ScannerT::iteration_policy_t>,
            typename ScannerT::match_policy_t,
            typename ScannerT::action_policy_t
        > policies_t;

        typedef typename
            rebind_scanner_policies<ScannerT, policies_t>::type type;
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  longest_alternative class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct longest_parser_gen;

    template <typename A, typename B>
    struct longest_alternative
    :   public binary<A, B, parser<longest_alternative<A, B> > >
    {
        typedef longest_alternative<A, B>       self_t;
        typedef binary_parser_category          parser_category_t;
        typedef longest_parser_gen              parser_generator_t;
        typedef binary<A, B, parser<self_t> >   base_t;

        longest_alternative(A const& a, B const& b)
        : base_t(a, b) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typename ScannerT::iterator_t save = scan.first;
            result_t l = this->left().parse(scan);
            std::swap(scan.first, save);
            result_t r = this->right().parse(scan);

            if (l || r)
            {
                if (l.length() > r.length())
                {
                    scan.first = save;
                    return l;
                }
                return r;
            }

            return scan.no_match();
        }
    };

    struct longest_parser_gen
    {
        template <typename A, typename B>
        struct result {

            typedef typename
                impl::to_longest_alternative<alternative<A, B> >::result_t
            type;
        };

        template <typename A, typename B>
        static typename
        impl::to_longest_alternative<alternative<A, B> >::result_t
        generate(alternative<A, B> const& alt)
        {
            return impl::to_longest_alternative<alternative<A, B> >::
                convert(alt);
        }

        //'generate' for binary composite
        template <typename A, typename B>
        static
        longest_alternative<A, B>
        generate(A const &left, B const &right)
        {
            return longest_alternative<A, B>(left, right);
        }

        template <typename A, typename B>
        typename impl::to_longest_alternative<alternative<A, B> >::result_t
        operator[](alternative<A, B> const& alt) const
        {
            return impl::to_longest_alternative<alternative<A, B> >::
                convert(alt);
        }
    };

    const longest_parser_gen longest_d = longest_parser_gen();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  shortest_alternative class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct shortest_parser_gen;

    template <typename A, typename B>
    struct shortest_alternative
    :   public binary<A, B, parser<shortest_alternative<A, B> > >
    {
        typedef shortest_alternative<A, B>      self_t;
        typedef binary_parser_category          parser_category_t;
        typedef shortest_parser_gen             parser_generator_t;
        typedef binary<A, B, parser<self_t> >   base_t;

        shortest_alternative(A const& a, B const& b)
        : base_t(a, b) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            typename ScannerT::iterator_t save = scan.first;
            result_t l = this->left().parse(scan);
            std::swap(scan.first, save);
            result_t r = this->right().parse(scan);

            if (l || r)
            {
                if ((l.length() < r.length() && l) || !r)
                {
                    scan.first = save;
                    return l;
                }
                return r;
            }

            return scan.no_match();
        }
    };

    struct shortest_parser_gen
    {
        template <typename A, typename B>
        struct result {

            typedef typename
                impl::to_shortest_alternative<alternative<A, B> >::result_t
            type;
        };

        template <typename A, typename B>
        static typename
        impl::to_shortest_alternative<alternative<A, B> >::result_t
        generate(alternative<A, B> const& alt)
        {
            return impl::to_shortest_alternative<alternative<A, B> >::
                convert(alt);
        }

        //'generate' for binary composite
        template <typename A, typename B>
        static
        shortest_alternative<A, B>
        generate(A const &left, B const &right)
        {
            return shortest_alternative<A, B>(left, right);
        }

        template <typename A, typename B>
        typename impl::to_shortest_alternative<alternative<A, B> >::result_t
        operator[](alternative<A, B> const& alt) const
        {
            return impl::to_shortest_alternative<alternative<A, B> >::
                convert(alt);
        }
    };

    const shortest_parser_gen shortest_d = shortest_parser_gen();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  min_bounded class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename BoundsT>
    struct min_bounded_gen;

    template <typename ParserT, typename BoundsT>
    struct min_bounded
    :   public unary<ParserT, parser<min_bounded<ParserT, BoundsT> > >
    {
        typedef min_bounded<ParserT, BoundsT>   self_t;
        typedef unary_parser_category           parser_category_t;
        typedef min_bounded_gen<BoundsT>        parser_generator_t;
        typedef unary<ParserT, parser<self_t> > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };

        min_bounded(ParserT const& p, BoundsT const& min__)
        : base_t(p)
        , min_(min__) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            result_t hit = this->subject().parse(scan);
            if (hit.has_valid_attribute() && hit.value() < min_)
                return scan.no_match();
            return hit;
        }

        BoundsT min_;
    };

    template <typename BoundsT>
    struct min_bounded_gen
    {
        min_bounded_gen(BoundsT const& min__)
        : min_(min__) {}

        template <typename DerivedT>
        min_bounded<DerivedT, BoundsT>
        operator[](parser<DerivedT> const& p) const
        { return min_bounded<DerivedT, BoundsT>(p.derived(), min_); }

        BoundsT min_;
    };

    template <typename BoundsT>
    inline min_bounded_gen<BoundsT>
    min_limit_d(BoundsT const& min_)
    { return min_bounded_gen<BoundsT>(min_); }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  max_bounded class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename BoundsT>
    struct max_bounded_gen;

    template <typename ParserT, typename BoundsT>
    struct max_bounded
    :   public unary<ParserT, parser<max_bounded<ParserT, BoundsT> > >
    {
        typedef max_bounded<ParserT, BoundsT>   self_t;
        typedef unary_parser_category           parser_category_t;
        typedef max_bounded_gen<BoundsT>        parser_generator_t;
        typedef unary<ParserT, parser<self_t> > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };

        max_bounded(ParserT const& p, BoundsT const& max__)
        : base_t(p)
        , max_(max__) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            result_t hit = this->subject().parse(scan);
            if (hit.has_valid_attribute() && hit.value() > max_)
                return scan.no_match();
            return hit;
        }

        BoundsT max_;
    };

    template <typename BoundsT>
    struct max_bounded_gen
    {
        max_bounded_gen(BoundsT const& max__)
        : max_(max__) {}

        template <typename DerivedT>
        max_bounded<DerivedT, BoundsT>
        operator[](parser<DerivedT> const& p) const
        { return max_bounded<DerivedT, BoundsT>(p.derived(), max_); }

        BoundsT max_;
    };

    //////////////////////////////////
    template <typename BoundsT>
    inline max_bounded_gen<BoundsT>
    max_limit_d(BoundsT const& max_)
    { return max_bounded_gen<BoundsT>(max_); }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  bounded class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename BoundsT>
    struct bounded_gen;

    template <typename ParserT, typename BoundsT>
    struct bounded
    :   public unary<ParserT, parser<bounded<ParserT, BoundsT> > >
    {
        typedef bounded<ParserT, BoundsT>       self_t;
        typedef unary_parser_category           parser_category_t;
        typedef bounded_gen<BoundsT>            parser_generator_t;
        typedef unary<ParserT, parser<self_t> > base_t;

        template <typename ScannerT>
        struct result
        {
            typedef typename parser_result<ParserT, ScannerT>::type type;
        };

        bounded(ParserT const& p, BoundsT const& min__, BoundsT const& max__)
        : base_t(p)
        , min_(min__)
        , max_(max__) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            result_t hit = this->subject().parse(scan);
            if (hit.has_valid_attribute() &&
                (hit.value() < min_ || hit.value() > max_))
                    return scan.no_match();
            return hit;
        }

        BoundsT min_, max_;
    };

    template <typename BoundsT>
    struct bounded_gen
    {
        bounded_gen(BoundsT const& min__, BoundsT const& max__)
        : min_(min__)
        , max_(max__) {}

        template <typename DerivedT>
        bounded<DerivedT, BoundsT>
        operator[](parser<DerivedT> const& p) const
        { return bounded<DerivedT, BoundsT>(p.derived(), min_, max_); }

        BoundsT min_, max_;
    };

    template <typename BoundsT>
    inline bounded_gen<BoundsT>
    limit_d(BoundsT const& min_, BoundsT const& max_)
    { return bounded_gen<BoundsT>(min_, max_); }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* directives.hpp
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
*/