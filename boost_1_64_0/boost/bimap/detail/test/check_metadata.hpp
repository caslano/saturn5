// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BIMAP_DETAIL_CHECK_METADATA_HPP
#define BOOST_BIMAP_DETAIL_CHECK_METADATA_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/cat.hpp>


// Easier way to call BOOST_MPL_ASSERT_MSG in class scope
/*===========================================================================*/
#define BOOST_BIMAP_MPL_ASSERT_MSG_ACS(p1,p2,p3)                              \
                                                                              \
    struct p2 {};                                                             \
    BOOST_MPL_ASSERT_MSG(p1,p2,p3);                                           \
/*===========================================================================*/


// Build a descriptive name.
/*===========================================================================*/
#define BOOST_BIMAP_WRONG_METADATA_MESSAGE(                                   \
                                                                              \
        P_CLASS,                                                              \
        P_NAME,                                                               \
        P_CORRECT_TYPE                                                        \
                                                                              \
    )                                                                         \
                                                                              \
    BOOST_PP_CAT                                                              \
    (                                                                         \
        WRONG_METADATA__,                                                     \
        BOOST_PP_CAT                                                          \
        (                                                                     \
            P_CLASS,                                                          \
            BOOST_PP_CAT                                                      \
            (                                                                 \
                __AT__,                                                       \
                BOOST_PP_CAT                                                  \
                (                                                             \
                    P_NAME,                                                   \
                    BOOST_PP_CAT                                              \
                    (                                                         \
                        __IS_DIFERENT_TO__,                                   \
                        P_CORRECT_TYPE                                        \
                    )                                                         \
                )                                                             \
            )                                                                 \
        )                                                                     \
    )
/*===========================================================================*/


// Check if the metadata have the correct type, and if not inform
// it with a useful compile time message.
/*===========================================================================*/
#define BOOST_BIMAP_CHECK_METADATA(                                           \
                                                                              \
        P_CLASS,                                                              \
        P_NAME,                                                               \
        P_CORRECT_TYPE                                                        \
                                                                              \
    )                                                                         \
                                                                              \
    BOOST_BIMAP_MPL_ASSERT_MSG_ACS                                            \
    (                                                                         \
        (                                                                     \
            ::boost::is_same                                                  \
            <                                                                 \
                P_CLASS::P_NAME,                                              \
                P_CORRECT_TYPE                                                \
                                                                              \
            >::value                                                          \
        ),                                                                    \
        BOOST_BIMAP_WRONG_METADATA_MESSAGE                                    \
        (                                                                     \
            P_CLASS,                                                          \
            P_NAME,                                                           \
            P_CORRECT_TYPE                                                    \
        ),                                                                    \
        (P_CLASS::P_NAME,P_CORRECT_TYPE)                                      \
    )
/*===========================================================================*/


// Just for autodocumment the test code
/*===========================================================================*/
#define BOOST_BIMAP_TEST_STATIC_FUNCTION(NAME)                                \
    namespace NAME
/*===========================================================================*/


// Just for autodocument the test code
/*===========================================================================*/
#define BOOST_BIMAP_CALL_TEST_STATIC_FUNCTION(NAME)
/*===========================================================================*/



#endif // BOOST_BIMAP_DETAIL_CHECK_METADATA_HPP


