/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_PARAMETRIC_HPP
#define BOOST_SPIRIT_PARAMETRIC_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/spirit/home/classic/core/primitives/primitives.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  f_chlit class [ functional version of chlit ]
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ChGenT>
    struct f_chlit : public char_parser<f_chlit<ChGenT> >
    {
        f_chlit(ChGenT chgen_)
        : chgen(chgen_) {}

        template <typename T>
        bool test(T ch) const
        { return ch == chgen(); }

        ChGenT   chgen;
    };

    template <typename ChGenT>
    inline f_chlit<ChGenT>
    f_ch_p(ChGenT chgen)
    { return f_chlit<ChGenT>(chgen); }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  f_range class [ functional version of range ]
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ChGenAT, typename ChGenBT>
    struct f_range : public char_parser<f_range<ChGenAT, ChGenBT> >
    {
        f_range(ChGenAT first_, ChGenBT last_)
        : first(first_), last(last_)
        {}

        template <typename T>
        bool test(T ch) const
        {
            BOOST_SPIRIT_ASSERT(first() <= last());
            return (ch >= first()) && (ch <= last());
        }

        ChGenAT first;
        ChGenBT last;
    };

    template <typename ChGenAT, typename ChGenBT>
    inline f_range<ChGenAT, ChGenBT>
    f_range_p(ChGenAT first, ChGenBT last)
    { return f_range<ChGenAT, ChGenBT>(first, last); }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  f_chseq class [ functional version of chseq ]
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename IterGenAT, typename IterGenBT>
    class f_chseq : public parser<f_chseq<IterGenAT, IterGenBT> >
    {
    public:

        typedef f_chseq<IterGenAT, IterGenBT> self_t;

        f_chseq(IterGenAT first_, IterGenBT last_)
        : first(first_), last(last_) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            return impl::string_parser_parse<result_t>(first(), last(), scan);
        }

    private:

        IterGenAT first;
        IterGenBT last;
    };

    template <typename IterGenAT, typename IterGenBT>
    inline f_chseq<IterGenAT, IterGenBT>
    f_chseq_p(IterGenAT first, IterGenBT last)
    { return f_chseq<IterGenAT, IterGenBT>(first, last); }

    ///////////////////////////////////////////////////////////////////////////
    //
    //  f_strlit class [ functional version of strlit ]
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename IterGenAT, typename IterGenBT>
    class f_strlit : public parser<f_strlit<IterGenAT, IterGenBT> >
    {
    public:

        typedef f_strlit<IterGenAT, IterGenBT> self_t;

        f_strlit(IterGenAT first, IterGenBT last)
        : seq(first, last) {}

        template <typename ScannerT>
        typename parser_result<self_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            return impl::contiguous_parser_parse<result_t>
                (seq, scan, scan);
        }

    private:

        f_chseq<IterGenAT, IterGenBT> seq;
    };

    template <typename IterGenAT, typename IterGenBT>
    inline f_strlit<IterGenAT, IterGenBT>
    f_str_p(IterGenAT first, IterGenBT last)
    { return f_strlit<IterGenAT, IterGenBT>(first, last); }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* parametric.hpp
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
*/