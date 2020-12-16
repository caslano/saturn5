// (C) Copyright Thorsten Ottosen 2005
// (C) Copyright Howard Hinnant 2004
// (C) Copyright Jonathan Turkanis 2004
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

//
// Contains type traits machinery for incomplete arrays. MPL compatibility
// is included for completeness, but is not necessary for the current 
// application.
// 

#ifndef BOOST_MOVE_PTR_ARRAYS_HPP_INCLUDED
#define BOOST_MOVE_PTR_ARRAYS_HPP_INCLUDED

#include <boost/config.hpp> // BOOST_STATIC_CONSTANT.
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_bounds.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace ptr_container_detail { namespace move_ptrs {

// From Howard Hinnant.
template<typename T, typename U>
struct is_array_convertible {
    typedef typename remove_bounds<T>::type      t_element; 
    typedef typename remove_bounds<U>::type      u_element; 
    typedef typename remove_cv<t_element>::type  t_base; 
    typedef typename remove_cv<u_element>::type  u_base; 
    typedef typename 
            mpl::and_<
                is_array<T>,
                is_array<U>,
                is_same<t_base, u_base>,
                is_convertible<t_element*, u_element*>
            >::type                                     type;
    BOOST_STATIC_CONSTANT(bool, value = type::value);
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, is_array_convertible, (T, U))
};

template<typename T, typename U>
struct is_smart_ptr_convertible 
    : mpl::if_<
          is_array<T>,
          is_array_convertible<T, U>,
          is_convertible<T*, U*> 
      >::type
    { };

#ifndef BOOST_NO_SFINAE
    template<typename Src, typename Tgt, typename T = void>
    struct enable_if_convertible 
        : enable_if< 
              is_smart_ptr_convertible<Src, Tgt>,
              T
          >
        { };
#else
    template<typename Src, typename Tgt, class T >
    struct enable_if_convertible : mpl::identity<T> { };
#endif

} } }         // End namespaces ptr_container_detail, move_ptrs, boost.

#endif      // #ifndef BOOST_MOVE_PTR_ARRAYS_HPP_INCLUDED

/* is_convertible.hpp
T8vf9G3f67jUDtcXY0U2uzlX7u8zoSJ+ixXffltiz0COBEFotSKd2Zv7+zITiPJvNzYz3MFt28tlti0MCYUsLc81e8+tN15XpHE2h5aXFNvnDZOEh681IoecENbCqNttFWGbHhac8cvvlq6l3Wx9w99xbbYXaafrSw82C5Ppvr23DDcrG2HYPjKsvnGh3Fe7nwizl/FCmgMsGr0WSQPIPnJgrjz7Huxdyek0LNHSJPbAHpRVhqaalHnanTy6oGNqw9DJshwi6MwMQPQGpTn7IWUnfVaSeJcezjoOdAXGjtxisAk+1r02XZrKatPNRJuK+5eCflI0ozLhKwCGnCwFW/tsn4ZGvEsKbcTX52w5J5S6dPrmKYq7Rr5FK88U8VqxDiZ+fPj4gi7DGdzrcOnzv2D6KcXyixftBQEHizY6i3nWV0wYbVoTLhWn94EEYaZJs/fx/tWEh3eUyrK8acLMEcS0bL9lcH+ZCUYyKRDe5BPtd3vb0FSEwbqdtACaqxOiddF3oUUCgqEwgYGxF2++xqbFqFLck/R+LM2SmrbGIFPyS5f/w6j8I0T5yTnqXx/H0+j9oAwL037DJ4ZuobFVYfxPDW7ewk/WF9M4ISeFPH8WtesIIdEpKTNfGJoUwX5Zko0kIXT3lyaclxPbw5rb705+LdKQcb8NcLMT0aRQlbkn7vtcs25t8g7XxaX++EHKRErXIy0LKo8w0WFtQZDlcfNEOhVBfhUmu7Au6xia+mSmXP4yE9d1sn2XX8XQ6IKItls/lsa0vLCHG+ZF/S7khZSJjuawV6F/RJjoj9rqyLw3zouTG1MSkXcPQ2cSIH1LT4hXiG1ZsZoxa6yxWUbaYatH/bFXEG41TyByYT365GXJpDixFvGqb17m+8bEIY0wzPadCRXvFucIOuxTqDOz3j7OIxybYVb1tUWtDP239H6ZOBr7XFQ2jU4mTGOrmHD7LsxtoJEEhvnp9t82tqxm9UXIyfYxdNH2HTEPEkvHKo2c38im0SSSx/nQ1GCXJJEML7DqVWn5iHN7WeGWf9rRMzPcvpt/aJ7RQf50rN7ZyphO7neJlUlj70aIu4/yYvwH60zG+Dxha2WCYj/3r+Pz091Ot7no8xPzMu6LMQPJqEw7W+F+IvYdfAOgaRB1N3Kj/a1dCVNHB+fOR3Zv7KNn67N9rgWxfnRhnvXugbVvrohwAgN+pTpaW/V6RvY6U3Fe1hsIGXPnkzPDccHq2hr1WmlQz6mEn3EM9xL77d09vzJmPbtG1jFjXl9PFOiNlOYYhijbjDy5bxCLIO59So/1oQl0FbJvvU0vzmqY+7JWJlPN0dnw3xDXevtT7o/MOAOGA6+3HkqbU5mXttHLWpYk62XY7Lz0PlVdPMLEXjU9Fu/QA4L62rR8z80T8wByD7MxXPJ88Xxog3JzLqR1Scb5qt1EmP8r52F2j8LSabXAH25SpzDZe0B/myfGKNYeqD1kWCo91tPqQvKisbdsRxIROrXWSiPfGlN1SifGVFIn1oV0FSVzZk6PxsUhj5N2OGmZWpfrS62E/DXIPLVTahpanmXLKBedUNRtMWHiHiYo5D1MUT5NMg25iVaeWRM0mfeHiflKc5+TvKJNyl1rnh9uKiHKKe8Ki7mINS07bUH82pb66J6Rx3uZuNb9I+3Q+ptc9c2kos8vA7evSZNlXGHCbZv6l03l2LykvKpivvG3xdxDnqQhg+CevbRv87u87DSg0mpfytre8XTm7F80/vl9qJ9ml5fOKWGrQZkxJu0toaaK7n8KaWdBUTWpsKwk8271/QhnsiEosTE06T09ojz2G1cHyDA95y7mIbL4EeyQZZmV5XAVzUNYttDfRB6W+w8=
*/