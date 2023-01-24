/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_0431)
#define FUSION_EQUAL_TO_05052005_0431

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/equal_to.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4100) // unreferenced formal parameter
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    equal_to(Seq1 const& a, Seq2 const& b)
    {
        return result_of::size<Seq1>::value == result_of::size<Seq2>::value
            && detail::sequence_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_equality<Seq1, Seq2>
              , bool
            >::type
        operator==(Seq1 const& a, Seq2 const& b)
        {
            return fusion::equal_to(a, b);
        }
    }
    using operators::operator==;
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif

/* equal_to.hpp
3Q+vI4JMWqoR5C9XXjhBTi6NYrJxBmDSjTR63JLCxRXw3g5fG4o8urQtPvff1I4i0Tg8PA4IV9DmP9FRKJ43+xiheB5c1WG8pazjRjecI97S75ZQvKU7r2wbb+no0ph4S5wXQBF84olzxVsKLmkbiidwI5/wO4i39LeVGJDnq/Q28ZYWENLs8Y6Q/jDdQHrGyvbxh677pQ3GZ4s/9PBiCstQmtU2/tBvS2LiDy0gpIGaix8/V/yhlYvbIv3ksCiyRvyhLc8iuj/3bhtv6TXC94+zO8I31NvAd/Gz7fEdeewC8S0rJ3xn9G+Lb3Isvq/p+D43+1z4vl7eFt9XhnaA75fPIL7q5Rxfg6epEbXvO7OisW1iMPIdvRCefX8R8exb/dry7LDFMTz7ms6z1bO0JAMGnx5a1BaFg/kd8GnHeXPdrLObtbgnKeiIxDdkf/Ij9fqbKNPolo3LqOVdqn0LiDnsxFHYh2jYupKnbO47Qz+m5BvoYTX4TVD/5umZeDypd4fpc5V1vQyG8D+NMd1ojr8N40fURnvx6katF1393eyAe1IzQApQa8AWELAZHNjqKLCroWEPqwd4hUXvoBIQOKkKi55DFR9UuZlGIAk8Lfu8MiBAAUwy+qLY9D8vyrea6fnlxFHe9Vi1gZNrJgVwthStl4JFmyTm+gC9Rm3ca7Ro01bMjwLffox0DVqwPrq/IUC7SP2RQDfcYBCG
*/