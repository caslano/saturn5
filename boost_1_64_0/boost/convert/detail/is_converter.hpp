// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_IS_CONVERTER_HPP
#define BOOST_CONVERT_IS_CONVERTER_HPP

#include <boost/convert/detail/config.hpp>
#include <boost/convert/detail/is_callable.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>
#include <boost/ref.hpp>

namespace boost { namespace cnv
{
    template<typename, typename, typename, typename =void>
    struct is_cnv { BOOST_STATIC_CONSTANT(bool, value = false); };

    template<typename Class, typename TypeIn, typename TypeOut>
    struct is_cnv<Class, TypeIn, TypeOut, typename enable_if<is_class<Class>, void>::type>
    {
        typedef typename ::boost::unwrap_reference<Class>::type class_type;
        typedef void signature_type(TypeIn const&, optional<TypeOut>&);

        BOOST_DECLARE_IS_CALLABLE(is_callable, operator());

        BOOST_STATIC_CONSTANT(bool, value = (is_callable<class_type, signature_type>::value));
    };

    template<typename Function, typename TypeIn, typename TypeOut>
    struct is_cnv<Function, TypeIn, TypeOut,
        typename enable_if_c<is_function<Function>::value && function_types::function_arity<Function>::value == 2,
        void>::type>
    {
        typedef TypeIn                                              in_type;
        typedef optional<TypeOut>&                                 out_type;
        typedef typename function_traits<Function>::arg1_type  func_in_type;
        typedef typename function_traits<Function>::arg2_type func_out_type;

        BOOST_STATIC_CONSTANT(bool,  in_good = (is_convertible<in_type, func_in_type>::value));
        BOOST_STATIC_CONSTANT(bool, out_good = (is_same<out_type, func_out_type>::value));
        BOOST_STATIC_CONSTANT(bool,    value = (in_good && out_good));
    };
}}

#endif // BOOST_CONVERT_IS_CONVERTER_HPP


/* is_converter.hpp
R+qKsFU+6Vgs6dkTpjYYq9pOl/2TpnrlBYUp7zDJu15Kixt5sMk3aCcYsaxHU4IMvuAGC32V50oYOcWjO8XOrFC0WvbRD1PHVbeSQlIkD45Y6zhYtarM9sNKvHhmhE/7mWnRb9UNQsWkM3xGrEdh14jFkBv3F776KhcV+HbDTz4r+g93eDctLChUYEdazzO+1sO0sl7M0eSd5gbs0rMRL0uT8Od5S72cQ33xRmvBXkqkfO6iICOfS3ulVh5nyY3GEQ5Cvjcyj6PUeuSy2iI/RedcmU5ec3FZ6B4u52OWWeSCngsHFM97AF3Or3q18R6vtefs/kNbEdjJ+11zg/1aY/u1pv2aecE7pjrj9P+jTAtL3Nk3lqmo1bEIL8EYqkoIGirHrG1FXbEyp45p6xnLaGzsl7eKRrkjPNkelhTRxxERl+iIivfEjB/Qd0Z5In24WYjGzT7XyiL9KSub3YoUvQ9u5jBzM+udh37RgX1Y6vBUEfI9SD3rPYJ0edDAWkdfo9rApp1BUl9Cs8xM6qz3DtJlQwNrHWG9UW3Es18zLuUm3rMvyOtORZmwnjVHwVqs/GW/zCMtdRvkPdBAls0I05ioryTzA/KYnjprrGBcoHjHEcjUqGY91vsS/ZIEu7fekVguRmQ5HbTYskgYyfcsh+X9InjrvZC8/6OybXFVls5QN6xzkrfzlZsT8wjZmPJyGUZdGe0CHu7DLkb5tItjJt6K7Up5sOOaX0iXuMsJU/ssk+x/NtUV8iqaA3ikxJWfbuQdfjW1cZv81OkgTec577wckcM15yzOmvRJjG9wwDhfMbNFj89b525n+Obf5Tqyb+bVG2v8w7QGtV0Z76ywaF93tZN8xdzYl8UWMCNZl+Ms9VZ+cDnIUs9hqniDvVntiTbGvaMPm6L+f7hvFGlFH3r5lLHvsul5KZnNzFFevG2GTzleNZ2b2lWW4zXveFUEq3rsc12L0dB47QVB2igCERMWDKwlxaxYoXIOPmP8fsr8RIImOfvV9m6jxIMStyxXW92HugUDaypofeVe9/9tWea5irMduTlpvu5S5/qUZ/3a0l4Vo4UDtzW41Z3Uwyv0JsqatUfK7oIikw9pWNvET0S1zvka32QcQWRkztX0Jm2F2ej3cL7W7gDfncYd0N3WNpaY3lnLWo/hSXz4Hmt/y71FK696oXkGVt1Hvci0SHXG/VxtM19Xjk+KHzrcRA4KMaft35GvmFXmwB1py6v06Hg1uDSWJ+Yn1szKyTdx/k43ay/ZRhefshAIY+D7A15tGFKJgI34tdtN9sJFiG4rPcz6RpUh2/t8zdPW8BNdjD2J/ViWa9hpL6NdjjBz73JVYfScr8956ZtZoK87sraet2Iycz44yqs/IK285jNk2MdnG7EMo02MzzYCNI02sb7a4I+LnHn6WcT7bINjL3Wa3r4k+m5Xkpabky5zsiSf7fhMVwmPaUaZ72+T5bZCjEoHI//wErar2Ix3DKOW+4hhyubj+T9xS+jlm7b4zCmg2+JukU8FOVXSpzlXt9Smv9YmsyQ/Xb2A9L6XHySN4xnCE3s5qfuYOIuv/EROaplbK4uXysZoZaOlsnFa2R9S2QS1DKdllC3SyvZJ7ZZ6yvyNsre1splS34+1shKp729a2U6pb+Vgtew1qV01reyIVHaXVhYlld1L2RVxXyCVddTaVQkwyvpr7epK7QYGc+482m4jlT2klXWSytK18eZJZcO0skKpLF8rqynN69bKfveXzkMrayv1fUIr+0gqm6qVXfWXZK/to7nUbpWyZvyTVPam1ve4VLZNK6ssndE+bbxGUrvzclmZ+Bv/JwIrLxs56pNvBIbo73SJxcAQcc+fn6k=
*/