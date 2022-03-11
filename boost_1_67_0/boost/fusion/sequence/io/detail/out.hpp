/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_OUT_05052005_0121)
#define FUSION_OUT_05052005_0121

#include <boost/fusion/support/config.hpp>
#include <ostream>
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
    struct delimiter_out
    {
        // print a delimiter
        template <typename OS>
        static void
        print(OS& os, char const* delim, mpl::false_ = mpl::false_())
        {
            detail::string_ios_manip<Tag, OS> manip(os);
            manip.print(delim);
        }

        template <typename OS>
        static void
        print(OS&, char const*, mpl::true_)
        {
        }
    };

    struct print_sequence_loop
    {
        template <typename OS, typename First, typename Last>
        static void
        call(OS&, First const&, Last const&, mpl::true_)
        {
        }

        template <typename OS, typename First, typename Last>
        static void
        call(OS& os, First const& first, Last const& last, mpl::false_)
        {
            result_of::equal_to<
                typename result_of::next<First>::type
              , Last
            >
            is_last;

            os << *first;
            delimiter_out<tuple_delimiter_tag>::print(os, " ", is_last);
            call(os, fusion::next(first), last, is_last);
        }

        template <typename OS, typename First, typename Last>
        static void
        call(OS& os, First const& first, Last const& last)
        {
            result_of::equal_to<First, Last> eq;
            call(os, first, last, eq);
        }
    };

    template <typename OS, typename Sequence>
    inline void
    print_sequence(OS& os, Sequence const& seq)
    {
        delimiter_out<tuple_open_tag>::print(os, "(");
        print_sequence_loop::call(os, fusion::begin(seq), fusion::end(seq));
        delimiter_out<tuple_close_tag>::print(os, ")");
    }
}}}

#endif

/* out.hpp
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
*/