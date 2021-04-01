/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    move.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_MOVE_H
#define BOOST_HOF_GUARD_MOVE_H

#include <utility>

namespace boost { namespace hof {

template<typename T>
constexpr typename std::remove_reference<T>::type&&
move(T&& x) noexcept
{ 
    return static_cast<typename std::remove_reference<T>::type&&>(x); 
}

}} // namespace boost::hof

#endif

/* move.hpp
zfjZFLHaV2e1FtU5bIpTCKco8oKZFzJje4vvw7Ze9+rBTaFFVVtRBBzSsrdyIjRxt0hIjdfESVqz5R3lkq2fu2TCJ/UeXQX46kzzo8c0RMMS76UOWYPf6asFKCQKS4c/9H0Ue+I0ORe+q938kuHV42yGXugr3AqHehzPqd4+iDZ9tJaiRBeDIM4FESAbG6EK1fHwwMwVOYP+gYFiuCjj94HdvusQfj7oHzZkFw19zy/IdCNzMEBAsgF2LOGyJlLRr8E2Dbt78wYoGiWAG6ZRIBNICId2zpMOjtxqOPmvqfYv8OsFheiMrUvV7R2zMF7Z7aAFOa5piEisnN7VkVf7gBrblmH54cXt6MO6XFE8CYXhVqK5bjpmV1RxxB+ODM306uUlIOEBb0bIF+4TFOJG/B24miYYgcT2bi/4gW0W/+zlOedqMLJPZ+9Nvg0MckW82YvEbq5+4rqJ1nBt9t7rg18LWh+MiAH/jrO64m4FC/dwvrX3ytdzaGTa+bWLZ4dWuTxuLTxHPBlEwLWlmTRVe+zER0VxT4Wq4q878Y6Jwkrvwb7G9adpuugePw==
*/