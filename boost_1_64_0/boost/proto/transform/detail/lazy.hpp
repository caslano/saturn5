#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/lazy.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/lazy.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file lazy.hpp
    /// Contains definition of the lazy<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/lazy.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    /// \brief A PrimitiveTransform that uses <tt>make\<\></tt> to build
    /// a CallableTransform, and then uses <tt>call\<\></tt> to apply it.
    ///
    /// <tt>lazy\<\></tt> is useful as a higher-order transform, when the
    /// transform to be applied depends on the current state of the
    /// transformation. The invocation of the <tt>make\<\></tt> transform
    /// evaluates any nested transforms, and the resulting type is treated
    /// as a CallableTransform, which is evaluated with <tt>call\<\></tt>.
    template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct lazy<Object(BOOST_PP_ENUM_PARAMS(N, A))>
      : transform<lazy<Object(BOOST_PP_ENUM_PARAMS(N, A))> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename make<Object>::template impl<Expr, State, Data>::result_type
                (BOOST_PP_ENUM_PARAMS(N, A))
            >::template impl<Expr, State, Data>
        {};
    };

    #if N > 0
    template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct lazy<Object(BOOST_PP_ENUM_PARAMS(N, A)...)>
      : transform<lazy<Object(BOOST_PP_ENUM_PARAMS(N, A)...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : lazy<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , BOOST_PP_CAT(A, BOOST_PP_DEC(N))
                  , detail::BOOST_PP_CAT(expand_pattern_rest_, BOOST_PP_DEC(N))<
                        Object
                        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_DEC(N), A)
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    #endif

    #undef N

#endif

/* lazy.hpp
SY/HU/4TPDrkYTKsEDK8ohEfIcNJxOPksX0d37EXTfZ3uNNv0rxvn6L7NmBmCITMiygmOZXbj9fXeAdz7KZj3HG8uDXrTexZmtq80443NeIAMcuVYPKT1/I41Z4LZOM+BmQnEBHjvpaJzhRq/6+GsgRjZwi12GwdlOYeLRpulGZp5xnY5lKW+ms3eM5nsYQey2ZCt2Gm28WqWMptT1eyKaYuDqI6rhh/Tj1SKGytFt28DMTHkVXCDntFH4uQDa1urDWXTmzUJ0Qi3gyYpald+0Q5a0U5USonxvrLS1n/W8dsPy5sP9GIj7D9JPEbYPx+wPrfBiHPRsp/N/W/TZT/NKJb6FvTPLOQZ/O6erOeqWDzTh85nbXjzAl0E6zPUMLsg7hZKMnb7dWBcuW886Ep4JUq6WxmfocCpr+m8fnN79Imf9Wb3w366okDC0OxkpCbQFb2ngnXuivpQRu8jUHwuHmI2UeW2cdmYR/DSA8L+9hC7ZurFU9Ocs6qZdnKZBlhsowKWfJI54UsBZKlSLQ3+vWPlb9sxr/XAthoLs9hMzVsC1YVlIXNMXRD6V0M1mBgBV/eFg3blU3zvPM0bIc/73xD54ct0LBceUjHGAuhw1moUInZxRHAG7VVRj3bPUOsYVdAXxE6qZJOtrPxb5HoszuFD9lFec4kuhq+sVgtFQs2DuAw26avZW16NvFsQtm6vHOQhs8QZ03r1OtIht1Ef56vLakI5WvLUhVS2Ha0a4HnmrHHvBzuCqfccaaBzr3bcadsAHZdr1ou0Ti0gtb2zmPtMn+Segjac6MTlH3hUHSgP7UqHhvoN7nHQMn3v8Ed00kXC5x4IzW4hGJa03pId9j0VJ1eatN1Or0McSzNG95o6xLk0wYC9oh4rJPagbIpjbKQ7lDems+F+8jb3e+6wORLpKr51KDbv95kYTt8e0aAmcgJMHe/682T9M9NVN5FHm97Dv5in+y5fMoLz+g7tckRzEddInzUWxvxEf3xUrLrt9WMA8ySN05kDoRNkTbp9f132D6M77Z/XSb69ruo/HfSvPVyKv/dzB8MiTzvFf7gfZTnCqILtOV9WFfTvD7A43km/1VClqvdeJ7k/yDJ8iFB1yJkvoboriW6RXx8N30+VHa2c3j8UXQXm72x+aN8bJ7kenqgv5zkuK5l/ritG76z/UtR509SnT9Burme6vwplv9hFqt9RuT/LOV/hGK1z1H+GwTdJ4RubyS6m5gNXSLWwb4o8txMeb7EZOtjdbuF9aOviH701UZ8RD/6GvG7deJ1LLGMZUFc57eJOn9DyP9NKu9bTP7PM93uYfLfIeT/diM+Qv7vEL/vNk64n2q2iLHUWfLmLwLM6/F9UY87RT3uonJ/YPVWex90yC2Uw9jeYC35vXXc7dmRQtGyEmAu/4+IX3xCudL5oTGMa+DdfcNJ1HsoN8zWYDnM8vnppOqdKe0qVqx4Esz38YjfB5Tcf+N7anY+fI/p87qmTvpek/YqrMxepUeDsqAOq3Enz88M3qmZO6b+gviQiCpoj2smxthfTnKM3ezGKvXu/MSeZaoPOP+EvdkKpubKxt5D2Uo6swWiePs9DWwudV+j2Y81+//T0bHuZ/56Xo3zZROcmxCOWsBZbPsr5sN+zXzAb4QP+G0jPsIHPEh98Xeiz94r1r9/T3QPE90E67W5/HKEYVvLxSVG9gA42fAf7Hp6rb1CPlEzHAMxpI9HmT4eY/r4k9DH4434CH3spXo+QbTbvTXlnmQqX8jTPWbwR3o4i7E7PWLvCAE2OkR3ufCdloV0uh5ps+xE+ac5tHrFyuCnW3oDOxrr0zNoffrPkEUfLGKr0jpp16LZfblnxPmhp6g=
*/