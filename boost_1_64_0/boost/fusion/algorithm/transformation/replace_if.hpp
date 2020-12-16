/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REPLACE_IF_08182005_0939)
#define FUSION_REPLACE_IF_08182005_0939

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>
#include <boost/fusion/algorithm/transformation/detail/replace_if.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F, typename T>
        struct replace_if
        {
            typedef transform_view<Sequence, detail::replacer_if<F, T> > type;
        };
    }

    template <typename Sequence, typename F, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::replace_if<Sequence const, F, T>::type
        >::type
    replace_if(Sequence const& seq, F pred, T const& new_value)
    {
        typedef typename result_of::replace_if<Sequence const, F, T>::type result;
        detail::replacer_if<F, T> f(pred, new_value);
        return result(seq, f);
    }
}}

#endif


/* replace_if.hpp
Jj0KCdfqsEEfxV2a76ost+e61jvtjY/Ryvi0Zblnydx8tOgchNyAzrBif52sndEaTZN0ecvzqfbm8rwRXXH+ukpaqs0kdrDWl2nQ11Jt5mHRNxXphUxEfoI+p+iTzi/el7/g750au5ax7Eniy2H0e5jc0dqGIyYbJM8h1J9gbThiYUMNNkSs9rMht7iiotJervnXBD/HYrRhd6TygfKr16mdzDbcig15BhuclSvW2Nc3vQxqPXM+pOG/z1296M8W/YuRfeiv9dePlBfnOzIqS1bYy4PZ587oAxHlt5+lJzWdf4OEF5ca9z0t6mx9j2xrDPZVurezdN+kYOaDQr1PH4kdVyJRyBZkv9ZmDHZI/9Pk8vGsBZFUpCwSxIZCmZO/Xq67GrlnLGXh8NlQ6cwtt68M/f4YfTT0ef9a9G6Se3AhcpC813v0Vqm2yuuPPYi60V10r5T53hIJSzO0VfHRMNQNWSPThPmvH2pPstY9xv675rMy3PNZZRmTkl/cs/G5c2/49Nt7XnqiVxPns8Lk3R52szhXaruM5++A4XAn9MarbyDeOol3rsSr0o97FgWOt1bilUu8Cl08WwPxbpJ4P5F4N+v3HJJ40yWeGk+UebRu8DrYC14PY+BuGAf3wGlwr37+owE7Lhc7rhA7tkFVzhJvnEW8zTJueykcBS9T8eQdEkRbxHNIvBI4yG98GSkObGe12HmR2HmxLl5mA/HOl3gbJN5G3TyMU+JNlXjGeSn381vszIJD4RI4EZ6pS+dIA+nMk3TSJZ35kk6GpLNAv6fa6sDpjJN04iSdeEknQdIZr99DqYF0lkk6yyWdsySdHEnnbN24vbyz8N+IYdx+qKQzXNIZIenEwHg4Ek6Bo2AGHA0XwzE6O21rAtuZLOmnSPoTJP2JYuckSacKcUo6V0o6XaBD0jlV5ul6wIGwJxwCo+BI2Asmw95wOuwD58B+MAv2hxVwADwXDoJboE21V3lfgNdbtNc8qe8F8HRYCGfAVbASFsGrYbFuXq9e0tuEZBvm9aZIuZwOo2EqjIPTJP3p8Aw4Q+yfCfPhGfBCmAafaRfcnlH79je0zss4f9Cy672O7//fWPMlY/WWa79mHghu/ZfzQMNrwG488N2uA3vuQHBrwYIZT385yDVhXQ42vi7MdvDHsTZMxr11Y94NrxHbxBj0QeQ55ATS4+/sT4RkI9VIDfIUchzp8g/Gu5EsxIXsRg4jx5Av/9E6lt361/rX+tf61/rX+tf61/rX+hf63/c0/19uX9v8+X9tjX9pCt+v7jX+2rk0rDXMdRRXuDxr/LU1s7v1/1bhWeM/VOcz4JA5/FQZfz8NcZLmjhzfuP+iWQu1Ff7xufkuVzDzdd71J0/28JwZtVa3/qm3Z10SCfmfJTRB5tqXIzZkCVKOHfWB7AjhLCeZEzDYYzzPybhu1j2vrM78ax+hha1Y77JXGNaqOuylUPLiN4+fgwxGliIu8pJ5doC8NOGMJ6u8qDOeWjAvL1vkZR15qWsoL67gzh+zyIuaq4qO8NYTbb6s+flRZx3K/Hu81PcxSJV2b84x5UfnJtO8Ou85i4jUKvzLdmYH33md/ZFrkPO0ttegLblaZW30PEspL5M92QZ7pLyM55rJ3hFynacYVX5sHSVcwhLVteXrgF8eP5U8lrTxlHcR3KCVd65fHmUNvLO8eJ12aKc2ldx4HsP1eZR5xmw1H73GMD9dtSbMZG/ZGuO8/YaOvnPAopAY5ALsteX72ysn7WkVtFl1I9C5dv07yRg1EolkyV4ZeQY7VL1wV4vG9zGIUnOxYosWT8oS+K2jb2+oF36+X2JfPNJd2lG11i8Y7NP8lcTBoEnlpC+TuM4=
*/