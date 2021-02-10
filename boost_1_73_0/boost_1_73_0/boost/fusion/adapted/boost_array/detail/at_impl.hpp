/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_27122005_1241)
#define BOOST_FUSION_AT_IMPL_27122005_1241

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<boost_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
bWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVElNRVZBTFVFLjNVVAUAAbZIJGCtVG1vm0gQ/s6vGLkf6kQE2/GdnFxz1VGHNLSOQUDas2QJrWEJe8K7PnZJYl363292IXFeKiUfimUD45l5npl5Zp1lD/Z/2WU5Oh28eqXmm+KF9/ugsBb/0Ez9PCBN76D9YOAS72+AGsAu6i7dgzdF3UHfRKUd1ol+TtM3wC01Sf0z0MHLVD+ipY3s4qdis63ZVamgP92D0fHxERzA4XB0ZMMp4YxWECvKV7S+suEkN5a/SnJ760j60QaqgFTOk4RJySRIUagbUlPA54pllEuaA5GQU5nVbIUvjIMqKRSsojANwoU//2zDTcmyssuzFQ3IUjRVDiW5plDTjLLrNs2G1ApEgRkwf86kwpyNYoI7CE9B0XotuzSaBKmkAHJNWEVWCEcUlEpt5B+DQdbUFVYyyEUmB9l9K5xSrZ9VtUA2a7IFsVGgBDSS2qD9bViLnBX6ji1C46ZZVUyW9o4WAvJ8IGqQtKq6dBjKqGxLoBB33bK1J2yQPVP6JgWXGu2mFOsnjtjWLlHR1BzhsC3olwtsvA0Nz2lt/E0j7lG6LpuWvzKyHfccBEdW0HNj8OMerIhk0obvfnIe
*/