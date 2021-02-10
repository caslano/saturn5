/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_20061213_2207)
#define FUSION_CONVERT_IMPL_20061213_2207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/convert.hpp>
#include <boost/fusion/container/deque/deque.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct as_deque;
    }

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<deque_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef result_of::as_deque<Sequence> gen;
                typedef typename gen::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq)
#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
                        , fusion::end(seq)
#endif
                    );
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
cQ/ZoY/jhThTipgceMU0RtiRo/dQNvGP+fO9p5kjwNOV7ishoNi6l/3zfQqB39pgFG8O74b0ownklZ1deoF3wjMz76SetLimPe3DvTUq3kZxRPFQa13ipERkoS16TOsrKkYNkMRZTrd9kd/GdF32coNDK28PcGXBHZO4WYVhxSQ05qhZqLAuTtKzTjjJKa8snFCLA/sRR7N8V9Zg8d/ScQWzGbahYmjN5ZJDwbg2BWqYPcrGKf8miQAsW/tATwXl8UTJz7Uu6MgCSMUicx97xYFuOzEIoBWzQijAvTkW3BkHhBQGhN85eioHOjdQ/Dd7DtGqHB1IIN5yhDI4qfuRWse2GqjpxTXYrbUk9qQ0xNKJgRJsPSk03moiDPXJFcc7tCwdnCT1Wm0zPnHl0znu1YdbjVV38vesuT0rnXCrdFYY6tZLzvNK4g2U6ez/e0+ItXrk57Vtpse9/fLc7Ilxl/qqwh/4tfLE/H0zBd7O+ARtfXj+vsk++/Cgu8n0+tenWKiTttVMdbd/F8Zy3ZabG2srn/ct9CpptjX8hTk8DwYqkqQw8NfzYeD2TGHgr2fB4Lt4jxiJ0k2myxwrm/z6LmsIW22u6e7vQ+P01tUAaYLO+ak4h62np9pvNRkN+++ZSzE/yp4CuzUIzoge
*/