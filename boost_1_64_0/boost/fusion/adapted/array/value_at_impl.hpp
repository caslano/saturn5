/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<po_array_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : remove_extent<Seq>
        {};
    };
}}}

#endif

/* value_at_impl.hpp
/QiSCx+J5m+ePtzpjXQe7alQwyXGWci2sO1wRtsal9My0qDl07DXWBtfyibouaGOgtcO/0hlr/NBnYokXCpJVIAq3P+C7gMIdIgvzb18b+t3rU5rbnlnWcz6yBJCOvG4Bp5cXlEiXAw+dqhHXyq/XSvee4yG4THbyJe+5aflzQhPYZoiVuWHPWBHXACS4U3eEuqRy+uRbC9tik+xAU4AUp2XkQnGO5+tYpaChbf31rVJqmLxf6pUiNlRSBx7ld9HTIFVid97Sz+qcWiP0Ezw5a6XVMFIY1GBjTfZo+CkXj2IYlTyoDLhqdUvA8GKlLNMVWZSiJj7mfAWfVd2RgERUOYJIOajez/RzajBrieSyxCoeE9AGY7ix9KEhc4H3qfeqa3qA+XncpF/+htla9tDNNUjQ9pw4vNq2EwZK+1a2n9jea3eCWhZZK2JCJGK09r6JCOAgHhlGazcoDMAb9P8E5J6mGoCoVsZTb/I53Wow6KIvcM46EraSj18glDBPi6xjardzr/Kp5y9lW7LpDiteEMO5deRKPHorRFFvIAN0ejxfj1XGov75mpNVQ==
*/