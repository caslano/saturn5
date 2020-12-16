# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_TUPLE_TO_ARRAY_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/overload.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_TUPLE_TO_ARRAY */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_TUPLE_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY_I(BOOST_PP_OVERLOAD(BOOST_PP_TUPLE_TO_ARRAY_, __VA_ARGS__), (__VA_ARGS__))
#        define BOOST_PP_TUPLE_TO_ARRAY_I(m, args) BOOST_PP_TUPLE_TO_ARRAY_II(m, args)
#        define BOOST_PP_TUPLE_TO_ARRAY_II(m, args) BOOST_PP_CAT(m ## args,)
#        define BOOST_PP_TUPLE_TO_ARRAY_1(tuple) (BOOST_PP_TUPLE_SIZE(tuple), tuple)
#    else
#        define BOOST_PP_TUPLE_TO_ARRAY(...) BOOST_PP_OVERLOAD(BOOST_PP_TUPLE_TO_ARRAY_, __VA_ARGS__)(__VA_ARGS__)
#        define BOOST_PP_TUPLE_TO_ARRAY_1(tuple) (BOOST_PP_VARIADIC_SIZE tuple, tuple)
#    endif
#    define BOOST_PP_TUPLE_TO_ARRAY_2(size, tuple) (size, tuple)
# else
#    define BOOST_PP_TUPLE_TO_ARRAY(size, tuple) (size, tuple)
# endif
#
# endif

/* to_array.hpp
jv3wC5yJuTgLL+Fs/A0XoivbYxG642IsiayPfr2vwhq4GuvjOmyGH2EX/Bj74XpMxKH4MqZgJk7EyfgGTsPncR72x0WYgB/gp3gWN+JN3IT5+DnWcWb/w064FWNwB76GO/Et3IUz8Us8gHsw0IXtjRXxADbCgxiKh7ADHsFxmIML8Bj+EU/gZjyJe/EUHsSz+ADP4RPsqLlYFS9gb8zDl/A7fA2/x/V4Da8jkfkj/oCubvw2HAPwL1geb2JnvI2T8A6+gfm4GO/iR7gOt+HvuAcf4VFUblx2CC14DZ3wL/gL093cef9Bb3SjvCy6Y330wDbohZ1keix6Yw/0weexBA7C0jgaA3AqBuJMLIvzsTyuxQp4DqvjDayFzh783YKuWAe9sC6WkfKK2ADbYFN8F5vjHmxl9INtUHny/oClMQyDMRxDMAI7YiQOxE44XKZnSP13jXIv/t7DbuQrMB4/xu74GfbA/dgHT2Nf/B774V18Hj292J/xCUzAhjgAO+NAHIBJOA4H4zQchgtwhDFOmIb7cAyex3F4Exn7TD9vjisYhL1wCPbGP2EfzJL8K8kPYV88Kvlxyd18WG70QSP3l7wfGv2Plny65AtxAK7GgbgBk/A+JmOnEhzPMB6NvIfkfXEwJko+UPI5OAQXSb5U8hto9O/qa80roZHXw5HYElMxBNPwLXwBL2A6Xpf8B8lv4Si8J/l9yZ8uyfs7NkUjf0bySWj0P1/yDZJvxbG4D8fjSXwFc/FVvIwT0MtPqUlYCifj8/iG0Q9OMbaT5Nsl/wKnGv1KfkByZfzGFd3QyH0k74FG/8Mkf13yN3E6rsC3cJvkX+C7eARnYh6+h8ZvxGfhazgbp0o+TfIZOAfnSD5P5/SDc/Gk5Oclr1Ha2n9LNPJYyXvjAhyMCzENF+EOfB9LBvA+g+XRyCtKHoR/xJqS15a8Py7BZMmHS/4ZGv0fkDxP8uv4If6My9D4w2I5dsEV+EdciaslXyv5BlyFmyXfIvlNXI13Jf9N8vBAa/+90cjTJB+HH+MbuN4YV9yA3+An+HRZ3u+wJRr5M5KH4EbsIHmE5K/hJpwk+TTJT6LR/3XJVTlr7ol/wrK4DYNwO47AHbgLdxrjJvkhyXNwF56S/IzkJcvzeQrLoJFXlDwZjf7HST5D8vm4F1fiV7gB9+FD3I8xFXg/NsYNjbyv5Al4EAdJPkTyP+IhXC75WsnvotG/Z0VrHoRGXgdzsDkexRA8hm/hcbyAJ4xxk/wHyW/hSbwn+X3Jn67E+z82RSN/RvJJaPQ/X/INkm/Fc7gPzxvjirn4BF+EfYOp+K0xbpK/LHkmXsDJkk+RfBfm4V7JD0leprK1/zpo5CGSR+IV7InfG+OKV/EjvI6P8M/o+aQ190Yj98MfMFDycpLH4A3sLnlfyZej0f9WyXMkP4s38SreMsYVb+OzQXwPj+9gvjFuki+UfAnexRWSr5L8At7DK5L/IHnTKtb+I9HIEyQfir/gi/grZuJveBgf4pNV+dxkjBsaeT3Jg/ERNpO8heSpqDx4f5T8Zcn3otH/WclvSf4LupC7V1PKFf3QDZ9DD1yPnrhV8m2S70Yv/Ery/ZI/Qm90rW7NvdHIu6MrDpU8U/Kp6ItzsSQuQT/8C/pj2xp8fsNINPLOksdiAPaQvJfk72AZnC35QsmvoNH/L5L71bTm5bEc1sLyGIwV8BWshEfwCTwr+XnJ87Ayfi/5NcmfrMX3SFgDjbye5KPR6H+q5EskX41V8XOshjlYHS9gDXyAtdGvNp8/je2CdXE91sOtkm+TfDfWN7aL5Pslf4QN0LWONfdGI++ORv9DJc+UfCo+jcsxGP8k+W5sgl9jUzw=
*/