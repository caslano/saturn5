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
S3PGDIScsgQNFusXd44152c1u//2+02TkGwVOpsYa07kg9Js4by+6iig97JrYM2io7zdIwmYSyuO+sY5OkzQcd/Cu0t+4+0h1DK5gVsS1uL06US2gXmqucoLNFeJ6rNE61ldL0kSKbNsO6ss+iRkyXVwkFvCJFzJw97Eq3/E4A48rPUb2YFf3FduUHxm/vV+X95X4OtrfH2Rr8/3pb2LLm5yUrzYTfcf6YsADCzz0zsPuVwsmm9n0+3+fNtNP/904aUn/bqaLl3pcildOtFllYterLgFf35FL35Iv2bdwrxyodf4+iKVKobHxrN8c1Mfu2aMFbeMPL4zgl8fCle/o6WQ3UC8O+MN8Q41VXkfJFnWB0h+sek4ZPtIpGoudAHekrhlvEn3Y+FGp37i1WtstkJjIFQc2w/L/nMzff/NVPP1fQgzJwBTsBINafjRmQFb8W7vqSCQliwzsCPiUnIpzLJ8MrOcyW+DEOslv4Szd8Wv4bzaPQQjBPxhhNNcRd2CHLKOtyBxeRoOVgx9vjISPBy1mMvBqEv47RzaD/bZtyyL04yPDsZoI1PEK3rxy+hB/xbOWd1WHmbURtzafVZQEM+LrefF/BzXSVBkJBUptIoUyiLQTrS16IIkgb5rDu9uiYsXH2fvK73NDrFleAOzqj0BN7zHSnHXn88fxAx0iKtonRiCVoxM6eAqOCF06hbzZFvMvW1OArP1OXLE
*/