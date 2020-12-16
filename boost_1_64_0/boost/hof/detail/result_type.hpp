/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    result_type.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_RESULT_TYPE_HPP
#define BOOST_HOF_GUARD_RESULT_TYPE_HPP

#include <boost/hof/detail/holder.hpp>
#include <utility>

namespace boost { namespace hof { namespace detail {

template<class F, class=void>
struct function_result_type
{};

template<class F>
struct function_result_type<F, typename holder<
    typename F::result_type
>::type>
{
    typedef typename F::result_type result_type;
};

template<class F, class G, class=void>
struct compose_function_result_type
: function_result_type<F>
{};

template<class F, class G>
struct compose_function_result_type<F, G, typename holder<
    decltype(std::declval<F>()(std::declval<typename G::result_type>()))
>::type>
{
    typedef decltype(std::declval<F>()(std::declval<typename G::result_type>())) result_type;
};

}}} // namespace boost::hof

#endif

/* result_type.hpp
3YDXdJxE8M+2Tpks7xXm8y/S9Sv9+L4A1A3m+f+j8P6bQTxZLSbN0jL3uKygusNUmNXudlckuGE7DpScrP0wwfKp9fK3GrWaXxCr1by3YjYMzf/9bDWfSTWf9yLXfI5e8/fv19bLfFgqA7U3hle8g3FY6m4tXr4DbzjoOndgB+/MTUisI0nYEipMyK2ez5tC+fzdVi2fNXo+PZTPEWfNZzblc9l2zmeens/2fZzP1k1o5KprEzzpofhH6fHfq8c/u/UncXwVZr4pHWvRxTPhkm96mB6/w48X47HaEUt+LPmFpaVXeS5xKslhOeiJHCjP6xHe0TqOPVtpcNso4ujomXh/S7tmfcy2+AzcRTdwDjQqiVg8sJ9Tu/gB16TjgXpvoBkcHuuc3E422DBE2RaXy/NBDprMboxhBZXFN+CX1SjGlYqRFjrQSy+lYkcin4vIqR1lp8rPwb334CvBjVDgHyITpHNC44Nvkz3u1YrkG5Bcmm3NiF5LutbE4rdnTUkvmFypGRGDlx41JT2XlMTWjCAXe01JjyUlcTUj4vBiqymxLykx14ww46V7TYltSUl8zYh4vCTVlHRfUpJQMyIBL9aakqQlJYk1IxLx0q2mxLqkxFIzwoKXrjUl3ZaUdKkZ0aWmpKt46kS7Jh14RT0MRTOBrz7ZSXnlqjowQNWFlUwvsVTkb1zcRrl9tz7kfh/cqTrkGrBUpOzi6EXCK6hk5oRvg4/SCo9bZJ5kp6z9rT8CaZwoxjsFFdfxA9K9Wj6kiiHs1c43vTuV9LDeYH4eveGU3ht+WDFbTHkjSF10jFPJkF20ZC9/N60DYmSvuqH0+qs810b2qvXbEM9yPZ47EU9vPR6HjCdWjWePPK1qF4ePyiM8ZjLcR7cYi4d3UqeC06/wQHvA1MNgxvtWUj3AkgC3JD9tpptD+b4QiKMhZ5bmNW9CF0b3ddaOkhUvvnehpoBcICvUjgotE6tekhX61C5VDnJxGcYj8c6HsjLb2/LGiTN44Xr7kKmW0Cf55Cbtk+wap8vF6ZP/NjPOyUpQqwLsab0h+Qks7GxloggzQamYuokjRMmyA43yTOOaTq6V/7Yx/X8JpL6D7Xj4/GTno+aadkOsO6TdMFXVPeh/kpsU08UJc7h2Q1fQtZu28kNd44F6rWt0at7JrpFTZAtVfDxFi7nhhIyZ1SJc4Yn/MBRfsR7fGT2+71N8B8GnnkPR4eqtUYoO92K0VkwhVuzqA7y+C8vLNZwX7RDzlKkgpZ9o/+p0H0L87sKjEfwu7/QGJqkCAxZZZZcqTbQFwIPo71/jfUd1tc+n6bGASVN5NxLoyBoJdCw6E0cXZzjIzlQs6BpvNYa/ZkfYGvrgs1odK3odKxWKU1SBZXdFTNz7N0dN3Nk8MmdGcG+Hj8sUlJnmcPHDXpC1HnNdKPVyPfVZoR5Dqccidc1Ohxb1vWrUUnIRWXzvTFl0ZbYWD3HmJcxZWBcFqTagYQrlqlDahzdoac+JLPmPwJy7Rdf9rCYRkYMkNQcucaAvgszX04Lyr3gdAzH0huWNpYvpbFzwGqdyBFXFg/HhPcEgDXqawiBFiyjXHfvv5GdZfvrm+8hcPi05TS5b7fPIdkXoX1ehnOa8r4IHKnPNXyM9xInR8BBG6LLKAZ/iKlBX2enpEHbi6NLm/uBUneqW3YgG3v2mOvwum3x/bl/IcVKDzmqwlZeO23vaVaf3T+iafJeTk2mW7uQOOdk4yhcPhaLcs0mP8ijLwE4/G3K882SItYGjcvv39Uhv3qBHuo6cMn+gO73ZqTs9ZIqokkSR/TEKn0yF//U6DEyroW8oNyixw3kjy9rS6OZolziJL8ApncSROG334gY=
*/