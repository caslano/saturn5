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
wlHFhzKQCH2JTQTIQrG6bGOrdwKuUELewUdTwau/qVrilQrNhK6h5Fc3C2DuW5LYg9Fc2Ji74v3ZsTkVwA38lsD9jrlQBQ8G79zJYOo4VVv1oVC1q5oilFBLmZ5dDMbuZNobT6fj3nByOhirBVV3nrdbzxAaJ9REwWYyBIXqeShwgrnNZET8Uw7laHSuetnayUNOJ0gsOGwDDyyWh2OezAoTEUSVI/11df/aYT/Zgxdz0ydXikysfitTO+xos7taZlNMf8V2aUmjSkqsr2l2sfFtGqTNIodCN1LNtdmA+rK/0uBHVUiXJ0LaPKDNX9jEeDWjKhdU9eSrOqnbfqisI1vl1uuTwMrb0cm1NsNGm/hxSFu1Uf+fdHl/f2t3u5mr34P+D1BLAwQKAAAACAAtZ0pS/qbA768CAABZBgAAFgAJAGN1cmwtbWFzdGVyL2xpYi9maWxlLmhVVAUAAbZIJGCtVVFP2zAQfs+vuNEHoMoaxtNY0bSuhVENtagtQpWQIje5EG+OndkOLRr777tLAmwaU1/qqrXj3Hff5zvftSMznWIGF2eD0dksHl7PLuPz8eVZfBF0aF9qfO1V1N3dCKALW0dcf2MaNNeIK2u+YeJft47jR2g+hLqleRtJBC+Qx/gQtkMe4aCGxC3L
*/