/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_05052005_1107)
#define FUSION_FIND_05052005_1107

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/fusion/algorithm/query/detail/segmented_find.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find
          : mpl::if_<
                traits::is_segmented<Sequence>
              , detail::result_of_segmented_find<Sequence, T>
              , detail::result_of_find_if<
                    Sequence,
                    is_same<
                        typename mpl::if_<
                            traits::is_associative<Sequence>
                          , key_of<mpl::_1>
                          , value_of<mpl::_1>
                        >::type
                      , T
                    >
                >
            >::type
        {};
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq)
    {
        typedef typename result_of::find<Sequence, T>::filter filter;
        return filter::call(seq);
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq)
    {
        typedef typename result_of::find<Sequence const, T>::filter filter;
        return filter::call(seq);
    }
}}

#endif

/* find.hpp
MbdpTh+r6SY8AnHrVgBC1QLmellUgMdM2VxUPyY4fWv7LdMatOh2pmqGk8MwNEbf55guUMvllJyzPBkIKApX2a4cHYg+y28CiSlWtuQhgHwVaMZAUy0bZTqm5pqBycrMQjpl9vTG6YJ6LEbj0xXd2fjOTUTZYpD5ocs7F8dBAVcyLqdpRcdlKTIv2DG+C7RkVPOHpmV6pNwrrt/l6A1fb51cIjJPIJSQz5SRiF1iI9zSWX4Ui2wjz4IG3Tl+Sk/FZb3xoLYOwHXTy8JgqhJNe0pw8p5zqSa2raGUG2vqlFVtKaGMaVACGas/hswchegnu8KcOswlyT4Ru8bhFOnLk8IlQ9MANYYua2fsRHEoEVUHZxCHn8Bin+h3dOMm8z1u5kVyFI2LKT4VBOhR9x53YMOtkPwbGJ80BmRUNPc7uaG/Imm4zmDDgUBSq0CC0ETDezJ16BlyzKd+hZIDF7A2V+n+1L08PJfRwkrmKoIcWWlaEIl9+PGzt3eAGigRWR9VmvjftlZkkeH6pNUIjLvtVuBHrLizcEGNitPUqzAgleD7qPfs+ybE1jxK2A==
*/