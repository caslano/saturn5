/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HAS_KEY_09232005_1454)
#define FUSION_HAS_KEY_09232005_1454

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/algorithm/query/find.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    struct void_;

    // Special tags:
    struct sequence_facade_tag;
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct has_key_impl
        {
            template <typename Seq, typename Key>
            struct apply
              : mpl::not_<
                    typename result_of::equal_to<
                        typename result_of::find<Seq, Key>::type
                      , typename result_of::end<Seq>::type
                    >::type
                >::type
            {};
        };

        template <>
        struct has_key_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename Key>
            struct apply : Sequence::template has_key<Sequence, Key> {};
        };

        template <>
        struct has_key_impl<boost_array_tag>;

        template <>
        struct has_key_impl<mpl_sequence_tag>;

        template <>
        struct has_key_impl<std_pair_tag>;
    }
    
    namespace result_of
    {
        template <typename Sequence, typename Key>
        struct has_key 
            : extension::has_key_impl<typename detail::tag_of<Sequence>::type>::
                template apply<Sequence, Key>
        {};
    }

    template <typename Key, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::has_key<Sequence, Key>::type
    has_key(Sequence const&)
    {
        typedef typename result_of::has_key<Sequence, Key>::type result;
        return result();
    }
}}

#endif


/* has_key.hpp
6ZEkLcZcH1PMqk7t+w2MfbXvXfR7M/2W0O9C+l1Ev4vpdyn9LqPf5fT7JP1m5eDvAPp9nX7fpN8XrsXfW+l3PP32o+eV9PsX+h1MvzfS7yz6XUi/Pvq9mX5zY+pPpt8T1O5q+r0ix2zS5qE1WSSv4pVHxnF5pU1Jat+rsrFob/q9iH4t9PvrAPw9Qr8H6Hc7/X42QN9H5mfChgWuIkNLCx6v66zai/qbTeE6TXykvDrUDOLDZEOR8ET/qDnyXe4YtGIo6byqvSlLc7d4ltQ7eLKqHzk5LaYSoFtYfxuIjsm7eEHfI1RoKi802yj0NRV6WyvkpkJjeKGHjEKbqdAirVAmFerXjzyRP4BXjYHkTHSw2GpdC3fmcJbKA65HzWutbHMpdw7km2upymdkO/aNhIcjqY20K40t4ktw/VrjlId3U3acVtXwQjrwkArSdUMBuZhsRqmYYHzgv5S74Dj24GwBYn5gFm6iRAoZatxHsrH6DVlG+PpuaB42zdeO7tTQi+pIhiR/0iCQhfSjbNSNv1DtK7NIzqWjnDvSwdk8jtdkifXsW0LEGFGA4IxR7cegjzbaOIEAERvoX/0NAK6nnYjeBCTaH54o8HVV7Zv6YYCvasJdtYewk7G+oLVftmZqa9WvfH2k2pe2a+m5fkbH4OHh0cBbkQGwHJiGdtFaZJ2VoWASuU2o9vDVuHes3IbzSHCEjU57qnYHwVKl
*/