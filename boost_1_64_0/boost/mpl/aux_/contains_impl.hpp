
#ifndef BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct contains_impl
{
    template< typename Sequence, typename T > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > >
    {
#else
    {
        typedef not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > > type;

        BOOST_STATIC_CONSTANT(bool, value = 
              (not_< is_same<
                  typename find<Sequence,T>::type
                , typename end<Sequence>::type
                > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,contains_impl)

}}

#endif // BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
tJJpwsKqBR5ewZSnmf8lci+z+MexbHMvWP42eIrlNJifGs/1jvHAxHTDvx58+l/wEft7/ivB/tBHK/2e9Jvg39sq/Y5ZF/y7S/B7s+4K7f/1cij91lfP03uzwe5w+q2jk1T+WiHzbxTvzSO7wuU/MEXlf/ulUPnXivfmk2Hz/2qLyv9YyPz3i/fm4LD5D23S/Q+Zf/0m9D9cfj5fxq2BPACMkjK4GIQTAyVfhKuEIg14NGceKrMC1R68Fw/YM+a4B9Y2WRvSPDAOe5i+CJ4/yJjjmDLmOMg3DHVNSJUJeN/zTbBnPbbpbh5kbjF/g8K/phKqKbOMpi/dvqyK/dPaSPrOBQ9WsX+KmH7J5Cr2T2sipb9/cxX7p4jpd71aOf2iiOkPLLXra195M5o9UGG2Pf20qOnXTrKnvyFq+hmbguyfoqY/tCHI/mlHlPQcXzKHdAdm8QPikIDZD51RnYTB5krxcsqTKhYKHf8I74EjKg2QcEz2exuPSvzjJcxaJFFu8+9L9KlDBX7mhG8y2FBX1WC+HK9c+SSYSQX3gt8w+UgdpK3djY3rLUOFZ69WrECG+YflorYi2lZwq1ZhJH0oBjvHHILkrgx5vqs4OS0eKdaBFbtRckSpNNqst7CLOiMjXMWFeB3IEcRZmVe+rFXslLeCg1sK+193wI0ItAqctx6MqshhuxEs1uFrTv7aTVEYGmO+dhUap/TlSDLQfGSG1balVD5iPRt7bGPw9FW6beKegoC0om3LifxJZofyjqZsMmqnMyAYWWHidUINzNpCTLGKE8Nn8HMJykVmlNFOTTWYBzXbXz1bA4Zk8WwwJDj04WA7ghViQOZh79wT6NDbDuUQjLTgPDpxWuD/xPnXM3hUJ92oObZGDX22BjxcPDcqcLt/ArEpPK9Zl+AqAE6/Dj1is+M0o5uubq6tOj8LywSWWAlBxfZ0aFZIpdjLKeBo7HrhbMorf24fy/5pZdj7Wtfa+r52h76vja5tN0Yc6BJ3098uDALyTTMG6/l4XMzHTIl/9gzPR1+aRKaBT7ktN8/agRnsC8YMbDe2NzKGW7Omyknmck5rpkT/09B/2l/mvevt5HB6bCjDGwxJW7dleNNeuKooScIAt6aCj6+3LLwWXqGoYJZP07qLjSBYjHRjve1Ckct97LCoBlul6FFsFdBxFeXaP4t+GMtsbfn8OQ2qcYhBd3ApTDB7UNsZ0N/MucdONR/kyB4a3P5aNV307pdOoOaLs+RxSaFOUFpQMQnY9abuVm/VrZue5kPoMsptfrlRVHYcaBvHcSwgEHGM7Vi48vKgY0GFgImfapHeQwgmgBgjtmPh2yW6sxc7FCWXYu8MuFHz+gTmoWzc60/VYMyNXB7zcbp0vs5So+tMQd3qwM5AZBx9o9XV9a9Jdd8/wtWdorwsty7hyo58BxkVFF0lzPDmM16QnMT9Kpg05noIYUVyQAc6xfQxO76WNbEzmIJ/GqMpuK3NTy2swbHSh9scSPe/dhKmhEysi3XJ+baSuy/UxLqciPVX1r1VpWjKKSCQf++p/yViHUl+OpyYYpiikH6qE+MnC/6B4/JDoiOvIRlGG3UHqQN/UBX2z6To/ywvdgiPy9IFSc098A6njDjirWtWjw3yHrRvKUqo6gCrylzstGxt5mhbG363E+94f5yMIS1UlrqZXXo7Vi62TQMjY4O0/m7JjwNXi1VP58094/HbwnodK0QVSFo2Cq+MF9SxAdHGuFksAs4kYZR1D9zHaaGaIoaiDbtCB4/ZUDVmHxD1rKGNw+l8LP33krDn8yLbGAsXZX1Gv6mtQNl00myWpeSOM3LKBNHOSqAvK8WXdgBtqNLvE+tlvz9Zwvs=
*/