/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_VALUE_AT_IMPL_08122006_0756)
#define BOOST_FUSION_DEQUE_VALUE_AT_IMPL_08122006_0756

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace fusion
{
    struct deque_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template<>
        struct value_at_impl<deque_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::next_up next_up;
                typedef typename Sequence::next_down next_down;
                BOOST_MPL_ASSERT_RELATION(next_down::value, !=, next_up::value);

                static int const offset = next_down::value + 1;
                typedef mpl::int_<(N::value + offset)> adjusted_index;
                typedef typename
                    detail::keyed_element_value_at<Sequence, adjusted_index>::type
                type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
TB64bKA89CtFPCp39HtUXDtKlPcNrSbJB9G305uJxxXY48J2894EamRSaJJJcva5Z0qDIBAuPkixaLWlshEiB+QkXPf20+VRyjIQLu4QKwfQ3Eu0r+kTyTaKekSEQ4r6nknURDGVU71WS8zV2OqF7WWEGdAJvbJuK81IUEGyJoVDJ+55u02peyh4Guiw5dXt0OA6oDIQFk6+QBgYQe73o7O5/Ac0ghx2WU/w5+mSKt/p1tLyijGtCn9ux8N7yMqz9FA1F7v8p4IQPJSr50LPwW11r0ad6jdEzcqaneGy6//JXl0jxPKNqZzGNLZKLPsSSIAp4IJelQwciGnJ6Kg7poY2AmjkY2kwG9bvXuWroEOGys6Q+asgyG4bHROSjodKKU86P+m8BKlU4rya4N4WSBldJ/ukCVf0p5aUrQcAL/iAZarVFsqg98nJ8sB/T8YABRexI6ctveJs5Xz85PxHxdF21IicU+yJVfknNwthvdH5OuO3e+KPn93VaXFT+luSM1zDyns1P5s2aIMYSQMMrjYjI+V+nrrl24bCX7A9oUwWTy478yDYIdUYUQ==
*/