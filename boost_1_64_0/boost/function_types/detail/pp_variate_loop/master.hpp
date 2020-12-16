
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifdef __WAVE__
// this file has been generated from the master.hpp file in the same directory
#   pragma wave option(preserve: 0)
#endif

#if !defined(BOOST_FT_PREPROCESSING_MODE)
#   error "this file is only for two-pass preprocessing"
#endif

#if !defined(BOOST_PP_VALUE)
#   include <boost/preprocessor/slot/slot.hpp>
#   include <boost/preprocessor/facilities/empty.hpp>
#   include <boost/preprocessor/facilities/expand.hpp>
#   include <boost/function_types/detail/encoding/def.hpp>

BOOST_PP_EXPAND(#) define BOOST_FT_mfp 0
BOOST_PP_EXPAND(#) define BOOST_FT_syntax BOOST_FT_type_function

#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_non_variadic
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_variadic
#   include __FILE__

BOOST_PP_EXPAND(#) if !BOOST_FT_NO_CV_FUNC_SUPPORT
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_non_variadic|BOOST_FT_const
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_variadic|BOOST_FT_const
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_non_variadic|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_variadic|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_non_variadic|BOOST_FT_const|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_function|BOOST_FT_variadic|BOOST_FT_const|BOOST_FT_volatile
#   include __FILE__
BOOST_PP_EXPAND(#) endif


BOOST_PP_EXPAND(#) undef  BOOST_FT_syntax
BOOST_PP_EXPAND(#) define BOOST_FT_syntax BOOST_FT_type_function_pointer

#   define  BOOST_PP_VALUE \
      BOOST_FT_pointer|BOOST_FT_non_variadic
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_pointer|BOOST_FT_variadic
#   include __FILE__

BOOST_PP_EXPAND(#) undef  BOOST_FT_syntax
BOOST_PP_EXPAND(#) define BOOST_FT_syntax BOOST_FT_type_function_reference

#   define BOOST_PP_VALUE \
      BOOST_FT_reference|BOOST_FT_non_variadic
#   include __FILE__
#   define BOOST_PP_VALUE \
      BOOST_FT_reference|BOOST_FT_variadic
#   include __FILE__

BOOST_PP_EXPAND(#) undef  BOOST_FT_syntax
BOOST_PP_EXPAND(#) undef  BOOST_FT_mfp

BOOST_PP_EXPAND(#) define BOOST_FT_mfp 1
BOOST_PP_EXPAND(#) define BOOST_FT_syntax BOOST_FT_type_member_function_pointer

#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_non_variadic
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_variadic
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_non_variadic|BOOST_FT_const
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_variadic|BOOST_FT_const
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_non_variadic|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_variadic|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_non_variadic|BOOST_FT_const|BOOST_FT_volatile
#   include __FILE__
#   define  BOOST_PP_VALUE \
      BOOST_FT_member_function_pointer|BOOST_FT_variadic|BOOST_FT_const|BOOST_FT_volatile
#   include __FILE__

BOOST_PP_EXPAND(#) undef  BOOST_FT_syntax
BOOST_PP_EXPAND(#) undef  BOOST_FT_mfp

#   include <boost/function_types/detail/encoding/undef.hpp>
#else 

#   include BOOST_PP_ASSIGN_SLOT(1)

#   define  BOOST_PP_VALUE BOOST_PP_SLOT(1) & BOOST_FT_kind_mask
#   include BOOST_PP_ASSIGN_SLOT(2)

BOOST_PP_EXPAND(#) if !!(BOOST_PP_SLOT(2) & (BOOST_FT_variations))
BOOST_PP_EXPAND(#) if (BOOST_PP_SLOT(1) & (BOOST_FT_cond)) == (BOOST_FT_cond)

#   if ( BOOST_PP_SLOT(1) & (BOOST_FT_variadic) )
BOOST_PP_EXPAND(#)   define BOOST_FT_ell ...
BOOST_PP_EXPAND(#)   define BOOST_FT_nullary_param
#   else
BOOST_PP_EXPAND(#)   define BOOST_FT_ell
BOOST_PP_EXPAND(#)   define BOOST_FT_nullary_param BOOST_FT_NULLARY_PARAM
#   endif

#   if !( BOOST_PP_SLOT(1) & (BOOST_FT_volatile) )
#     if !( BOOST_PP_SLOT(1) & (BOOST_FT_const) )
BOOST_PP_EXPAND(#)   define BOOST_FT_cv 
#     else
BOOST_PP_EXPAND(#)   define BOOST_FT_cv const
#     endif
#   else
#     if !( BOOST_PP_SLOT(1) & (BOOST_FT_const) )
BOOST_PP_EXPAND(#)   define BOOST_FT_cv volatile
#     else
BOOST_PP_EXPAND(#)   define BOOST_FT_cv const volatile
#     endif
#   endif
BOOST_PP_EXPAND(#)   define BOOST_FT_flags BOOST_PP_SLOT(1)
BOOST_PP_EXPAND(#)   include BOOST_FT_variate_file

BOOST_PP_EXPAND(#)   undef BOOST_FT_cv
BOOST_PP_EXPAND(#)   undef BOOST_FT_ell
BOOST_PP_EXPAND(#)   undef BOOST_FT_nullary_param
BOOST_PP_EXPAND(#)   undef BOOST_FT_flags
BOOST_PP_EXPAND(#) endif
BOOST_PP_EXPAND(#) endif
#endif


/* master.hpp
G9DnD9EdBvzMgti3Qn1vAC6mQbUqIGo1TPEazHAuRJQHlSgHVFUCWiWo8ymYqgpmJQFCvKFueTAVM8TsDVU+DehdBZhZCTjKhspug/pcgJlkAkrPALJTIPZSqOkZiHwloK4M0LIe5l0JcyyBifjBxGMBD+2gjlWA3EuAr4WAlm0w+xWA7SLA7gRAETP3MsB+NkxJAhwlAub3AyqZ2q+CGkYAPvwAN0Ewka2ALSNUehXgMxNwXA2IKQVMVcNc4wGlRYDpw4CK1jDv6+gGzDB1G0xoGiAhHDDujy5DBQjTQfWNgN/d6A5sgNxTgNotMImLDAIBnTbAajvA3Q2YaySg2Z91QegetkHlvWFi19FNqGAy1VD5QJjXBHR562Ga6ejWItH1zQJctgbUzEXXsBLwWw6YuwA4iIe5FAGiVqC7u4GuryMgpwTQKaG7WgiTagdznADztqHLTIeplqPb7Iguszu6DXndA+YeC7O/BNPMRLeQgu7lImB1GqDsNLqe/YD+G4BONbq3FYADHeBvCLqeLTDxC+gmtwLmp6Eb8EP3lAJ4iwD0dkf3qAZ0zkI3kIcuoRSwG47u7QK6we6As3WA0v3oXlLQNfigK5iFLvA0YDcRXV8JuuGFgNnDgKwIwFM8urYtaIrVaILpMK0TMNWTqEoKqtEC6l+GqnSBOo9BM8VAnf3RBC2hSmPQHNUwg51QAy3MTwIkREJFJaaCaPoqmP45qEUFTLkVzHE1sp0JUXpBjayo1maYQCuYzQmYzDmI3YzmLIFZh8H8y1C9UKjscZjzFYjbDFWsQvMshYl5wZTSoIYpgJ00iHcjxOqBakuAFH+YrRVwUAq18YdaVUDdrqDqx2GqEprnPEzdwpoAIl4OkzoO85sBEewAtGWjeVOYSUA85wEbHhDBJqj0MogxBk20GeqbCvXbCZU1AyLXQMVaAhbXQhWPw9w0gMBdUMlyQEgUxJwKc54M85kOk1cBMlrBLOXXqlDTFjBdFcSTBli5Ckg7CxW4DBW2AJJkaIL6lQN2ZkLsnjDRtTC5NTCjHIh6OcwtCmLXQC3MUH0PiNgTJroZEHoeZnUV8LIDIp8JdfaHOVyB6WQDyk/AHLsCamNg3i0BwZ5Q4S6Aby0gMQeQ4gnIuQzTXAbYmQHzVQH6N0NNLYCHSkCmBdAQAxhYBrM4CxXsCigsASSuBryeBByshgqroYZhgLk1gPVQmHQLwFRXdC1qQHg1uoG1gPAoqGEk4GY6YPIsVLgEprUcph4Cld0FtdwJ9VcD0iajq2iBrmYXTHI6IGEy4OEqTOYE4LQa0FoKWBsDU5yBbqIC8HkVcBIF8wgBbGsB4RXownYBLk+i+yoHtHmhq5gBmI8GZHVDV7QUXU02IPMkzKUMEK5GV3AZ5h6JrmYn69rQvYSgO+wCOIkElG5CtxKKLqscEL0DsL8G0LYJXU40usQxMKUwwGol4Dgb0GUFDJaiy6mEeUUDYlIBD1Z0h2WAgbOAg2h0kRvRHXWDuWsATVcAt+fRDTCo3wioXA54SkX3dRnwfQ6QsgldQgig7hwgUAO4SQM0VAHKqtGF7EC3WYJusiVgNxQQk4JurBJdcQ664C7oFrzQJYeha68CVLUCFHoAziajGyhF15LjixEAuoJlEJEPguxHdZtCteeg6Y5BZY6GYRCI5psLNV/CTARVjYNI9sHUY9FEyVAfZoajvDD4RZbRyMoLVZuNrBujuiWAgJ0Q+2OAlF0t2KALgzqoXkOYqh+acuEADBShkqOgusdQjbkQSSLMf25bTBog1t2oVsNwDB4hkp1QnTiYyo47MEkBTDRn4oFIF8Pc5wZiAgJRJA3AhIEN1AIw4UDzHYAZN4U=
*/