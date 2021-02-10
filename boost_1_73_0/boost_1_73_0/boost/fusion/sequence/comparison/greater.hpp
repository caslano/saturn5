/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_05052005_0432)
#define FUSION_GREATER_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/greater.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    greater(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_greater<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return (b < a);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator>(Seq1 const& a, Seq2 const& b)
        {
            return fusion::greater(a, b);
        }
    }
    using operators::operator>;
}}

#endif

/* greater.hpp
2r+GPekEWv6HzFK6g3IDAvZCOcDY4o1TyEzjzhzvqNDsoeF2Csv6QQpnQA5TOHqSiks5LvcWmK6V8+gC5E+t3cua+XXnZs24m0z2sLBOeaFGOlh46nxfqsHwYTgKPvYuyA52tSBsEfqoQb7G8tvkYNMBeMJZxYlchEV0R+f9WEHZzYdxh8GjrYcpFbyjSx34Yy7cqEP07EFQCz6nLy0y3OBBSKFjZ1tRqHQ3tF5ScLCCSHzVrNt20xGw8/XhkZ5UJmC/tk4AxkD8stTe687wy/V4ELRvxlQPlRkev7kAh9Zcr77GQG+asq1q+HYdAs1hLpfLmSa6iCVAsAFeotok/GeI9yqm0Tya+ufqmF4XZRykOSmlHeZ0bYeCVPj1KGCuEaa0AadAojiGE+mpJNila5lR+iLMoFLeQDt2KeMNvytIV3VXXxREx00hp+QBdNhiytUBXdhICmH2w56KwGGXCKuqPahv/sHgHvydifsscsv7qBR27wsGNFxtHjxSV8fp8j4sLQcNhGClnAxw3UaFTaVXcv1lNerbSbz1ETbxux8SrB9IQUo8z7cVFlm60lcdwT6aC+UKQjz71XFdul2gl7A9DYDIYtuhrrrmhGEVN2A7osytIUtWcXT7dBoeFd2JZ0QM+jNQh/rM5sD+
*/