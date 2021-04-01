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
mMU4knmL5gYKVrUJ4unaPHTtY8VlyG0Gy6zrTfQv30K+aVpv/t+RthW9yahqt07i8qw0QAgeNdVZNJskWh9h7mQ4QvjnWvEzimW/kUsRYc3heAdL4yIJ6Mt9LzZqEmY1C6dwHIvyoeNpT6Aa2fJgnWicdVK+ZWcvM+8ihDmfhddq0ZiHeUHsW+ViC1cFO+F6VLwOdN5CdftHM0UA4JcRPdeNFId4e8Qfjwy2G7BKeMW2KZL/2t+FicixJ1EUV4lg5oXTwD9fz+aKa/fEothgoV4wjkZl+3COrS3p5QDoPU/HWZKxIu4PLs9r8FExgtDy54bJG2HSeEdh4CkK7g9ImdTrKo9dno76MDTfuT4Pm3BKr8m37zPSwemCG3pJNkPJksZ4nSBkb2XDVS4yuLVNL+xU8nfWfwsh3BQVLbVBEb/RG+9vn6V74/vuoYpS2da+wm3ZAKIaUmdOgqdMhQZ8riEJpVpqlOJ6JGx4wd8z6gM2YSkg+j0dlSZq4wwOWxiK6Ymc2FG08Wx2Wongdy+IHkRfkJSbDIwfY1YTI/Kz6LKlbP5hoaTZ7yyNLQ==
*/