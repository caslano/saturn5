//  (C) Copyright Nick Thompson 2018.
//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <random>
#include <type_traits>
#include <cstddef>

namespace boost { namespace math {

// To stress test, set global_seed = 0, global_size = huge.
static const std::size_t global_seed = 0;
static const std::size_t global_size = 128;

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
std::vector<T> generate_random_vector(std::size_t size, std::size_t seed)
{
    if (seed == 0)
    {
        std::random_device rd;
        seed = rd();
    }
    std::vector<T> v(size);

    std::mt19937 gen(seed);

    std::normal_distribution<T> dis(0, 1);
    for(std::size_t i = 0; i < v.size(); ++i)
    {
        v[i] = dis(gen);
    }
    return v;
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
std::vector<T> generate_random_vector(std::size_t size, std::size_t seed, T mean, T stddev)
{
    if (seed == 0)
    {
        std::random_device rd;
        seed = rd();
    }
    std::vector<T> v(size);

    std::mt19937 gen(seed);

    std::normal_distribution<T> dis(mean, stddev);
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        v[i] = dis(gen);
    }
    return v;
}

template<typename T, typename std::enable_if<std::is_integral<T>::value, bool>::type = true>
std::vector<T> generate_random_vector(std::size_t size, std::size_t seed)
{
    if (seed == 0)
    {
        std::random_device rd;
        seed = rd();
    }
    std::vector<T> v(size);

    std::mt19937 gen(seed);

    // Rescaling by larger than 2 is UB!
    std::uniform_int_distribution<T> dis(std::numeric_limits<T>::lowest()/2, (std::numeric_limits<T>::max)()/2);
    for (std::size_t i = 0; i < v.size(); ++i)
    {
        v[i] = dis(gen);
    }
    return v;
}

}} // Namespaces

/* random_vector.hpp
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
*/