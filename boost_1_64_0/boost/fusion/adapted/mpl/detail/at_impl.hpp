/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_31122005_1642)
#define BOOST_FUSION_AT_IMPL_31122005_1642

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>

namespace boost { namespace fusion 
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template<typename Tag>
        struct at_impl;

        template <>
        struct at_impl<mpl_sequence_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::at<Sequence, N>::type type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
PzMXM3WDJ1VzUdVVXnlWLmo6f7b9/2Uu5ujMHHPPdW51mzed59ym+XNdH0t1nO/ZLnCG0zgfX/PcaT4fdJlzqxuX52L7K53b1Dx+hXukflJvMSJWpx46ImbvNiJauvnFEXHwl0bEOl3hZ9HRsceI+CY2pnF+DNFjDfmasSNisG7zA3uPiNE6vjIiTkRO1/gejNEt3vGrI2KkbnJh1ogYl+b8ekTsfd6ImKIr/BtM0g2+eO6IGK9b/JHzR8REnedHMUfHBSNiwcUjoprmXDIibp43Iiq6wztc6t90gc+5fETM1Pn5I2KnF0fEQt3YMCKOfXtErNA1vhNNXXx3RPwES9M4771xRKzXFf7jByNiberoj6sRva7DW2zVH2uM13ny+P4YbLw2qT/2O6I/pukKf+Kb/TFOV/nvR/VHJY0f3R/3HdMfY3R+Sn8cgYlpnBd8qz8m6cK3++MYjE/jvFu5P2bqMn/suP4YmeZwA6N1i3f4Tn/kdJErmKervNvU/qjqOg8/3n37zOGfneC+OjOtP/bCeF3if0z3zGn8B/1x0A9dX9f596f0R1k3ZvTH/J/2xwydP9W10Ulz+OGZ1iSNn9YfryBy+mf9sQQbjbf5xNP7Y2VaK87N6o9Fxqv82TO8jy7z737eH0t1hyefaX6aw49jgc92+KdVa+76db4Hc8xp8SbUdOas/tgdy9Ka8E+wXNf4OizRDX4cC3Wbh5zdH4t1nvdFLq0J/wIjdZ1vwzDd5BcwSHe455z+GKoLfCjWp/3iS7FZN/hBrNUtfhOrdMzuj89ggy7yiVijq3zAL8zp07xojnVPfW5/vHFef9R1bW5/HH5BfxRyrslXXdgfE3SbD6z1R0lXki/yWV3jezA5zectLranOsPfRV5X+Uvz+qOo2zz30v7I6CY/g6zOXNYfR6KqK/w6RqXxy51/TEvzuXu+vdAFPhkzdZVfxSKduaI/9kFF1/ldzEnjV/rsb5wHXeaLECPM4aeR0R0evAA6w2PQMb/Is7BO1/hJrNYd/tZvnStd5evQ1A0+6Hf90U7jfCc26ha/i5aOq/pjF6zQNd6m7hkGPBufi9X9no0fQlO3+UMs1Zmr+2NPNHSJT8N8XeM/o6ab/ArCNeP3/bEr1qX5/EO0dZVf/INn8L7Fhc4J5qRxvh4V3eR/YprucM819sj8Ah+FabrCF6Ks6/wQxuo2D7nWGUjz+RBkdZnPRSvN54fQ0B3+5HX2Uef568i6b5nPReg6342N5rR4E4ppTRZZE4xK8/lM5HWNH0VLt3nE9a6vC3wyNuoq34WqbvE2f3Su0jPwUZivK3w95ugmf4CCztzgOVHSZb4CRd3g19DUsdizYZ0u8blYrev8PDJpbXm3G62bLvJpmKxr/BAm6DZv/yf7pfN8OOq6zJego+v8JGam+bz9n+1jehc+DHVd5otR03V+EqN0m7druG+az4dhQprPl2Bpms9PoJPm83Y3OUtpPh+Owel5+BIUdJ2fQFm3ebubrZXO86dvMX/A2vLjmKk7fN4S83WTX7/VGdPFvzirqOjMbc72Unuqy7c7M3d4rzSHVyd03NkfZ2GObvCsZZ4/Nd98l3fX8Vfn9m7rmbrptxEdXebr0NZN3uFe+6irPOg+50QX+BXM1/nl5qKhM/f3x9+wSMcDrol1usxnYYKu8Z2YrFu8CSWdedDfFxR0kU9CUVf5eozVTX4aWd3mrVfYO53ng5DXZd6EwXnjD/XH6Qhd5/exMc1/2FoiY7zGlz7is7rNU1f6O57Gecijrq8LfBnG6wa/9zd/03Xpsf64Glnd5J7H+2NSmsPFJ6y7rvD1mJ3mcPeT/mbpAh+LNWkO34LFusUfWeU=
*/