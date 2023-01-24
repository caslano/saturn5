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
K5vHR76lU7YRpiY5Hd0nrb9KFWVKR79+vZiqaqCpgkoxHW2E2sphVPVt3Ucb8ZSlOiMh+8vv5hTrId8Wypt3mpx0qFY00ljPCLUJUdtUKxpM0ZWsJtu9ZFWZzUDavpSromMcLTur6ThH/c5uTZVGJpCqRnlRLZBU9VJPeqU8ONb3dJm7LtR4sa71usaLKXpjNF5MqkR2UnsxodNL48WGmMaaF5natK6gUDa1vRGkdJ9Xg3SKJcqsaPr716eXjFKbdAu9WJvLP+K1GUiW7JQJgTprbIGatT2NwceoRUe7Z0qz9H3tMCsSpl9nkTtbcm+qe0PWr9PIzeoxKVxxZ0hujawt8tnxM7t0aYg92XPvFenK0WD78SA//3/YKU3PLSGezPAqlsZ70kgalNzHKyTFc1WoZLn1yWAQahee+5FZb+1FPoPE6JYxv1YiczfL4L3ZM7yOe5RJnMbufG0TJJl4hXEFT8SXVrCF+bmHs/kcILm71Awypeu0x9a1WCRmjjawWNg3b9inp4MDhS+SCqQYZiblFtE3zGqJcbmuHHBd0dDukftLMZUrcxabZUbRYjbmdahQXhgqyFDqNC9DmTWU76Ese10mfzYLmDdVGdDCuykTWXs35flO3ZRRPaCbMiP0IzdrM3HvKOpSQoZakYlRL5mZ6F5rf3ab6xiV4HGcjbzhbGlLPlHoLDsSSqlFE1tsKtFdR2WIMFXRhT89
*/