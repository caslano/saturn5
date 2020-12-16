/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_KEY_10022005_1907)
#define FUSION_ERASE_KEY_10022005_1907

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/erase_key.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct erase_key_impl;

    template <>
    struct erase_key_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename Key>
        struct apply
        {
            typedef typename
                fusion::result_of::erase_key<Sequence, Key>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* erase_key.hpp
G2pRzndocjyPc2gcuAPz5yjHjzuLvcNNy8p3q+oo67+M5mglj8fAKMePPWNfbUeOJumVBv1Pse7y1514SoFYm9+wrPKfkr9ZvR1pX/koZ9tXMcrZ9rUR5Wz76kc5276Sv8c4276KUc62r/koZ9vXZpyT7es02myUte0r/48oZ9tXlLPtazPKjW5fWyN5bl8Z23ubZlfIwawvCxeOWPgRb1csNUOxBveDUCvT6OyKm8e6/A8lgyLmtvKjqJ7VbQt9+DvA8etQfteYz48aBk67DGvTcnDa0ebepZg2vS8pC6iF9qE57dJTnPDp360576fAp+8ZXfspufdonf0UsRdjGO2nDIy+s59SfG/Ip4tqmNfHdTdN5XsTX5NMajaoh28YDTaN9UgVh96fKL5PamnaUJ5Kw4PdHfSx35Q6zI/ffftWRA/mA81vW4ZNk9e/57+7A5eG2cHc7SMZO1tbWNXrqF2lpaukWKP8GDTsCCOvn8w0uYvL85HCDbzuVzWW+T0WXoN9mmD8ARapb0ndu4tS7z/88plOb+sMv3K+WJHnOZ4S0Yfevvv67J4E4+iOHH2bTtTxwMZZWRPte8vq9MlV8TZqTKd/5N5h8ogIsz/Zj/mH1ck6WM8bvVZZFHrB6MuUB9aLRm+o35esviT1eaOfaS00k/24axHVqSuschlsGOZsR367s6v1A2OuzoS+aXXKI+s9q7t6amIOYHRbTwPD6HraMrqup22j63pKHhnqup5yRtf1lDe6rqeC0XU9FY1u66mkGLIVXw+YTz4l1OM2WDDcaBucN3FqG2waXdvghtFt3XYNo+t20+i6bntG13XbN7qu24HRdd1uGV3X7bbRdd0mjwp1W7e5kPE2iLn6szJ9cSmtdh5zekJLv3rMWl9qVCzydwOpUZbUO1LFi2TaKj2BNra4b89YImx6K9DblGSno+99SRZ2xX/nGoNGG+Xy0jhDDYTXhqMMGtE+zP9Hcvt53csw3KHDDuMMlRwzpThDJcjMvGG440TfHGV0/jeijM1/dyTH+d+MMjr/vSij89+PMjr/A8Nwh4X14yij878dZWz+k5fFOZn/XJTR+c9HGZ3/gmG4U4C9voaZdmefyzj7tlrzJiveoQx0ipz9aa1RpKw1Pw7t5AL9d6zAad4wGl2CWz23Z29hH36f+3LG0AMNfmzBPFJrVPysFQKNcsM+fqjt5zIqSc13TujTfqa0ak1o/VDbK/YJjDbMyB70WxGdMsPr2lb31cNxJD+PMfuh56xOmePf561O1ch6wepuwIBeDHU/IMBPCHWfBYzpRqfkyf2/UKfkybqZV/VGmvwm0O4rsHbWJUxof85+RzNWOti5uireKn+G/524WLV4rk72JfpLyfg5ime47GYk0zxDqwP09k+H7edPPg203F1bGKavgbahNNQ7frutdVdot8y05M9So0IhbXdWXueyNK1VnZ1nfy/en/++T9r/g8XfU9eN49lgLS1CjmfzIaxVxpJV+Ffny/7eqoyVb1nwzYX3epR+q1t6nW1R6qlYQVqlFtj+QGqBfW9JzbevLB+DC7B2S9G2tuTfKR8yD/OXFFrqy1LhifEY7cJdg6WGwW+B8lrWCIZW2Ook70M6NsCtNGtrVfoiO+d5V6a5z0ekhYX2pTSMYctoX1p3BTaGer+c1KjASEP9zbEm2/xu+KfQXVs6gzAfJf7uPhsv2mBOajS6SS0vtb371e8KUiOfUWrNp2TamZMrrdVmo7HKa92Xuo7T7jE3OT0xOTF8Rfz47PgR/+4qj/PFi4/gVjq8RjsiLH8ueF9WLs3ClYg7PFWadQsm4g6B/rsrVfYPcy7sI5PTkzN0K9i9nTvrk5icwXw=
*/