/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_05052005_0214)
#define FUSION_SIZE_05052005_0214

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_size.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct size_impl
        {
            template<typename Sequence>
            struct unsegmented_size : Sequence::size {};

            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_size<Sequence>
                  , unsegmented_size<Sequence>
                >::type
            {};
        };

        template <>
        struct size_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template size<Sequence> {};
        };

        template <>
        struct size_impl<boost_tuple_tag>;

        template <>
        struct size_impl<boost_array_tag>;

        template <>
        struct size_impl<mpl_sequence_tag>;

        template <>
        struct size_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct size
            : mpl::int_<
                  extension::size_impl<typename detail::tag_of<Sequence>::type>
                      ::template apply<Sequence>::type::value
              > {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::size<Sequence>::type
    size(Sequence const&)
    {
        typedef typename result_of::size<Sequence>::type result;
        return result();
    }
}}

#endif

/* size.hpp
vYPh6KR72N0FhpGEOxpHzgsUKie1MwfDwfEuXg1t7ZoUMCkOfJVUDsYLXNjcFSTqym5TaNZOp5k7belDziKla1L+6A1OSynuRiP4ylP0IbLXfgXjcMmSDEWRqcSK4+iLTsatVtOC2mmRM2bsgtuneBfkr4gbeumQ8AkLF8RIyEt1YWOG2SE6so27bRsyBFt2Q9q2t4X1ydf2pfC7o7Pc1UVu6zj1RvIDUktUxKcns/F4N5X1DWrn/GoDoda+bAZQ+jn2Uu+Vz6ykiF9jhdsitK/YicIEmfLrW7oeVUPE9Eanb2zrOOy9PH/VPTvrDYZFAuwtoW1wvtivRmTTdpAwZXpKa3XlYlyzsFpTs8tb3e0NDtZhm4Rh4u/nuR7Yn82iET+Qutb3ctWxv54ejd723p4OPlYa4MaGk/sCu/b9PbDoacHqw1UqErTxPHoEQcGjQ1+Le+uffTjsv+oXPvq0/cUeXkZ3vtS7oS0Q+BdLAd0Hw6gUaChEYkLbX6xQ1hVVMwakRb2hIQGy/bTj+5kLASy5BSI/sfUFzfKKLT3crjzsLD/sfHGxU2LdYYPLdODOYKOe08/tJ01/zvqRprjrEYaUykI662LCWmzjD39LKlgwFpNJUXI6jx9j4i6u2MKPFfYSKCurffb21h2n
*/