/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_13122005_1906)
#define FUSION_ADVANCE_IMPL_13122005_1906

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>

namespace boost { namespace fusion 
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    template<typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        // Unary Version
        template<>
        struct advance_impl<transform_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::advance<first_type, Dist>::type advanced_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<advanced_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<Dist>(i.first), i.f);
                }
            };
        };

        // Binary Version
        template<>
        struct advance_impl<transform_view_iterator2_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::advance<first1_type, Dist>::type advanced1_type;
                typedef typename result_of::advance<first2_type, Dist>::type advanced2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<advanced1_type, advanced2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(
                        boost::fusion::advance<Dist>(i.first1)
                      , boost::fusion::advance<Dist>(i.first2), i.f);
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
Fr95fVO0eDAPZpVeNr+NlijNl7Vj2BY0K5gPs6Nzvv8BzQYWwGzDnLZj0dLAvJltiz8ZiZYBVoLZlc4rXNBOSXGrt28siZYl2bBeRzypntI6DUFtv0J7DebJrPVv5n1oHvUKjrkuaJOdag1WjNk/6yuGU63Bgplt+dp3JdUajPfW6z/3vkGzgPkym/ZdTHu0VDAds//sPjILzS7Z1vnlnqOlg/Hck2uFJaPtkfK79cS2k2otrTPgaNJ+tGwp91VJvS+j5YL5M2vVyPUw1bN+QTu6zscPTQ/G+959aaGtaLFgfC39+5UORTOD8Zo13eG/HS1ZsuyDE5uj2cD8mHncmVIabZk0X+5T0wW0DMmCzxgTqGb1pdyrHYqimoHpmL26+UsX2oPSmBUt8dvQdKaCte7yve0g1UyyFat96LxHgXkxixh8gvpnkuJSfi39jOoJFsCs2PnqT9CsYIHMTtw++wbNDsbzc2/w8C3tQWnMHZfOhlHNwHjfe6e+2Uc1AyvJrF63ktQ/0aCgZdX0/ofqAsbHdDH9FkF7CSyIWc8d/c+gJYLxuuwplvId7SWwcsy2j1z7F+UOVorZ7w0XmdAywHhvD2/IWkq5N5CuZ81+voWWJa2lWbE1dK3LAfNldnJh2Z5oomHB8/7gp3Mz0HRgXswOVb7RimoGxmt2u0nbNKoZmD+zi30zXqOZwXh+MQvetaCagemYLfKPvIdmA/Nk1i3AUoHqCcbzm3m4J+WXLuXnaL+D6rJHmu/+44tBaJlSfh0PPfiF6gnmx2xn/d+/RxONCq7l1OhrTdCCwHiPnt6eNx4tDKwoM59+K/VUz0ZSPQPuUY/M0nyviy6eSvWU5iuUsI32Z6oUt6/P63+pnlJcV/vVjmhpUpy18JXjVE8w3qNSle9OoL0LxmvtdST4PFq2NN+FGhOC0XLBeB9iShg7oXk0LnidqHuptifVE4yP+VXL4MtUT7CSzN4sbdiDzjRYcWa925SIQLNKdurGjTJos8B4fs9yX76jmoHx3s4f1iADLUMaM+Btv41UMynu6uPC5+i8S9Zb36c57U+pLnd2HD1FNWtSsC79dte7SvsTjK8leX2wC1qUZP1mHVmLFi9ZTsrZYWgWab7on66NonpKti19VC00mzTmcd8tu9CWgfH+9fXpepH2IJgXs46zZlipnmAlmCVe6v0ALRusFLMHv1wviyaaClHkk0Xl7c+t4QuonmD8/hA5LLIx7UEwnsPPP3oGoJnA9Mxavan0N51bacyjKTtX0D4D4zVbFJxal+oC5sPs5Ncnp9N1EMyXWewvz6jvDrBQZm7nX1Ktc6QxWz4+WhntNZgfM12zh/g+AP53wT14pWyt62hRYGWYDWj1RwidPzDe26W+7TzQUsH8mUV/CC+HZgcLZqYf8mIkWgZYWWYXB1/eRucIjNdz1pU+hSl3ab45Q7o2QhPxBc/7wP01YugcgfG1+N0z/4UWK8VF/zW+IpoZjNdzY/k52p4A4/37Y/6jR2g2MG9m47sMjKC6gPF6Pq+ZdZ7qIq3lnw6B/9BZAQtk9i51TwjVRbLfo9t0pfOQUHC/jL62ugPVBYznN2b6LB+0KDCeX+S7VhQXD8ZzSHVcqkR1AQthlrG7eyDlniC99+0WOoXOg7SWme/GzUZzSFZzzJiRtF+ktQSPHqS9NwTjfZ9daOsyyr25EKV5360jaMxYsLLMIq5+QXvJAsbHzCxv11PfwYox03foPJlyByvBrEXQ7vOUe3Pp84JfNzWj3MF4H1ZvuDKacgcLYnZ1epgf5Q5WilnDLt2aUe4tCq7lXvvDXtR3MF6XgI5N3NHMYOX5fPdMrdBSwXiPdvznZGHKHYzXZWQ=
*/