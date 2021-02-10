/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : access::struct_member<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* value_of_impl.hpp
HeM6AX52xHxtugaxoFma4DJt+oij9DzcW2clBnXq3MLhUDcK8TFhR8THhLdMKcUbOSK4KVld/B9QSwMECgAAAAgALWdKUht6WYvhAgAAEgYAACgACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy90ZW1wbGF0ZS4zVVQFAAG2SCRgrVNdb5swFH3PrzhiL+3ESLtO6j6qaTShK2sKEZB10TIhAk7xRDDCph9Sf/yuDV3VbtL6MEfE9uXec66PD87Kwsv/NkaOhsM/R2qelAbN90XzVvxkufp7QZreof9R4YrmZ1CN8VB1l+7iWVV32DFV6cB1pNdp+gy6lW5S/4118SrVS4r0lUP9RDS3Lb8sFXYmu9h/9+4tXuH13us9G9Os5qxCrFi9Zu2ljaPCRD6V2c2NI9lHG0whq5xHgEnJJaTYqOusZaB1xXNWS1YgkyiYzFu+pg2voUqGDa8YJuF86QefbVyXPC8HnFvRQZaiqwqU2RVDy3LGr3qYJmsVxIYQCL/gUhFmp7ioHaJnUKzdygFGN5FVUiC7yniVrYkuUyiVauT78Tjv2opOMi5ELsf5vRROqbZPTrWkbrbZLUSjoAQ6yWzofBtbUfCNnkkiCjbduuKytB/aIsK6GIsWklXVAEelnMn+
*/