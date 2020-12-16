/*
 [auto_generated]
 boost/numeric/odeint/util/state_wrapper.hpp

 [begin_description]
 State wrapper for the state type in all stepper. The state wrappers are responsible for construction,
 destruction, copying construction, assignment and resizing.
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED


#include <boost/type_traits/integral_constant.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>


namespace boost {
namespace numeric {
namespace odeint {


template< class V , class Enabler = void >
struct state_wrapper
{
    typedef state_wrapper< V > state_wrapper_type;

    V m_v;
};


}
}
}



#endif // BOOST_NUMERIC_ODEINT_UTIL_STATE_WRAPPER_HPP_INCLUDED

/* state_wrapper.hpp
sZEYkNiNotQdGK/+mfVl79AOX3YUtmW24456qLBjSo+UUIQIU+glqdPdGshQZ9kLzfmiYIR+/XhVoSVf5Brecwtt+eJiw5uHXJbATyGjTcnOlOHUn1nT66wsmUSlJbQJt3A4lfPx+Xr40HyxBR5+CBzvZAcSZk2vGRcHuSa8lM2Pfz9uhzUdj3HPxnnPFWy1BWz0Ahyp4KcySesG+eLZ15V9OI71PZybbsHzN7lKsG4/SxLHM786Fzlr+umIS532j/gzCRM72D3TYjLOlxOmnAjTqqyYiPRNSyD95tvFX4brY5FUk5g2BQefH0M7KAc6VVvate2vj3kKPnG6Spi/+kipmaDbManRU1NGxXsYtA9/TwdtmiOnWl9MMevLsDZ+ap0+B2jm3aHNvI7K8/KZbh1nOIypSzyN5MKh/8IMXhVls2jWnbp/Nkukf+VG//qcVv92tMcP2GH/yk/Rv9j0padIr+akaXHtvj+pU5yj6BG9ru4AXpYMbQdevEO/Fl6o/6fgJ9wRxU94uuvpish6Wnb5KddTPsaQLIJGSqZRxMd2BuskmS5BLdvGNZWS/+Ri2uTqK1ORMjrKRi4umg5cXwMPBV4dOB3ltdTzWtpLiMxEIbQvkQLr4HG8n0MoBd+LeMWNQ3SeGBspvQDSsVdcp4eVeLTzOtQqf48Dmdb8SY3XrGs4+BSPaLq3Lx3lmeIT0/IsJusJNHNo4wSsxqlW4W1MGD1JdOWsTnfz4k0kQDi9cVLYRJWRp+bqsLsVa+HzCGg0mwil+CYCrO3CZ3oMfNpi4PMr+iRt8Lc957fB307Bn5tibpM/QwyfxOSI9r+vVOLUhc7LB3+RbjHp/LiR+fHZ9+T8gHpumhgyQ7cpYi5So9gWK7IovBiK76W3M2PS0mNmTIe/us/5+Iv67t02D4/TbwuVpxHsqCvSqHz1jrSvGEQ281/i1EjGToxYSpS5SxAPY9k2KqRBTfBOoVdtcL7Pu8aD3k0Wnlz0rooOxJL/QPxlmB5Qg9PClPB8p5g3hO76KUg9FH6EU92OVKiC8CbccNK7AbjqmjUb1d0iq/vmwmOM/5c1ZjDp8/eX6iTaBI0kDb7wSe1eJcbAj3wNa6uw0qXNyfEpRhhNLrwcBqJ/d4OXpMEE1+OSmrx5sM4L1hC8lO4GkoxkB6KS/TKSzKv0NpJkdSPO90GS8saze5sVIe+lEzV+lESCM5QzLAY1Xi/vMpSnpOjhXnH3IMmZi1FukId9r0dkExRWsZQWUVvx4Q6Zyc3UdaIUUiUcvpbdWexGLNwZ7H6I3WNokWd6j5nvQZkL8GkUTswdlToluKuVcmyQpVrIXUfu3PmAF3b41ap6jm3l+lvN3C5OSWujVH0UbE1d0FcZa4xQ+i4w4j7JvUt0OJns7EhiSjN8zdK3n8sTXMZX7P6A3Tw11CHEYbyYWqhYqPUE+B5RSlBLBGLJkZymVtm5PZO53zZ257E7kd0eM7XNvKBrE3cOPkQ5zRLt9gAUJzCNySf+PhGMvVtcPGRTDR6BaYbrDumigolaH6qcy0lLjQTlhmu54VphuFaZNRaDpVwPTTtay6tMFm5KpjJHH7rwpq94gRlyHq8loco1Zvmhvs/dQiSxLbPbrmf+cSSzzUKZP0zXMj+gZU7jDIgkOCJ3pexqvdbCYN0+cvnzlQVGWeuIH1V8eg5/RGJllUW9TqOwkrKHH9nPNsV4xN5xFlksJQdWwA2FjVqSjXFI0Ydx0rwQqOXkmB9iUrmaEHXpT2uDX03I3OktK04+50yT0/HLraGrUsR94/SVwxtFmXznXF08O0etWsz1JnJ/S9nt5DYMQx0mngcmM9kEcV5xz1hdXCBObcQkxDY=
*/