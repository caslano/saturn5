/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_27122005_1044)
#define BOOST_FUSION_CATEGORY_OF_IMPL_27122005_1044

#include <boost/fusion/support/config.hpp>
#include <boost/config/no_tr1/utility.hpp>

namespace boost { namespace fusion { 

    struct boost_array_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<boost_array_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
p9CoilFPRhMNRnp2DYz/vcS1Q3qylQyx67x4n303UvQsKdSBkDGmlPsmkKg7Ei2zmbm5nxDN0U9aL2JB+uBzlsx7qnhezmk8JFvpoaH9HPno+yuCKwsKQ7suP45jNbKw2hSqY/bdMqe8QgZqTLse+HpW/djYtfSfcVQIkeD43AYPgI5t61ITTZjpkul6LMOinsa478x842PniZM2GdTg9HUFqCZwkGMo0uyNnGxJqmCWK84DZeFvsTxRXO+u7OiBdzITjebkoNAZ+8+glELilUDvBhSF6Z1Nw20P5FLRWljOFq1RLIp414j0nUspoGrEITC7QX1QRU5gnxCQBQkl0TTB8JdbupuUPr/T6Rc2P5jJ1CH2eNfEmDzQ7UcF67ASk0NAKPJgugW6VsB7FvQJlh9606gETM3Hkr25FBta1QTeSsCj2nfkiC/WDIsYJAUVBNXgTbSNqcTfVnf8LmTheEFOMGnb9aRlKQUi88c5sfh/9BlzqCxxTM7DPnQrFwN5Urfq34Pq5RoltTOpDYJM5t9NMdQLPFSfaGdr3Bt8Z6UpxvHpyL5ukc+nKw==
*/