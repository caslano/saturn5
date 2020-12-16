//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/find_if_with_atomics.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) for which \p predicate returns \c true.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if(InputIterator first,
                             InputIterator last,
                             UnaryPredicate predicate,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_if_with_atomics(first, last, predicate, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP

/* find_if.hpp
Fd8mK4aaL2ic+mauuUbsi2gfCXzrjLRaEK+nHNiT4Z+Plt26ZXTgn4JpDJ0yzmobfEXiD7Eq8WW3I6WpYubq2WYt/yoJU8S3Tpfs+51bnfYR7dun1owXYhaSV4pMlM1qhA+1X+1+SaeBae/Pi71SyH1qm8Q/oVR7X3X9nrYDU9cBa0FIX9yiqCOv8CDMkioRt2TcDg0VPepMNb3Pig+eNc8Kx7qk3XEqJwjn2srexM/YH9AGaKSh35E0PD0hXsfG+WKfHd6NnF0QHuY3V5+YNz13HD9NW9C49VRHK99UxH5deA9yelG4u8QzinAyns6RcPPCe/Fvj3CXfR6CuNfx23swPZMaM98mbhD/GeEe/8viZV5E1dnfS3Q8l3hsaDNlXPu8vtPqOqGrX5B5lt+7/zjSsdfr/Uqukx/elvG3FZsSpjCe1CFUM5kf2eYfaj+j/E75PbwcToA/YN6KNu5CKlX8Pxa7PR9rqmNSainmXkekDLZ9N3bfXGz482Y+ZeZOR58rOe/qbdzaX+BzO3nAuJk52x22W3tLx8Uk49ZV7N/u99m7SJzFL5hx09MOrXjcVvu5eVqT2YMQ8G4d7xgnTbvTsdI5/uo3Juhxk/ZivjHRRnCTNuIYPzfoQ/2Yjp/IEuT9K+G30ne8k0F5AyvxDmbaSC8J+5B1OWPeeoy2NU2jcajxU/3rGT3bF4n9gJUtqbmCvUuZ9fA9JOxeaxxl2YzRuRdp2ntI8yt6dXkT06wjHSP+Ixi1z5e+lEyIkeK2lTC+vsb1ps3MNXMQEyaDmWGsece5TdzcuIyJCdN38jFlfC8PnJunBJmbp5acm5v4+eIuZZQxcqjkiXfNgPn0Sf14VI2MtoefuJEvcp+TX5L77PcZMeT4qGEXhPqOqP5DzP28RezDXJ1c8q5p9sB9f1D3pwSZD0826Vxi5u2Lxf662lk3/Ip+ywqcH2t7XCDhtyPfryRxhpk0e5p5/G/FfoO7EqdRxpr1thPy56R7X51V/7wZFyMC9r1+oum5rW7m3aHty6Lz3Df31nIODnLNdlyzj3xql5mquI+i3nDjF38a9nr3C3wXCDz3II8gy+VaF1uMy1wPN1Ovl1h1TfjJmdMDv9Vo/Mcl/b7uN0mhiisiMA0p90DJYJaMGb4y/lWuO1Xt7HOX8MVWrHnesMM43TtPi9XnaLFc6053qqu7uuEo8boj464e+K4g9VIk/lHmPb+mx07YWPGnJ4p9nZVEmFgJ40wz1lkH8n6qZ1U41v7iJnMSDa9tQPqeaX+jpcxvugLbn13mvOnZk6TQJfX1kx7/mHN7dIzRfMl1zP7Hh+Q6rQhbQ8Inafgr4z3tT6YxnsmUvHdlq+6mu6XMncQtVmVSW8WtuRWvbhGYw3IPRlpx9AnCSn/dgvmzXLOupulN9E2JH6tpuiS+lJm4pCnyGuJqfbejPus6v2ea8pFdLXuaY3+qlNvMlZ6VPHRnhIgnpTD9/maPE70ZX6vr9/W/Yz7DXIBpipnpqWPoM+nYXdBj6GTOdcsi7wqtSzvabevS5tqOPYcZ7pLf7Ce7S77T5LtLvtPMdjvfaeIdOtfNmBPw/dW0W6MDKsGbhoRLNnbT9gLOWKLd2XNxnROYNme+4Vwp+TdtS9zTHHnAOeCb7RbdB7Be5ww3++YMr8qzxCO/ONs3Ww2XYJ4TyWKfz3yeGQIm5HxBwjWQeLWwXyz2uVYn8jYFo3omVJ5gz08uknDX8NyLtCZhzFxB3OsFnn1jZCILxT9G7TxRxE7/MXs5GBo9pfWLc6uEiQyMY77bfyLz4NLrqbDnB6Hen2gLZn4g5ZZ5QNqrwd+VEhr71iySBxgNm1OZn3vvnfeoMqphEpI=
*/