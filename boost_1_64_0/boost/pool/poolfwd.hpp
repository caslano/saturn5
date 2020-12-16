// Copyright (C) 2000, 2001 Stephen Cleary
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_POOLFWD_HPP
#define BOOST_POOLFWD_HPP

/*!
  \file
  \brief Forward declarations of all public (non-implemention) classes.
*/


#include <boost/config.hpp> // for workarounds

// std::size_t
#include <cstddef>

// boost::details::pool::default_mutex
#include <boost/pool/detail/mutex.hpp>

namespace boost {

//
// Location: <boost/pool/simple_segregated_storage.hpp>
//
template <typename SizeType = std::size_t>
class simple_segregated_storage;

//
// Location: <boost/pool/pool.hpp>
//
struct default_user_allocator_new_delete;
struct default_user_allocator_malloc_free;

template <typename UserAllocator = default_user_allocator_new_delete>
class pool;

//
// Location: <boost/pool/object_pool.hpp>
//
template <typename T, typename UserAllocator = default_user_allocator_new_delete>
class object_pool;

//
// Location: <boost/pool/singleton_pool.hpp>
//
template <typename Tag, unsigned RequestedSize,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32,
    unsigned MaxSize = 0>
class singleton_pool;

//
// Location: <boost/pool/pool_alloc.hpp>
//
struct pool_allocator_tag;

template <typename T,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32,
    unsigned MaxSize = 0>
class pool_allocator;

struct fast_pool_allocator_tag;

template <typename T,
    typename UserAllocator = default_user_allocator_new_delete,
    typename Mutex = details::pool::default_mutex,
    unsigned NextSize = 32,
    unsigned MaxSize = 0>
class fast_pool_allocator;

} // namespace boost

#endif

/* poolfwd.hpp
0K0eXdrYQm1QWr9y9ErnoX+nMg6XWH7yvKyDpDiGb2f721GNnxxzYoC7pupb+ZxYGhMW+i7KMf42YI1tCc54rhv2JM2wI2Ea0r6wn/LPZnDFdTHOa8USyROisYcp9jmNHMoNWvEo3WpqbOJga+wWq66PBiziwl2scHTI66qVebiC3n6Rie27rtwO3h9MCcHK+KyRK3fRwSZxF7dN0kvsJg4F3XPTNYo90rdtn7V1qbHzCj1Z0fibHHxb9EmI0WbwMxqvdbnZqWMrUmxBBV7ANR0c65TGXnL07oquE0UrRctt3YC22FscuT0i79oEu0GLhFzzJi3FwnWbVUnZFNXw/sL8hupc7F3wLzv1lM915H1WQRllKPF16ja3/yKcu0jTuFHX6eTNfnc/cscxlk8uhFcrxsI+7qXnna00y/H8p2M8HivJGqinePVSrl6/c8fNzjnXHit7nLuU4VCzdTO45/G/QYNpO2iOxX608nXWdPhMVyjejg/K/+y+wQamSLtAPTLnroHNHNuzNa3oWzl/aWMrdDPpkL60SHmfE8NZkEd9EdBTcHuHeo77yppG4DwuiId9yXal2Xl/zn3bLUIgMFwUalfjFLmq9fu40w5t0xXysdAglra8wp7S2M842BQxBhkCAU8Q6OSU1uXLri5t3FZpG8XDPCrI8RfV/ztz7l2EKAvTGP1qBejFebK9IOvjL+bcuxN9nwh5VB8Pe6FjwxKtmMy3P/9MWg8svkmYiUK9tqnqrMfT76j8w11YY9fT5YFwnBv43ma9cetQhFVdFEXQnlmxLLTOO65z496bJkxgKp2FPWQcKLzOu69zyqiKosY00gXtwnmxHc8+t5y0E2nR5F2AVy5MQbydZinPc4btSpTBZTMMzQ13/g4otgmKuMjyFKG3Lxw8gi0CCN16C7cOddKnQj4LHXv2PuYNXcozK4oqwh4M/XuJ5PHV+px29YGlDydLWQU0PpTaP+cp/mAZF13VVFmA3bCr903XuWMM8Y45tl/KlCmR+iSDGcvGpVvXLoe7sSowyKTZG4cCaWim3sH8qMsjwlx0JQbbyLIGFreMz7v4DB2iFUmvy1BKuX3iNpenjMsqadpYF3LSx3PHdeyuUpekRaE+s6oL57ns8hRlCx8AwpBHbzGpDeG50+UpCxGLOBGqIFUhxjN5IeUZnguv8rY35Zz08OxyedI0a6taqBl3m3bb6/KU8rEO0ReGSXjqs9/l6Xqs5H3dBHQ25OMvoDzPKSO0WlImeD2MJLV9jJ5H7oX/T+bnz5xdm58f30o9u4blR9N3cvrKAFjU+6xI7Z/i+Tp98eCQOX7jOOXOy+l38kiFKxzcyfWlpcmNWsbcSBNpq55nQOKLpBiUHfZSnV5PX8hym7cJPLhtFlw7i//OjH+uIm5GOhOOHLh2Fv/bf/LaGfx1+EMu6bSdLlJ5sw0OVuFVDYYkokmnfAiPxD7v1kdgvegkVgk5OQ/QuEf8NGg7X2BoZ7GDxPVvxG9uyH3fzgd+HXSTnxT3gWS5T1J7w9/h/w9zqGP+1vmTywunNuwecvMuHKc8fXIfqjCzd53GoJEN/WfTdHwsq0twN04fb9eOOZ0s7hdenNbY6ry4w4tDI5H6b4tB4DfKfKTCrd3dwaGRbb3FPThtfmH91DlTxt57TtGHEMR56eUa2u/JY70GnCTblYTSP79T0+3MSOmz96J0NTsT+tcMnVoYlt7cW9PpFGLpd3C6KuCpij53H0L3G31ozxH7T4MdzbUJ0fPm+2oanWHwXbWe99N01yKjMnbeX2OIZUHo77T0MyuWbvTb9QBNVyYD/Q6GZlfkCeFNdhm6Emx1/62huavuMCYV5qYHaoynBYk=
*/