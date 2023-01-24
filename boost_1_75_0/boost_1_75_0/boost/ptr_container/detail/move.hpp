// (C) Copyright Daniel Wallin 2004.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// Contains the definitions of the class template move_source and the function
// template move, which together make move pointers moveable.

#ifndef BOOST_MOVE_HPP_INCLUDED
#define BOOST_MOVE_HPP_INCLUDED

namespace boost { namespace ptr_container_detail {

namespace move_ptrs {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)    
#pragma warning(push)    
#pragma warning(disable:4512)  
#endif  
    
template<typename Ptr>
class move_source {
public:
    move_source(Ptr& ptr) : ptr_(ptr) {}
    Ptr& ptr() const { return ptr_; }
private:
    Ptr& ptr_;
    move_source(const Ptr&);
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)    
#pragma warning(pop)    
#endif  

} // End namespace move_ptrs.


template<typename T>
move_ptrs::move_source<T> move(T& x) 
{ return move_ptrs::move_source<T>(x); }

} // namespace 'ptr_container_detail'
} // End namespace boost.

#endif // #ifndef BOOST_MOVE_HPP_INCLUDED

/* move.hpp
uo+jOqs+foZm7ZeFOYo+CIO4O6nKS7wgDSc7mVPTkFt6QJ5PTHwv1O3ts8xRMEuQPdaSm6/6HsabzQvMgagQJFbGJCvMbYFJ3jFLzFE0T5RwOP11Zo01fPigdERTIwLDFhmisCsdpqu+5SKCEqerpu6LzXaFJGg8iYCpN/iwUXPj1YOdS1hz/GKiHBmrdZW9qL85HYWH0QJt5SP+POnIvuvJN1j20zyU7QwvCo627YbdAYk7LZHgkHjaW/bxOkVDqYk8Ykk9zcPNyG6Yn9i+GK6BtjpvCTh8wEzVgoOtpT9hmN1zpT8dSdklunpSiRl0293vWSI9ThhjGJ+fc9AasuHLOnhNRGwokuM1uQ6GWVHf0T0RXf7kpyoie3lZ211YzdBGfbvXRKx6QacyAiLDmeFBUbozGMxovxDPqOhARriuUxgzyi8khB753wzWn8m2flkht8QedXF0c0fErDhPTbSgno3qezPWzQTy7GhlK+oqKzee/ThYQjILWstCHSvkGJJYS7qK8v3F8rTeHvahfUD3WFr9r3IZEkkPDgwJQUrkSKVfXQs0lx4zrQjMJbenPfBlj8E0SMStQVbU0x7czOWS6GpFG1jmGR8DiUhZ5mmLeeHuCA96Z7UVUiVkvpFGx87zw6D4L9qGnp9kFrjXPaLZlfbA+3q834pgBQG3+8riva8WDuPBsaesCNb/ccPdvXbj0I0wMdZWhnDJ
*/