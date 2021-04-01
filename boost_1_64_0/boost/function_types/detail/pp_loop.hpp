
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
pbKaELk1XO32/k/AqAo2U2iuk9KLg/IORrmeayKEc+rPPO0/WszO9orRrQl98Ofkm0nmgcWyeCOQL3zcaQ1AbTT0VcgnJnh09u4isnf9HjYx/Vgj8OdEmc287dn9r4GEgUuItrxsERtER8mFNzgAaAcktt3wxfBNb4CzcdjGa2IRi2AMV6jyFBBFZpql6GUDS0gl4LZSoSa2yg8FVwBhL2peH0EVOwUVv3FUSXTNl3ytMcAe8mm1HA1H7fyv8qOQRbEE4P4ifaHcgEKBcRKtppwNoJ4BvA7aGM4fft0nodmbNRtD8nFb+Ycbyr8SO4aLQYveKyoOGivOjWA5RehaGUGeE19h9csrDfNxiAYpxZNBNQ4EF6n2QMXkVeGaZax0GZ8g2Vvtkqlrqche3egPHLIwEmYBigG5l/TUjULecA8llYxxZr2IPzkIuwjXhNQLkpixMgxT83zrL86nFl98AjOR1uq6ifRJdkixEdcFBpEVjlIcqEwLw7iVV4PHD+zF4t1No15S7uxe5NauqfXKz6tGnW8HE6GNK8uWVvCe9E9ogzEoKgn7tgP98A==
*/