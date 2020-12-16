/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template<>
    struct size_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : extent<Seq,rank<Seq>::value-1>
        {};
    };
}}}

#endif

/* size_impl.hpp
jjTB/YxmpKcdp9c02HMK/LXp79emvt+c9vJTXq9pKT/f9J5rfnWe6T3H5CeHnhMDHrw/jKVrhpZgOEZTBa4wJ43T7NE4zV6N0/yVxmn+SuM0f6NxmtnG8Ye1OD824pc4P7DzgzM/MJv5Nm72bOPmr7Rxs3cb5wd/doDnB3fvgT1+RNTuwSX63XbZHZ+u8tCq2SQ7OzW2YMdEuxJhop1wm2iV7YlWWhObwz6ms/gefFOWUd0s1sX5cBxehC7F1bPKXtax/Q84bDhvlFcfHNkcS23+ywtSqzkZyFaxkWz1m7c1hodHe9uL99btd5hcdDsszWBNkrfZkEltVryMTU4wetvtGBaZ7LwkttiRJjbMfujxV6og3+7FDJeV7bJK3mgNntrqjd6W4p/NeljN88Rm/0qUtf964zZ7N6DNcXlbUc6e9l9v4GQKS6355rdJLrVhGAbzUXjlw5TRYTnb0JsipmPLkWwXSHDbDIPQ2DqKVPWEdwnJf6uaXTLHeWr4BIHp/nTLPPsfWh/y+cD9PWJPNIG9z7jeCMl6WXrcTa9ommzNZZI1hN3pkR/uzNraUFSj+AKTf2XUXWRCyWwixPdPDjg2fT+ameOgydZOLkyZeMSRY5sdJM8/htLmwwe56wTJZVcT8FKEMW/lsG/ZjjIXtuJLt6axENIExQHSDGMHNGdXkH+XM9F6bbTDcXcx0q4Fe3zkgU1Udf6ysD2my3M6ue6yf95kt21zFrkLd3TeaneF86b8muyfttP4lDu4UJi7QJi7MNj7gmB6ITC5AGjXsYeGi39kxaednM16ns2IYsg9cCFiugGcrR42fIQnjB45cWxGtm5qLPncC8zNlPbH9Ap7KttMlr/qnl5xF+HwdJQdHo8y+/oTOHxwJh32NuUkJrv76tevreCJ+azh/Vp3kig1yW/xeWzzfxFNufjHOrfpkRZmc+chxciUDduhhOefmHZ9BQf2wqXik2KprZC175oR8sF2QTVvpNDDeNT4/ofJAc71Ku/aq029norV4FfeZiczefO4NHDvPNiyX1irwvBmTnC33AQjDBvvwMR5HefthVI0vHVsk8KOnYSQ+QetmjqmixnCtHScx7eV8jcN8jeakptMdoMpvLlkA774dH+sWb3aPmyImWqjKS/bIBNTo1F8qswmSxhsWvBJclGw7xNQkMNh0E7+5UP/BMsFxva7GKWJEPxLTmHdf8xuJieCHWpSXQ43pqd3o0VPbh6LdLA+CxxtQvQ4X+qByT3W9gbM0eu4M17D0UKzwCvUG1Kd9YlEHt1fniYL1AP3l//nqx8XiPDhoHqipatz/81QbHKzcrQODNLRpKv7kntrTzGY8pbRYbwHaD9/3WZ9SN8gcuSoOWY2q5xAt/KamJZCxKgUZrBSmJSWwiy9S2Gn3E6RWs6g9ZxYlY5jav5UyUzsUvvwn/nwa/11i1/b77TjNsWP3c26uzPLE337ywN9+2251a7e+x/3Xxsv7eGjQMJ18FY77r7DVrtstttWW1Kzl5SYgFd4FbzNVjtK9u2Lh6MKYaC22ZZbyv9j7xrSfjtuMc8BItT22K74j0f57X3TJUKXw77YYqT2IVHk3Sqy7dmybSGvCN1NnuCEvOvA0E6ju8z2LMdySC4OrVuMHFk/MJWborB0mw+4l5SZtkPNpLimTGNtDOyz1Za7yQuMEkO8jYHN1jMpqGwTdtx9++1J1l7C6TvVTC1e+LHZ5ttvlZGivO7jQvIW+719dbdQ2G39teI1wyLutnfNo92jcoiy44BcXdg1rYTdd9si3NLsP6jFmfYY2HUgdt5r4N3lHxJ2GdgN74tmt4gsEogNsKnGx460zlZIm0tf2MJ/z/GsWvw=
*/