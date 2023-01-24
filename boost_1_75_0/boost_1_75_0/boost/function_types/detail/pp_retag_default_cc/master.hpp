
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is guarded externally

#ifdef __WAVE__
// this file has been generated from the master.hpp file in the same directory
#   pragma wave option(preserve: 0)
#endif

#if !defined(BOOST_PP_VALUE)
#   include <boost/preprocessor/slot/slot.hpp>
#   include <boost/preprocessor/iteration/self.hpp>

#   include <boost/function_types/detail/encoding/def.hpp>
#   include <boost/function_types/detail/encoding/aliases_def.hpp>

namespace boost { namespace function_types {

namespace detail
{
  template<class Tag, class RefTag> struct selector_bits
  {
#   define  BOOST_PP_VALUE non_member|member|non_variadic|variadic
#   include BOOST_PP_ASSIGN_SLOT(1)

    BOOST_STATIC_CONSTANT(bits_t, value = (
        (::boost::function_types::detail::bits<Tag>::value & BOOST_FT_default_cc) 
      | (::boost::function_types::detail::bits<RefTag>::value & BOOST_PP_SLOT(1))
    ));
  };

  template<bits_t SelectorBits> struct default_cc_tag; 
  
  template<class Tag, class RefTag> struct retag_default_cc
    : detail::compound_tag
      < Tag, detail::default_cc_tag< 
          ::boost::function_types::detail::selector_bits<Tag,RefTag>::value > >
  { };

  template<bits_t SelectorBits> struct default_cc_tag
  {
    typedef null_tag::bits bits;
    typedef null_tag::mask mask;
  };

  class test_class;
  typedef constant<BOOST_FT_cc_mask> cc_mask_constant;

#   define BOOST_FT_self \
      <boost/function_types/detail/pp_retag_default_cc/master.hpp>

#   define  default_cc_ BOOST_FT_default_cc

#   define  BOOST_PP_VALUE default_cc_|non_member|non_variadic
#   define  BOOST_FT_tester void (*tester)()
#   define  BOOST_PP_INDIRECT_SELF BOOST_FT_self
#   include BOOST_PP_INCLUDE_SELF()

#   define  BOOST_PP_VALUE default_cc_|non_member|variadic
#   define  BOOST_FT_tester void (*tester)(...)
#   define  BOOST_PP_INDIRECT_SELF BOOST_FT_self
#   include BOOST_PP_INCLUDE_SELF()

#   define  BOOST_PP_VALUE default_cc_|member|non_variadic
#   define  BOOST_FT_tester void (test_class::*tester)()
#   define  BOOST_PP_INDIRECT_SELF BOOST_FT_self
#   include BOOST_PP_INCLUDE_SELF()

#   define  BOOST_PP_VALUE default_cc_|member|variadic
#   define  BOOST_FT_tester void (test_class::*tester)(...)
#   define  BOOST_PP_INDIRECT_SELF BOOST_FT_self
#   include BOOST_PP_INCLUDE_SELF()

#   undef   default_cc_

#   undef BOOST_FT_self

} } } // namespace ::boost::function_types::detail

#   include <boost/function_types/detail/encoding/aliases_undef.hpp>
#   include <boost/function_types/detail/encoding/undef.hpp>

#else // if defined(BOOST_PP_VALUE)

#   include BOOST_PP_ASSIGN_SLOT(1)

  template<> struct default_cc_tag<BOOST_PP_SLOT(1)> 
  {
    typedef BOOST_FT_tester;
    typedef mpl::bitand_<components<tester>::bits,cc_mask_constant> bits;
    typedef cc_mask_constant mask;
  };

#   undef BOOST_FT_tester

#endif


/* master.hpp
pNLT+2/nDBfGouZoCJ39C/g2DXAYtdOkvTTcPSSIQn7F6Jz1M4HxbI6x31Ql3YejNfR6FahADNV9HYmtqVZszb2mmla3kwb40Qj5DDJC/mNQgk1ZQW9CZVYdOWyDPfI6sS//R/bI0bo98pIfxa/06ge7Fl02be8e8bvoAtC7dbdq4M4URaft/Qle/w0P99ObvRHFP7JiTpf5e6WmyXcMeIExgl8bI96NEa/GJLkrbkjxVrhSxe808Zch/gQDsibXOG+0GDLXEjSy9A/JMLbMttvEokvMr5gwEEdyqIV9Eiuk7QTpAynHzudpDzjcHLC3krSV/dpLO+/2jNSCv8o1ykfDLPeTqq+uN5mqrwx+1oqeZcCzNFlJmqzE1y9JPksyn4U25uvn4PpWDsL6sN04fvYmPYuTKsqQfWMw7xk5Wy17BirgN3j8N26ART9uENlkZJg2GRme3sNT7OX/AkLuH08LUJC/r3a1FXQfuGRj/MZjmEvFpraGS5aDeU6Mf2db20H7g0gj0SA6ljyCgZiIR+3MXWWzjaRBbg7KLhaGc2tNWzzDsdXL+zgJraG7qXhMF8vHDNz7LL9Fw/AUctij72biG7by892o53NoyU2athGhxn7rFX0+0t6kz3ySmARLziVNZ84ajXLmDnRpO5qob0u6fWc8Xl4fH2IzQ0zx0i8btQP8dmAY2/0kq+1+Uojt/vMDm2IS2Ll9ONv9
*/