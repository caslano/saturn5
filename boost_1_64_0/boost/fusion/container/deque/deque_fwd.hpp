/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEQUE_FORWARD_02092007_0749)
#define FUSION_DEQUE_FORWARD_02092007_0749

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if (defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS))   \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   define BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#   undef BOOST_FUSION_HAS_VARIADIC_DEQUE
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
# include <boost/fusion/container/deque/detail/cpp03/deque_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct deque;
}}

#endif
#endif

/* deque_fwd.hpp
7EOPOLKL1Y0KYN0tPI7RAhl/Xy8/WcVe+Rqr7EDJz0aynTcQf6UxfvkNUc9sdchXf8fNVpM4FxBntSFOyc+AxmOsbT92OVdb+Eopr5fLNra0GOOTw0ROu/U5TlzxrvETb7ppvNa8+sbr2qctw6Vfg+RvM8JC4i33iFd6Ljvn2LPrkMf+4iyVOC+QONsTSoizwhWn7E81avVpkoJa42yjxKlf10t58D73n2ceb7VJvBRgutpnFwRSpmqIW9/m+X7ijkg3iVupBq3nNo+QeFnIJ95FxJtsFq9cFui1Avn1S4NeF2OShsWkocQsDUpv5npuu36f5CfecrN4lV7DpyletWOO/AacRehOWEq8Vd7xOupfvpX5LTFFrdeQlXmV+/B25umJyPBOz+kp955pkhV65dEGP2lK90lT/Y8Hz/TIyryOk8TzfdOzjOXX+qTn9B4nF0vaJqlpM1mxV74dNUlnKd+t8kln/Y8lV75dp6ZNVuaVHlt78/RETPVOT/2PMc/0yMq87l8qJD3ny29aOOFmpVzp6eFZzQCujYzXIAmcQNR9xQpaY0e8VTl/GdepX4PUXt/mqkO5NtqwfV73TDKWkTz3IGW0g7YS+mWq6ViN45Tfr0xXOig/mdkORwD1PUp9SmiOZ32K3eR+or/7elDS5zu+VJx+v+lwUu2p1p32zWLdzF8uz8K8K59XyOfzsj3//my259875uh/9ziXvSh50FrO6a0It7FM1DRXHjj06+xfcl3o3idedb4dtYUHye9JNKFM+R11x3var70lb6V+NaNgmle5PCppipBj7yLC7f9m727goijzAI5joqIpIhkioqLiOyoKKCoqKiomKSoqKsa7gvKysouikdJlaWpGpZ2VJl1WmtZRWWflFZVdL2dFpmVlRZddVl7nlZW9XN1vZv4Ms7uzsKh1b7ufnr7uMPM8zzzz7OzOPC+jnLPq8nTev43lOV0uyyWMRJXXTU2165HVuJl1q415qLuslft89bcvpBnaF8pM8rPO+NvSqS1E0nKqv3nq/eiazpRbF863SuZyyKNhbNnUEBlblpFdNET/nNovHyzHoDYuH/Z/MJEELyYuSTO67r6P3pawT/5+ySUyLnEJ703Geu2V8pwudTyB8BL/SMxT11d+idNIETG4/t/+Icbf/pIXtpRl4FXs0N4xWtIPDdFimCjpj5XxwFVa+ul5PNouXR9eBemZS9y5jjW7H2Tc73JJ9xlJ9wBheXv2JF9NV7np1OgxpE7XWpJWSHf+p6RBxN3wD3hrFMsL1LQWKb8P0vNSa/f1v6LduouxnVDSUW/VpWfkZUveynGK+jnWLuSC7O4hGq/b5f636T1JOZYOc+5JvZcyt8pzB/X9Vuv8xwV6nbc7HuE9+J+yrhyPrrhVObdazI+HtncNf886tWtJ2SY7HQ+t/NIaKL8ck/Kz1FN+Ja7LT8pKys+hfm6VwQEfyz3qGsLtymdwqWl5yOfiv7c8LlTbtzv10njOSezJ/3itJgQTVhK2Kb+li7Sx9pSqTWvma/j3lPx+cjrXlmCPunOty++0EMyKsh9veplV/01kVz/2Sb47ENrI+XI765Rp61uXKP2XZibNmDx1kvrLtKA4L6/+c3SI0xwfob34n9Q/fymfu0ijwiyN4vwG4649NjvUfbTyneGwT5Jef9kv5e3drFttkh4TN6hV0Z19qk13miHdAKkTJWqdUGJaWFyQaT+eP6a3c37uUe4D2kzywwXuuebF/lxgod7Y5+Og5KOv3MoJJdynnBtN8rEsPa84uxH5MBwLl/d+z2DyRa7G7F64MceNHQNtPkbZ9Zhj8zG7rsb+/vJzwZqPXXY95th87LWrMeWNH4s=
*/