/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED)
#define BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/deduce.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/config.hpp>


namespace boost { namespace fusion { namespace traits
{
    template <class Sequence> struct deduce_sequence;

    namespace detail
    {
        struct deducer
        {
            template <typename Sig>
            struct result;

            template <class Self, typename T>
            struct result< Self(T) >
                : fusion::traits::deduce<T>
            { };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template <typename T>
            BOOST_FUSION_GPU_ENABLED
            typename result< deducer(T) >::type
            operator()(T&&) const;
#endif
        };
    }

    template <class Sequence>
    struct deduce_sequence
        : result_of::as_vector<
            fusion::transform_view<Sequence, detail::deducer> >
    { };

}}}

#endif


/* deduce_sequence.hpp
P7pUcVEkqgZZbA679M4zJWWv40g7yyy7IYx6/KBLe9HFn9BeNQN9ha+PjR3W+rek9YSBC+IbKuac+zqedfRv6fJULCrCXIiKXG3GXdugzcQzqQyqMpFJBTX2Npq07m9y+SSrk1BwnmdmNOrGovh3u/jHKBmEtRQ5W97ZXm3Wif48ctnFK1ZIkYZpHnfpQ1/7eVylZVJ5HNZ6rgcwuehGmwraxlUV6hcqBaiAvWJN4X1ir71CISKl4sS/P6b3zoefRfXVqg6yukq6dSI7ffrJwKdNFE/DiA9kN07QPsLlrxkM40AqlTPUbViJ4F17MJdngVcVCHOdtc2BE4XjR0YBnvjEzstc1t20T2f8+xpfK79Rmqe/2LX+Vh5ofKnMPWkSBh2loD+V3yCOLE4I1DaiX4Q92OgU4uhihEjr6+Xi6Q6Lq0+HQl8v1zsMLg20bPp96NsWEWMn9Oa9LsVdRxyZwBF5N4NjT9a40aPN9acmNbRfPQLGfkPr9lFnt8+ug72fae9Z20ZNI9+tq+dT8Dup35egva53NJwFEGL78ak9zCnbkQ807X74zEQMJvZwU5ajT0OcL9huH5l+v2TxXldqm8yPQPm0DzrtfY4H5RI8WbE6L9gnfnng9Qt5b/oGg/H7xPExs6/DoAzoY4J9k+XTNTvSr/t0OLqQuI1AJ3KI5xDUzfkYUsa5Az4dMrExLw2djh/MB8uy7+BkHORlY15Oxuj8EPMbxNh+6/vuUbM+xvXdc2USHTJx9RUPPoQYX55Mhqif+W9YyNhN9+gt/huW+il6LWLJHKYzR8y/JmKob6XtW07E6MysrTBicLwSWYxv5dGJLF726BhTE3W4hH7KqYxb58k4IidTt5mIIXK50sP0hAVx1/bE6RwRB3piiqOCY22jLzc4nEfxXdPDDuP3Rgdxt26esN+7tkCef1kalMZ+X70dfte5Yx980X43vk/BpNtJb/32QG98RTUY69sLv7tzie3bS3fo6GQesPq6O3Z0b+xa310Ug83njo1n3Ilg/PEBGJR7xPbl2rFvvzNiHLl09Ix36eieLGG/f5ViaN87bfvsI4Czd2723Sz57rftM+5K6F7b/saj+227ejfE7Nm2f6MYv21dffXdKbaKuSA+M5G+d9u/9B4E47X9vzy63/avvifB+G3fxeG+F+BA7/lo41fs9p0Os/m+tQaf8dvH7q2/jfU38pb0S4Mwa2aQNi/USzxYUturJA/zRBkb+mPHwbuHjp7xaNjf2u0txu+R1K9iHVeSi8yybo27w+Byt9c/I3uxEEqRZbLMkenscMnaMlu7kBHh4yyreRIHed3xqZBrRdLaC8AVrRfrh/BqQ886LjJkPR0IHgYJZKuDN84tjRZg32/S+Cb6Eu+lEZXauCfI9kwElIkLbSKYxjVJ4+NlaVlUoQgnp9Em0Rh9QBpd+82WPfvjuKrCUlUmDePl9cKy8QI5QvvxksbG4zKVVRY4bJYJYwKU/ZgCYZ1y7KqdjUY49LluvHx+iGfzc2gTTvgFU0maijKJaAIgXVa0GMYvIbwRq+OkFiIvDK+xN8Ey2/glJdWV8SDIKyPOujFd2UI7YNo2KlFVUPLY8OhbXy2WVJ93uezFd8uE4nEZsnPL2rZp1IRrgmuinXP4esTGeyp7NstBXggRKkZNo7Tl3ER7xzeJKXfcpYKXUSYL1nrKIVZyJ1EPRXl0qFchYm16uzfPddqWaZQUqgrRXHdiLLOpivqMr2Vahkkde7axJhFi5erEKE0rGpcpzbNY8jS1NrJtdLcmQM9x+Pfmmva14PlLHVXU35fKCh6UkMwLTs7DVDHRJvNiRepdwFxRV2Wp9dseE8DnUfZcPv08p4Y=
*/