/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_LIST_FORWARD_10262014_0528
#define FUSION_LIST_FORWARD_10262014_0528

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if  defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   undef BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
#   define BOOST_FUSION_HAS_VARIADIC_LIST
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_LIST)
# include <boost/fusion/container/list/detail/cpp03/list_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    struct void_;

    template <typename ...T>
    struct list;
}}

#endif
#endif

/* list_fwd.hpp
BhfkUYYOAwVUbmSy2BaoM+Th2k0sVJ+smm85ULaeyA3f2PKDNuF6imhxzh77dileatZm7u5VsodXWjKOHgijb5ZoNGyQS618vBuKtDdsJezPbNWuNOvWn6qAtFu7n7Xl0spThhPFiQOaKvCn8DYSGO1LRz5sK1KWaowGt6YN5HAT9msidrb3xB1yyMNsg6+p3MeAvvhuj4WHJsE1uBiMwZk4R1OAARZx6o2uq66SEPtxOR1yhXFJxbdGH49q82AbtjiPLsOC72ijRBpva1CpOMczYT8YpCt4GtCdH2MK38I4vI4DlaPZJa86jPWzKmrCeoAlbHfAuV6Vsx4qOjx0EA06JZxIl+JchyLrKGVDYRkEMtcv/LAljNBtWFmaZIWFMlh2VKsM2lC6JIdOTdBnx9Sj5nJtoRh5AMsZ1rvjTYF4ZTMa7Hw78HU9+LVRm1xhh3o7Q5UKzA+dyPm2gHkXjxjv/ZZUL6ZXXLsz0VXhsBJ1g2WmeKtqeP3wHeoY+H0q9j838X3jlaKZt3eT+DYP/mwU5FS6TrUQPv2IwVs1kOAt1qkOZ5I2uE9A35qBaveZzNZYjWL1E94mo8g8fLDLQK0X4sGZMGCRVNG/MP6IHk1Z0F0guYF1sOUC1iJxCdpbP72NnAGDKJQuIGpu
*/