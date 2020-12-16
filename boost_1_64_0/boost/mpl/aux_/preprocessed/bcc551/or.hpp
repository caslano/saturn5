
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/or.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct or_impl
    : true_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct or_impl< false,T1,T2,T3,T4 >
    : or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , false_
        >
{
};

template<>
struct or_impl<
          false
        , false_, false_, false_, false_
        >
    : false_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = false_, typename T4 = false_, typename T5 = false_
    >
struct or_

    : aux::or_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , or_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , or_
    )

}}

/* or.hpp
GqsWrFBPX26ymoW1dkiHVuRd7Zkw1xy4q2v79I4Cu1DYfznMfy6duxoOW2vX2Svp4WvJz7XAYtvtTlEEUuXN7NkRl5VvjRTIV0ZKpPOQpoXVVgurrYPVNjjNJM/apA/tcBQ3xU2PmK3gj1xBHhOlM5UK5qgUzFEjeKMeR7zJbRY20BHxXPn6dqZwXVUwSL5MkSLBHeWSgKgSxFEriKNRMEeLzOZOyc6lCvfNhvuOjLlydq1ATq2ViKtWIX5atSCSugi9R1NIUMgOQe3pModGRBhEZtFEGHExVV0en0VVV6EY1cgX8eqFvzQLSukQfKIIhs8UfKJG7Fhmf5Ew5HLhyFWCW2plajUKU24RrtwZoXxRe7IF6buC9QsE7ZdE3EcQQ7Vg/jrmWgPV3QwLapP5toOOnkJ1J/WWEdLXc0VrmSg6S6nwoUp5J1yNnPKsF5zRLNm7DuHUiuTtMiVpp0rGLl/SdUXRnJREXZVk6WojXiD5uRaZmJ0RGgH/D1F2Jmtd+EG2sFBX+GeBMM+SrmlaCf+sFuZZJ/N0rXzlp01m6g5QS4qWLux7BOzbpOLztbFUfBGMobRLN6yCMdTIVKqPWLjohx2C9BQ9FcaAFgdjUHVX96n+AhhDkXj65XoFjKGqi5PXwRgahZe3wMvb6QI7wEupXfx2BIzBFW2qQOZ2iWDxigg9RSw9muXC1NsETe0QnTVdFNYRoq3miqo6UZBmqaDMSnnjS418Q6genNkkiL5VEP02ukCqlUYXAIPRBVzLpwsUWIV0gRJrGl2gQtJT1dYSukCdtZIusBbG0CJfPe+UrzakyvcassFrI20XBSuPLgByow+UolRXyHnSavISy+gD9ahZa7vUrI7kKQhRtNLl+wwjJPmTyzwfSx8ocorpA+XoDpWCQuqZ5E30gBa0rQ7RthS0rTTh/TmuKgwkX7hHkXCPclEBqgSn1EpqqlGwSguTvN3tFMSSKt/fzxbc4nqCJAW9lAjzqBDmUc0kX0YPAFPKWe0N9IAO0M0OZnkKPQCcTg9QUQZzBa1PBK0Xx0rFV68UZlIjnKRe2EizfPGoQ3iIIrw9U5iIGuFRJnthlzpaLoi0KqmMCSZtFP0iUko7hZ+kilqRLcq5K+9VLJA3KpaIgloBC5hHB6jxlwkbWCscv03eML1DFN/0AAxL/auBSf3ng2UnirpaGmnvoqrWMN2XU/+NaCDNogN3CIdQwlQyuJmitqqihOSL0lrUpaRV4OVVyRsha0UHaBRFrUWSt53CN1J3KyMjE64kbAsiRSDS1kQVqBZ9rU4ytGsjxIzGtkXSg0OVlJTo21fp8tWrEaJA5Yr2NFG4SWmkton2VCOqU73oTc0RopYcjqKlohdkCqZWNRe9IF9wdZHob+VaBdi6Sr4UUyvfiGlk4q+TMyntVP8OeF4qcz+D6h+BXuDqYHCqfyJ6QYnocRVggHlUfw16QZ0oW2vBABv0NjDAFqpfMVKofhQh0YNMIxcMMJbqL4I3lQoPrxRHv0byQPVggCaqP+m3dIjToojHkinuirrboyik+iOlvwKeVSVfEasVDbrRhNELn283O+UtW6nyfq1sebOWK+93LgADTKL6S9ELKoSTVYMBllH99bCztWCADVR/B9r1DvliS7p8q2VEl36dj385UTJBkQNQKWfJa4TDNf9X4PiOryH5TMHy6tfQfJHg+XJB9FXfwvQt30L12f8CXF8qyL5SsH2NoPv6fwu+L/gnIfxSwfiVgvJrvoXzOyKkjxAxVGnekz/VfxTtp2pJvJ8tiN/9Fuav+DOovxnNsO1b2H+EoP9cwf8TJddX+nfxAFjAn+cAwgDA/4L+wf6C/MH9gvrB/EnE/28=
*/