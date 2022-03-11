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