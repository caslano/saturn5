/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_DEREF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
        {
           typedef typename
               access::struct_member<
                   typename remove_const<typename It::seq_type>::type
                 , It::index::value
               >::template apply<typename It::seq_type>
           impl;

           typedef typename impl::type type;

           BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
           static type
           call(It const& it)
           {
               return impl::call(*it.seq);
           }
        };
    };
}}}

#endif

/* deref_impl.hpp
MzSZPhQqu8mqLJQrqw6urPcyHUVzWiAhWlxLFKLwMGUKg0mMy2RmT8pw7Hf8sgR19mXOccy6G7rH72cOwpgDSpWscLB4qW4mOFU4wNHZxInwqvihqcxBFnOQihwMlxykMge4ITpxt8lBOHOQGsxBAB4s4dMKczA/kIP5yMEW5qClykEic5DMHFD+7QNCu8oxm9zLnJaMcQE8FhPNmInEYCa+XEJMzA1kguY91czEy+pcMpaZiGcmGF8cmHBWTFhO9GOZD6BjHN5l8hHBfMQG83HFEkX6qlj6drH0VaH0nVrE0lcVyOsW5PUw83rYhgmnSrmiqmDJW7k4cGwco8zUqJ6Ji3gcoC97dJFeJ+jhpkVWq1kd4ZIl51slOyyyOtkSmgtkyQqr5NGFlkBaAv73Qi6pJDGqWmgpj6Wc3y5ktsk6LJYvKpl1XuQXZWadmdajfH40k8cnMZo8uVBOzMT8Fv4emV7WDScFiAPyxkKCB3me3xAj480LYSWCHpyYO09MDDY8jRMDGNeD5qVz9uHm96w90Zpx0b3H/UZH+K/dvRR5VrqPpg6FfPXwNY+vuXzN4Wv2PnOK4SyLcZbdBJMM/V6cZOB+kIKZQONbeP8eAVjeCNSjTG4v/1o9b736s0AX6rsxk6P9zBA6b70bJxevJSgu1O9+rrpQf/eV6kL96esNTS7iKnhyUa4FQVeVy8nFqQX1THeDJxcbFqjr
*/