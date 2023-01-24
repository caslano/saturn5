/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_20060124_2129)
#define FUSION_VALUE_AT_IMPL_20060124_2129

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/config.hpp>

namespace boost { namespace fusion {
    
    struct zip_view_tag;

    namespace detail
    {
        template<typename N>
        struct poly_value_at
        {
            template<typename T>
            struct result;

            template<typename N1, typename Seq>
            struct result<poly_value_at<N1>(Seq)>
                : mpl::eval_if<is_same<Seq, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::value_at<typename remove_reference<Seq>::type, N> >
            {};

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename Seq>
            BOOST_FUSION_GPU_ENABLED
            typename result<poly_value_at(Seq)>::type
            operator()(Seq&&) const;
#endif
        };
    }
    
    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<zip_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename result_of::transform<
                    typename Sequence::sequences, 
                    detail::poly_value_at<N> >::type values;
                typedef typename result_of::as_vector<values>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
fzgfioDfkVzVvf+yvYH/AsKvkdVDi+5h/oOTv2SRzwBSioif2iworFw+pju6nwSGUPc7D8oftEf8VgVM17N+jjnJuXzkPTbFl5OyP94P4nMmy4JsZeoVfjJzWLdMvi1AhJOtoN7Y39lfsI1jXP1npO8u+gAeEmwaGth8J/j3ZNVm+Xu8A3JOmyIWZjQ8LV/5bPkavQ+84k374ck7uzJtoMZ5f2AcF727QSftlA+0yKjML/xw5lem28Fdl66+Ljrf9NnSu3TeD85zF7CQmtHL8wg873jWO/D0nEH5GnKH00W+VvGFO3jWOOuD5gd251AdhaKBLegMZ/rK6f+5P9QMIGVUh3zmB6F+3sdNPjO750xMnm9idhhdnZxdKnVF3MdvsId8UvzGBD96AfFQ6DdzPtt4gf04iUbf0yFYBXjEp+Wrni1fo/NINcjYRsf79Glbny6H58b7HMM8OWUmH3XXJlkX8geehJTfj172PPf/3MVbXd4f+osqxCyNbq5x+nAsc3/Ytz5gA1h0D/L3BxN3czzRlDx5MxGVYf6IRZoLrgmwu568l/PD0YlNPI+9NLcc8S8ofvKDzIsplFUDW4v+yOUj125uL3zZp+yH2SS/m/0Y5dsvYb6g8fD63EfufnFbP7Dk5PzxY4pMProAd2VQyU/m/ISOZzzPgcrQlt4JWaO8vsC7ZV4QXQYguO3fe16gJ3fQ60R+jfl/8Aic
*/