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
DCrkxXWJhJWZDzsZJPwlK2pep0EcUz/yRvcMguUm06UxImnkTNVlHqg6dNLATcT8eHNn6xyWA9O4RNKQLOSh5LFISBqmHahXfJvGTb00pCzqsuCpn4az0PbSuNpLoxIqjeK0pGng6Yy0KvoBH824+ykJwyoUImDtGZTOwCh7u1T2wlIlsih55xMfc8RxRWPVHH4RtSGLC5VkOrZW3/Si5dvG2LwuX8UqyetaAMK1yuzHS1hweRSTsQyCOBOMWmvS9UEBD9mDiDKtCyjf5vqKZkLtIuTaz2/V5a1ZlamwyqRkxLrD7NfwjEnyixgPITuZ58wzCaHz+CWaVxxJHe0mQjYn0Nj9cU9J8goYSEwZRlGJTKRF7Lx3mfClrE5iKKGQbLJ5hxeP71ovX5HlRRRFrd1gM0jgyR92uV3nrhO+GGS8qAN9/vXVM57/z9kXUx/3aZKnmUgZaH/MTRAw9uJNHHkxlc0sqJVK85Aygb6o5bMxIglfwPJaFCoOctZ034XxEtXJIF/a44vqVES8yBo+cDFygfYHQ/+pLl/VhEpVUaqLaW+dvNghlEeGdZQWEbK48RADjB1CyhezMi+yQIYZ868avPZ/k8urWKkKmaZViraBpsepnonyCJ6lSvGYUQ0rjQFwxeVZkCqIK5XWDUv1ZCnRlhDPN4AnMU2KCv5fJGyv69NePOF/9vgznuYqLyM28VrV5z/yEnoulDDhhnFYsT2uWz29WI8/lUqHQ849fsye8p8BflL/qq6KCAb1RFMNv/y7Pf4s5oFK0pjy713/N/XKX4e5lDLMkf9/1P9yjz9ScVKrtKL8fv0xFi3hFyyORCh1PNtJ18k9neI/Ca9ktcyUCKKK7W2u4cVKO/JSJ40oYKGI45qXOfsfJh/9OZm56YT6XQevyiQO2Z4m873Yb4RfMR6UZVbkyd78pBh2f07SqViSiVIUJBnPyq4fb/amXhpRVWR5koj/lojR9zIc1ySNlKVxUYsoyNjkpyreXPdPwi8Yz2qRxUXJJj3D6cWAPPKyXt6qjmWg2GTrA7onXSC8Fcv0TjDJE5/ZkyqG8QvdNKKIJXlWBYJPSoNKlROH7bWkHIopkQRJVIZ+GqQrPfm+iabT6CXjMIj+ezrHfT0USSdnRSKTKMwKPx3Soydxnu73CUzzAYw0NvnJlBdT58jLXZ/eYVULKYUZ6U5ggSHuT118xTiM6qCqC+a+7jA8Zx7V9T3wkFhzURyGsm7mQryhxn2m9U+vXD7F6gqGvoorfB4AS+u57V26tq5SHhHUQRrLWPN0F92YE67/pHyxto8qo8CMy8ZkF40Kvfg5b3J5F0odoEaaLYobp2wFY9CSvCSLqoyHSlVs76dOXp5X3DSk3hfVPAl0CmQjVYedjJE8odOETApRhA6Hn2tv3pl6BZ2HIy54nKQkjUlTqL6bv+Nx2Du+RN/NA9gNFGb8nd8J6F98OdJJsDD0GaZ1YgOMFQZADBZG3hv+2rv3tPaxI9c+duXC8u6UY4u7Re2jhIiDMOI3bItw5y4G04d1feAeGCIcgG805r6R+pUuY3tFbv0LD8x3FDV483re0l87gb7h3N3PTRu6uXpG2xz87pnLIWY008cMN/qYdB9iqJmcgzm6n2IwGddHHWLowEI7BI05gBjQDU9ZH+cH4Xtn54t5gJWMa++6Re/S9Q1uHpc3/I7StXP75YAcjKxd1MCjQXGce6Pn03kvq/IqilQzWbZrkwpOBeXp7u78gd0c4fIdK5KiTKM6Yt38yDvc+wlOKpnyuIDrzj5u9rMDB5eHYZ5rLdqoj/vNZ1xclgVRIWTKnt/H3eTme6LOVJ6LuLlcbJEd7jLBKV6pOOH6AtHg0B8=
*/