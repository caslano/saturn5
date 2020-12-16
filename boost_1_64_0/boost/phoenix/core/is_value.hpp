/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_IS_VALUE_HPP
#define BOOST_PHOENIX_CORE_IS_VALUE_HPP

#include <boost/mpl/bool.hpp>

// Copied from is_actor.hpp

// Note to Thomas and any future maintainer: please make this as
// lightweight as possible (as it is right now).

namespace boost { namespace phoenix
{
///////////////////////////////////////////////////////////////////////////////
//
//  is_value<T>
//
//      Tests if T is a value. Evaluates to mpl::true_ or mpl::false_
//
///////////////////////////////////////////////////////////////////////////////

    namespace expression {
        template <typename T>
        struct value;
    }

    template <typename T, typename Enable = void>
    struct is_value
        : mpl::false_
    {};

    template <typename T>
    struct is_value<T const>
        : is_value<T>
    {};

    template <typename T>
    struct is_value<T &>
        : is_value<T>
    {};

    // This does not seem to work.
    // There is an alternative in value.hpp which does work.
    template <typename T>
    struct is_value< expression::value<T> >
        : mpl::true_
    {};

    template <typename T>
    bool is_val(T const & /* t */)
    {
      return is_value<T>::value;
    }

  }}

#endif

/* is_value.hpp
JqvJbI9LO+yNehr1WrzONqzvgPyRVWKW3evsUpzLyRyY6WNu3kOOyPiYTerqvh85IuN19vpw8jaMNRmfRx12dmmC8VT6siTB73vMI8XqbHsxFmOtXNMm9SY+E04l4zlaPGvm79hTyaowc+oeNhz7Jpk178u+4FOYf8o1b29xWYj1U7nm2J89X2NvVNpVWRlojxwFmbYzHJuH85kTGR/rM5OGdsL5hYzX0rOmVW5h/pHx+3108lxjrJ9klsxCbQJQZ4HKNTce/16HZycyC2bTDp4Mwfwj43nwX+fVEXlX+nLLM78/noEUq53pgTN0vGK7ng+4gnmkWH+zf1XEPFLG02bF85fYGxV7defDGJyJFOvWZ8Z0rK2K7W150hJrq2K/hZ8rxrlnoKlt/LHrDKy7il3Y3rUFckvG817dpaQO5iaZK7NHmyfhmqFkvHbjt0Zg/xtPxvNewbqwNZ5hyWqUWXWyHzfd+wnPomQtmA3LehiB8SRzYxa44qdP8X6CrBmz4cPq+iO+QbRmMRu68Cb2AD8ya2Y9j/x0AfVJVo/Z8eKdxudwMjtmtsNe9sL6QlaF2bUPPsHcTFDaJb4paoXnYqXdojWNPsSzIZme2YTPH03Gek1WnVl4vymdsV4r98u8s+oS6mUwzT9m0RNGJ6FeyHi78fOa432rJ5kTs9bOx5bhTERmYJZ7sRnGOozMlpn5wxsumLdk1Zi92B+zBuNJZs9s7ybDJzjbKPbznfWz8dxI1oDZcqfqWK8Lyu4H+7T7BcwxMhtm++rMQ24tgk3jKz3VzxFjRsZz9Nn5E3moQbLazPotbfoYayRZJWbndzZbiRok43OldvcTHTDHyHgMXSbkrMC7ILKqzC6lLjiMPY6Mj1n4uq3f4DlA6Wfz7EU+eMdCxvM3rer+QdiryHgNJi351BrjSVaL2YffLM7EmA3R6eowG3g65DT2FTLez5F7jmB9CVTaXZnWDrUUTsb7Mufvql1QS2QOzB7Qq3vUEpk7sxh/488M5ZLxccl7Ows1X0zmyMfs41C8JzIMNY19uq4f9k1PxR53mDwL8ZFVYRa+YjXGOpSMz7/6Dyp2wzmSzIaZfnnQaqytZAZmP0TuRrskxXr8cvss9jgyN2btGia5Yh4p7QYeGjUTeSfjechpX/c2nsOHmdbny1UpnTFXyJyZdWgwsjLGhYzXYKUvh+/EuJCZzIcvPbdivVbuN6+d9wicC8h4bpNrn6yIvV+5n75GtwiMi9JPRx8n2FUyBz6n7b22YlyU+1UNemVcd0NMa6nb2aHDsReT8bzf3OljhbMwGc/DxL0VPsc6obQberYl7hdHxvuSsmb+3zjTkvH63OEz0QPnVrL6fFziOm5BfGQ1mZ1yqTMdef/EtCbuTlqKfnqS8TFLf7nxN6yRZDy3bX+e1hvP2mT1mO2s0Mr43QEyO2ZJsybtxplP6cuIgatCsBeT8djvHl6PuZKrXHPG/VP3cC4nq8Psz48PmOHsTZl0ZVZ5ZU/jz3WR8Trz75y8BLGT8dh31G8fjtjJGjK72LBSB6wFZM7M/r3arR7WeaUvQ4+9qYqzKRnPQ+iuJcdwniCry2zqmYYJyO0I0/F8NdnXH7kl43U24drhRMxpMj7WrokNDFjLyXjsrWo3SEF8SrtZPmdOYz0jc2E2MN7+LGqXjNfLsvioYqzlSrtbFrcQn3OoaV9S1/3+BnOTzJ7ZhpM3auMZloxf8+1fXX7BuYeMx3Ch+ul2qE8yPmaVZn1ig7WHjMdw6P6nWFvzFYt/kY93jrqRpvtDv/P716A+yerz/M0wG4b4yHh9ujz9biXO0GS8n1N8RzbFsxoZnw9bfT+sjfyR1WT2l/72HM0=
*/