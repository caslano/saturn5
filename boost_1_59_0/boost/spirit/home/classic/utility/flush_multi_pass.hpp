/*=============================================================================
    Copyright (c) 2001-2003 Daniel Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_FLUSH_MULTI_PASS_HPP
#define BOOST_SPIRIT_FLUSH_MULTI_PASS_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core.hpp>
#include <boost/spirit/home/classic/iterator/multi_pass.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    namespace impl {

        template <typename T>
        void flush_iterator(T &) {}

        template <typename T1, typename T2, typename T3, typename T4>
        void flush_iterator(BOOST_SPIRIT_CLASSIC_NS::multi_pass<
            T1, T2, T3, T4, BOOST_SPIRIT_CLASSIC_NS::multi_pass_policies::std_deque> &i)
        {
            i.clear_queue();
        }

    }   // namespace impl

    ///////////////////////////////////////////////////////////////////////////
    //
    //  flush_multi_pass_parser
    //
    //      The flush_multi_pass_parser flushes an underlying
    //      multi_pass_iterator during the normal parsing process. This may
    //      be used at certain points during the parsing process, when it is
    //      clear, that no backtracking is needed anymore and the input
    //      gathered so far may be discarded.
    //
    ///////////////////////////////////////////////////////////////////////////
    class flush_multi_pass_parser
    :   public parser<flush_multi_pass_parser>
    {
    public:
        typedef flush_multi_pass_parser this_t;

        template <typename ScannerT>
        typename parser_result<this_t, ScannerT>::type
        parse(ScannerT const& scan) const
        {
            impl::flush_iterator(scan.first);
            return scan.empty_match();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  predefined flush_multi_pass_p object
    //
    //      This object should may used to flush a multi_pass_iterator along
    //      the way during the normal parsing process.
    //
    ///////////////////////////////////////////////////////////////////////////

    flush_multi_pass_parser const
        flush_multi_pass_p = flush_multi_pass_parser();

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // BOOST_SPIRIT_FLUSH_MULTI_PASS_HPP

/* flush_multi_pass.hpp
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
*/