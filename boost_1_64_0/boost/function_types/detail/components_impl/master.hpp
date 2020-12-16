
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusion

#if   BOOST_FT_ARITY_LOOP_PREFIX

#   ifndef BOOST_FT_DETAIL_COMPONENTS_IMPL_MASTER_HPP_INCLUDED
#   define BOOST_FT_DETAIL_COMPONENTS_IMPL_MASTER_HPP_INCLUDED
#     include <boost/preprocessor/cat.hpp>
#     include <boost/preprocessor/facilities/empty.hpp>
#     include <boost/preprocessor/facilities/identity.hpp>
#     include <boost/preprocessor/arithmetic/dec.hpp>
#     include <boost/preprocessor/punctuation/comma_if.hpp>
#   endif

#   define BOOST_FT_type_name

#   if !BOOST_FT_mfp

#     define BOOST_FT_types \
          R BOOST_PP_COMMA_IF(BOOST_FT_arity) BOOST_FT_params(BOOST_PP_EMPTY)
#   else

#     define BOOST_FT_types \
          R, typename class_transform<T0 BOOST_FT_cv, L>::type \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(BOOST_FT_arity)) \
          BOOST_FT_params(BOOST_PP_EMPTY)

#   endif

#elif BOOST_FT_ARITY_LOOP_IS_ITERATING

template< BOOST_FT_tplargs(BOOST_PP_IDENTITY(typename)), typename L>
struct components_impl<BOOST_FT_type, L>
{
  typedef encode_bits<BOOST_FT_flags,BOOST_FT_cc_id> bits;
  typedef constant<BOOST_FT_full_mask> mask;

  typedef function_types::components<BOOST_FT_type, L> type;
  typedef components_mpl_sequence_tag tag;

  typedef mpl::integral_c<std::size_t,BOOST_FT_arity> function_arity;

  typedef BOOST_PP_CAT(mpl::vector,BOOST_FT_n)< BOOST_FT_types > types;
};

#elif BOOST_FT_ARITY_LOOP_SUFFIX

#   undef BOOST_FT_types
#   undef BOOST_FT_type_name

#else
#   error "attempt to use arity loop master file without loop"
#endif


/* master.hpp
lu3vb5pnPIb5WuR3ov2BZ/wAdOcInQGe8YPQbRC6VvCMH4LudkK3Azzjh6E7T+iS4Bk/At2FQrcPPONHobuz0JXBM34MusuE7iB4xgXoWoTuMHjGj0MXFbo58IyfgK5d6ObBM34Sum1Cdww846egu4/QHQfP+GnoYkK3CJ7xM9DtFLpT4Bk/C91uoYv8XfOMx6FLyvYHnvFz0I3I9gee8fPQ3V+2P/CMX4BuTLY/8IxfhC4r2x94xi9BZ8n2B57xy9AVZfsDz/gV6GzZ/sAznoBuRrY/8Ixfhe5hsv2BZ/wadI+U7Q8849ehe5xsf+AZvwHdk2T7A8/4TV43yvYHnvFb0D1btj/wjN+G7vmyXUXwu4PARejmZHsBz/gd6F4h2wF4xu9C9xpZv+AZvwfdG2W9gWf8PnRvlfUBnvEH0L1TljN4xh9C9z5ZfuAZfwTdh2T5rdE840noFmT5gWf8MXSfluUHfh/wJ6Rbp/qx0M2APwz86Vp8f0uWC/gF4M+g+6rQnQR/GvjztSDktRb5Bf4iRLdwCd7HBN0vSXdr1f7l+HepdrdCdwq6HwldF3S90P0Kul/L8QX8DPDXa/E7CLJdgT8K/A105/xe9F/wJ4C/he5coTsFfn2Txt9BdyehM8B3AX8P3aVClwSfA/4Buk1CdxD8EeDpkPqYB78A/GOIbpHtAP8Uotu4TvMtwD+H6HaAHwX+JURXBn8I+NcQ3Rz4m4F/Q7lERbkcB38S+Hfotghd5BzNNwMjTVi/CV0X+BxwTZPuRwmhmwO/CFwLXa/QbbwFxklgE3S7f3+W5xhh5yDwnCa9HztwlvZWex1CfEeA61F+w7LdX4z3gUJ3K+hulPUG/hRwA3RZae+Wmt8BvDV0eaErgz8MvA10VdnPwS8Cz4XuobLe1mMcB962Sa+7Hy10OfAHgbeD7slCdxQ840bE+2xZLuBPAm8P3YuEbv2tNM94hyY9Tr5S6FrBM94RujfJcQ31xnge8vEe2T8w3jPeCbqPyPEKPOP50H1G6A4hXYwXNOF9kbLewDM2Q/ctoVsEz3ghyu8HQte8AXaAF0H3c1l+4Bkvhu53chwHz3gJdH+V7RQ846XQnfMHcd8Cz3hn6M4VumPgGe8C3Z2E7hR4RgO6S4Wu9daaZ7wrdJuEbh94xruhfqMyH+AZL4Nuq9DNg2e8O8a1+wndCfCMm5r0/CohdKfBM14O3bVC13wb3LeA90C8g0J3BPwxYAt0I0IXORf9G3gFdA8Qui7wSeCV0KWFbgb8IeBV0E0K3evALwCvhq4gdD8Dv/62GqPQ2ULXAp5xcxMIcXWBHwXeE/Zmhb2D4I8CW6F7uNAdB38a2AbdY2T6bofyA7ZD90ShK4Nn7MC48TShmwPP2AndEdn+wDNuge7FQmds1DzjVuheKXSj4Bm3Qfd62Y/AM3ZB91Y5HoBn3A7du2U7vb3mGe8F3QeFbgd4xntD93FZv+AZ7wPdcaFbAM94DY/3QrfxDppnvC+P90KXBM94P+h+IHSHwDPugO5nsv2BZ4xB9xtZfnfUPGM3dH+S5QeeMQ7dmtOi/MAz9kC3XugWwDMmoLud0G08T/OMO6E7X+hGwTPugu5SoZvB70kz9kJ3d6G7GTxjH3RXyfTNaDfjtdC1C10SPONu6LYL3Tx4xj3Q7RC60+AZ+6HbJXQt+H1qxgHoBmT5gWcchG5E1i94xiR0N8p8gD8BvA7334wsv4dgPQ0cgm5K6PaBPwhMQWcL3Rz448Bh6G4SuvU3Ib/AEegeJXRHwS8C90L3RKE7NoXfI3ioxutD7jP7wB8GjmIe8QzZ/sCfAN5AuibCF8h8PAzzWOD9kb4XC10ZPOMDYO8=
*/