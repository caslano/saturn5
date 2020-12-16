/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FOLD_S_HPP_INCLUDED)
#define BOOST_FUSION_FOLD_S_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/fold_fwd.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Fun>
    struct segmented_fold_fun
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit segmented_fold_fun(Fun const& f)
          : fun(f)
        {}

        Fun const& fun;

        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef typename result_of::fold<Sequence, State, Fun>::type type;
            typedef mpl::true_ continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const& state, Context const&, segmented_fold_fun const& fun)
            {
                return fusion::fold(seq, state, fun.fun);
            }
        };
    };

    // The default implementation of this lives in detail/fold.hpp
    template <typename Sequence, typename State, typename Fun, bool IsSequence, bool IsSegmented>
    struct result_of_fold;

    template <typename Sequence, typename State, typename Fun>
    struct result_of_fold<Sequence, State, Fun, true, true>
    {
        typedef
            typename result_of::segmented_fold_until<
                Sequence,
                State,
                segmented_fold_fun<Fun>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, State& state, Fun& fun)
        {
            return fusion::segmented_fold_until(seq, state, segmented_fold_fun<Fun>(fun));
        }
    };
}}}

#endif

/* segmented_fold.hpp
GhIPyp20UcWlkv46SvmW9P+d/TXGWdgXZ+NgnIMjcS6OxYdwEs7DpbgAV+BC3IKL8CV8GA9iLp7BxXgel6BS/pdiKi6X9zqPynudx3EBPoGLcKXkI/cy0taUOEt9GOg09/qzrNcM1+JtuA5jcAPehc9jFm7Ev2Mh7sAX8Ahuwi9wMyrXi61YD1+U47MdLecrzsKd+AzuwgJ8Wd47vYLf4av4I+7GSsp9Cl6Pr+PN+AYG4x68E9/C5bgPX8L9+Aq+jV/iO+ij9MXAavgu3oTvYWt8H6OwCMfiBzgHD+Iy/BifwMO4Bj/FfDxirxelPSk206kXW8p7kVbyXqQ1dsd2mIrtcRoG49+xAz6CIbgKO+Jq7IQvYmfcgaH4IXbFr7Abfo098DyGoXKf2RvrYx9sjH2lXBNhaUfKMZd68UblvJN4D5dyPRrjMRr/gWPwFN4h6b8TL+FYrKTc32MtHI8hGCPlNU7O03g5TxMwBxOl/E7CeZgk5XgyLsMpuByn4pOYinlolvJzF67FDNyEmbgF78admIU/4XT8HWdIucp2vOeUtpzu5xvKZT1P5hsqctqen9N9iry/lPWkPSO0drNe2EDPtmf2cL08D9cr8jB+foM8Wy9K1uvgZr1cD7dXNMizdJgi5bi5y+cS1qvotF6OrFffzXp5kRI/N+sVyXqt3aznN1jyz816UYM9217uYM/it3uwZ/liGuLYXqDLenHO82fJei1LWC/aW9pcSFsM6ifLO0LblMpZ7LcdzsDOmI1heD+OwRx5H/oAzsJZuBFn45s4B9/DuXgE5+PPuACVnS7EhrhIfid4GHthLvbHxTgGl2A6LsV7cRnOwUfwIVyOG3AF/oKP4UVciY1I05PYCp/CNvg0dsM1OAjX4Whcj9NwAz6Kz+PbuBF/wELsRN68gN1wM47DLTgdt+IMfBGfwO34DL6Eb+EOPICv4df4Ol7CN9Dfh/cBmIR7cSruw1m4Hxfi27gE38Xn8D38Gt9Hn4qUcayFH2Jb/Ahvx4P4GH6MT+Jh/ASPYAVuXD/DFngUB+DnuBi/wOX4Je7G43gCv8Jv8Wv8AU9iq8rcn+Ik/Bb/jt9hPp7GM/g9nsMzeKMv90zYG3/Ch/BnXIS/4FY8j5/iBWxWhftSvBl/x2F4Ce/GyzgD/8Ac9PKhPGAF/AC98RBWxMNYGS9hFQyn3FfF2/A6HIfX40SsgVOwDk7HujgD6+FMbIiP4Q24FhvhemyM9vf+ch521nmvSVnPqY9hGIy90fa93SV8b4B8b6B8bxBGVmI9ftjaQzg9ytujudCKvmUuI34ECyGY81n/Wfdzo+161jE/2i6XOdIOPvvvmSft1LPlc6Vderb086U14Ji3yfd83rTwfM/nThuR79n8aTn5jjnUVub/Z82jdiC/bHOpFec75lO7kF/6OdX05lOrXuD5nGr+BZ7Nq5bdzfs/Zm61yAL386vFFmjnWMsqKN08a2Op67IJeYQ9hFOE6twIBRFGELIIKwm7CScIvmOoHwnRhCzCSsIewmmC3x38GyGakE3II+wjnCbUoVFBOCGWkE0oIBwgnCXU4SE4lBBNyCbkEfYQThF8uaFoQ4ggJBEWEAoJRYRzhMbjvU3dCbGEuYRCwmGCKcbbFEgYQcgmrCYcJFwiBMR6m6II2YTVhAOEc4SAOG9TJCGTkEtYTzhAOBf3vz/nnA8h9RqP/2+eMD0mkx5PygQA7Oaq5gBQxtHf1tZkH4/DT8aYf5qbhGa4EpOUfhdf8l7eOv4ZPbdSkonChKTECVM8Gxu0Ys2gr5rZ2k7bx3OJwoldpW+BZQx0aVNcybKMIbnYT3Km7M/RL/d3+xzktHGWNtBXLHOeS8w=
*/