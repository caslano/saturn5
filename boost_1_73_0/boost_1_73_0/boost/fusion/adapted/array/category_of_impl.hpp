/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_CATEGORY_OF_IMPL_HPP

namespace boost { namespace fusion
{
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename>
        struct category_of_impl;

        template<>
        struct category_of_impl<po_array_tag>
        {
            template<typename Seq>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9URlRQX05PX09QVElPTlMuM1VUBQABtkgkYK1VbXPiNhD+7l+xQ78A4zN5ueklvfSmPgKNJ5yh2Bylw4zH2DJWayRXEhDa5L93JZskJM0cH84MliztPrv76FnbmTeg/d0uy9Fw8M0rMv8ILxz3TiPB/ySJ+n+HKLqH6oeOcxyPCNWBJ6/7qAVHed1D03hFdawrPY+iI8LNdZL61tHO80hPcaXyrP27vNwJuswVNLstOL28vIB3cHZy+qMN1zGjpIBAEbYgYmnDVWpWfsnjuztHkk82EAVx4RwAhjmVIHmmtrEggPOCJoRJkkIsISUyEXSBD5SByglktCDQHY5mnv+rDducJnmNs+NrkDlfFynk8YaAIAmhmwqmjIUCniEC4qdUKsRcK8qZg+EJKCJWsobRScSF5BBvYlrECwwXK8iVKuVPnU6yFgVW0kl5IjvJngonV6sXVc0wm1W8A14qUBzWktig7W1Y8ZRmekSKcLFcLwoqc/spLQzI0g4XIElR1HDoSomsSiAQ1GzZ2hJKzJ4qPUjOpI62zfnqwBBprYGytWAYDmlBu5Qj8TasWUqEsTdE7KPULBvKv3FkT7mnwBlmBQ03
*/