/* check_metadata.hpp
wTWFv8my1bHsC00GjHNK+J5+u1+v+50vDPzuNHpMv76Omo32zPKCZsOMWf6goFmBZ1YQNMv3zE4LmnX1zAYGzdp4ZgOCZqmeWf+gWaeZxiw/aJbhmZk4J3tmJs4+Y9bXxPmzGcbMxPmPnpmJ81uemYnza54ZcVZZPLoPzD4/c43uw9Hz61Q2VgN5smq+AfKtgLn5VjBy4QaLubb3KldOzRYs0XttMWbS7ooZ7YmuD6UdVXfdIO0jZtRd60w9woyyTi7auslo6yOjraeMvm5ylawj3PzM1M8OvXz3wJbt3/jaPWc+uTX6+sWDsq5N2379PqyHfQPj3nKlEWwubKPzsG3hCl03thrm6PxdJ50f7qzzw13hDDegr4R+/TrYDa6Hp8InYHf4U9gbHoZ94N9hX9jFv04IVsP+cDkcAD+HA/3uYAFsGse8DewCB8Me8Aw4AQ6FNfAseDUcBh+Aw+HDcAR8Ap4NM+MD+q7Qry+B58AJsBhuhaPhNnge/C0cA9+AJfAdeD7slcCcCzwNyjwlnARvh5Pht+AUeGoidQX2hBfDPnAGPA/OhHXwEijngZY1cjaiGJtnfDswtvxj9DtRjNEyHirjhjIeNz02RhW7YtcJuU5C/59Nv/ms7T8x8v/bZBOG9v83qZz8r/zvX7gHLvfLdLzI9P+5N0GU1i4s9Uehxgnur8MeK28MQP0UmDGAblPQs8rE66fiX78Li437fLOvJlfc/zzUfb7Xj28j9r90dQ+Z+u8p8Tm9o6wcDjkvuKnZn1hhvvmHTFX5YdpfKZEw94vbHOwpSfPd+rTYNTJ9lQtEfxXrXJo4fFPz/u3gBPchN8sOqE+zWHeECrJRmtrpXo7tTsRreKrE9/TULfIN4cr3w15+k8/oJZ/FbJ/59pC8FLMDtlm+tyfk9IBZ8ExiU+ZD4s06beKPHq7EbdXF4WWu2y2jlbn6GWTK8F7Rdw0tQ0fL3LjvY8r0W6Lv5R5rGfrLYeo07StoX2ynhLE2pAzTtAx/LXb9nB4qN7sC/8nTtFwpuwQtO6+8/rmy2hmhrHbb5eJEL5dDskYx+jfYI/LN9nHu0heyp/9q38KhT2Z+u/mZg6PtLYm2p+L4vzlP1F6d493rclDyQ59vfTdl6NqmL6w1aV1hPkQ5/WAB7A+L4HA4HY6A5TC4Fu0cXXtWBB+Ao+BTsBg+C0fD5+F58C04Bn4Kx8ImxKME9obj4Cg4HE6CF8CLdc3ZLDgJzoOTYQ28CK7SNWsbdM3a93TN2pNwGnwRlsJdcDrcA2dA+QZ3gs+OJ+slFbVe8+MU3HWHaZofLTQfMjQfMjUfsuFy/Vb/hn6ji4xs+IiuJfpA/R3WNUOOfps302/zzvpt3l+/zYfAHrAe96whMd+hk/Ss2SI9HzZ4NuwEPfu1m57rqt+o5uxW/VbVM1ahdQYq89Qhc8qr+I7dFPuWjV2xK3bFrtgVu2LXSb5ORv+fQxVOSP8/i/mIjBT/AKNL32NhWRkyM/ySk2RsHLslHbHb6LdbUj5jnv+eNWI+FnPn235zolNaM4+xRxlLaGWNJTzn8sdat9wDNQd/VReYfiXj7bMk1OBtI/UT+a5WPykqOwLfom+DfRJpNfNMYu+/ebXYn8r3qquy448sF6Wx3TdrcHZgrS9yOrZ46UAIRDB/nGhpUPc9tQ8bGt+HNb4dT0B8K+M0nip7oguqHrcHTHwlx2WyA6to8VX3nZxoaymKPTcie76efGrDvTOoA8lNmiHCNT45IcGTHUaf+rjkqJv06TxNQdg8jcrc0HSPiI+c7rwLTbr1uYmaZtwePc3qxsg5yZTxgmOXVXSs6Qo+R9sSAoEs1/ML6jRdVWHpCjxPlGo=
*/