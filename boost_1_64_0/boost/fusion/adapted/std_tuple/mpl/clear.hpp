/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0940)
#define BOOST_FUSION_CLEAR_10172012_0940

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/std_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail
{
  template <typename Tag>
  struct clear;

  template <>
  struct clear<std_tuple_tag> : mpl::identity<std::tuple<> > {};

}}}

#endif

/* clear.hpp
xkr8sKwukS4jGfI79LMzKPBagif3ybXV+8ZGtCPf6hpfkF3NmWrkSuISKkkWXB6boczMDW69QIwn7OMyU9oiiP/mkHBIxcMqzMXatXZkhGhGVNa0e3O5QS/NuKb/HEWg88DatGDTnvrGMr5TDlvG/w3pxodSaOdG26BjFrLfdnX5tcZPssZ1c2sfsUGmRX8XWx3qZBgtlG/rsnyOg/WMgd+T0RlwaF/wmfP2sw+iH4tGTtAn3OvzU1x8BBwRNa3W1oQiAgZInlm2PvLe+ZEYe4gI/NgzTS12wnSXysEFwNdaJY4ZjK7+Ut8tILNK4U9M8/B5ZCNfI3eAPfsQ5isVgcT5KPYlQ6kEjys6ApWIH3afK5GreWrM/1AmNs6UhKRKUCEVwLitPKGMU5MHvWKGYiYJ9JlGP0H+V8qg11IxoJvN25PHLpev7QcAaJNgqHEg/gJhZWmSPmLBpc3k4npIB/nXJe1ZrzWs69yrPMeYPncmg1MFFGtVz+g8nXvBXDcEd0K7c7BhEmO5AGmn9rMHqs/K687cQz+vvV/2MESMqYZ+zkD1DZIxpAAJwA==
*/