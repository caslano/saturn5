/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_VIEW_03202006_0015)
#define FUSION_IS_VIEW_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct non_fusion_tag;
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl
        {
            template <typename T>
            struct apply
            {
                typedef typename T::is_view type;
            };
        };

        template <>
        struct is_view_impl<non_fusion_tag>
        {
            template <typename T>
            struct apply : mpl::false_ {};
        };

        template <>
        struct is_view_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_view {};
        };

        template <>
        struct is_view_impl<boost_tuple_tag>;

        template <>
        struct is_view_impl<boost_array_tag>;

        template <>
        struct is_view_impl<mpl_sequence_tag>;

        template <>
        struct is_view_impl<std_pair_tag>;
    }

    namespace traits
    {
        template <typename T>
        struct is_view :
            mpl::bool_<
                (bool)extension::is_view_impl<typename fusion::detail::tag_of<T>::type>::
                    template apply<T>::type::value
            >
        {};
    }
}}

#endif

/* is_view.hpp
ORp3762rovkkMVeFVIXhIVVBuXu2y/PoSHAZRiJjRgFO6zGiZSrTvFJRpgx4slxfJOknURrkIk6Zmdx7b7dp+as6FXmtKkZW8N5bu7cBD/H3VxdVmUtBmfx+v0z7PQvKNBZJzOiKT/e5V0leMavLWIkqKXpMbjswtHEhvCFLVRBEKmf9nYFhZGjj8lj6TjOrYO7JDN8m6dMA/aIBD3kbmpZ5EqcV22O70PcfOOfyL8A0FKdxqDS32wPWLyRz8RVLIxhFWSCQwWmQpa4tFSljAtg6Efpx+UT1Hj2vjHr1y3gaZFkdsD3Ufv356FKPvw7LuEpyxfZQB3b86JuS8EeM50lZJYG0/LTcGLOJ8HEWSZgIZJIgn59ngH71qByIvOB5ldWMaPdbphdh/DiX5zFlHWRpUBUMN2n9PKYeR/XJaRhJzlNGdnUmj65Oh12eULAsDGTJRWWZSKVoLEzCG+uzbZxkkjN/2+Hp/VPCC2WsuYBxoTxeIn5WBlYJf8biVN+0lBXl9wb0vzFeEfDTOImwZBcVO6tDYZ8FLcejTpycbx0yeGeZ2afNEJ+gUZmXsmhZjTmAF//xbW5+FUtA5ERQGqbhBvysr2303njfRHmiINSBZXnLox0gnFtd3uq/6wUeYrcV5UKEUrRMF5afs3ZOu164cNaxT8S7D9omOsNIpjzXvK0GCq4h4W/YoQ7v9Z4slCKFChZBy/sCGMVwTKY5I+/s42m+YZqHUZoIpvttvunCfgCrAG37XF7FUpnUVZxnGINvbWw8TRg+0d2HkDyhceOszoOcd34uwJUHFLp1dTHSA0CXAXcG1h/Bs0k6kvGMZ1kUSzZExQTln9fbEupP4CJJo2C8yqo0rnOSRnMbTZIg6+hUOkXPLmkaBjoubbvCGH3dOsRgovLyNpI3Z6koRKV9GaxtQBOM18atQxN3ncK4XZd7dVcqyrKwCBkUUhcR2eZ9zxAoc72+L0PtUUdFmIajaOx8SuD9Ge37PCqrCtY6dgH8tDaNBkdyPVD68+TsE6jfozyLtZaRgb+WjgctglHn4fLULMz11XouWx7qZdfeo1KeSCaFTHPV8ujjPI2DhTK9QPniIpRxEOq8tHZpGRpCTxaWD31jPIHKUZTkOpReyCAviF92AYbCc4z7FhzNJhHsj9Un9H0YiCjmYc7AhgQ9vdgeoecaWu460HapeaxZfSZ4Wtytc5dcvoW0DKC6MmJ6mrFjzp1Laf/p8IclTzLWpE5llWFsa1KviKWVLCLRxEZrR9lwpS8v1vf3M2dIm3BtVSHDfFJctb4viisk35SVsPKXCU8prw2AafixT/9C+CUIkcxUnBcuv5kVtAOFzQ3Hy3IXV+3oeuOLgZckalpLfzDQL20gnThzuK8TV+1d1n8CAK3zBIzH+2hqx1wGosh5YlQnTw5lFrm6jMHxbr0CPnLeC+o4TmtGWej4+AvNK6yDIFYZN+oW7w4b85qi9+ZFUsZ5rm0GIp/tXmBn+2aw6an44ukoUHxJ68KXTmsdeBVxGhfmnc69+Olgsu3Z7qCPW4IqQu1cm8vpPsZcjjv6misUwyNVkPtxfN8x08dhsRCzsK+HwSLZe93fUMzk5nBj9u83eBIZjMaisXTMEOv3C0o/tVd7vu1gH4f2WoiRs30M5mdtBgkGIxEh/a2HfDrchOCdY3wLpOOhh5bZ8VVwy0lYvw0uezgiC5j3yq08XE8eqH9TH4vFtO0/CYdFtDYOr72Nh9tLNrA/2G37PCgfiPmLh8HMsd6XDnsYT07QnuR2fSyRFcTN3t7HTRqjH/NxKDMYz+cOHgblBmO23VFj8JBlDWFc+3UPs4sg7Nc7UQwVPuqPlOKwcoi5eGc=
*/