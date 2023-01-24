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
ultEgQ9pLeXF8r2mlVeNIdjeTzN07UDzrygtdZD2N7FQl5lwlxkFF4NvoFqT7WjKIQuOOevCUzlBfhqbS2ZGamQ34vwGa1NYmwD1rnHtX7Ik3iKITRKCA9yvIFPVUo8XJylPg1srCJAeq/2h5YeThGtN2T8uuEJc6c3T+Pfcs5+pJ49jkb0bSzkT3nbH/SumhkAqfkmztcJURVoqIIv2L1GWmdR3cxyHgndWnm5bym2tJK5rSRDSbqrbfqZl84LFsfaJiVgwOUJdxNuoUVonLHN3mlbaBfyYtiF45u0aSL+to5954CNXaAhf+Yo8kqzEf681cicnzfc1G3ZsJtJFvOcU8r6J4KNocwU+S9gjfHAleLVeV9uPy81CdnQaInw6KDNoZdk8rkblUqEulHEsoVaT4RwRCFpGoLnI1N5N8/pBeWPQbMcSgj/piOYP1m1A/k0WW9amT79CNKdXTPA6v08h4uussvt+yy7iLxtX3EN7WNPn3O+hxr5cISdv8I+Y+lkBesdiztwCkS3Xs9RLQ+hsrXsoAotk2HXj4UgwgXpQm2BN8HJrI7KN2CXMQXoKSgjKWgQf5EcTamN3eGTDtcQEzMNYl7iIlQqpaCUzZ8131huSYy0zZoQojAhPYAVom+t1g1tc3xkFr1hhvVia702GF6i7iJc5Q7s6PZm6XB1DO/Qn9+aIUItBon/O0TKy37D1OoQMIcrxy4KG
*/