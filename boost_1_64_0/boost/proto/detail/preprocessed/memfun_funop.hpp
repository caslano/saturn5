    ///////////////////////////////////////////////////////////////////////////////
    // memfun_funop.hpp
    // Contains overloads of memfun::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename A0>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0);
    }
    template<typename A0 , typename A1>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1);
    }
    template<typename A0 , typename A1 , typename A2>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8 , A9 const &a9) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }

/* memfun_funop.hpp
6zlAuluQOgZuEyTIbh5lN0WE6J9GjeueTa1iT5BV821PN6rMR5xtaR1DzYKPUwAh3Kz7aAghx7DbbA4mxbX8HKF7xzZLlkycDU1SVARMFjDSaIeIQPw03SfsFg1ALne/ZDI+XmEl7cbNL0ufVl2uH3btMjJrcD2ffhDR4HSJ0//Un99BfOFg+FHYB7ld+vOAQwYI4rq+SSlzExAgCa9EHzwzXiUobM2phO7ww1aNaOShfJP5mvESkq7MCNxSSMLbAINyiwjPraRWe3RBxwj6dITK93GnWVnct9wr8V/WK+3YM8+liDJK6MSYLj9dy7w1qj+RYm30Y48LZ/xttkrML0k++zV8BFSGsseRN1cMskgNFb4zADwlpCvEDlPzFQymFl4g2jIKjpWAV4VEAl7pBrb7IuD32QDG6bj+HTakonsM/Uq7ojdO7lY0sVTDd8BZId5bzHzotae96FWqvCYsdZPcoLw+suEfSBypW0dbrYazwYwAsDo+30rOQRfjpxD1bHr4KMelrUsxvGJ5aHB2G7+fPZMY50uAL72RGHVAxyzHKPx7GyZWlHkknw==
*/