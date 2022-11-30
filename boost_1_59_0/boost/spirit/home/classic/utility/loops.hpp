/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    Copyright (c) 2002 Raghavendra Satish
    Copyright (c) 2002 Jeff Westfahl
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_LOOPS_HPP)
#define BOOST_SPIRIT_LOOPS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/parser.hpp>
#include <boost/spirit/home/classic/core/composite/composite.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  fixed_loop class
    //
    //      This class takes care of the construct:
    //
    //          repeat_p (exact) [p]
    //
    //      where 'p' is a parser and 'exact' is the number of times to
    //      repeat. The parser iterates over the input exactly 'exact' times.
    //      The parse function fails if the parser does not match the input
    //      exactly 'exact' times.
    //
    //      This class is parametizable and can accept constant arguments
    //      (e.g. repeat_p (5) [p]) as well as references to variables (e.g.
    //      repeat_p (ref (n)) [p]).
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename ParserT, typename ExactT>
    class fixed_loop
    : public unary<ParserT, parser <fixed_loop <ParserT, ExactT> > >
    {
    public:

        typedef fixed_loop<ParserT, ExactT>     self_t;
        typedef unary<ParserT, parser<self_t> >  base_t;

        fixed_loop (ParserT const & subject_, ExactT const & exact)
        : base_t(subject_), m_exact(exact) {}

        template <typename ScannerT>
        typename parser_result <self_t, ScannerT>::type
        parse (ScannerT const & scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            result_t hit = scan.empty_match();
            std::size_t n = m_exact;

            for (std::size_t i = 0; i < n; ++i)
            {
                if (result_t next = this->subject().parse(scan))
                {
                    scan.concat_match(hit, next);
                }
                else
                {
                    return scan.no_match();
                }
            }

            return hit;
        }

        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, nil_t>::type type;
        };

    private:

        ExactT m_exact;
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    //  finite_loop class
    //
    //      This class takes care of the construct:
    //
    //          repeat_p (min, max) [p]
    //
    //      where 'p' is a parser, 'min' and 'max' specifies the minimum and
    //      maximum iterations over 'p'. The parser iterates over the input
    //      at least 'min' times and at most 'max' times. The parse function
    //      fails if the parser does not match the input at least 'min' times
    //      and at most 'max' times.
    //
    //      This class is parametizable and can accept constant arguments
    //      (e.g. repeat_p (5, 10) [p]) as well as references to variables
    //      (e.g. repeat_p (ref (n1), ref (n2)) [p]).
    //
    ///////////////////////////////////////////////////////////////////////////////
    template <typename ParserT, typename MinT, typename MaxT>
    class finite_loop
    : public unary<ParserT, parser<finite_loop<ParserT, MinT, MaxT> > >
    {
    public:

        typedef finite_loop <ParserT, MinT, MaxT> self_t;
        typedef unary<ParserT, parser<self_t> >   base_t;

        finite_loop (ParserT const & subject_, MinT const & min, MaxT const & max)
        : base_t(subject_), m_min(min), m_max(max) {}

        template <typename ScannerT>
        typename parser_result <self_t, ScannerT>::type
        parse(ScannerT const & scan) const
        {
            BOOST_SPIRIT_ASSERT(m_min <= m_max);
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            result_t hit = scan.empty_match();

            std::size_t n1 = m_min;
            std::size_t n2 = m_max;

            for (std::size_t i = 0; i < n2; ++i)
            {
                typename ScannerT::iterator_t save = scan.first;
                result_t next = this->subject().parse(scan);
 
                if (!next)
                {
                    if (i >= n1)
                    {
                        scan.first = save;
                        break;
                    }
                    else
                    {
                        return scan.no_match();
                    }
                }

                scan.concat_match(hit, next);
            }

            return hit;
        }

        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, nil_t>::type type;
        };

    private:

        MinT    m_min;
        MaxT    m_max;
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    //  infinite_loop class
    //
    //      This class takes care of the construct:
    //
    //          repeat_p (min, more) [p]
    //
    //      where 'p' is a parser, 'min' is the minimum iteration over 'p'
    //      and more specifies that the iteration should proceed
    //      indefinitely. The parser iterates over the input at least 'min'
    //      times and continues indefinitely until 'p' fails or all of the
    //      input is parsed. The parse function fails if the parser does not
    //      match the input at least 'min' times.
    //
    //      This class is parametizable and can accept constant arguments
    //      (e.g. repeat_p (5, more) [p]) as well as references to variables
    //      (e.g. repeat_p (ref (n), more) [p]).
    //
    ///////////////////////////////////////////////////////////////////////////////

    struct more_t {};
    more_t const more = more_t ();

    template <typename ParserT, typename MinT>
    class infinite_loop
     : public unary<ParserT, parser<infinite_loop<ParserT, MinT> > >
    {
    public:

        typedef infinite_loop <ParserT, MinT>   self_t;
        typedef unary<ParserT, parser<self_t> > base_t;

        infinite_loop (
            ParserT const& subject_,
            MinT const& min,
            more_t const&
        )
        : base_t(subject_), m_min(min) {}

        template <typename ScannerT>
        typename parser_result <self_t, ScannerT>::type
        parse(ScannerT const & scan) const
        {
            typedef typename parser_result<self_t, ScannerT>::type result_t;
            result_t hit = scan.empty_match();
            std::size_t n = m_min;

            for (std::size_t i = 0; ; ++i)
            {
                typename ScannerT::iterator_t save = scan.first;
                result_t next = this->subject().parse(scan);

                if (!next)
                {
                    if (i >= n)
                    {
                        scan.first = save;
                        break;
                    }
                    else
                    {
                        return scan.no_match();
                    }
                }

                scan.concat_match(hit, next);
            }

            return hit;
        }

        template <typename ScannerT>
        struct result
        {
            typedef typename match_result<ScannerT, nil_t>::type type;
        };

        private:

        MinT m_min;
    };

    template <typename ExactT>
    struct fixed_loop_gen
    {
        fixed_loop_gen (ExactT const & exact)
        : m_exact (exact) {}

        template <typename ParserT>
        fixed_loop <ParserT, ExactT>
        operator[](parser <ParserT> const & subject_) const
        {
            return fixed_loop <ParserT, ExactT> (subject_.derived (), m_exact);
        }

        ExactT m_exact;
    };

    namespace impl {

        template <typename ParserT, typename MinT, typename MaxT>
        struct loop_traits
        {
            typedef typename mpl::if_<
                boost::is_same<MaxT, more_t>,
                infinite_loop<ParserT, MinT>,
                finite_loop<ParserT, MinT, MaxT>
            >::type type;
        };

    } // namespace impl

    template <typename MinT, typename MaxT>
    struct nonfixed_loop_gen
    {
       nonfixed_loop_gen (MinT min, MaxT max)
        : m_min (min), m_max (max) {}

       template <typename ParserT>
       typename impl::loop_traits<ParserT, MinT, MaxT>::type
       operator[](parser <ParserT> const & subject_) const
       {
           typedef typename impl::loop_traits<ParserT, MinT, MaxT>::type ret_t;
           return ret_t(
                subject_.derived(),
                m_min,
                m_max);
       }

       MinT m_min;
       MaxT m_max;
    };

    template <typename ExactT>
    fixed_loop_gen <ExactT>
    repeat_p(ExactT const & exact)
    {
        return fixed_loop_gen <ExactT> (exact);
    }

    template <typename MinT, typename MaxT>
    nonfixed_loop_gen <MinT, MaxT>
    repeat_p(MinT const & min, MaxT const & max)
    {
        return nonfixed_loop_gen <MinT, MaxT> (min, max);
    }

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // #if !defined(BOOST_SPIRIT_LOOPS_HPP)

/* loops.hpp
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
*/