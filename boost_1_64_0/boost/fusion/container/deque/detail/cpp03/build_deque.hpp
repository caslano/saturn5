/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BUILD_DEQUE_02032013_1921)
#define BOOST_FUSION_BUILD_DEQUE_02032013_1921

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/container/deque/detail/cpp03/as_deque.hpp>
#include <boost/fusion/container/deque/front_extended_deque.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_deque
            : detail::as_deque<result_of::size<Sequence>::value>
        {
            typedef typename
                detail::as_deque<result_of::size<Sequence>::value>
            gen;
            typedef typename gen::
                template apply<typename result_of::begin<Sequence>::type>::type
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence>::type
    as_deque(Sequence& seq)
    {
        typedef typename result_of::as_deque<Sequence>::gen gen;
        return gen::call(fusion::begin(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_deque<Sequence const>::type
    as_deque(Sequence const& seq)
    {
        typedef typename result_of::as_deque<Sequence const>::gen gen;
        return gen::call(fusion::begin(seq));
    }
}}

#endif

/* build_deque.hpp
AU7EhmjGRngfBuBibIzbsQk+goFYiEH4O2yBz2Mwvoqt8E/YGt/CNnjegzGlvONJ/XfHk/q1zK88a5bvdY8rNc/k+4scW2r1LN8bHl9q7yxfj+daLpzl+6sZa6p4FnknBM1m7CdCGiGPUEC4QPCZw38jRBMyCHsJxYSrhOC5zLlMmEc4QDhP8J1HORDiCcsJ+YQiwkXCFUKT+cRDmEBYTDhAKCZcJjRcwH8jZBA2EAoJFwhXCQ0XMgYWIYEwj5BPOEP4K8E3lzQSQgkJhFmE7YTThM8I/osY82qRd5wq78/78/68P+/P+/ul/W7S/P/WJvkVNf9/M+sYgDI+UCX9uDa1lPGBzvIORB3LwRa/MqSEO3NzSvtaaYdrXUna6hrP7R0qY92tk37ZKzGZNCT9njTo5klWk+L2GCWO6YjWzJus7w9xW50U4s5fo7zXlmFRpplkrEHtnGkZ6Zmp2WpfCD/7MU+s25nCdoKOVCWvMu6fbEib96uS9yPYAA9hgJL31yTv0iZYm3F3xjqQNsC6vCfgAsO8z7C2bebdD98cZdyeP5AGTb4zbX3t6Xukb9tsqaLvqzWVfBSdc9Lv1cN+1+nG/dU4APX9paaxbKmzeD3sY5zuRn81te+vr74PWdcGhOKytESOGD4ocUz/mNFR1zMnGOWv60uWUk/Xl0xNT0MZC+8zSc9HhOnkx1xc1m6/f2Tk6FH9I8dV3PH9rdQtbd+QIknHVqkXGwlZyjH2Rlk6rh1n1pR4MGaW0bFtDpX6bdcHaoa0gbc7fm/qHGrG7c2dt383bu/srD27dw61KRU8h5pxfwXP51arqDnUzC2t7dkr7bznwncbXlr0vc+f+j8U3Pr65lBLInCNV9s/5jt8T2kq7XeaYVsMxD7YHIdiCxyLLTEDW+F8bIP3YVv8Wr6Hy3Wc67stnobKd1CJp4PEMwQDcSh2xRjsj8NwBA7HLIzF+3EUbsA4PIXx+CKOxvM4Br/FsXgL8SZgDRyHtfE32BwnYAhOxH54D07AREzGJLSgCZdgMq7EFMlfRCW5Vss1nPxRFtb2jtbfTMnfHMnfXGyN87EXLsBhmCvt2hfhvXg/LsYluBGX4i5chkdxBb6CK/E9XI1f4hpUvqutxUaYh+1xPfbEB3AIbpB8bsRs3IRP4BZ8Drfiq7gN38Md+BXuxOpKPrER7sJWuBvD8BFMwH04DffjAnwUN+LjeAAP4SF8QttO4ZzanqHcdiilslw7F8vJdZc6xrYJ2uUCJd48glmW+0yOgztwsUE75xb4FPbEYzgYj2MCnsAUTTvn3+FKPInb8BTux2ekvj6Hr2OR7L8X8CN8UW3nJtdH3CrpqokTDNrpBeNU7IcZGIfTJD2ZmIPTcR3ei+sxW+qVBUt93f+u5J2r5L//benX8F3per8p/RK/J93otyTvXCX670fhK/iWQ1hMOEAoJlwhBK3kW85K7zcX78/78/68P+/P+/P+vD/vz/vz/rw/78+z3834/s9kDjmW9Izsivr+X7mdj3x/lv7o/GoRrHO/E+5UvhE+X/b9eVjc4MQhw2L5dhpvHb6Nwf6mu55To5aMhbjS4Hv/donzDomzFqEfceY5jZNxCX1uLM7wyvo57CKIs8AwzmzJp+vv7PKNUY1TxumXMRPZho/jOIrKgMC2v2vTd17S11u+kYYqESj74QVn6aNM3PhWK+PfqemrZTeHYor6HdXiODeEpCtNvuuPlXSNIgwkXUUvXGsfMtI6vZ4ylpzr77a1JL5DmvKifNXx6LTjrkmapiejdj7CS5KmTvLNvy1hEGnq+qI2TSmpGamWVCVZ7nzTlnKyS1eYPg1quSTIK6RIae/Qj1DAuma7NBA=
*/