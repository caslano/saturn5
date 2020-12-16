/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_AS_VECTOR_11052014_1801
#define FUSION_AS_VECTOR_11052014_1801

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/as_vector.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <cstddef>

namespace boost { namespace fusion { namespace detail
{
BOOST_FUSION_BARRIER_BEGIN

    template <typename Indices>
    struct as_vector_impl;

    template <std::size_t ...Indices>
    struct as_vector_impl<index_sequence<Indices...> >
    {
        template <typename Iterator>
        struct apply
        {
            typedef vector<
                typename result_of::value_of<
                    typename result_of::advance_c<Iterator, Indices>::type
                >::type...
            > type;
        };

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename apply<Iterator>::type
        call(Iterator i)
        {
            typedef typename apply<Iterator>::type result;
            return result(*advance_c<Indices>(i)...);
        }
    };

    template <int size>
    struct as_vector
        : as_vector_impl<typename make_index_sequence<size>::type> {};

BOOST_FUSION_BARRIER_END
}}}

#endif
#endif



/* as_vector.hpp
z3OY7DOr7ntJ8uTaB4NlH8TKT5REaQdnRWtXpWLasA/k3Sk25eUpPu6HXjt82w/G61aySXnHmpyXDpPzL0j2jZStnNO1zyerdk2Ylz6P3Gj7yuQcScQ9Ld3LZjky0/MN1xDmcxhp1yCTY8tucp7pz4Uzsh9WyXfSMsJQ8nex5jspz7HQv/6InseJM0+XP/leysjPy/E8HmJuVVcwUB69DpDv4PKN7nzkZBUU8NPKIyt111Uo+6Wp7vtR/x1yRdJcK79FypT0Wc6xTtJU0+IbUXllT93tEaX9oed1VfbjnJr3+Mj10/iuGjkODL/n9Pl13Fb7t9tglg1f75FfecVQ3b8dvP6GMrx3SJ+H8Obu99MTT8Y+6kX80oc98nBDvx8lD7p8Gfu4ZuXa03M9no/frX3PetYLnZH8rpD7/aWEMSxbWarll/XbeLlQtp/HdU15xdc835f86+tFeGLfl/9rfWtl3n2e5RoTpCb0urSNfQX73qGcmO58UqJFcij6cB1sxXXw4Gr1OmjP5Eoo81bLPFbETPneN26TXB/vVcs/WrZJ38dY+T4xO17l+0C+o6ReI0iuhXJtNJSZw3UFbeV5/czRl+MANW987xve6UV+iatdu0ery3Hxq/XbkrJj0wznU/fb1QI7LWV+EvuxLbFr9GWunU4+tcn+wdrabbLvN5RjscmxHV+TV6kvMZa53eHeVqtuu1iB8R1pDuN145xsZ5ycs0PknI0t1W8n3c6Rs/YrP2fHyRU9Ra5zSXKfZKm5xtDumXslH64v/twfcQ64pt/K8fAJdlKubcv06cop6MM5qBwPE1dox4PZuab9ng+7w/weyHi+RZucb5mG883st0icyfnm8OF8C5Xy8/YbMd7LuRivOxf1ZfxaK7WAnpEy3oXd2J6rK/RlLKecj+dc3krjOaeV5zzzc87bPZv+msHmG3+Hy36Q+yLjvZmUn37/yDmgLz9b7euQ8w7z8/Oi/nin3NXTs+5j/t91frrze0ny20O+48Llt9pF7XdIQXpaYX6Wc6Hy4KTuemfT5ya660H3NurCMxuxDE7FyUod9041vTweGall49vxkrLLcLyYPL8qrnl+Je+VMC+nNcZjw+N4UQf0lONA14fG9b2iu/Yz36Q/RzR2d+Vrnqy7YcvLlFE45dGZDfhWJduhu8ZJ/pSy83i+VSXlN0V+504gJHRl/tPueu76P3PzfNaXItctXX294diJC1FXmCXXdjthKnHDd6t5ob5ded6Wa0tzLPSlnYo7vT+Guc65AmfN8St9ZAry06SMwrVyTvE4vqpCah/Po9hG6zJ9njLy0/34TV3V0vwZoLWttNOWdjqbMVHZF/rtl9/QaXn+lQHXnVr3W+wXud8yPiPKKrAVPxh1n+G791Rb83PbsV6fv4KsRX6UhfG8/ox57Rp6bwNh/m5Cb20j/H+n4JfVZsL8nY7e3qHofxsLf989aXVt74UV9k1723569HKb1J+fKftWz39/2wvzd2f++9tkBBOH9Vh3jLh8IDuqvPfZH/zu7xvv+uraavyLvXuBa6qKAzg+EhVKzQcKKspAQBDE8VIERBBUVFJEVFQUgaGSKAgD0SztbWVJaUllRWZpL6OyMrOk7GmWVlb2trLSnpRW9u53t//uxhgopT3v+XT6bqdz7z27bGv/c885d7V5XtRLK99OnXJ/vX7iWa3eunZHfe8/NlZjpk6uCcm1oj2cM3fMlA9YjQvzcXAdeuMt6I/rMQhvxSS8DcfgBhyHt2Mm3oHfoEEn134wSo7TCv3lOG9RzxPfxgH4jmyXSK6R7SbLdvb3nekpYzW8MQx7YRL2xgz0Qcvx5ToLBjs5fq68zjx5ffly/Cw=
*/