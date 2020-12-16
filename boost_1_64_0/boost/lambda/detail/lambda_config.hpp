// Boost Lambda Library - lambda_config.hpp ------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_CONFIG_HPP
#define BOOST_LAMBDA_LAMBDA_CONFIG_HPP

// add to boost/config.hpp
// for now


# if defined __GNUC__
#   if (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) 
#     define BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
#     define BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING
#   endif
# endif  // __GNUC__
 

#if defined __KCC

#define BOOST_NO_FDECL_TEMPLATES_AS_TEMPLATE_TEMPLATE_PARAMS

#endif  // __KCC

#endif








/* lambda_config.hpp
iaBRoGzQPrgvBi4HbQXtBO0HBaWC9x6shwQGDXCo1qBuoGRQKqgAVAIqA60BbQcNGoc18MByUCLCjgIVgEpBG0E7QYdBnuU41waUCEoDFYPKlvvXXfqv/5zLBcr/l9v/0wum5xTmnqs1ANOj8T/IcShsynKN5f/8GJAzBv+XB/U4FGPlKfkY/ckY9Fi0dQwq33knb5gee9LNZx4bsVhs6PPFv5HtPAPD0obOsLTNeucBrxWe9lCDw3b+wZr+hEiZg4PQtnOl5LXOjeXp+ZMp4tdY1eMemNWdTP9cMy69BydNeIaoCPz20fMjwmdKrfWUKXwDtb1iWWTlXMLpOtjMvWNx6N9+Ppz6bWydD6ferPtGTV1EUBfVvnEustIGxLpx0kkB+G6Adx9ZtFDx/hl1I30q58dZR2qbT0F427LRNp/vxL+Hbd1gWN+y0PMhP4h/Nz3nkQ9ZZoBMm1BB9M/Ts1V30JNuQ4m0/bdlRG1AN6N9JlSuo5maX5hexGk65vkn7AfV1tLUPidHXtY5iXdGUX6hbZsAr73uWNeTxT9I2wz2NYE+z8JmgHzZzZXaz9tRTmt9iwng5BPnxAaDjqMcMg6IHgvM1R5S6TgpVtf6hvC11pk88e+ropBvsyhn0u58sHGl/X5WdN1t+JDFdr7vKF9bNjBvj4K+Au92n7xxgYglX9mzCy22A7fU7yzssQmyyyvjMyzhZ8/Ksrc9kdeqF1l3ofvYaDMtpJRo5fFZr9JaeC5VXfBv1Bk27ViUYWEgYkLawUaAw3lecHJwO5i1HZ5QV0CQx9U4OAj3geharLZ+zPmIrn3LSMvyhsg6BHukDLGBW8pKqBCUBE0X2ZSVx8YWnva+71w/y476Zv2lG3ToU56HaR+Xzfas054Y6PSgb3kWzso7s57qfaQ7hH8Weqwg6LmtfZke9LVHFc4pyLEpU1vegi7WtWtB5fzftekfrGGdLgnbVcJSVpeEjbH9D7WG7SkaggYs6X4m/g1s/0Mb4ek18Z+G8g3C3EJ9/Q3cdpKmk32S2DDhU/c+yaYfp61GdOhjvxFd6f9KUwcR1IG1nxrEdQD3gwzOQYWg7DPKbco+fXbhrLr2U+VahyIAy1nb6WaKfzZam9um7O3CX5OZV5Sj96PniP8qsQWNBi0D2dUDxqN1Hgm5m/7M/07I46NzulFGa9uKZ4MdRf2OBH2BOCv2V9cvXzps3ku571v6jBA7XTMuo8b+xpCw/aW/qd5P/eSariF1+T+YxzUHvRioJ+hb8K553yePuJmSk1+n+iNhmadxYdJ+Edq2nyCvtb3mmrxad8+Kf2O9n/wxeXbY6Uv414m/B2k5zwzDenQN5H8l9Oe1XeQLbpIvbYvafQ5tUQcbmO59vo1rN+rEvJs3XjY+8mjgLb+q2UY1uKHp/sc3Uz97JC/68I93rEl+t9VTmGDrFGK6b/pw3PkrMh6tf2PwLqPxiXXPYg+txF8YteSbBcNXjr+xw9jfhHardwjz71NM9/0Ls5eubfL1bw9HTPrbzkXPd6jZBmZv46nZNtYpzoB7r49azmu/8eknXp1d8F340sC958421kjytWjdqr0fvZyQsODlkcVTb1179L/HZvafaBtjI5F3qVjwNdc2MI5ZOW6Hn9X2JPuYvXO/bs79RgGvA5pxzAOeD7wR2Iq2mPa0xXShDWYQ/QcDF9J2tgg4hu6mHCl6PIaGSzkCgcmUYxrlyKNtaDrTnQGMpw3iIuBMYBJwFuPtpccqGFMxXllXa7FxmJjNOfIcYBtgrraR8J0fOIThLTYS2b8ufsAQ0502lytogxoG7AS8kvKlUA8jLPvWtzP+DYzfum+9C+PvTltfD2A/4EBgEt0=
*/