/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ADAPTED_30122005_1420)
#define BOOST_FUSION_ADAPTED_30122005_1420

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/adt.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/adapted/boost_array.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/adapted/struct.hpp>

// The std_tuple_iterator adaptor only supports implementations
// using variadic templates
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/fusion/adapted/std_tuple.hpp>
#endif

#endif

/* adapted.hpp
nsLtrDRLfZYYP+tubcbA6lFZLotKgrFrxs4uPUHIY8eUM2qznmCD3Ko83jDOtXye9LVfNzHtsCraRf2rp8dyhebOvPp5Dio8dtfdIRdsjL7ZK8oZY+VrCzszPZdRN/g1n4r218ZRnC+jGDRG/WMZdYjTXDeU/qGxmtvYlBN9VaE0tV7ct5q2aeOdbDuaNOtRikirWT5qw9hNtcepUUweK+Q2y4Vxou4sl1fDL442rbuFjBvU6YImLoJhHCDfvLatujT243bDXKF5acqzZi5Ys4J+4Pbty9DX3v7qCVbNbY6+oHL5xsw8tXeFy6HtdpgdQ1bGQB/AncdYbo5puFGb9QTryxxDW6APuWzUBlxXbVPu81mam/NaZnW1XIn81ssF6ykd03hxeF7LQZPWjer+hK066MYmSJPbC3XK0n+cp59eK+8gNMbQwetsXyxpMErzVuoxsOIqHdKLrOGSYz3ZL3Cxpsdr5GY9wWq5WyyNQDnRdzTO0Ed9WrcbojhFxGE+Bi7iapsRfs7bJ8B7wimew3/N4TU/HocLuPNMq9Sv84bbVecLjRWl79p2Gj9eZ938osKZ5ouL/BGf/DrfeM3SdozX1vR4ieFIh/sxw7rxZ/FR+2QMNwea/FeUK8oX9IP4EdBGxzrvXKM4L7R9hjJgjDjHio6JeD7Cz323OuZAhrXbVUbQSvBnWA9WTY+LWQ6/Oty1E67Nm+cVz1/wkoi3ZnoezMfjEfkhXRqXWdZilBvxQJ913hL94Pmv8WK6SbwO9fGsn0dAPdP1+hp9rOHiPnbwx9SWs57xtJg50MV38X8GD/kYfDf8ymMArnPHT8cQj2gT6xOyrBGRP4M+Afk63T6a0774KZoorjcfCueNDx6aZfQs/fB344m2QY6CfAJ/XC+UX8N53D52fWsVpeeDV9TPeObZPPnyONBxnFc/8cUtPJun/+c867LODZWbWD+TXyLI961ZXwMRuA/Ar7FeCOm4ymh5mdyKPcGK9RVOXXfXJcR/W7BG3Zbr5iWdugeWVVFXj8yJcYMw7AdfQzxrS9qQM6RhItkElyDzXIKLcqwdlePRFI+2YQT71IJIp7R+kFs9F6yej+cc/CiL9gvkUXGhE0D/wJ/36EZUz2t4yM17grVYF4M00bZoc5LZTd22EV6M45pyJduMdYvM/4SGv13VI7dQOrE8wTRVeWJfOshvgfgVit9H8SsZ4qfLDf59Z9tGORc/TnkxzzhLrsK5TtzG2k86rtXPcJanYxc8N+G5HEwnZ2mu9/nmKlxf23plWuCZV27RM3I5KT63l2NPg/PlfQWM3TRd1Xit6dK+RYft8LVnbOc7aA/QEtAKlAN7AqRjRt6o49qcN9JGmoYmbiL+lO4aYXROcnvmNS6XyzOeWYfQkh7RNk5njtJp1m311nTWWSJYZ36F+vK6tm20RLDR7Kr1VeB3lmsOa+Icr4ns0vyoIL9ZzY/qo7Qln7HdfOOn2WfoK1rvqU7oM5L/eA4218Ltrc4tom9In/YMnOlXKP28L/31o7RejlLKwAcyHHljDyi9n9rUU2ypLsKtqeFY5gd+qR7rXgE9/9Y56w7ZeD5dX59nP4joqsMFr5QhXFuX+VLCM53nvor3iN3jWeCg26zT1/bFOqC8AsZv7KKdWZ+9ZzQG7tcxtteSu2+5az63TrBmsVW3vjri7Gr1FKl98X3tWAIMeg7QAo13chTmPfCN3E/QmZDuct00PZV+iuZE0C6N9QnOLsYK8ZH3kx0BXJLbyP81z0GkyXPLhNW15Wviv/rIrehcWJ1lG8gm6tL8bp3nDAf/ymOV4s3Dje0XmC8DnOSRPqKxFaYhvF/t4SE0vZhOUp+Ad863kYM=
*/