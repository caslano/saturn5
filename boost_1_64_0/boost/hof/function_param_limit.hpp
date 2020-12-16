/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    function_param_limit.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_PARAM_LIMIT_HPP
#define BOOST_HOF_GUARD_FUNCTION_PARAM_LIMIT_HPP

/// function_param_limit
/// ====================
/// 
/// Description
/// -----------
/// 
/// The `function_param_limit` metafunction retrieves the maximum number of
/// parameters for a function. For function pointers it returns the number of
/// parameters. Everything else, it returns `SIZE_MAX`, but this can be
/// changed by annotating the function with the [`limit`](limit) decorator.
/// 
/// This is a type trait that inherits from `std::integral_constant`.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     struct function_param_limit
///     : std::integral_constant<std::size_t, ...>
///     {};
/// 
/// See Also
/// --------
/// 
/// * [Partial function evaluation](<Partial function evaluation>)
/// * [limit](limit)
/// 

#include <boost/hof/detail/holder.hpp>
#include <type_traits>
#include <cstdint>

namespace boost { namespace hof {

template<class F, class=void>
struct function_param_limit
: std::integral_constant<std::size_t, SIZE_MAX>
{};

template<class F>
struct function_param_limit<F, typename detail::holder<typename F::fit_function_param_limit>::type>
: F::fit_function_param_limit
{};

}} // namespace boost::hof

#endif

/* function_param_limit.hpp
0kt3yYbi+jTtBLWHOdLnbpEXnwdJz+fZcwF70q7QJS2IwYQIbjZICfh6kcNYxy37buY2eR9N3NhMXeCT+bzN+WQiH/8UzQuHT9Q0dcdkoGUsBXYRxOLL6GwcJIQvoVzKZXgOhz/L4QdvUCrfB9aKP9zAkZdx5Oxof62AY97FiMNBFzvgulG6/A6C7sbLJHRaMcecvo7yrNwpNfcvvYN36kC1WVoNwqO9tJUcbYHMoujVOjHlDoWOg8b+FfqdX0FjaC0UVe8WYxAZmiHqGbQ/34aQOzmT3uyffSH736/BX8L355soxxKCDzqDIgZ8T3KaLwcxS2eJPV/kBoaihJtoBaKnXnzlyjgv6R9mrOcf8KsXr91IaOOOb8Ttc+b6h3Gv+7O0m+U69+RW83qyj5ZvDB5/veiH6ssxNccvL38uxXrItxN6XJq67r09Rf/hbUluGpbKFrC4C82fyHcz9yM37OiW9gBB1eq/2QLa2GnxbTliwRWppykCTaQ85+zure8wf9dZ2U0cwPuswWL/YC17HHXWRedxhxA+HJ+BSvbR8tl/ftx/APw5HTHYPMEKr3jYLzscmCs+FUs43Ss7kqbiYvbs2GEi3R/YjMzK5c7oceK8S5Db+vChXbtXa+RUkR0mCNulumBPHeiIm2+VhQM33Kay3XYZIvitavIsNhPWGcW1IM53qRPHaDs488vicSYhjoS2jYMGx8sdwkqNVwF1eqlHyAYhnQ4sP5d7vLxenMuLZh7FfQu1MQDYfq7JRvqplXJ4tEnpsRwjS3qFS3oQqKBefD9CbBiqXlcdW+X3u1C5BzYxpi5DBe+3ADsGzzbwzimU8sobTBjXcAn+W4wSnFtD8DBwEMedHY9bZZXNcb/FSpIbGZy0NNAdt4T6tkUlnseJHUhcB4ru3S+YXUgGTMGGvh0lypgeigkq8dfbue8pDigi5Ly0ifHGaVcSwnoIPLKtux9fhchtlMxZuW+h1siF3MMJcynhvdRJNOwLa2FKQg58NFueLKmZowe2U34Dt3DmruWMZszOv8WnzAAtq6sS079gEI7O6+egbamR2YJ4nTiFh5FDtoaNWuNWq3EVke2oAuB13Msl9NSL11dxOdTAl1EDP0MN9cpYQg/+DcANO7cYuEGdtMHITJj4aftvUiBEtmDHC93dKMNqXKspepXmVNE7OJFuxmhmWSuRr/EiJFpo5yEuukO16laiYxKaXFwaMXt2FWrnqxd7rjBJiE2DGXkcXKAMAeR36UjfNowORcBFRoxRaLVD3GrL6zgnNlA7BlktgM6BP2jdHLb7HHM0ZyIodGRQYEjoSE5gQOhIdiA7dGRIIEsrADzR0XT0HSuCLmQgRZlhKdS8vIhaG50TRFazkVcptFluHFHHO5MDt8uOcOvlrM63awkKIf0W1FlVXd9DajQprxj/zSeY/1m/evFXEPHgmOyMr3fD/CPUgL4KA/qFTekWuzzQqMbilF8vei2TC56fF0aPvvdE92Jd996YvP7dflOye9qOZPpwJdP/4cT7mito5VtNnJLVdaQ1WfgUmeNsGUSIu75O3OalbUAdaXQX2z6P/w/xdQPJm3bxXMIGgY0sR+bbvmNdyF51Wsl4ovb6oo3oQmVRTLy7Q5FZtTrxr14NurTsiwch0t3z5E1k2xmv+i0osvkGdnsJlfi9ICkbumOMUXxiHaLCQNZ9Mi+osGoDPM0WXjcoK5+RlbNOW8QAtIYZAYawa5ATH7IffAoJUL0GqKs55grEpD4BqHNMUBeb/MQEeP98djK8+7cnw/v75Sa8e89meA/d0AO8Xz/bhPd6huJXkrVN9DvyFmu5Q1i9iIL2Po73KMfLYbK8Xty0xbCSgcM=
*/