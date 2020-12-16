/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_KEY_20060304_1755)
#define BOOST_FUSION_AT_KEY_20060304_1755

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/has_key.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/iterator/deref_data.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct at_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
            {
                typedef typename
                    result_of::deref_data<
                        typename result_of::find<Seq, Key>::type
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Seq& seq)
                {
                    return fusion::deref_data(fusion::find<Key>(seq));
                }
            };
        };

        template <>
        struct at_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template at_key_impl<Sequence, Key> {};
        };

        template <>
        struct at_key_impl<boost_array_tag>;

        template <>
        struct at_key_impl<mpl_sequence_tag>;

        template <>
        struct at_key_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename Key, typename Tag>
        struct at_key_impl
            : mpl::if_<
                  mpl::or_<
                      typename extension::has_key_impl<Tag>::template apply<Sequence, Key>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::at_key_impl<Tag>::template apply<Sequence, Key>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct at_key
            : detail::at_key_impl<Sequence, Key, typename detail::tag_of<Sequence>::type>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename 
        lazy_disable_if<
            is_const<Sequence>
          , result_of::at_key<Sequence, Key>
        >::type
    at_key(Sequence& seq)
    {
        return result_of::at_key<Sequence, Key>::call(seq);
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_key<Sequence const, Key>::type
    at_key(Sequence const& seq)
    {
        return result_of::at_key<Sequence const, Key>::call(seq);
    }
}}

#endif

/* at_key.hpp
/w7ocF9P6TIPBaM/wpoytB1wj5Db9mOI0/Z4aBt0f1h9l04jJ2chkYoMnDBpnlvh/X8Txur/57Bqj2L5XuCDtyoEy4J+8Xbq97E+omCPpgnz6/WsYnxpNhgXVfv11MiSzPciO+SGoyLQOrVr6n5gQNHdTmD4hr4HutDAUabAj2xR/Qpats9MNnKjeIOCQzKHy3iVA5tVe5gwTZlVSGZwI1lq0/61SNH/5YHNIlWEHrORpXbqY6oOx6MgMBPTdbmd/qnAqep8SMXHRph4fhyZsVACOQTe+BSJ3xbYtp3HYPCJoeR6FD9F9IlZvCPTsvgcCCtWNeaPr+LtyEhjy2sF1obzhWJcBCIvMXLLceLAb/Cr7nab3aqZGziMUZ7TbGIzztMwUGFcC9th/F1M20DjPKcLGladMRa+zuz+eXSI0JAZ50eYrycHka7FEb9I6DSOOAgmNDbP7xd+iUgrXo7w9+v4O9oF4H3ApDK/4mBQ80URDLzP8l0aztFDhI4ieLhP1OEriIPqKL+PD+PvZO/Wl7/3ZLnIB+MT6Dh/yvb5GPmdTZmS1t8qaNh+Ut4I0HC+lTwX8Hdd3qFtSEN5GB8badAW5dJwVt5LAe92QV/n/Q5ftHF/do9hHvKetl/mBwNsIWv+rDLv3R1U57EwyCEVo5WUYxbCyYohi3P2QXWePNaKbDN3Asforp3F6cnA+en8QCW+JGT7SU1jTuRE7FXihm2mMeB8O0lD20JlZmV6HRm/ZTPVPw6jsAVbv3cqK87jfEwamxiWSGMNW+zHvsLyLuh0MTZxXC9SDGPHnIXGoEpDVhlPCsbt0UEiX9vLfVrHkL3cvkGNTnzo+5QO41zJMUBprGik+ZsJDYpU9i+UBsUhDeYyoMkxA3SlLkgj+iLv1DDQcXxQ3q8gjfJijrgtjL4KH7nszzgm2O94vjBnIIaadWqG+hShjd65AdUXJbRd14RzA+w9VrT9wZUBmucqtM00dF3W8eHox/aNlfhOAzRPTgrHksjxy76cn7LAZwD3LRhXbYCuX0nEfCjDZKProejvd//L1m+lxEoeznEoj9B5lxXxrr/O4uW/PoeJK/fdk8AHv92A36B12c85cPBQ2Jj6o+D7AWAEAEQVfD+p58OUI/sB82XkQ0DB+7N6XtZ/sczPw5ys1KSQ91FVHsTBhZ5S/H5L/R2ihqjj7z78ffmgIqlyl7OwqUqn+/Y7dfQJuR4uDVboeBU4d17V49Wbqzgaf+SKRqd3+TuHqnRYJtUcjTpd1QNxnx1GXKFoOdHPnu30wWNBlgd7UcCVOS6nTS5S3bPcQbprC7I8H3GaIJBzkKCdBLk6fWaboCt1Ub9HQYd5pEGvi9s5XdcLfAoFTS/3R0hDvajeOwWd6oVvXrsYnbcm9EtY97n9OPxertOcCFEz+RsQ5tC7r/rFBW4WWk4QGeXBt+Kn48McoPrARG4eFPnMK/kJOdsg2jqrfEehjCj3fHBFRsd9GELoD0HKsA2Ysmw3doJKGZiZEONQkTI804pZUvNUy1H/YSLfMTwndTLwzJfyi3hZJ1Mz1mIifFrlPQ7m2iELMSg5OcNJ4ZNzR/HJ6a8srbwbvGQx5zPIUs8rocfS52047CXaQF/4N5NHG0mZgzHX8d0anJKdCvNYGf9BHGkUBPLzyTvHoN8XWKZSkel09ty5cs5/QuRigh019N7CPmJZ/lY6KnPbHkZ7k0KDGYhTStpbJK2YRQWRzcGhiN0E0XDFXM9+/8Uk/E7Co5d6zSiyYLQPPA6//QmwsC5YcIEYnJz1zWkf16Fi3fgboRetq+WeOi3kzsS20Pud4jfQARpw1juV2tNc77+DTLq1gL4Gv8OAY2VNz5g=
*/