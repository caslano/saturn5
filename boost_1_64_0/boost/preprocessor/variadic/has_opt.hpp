# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_HAS_OPT_HPP
# define BOOST_PREPROCESSOR_VARIADIC_HAS_OPT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_HAS_OPT */
#
# if BOOST_PP_VARIADICS && defined(__cplusplus) && __cplusplus > 201703L
# include <boost/preprocessor/variadic/detail/has_opt.hpp>
# define BOOST_PP_VARIADIC_HAS_OPT() \
  BOOST_PP_VARIADIC_HAS_OPT_ELEM2(BOOST_PP_VARIADIC_HAS_OPT_FUNCTION(?),) \
/**/
# else
# define BOOST_PP_VARIADIC_HAS_OPT() 0
# endif
#
# endif

/* has_opt.hpp
Xx62vgrVySxrW6ZbxfWzzN7PheKWKdu+TPt8nEsUu0y37H1tLm6ZAsoVLNPkTsX106JcQT+TmxW3TAn2fqr4OPsWu0wT7X0FFLdMq6jTx9+o80b74uaXQ52+Rh2vN170cfb7m/lVlnou5Qu+R3nzBR8Pbov6hI+HK/WK/C5F2tQuL9/PeL05ofD3M1UL1pc6a/10v5/4eNJv5hIfi6uPh2fhvgst9xTardHr/+YRH1dvZeu/0DKsK6jn/ub+4urkUKefMQae09ML6mwoVCefOuv9jDpvXS2uTrkKtjrfFlenNXUaGWPi+1ZWQZ2PC9VJsNfZXLjO25Y+pQaQP1PKdK86iW3a4mMnsYN4zt+hnCOE1c1FtLHf185+P7sseX5R4kWJPcRauR/Z88zjOLbW9/yyPn9EfEn0Z1oCMVPqHiKGl5J+pE578k8xDBOpO4AY6G/vJ4nnAUxzJpL9re0G4WB5PgSHyvNhWnsM97dGCjFCppWU5eyI/kSADvs85hOBBMuqwzjILpbvCFcp+8Ov0HdeBfeeCtHXO7bn6/7oZLsX1Udz7feJCpYyvzkFZc2DlZQ528qatSwouzfbVtaioOyavax5Qdlge1mzgrIe9rKmBWWd7GWNC8q+m1VQ1tQ2j4P2Mlt/6+1lTQrKPrCX2fprbStrYuuvnr3MtswV7GW2eXjay2zL/Nt7trImtmW2l9nme8Be1qig7FN7WcOCstX2MtvYL7KVNbaN/Qx7mW09XreX2dYj3V5mW49B9jLbevS0l9nWo7O9zLYebe1ltvVobC+zrUcte5ltPSrayhrZ1qOEvcy2Ho9m2sps63HbXmZbj0v2Mtt6nLSX2dZjn73Mth7nZtvKbOtxwl5mW+avbGUNbcu80l5mW76Fc2xlevl8KdPft5jucfaJfq3xoZVvMlPS/vF7nFGmv/PU3+fL96B8x6+/e3lZ17N/J0O5/u5E92n7vkWX6+8Z7uj68v2D1N9uq2//voBy/Te0/vcF+dta6uu/j/YHUG7/u0mXZ9r6sf29YrungnL+5++dUPS9B/75ewwUfQ+G4u49UPy9GSo3Nsq3xLRdmee++7zbxdS0e+8sevWfv/dA0fdgKP6eCkXfm6G4ez/87+5VUPS9B/75ezkUfW+G4u/JUfS9EIq758E/f4+N/+Q9EqYo/dCfZxOQYj4n25/3NT1vZK+jP6eGODGWxnfDpudLTc/Xm54vMT1vbOqnn6l/fR3Lgn8bxZFy/cQSckzS32DI9ZhHoweOQWP6q1gSX8QncSxWl/Ja+BKGyHXGoyXvJ9cfT8ZXcISuL9eFtv1bIK/jIq4LPYF6Frm+tBdOlflOx3pyfemncIb0d9+z4N+19L/b6f5aW/T5iPqRpqz9jJfrwb6CzYz54A2chC7UfwM9cAr64FQMwGlYBafrn/Jbr3v+NL6tWF98BxNwBr6Bq3EGrsHZuA4X40f4Ia7HdbgBP8FP8U+4EXfhZ7gfN+Nh3IKncCuex234HW7Hq7gTf8Rd+BN+gb/il/gIs9DNiWMOeuM+9Mf9WBYPYhU8hDXxMDbAr7ER5mBrPIqheBw74wmMxVPYE09jPzyHSXgeh+I3OAK/xXTMw7F4ESfidzgVLxvjhVfwffwel+I13IzXcRv+gFl4Aw/gj3gSb+I5vI3f4x38AfPxZ7yLD/A+Kmfed7E8PsAgVBb2a8lr4UOsL+Wh6ISd0Rm7oiv2QzdMRA8chp6Yit44CUvgm1gS38dSuBQDcAWWwY+xIu7DJ/BrDMITkp/Gynheym9hVfwVq6Ori1I10AtrYQDWwUCsh1WxPtbCp7AxPo0t8Fnsgm2xBxr78WBciBPxfZyMf8SZuARn4VI=
*/