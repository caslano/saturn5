# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
# define BOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/seq/detail/split.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SEQ_FIRST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FIRST_N(n, seq) BOOST_PP_IF(n, BOOST_PP_TUPLE_ELEM, BOOST_PP_TUPLE_EAT_3)(2, 0, BOOST_PP_SEQ_SPLIT(n, seq (nil)))
# else
#    define BOOST_PP_SEQ_FIRST_N(n, seq) BOOST_PP_SEQ_FIRST_N_I(n, seq)
#    define BOOST_PP_SEQ_FIRST_N_I(n, seq) BOOST_PP_IF(n, BOOST_PP_TUPLE_ELEM, BOOST_PP_TUPLE_EAT_3)(2, 0, BOOST_PP_SEQ_SPLIT(n, seq (nil)))
# endif
#
# endif

/* first_n.hpp
YiJ52aE5Maw68oGn/PPMXl3wZjnIXth4NfpL6gWsmJJiYSsz21owxWY/L+EtYsJkVUygq5ZE7FRLDxnOSG+Pub93Uhm94eihTZ8/iNnvlVQTyW8Pgh6QE2ILD3HXa+wSN14MsZBXWNdDHVpOaHsfw4Yoc51TuogXYQm0im3n4wKWIchHC8AjDLMO4tLmq/FFfpDIMZopIDFqdRH8CH+9YhjuBmqtY4DohijOrzfupjlY20vOSrknqQlwi8Ne3XSEUSEYKdOQU/CaWmMaQ5r+tAoGaqUCSSYnaai86USwyoLZ5txw5QJLr/15CT7M6KvbQUbgGluzxvWJ+ZN9Tn5v1FBZG1gJaRBVz7gew5HuVWhAdrfJDGPgg2c4ea61GX+QzeXxEWznz2P/zlhhGFJvoyol7dzhg4cceKHWQhclJ4HLrSxLhGby1mV7950okYNviFQLEFRfFKDcYKJLYyfHerN+3DWExfXlE9KrJ/Ir7MeKudFrurNGDk7hxM4sbZWnU2N1NeU2fQOl9lBD4M7M5/hzGF1eHn8PlDFKhNuWQ6mN2ZZx//BjINPuC6ukeBPHULksVz5K0QWjR3DpcFQ3+LgWx3YFjTDmV002qCJxm3zaVTdnFFjTNTrIMQh27GkfHc40s7TzdCnP5PtBorFlXna8gMIKkBtZhR/28Oj73E/T7W/z54kb+NMwhLckpHAztDFGzSc983nn2EKsDOsNQvRvTvTRiWtPtQ0+fTFACopdpbDiK6B/PfnhwZ6aHabfmPPwhbpFb7e84kgUTCaFcfwQdmR45fUHXnrQG85jA9fX69MIAn564lSJdXBhWvUQNCeyy7GJXXGvUYQ72KItzfWdPsQNI/qwPJ4i9YDHxRXsD77+3h997SYx6Mqbt6Q0JqGNZtC0zrzkN5yvVLV5vYfD+pVFp1JO7ZJ2VpvAD7ypgS5eCa4oRxEy69ZCYTD/U7ytV4U38ScfcCohF3beENGzpGBCHZjxsUoNzywxgq9hFxY393C0/NHqx3yk+1I2aeKTcOGpV4fZ3En91f1aIErSAais3d0DAvaA9ljsN0zLUygO6YY2CVEqY9+UzWMnVfpm/C8jU0a9kdXzqVrFjCbpmsRq4Bo41P90EI+CGOpSN3VeOJIonUDgbsMGpe8v+cUMO+iTdRqArD6zt6x24V0sK7r3Tawp+klRL7aUo7lyLaLwGZdYZ8crBczjxr0tbPseOv9wfRR4zRIy3Rou4ie7hkMnriJK0KpkJAFhJW1ULUDG2PTT3oMKc9lbYSJuu9vTbqbs1pGdpVXDsKR/uc0hHa/c+McomujxEVw2POXuZP9i0mIzPP1he7gIltC3LH+Od28mzystSJoGQA2zPexkp+b80ZyyuZ2X/lGsKBJeVCdJlFRzR3KqO7KpIdI/SDJho9I1jUpnp7zsszp3PFtIPOlm6RdC2+aUkEZH1Opie6hc7UaQSwu/rLVrUpslpjzyscOqOsMmmp8mRwsY3r8Ly9rtIst+SE5A52jYiL0aqchWd8s3XIRXK+fJ0+z5qIK9/crFs0wOQcuAB7H/5Uc5Qr4fLW/4u+6x+OA4WXQ5ZH7+3O4kopvQoNSgiOj2SzlNcdn+0je9+JHUBmLHksNxLvPbGzpvQppoZAWjI4zNTq9FGh6qlDMutRx72X5TXrNK26MRrKjvcE2IcJYhS0LqzYYoYOFXi7FDGu75DUZUMJt2FKhCx3WlmgwjDl2zCyiEEBrmVVjWCXTz7jxWnMyWM3CVLV+kRHajhN91NQ5Ki0b6IeMovon/rJ6CjRfdFKX9G/YWFRpvHZr2VRcW3bv35o3ufIjqxVwYDFOzLxwj8hFxfkC6NRLBRof9xh0=
*/