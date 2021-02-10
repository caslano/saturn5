/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_BACK_10022005_1647)
#define FUSION_PUSH_BACK_10022005_1647

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct push_back_impl;

    template <>
    struct push_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename T>
        struct apply
        {
            typedef typename
                fusion::result_of::push_back<Sequence, T>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* push_back.hpp
PuMR5pmU5f74zPT2GjTxk+oJsNRNrh6b/uVmTfVAjcL7Xh5EEYUeo9So6ZGOGmhaC83UB6bUqDlVoLjkRtzg0dpNv9cZXAB30Bj307wGYn5qJio1aqoHZ78bgct5CErntxK4Mmcuuu9uPry76V1eaGk4BZtAHIEgvVWUeOYwxdEWquZP8YMjgHJqJxbgIIENLyZRcR8BeSNVszOAQ8GwYOWgaTyXYbHJ2Bm5X4bk29jBmAEUhGi3TtOZVhAMAwlxEtsgZtM0VmyL/Jo39/65B4J93nDE45/+1NxDcZ+BuZ4lNGY3GPwIMp9aur3FP6nlKdryYNuT8FXYrygCAdpBgqZYhFFCWgh7PotHbYcnmdI23Z0FbZ/ncZzt9+9lMDvuM/lJiG9qr/apf55ratQbRrT9vjFnS6SRF2CoZC1x0EUf6Y3wepEBKmd/Sw6aTV7sAixQenrGUymGoaXwvDQAGWE8MVHfrrPbfk9OXWLZIGhf9T60MbhiV08W7G9Yv+33XDDA1QL/u8tAgJOF3vuOAHxmEfZGXA76H0QSrmS+DqeS/FQTFjGA2Jkt1kFQpDF4tL4Y2nHhdZ132n9LvSOwgkYfmw5EYNGXoHgcfTjE58HlexiGR/k8CkY3nU53NBL75+I+jefwKug9Z2Fu
*/