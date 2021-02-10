/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    holder.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_HOLDER_H
#define BOOST_HOF_GUARD_HOLDER_H

namespace boost { namespace hof { namespace detail {

template<class... Ts>
struct holder
{
    typedef void type;
};

template<template<class...> class T>
struct template_holder
{
    typedef void type;
};

}}} // namespace boost::hof

#endif

/* holder.hpp
Bu5rYqgoYplCPIL1FVjngBIDd9vhAyGDjQi7EIFbLMk6aG35bPdoyMtuYxMFP4KETetswhFwGakVFmWsQsljKSUE5ISqxojkgevQuQq2CGEHHWd6k+rAeeMYOjjUAQ7WJ0hhqAdlF0WfBwtb8lY0q6bQxTLjRYhQkd9D8GiE5sRXdpxC0x/gcW4coSaMNpb1MTeWapSTb1sWazg0mGrlc/SMcob4s1Hbezk8eVyunyaPt8u7xfT+aSLfZl2M6JM7juAgNewLwgP5Tx+zFb/Id39zOcVlU8TXhvZ1UiMq2u1Q0YNU0ysDtg3Cci2CMvrEM/DfrRZgucdodw8Dp0es1D1bVbmXcwXKkWWy2eq3wg/o3EgXKYsiNrnKjbDzKXp8EcOcnpc8v4eDvo9kWIZiITfhsURmjUaCKNU0NCe71Mdz6m3ElI7QdGV9btEHkB4SRglfslRpSReShYxIpc3dihS0Auo8/enUlZuT/RIKiZ4s/1pG781giwVXMnzu6h38uK76MINhRDmm8+LExfn062IOB0q1upB1VZgsOdb3NjDT1slsa5BSxJ+p1FozDH8/5UNyw+C2MagvY/MPUEsDBAoAAAAAAC1nSlIAAAAAAAAAAAAAAAAZAAkAY3VybC1tYXN0ZXIvcGFja2Fn
*/