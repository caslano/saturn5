/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957)
#define BOOST_FUSION_TRANSFORM_VIEW_ITERATOR_20070127_0957

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion {

    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<transform_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };

        template<>
        struct equal_to_impl<transform_view_iterator2_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : result_of::equal_to<typename It1::first1_type, typename It2::first1_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
t75yHNauJd2oDIl/kJQOWWGXv3sd19P3oZ14cyJrEEjUFSGAmWaO9WZwhxUS1urcefArJ/S5PezRtzdrref6v1BLAwQKAAAACAAtZ0pSTpwTIBoLAAD9IAAAGAAJAGN1cmwtbWFzdGVyL2xpYi9ob3N0aXAuaFVUBQABtkgkYL1abXPbxhH+zl+xlWYikUORkutR7DjJlJFom41NqiKVjDuZwRyBA3EWgENxB9Js0/727u4B4ItISnbcyrZIHu72fZ/dPfpYhWkgQ3jb7133b72ru9t33tvReDK48d42jvGJSuXuh93W1/tpQAse/fH4n4c/+MonbnL9Ufp2927P+x3cHzz1G74+xqQLqyO/e014/MjvcMpHvJLL9/Te8x5j9BvJRr+6dPI3j97iCh6jk1c6W+ZqFlk4vWrCxcuXL+AMnp0/u2jDtUiVjGFsZTqV+awN3we88pdIfPrUMfLHNkgLIu6UpCaRMmB0aBcil4DvY+XL1MgAhIFAGj9XU/ygUrCRhFDFEq5GNx8GwzdtWETKj4jIUhdgIl3EAURiLiGXvlRzRyMTuQUd4nEkHihjkWBhlU47yFuClXliiAaxF7HRIOZCxWKKjISFyNrMfNft+kUeo/TdQPum61fqdyKb1Jp8QCESsQSdWbAa
*/