/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_STRICTEST_TRAVERSAL_20060123_2101)
#define FUSION_STRICTEST_TRAVERSAL_20060123_2101

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;

    namespace detail
    {
        template<typename Tag1, typename Tag2,
            bool Tag1Stricter = boost::is_convertible<Tag2,Tag1>::value>
        struct stricter_traversal
        {
            typedef Tag1 type;
        };

        template<typename Tag1, typename Tag2>
        struct stricter_traversal<Tag1,Tag2,false>
        {
            typedef Tag2 type;
        };

        struct strictest_traversal_impl
        {
            template<typename Sig>
            struct result;

            template<typename StrictestSoFar, typename Next>
            struct result<strictest_traversal_impl(StrictestSoFar, Next)>
            {
                typedef typename remove_reference<Next>::type next_value;
                typedef typename remove_reference<StrictestSoFar>::type strictest_so_far;

                typedef strictest_so_far tag1;
                typedef typename traits::category_of<next_value>::type tag2;

                typedef typename stricter_traversal<tag1,tag2>::type type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename StrictestSoFar, typename Next>
            BOOST_FUSION_GPU_ENABLED
            typename result<strictest_traversal_impl(StrictestSoFar, Next)>::type
            operator()(StrictestSoFar&&, Next&&) const;
#endif
        };

        template<typename Sequence>
        struct strictest_traversal
            : result_of::fold<
            Sequence, fusion::random_access_traversal_tag,
            strictest_traversal_impl>
        {};

    }
}}

#endif

/* strictest_traversal.hpp
say0sTWfEby5cT/f4GQnCwdGM8AkTwP01qeckwQlgJWxa+JZxAUnLvb90W3KPk0pdcYQ8y4g42svxZuBj5A9j+33vb43x4qYH+vD6tt8p03+3i2++wZ/9/YacCwRdMr26KVKLRP1yjvgJsvTEtY4vkS1GPvlFV5Kdl9XWu+mL6kCKLksIXOc2eHpyUn7sM/u+5ZihIqUvm44MyLHi6Gx5onPP9bbwjktFr4Q+Gqkr90nf530RZ2lVsCYw4Hqb9N8ucyU5n+JyLT7RAlEpz2WkCoEJFuoUL9K1XvaKcDiQRXXrsHN4qdhN3h/bZ4/2HhmN38ozJwwenZXqzBtjraHCCLFiaEHIUj0SgfGVaPt1zE4rsgQZjjJftRIc0wU2tsGLme9WeLzgH0aRsIDEfGUfd7dqtNOr0bPOv12cHLwtv36bT/YdSlbLV2jGw0w4iLYWpLmBVcaNBlmiDU08+AupAoja7JegZENyadzX6AAk+U6fXjUwctuyvFB6lCVZOvM3zmGVVe56hoXrbDGQILgGCbIzMfImMfjGzOFreBQK5/IoZ3tEFkKBGQcY3KTfMu2wPyL41s5zzqFl691PLFuj0TFGP+RfTg4igqLKb5tQmTIOdulCjm/CMe/+vb9+/lpv+2biE57/arvKWTs
*/