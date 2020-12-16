
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusions

#ifndef BOOST_FT_DETAIL_PP_LOOP_HPP_INCLUDED
#define BOOST_FT_DETAIL_PP_LOOP_HPP_INCLUDED
#   include <boost/preprocessor/facilities/expand.hpp>
#   include <boost/preprocessor/facilities/empty.hpp>
#   include <boost/preprocessor/punctuation/paren.hpp>
#endif

#include <boost/function_types/detail/encoding/def.hpp>
#include <boost/function_types/detail/encoding/aliases_def.hpp>

#if defined(BOOST_FT_PREPROCESSING_MODE)
#   define BOOST_FT_loop <boost/function_types/detail/pp_cc_loop/master.hpp>
#else
#   define BOOST_FT_loop \
        <boost/function_types/detail/pp_cc_loop/preprocessed.hpp>
#endif

#if defined(BOOST_FT_al_path)

#   define BOOST_FT_cc_file \
        <boost/function_types/detail/pp_variate_loop/preprocessed.hpp>
#   define BOOST_FT_variate_file \
        <boost/function_types/detail/pp_arity_loop.hpp>

#   ifndef BOOST_FT_type_function
#   define BOOST_FT_type_function(cc,name) BOOST_FT_SYNTAX( \
      R BOOST_PP_EMPTY,BOOST_PP_EMPTY,cc,BOOST_PP_EMPTY,name,BOOST_PP_EMPTY)
#   endif
#   ifndef BOOST_FT_type_function_pointer
#   define BOOST_FT_type_function_pointer(cc,name) BOOST_FT_SYNTAX( \
      R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,* BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)
#   endif
#   ifndef BOOST_FT_type_function_reference
#   define BOOST_FT_type_function_reference(cc,name) BOOST_FT_SYNTAX( \
      R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,& BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)
#   endif
#   ifndef BOOST_FT_type_member_function_pointer
#   define BOOST_FT_type_member_function_pointer(cc,name) BOOST_FT_SYNTAX( \
      R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,T0::* BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)
#   endif

#   include BOOST_FT_loop

#   undef BOOST_FT_type_function
#   undef BOOST_FT_type_function_pointer
#   undef BOOST_FT_type_function_reference
#   undef BOOST_FT_type_member_function_pointer

#   undef BOOST_FT_variations
#   undef BOOST_FT_variate_file
#   undef BOOST_FT_cc_file
#   undef BOOST_FT_al_path

#elif defined(BOOST_FT_cc_file)

#   include BOOST_FT_loop
#   undef BOOST_FT_cc_file

#else

#   error "argument missing"

#endif

#undef BOOST_FT_loop

#include <boost/function_types/detail/encoding/aliases_undef.hpp>
#include <boost/function_types/detail/encoding/undef.hpp>



/* pp_loop.hpp
VuPFLlFYkKjV0R3Ep+2wi4YlJf6jJ/NT4gSJXR/35nlPqF/mMHvhYYnvf50n0EstfFDGkbgSy+e1blj3Ibgi/Y9f7n+Ntg66qxu2iTVrOGHvoGOqy0SMa+T2pfNHCAAc0N/LH9Y/nKO6295xLdckney98GWU/fwGLjvPtN7rOomrIlcFH3qm7HHX7YkQRem+lGb+dTFWfatghob+sQhFjOImNwq90Wbh+pekZ3eIKYpvy1RvX1msQt9zi1rgROuRCYWpz8rBxFZAFdTrqhX4oqmvVsdrmurW+5pbx3SV7hbtllCtmD5Za80+OBg2xFPFZr+s5yutlSF4SxVWvig3aX96jeSs5v7EGedjmw6QpJhIKiJx+ZY3Uz6tQQc7L7Pwk2mUre7koALAIGafQHa+U8FxlWfhhx/XFWgJNuxrIeptXb3d665nZcjQ8jyZS+Obhx60HHpmsTBeWwHAiAfg7+TWn6KKrTvm937VkxlKDtV8Yhurw+FBEoc4bO5c3fSRf+XVyvsvP7EWDCeTPoz3t7F/22ysbfmKSq03oTma6tn1zGfEvifXyh+48pXJXzuoQHU4+Ni2l/e7OpP4Lc4cjD1rYquucfmlMxOVV7KJ+Ibip2TV3Aw0q2sO77DIPtdj3DaxnJsdb3Bgej25WlnPUT085OaHS3pjEWyDd8eGzLZusOFLrrmlXPC8Y+VAKevD/DCibPtIw4xbOi6HdygyCW+KU3pW+jposOL1BusDG6SirV42FlSoCp328u25fNbksNWBk9uMgEhG7Kd/HLdpp4tJwhy2G9yL3BKC31tFt75Wpfbq7til8nE1ACxb/Dx5GfbXYcXMPT0vrLiQ2N9+y8GDlB4m9uweH7llSknuoT/ctBbm75WqY/Nt3zov3N8aACBa9M5BBgDg7y0JADLRaPizvJfIhfplOfOq+1gXyvQwOPqyzeLxMyw1fgBW+Hd8+i6WoZ8Ahp/UrwL0Q6NffBSen+dkLZ/JMkj4Q7wwABgy2G3o7HDghdGruqvxRU9p49earBaj9O7NCBh26a0yLu90OZz45vNtYNE7ExQvJ0ZDuzdHoHIkvv6phYFeVXs+3Vtpq70mcRFKm4cPfq6seH6bzqJR2Wtd1G3xL8qy5imJpnSdpmw/9nEg9rEGn0yq0cz3u8a/488SdSu9dKxt87QOee8b3aTmm+O1Ql/nY0BhcuH2s2JjtRJ+R8qHSXJvmSEOj6tPHE/6+DAav09mOsEp786meb/76t/xh4Hgz+1lE8xx/FubszKVhONaI0ujW5Rtey6bJFrF0su4FXb3pEjUbMaDg2obumX6753hHVOa/fjwNmW+cGIm3quQUNHgN7HGvprrfk3aEb+ckgshWgWid20K3sdQCOnv0tpm+GRNSUywVeWhspOGu3hrVWDZgLt0xjTf2eg/7FcoNTXW+tCb8WVn7uTW/l3/flJ/mrbdfnrEw5LF8kvX9e1bqm59tdQW5Anz9pQc6o849mmHMK/ghsGbE9JZmxSsPk0YB/It99uka3GLXTKGv7hB4RycKO0v6vJpwu7/yr/1BP86asVyuOXNg/kZhLlcWztCCs6T7U/sDJv0q69BlhcHNmW32KznSyK6VKu1Yp86A//TAmL+Aw1t5+W5Aj7tePBaVjyEjLYwm+NonxTbljbz50VO4jYyK1bF8F3d5Kc/IUbOce2y772IVNU+elUWu2/vaGp89XJ0PzvVONlz3itLVW/O5dyyJzW5IfPTI7c1y5oX+PLwa1IrXcUe266KzItZceeBoH/H/79gM3tEfeNkiZu9x3iYPq0cZWlbla5KXnTzyHi4UWikVWGfQgsXEk+QU/fH17gJNqpMnQqvqTPiu94=
*/