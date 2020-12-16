/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_1142)
#define FUSION_EQUAL_TO_05052005_1142

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2, bool same_size>
    struct sequence_equal_to
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
            return extension::as_const(*a) == extension::as_const(*b)
                && call(fusion::next(a), fusion::next(b));
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

    template <typename Seq1, typename Seq2>
    struct sequence_equal_to<Seq1, Seq2, false>
    {
        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& /*a*/, I2 const& /*b*/)
        {
            return false;
        }
    };
}}}

#endif

/* equal_to.hpp
QuQghE/6cHd1Y2etTkZ0uzW6FIE4kGc2c5pj0FEu7+ufuwn8JUXwpyp4r/QBychnzSz3MfCOR8g+N9WtkMWtKPyLbZbDF35iuB+FxD3FIiRb2jaXI2GQ5xZx7v2/e4Oq/xrj1y9QloiEUHB+jTzzjN8iQwg9ITIENX6HNCc9lvu3jbhr2IiduNDbifNstd96XEZHjsi4A9uP/+Q098i5MOLlLoqXQ3c0/RODNOxBmVXlqj4pkUO1X11/w03M/SpFauWwAwXzI+XeTvsay3+JO2rh+xE4vrEWi2X/nfh5BO/2GC7uheiJozKvhCDyUxnxQytHj5Buaf4eUMr854RuqcSpLTaSmPQ9uHAFXn2ya8QHC1+6O5Q2y8FTiurCKJ54rFRuEvcZc3EpURjh9ptw7XQzVV4s4JbwAubP0k7hngfE/dxbPgZ5JH6KTj91T8CeDPymglV5q4AbT1XYX7UMmS3U+437qu024nBd2/VGHIhx5hv1gsCx+l6+CGq8d+yZj9f3Ms37vkY8wbzWATbjCOYJ50/NOGBen60rNwWOPluZvisT/lY4Xq35aeoIbybwBFK9HoyPxHnlfoEzXu2vjanevTenb1P2niq/S7cqKuPaLeT30YRwf3vL6pv0zqBz/NKtzO99Eftmg+XSuLWEIwNpy7RrvI34Xj1AAFo6r5nwxdsK+Pz76cstuP0mcKtFgfOf3z3PN+HIkqSOE6uecPjU1EpT/Y44F5e/Ef+2GU8+XWq83ds34lFj6f3jDgKvKRCsvmtcuLvcA0+L+aW/L95T7Y1TET5Hx2ZQ30klqGmuPlLCxPPIc3foe+vx8nuZLEPjT9T3aQW4pyrn0VS3cFOsHE9NX4DbS/hgQ3zvUzyHRfWdTDlnxPcTJQyP+rLfCdZ6pIbJ+BrES+vGfRqGo0RkF8BX6o/rqty14cZsILBaQ8Xn5XurcqGimLZW1XfnIbo+MLmq6rokv4udZroOUwqBYNQ1UbyUZg3jLUSeIz6Lwzc1YIPVVRQxaRl9CloTvjPbOnPGKLs4YsJR72iNaC8DZtYrN1aSpZeOmnBhKQI3eDjGmv10ETjUj+tbrN2njkvepc6yD+tF8E79dfChCl6aY8xo7t5CjTfOe+P71RvU9+lozRjnxXfcRPIwg6/ubGreERcdfkdEMmqE7ir+7zuiukvxdUXf7XUlvzevKwGz1hV95+uK8O11he+dx/+HdQX4L+5trSvizV5XBLPXFcHmrCsJm7uuJNxeV9Q+vq6ob611RXXNXVcS3ryuBGzuuiL43HUl4Y3rSsLmrisJn7+uqHx7XRFvc9YVzRNrXdF3vq7oO19XkgfMG3tdSZvaweMBK21nMXHlbBM+NqfFe9C7xXdlaitm9pTO+Wv4SU37V4BNvd75mwg4D2zNZUYN54GvNc5HFmwcyaL2w9nDcciK1uDl5XUcqAhN+MbeGvzskMu3DXBp7mv62RAOBRtvaX3tb2/K4X3qVmauROWdvJnGF/VJnrVMul/AQVuzyfs6fbdt8ky7p9nNBZ4a81JupjJ+WcKas1nDaIzwZreYhyd1uBLv+lw8Ug1Rma+85XxcSFhU5oFbzcMjcZLK/KCJq3W9Ytsazoaaz6VbN+I1vrG/1cK17VYWb9OIY/vQN+MJo1gq6/G3bcShxt7V0AMmpa9Mqa8ZjQ0/zD89wXyb6bjtthdDXVXl7JfKAPJfwd7O7K9CER7dEaE0TFcNeqdcfCJ/p4x7cERow/HCjmtgvXtffjR/B0LahrYIr9kRQf8HG9lgk1RZxyl/zBP5e2yBcLieiOk4PwcHvUtGT6z5JKRpFqfe/23/8mDFy6PNOFVZ0o3xTJo6UI0/RqrXtZ0=
*/