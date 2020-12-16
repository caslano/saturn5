/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010-2011 Christopher Schmidt
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ADT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/less.hpp>

#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_view_impl.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>
#include <boost/fusion/adapted/struct/detail/is_sequence_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/category_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/size_impl.hpp>
#include <boost/fusion/adapted/struct/detail/begin_impl.hpp>
#include <boost/fusion/adapted/struct/detail/end_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/deref_impl.hpp>
#include <boost/fusion/adapted/adt/detail/extension.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base_attr_filler.hpp>

#define BOOST_FUSION_ADAPT_ADT_C(                                               \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, IS_VIEW, I, ATTRIBUTE)                       \
        BOOST_FUSION_ADAPT_ADT_C_BASE(                                          \
            TEMPLATE_PARAMS_SEQ,                                                \
            NAME_SEQ,                                                           \
            I,                                                                  \
            BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),   \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR(ATTRIBUTE),                      \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE),                 \
            BOOST_PP_LESS(                                                      \
                BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE), 4))         \

#define BOOST_FUSION_ADAPT_TPL_ADT(TEMPLATE_PARAMS_SEQ, NAME_SEQ , ATTRIBUTES)  \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        struct_tag,                                                             \
        0,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#define BOOST_FUSION_ADAPT_ADT(NAME, ATTRIBUTES)                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        struct_tag,                                                             \
        0,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#define BOOST_FUSION_ADAPT_ADT_AS_VIEW(NAME, ATTRIBUTES)                        \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        struct_tag,                                                             \
        1,                                                                      \
        BOOST_PP_CAT(BOOST_FUSION_ADAPT_ADT_FILLER_0(0,0,0,0)ATTRIBUTES,_END),  \
        BOOST_FUSION_ADAPT_ADT_C)

#endif

/* adapt_adt.hpp
qU6p0+qMOqvOqfPqgrqoLql/1WV1RV1V/6lr6rq6oW6qW+q2uqPuqnvqvnqgHqpH6rF6op6qZ+q5eqFeqlfqtXqj3qp36j0Lv9BSK6210VY77XXQMTqOjqvj6fg6gf5AJ9SJ9If6I51YJ9Ef66T6E/2p/kx/rr/QX+r/6a/01/ob/a1Opr/T3+sf9I/6J51cp9ApdSodq1PrNDqtTqd/1ul1Bp1RZ9KZdRadVWfT2XUOnVPn0rl1Hp1X59P5dQFdUBfShXURXVQX08V1CV1Sl9KldRldVpfT5XUF/YuuqCvpyrqKrqp/1dV0dV1D19S1dG1dR9fV9XR93UA31I30b7qxbqKb6ma6uW6hW+pWurVuo9vqdrq97qA76k66s+6iu+puurvuoXvqXrq37qN/1311P91fD9AD9SA9WP+hh+ihepgerkfokXqUHq3H6LF6nB6vJ+iJepKerKfoqXqa/lNP1zP0TD1Lz9Zz9Fw9T8/XC/RCvUgv1kv0Uv2XXqaX67/1Cr1Sr9L/6NV6jV6r1+n1eoPeqDfpzXqL3qq36e16h96pd+ndeo/eq/fp/fqAPqgP6cP6iD6qj+nj+oQ+qU/p0/qMPqvP6fP6gr6oL+l/9WV9RV/V/+lr+rq+oW/qW/q2vqPv6nv6vn6gH+pH+rF+op/qZ/q5fqFf6lf6tX6j3+p3+j3bPmGkUUYbY6xxxptgYkwcE9fEM/FNAvOBSWgSmQ/NRyaxSWI+NknNJ+ZT85n53HxhvjT/M1+Zr8035luTzHxnvjc/mB/NTya5SWFSmlQm1qQ2aUxak878bNKbDCajyWQymywmq8lmspscJqfJZXKbPCavyWfymwKmoClkCpsipqgpZoqbEqakKWVKmzKmrClnypsK5hdT0VQylU0VU9X8aqqZ6qaGqWlqmdqmjqlr6pn6poFpaBqZ30xj08Q0Nc1Mc9PCtDStTGvTxrQ17Ux708F0NJ1MZ9PFdDXdTHfTw/Q0vUxv08f8bvqafqa/GWAGmkFmsPnDDDFDzTAz3IwwI80oM9qMMWPNODPeTDATzSQz2UwxU80086eZbmaYmWaWmW3mmLlmnplvFpiFZpFZbJaYpeYvs8wsN3+bFWalWWX+MavNGrPWrDPrzQaz0Wwym80Ws9VsM9vNDrPT7DK7zR6z1+wz+80Bc9AcMofNEXPUHDPHzQlz0pwyp80Zc9acM+fNBXPRXDL/msvmirlq/jPXzHVzw9w0t8xtc8fcNffMffPAPDSPzGPzxDw1z8xz88K8NK/Ma/PGvDXvzHs2/cJKq6y2xlrrrLfBxtg4Nq6NZ+PbBPYDm9Amsh/aj2xim8R+bJPaT+yn9jP7uf3Cfmn/Z7+yX9tv7Lc2mf3Ofm9/sD/an2xym8KmtKlsrE1t09i0Np392aa3GWxGm8lmtllsVpvNZrc5bE6by+a2eWxem8/mtwVsQVvIFrZFbFFbzBa3JWxJW8qWtmVsWVvOlrcV7C+2oq1kK9sqtqr91Vaz1W0NW9PWsrVtHVvX1rP1bQPb0Dayv9nGtoltapvZ5raFbWlb2da2jW1r29n2toPtaDvZzraL7Wq72e62h+1pe9neto/93fa1/Wx/O8AOtIPsYPuHHWKH2mF2uB1hR9pRdrQdY8facXa8nWAn2kl2sp1ip9pp9k873c6wM+0sO9vOsXPtPDvfLrAL7SK72C6xS+1fdpldbv+2K+xKu8r+Y1fbNXatXWfX2w12o91kN9stdqvdZrfbHXan3WV32z12r91n99sD9qA9ZA/bI/aoPWaP2xP2pD1lT9sz9qw9Z8/bC/aivWT/tZftFXvV/mev2ev2hr1pb9nb9o69a+/Z+/aBfWgf2cc=
*/