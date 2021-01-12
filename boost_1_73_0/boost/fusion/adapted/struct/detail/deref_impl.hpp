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
efcSqxu1Q4HldU1jHa8zTZ+TJWmnabBIzCwsM6yLxUwzzISHtZOEtS7h24yhnYTvXQlfx/gLnUmLOCcIAee/2PA+osSLSjB8R7F3LOncZz1Wpc6Kgu9qO0g+kTj9+ne2icF+Tpcalvxdiyf88CrYCvvzPwqrr8ZNZ0Rfep21VMzO8HTAhYXIzbSMMR4/91HF6Pgx6F7F8LoLvYh5SpM23KWr6Zq9D31OXHmUeG7IfNs4O9at
*/