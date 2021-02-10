/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_09172005_0730)
#define FUSION_DISTANCE_09172005_0730

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion { namespace distance_detail
{
    // Default distance implementation, linear
    // search for the Last iterator.

    template <typename First, typename Last>
    struct linear_distance;

    template <typename First, typename Last>
    struct next_distance
    {
        typedef typename 
            mpl::next<
                typename linear_distance<
                    typename result_of::next<First>::type
                  , Last
                >::type
            >::type 
        type;
    };

    template <typename First, typename Last>
    struct linear_distance
        : mpl::eval_if<
            result_of::equal_to<First, Last>
          , mpl::identity<mpl::int_<0> >
          , next_distance<First, Last>
        >::type
    {
        typedef typename
            mpl::eval_if<
                result_of::equal_to<First, Last>
              , mpl::identity<mpl::int_<0> >
              , next_distance<First, Last>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(First const&, Last const&)
        {
            return type();
        }
    };

}}}

#endif

/* distance.hpp
wxf+zGK+/BdPGqIzg8lpePBwTAlOrAplcOuDZMchx+l1uVLdEpoOna/By1wG8+Gy29tBdw5Teh7j3aRITHiCyYW0ma+ohc815qWyuqiQrqmKZx5emjScjakRz4TdCR2DR0ATjP310UXHe4NCzyekqBH3C02LOtMZsHz3TGEi7JZil0VCXlaKc11NMuv8BQwpcJcUQ/Ez8GFvXd/KwSquRnxZVA/IcIPVHB9mg1SHPkTbaJEabF78Xi2sXuX6Veug6OoEWx7Jkks4kSpllEKcIq6uzKW7/PCKZj9wQd+nJsQDHY8ii0BtkYFigM98/WbeMDC5b3lpI4uVp75AKHb4Fh4sIzOhW3POah+a5x+dHi0pfc0D22UylawLdZW2OrKEVoO5o53lx4nOX6d1mSYSmPhBus34i7UlqNBVVxil2bn29BlhrrGH2rUzcPYbvWrm8K+lff9eH/4S8Frss53pp6nEh5UcvAwXI1vojs0lidZRdtff7C6Fubwz14dZo1MBqMpLfEFUuaQvlwBMd5fip3BRYGD6woA394tgpV2ZUZUzGRp5MHZKaTp4M3q1wq3QFN/aZ+deAVPdKZ2gloM65jx3QRfZKUZmoADSHbHAsbqh5DDqBZ744SwWLPSoUyONDVRuT0OjK+Es6Kp4
*/