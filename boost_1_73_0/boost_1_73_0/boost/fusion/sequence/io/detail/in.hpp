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
PcQ/wb4Ge9PpbktwCio6XggR2iFCVRzPOWq0/P7qK6/3qstKSlal7gy6AjaMAKCPgQ2mvtelS57nsYM8hGxKWbJbLgdst6pU3xSL35xqZ2Gr9pkBiIG/lezQoyrfqX4sNc50o8OQ/+1icqQ2BDb1qJEv8XVASHsLs+tkClXNxfmp3iYGASsoX0C4OkydAv59NnHPJlBYN/QzRJRYlNhDbNPxhXkGeaoXlokPzxB+UYbF65zY6aSQDc09C4Mx6IoYKkuPSkxjHNIdHxtFqt+WFynmCZx4z0qohbriMJo7EdnZKCguvK8ubEE+dktzSrC2pGihLig3As3ZvdGKMlBpQ2vDBVm6KrXla9bhncUs3ximx5A/288Qlb0oTcH9tYBkw9Nffzz4aKFT2X9vjvPqB2pWmairbA1FaF8Zq6/OdmOr3heQdZOsdc6Tm2xxxJ7X1RVR1Yx26fPo9NSdsvqH9ENS32ZRUqhQHBWBzzwKQYirUKGGPudng+FUlU2/DHong3GTGa0PLJutImMLwiinVBQ3XyfzgeRKPw2V55x6j96qtSgi5ZEqUJRFrLpbym6+8qRNkO+ShooYp3q3lFdzQ08ahrppguUpotUVzNjLjlh9ugIeh39iQ3GHl9l/YIevjn7409GrP7OfL6a2
*/