// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_IS_XXX_DWA20051011_HPP
# define BOOST_DETAIL_IS_XXX_DWA20051011_HPP

# include <boost/config.hpp>
# include <boost/type_traits/integral_constant.hpp>
# include <boost/preprocessor/enum_params.hpp>


#  define BOOST_DETAIL_IS_XXX_DEF(name, qualified_name, nargs)  \
template <class T>                                              \
struct is_##name : boost::false_type                            \
{                                                               \
};                                                              \
                                                                \
template < BOOST_PP_ENUM_PARAMS_Z(1, nargs, class T) >          \
struct is_##name<                                               \
   qualified_name< BOOST_PP_ENUM_PARAMS_Z(1, nargs, T) >        \
>                                                               \
   : boost::true_type                                           \
{                                                               \
};


#endif // BOOST_DETAIL_IS_XXX_DWA20051011_HPP

/* is_xxx.hpp
ROXVL6TqzUTP1OqfF2D1lpJok+9RiXaGYueH9Ke4vISYwnW7pT/FrUvD96dowEG9s8hsv3y2JRSq9U4x1Vp2BS9j+f4nFSJozYeGd99yi6gk8bh5XB3uW/oUm+MfLA3nviSK92fvqJP05/B8pT85vvD6s2G+uT9PjK1DfybPN/Vn0JJw+tOdqmk/j+SlQ49/EH6tiurin3Jgnrn+q1eL+qHxu5dqaZfXit+kIPjzptcFv45B9c8R+IV1PqD3H+aqRm6R/FEF2q27VcD6AEtDxXr9/YfJuD74Tvr+Ax3b0siqcFZDWslG12OXzpVQPO+MPBCRbRFvA42jGok+RdlLuHkCWm2yRTSUTTL32l0/X/XrpmPoUAe+E7sWCs5psK8Ev82KxMT1IhG/XQigxJOyFCIqF0Qg/H9RCaQr+R3xVEWUfqUcKD0bKP2IpPSoSaitPcSamve8bNWP9QZSvXuw3jPGeq2p3n2R7PutVxlVxFFVnSE5gh+3vUG31EsRO9rzx04V7p3y+VoXNljP2OBmtkVV/Rohqg0chaKJD22GE+78jOzOfGQgNliYdLwK5cu4SttFzQuTwqopesNXUcOPPWfRcCY0PC+CfRsxytowC0GMJxDjEUSWEcRPExmIfoCLfEwPUUgoEyjIyBJtsf4EY/1nof4Ju+j74ItIltlTgsdE/1SJlp0KfHoxS5FeLK2uoeJnLTG/K3CbnWVHL6bsE4tDPY+Rpz+PERn8PIaM9VKfbWbazWOEGCVc2PiLGOh/Lhwtd03hpfjr0drxXCUBEJABxAUSH7B6MlGIyeRm+zRvMy+ndJeMcvHpAJaItjYPmmvusyXKO6Xho4xBIV0gcWZth3+RV/iLgNp1/QWCEjlELCIwMae0hL8LvVQ3udEOLuJKJNIhyYDGuUirl+OMrx4Mh6YfJBZo9awFC20BuxIc3Kgc9o0/VKtdOE7xVX+yn1AgzB4JsxO+F4HVTfoitLpZ+B9jdfPf+1EchBJvJi8UR1t515ywE8wlXfP6QNLcqfw1wppKXH6Yzw1TOzvaBt5m3xIqjrQMx31Gyq/q3rNsBrasbjH54ktmkCPM3SaD4lxIBKYOGeS/LZ07V2wBRtwCjPiYZMQO1+DCfzxSmVTKC0T+JCnTO5mQ31ffTToS0AEI9Bkj0LfHI9DHYNv4dCRyMcAY6oSF6cd8o6YQoWVwe+vNAO1pI7RbCdpIBk16A95yI66V9bnlauwAixeQexPMBxHmUiPMrgQzKhJIUKgupLxyFlUej5WzjJV/GoeV90ewFZC29hDvExfQRE7GPRFWXoxzQomzWKIMAUJJP/SBcvQWwiBq//Oncf8wtl/I2q9KiuAjJgMUq7ioltfg48TDa2UzXQuv5HPJkS2Zrrd7GbU7GdutZ2z397Gs3VV2XbRJKNkaZOadK8y8c6WZN4uKls1AIQnG2G0McB5F463HWiGd7d96m2WODHsYkGl5/CqKA7epz0oIHyynTMFAY06Im6aUGsfQuY7Qmb6JbDYHm5BBwlxPhLl0kwVDfH41I0yxCax89QH3CpjzYC3GQi04FdSfZ1CFnnYqtfDDU9DCVmML868Wbz7kin4RTaRALKNZICttuhCNP71o/FlM3VvBAFOrbUB1jfrxtpeiIYr3/9vJqX1yQvov75qKi7oMUjLDLw2Z1Sd5PN5Dh7092VFjKpwbxvMFAo4ev/hBtnzJy3YgyBoYARPnRbLjfX1jGndzfCAz2AaoRYQCG0rRWhR5yFv6KvsK6Z96O+LXInQizol8aWDpQfjqGXjo8MCOB8k2+RU0S5Y92IXLU0LJdulIieJl5H4vk9M6srrAW9woUjFoFtXnY3X/bMSM0Oo=
*/