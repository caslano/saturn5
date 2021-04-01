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
xYzuxPBxYrdUMwvkdEebJWPpt6SAf5WhgY0iK19lqQl72C3AyxM+/iSKS0O0KAr9dp61mawwaIXE203/Wl9JD+iS6ELKMtsvxge/j0+cx47iGVz5vQvhD5hUUBvabsVppllErsy7qEF6XvyrxCveGkMbPdhQeoFqIibzH2Yp5HetLklqt/plIMlMcr2eV6plJG5cjx0ZpyNsGce1gUuNdfh4brAgK+V5z7+jP1xwVZ+VqxgQ+lzoS8GDjJXpqHllwrKtAn6EPUVUpQI+T+87gb4x+wP3u5SEKagPr88UWaNy50ndHmuBWZuBKfCd6WA5lgoCdSilcDuaxdcV0jpLxZS3j6cWP6wANp6xsQBl7tKaoAVgGq5gdtthN9npFuzrOVCjMGu/ryXoSWKPm0LWAZECJaGkFisEc15TwcBXjMLDgKTA8U5Q7tuqSPfowwUb8DMvOs/LIZbWwpxCKsqFQD/8Q/fuVTFq9x5gF0AwHmbPDKjJndATpicjVKd0A9m3n5ioTpL0uCss4MJr3Er6UfBtFvFGHcPA15TSkbL2/3jfO+k5qOCcfT4Lkw==
*/