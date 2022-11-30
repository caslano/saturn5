/*
 * Copyright Nick Thompson, 2019
 * Copyright Matt Borland, 2021
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0. (See accompanying file
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_MATH_STATISTICS_LINEAR_REGRESSION_HPP
#define BOOST_MATH_STATISTICS_LINEAR_REGRESSION_HPP

#include <cmath>
#include <algorithm>
#include <utility>
#include <tuple>
#include <stdexcept>
#include <type_traits>
#include <boost/math/statistics/univariate_statistics.hpp>
#include <boost/math/statistics/bivariate_statistics.hpp>

namespace boost { namespace math { namespace statistics { namespace detail {


template<class ReturnType, class RandomAccessContainer>
ReturnType simple_ordinary_least_squares_impl(RandomAccessContainer const & x,
                                              RandomAccessContainer const & y)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    if (x.size() <= 1)
    {
        throw std::domain_error("At least 2 samples are required to perform a linear regression.");
    }

    if (x.size() != y.size())
    {
        throw std::domain_error("The same number of samples must be in the independent and dependent variable.");
    }
    std::tuple<Real, Real, Real> temp = boost::math::statistics::means_and_covariance(x, y);
    Real mu_x = std::get<0>(temp);
    Real mu_y = std::get<1>(temp);
    Real cov_xy = std::get<2>(temp);

    Real var_x = boost::math::statistics::variance(x);

    if (var_x <= 0) {
        throw std::domain_error("Independent variable has no variance; this breaks linear regression.");
    }


    Real c1 = cov_xy/var_x;
    Real c0 = mu_y - c1*mu_x;

    return std::make_pair(c0, c1);
}

template<class ReturnType, class RandomAccessContainer>
ReturnType simple_ordinary_least_squares_with_R_squared_impl(RandomAccessContainer const & x,
                                                             RandomAccessContainer const & y)
{
    using Real = typename std::tuple_element<0, ReturnType>::type;
    if (x.size() <= 1)
    {
        throw std::domain_error("At least 2 samples are required to perform a linear regression.");
    }

    if (x.size() != y.size())
    {
        throw std::domain_error("The same number of samples must be in the independent and dependent variable.");
    }
    std::tuple<Real, Real, Real> temp = boost::math::statistics::means_and_covariance(x, y);
    Real mu_x = std::get<0>(temp);
    Real mu_y = std::get<1>(temp);
    Real cov_xy = std::get<2>(temp);

    Real var_x = boost::math::statistics::variance(x);

    if (var_x <= 0) {
        throw std::domain_error("Independent variable has no variance; this breaks linear regression.");
    }


    Real c1 = cov_xy/var_x;
    Real c0 = mu_y - c1*mu_x;

    Real squared_residuals = 0;
    Real squared_mean_deviation = 0;
    for(decltype(y.size()) i = 0; i < y.size(); ++i) {
        squared_mean_deviation += (y[i] - mu_y)*(y[i]-mu_y);
        Real ei = (c0 + c1*x[i]) - y[i];
        squared_residuals += ei*ei;
    }

    Real Rsquared;
    if (squared_mean_deviation == 0) {
        // Then y = constant, so the linear regression is perfect.
        Rsquared = 1;
    } else {
        Rsquared = 1 - squared_residuals/squared_mean_deviation;
    }

    return std::make_tuple(c0, c1, Rsquared);
}
} // namespace detail

template<typename RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type, 
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto simple_ordinary_least_squares(RandomAccessContainer const & x, RandomAccessContainer const & y) -> std::pair<double, double>
{
    return detail::simple_ordinary_least_squares_impl<std::pair<double, double>>(x, y);
}

template<typename RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type, 
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto simple_ordinary_least_squares(RandomAccessContainer const & x, RandomAccessContainer const & y) -> std::pair<Real, Real>
{
    return detail::simple_ordinary_least_squares_impl<std::pair<Real, Real>>(x, y);
}

template<typename RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type, 
         typename std::enable_if<std::is_integral<Real>::value, bool>::type = true>
inline auto simple_ordinary_least_squares_with_R_squared(RandomAccessContainer const & x, RandomAccessContainer const & y) -> std::tuple<double, double, double>
{
    return detail::simple_ordinary_least_squares_with_R_squared_impl<std::tuple<double, double, double>>(x, y);
}

template<typename RandomAccessContainer, typename Real = typename RandomAccessContainer::value_type, 
         typename std::enable_if<!std::is_integral<Real>::value, bool>::type = true>
inline auto simple_ordinary_least_squares_with_R_squared(RandomAccessContainer const & x, RandomAccessContainer const & y) -> std::tuple<Real, Real, Real>
{
    return detail::simple_ordinary_least_squares_with_R_squared_impl<std::tuple<Real, Real, Real>>(x, y);
}
}}} // namespace boost::math::statistics
#endif

/* linear_regression.hpp
Sz3rrwHQaeZxrFtiWx6N02EVRzBJemTzh5mU4qSejmzG2xitvUIQTLceMAuNmB+RjDLgu0lyXgO0pEsotYhmzjcjLoxsYrr2pKEGO18xfzO7DhgoSHq5VsrJ+h4k35jZKnM9Qakr1xkZJ0bLDxUEfQi59sCOdfvsMF8LS5fZf/28a1aZDaSYQ/xC5jVdvFfn6PB4HuW2+fW5IxeSELlhRE+6muH2+LLd2k+uituul3Z9mBDBVjfEK202+WLCPJNdzV5ONT23J5N1MVREdgdI+xs2GbLvZlaDuJ57o+ZvP/3kNeYtZTofvME5s2LIdOi+tYnHKBkcB/tIQG5lHRYxruP4ahbW7BfP3dFeWiQ1VlkxTicKzqkYVxHNwiTo7kWpCNN5DAZi0igbAPu6SCiha+xCswuQxe1Z5fP+Hd2rwmvHyUlYq7PAZIAgeuev41vbVrhD0YfOaxUldPy5D9czGM/PCFNo+Qo1/+wIoirlyU8pQ+eQpoIUPTnalmnTWDIIKPQNVIqyxTy4pxLJZoWWE9FgF2dSvwJiRN5qu7tnbmNBDuYfWMRSdyORlgpqeEs0wo0Ii2V3G8Sr7jFupYF5Pg15OupXFbd1zPS04OmJofnmuk5A+cX/5Q6lZSr7IqrMGZEXW7nmPLjcq7Z9Mz2YbBNlXJegChzHFABKhY7ndaqX1i1HXgrb3QfOdYzYI8+0AnccV3UzzwgHySKc5laycZdRkPnyp/23U6ogkddVLnEtUYWzPKh36wZLqkx6eSgS7q22jXQQc3xAlUgahGNd6EPGTNy245TNl1Ko1iNfU9NjJvtNPpfNOT4cId+8g50i9BOHKaaqQCusZLS2DiXnl6AUNz+2/cMJ7g/gLywNCOD/nx8H1C4GrWRJ0LYIcVYCE9dAnIAeonIlju662Pw8laQuxyYzSp6dbKP0GThX0oI6MrrIFRR2SVFaMri2MdkS9XVmhtvOS1O8B7Yja9Bq8JtFien+YWWI4GrQg4+H5EhrQUuYq5CB3j9m9I7UR29pRvXbM314aNuK4QtNJIZhrlvkWx6/bDhvN0WyYvAcgpoCzMI08jrBEHADfolGwkxQ9DnWuKQ0vZhWb4UbatrpFXgl7jITb7p/NSnU5ooKVUMjMirkcv/STa24QzVBxuojEM8Av8TkNawmP0zJVky94VSnaA+GN2NrS96EhjxTFcdx0K1JN1UfClMV5mqsi8jOozzVwR27liu1zxs2PABtwXgtCDBVBhSO9w8tGAw5M0GL0RvcvvYpcnX3xdGmdvJhcJYDzb5rSbIrWkUUSdFVfFczEOf0g4sRGRuYKhS9AC8zWMGfPWKQSxriFqoLXwSROvX1DLXzHNm59pBC6og4ygP9aau4H17IdIztI8dVtcEML7mmvAflOxxV+Dkh0vMQWPbbveJ5o05PXIYS9cXDh+mXsvOE9xBN00KA+1OX6L2Q+uT8eZvP68nclzcMW/SHKmp2xtn6VR5fT7qYqiq9rLr7Agt82mNTpupQaMpdlCYAyR36FGot0mGlmVSX6Ad1AhsIq8D7mLxEH+Sf6YuSAmuRXUU+1/nEV1Hiq9NKz8ykA2OGvVyvWAkYPhCkuu6tMZF0U6TbnYwfQdaNY02wdbFHRQgdEc5unL8RLq/h8xG7SlyxbsdXIXMQEjR4Hsi5UrPHhb6dTL0UcA3bEGt68LMywEYXPJg76fv89IWf5ksO+CHTGXxvGbmzcbKX/0lhzbrw5R/XxKqma9nheHQK6cKYjQoWOeSMUEldsQF0zGSOaPqSSbWAXytz+UAJwRejqbQAIzstideJhE0s4p6ikO0aHR96UlQjT1sI6kdwGYWDUavLANw+LvkYEUtswTVrLSMKvzdjVNOh4ZryQ29evKc31HVjJsiT7WSqg9+1ko5uHDL/BGg1HzFJGvBMFRZT3PeyVRx0kYpBkRshKRHxRQQBrpYmBZ+iJtVuiCUB31kHg/hivoyE65zZ6mno6LNuOxfOspdr09zztNwkddhFqmCSDp6YMIKTjAhaDealWrf2yLdBOTjjDrEwGj5ry5MtHnV+BOoSXpzuDFQ4t/pjvsnBZPV04Ou4Cx+uwI3NiHPGq5oNF/R6wQDIUHMozcp7XGvEHWlvE3kc4CH5/psELeLlkebNzaa1onvmqGmA6/yieGMUGXdD1amn2Q8KAR8OzWLYmk7uHXBQ+afe3MVAJXLQT9u9s3ZAoNqZHHJk5XJB15W9Cg8YMUz244+lozVm74+oUnNEKLhPs1WwzeYxfPb1kTe9QPFSuBpxKg0Ia3vd2gUJ+x3d6qELLm3xr97HUuxD+Vd53NaiJvSI+bsCOtxSl/0y/ybU1uj2ceSnUgMh0HCUAQI4cUiLoorkV0Mqts4oDUit2+18ubErX8lFPFT1vHwrUCbmHiyTC2vdPk7FwBC9swlf0+DYflcrqWq4MGTlbu86DFh6HnfFHXdMSAcoVNGSdgi2CFrT85SA5Nyjx3L6Z9neXSyKpIq2/6jOBWf4H73OEoCxn1jXBaXTpduhFuQQBKsI94FL+T/f+po3uQNe8c198LT8can86JLrrGad3hKqvuUj0pXrmiMGMLo6vZK2vtztc3OC4oLmZP8bjzCo2hm7HYBvAoBzhaBZFg2sKUKW68TNC5KaKBz+YSfHeAJFJbDfHSsLZVaKR/15Fmyirs9RzihEkQfyjdvrRlD+g/zhpVVvSaJczSxUduNRcg7Ogr17p/ZNQRJNC6QHDBrEUF3DV61xiQto5tAN/JamVxJrWPpUDmBGJmdVKJ4OiTmLBfEx0vWl2rUn//QwQzRShsWbuI9z8fXFBsfHWD7SCHk3VQ8Uo46Z58/7TP7GK1eLeZ6P7YYCPhIXEjo8EoiV5uWi9hLLSxga9e4dy2p84h+gGe7OgBBb+SS4KJWyUN4la6lQsSULAyrhdM1tfwPOHhvktcI+uRCqwRJPX2AnMD/hLgiGNbkUb16oAQ/NC5EILlqtK48wbRyFD2+fzW0ZiLcDksarCEha7OIqzhSymk9Bd+/2kDZ2MfjOd2VD+ydjRzXlxiT4zxEnH24ZpvdNj3tMVCbkdrBDQ2kHEkWt7GGBDFSkBexcA4/cec+HTgpDLQd9DpxtRiWKbpgg/qBwxQ+iBPXxrAcE04oeTNKqu8HzohK7f82nPbbaD1XFN72I/+YmxTJQ9Z+BxYTNwd/FuRN0BvtiSrKtgzj+e+pSLp1iYInvrPNkJj0mRHGvK7Xty+LvzOxwvZ5SiBjwV8UMOQ0TpQC9Q2c73kRiYqY2e5Xi1qQKUfGECaeLgyhrIURhnC77HeXc+fvFtv2D67Q0NLLt3Iaf++wLfVKnOJv+Fq2aR5nJMYdVYw2u9NpNP1qlFgwMoDHrj2LKeyJ4tRWE2BojRXS4LLRt+W9qiLl/SHPhPsXgffCDITUBNU9UiqnHosxCzle87wk7REKzfTXmtF1Yl40J2YiiN8UtwvVwUIXtqaW1Cj9G+FplCjj1ofTEQkPXCxqEJdyf8yRjvSpY3Cg7JEdXcYGyjmcJKcXIZus/LUoGO1zyibL/SnE8zilAm+gXwv1yrNJDc5+ZsiHLudGAmEP/Q1hU3CScnPMGK1JKzKkYHyNcOeC4TSfKcOXvGwrXNH0POZkIzA5PHaPsko04bp5vy2IdGACTRxQXpEbkUxqoFp6hd77BH+QkPY0ryGBHNFOYOUW6l9V4NhgnPzGRo66U0njytqhTafqlFjLsuiCRuZBMvbDD3wXEUVvAgqPUuDurquTCMUbf/PJ4z8dlcq81YLMrC8HOqvaqKumhfR5SnnteG623MgfSK1yfnz3pLyFTzbbKzUV+7ZRtV2FxUvGRLykFghhSwNm1hSrVNynm68mVTX+OCijwaobue4JqCS3o7b5AKxa4KRRdZj3eJTqK5o5//1EvbKULfH/M1VBWDMDquCzFZsEyOW6zukZDsT/DQ5vBeT56rVlVcONiGFavWuHkYvakceP7/E95Q7YWQQeeRtZgud0fGJkXhdu3LjKwonn2ghUdzGD7bOb8MPiN7n7RFpkiPq95mtz1MnLrQ3PGE+Ru56DG7VvM09mKkuafDxH22JAonlmHz0EO0GZK/yfaRvHnY1whhXVc6IwS56dLi0on9IHE560WNTMLeZHZCUG3K21Ic8WMPQrcJ3zoRdZR3Vi3mlW4QKEr2bbyulhTOip896KhndyugmgUUCZBc2refAh628Xltb4JvPJBzPl7c/vZ9eLX9aaQsppCKMD64RIQ9kwg3tFLIlwlfnbnKnTQtY4dsZr8PiXjZOmEd21h26yTziOFhkq46A8dsZj3yfkP7BYCMijPZWj8IZoPhgwRtqE7m68d6M5tXeNAlGxP28mAFnrDw0N81lzAfReZ7UYPLsbOGPA8abx58ifGYPqYsq4PN7CKpCqfVZQRNPLckLk9CdG3EvDWuOpdlHI92PrkWvy8cyJuvMAshmTJs5aMGo962l1pOj3M4Awv/RNYJzjg7EuljO3vb4ISJqy9fp80I8N+ixCYuQCAQa+tfuhTVepIiMGov1wKE5W1pmQ5IKWEU+T0ZCBrVtlQqsfSS2XYAKdsL4vqYnDmqtiJmDn0WAgkv5vP04gFrhNZF+SOX284Fd4AUriMWA1Odd8WyqsVB50/06gEDUZlmcGKPRHNrChIGm4HjJsVrBC9Mza9lyjC0GAN1ruc+xzrwXKI3Fs6tj3jtqhbGrebzqSJayz5YX6nVrH6xhQ1kiD3qNbHsAX5Df/z4LL758LxilmRvisT8Zwsk+VV2LjqmKglmfXjT5bYjfNkZn1VASnAmOZ/OawaR5Ts6lIeQZk0+/GSUQhRwj18tZpjsjUV+oXZY+x23aaJ1SqzZj+OE1wEi5+XJsA1ZpoOKmGsOwqDjswiTHhHe6cPH0UjRlbktGaHC3kGnnXZmWZRJyz3bVxp6xQokOyIU6yj0K/T6BpLjRehtvFWrq/GSPcswC/gOMvrE4Qru+z/HiNirBpazkgcoX2XQKsfxNaRNNowzLg9p+orsCNWxY5raKn3Se06cUwzdi8lAMXtgUYZGiSpfO4u4cDc/8bfjgrYsKYtOdPZ9qmgMJaptkapFmXA4LCLbKWM0D7b91K2eTVzpkiiNvw0J/JMEc39/hJifkZLHbggkIr/WJHkAyNcV+4iX7NE5A5c6DxZBM25yaJq/QC2CjTw4q+upRFkPIvxm4nwhRztXIZi8pV4TFkRBZfeqJ4sHtTcf0GdFlbwqafMo6OvyFHQWUIbImZGubJdqTzLGnew5ixeaihO8nAAxejVIJv4JLloC9nZIjrP9EnWLVtBCMFCFkd4ElHNQwP1QdmyoRdYXYpzPrVzpEbpbaIx8p6eG6Wce3CTUjBgwqgh4c3PBDKf4rK3PrW60g7p2TlB1nuc0g/2/gOC2FOTOkW8lpqMg6S5GLBlKitvk1DCJ7a0e2lD9IEKF1kRR6Ioqa6gSKHDYT3xzkhZNPEWLxNd01yir/2qAO/6J7cDv7epg0YYOzLBTN+8EEdVr+H+8EV09CtkY1jlMb87WwYWOHsbO1AxOdZXwnY6NqJzG4HUcbjYJCGSgKdaP0Gq0DR2YWx80hXrvfLXysB0/Zs+ML9QYReDFA2PY3ukwiI24ZEaXqBKBdESHEY/Ep+WnS15BBaMmRkUcDjNRqKSUiArLkBKzHGIYnFHmyddLthsw6I9OspqH3uM4zT0b+k5SaH6HcFZ4avEARluU9ORZ05hNzEv5iIb+VosOBV02DAWzExIdLBXrJkXoLJh+xSM6BL/rG/U2e7RFuocC0bN//lWYABEK+tpwukum2SllW9MGoWHKINFdy1i9tTrLPLF2GtiRJyjw2S0Ok9bV6qtnizd9In4aHZQw4H1EB9HwS7w01EUJ8Q2kSAoATPMdsoG08vMAJ8XkXDILmbfHFPHdEympH/n5MtDjBJLC//z0KUTzt26GxoGcxqdN1kg4UJshkW4Ql87Tf/Kq+6pzHgX2i2bnX8CwEFecJ06grBCaA9d/AmLRy+SvBFxgirXc9DgspPj3EjoQgiDvCcBz9yuQJfR1jaDrrwh1BPeTd7p8LaWv7/oEcyWW4q0kVlI4GHklaHp8PrWDFIngqDomBG03nON76cYL/B8kJShtW9lk7Wx7kXOvC52mJRnkNrxdHmxljvhcFMo/6buRv39jA4TRSvqjMrfU9nokLDhfo6f4nuOe5JzD51BqkYxnF2vMh1DXYUIOfOfudQsSQRHtAG7ykc8oFAQKl84pkOqU3IdsmSzEkgahLrsiF91qE+kX5yrfNEfWvKzjAYvszEInQDlfs52qRY/lD0ccPqsev9nm83O+MI3iC/7oikLLQ+y/LE4DrnNc8CaBmLy9Qo8XoHcke32ceai8S5Qtr52FeypDXwy5zPnWzW+rXcNcjniU08TEk1ZokIJZm1hd2PzMBFr49txCiER495/qipt5RPVL9iMxEr4fL5/6Y/H6uAGnMsyq1czQTwTKNqckmiL/ChE0YXztQrlDEHKzJZoZghhVFEOzlstRNBDSCI1/rxEpC0Sx9bpRHjs7AqXvy6+CBOIZRyp/4VuwwNjXg26pGXfIzGQucYTxibOzRdQ6NQiYOg8NYn20ZQvT37dVwGaRRlbKCzaCrLzHnp8Ujs4yXRD6EQCeg6YkOVZsrYSlhEiRHcXqz361rpktTB0s0OCfjynum3/oqJgmvW0qL0ITi9oyWwM/w3wnyFyFaWTUc74dS0VR0FQ/qr5JdOo5Lb0l84t+gktd2l4os+2jjul2KnvsmH5+VQ33BblMloTAkgZIFT6bxVRPEZrRUoy8nen0kmWWoQSeledbeYyDvk9LdIekaNw0/BIqYh2kBAFC21S0O+QBubj2vN+0kSaBrTh3WvvOo7jFsRP9Ij+7Y8PK0Du1Pa04RNpM60M6rdmhvwS6Jn6lQts8ue2ThAZBSC45pnkCAZhe3dii7SsvUglU7unHXWdMRHjgLhieoNCzhY9xX338+Jsgo/JB7RiUT6nuUR0RpbJeA1wnlC6/rvgLzKOIGfwQMnXiwX0LEDr0JumSVqPoY5UhEzOxk7JyKJLyRmPC68BbxqNb84Tqd2we7m6fbwj546jqOBucyjnFG+LgStVvCqJ7teljS6MTKKM7eK7uHy0HavgZzIRJc3WhANpGiNQGeGOZ8/Sb4jM+IbLrf3ar32gLVpOkJNDptonreZNhPK2/Hiije6BdaM475GcjmmWvWowOn/aknNfQkQS+uLZr8xiXdZtuglMVd+aMmm1o9US/MuasRLqA5RGchZbv9ILuX5gJlBpSeuB6fInrU4Ae3JAEHYydLxNAU1DwqTYOINfxe0apulNPpa/Rih83udQ8CTQhu5PjN5WByXRgGPPg3gN86KQXHgYfPkbCA6dxFOFfmNjGlxRLvN0W+9VajiyBhJCVJAspLR9ZGP0fi0r5603vNqc3V0UnYx+f0HE4mdtJqbgVtOlOBTiQDVuTOv+hl0SQc7rFLVbNywgh+cIJ9I5gmm2Rigkvw6HPbfyzhHsZ8h1udNieLvN8Sboio0YWSmyjTiuA+M5wHKAQJe0fFq+VhNmmNeb2m5sMzwp4Oobk+VWRbOpUk0Cp2rt8dTGVK742tdvgdV9Yw5I24qk
*/