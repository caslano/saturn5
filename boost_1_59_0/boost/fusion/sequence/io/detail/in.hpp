/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IN_05052005_0121)
#define FUSION_IN_05052005_0121

#include <boost/fusion/support/config.hpp>
#include <istream>
#include <boost/fusion/sequence/io/detail/manip.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Tag>
    struct delimiter_in
    {
        // read a delimiter
        template <typename IS>
        static void
        read(IS& is, char const* delim, mpl::false_ = mpl::false_())
        {
            detail::string_ios_manip<Tag, IS> manip(is);
            manip.read(delim);
        }

        template <typename IS>
        static void
        read(IS&, char const*, mpl::true_)
        {
        }
    };

    struct read_sequence_loop
    {
        template <typename IS, typename First, typename Last>
        static void
        call(IS&, First const&, Last const&, mpl::true_)
        {
        }

        template <typename IS, typename First, typename Last>
        static void
        call(IS& is, First const& first, Last const& last, mpl::false_)
        {
            result_of::equal_to<
                typename result_of::next<First>::type
              , Last
            >
            is_last;

            is >> *first;
            delimiter_in<tuple_delimiter_tag>::read(is, " ", is_last);
            call(is, fusion::next(first), last, is_last);
        }

        template <typename IS, typename First, typename Last>
        static void
        call(IS& is, First const& first, Last const& last)
        {
            result_of::equal_to<First, Last> eq;
            call(is, first, last, eq);
        }
    };

    template <typename IS, typename Sequence>
    inline void
    read_sequence(IS& is, Sequence& seq)
    {
        delimiter_in<tuple_open_tag>::read(is, "(");
        read_sequence_loop::call(is, fusion::begin(seq), fusion::end(seq));
        delimiter_in<tuple_close_tag>::read(is, ")");
    }
}}}

#endif

/* in.hpp
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
*/