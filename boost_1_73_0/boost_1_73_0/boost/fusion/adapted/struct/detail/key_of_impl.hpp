/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_KEY_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : extension::struct_assoc_key<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* key_of_impl.hpp
9Z8rBb6X6i385uI74JLd0+/77W+bI/o++QG9fvv2Z/RX9Ob6zfUlSleP2/oe8WP9+KHe/3aJflk3v/n3ZvXly6tD/a9LVB/R6v5V80Fisz2gw+7j8fNqXyN4f7+9qx8P9RqtDmhdH+722w/wh+0jOm5q9HF7X6OEFUuaTy7R5832bgOf8fvuGR02u+f7NdqsPtVoX9/V20/tRzyt9ke0+wg0fPZ6ezjC5z0ft7vHVyC6Rsd6/3CAj1DCV/eHHVp9Wm3vVx9AzOqINsfj0+EfV1d3z/t7GPnVend3uLrrpv5qc3w4zWIJI3hY/Y52T0d03KHnQ32J1HOX6GG33n5Ur7AU8Mun5w/328Pm8utQQNDj+mq3R4f6/h4+CrBtfWiHXCN+WplL9RR6gtFuj+rlsHs8KEmfN7uH3oOwhPAhH5/3jyAGlgCeWe9ggS/R8+O63jfPNpPuJJxWs1lax5Z8Hesa7R5hJOhbzBHl36IPq8P2cIkWVExZJdAClyXOxRKxMcL5Ej7rhuYp7PcWJO1R/eVpXx9A8h5tH57ut/W6Efjn/YBAvoFBr9GH+vi5rh/RbPW/upnZ6qFZwUT9IoP5HF4dvxwvLh5Wj3KGc47+6Vfos05cIJRUZUbzMZM4EXROOEtuiHj1YxRRFAnL
*/