/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/fusion/container/list/nil.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    struct nil_;

    template <typename Car, typename Cdr>
    struct cons;

    namespace extension
    {
        template <typename Tag>
        struct empty_impl;

        template <>
        struct empty_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
                : boost::is_convertible<Sequence, nil_>
            {};
        };
    }
}}

#endif

/* empty_impl.hpp
GlyTJEggnaViCi347J/9zAguz5LD59Msis/kQz4WPosIkjBLLU1iiaZf2CcG46lNpZQUlQnBbsPGKo68d4nW7im5lvsYkAwIAbCqHpcSksWeecymJ+o2eSbo3pjBO/bGTEA1gDjtd8MM+111k8Mu164KmSJM5YYzoySBZThz3ZDiy2eVCGmS7Zt61pPqe5GMkPD/qq1DeAHMurOIjxCF/DcqspByt87M8cJOIvm/bS2oyFCWIKU3kizYdnKQksBX4DVfN6O5NDotn+Vo5T0Sx0IPVOQTCzesT4GnDfw2NphzEE9Df6h2UX2FsghkK67C58RVRTsg1yNy04XQNG0SnyKOgGFRRccHBp2sEp7BjVIGoHvEbeWLobZaH8F+RSyBA5FipepQd74uelOKyozwCEu/LpAdAetDF33nnMQ95UQq3GNv+OXR3ZDhyMr0cXkUadI4UYQpP/gIJ2hGPk4pclmTXuTKBlUd3QtsgLkbKo0KWAanDEdR+YSNUB8cG6nR4xFazWFhIeAG7+81GLmnH+BWmaihK6dYjaJAdolXRxEC+1D+qQhtqblwbw==
*/