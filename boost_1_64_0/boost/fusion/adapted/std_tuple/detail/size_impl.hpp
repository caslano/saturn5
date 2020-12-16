/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_09242011_1744)
#define BOOST_FUSION_SIZE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <tuple>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template <>
        struct size_impl<std_tuple_tag>
        {
            template <typename Sequence>
            struct apply :
                mpl::int_<std::tuple_size<
                    typename remove_const<Sequence>::type>::value
                >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
zFsxp3eVfX4m5sUu4sym4xSf87tGexJrDNq97cSbCDPvbQsvsF0nbae9wPOWSTt4Aflck7IhTzA/NcXJEzjb1vJ2w53ls05rlQl37vFpVufBlh2vEntDwPT49HTLaLDlHiN2hsfwGNgbmQVXTjE70zL/fUzsLMfi9+7ZlgXv3Tc5Pf3efbPlwXv3LdCl22P7t4qOcDjdbxO9O+NGRJinZIauBPtIlcbLFZcOjJXGKuaXsfmdys+909mcltl8vguaXMzPtu9mHVdNsfYe1tBN4e5KT4tjdvtDfTvpPuz9lWmOrgP7RI1NeWCssnjIn+/7oNK5MmKfqNLpJAX+scD3U4LpMd85rGF8traTNYstUzx2+4hmU61Je5bDR1kPdrZznj8mjB4xP4jbdMM6+MeFy6OVplv38QnNW912zc5Hik4zHObn5vQM/PgpYTbLJg/+WQCfFhu7L4zeOeey7n6LfEb+pk/fdF/vofx78DwwuJvnHKHlCf+db1ngv8+Jrv1H7AJhs8PwPq+YDu9CpYflcZFj6fK42PF0eVxieVAeXxBdygPPXGqZ+Jr0y6BLteT2dDnrcdnJGbU8d1jYlUqDqTPArwDDXQMWU7xXWlbPvGeugp46G/xqsDCeL1m9FcfzZTA7XrN3U1xjdFrtgHZ4Lf7WZyRfB02fmX49NPkcwLZfgY5PARTHV1mjOw9oD6j7G7Eg7q87nWLivZ9OQ4hI9w3Q5x7KYd7o/vbDvMnpFCbPuzlNpx57PR3z4/s26+Y+BuzxtH8Hefiu0yUPN1styMMtrLv7HL7n/vbDvNXpkofbnBbn4XbHEB/07xf6kqFiz2t7aoK2fZP+A6vTjhV6Z5D+Q63z7j+K+0daxy44m9YfO9ZxZyreYTX+6MYRIE13BsxEQs/8xNc5EsTx04KNmn2N1alapZ+1n2ltPubEtFabamRNqvrE7tKs2H6ftYnR3JhmXQ7/bq1hj/o90JbP78c5ZZgP0zrORllX6ZpYmN8bcodxLq3m6o7KX2tdfXP+jdXxzqffXMPM7vPZfGb8bvotGL7XNIvzJSaHcUk9wr6fbbBokYcDjazNc2JpVpmPuB8A199EJsF+z4yybS5Pqevxw4MFWzFckrNMcb6t0hsd1h4Wza1N+YPV6NdDo14ZMit1FpZGbZ7+GPJqXrPskZB1p1p2nPcnx6Ss/2w1ymUc16OaB3H9RbMgrscckznbx50mZf+E0cYWlysLSuogOPjxSZ+5365PFXq50j8wsGy0f2ClO0f26UDXc4nP+Iw/yzRq7VbO/Nkkn5pqgP81wfPMzPfWc57r8rmcRxvoeRDvP5Jc4v1nyCVeagP/Ik5dki06/H6i/Uc898U27nT6Tl61p9fznkvhNDWChdrEnkuxnNkGW/hM/67ZUBjPqtfMb6lqzX3zfJ7POVj89n1+yKZaxbrLYhFKMd4pZtIbxpjyv5FviyNKTHOl80g4LS/QNtyWi6meRg17RzbWXNo6PqlyejcRGzWbz3uaNg1YlufueDdzCEujiXRsFti12vWMxmDgm/uc09iQdQhb+BxLMPjZF2rmVljI2vQtkxzZQPxbJW1kXfmLNEc90neUvZj5kvLCytCSkVFTHalpEts6YjI3u03MTDWltaPEX5Lm0/kkh71txOW85e0iJs3D3Z0Y2+Q6/u2TXOLfgbk5R1HCtn3Yy5ipY5z5mR1Fl+Ml0U/u5JicQfNy0Ywh+Y5sd3a6zN3sItokmlZxJByFs6vH5EzL3SLdrmBgvnuSmyzjd+Ie4OnjnDmMVzib9Lnie4acltpz/veKWE5h7i066kSlMa1+s+/jcRzohzzt6zF0CabRunk84fqnLfl9P8dk7ms=
*/