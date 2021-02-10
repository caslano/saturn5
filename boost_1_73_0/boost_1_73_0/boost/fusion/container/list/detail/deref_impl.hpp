/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_07172005_0831)
#define FUSION_DEREF_IMPL_07172005_0831

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct deref_impl;

        template <>
        struct deref_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type value_type;

                typedef typename mpl::eval_if<
                    is_const<cons_type>
                  , add_reference<typename add_const<value_type>::type>
                  , add_reference<value_type> >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return i.cons.car;
                }
            };
        };
    }
}}

#endif



/* deref_impl.hpp
fxcznj6VGSs3xn3nPU7wv1BLAwQKAAAACAAtZ0pSWa8NwbsVAAASTgAAHQAJAGN1cmwtbWFzdGVyL2xpYi9hc3luLXRocmVhZC5jVVQFAAG2SCRg7Vz7c9vG8f+df8VZmcqkvhQl2amnNW23tETZnEikhqSceJoMBgSO5FUgwOKhR5v8793de+AAAhSVKJnpzFeZWOThHrt7u5993EFHB8/302AH7NEfh/534Ad+04irOPon99Lq3o7zM5P/wagf4fdjixyxfMjPTos9PuRn1qQhjlrlHX52nMcW+hFpw3+OcOSPDn6EFhiGI0+j9UMsFsuUNU9b7OSvf/0LO2Svjl+dtNmZGwoesEnKwxmPF232zqeWvy/d+/tOwj+0GU+ZG3TUVNOlSFgSzdM7N+YMPgfC42HCfeYmzOeJF4sZfBEhS5eczUXA2eno6utg+KnN7pbCW+IkD1HGkmWUBT5burecxdzj4lbOsXbjlEVzGA6T+yJJYcIsFVHYgbU5S3m8SnAOXN4Nkoi5t64I3Bks5KZsmabr5O3RkZfFAVB/5EdecuRp9jvLdGU4+QpErNwHFq1TlkYsS3ibYc82W0W+mONvEAg0rrNZIJJlO6cGlgr9oyhmCQ8CnAvGCZ5IsjmbKPG0sRtbA8UixV9J
*/