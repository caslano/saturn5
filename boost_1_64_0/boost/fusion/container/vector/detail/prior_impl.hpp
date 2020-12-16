/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_IMPL_05042005_1145)
#define FUSION_PRIOR_IMPL_05042005_1145

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/vector_iterator.hpp>

namespace boost { namespace fusion
{
    struct vector_iterator_tag;
    template <typename Vector, int N>
    struct vector_iterator;

    namespace extension
    {
        template <typename Tag>
        struct prior_impl;

        template <>
        struct prior_impl<vector_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::vector vector;
                typedef typename Iterator::index index;
                typedef vector_iterator<vector, index::value-1> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(i.vec);
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
aWo96Luv1TQ1z+9oaWqenybN9R5AJVqammerlqbmOUlLU/Mc/bXf/8w9gEJ07gEUpnMPoNAa3oNO7x5AQU73APplYyz079FT+zpDbX+jn2H+k17yHZTvpBkGEMe9/j/vXTAMv8PhuKiRjL324Tc2dscEfBhH4T4cjVf68hsbr8NEnIFX4yK8Bu/AMdiC33JJuAGvxT/idXgPjsWtmIyP4fUY3YQx3Dgcx+OrmILv4QQ8jROxEb/pJmEnnIxZfvzWxrswC/+CN9ZyDEeJ8fvAmIzJmIzJmIzJmIzpPz79JvX/tJn5s+qo//9Zh/r/fmlLDmlIHUI8wwv/T9X6v2ydrifp90+pQf2/1Zdaff/Lz93rta9oaWpdfJuWptbF12hpaj9lppam1s+HaWlq/TxIS5P+KK7DV9P6y32pHerSUj/OdH1WoaTneqhPF3q4VmGJS33aU905Xluvx3oyONTva1d3jtX2kbpz3deTf+368MoCJf2TijuyDvzjtR8uLHt15hCfkHr2evJpk3xW5bNbjB2IEy7PNWyOPbElDsFWeAO2wY+wLWbKcw2XYDtci+3Rn211wDswEP+EHaXPozM28+a9wc7YBftgMMZjV7weu2EGdsd52AOLMBRXY09s0IB6OC7DMNyHEfgdxuCP2PcSnpu4x6gzGpMxGZMxGZMxGZMxGZMx1dnkTWT8WvX/tLnpeflZs3PqoO7fhrr5SaVvf7MX9b20jOxpM/JZpa1N4GmHNgGz9DFmy77NJHZQUcr9xFbPGkPGx45NTJWM2dsETBdtE2D8q9qPbHUaz14s22ooCzQg2rTif5/qbSuVAbDVb6+qLhtPPW1RfaXueO+4l7z9Vv7waPDuo8GhW0YP9vQ8mNo/Z6WuxqHqjx/1/Hwa/Tp67evc+nX62t837FA9Jf2KoPRzN02e0av+3BlNij5LP8LYOFv63/7w0StD0rPuWfr1gum7gnc0qP34V/02Bk/jcT2Pl326wPa+nLkq8qlRjyW+f3hbbOl1m87xTBhfJf1A05b7UqOjXxzcoFf/OZ2Gd6h6Lo589uU7QXuA9nwDaUPwxrbYBAOwFbbDDtgJQzAEe2F3jMZeOBB74zCMxKswGpOxP07CgWjBeJyJV+IZNJvkewINJV/1bdthkjYPxRbYAFviPmbO3uJbo3ttKffCTyGsch/8Cp2xewl64/dc7pcfSiRfZCzfeQ/j+cpkTF8FcYHQGdcn992/+Pg+i8MYv50XGecXEin37a/hmL84YqqM/VtH7PQwBjBAxgEmVo0FdHkOwHmXcYHxOmMDl/Oebd1itOMYkzEZkzEZkzEZkzH9HqZftf8/zcp/qYUx5v5zo+qgDUCp6z9se/7/ZfZ770v9ewzRhRhNfMyLwx/Z6hVZkXmpY4cmpyaOGptc7bOS20hf9ketlHr+rHRr5myLSdITMFf6yK2p2Vn5Vu2ZyXf5O49bT9GuU82xpOdUPbtYzfNJyXMM0VbqQde2ZgxvVZ7zU3NnZ+XPzpHxCqHV5NmMY1o75VntN+f+zqTPnZYteRgseai6Bm8WEUhkEvlKuZ2w5WF2Wn5uanqhNdUSmaUWILNUW4ZV4wHm2MpqmjpmYEZz5e/cXPX5645jEWS5IK2MncorTK7x6C557UKsZ39L7eWVH5lVd+W11paeZi2UtHgM8bflyZpXdS8DyZe/t33F84g2RB7xKZmb+rE9X+nW1KoPS6r9C1Xz8pNyUD97re1/y1rsz6Y3Uy5NvUnn70X2bUo5qp8/23y7mc+H+XqSdp/MJ+M01Hvb58u+SahlXyT72EVZRsr/ZuWPT+z7ONP26aBZ66JlH8S+OVyLbd+Xma7fiwuyrZ5SniE=
*/