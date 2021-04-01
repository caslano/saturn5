/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEQUENCE_05052005_1002)
#define FUSION_IS_SEQUENCE_05052005_1002

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename T>
        struct is_sequence_impl
        {
            template <typename Sequence>
            struct apply
              : is_convertible<Sequence, fusion::detail::from_sequence_convertible_type>
            {};
        };

        template <>
        struct is_sequence_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_sequence_impl<boost_tuple_tag>;

        template <>
        struct is_sequence_impl<boost_array_tag>;

        template <>
        struct is_sequence_impl<mpl_sequence_tag>;

        template <>
        struct is_sequence_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_sequence
          : mpl::bool_<
                (bool)extension::is_sequence_impl<
                    typename fusion::detail::tag_of<T>::type
                >::template apply<T>::type::value
            >
        {};

        using detail::is_native_fusion_sequence;
    }
}}

#endif

/* is_sequence.hpp
aiZmF/l2oY8M19UYfoTXC/bmWs6fmFZL222aNYgVFp8fd1IVkjfozwF+OMsaeLPAxjEXz2jXZ7dFv17QZTp0Gy/fzSVZizYptAGQKEYqghI9ZRrHVlEil8wqnPBgXPI1Q+vNE4t4t2vG2u3+Wl2rbSbcC7f05r02hBoxCoxNijQn5XfwkSWF92ouBX/SvJiBSo4crRTFOJrzBuxDo1JV3VSmz6T7oCuPPrgs5clhs3S/vDmB+IIfla1/Up1zqQMEDJxLjv36hiohhBwfCq3885ObCcFrMCt9e7jTWoPELRXtoCg3YFgKRU7Q2ef0HiVDQ3IP7qr8MnSTzRTj6D3V4Oa10BOcTvUZws2xXwRNNDk4tfTyECJFYD1kPN3eRTLkNTDCQ+JNdAHlJOxUTrKII/5Xr+Gse3pLRHOrQ9KXjZrhF3YjC5qcFilCq70sowVh4zx5Is/HeqGSxU2cKAFsPXE8s9AKUWmN/0OQ64jFGXc/mQYK5TDRGkXc9JcCdf9B3QfIdZe6QvtoiD2+68exWhRbGGYl5T9M/Z6Skkb/YCXz/1t3U2R7QsP4Lw==
*/