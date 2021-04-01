/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_05052005_1141)
#define FUSION_LESS_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_less
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return false;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) < extension::as_const(*b) ||
                (!(extension::as_const(*b) < extension::as_const(*a)) && 
                 call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* less.hpp
V+XqADPOK7Oxoin60gMYq9N7DLBUNGACYkoAdJtGFuMlCq3vR7uLySY98YjEZp7zCjwU6kMvvHGpAF3miZJdI5Nk7Y40RlYR7V0MoYYdKXGXlGySbFSA3NuCKG/0kK/rdbocC/KqB0+0WAS9M4wGFixI/5f9Rgd5W1kClKZn3whEWEDsxs+FF8r1inZVrKxEu9nPE/gdlP7d3O1IlYuiE7zj3MvUnpfbRj7h8TLuKurspVe+e1yvnSV20I+4Lv9M1jd9lktuChekg0ApKG0SiLvfrLFJWpTCAPbgTr4Hck37oafV7dqxw26IAmC5qGct+pwwLmdzzHBrNCAsxrt8tR8eyBr4kmVaP4y/ZrpCdLb2untcIGEKbujWNuw+eW0Maf15lp8V7+YdBBCiZpbR30fFPj+Zd1ur0hNBZlOj2SKtT1JfnKNrmtRDhA4TpNCjVTEJdnp9JfEc1j5cl7NkPUskCIG5FtUnRZ+ALbqAQqcKrbNoTn0tAFqE7yN9GaCwo8no0AqxD1yc9WMiSq+oLqjiNJCbbWL4MvuURZIVcck23pBfYXT2RNvIjQ==
*/