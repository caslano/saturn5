/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_EQUAL_05052005_1142)
#define FUSION_GREATER_EQUAL_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_greater_equal
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) >= extension::as_const(*b)
                && (!(extension::as_const(*b) >= extension::as_const(*a)) || 
                    call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* greater_equal.hpp
IUjSAal934C1+C/Mnp2szgYP+laEW9DRaJq0qCVdA+9EfA/BARTIeIYSlMQGBa+/hl4fkLtqCxRJS3HKDDCGPBaKWqs4ebL/zXTbXNhG15JonNcS7KpFmi9GGa79QnyQ1Q9L9IzVwrhqSrdIt13GbfaC60q9vmIu8JGQeMToBHzUGnRNZ/ByQH5ue8ALtYckz5xRoC2Klc43aisXGv9lS9LmS/7bQCs/U7WdWnQDF8S7cSrVnYGWtLTHMXTE+OhrpHGa2j//V/BmeAnoGzoFqAjceI8vb0s9M3JDBuOM1q5r0fm7qYeSwkUBlvU/9pCwSaP/Gti/VRDmsVagV5BJVsvGANSfK+Ky26EdECPa6o4QVwwYRzIS2uOLtzaoKQVwv/CHa1Lw7+froTND58+3SBUBuLbPqVonAKSGTjpCZ3pbgTlk6fHjNNObr1SpAAAhgIfLibCJ0YS3p18ew+j580hbssvi562HVace4JW3siC3vl/hiJeZd7Kcm5wvh5SaZ9Vy3WKIBlnRdSJIRL9zzDAgh2R/BO9TBnGzr3hCeDNRATn8nwT++jtjdw==
*/