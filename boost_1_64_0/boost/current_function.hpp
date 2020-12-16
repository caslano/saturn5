#ifndef BOOST_CURRENT_FUNCTION_HPP_INCLUDED
#define BOOST_CURRENT_FUNCTION_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/current_function.hpp - BOOST_CURRENT_FUNCTION
//
//  Copyright 2002-2018 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  http://www.boost.org/libs/assert
//

namespace boost
{

namespace detail
{

inline void current_function_helper()
{

#if defined( BOOST_DISABLE_CURRENT_FUNCTION )

# define BOOST_CURRENT_FUNCTION "(unknown)"

#elif defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__) || defined(__clang__)

# define BOOST_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)

# define BOOST_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

# define BOOST_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

# define BOOST_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

# define BOOST_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

# define BOOST_CURRENT_FUNCTION __func__

#elif defined(__cplusplus) && (__cplusplus >= 201103)

# define BOOST_CURRENT_FUNCTION __func__

#else

# define BOOST_CURRENT_FUNCTION "(unknown)"

#endif

}

} // namespace detail

} // namespace boost

#endif // #ifndef BOOST_CURRENT_FUNCTION_HPP_INCLUDED

/* current_function.hpp
t4FcI08wBMDH+pWBBlOxUR8mfS7PM1R+hiKVWsCg6jJDe8vQgOqfKKb9lyhKbUGMY7WIbr02r7flDYyBZ2nEG1axoKyQFgkIjlWMW/UK6IW6I0fGZ8o/3s6xor2VX9o4VkRQ2zMOmp8Ixz0HpNP2Ex9jczyIoFP593cPs8C+PLAv//gIRyGl6nxmz3mqamXRK+38qnuKr7TWvGBhfam+NJX3pMjbwo3xLMZvUASvVSRzPz8OvpRJtKlCP1FJ8TJb7Q35xxN917q0z95oxdPq8vzj/XzT8Wq/9pL846N83jfCadu5FDpKNtZXNCZHrw+zc86x197hFj0fj3VkrbWd8o/39j31RgTri8L3EtbhcNU7Vk+3wnARk1NYAya/IADd1zbjHVJO/MjejhV/FD/XwV9SriAu7Ryr063iZZEP4dhIVQOtzHH+9bgxzpx5aozl0dIbTTnqyRChlZ+cFWtRBP0nY3HXkMEtf8JUSdDvlKkmQe8Bi199Vd8Qgn4NgDnESwCJn3+BURfbulHwojW5FgKlW5P3pMQhAt+umukBji3clybH1WsVB/agMbB7lrUwsL6tQqdzV10AbdFCIfVwTtdQVTUGPqG1dJIzt4E9qQ7qqonS/CSeG7rrxsroS0c1UkZTaFPZqPe3ovd4AxGDkCXD8e8X+PcE/r2Pf8Vdw/4r/bl9ozw8jeRg2kCD7rjuMukOpxekRtDX5AClKInJBzPUu9OKNDiCjJm7anlDkHVfq/yFHe3pHlLn/LNVr47g6WfzarrYrz3FfkU1QqEi112/PNIws6AochXEd8KNFQR1EIrfBwcGI62+trByrHeeqqpZTZuoMMkLuFdAjft4qAnGIJhgdG1kgNHI5uIT94pAjtM9JMBgcA5csYhuN7YT/Gye/qVF3mw79zb9qC+Udy/xMJNZA4FftV3chR+HGF0MvVxJW7vz/v8pndArK43BTO4oxJIgns3Gnd3KMMloDawk7B0jjQi2gxVCF42Q0sgHw4U0kksVKo1UQ/hDWzGE1yRL/sbGf+mfiv89IOgPoBVYoKb5nySF+BOwNc9fG5I/5OuGZvmPh+SX92pevjAk/96o5vnXhuR7RjbPd4fkOy3N8/uE5G8/1rx/ESH5vU7Tv0/6B/MPtDnN+EPyn0ptnv94SP4jgebtF4bkDz1N/64NyV8ef5rxh+SPb3Oa8Yfk20/Tv4iQ/IWnaf+TfsH8dSNCy6ep20Flv6b+Doz4/gyzDhlzJ8l/nFbS7CmeHfDwEcvehT35qLd3Th9xPn12mzifEqpseN/7JrIX7Qv16MDDIuBJrc45QACt+tu9RGvMP9pk/0GNwELipDxP8cfoy/miL5ff1vSs/BhnpcEzHgUPEXp0mRnvIeOM7/+y23iLLw1k2na7k9/O0Mr5zHOQE5MAomh3lgoSEcPgllFOeIU5d5FhmRaFR58ZgTf54HOry9/GqVWcmT8+L7HF8fUT47vTJ8Z3buj4zKgylepL8QQrFQYYYflZ3SZN/D9ftA72cqNV3pvER7uBl8XKuAYRYN/P5j7aKD7AJFmrtDQtzmobiN1xc2/DhsCegRuqdqx2CD0eJx90rG6FIVFb+47B/fhzxIg7OFZPJCsYiF0iEnyHvNApSL+/o4fxlDgMqCqhqbhflHUEYjNl2XNgPzgJhasDsamqsGP1hACQNRDbX4J0pNKhyEyNkWAHPMWLrM6S2TyUkvjA5vOZVN1NtOpv1PJyKg/giQGpAdN28jg7soKeGNY6IXtNqq5ywUJSHw7TBt5bxVHyg8Qn+KY/uBprZl8qfW681EdRhHf1i6gVkjKR888xzEjhk/t5wzOztMbRZxhWHqf0uzoYTjdoo0g=
*/