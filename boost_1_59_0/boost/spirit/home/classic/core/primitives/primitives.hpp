/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2003 Martin Wille
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_PRIMITIVES_HPP)
#define BOOST_SPIRIT_PRIMITIVES_HPP

#include <boost/ref.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/assert.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/impl/directives.ipp>
#include <boost/spirit/home/classic/core/primitives/impl/primitives.ipp>

#ifdef BOOST_MSVC
#pragma warning (push)
#pragma warning(disable : 4512)
#endif

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  char_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename DerivedT>
    struct char_parser : public parser<DerivedT>
    {
        typedef DerivedT self_t;
        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<
                ScannerT,
                typename ScannerT::value_t
            >::type type;
        };

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename ScannerT::value_t value_t;
            typedef typename ScannerT::iterator_t iterator_t;
            typedef scanner_policies<
                no_skipper_iteration_policy<
                BOOST_DEDUCED_TYPENAME ScannerT::iteration_policy_t>,
                BOOST_DEDUCED_TYPENAME ScannerT::match_policy_t,
                BOOST_DEDUCED_TYPENAME ScannerT::action_policy_t
            > policies_t;

            if (!scan.at_end())
            {
                value_t ch = *scan;
                if (this->derived().test(ch))
                {
                    iterator_t save(scan.first);
                    ++scan.change_policies(policies_t(scan));
                    return scan.create_match(1, ch, save, scan.first);
                }
            }
            return scan.no_match();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  negation of char_parsers
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename PositiveT>
    struct negated_char_parser
    : public char_parser<negated_char_parser<PositiveT> >
    {
        typedef negated_char_parser<PositiveT> self_t;
        typedef PositiveT positive_t;

        negated_char_parser(positive_t const& p)
        : positive(p.derived()) {}

        template <typename T>
        bool test(T ch) const
        {
            return !positive.test(ch);
        }

        positive_t const positive;
    };

    template <typename ParserT>
    inline negated_char_parser<ParserT>
    operator~(char_parser<ParserT> const& p)
    {
        return negated_char_parser<ParserT>(p.derived());
    }

    template <typename ParserT>
    inline ParserT
    operator~(negated_char_parser<ParserT> const& n)
    {
        return n.positive;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  chlit class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT = char>
    struct chlit : public char_parser<chlit<CharT> >
    {
        chlit(CharT ch_)
        : ch(ch_) {}

        template <typename T>
        bool test(T ch_) const
        {
            return ch_ == ch;
        }

        CharT   ch;
    };

    template <typename CharT>
    inline chlit<CharT>
    ch_p(CharT ch)
    {
        return chlit<CharT>(ch);
    }

    // This should take care of ch_p("a") "bugs"
    template <typename CharT, std::size_t N>
    inline chlit<CharT>
    ch_p(CharT const (& str)[N])
    {
        //  ch_p's argument should be a single character or a null-terminated
        //  string with a single character
        BOOST_STATIC_ASSERT(N < 3);
        return chlit<CharT>(str[0]);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  range class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT = char>
    struct range : public char_parser<range<CharT> >
    {
        range(CharT first_, CharT last_)
        : first(first_), last(last_)
        {
            BOOST_SPIRIT_ASSERT(!(last < first));
        }

        template <typename T>
        bool test(T ch) const
        {
            return !(CharT(ch) < first) && !(last < CharT(ch));
        }

        CharT   first;
        CharT   last;
    };

    template <typename CharT>
    inline range<CharT>
    range_p(CharT first, CharT last)
    {
        return range<CharT>(first, last);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  chseq class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename IteratorT = char const*>
    class chseq : public parser<chseq<IteratorT> >
    {
    public:

        typedef chseq<IteratorT> self_t;

        chseq(IteratorT first_, IteratorT last_)
        : first(first_), last(last_) {}

        chseq(IteratorT first_)
        : first(first_), last(impl::get_last(first_)) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename boost::unwrap_reference<IteratorT>::type striter_t;
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            return impl::string_parser_parse<result_t>(
                striter_t(first),
                striter_t(last),
                scan);
        }

    private:

        IteratorT first;
        IteratorT last;
    };

    template <typename CharT>
    inline chseq<CharT const*>
    chseq_p(CharT const* str)
    {
        return chseq<CharT const*>(str);
    }

    template <typename IteratorT>
    inline chseq<IteratorT>
    chseq_p(IteratorT first, IteratorT last)
    {
        return chseq<IteratorT>(first, last);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  strlit class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename IteratorT = char const*>
    class strlit : public parser<strlit<IteratorT> >
    {
    public:

        typedef strlit<IteratorT> self_t;

        strlit(IteratorT first, IteratorT last)
        : seq(first, last) {}

        strlit(IteratorT first)
        : seq(first) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            return impl::contiguous_parser_parse<result_t>
                (seq, scan, scan);
        }

    private:

        chseq<IteratorT> seq;
    };

    template <typename CharT>
    inline strlit<CharT const*>
    str_p(CharT const* str)
    {
        return strlit<CharT const*>(str);
    }

    template <typename CharT>
    inline strlit<CharT *>
    str_p(CharT * str)
    {
        return strlit<CharT *>(str);
    }

    template <typename IteratorT>
    inline strlit<IteratorT>
    str_p(IteratorT first, IteratorT last)
    {
        return strlit<IteratorT>(first, last);
    }

    // This should take care of str_p('a') "bugs"
    template <typename CharT>
    inline chlit<CharT>
    str_p(CharT ch)
    {
        return chlit<CharT>(ch);
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  nothing_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct nothing_parser : public parser<nothing_parser>
    {
        typedef nothing_parser self_t;

        nothing_parser() {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            return scan.no_match();
        }
    };

    nothing_parser const nothing_p = nothing_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  anychar_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct anychar_parser : public char_parser<anychar_parser>
    {
        typedef anychar_parser self_t;

        anychar_parser() {}

        template <typename CharT>
        bool test(CharT) const
        {
            return true;
        }
    };

    anychar_parser const anychar_p = anychar_parser();

    inline nothing_parser
    operator~(anychar_parser)
    {
        return nothing_p;
    }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  alnum_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct alnum_parser : public char_parser<alnum_parser>
    {
        typedef alnum_parser self_t;

        alnum_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isalnum_(ch);
        }
    };

    alnum_parser const alnum_p = alnum_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  alpha_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct alpha_parser : public char_parser<alpha_parser>
    {
        typedef alpha_parser self_t;

        alpha_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isalpha_(ch);
        }
    };

    alpha_parser const alpha_p = alpha_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  cntrl_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct cntrl_parser : public char_parser<cntrl_parser>
    {
        typedef cntrl_parser self_t;

        cntrl_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::iscntrl_(ch);
        }
    };

    cntrl_parser const cntrl_p = cntrl_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  digit_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct digit_parser : public char_parser<digit_parser>
    {
        typedef digit_parser self_t;

        digit_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isdigit_(ch);
        }
    };

    digit_parser const digit_p = digit_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  graph_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct graph_parser : public char_parser<graph_parser>
    {
        typedef graph_parser self_t;

        graph_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isgraph_(ch);
        }
    };

    graph_parser const graph_p = graph_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  lower_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct lower_parser : public char_parser<lower_parser>
    {
        typedef lower_parser self_t;

        lower_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::islower_(ch);
        }
    };

    lower_parser const lower_p = lower_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  print_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct print_parser : public char_parser<print_parser>
    {
        typedef print_parser self_t;

        print_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isprint_(ch);
        }
    };

    print_parser const print_p = print_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  punct_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct punct_parser : public char_parser<punct_parser>
    {
        typedef punct_parser self_t;

        punct_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::ispunct_(ch);
        }
    };

    punct_parser const punct_p = punct_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  blank_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct blank_parser : public char_parser<blank_parser>
    {
        typedef blank_parser self_t;

        blank_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isblank_(ch);
        }
    };

    blank_parser const blank_p = blank_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  space_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct space_parser : public char_parser<space_parser>
    {
        typedef space_parser self_t;

        space_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isspace_(ch);
        }
    };

    space_parser const space_p = space_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  upper_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct upper_parser : public char_parser<upper_parser>
    {
        typedef upper_parser self_t;

        upper_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isupper_(ch);
        }
    };

    upper_parser const upper_p = upper_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  xdigit_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct xdigit_parser : public char_parser<xdigit_parser>
    {
        typedef xdigit_parser self_t;

        xdigit_parser() {}

        template <typename CharT>
        bool test(CharT ch) const
        {
            return impl::isxdigit_(ch);
        }
    };

    xdigit_parser const xdigit_p = xdigit_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  eol_parser class (contributed by Martin Wille)
    //
    ///////////////////////////////////////////////////////////////////////////
    struct eol_parser : public parser<eol_parser>
    {
        typedef eol_parser self_t;

        eol_parser() {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef scanner_policies<
                no_skipper_iteration_policy<
                BOOST_DEDUCED_TYPENAME ScannerT::iteration_policy_t>,
                BOOST_DEDUCED_TYPENAME ScannerT::match_policy_t,
                BOOST_DEDUCED_TYPENAME ScannerT::action_policy_t
            > policies_t;

            typename ScannerT::iterator_t save = scan.first;
            std::size_t len = 0;

            if (!scan.at_end() && *scan == '\r')    // CR
            {
                ++scan.change_policies(policies_t(scan));
                ++len;
            }

            // Don't call skipper here
            if (scan.first != scan.last && *scan == '\n')    // LF
            {
                ++scan.change_policies(policies_t(scan));
                ++len;
            }

            if (len)
                return scan.create_match(len, nil_t(), save, scan.first);
            return scan.no_match();
        }
    };

    eol_parser const eol_p = eol_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  end_parser class (suggested by Markus Schoepflin)
    //
    ///////////////////////////////////////////////////////////////////////////
    struct end_parser : public parser<end_parser>
    {
        typedef end_parser self_t;

        end_parser() {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            if (scan.at_end())
                return scan.empty_match();
            return scan.no_match();
        }
    };

    end_parser const end_p = end_parser();

    ///////////////////////////////////////////////////////////////////////////
    //
    //  the pizza_p parser :-)
    //
    ///////////////////////////////////////////////////////////////////////////
    inline strlit<char const*> const
    pizza_p(char const* your_favorite_pizza)
    {
        return your_favorite_pizza;
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#ifdef BOOST_MSVC
#pragma warning (pop)
#endif

#endif

/* primitives.hpp
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
*/