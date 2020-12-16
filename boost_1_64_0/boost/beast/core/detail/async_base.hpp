//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_ASYNC_BASE_HPP
#define BOOST_BEAST_CORE_DETAIL_ASYNC_BASE_HPP

#include <boost/core/exchange.hpp>

namespace boost {
namespace beast {
namespace detail {

struct stable_base
{
    static
    void
    destroy_list(stable_base*& list)
    {
        while(list)
        {
            auto next = list->next_;
            list->destroy();
            list = next;
        }
    }

    stable_base* next_ = nullptr;

protected:
    stable_base() = default;
    virtual ~stable_base() = default;

    virtual void destroy() = 0;
};

} // detail
} // beast
} // boost

#endif

/* async_base.hpp
2SX5WpecfCmW8JJuVj3+30j4YYzXUWouiDYG/vQt+t0l3SUe5/rrJfxbpOxRi0DUY2W81sH1q3X8b5Fwt5GGf1eAguu5NOGH1TPnqNS/9tUB10Z8hnLXsIFDmdhGfnnb46JNLdtoFdCLNjpcbtNGps2IvbwxXhsVx7VowwrTX2akSl3TxsTSZqN0nESte1xf4lQaZyjDEmdGTmFFvrajixKeeUYvtkWGTqeFrayXSpyB9MPmYka1DvQ+MUiRb0Toe92vFP4e2JHBfeBoN3MUzYyVdZTgwabQkwb5sPZr1+B2TAeijAHtmKGfSbkD+lVP7jvMo57fbJBhLrxnhmgzXJo/ZUa+XXsxToLlWyKIzfBROryR1ImsD8Wfh1p0yx5AO38cXO9vrbtY4ZusOvC7DRk6rdga7RPH8KYSPh59rLn+HkFRO9Q1x6L0E9RtRoi6xVyM3//wlSueNgft+Iz5DqjfCP5cDuIYfBboA6S7pTRE/U7BF0Fq9gdtY/CUxOmCEULbITOduJpyyrp7XcIb672+z05iLO7NMm2J8jFXolI7ATOBz+GPDT6Z0cXJyKLuN/tE0LdlyD9Kr9c/Fn99w28j8Oxs03+R5XsjZfm5fnnS8dP1Hsoh8Tcz/DrtSuK3MlqrTT75Ukwjy9dQlCWmM0z8F8H/nvh30u/Px5iAfGCXSu+RvSX8Ax0cx5neAL7Tzy8v1e+4c5aMU4bVxkfi0cYH82v2I+5zWHTi9wjfEIc/blpQ3Ga+uHx3se+9rOOv5b0vqeA69qfVJygt3Pst5bhRbN4gCxRSv13C6ZLeJ0Z9K49lD6e5hHscvt9Qqx3CYJGxA766soTnFlQUTZXwnvAdkfBOEv5SM+lJ8luEvKGPBuetfFqJxQa8jbz7G4PtIHGlFRi/D+O/AamOUNNycrOkX4v9PR6J26vHtMEy3v7dJysOnabEQ6JMM13Wi5fI3uQVLdChIC+NG1bTXozt92NB1wR/t2yONR8wSf8d+IzPBe+Iw3gDJOlvFm1iPu2+i1yl+F1k2GCbbU0bbOnjhxFm9kt+z0ieHdXf3kE/4RiHSLwTnn2HvBGG5oV8055U82qZF17IJMdOyDLjJ2lekVE97qKd8WwQ51oyNyEf24/P0/Vz3Qb8VhDtEmk33tWBugcmc5zacWXgOJVTONlujCJvkp5P7Bd/jONMtdywGZcYp5WKoxy+Kf4GDsNwWvplGctM+zHhaezoqn5tcFxiOgkhx50LdHhTFce++Lr4GznchjvU2KN/T0+b47M9Og07BtbxR9Jjv69SNcYfPQ9Lk/hlxu0qVsdPC4q/VtUYg3QdJkj85caflMMy7gTG3wB/9XeSplTbUc2V8Yp+Qy0QfyO5HyOOwn9Q0v8eK5HHUHt4Dh8c45YjvY5IIdpfPjgZN/R8cKrE72NMQBumoi9HIqwFJOqBJOz5yB0SwObyN+beQvi7dvOKkhB9bpa1z/FZpZZtygm/1xDc36pUyP6G+q/Z3zaogP6m96FLfoH70HXdV67rvnXofVn7/eMMt3yDYmHeyjuafvngoSaXv7Nr0ROpp24/++5WYvfVp959o77etG5j0mUffbh121T0AZf5/K4JV47/xLPyd/M2Ndq/+47VO3++/exTvW8tewrco6gMsR/cANid+5o9uH/bkzY7vbhv2xuYQT9tKLiWlv0CSVfbUHD/uBn3j9sCzwL2AY4D9uf+9bnA84BZwAzaHIwBLgdeCKzi/vca7rPexH3WdYx/J/db7+N+6y7ut74BHAH8nvutLsO3zxoBHAWsB+wPjAFewvK8rLgeBa5neZqKzYLPXcb97Sxge2A297Vz+K2ImbS9ygXO4z741dzXvoY=
*/