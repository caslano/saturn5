
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_function_pointer_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_function_pointer,(T,Tag))
    };
  }
} 
#endif 


/* is_member_function_pointer.hpp
d32z4N+EwLMcfM7VlIIR/ikHu2UloDVQQW3e3+i/xPNsjJgZAhUc+Y+uuXS18iezjp1P/VvHsImJ2rSEa6Du6wlEzz3CJbKsqGmDGvJ+WyD3ihtbNXU1jdKJ4LslTRHz2o1WaaTTrKpMOMeqYMe+LDZh82RKN49kTZ3fSTdlIeJfm5G9aBt743aRNqmOIId7+8h0qAJN/O1M65aOhHZNDx0Nz+MXS5LpxBJPNntAjHYfmMjmb+uiZXqhtHCtMMlPuIniCdtw7vs6RFpm4rzWJH7ncB9lJEYgTGIMig/o8He+M2jHflU6PWEN1cpV8L37zEmhQ4H74SNdOOnIStc2o21lDM9hReQ9VpAxVJpipYABfC65gEcLvVibXS4q79eQU7MMJYab8zXvekhF14eEzrSQdK0z/3agDPfcLPnf2iGY63WT77OopO4Fj3nZqrm0V2kift/cgNt5VoIcYjRlrLyMexp9cL2TTMbjRkJZ+QULunWXUlsPYGPzeFqz8ALkNkxFz5n5VD0jhczq3zLJ82K0OqWL7rr8gaiDHbv3pJc2zf9BW0oeUpm9P2YojYT++FDoe61GwcZr/LzPeKw5kMC/KGvSI1SwKae60P5vNEszEIGj/FrqCczCvcIqti58NZ3rUaVrk3fBY51g7bcuI8XmJNL2yKar2zLZWrdSFLv3cL9iJQpbOoeZrS4nsVE76N/VaBosdCKtTcbUeNwRj63+0cIjU3hkzWaaxeRIKTKaIm3j+LKLevQiWgL2A7p4raMG9kiCaC+j2VcVyfBALBwTYzFr31yqFiugyLYAPpu5CPYhB8mbb9G57ceo9IcpXVQ8zmUDIvG3Yg730bOn3Y2G3CxuESqUVXHw8Vaa0irHEspkof3QnU/2kaGG59ow17uKJ8p7mdTzesrLC6D+9ukIWRKInMVFxL30aPL9TppU8waOuw6Rd3M/mto+0/RPxTw5qZhS50bxeuuDOGsdSw11CYgarcpKvr2nf0Mncr2IMLQ+W8CN+8xJu2IjS0x8RBFqujiqUoTlccWEkjzUZ8xha+9shujDCyS5IZsmacYwmdnhmPjsGQIzPdH67R21w4E0dG5Ba0crHR0M5f/aTlOu4yxmvHEN5UlpcrvBbho/qpC+62bBNDefNSScFOiVfCxu8QbblgqHZ8r4teoBc2gKR17SMaYYkUpJKlvJtCqO+q5sQj53xLAFs3HeRoeWX5KCnp05Ws/ZM8dHy+ijZxXrLjaDomklS7lgR4d3C7KngVq6/34YtELvYm3CHPrpaEjfN1zltwP6EdLaDB+FmfQg0hXO6uXwbBrCV0z9BfvG3/TALo+2XNVjaopjMLDuE+/I0qWr/aPRkjyUamf9gEvjUbLYHsC5qxnW/uzhR7afguTHS5Q07x+ad/aw1ad6KX+jBhMZKUpXraJRWX6ffF8MYSgEsh7YswDfXQK+/oul7InHt3B1nBd2J61YE1YpJuBG5cLsYwzHnGH53E1CkI45p1HaZ3/MTHLlKe6mAv72EL0bX0Ku3Q1fUU6aM+ThYXuJQletYoF1fbjqXkKOJ69Q85Ry5lf7WrDfQzDqwnsympWJQwZeZCHkjSuJGXQ8cASdePGIRv6Xi5Bhc1G9NYO1SCSTfsoVCOWm0SmnemZ9uwXcVomW3nqNMN1qaK6+QOlO/XAV3GF3L2/ErrEk54czWWv6fRSaH2GrbuynPcLBXNV6Ckx0DvBe+bt0vLKW7Rn4hNwH6/mSRRJoFO5gzWX38dahiqm2/YT8optMNtkO1w5kMosTAahQ+ME2do5BWbcsU1oTi4Kn5lz1YwAJSBb5ukQhItiXHJ8qUu4vwVkJcoXvt7tsaJcfZc/L5v8=
*/