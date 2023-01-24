/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NOT_EQUAL_TO_05052005_0431)
#define FUSION_NOT_EQUAL_TO_05052005_0431

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/not_equal_to.hpp>
#else
#include <boost/fusion/sequence/comparison/equal_to.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    not_equal_to(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return result_of::size<Seq1>::value != result_of::size<Seq2>::value
            || detail::sequence_not_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return !(a == b);
#endif
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
        operator!=(Seq1 const& a, Seq2 const& b)
        {
            return fusion::not_equal_to(a, b);
        }
    }
    using operators::operator!=;
}}

#endif

/* not_equal_to.hpp
NClQCYsAWJ6MUqVhZ1STaWYfYb3q2MPqlI24qQGFe9JyguK5VV1qMkWSKYnldgUX2yskPVclWUQ24OF45d/JmPuYbGoXSYEf0gI1aqMQGp4aUMzzOkssUUuNhja1tv0BMF6MtmHWW5JHK1Igkiblb/e5Ak+kmuY4MOZzntmfrfyDthwboVug3jGpgbB5XorEksgTzixi3fJIwCohkuxkwxsxntTll/GlEG3mUWJagndHTE7aqXoUg2OUwm2PsGg5LbVKGkE/2Qx/FZNjT6CkwUSODIGS/Sbu/3kvej2RzSG7uVyde4fELmGjj2cPb86uSwqVpfC+evNSbP8SnsuHV4BxBTxsK/lFYWhQzcHMdC8lg8ufdXzegOAsSn01qW5rvNkUoch7vTpjRZj9g3d8IY8fwHPs3Jek210QJyPHrhSUbDwOhZ4ouMVxMFisUIh0SaG0EEQT6P0azHjaTTmRiM2kYv7PW7WnvglURuOYBIw/QYaW8hM+3Tif27OTv5ntd7NuyLYe0Bu07v/EyreQolFn2BwtcvndGtOsTVSiebtj2JWi+3AgkzQgAcIuyvhYCCn9tXZoIuE0xWIcj4dRsPXtyr/NxKgYJyOwWTkLN7bi49iY9Cc2m32JG3Nwe2pKf2zTCPMZE8ds/uxUjDFT9Sgat8wEuE/Q00N3Uu0n7zabCk5UY4izNG6dUnpolRnB0Yzx+lBMgot0x09u
*/