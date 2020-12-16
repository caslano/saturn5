
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
e+jZQTV3L2NT9twN526IRDbZBv3fOzycvCdFee6Gs9rPqqcv50tekp6p6jRmzWt4Hq9vd9ecmV3/7rnqvQq7WvVnNRx1dnYEz5M26/ntGrhn4F7L+15wN/E6D+5zeF0H9y14HQc3X8eF/RPCfuuNm3z6k0J/WujX39Ofnma417E9uDl9O+Dm9O2Du74vcs9/bn5v15yX7E3U8hi/0nn19SAzi5YFGX8PLc89kc5o5dPk5emPFXz7Ff0i7bzhyHqI9uCZDQYhb//xHY+iUSiujnmVaCA11f085nNG0nQsLW85PSCeoxNnbIp6oUkjRZbdKlOOanBikBjnI8cpzlP2osNjnCuUps2dFKF+r+2mK23fmcmee1EX0v5qxm3U5+j30iuuDUTog5X6O05KBEryNKUUNHj1Li/6Mp1+ORHYlpGB3QOD1w9cAZ1+mSgGazVTQroMuvDOKRoE8jWjpXVmU37mirp94jlcSacRMQTyap6vLePiKFPOfNGQ0znmJYH0YlTnBOPidPs1evZKmbA5DxuEvi7Vg6P2b8GIzbcQPRDXw24IKSAIYBdzW6Mvq80iXBKTXDoc7PPnhNjIE+yohuPJhkfv3jfVZBW2Ank9nHIpcE0K/TBNIQw9m/ela4DuJ8LfLV5ZgYJ3iTMYx+3K9ObMWdxXpidmRbinAGm/558a3/iav+TCZe0U1wj9pVo/dxeN++6s8filF64qPcfvsryusuY/m78SyPzovya+4xctH99+kHe+5sziO2gE290n/eV9DOQHxs8svtDyXCG+N4D8lPGvia91le3qv+2i25VehtMAA7dejvvcepRb1Xgw3TGmUK6f67dNz31WoRHVbmfLa2dfPDacMDzbR5GBxPVGGMffizDwuxXqOxPbCIU9cunvWSSH+vYqG7sTN0AF/5HuPX1xeOOSfj2B4eEfG6KTLMOJIc/+VSLu8ya3DI7wvX4dvVK4s90QvnSN0/5DFmeA2J3cu3uMfq+l7qaz4nXeWdoTW6XDSBQQhPBHAN7fUOXXhRdk0+QGtsP5iTK40hhF7/2MoHDnS+Nj6jWBmG2yf3mqq0zTReGGWXI72StltQDuuhmrfVx56MBwozywT0RvoLem3fpM9I/FUgNtYxWyIN0qlNQdqFhY0Qf4IwD86RtJYxk69jWexovg2b+E9MJNux1jib20ndWX7E0Mjbnbh+CRNNeNpEn3WE9vWR34slks+aRiTXWcLZh363Apz7aFvwyj/NXe706LFhVwo8iYd4vK6w6KHLzqy06pcElIf1lZkvfFiH6S1l+p2dpp0G9n4HUL8KcDcobaZGK3Na32YqjQ4C6kJ2n/poh3jLrh6t/VQTLZf1pPS30hKC2GSpXc56D3beRM2qCySY1XLrj7UmqThoxV1eYTXmCP7R1XN0PLLikwVFdbwjsvGRc0rQcpDtuynZddopVi/aZU8JLbNy6vNlrsHO2biH2zrDlF5ejbB9N+6nUWcNe/nQE3LQ8zziwf+1lVeoEJVwxx9B72gm1Q59HZQeHDfnl6ytm7kgkif5+XqipvGSp/N+NqHatLjBYHbhbE/pApTnJLXhVxht/ojw603P2ybBbU35gqG9wvxX1N3MToGh4aSQ0nepZQVCrUYChpTjszad1D50dpjG+hQ0z06QrjKqO9Q/1jXGm4YxCNkGMkoh2nFsqcErV1GPe5xrBp2V+aMMZrE6Hznbb2js4tW7d1bY91x92vb0aSVJd6swv3wYH40A1JSjH4nsTuqHqDCWhc+P0Eg3qzU8GG/kWne61uHYJyFLtQ+tKGqJ+5reFq2jM2s8qDtnCNNDU1WqNVacdN935eAganv59Oa8f3JGJDHvfgwJ4=
*/