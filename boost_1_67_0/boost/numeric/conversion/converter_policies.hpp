//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
//
#ifndef BOOST_NUMERIC_CONVERSION_CONVERTER_POLICIES_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_CONVERTER_POLICIES_FLC_12NOV2002_HPP

#include <typeinfo> // for std::bad_cast

#include <boost/config.hpp>
#include <boost/config/no_tr1/cmath.hpp> // for std::floor and std::ceil
#include <boost/throw_exception.hpp>

#include <functional>

#include "boost/type_traits/is_arithmetic.hpp"

#include "boost/mpl/if.hpp"
#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric
{

template<class S>
struct Trunc
{
  typedef S source_type ;

  typedef typename mpl::if_< is_arithmetic<S>,S,S const&>::type argument_type ;

  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
    using std::ceil  ;
#endif

    return s < static_cast<S>(0) ? ceil(s) : floor(s) ;
  }

  typedef mpl::integral_c< std::float_round_style, std::round_toward_zero> round_style ;
} ;



template<class S>
struct Floor
{
  typedef S source_type ;

  typedef typename mpl::if_< is_arithmetic<S>,S,S const&>::type argument_type ;

  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
#endif

    return floor(s) ;
  }

  typedef mpl::integral_c< std::float_round_style, std::round_toward_neg_infinity> round_style ;
} ;

template<class S>
struct Ceil
{
  typedef S source_type ;

  typedef typename mpl::if_< is_arithmetic<S>,S,S const&>::type argument_type ;

  static source_type nearbyint ( argument_type s )
  {
#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::ceil ;
#endif

    return ceil(s) ;
  }

  typedef mpl::integral_c< std::float_round_style, std::round_toward_infinity> round_style ;
} ;

template<class S>
struct RoundEven
{
  typedef S source_type ;

  typedef typename mpl::if_< is_arithmetic<S>,S,S const&>::type argument_type ;

  static source_type nearbyint ( argument_type s )
  {
    // Algorithm contributed by Guillaume Melquiond

#if !defined(BOOST_NO_STDC_NAMESPACE)
    using std::floor ;
    using std::ceil  ;
#endif

    // only works inside the range not at the boundaries
    S prev = floor(s);
    S next = ceil(s);

    S rt = (s - prev) - (next - s); // remainder type

    S const zero(0.0);
    S const two(2.0);

    if ( rt < zero )
      return prev;
    else if ( rt > zero )
      return next;
    else
    {
      bool is_prev_even = two * floor(prev / two) == prev ;
      return ( is_prev_even ? prev : next ) ;
    }
  }

  typedef mpl::integral_c< std::float_round_style, std::round_to_nearest> round_style ;
} ;


enum range_check_result
{
  cInRange     = 0 ,
  cNegOverflow = 1 ,
  cPosOverflow = 2
} ;

class bad_numeric_cast : public std::bad_cast
{
  public:

    virtual const char * what() const BOOST_NOEXCEPT_OR_NOTHROW
      {  return "bad numeric conversion: overflow"; }
};

class negative_overflow : public bad_numeric_cast
{
  public:

    virtual const char * what() const BOOST_NOEXCEPT_OR_NOTHROW
      {  return "bad numeric conversion: negative overflow"; }
};
class positive_overflow : public bad_numeric_cast
{
  public:

    virtual const char * what() const BOOST_NOEXCEPT_OR_NOTHROW
      { return "bad numeric conversion: positive overflow"; }
};

struct def_overflow_handler
{
  void operator() ( range_check_result r ) // throw(negative_overflow,positive_overflow)
  {
#ifndef BOOST_NO_EXCEPTIONS
    if ( r == cNegOverflow )
      throw negative_overflow() ;
    else if ( r == cPosOverflow )
           throw positive_overflow() ;
#else
    if ( r == cNegOverflow )
      ::boost::throw_exception(negative_overflow()) ;
    else if ( r == cPosOverflow )
           ::boost::throw_exception(positive_overflow()) ;
#endif
  }
} ;

struct silent_overflow_handler
{
  void operator() ( range_check_result ) {} // throw()
} ;

template<class Traits>
struct raw_converter
{
  typedef typename Traits::result_type   result_type   ;
  typedef typename Traits::argument_type argument_type ;

  static result_type low_level_convert ( argument_type s ) { return static_cast<result_type>(s) ; }
} ;

struct UseInternalRangeChecker {} ;

} } // namespace boost::numeric

#endif

/* converter_policies.hpp
lYdNdAoZ/H1btqVGG53KyGsh/yIdt4BEG0t++8NtSpyA9F++J/fEr1xstzext+1sN15DYRHg6NGkTD2nhQKJV30cT5puhLujwaiyL67Wu5i4HHGUbr+zOaaUv8GiM+M81LnI4bnHL7MUGij4WvNxrImvFOi3rJu6QUZga3f9eU1rLvwAmaUWzT3l+FIj/yJz6ETuRznPXyj36HVnyJ1uL6HZJD4KOXvQ2A8QBRm9RAbCPFLNHZZEWbU/3PNzIwMHLUQqBk1Al+zRo0lognwdHe1A8nKnKY8dL9nel+ttqt5sfESvE3YocUPTsqLVlXy/vvOqUIbPBU4lsslnsdOCdux3R1yYxg6NBXKS6310BgelyxPWn6IjGBi6D52vryJ19i+wNvN5Vn5TUaWERdCC1oCjh65bEby5XDl1ED6BHVSBOUohncrPEFIEzcL23rJPkt/aWGwYPEv3Y4T8DZ6ZUahof1hRYzGZWKsyn6ce7WeRwSKnT2ndT1o1zMs1WSk+kyA+eoRu2U3AD2eiJOXToqpQMwJv1BpYObr2EyM4LEZYUHIoqa+/HzZkDjVLWyciCP30fL5sCkrcxePMbKPCkpNzgpXgR01VTYt6EazzWeLLZQ2Kje3a7zm+3X5owsk8NGga7a4QHGeDC3MlrktMdjE2KOdKDgi2TpExOmZkjpNaSRBLRTMTF3Fomtbkca53vrlbWSy25Sympc4uzocJRgdkoffug1Um++/ocV31WJimRZml1dXVMTqfqVq3njd4fP+ieRxsKLbovEFCx0WGL6kXJNDtliNXlWIJ5WtklwRrRATc+hIP/d4+xJSUJ+6os3/rpleaFypOXEHs/cErs6iIj2lU/rrmV1fb6VAnnkDFTZ7vJF36ENVXBTqyydwFuCNB/pzusOK9PkBixoHsj0eWQW7SFAtDDxYs4FPGzrwsKOf237nOcb2R49ImXHtCjW5vhwfJUtz/pVOhv1b19neYUQqoSBoZWNgypfWvwKuizvJdruSRJgGifqNeW6zXGioEJKyKNwEe88jrntbVllV8pOBUZiOJaavGdWdOW0I5YtqL7LBNoqtw2Wk7EAtxJGltbjErNYAvyyZUSkyIByZMaZtqVVgzU2pG6OvYiC6ouMdpeSNShXb7y8bCwoJ1QcTgrievLbv9u2jgz3bZXwbYZHnEJfS2bDEZSHIADGEoZQHlbxjKPbv2cjv2V8PbmIZFeMPbQgpKAPGdZwJo1637c0MgQXBpFaUtrEG4J7EYorgK4zfI2eMB28NrOw1oH/V36n2k32GeRBtx+kCpGUpTJIqO3O23j8Sf7FMrX6fri3swhElQYDyPozgvniiyEa6Yn34r+t8RtuJQpgj8UMg2R+EDSqrih1umYMJBhgvm6H4pdvovESopkKPrU528L6GCVHeLDTbD5AvR9++Z1sUGm80PQzb8C6hZv/dXN71lm5hEmTFVjDqMbBIaODG0mjTI2FxqsdIIRT/96ACBogCCe+gYAiSAMKj4BdRoGrc0V9N1Hm2KYWiWJsvv6d8b2rpxSt/6z4UfMKuKWHviy1R2WZ3WSiWgAgDUVIrfd213h/BE7vN8vueZpRSKW1jQGAxE6C38VXOJIuL1Zl6mFrpQ3NvJCLEXhrp+cbAUEt7CvvilN/EYZB2BMFaDBHqMrR/WxeX5ZTveajo6vDVIY7uA45YkcULp0N5ODHEbSFpMUxGEGQmJtMUYOEVfusIwbM0a0KsrqwgflwapYI2rUNWRutlWH16nlyuBdluZNjbkj89IRV0z+3vHvrayBDIZsB0nZdj/O4h/JEFcEskWE0XymNbtxGadgM/AgEyxSMaJTrPpiidboIkhih8iviCQRXZrqZQfIgHS9x58yUWFSKmF/DZaLzLMMpsAbGZ6B1Czy0BH86viTU1RUVFgsZbfE4i7P5rV6WsBNhuDpjcV5+uXO7QMNcRcQ/u13W5IqaSN4QF0dGITfyWD51xYNjnnBnKi6Jlb/EglPT9vQtOTL4+h0GsCAaPEw0oJyEV1xMhS4OJJILCwsILK0/iEUvWB8zaWpE1Ov1ygUcL7m15Oyig2PC7bG0H2+T6IW1xVXmT+yX4f/Iolzz809eYomzrbdpqNfxByTHQb1CNo7inCoU/AvBf8vugow2KxYr3NaDSp4Pz8fJ37bfvgO+HLtVW2EDFmkCOm1Lo5lSQlmqvy76+e4Ib+E6tsskA6LPpj9lROlfFdAG4NSaGFX50lhjyFxQp/381aj0JaqhdkdiuMCis79buZ1qDQRGFsijFmPhLF0w0/4cDOoMoUzuXJBQgXIbLO88ivDrdexJ+a4AlxdEB27Emr0PFcWswItelpd8dO3qqUTCn/IJ6jy/jqCIdXcH9sRu015GZdplBhQ7Nn4YfXq1dwZVJIU/pBwqtz2Ql3ECTnmVJxZxCWlylB5He7vaFY7+hBh4LFU+FZ4M55Odf1Fql1uwkTIFjvZFlGToXczxy8UbCfXNJytRZZXLmVDu7HIj187nDEkEP8gvTG2mbP6av6v6rCALfj4YM3h+WIQFFOJidEsvjttzB7DmBGYGzBPlN3TBejVIyR3PoWFWBlrmed1WeL19sJGqS8vFwqk2v5utzG6/QCS9t1G1zPSdadVJcSI+ILWn2J8cMCLYA6ER+VjVRu5Mt9sp3SfmQIGwl+3wSG6Yhpx0lYDkI6UXUzs3vLvhwSpm6JGAFcyCYNpF21HAL+KqgcxQo+T1SD2rV6Aciu+/UZZsYpZujfVBLQuo+Px87P6RzB4BatNlXaAaNEsqdgBtlBMSGSRAgtaHRDAKN0eqkA17SwgYbHpa0QgDSK/u4mnEG6YOzwezleW3Xn788PW17paojRH5cFZIn8cVtBw3mUdpyM9Qgi34WXq/R7joHi6MBRXBzjhnqorZjuc/BFxobzlQmWSssz52t1DY3mr24U/XL4AbxQIjBYl/mcJKhL0egX8n2YMQwYWUY7l7R4IUnxGc7yP7EZJKt8by1VjHIi5TVp+ZQoKK9ipJvLaLNDGqTQF6gSDIRPhg6upDk3DDVj6eQXBx3YD+niCKSu/70zwfvLW3+u716v+Wy4HYJW+Xx6Y46/U2wsf4BkVFNiYBl2B4aWmB0Ve3pWoSrOMjohKi52M/LJY2tt5byMwMcYhdZZ3zz4qWS+2vo8CiMPxr89B0BZp3DBScWfUqhcKeRH+qMaZQ85AhRNC0NzTo+C/GKZanwQwaVwlrehXAjFjLheloia3hzQS2gZCsrKwv39wd68P+9/rjvODhRlup+wQ5mRZstVuHn76IJyo58MrGBU+1mqyxK8F4EQTCqd7wsskzX8oH18Ba8Hq1K0MhxwrxkudlbQS4scqBhtjibHJ19kGHSyxBZ7FczJdmqnrpY9soSYKUlfogh13WlLS0sLLpL+86M2OxtEPM62dT1fk8da8w77Qj5ejmbEFnMv9tJBjj03QlLyZrnBCg+PZy0yrwqi/8/g0oyeks82KYaayCziBs/UiE6Dz4yJR1AzgSavN4TId2lRgP/kaY7+HaW2hfk+H5c0MIn0m2RM6Hdxl+9T+rDMBHZ1E2zuwIiFtcBlt5DbSYaDx8dPFOXxh5//0L03CHGa6G0LenO91cXmUYjvFoJwR63Of3DY7nG5W9N3HzzFi/OX6rKBzARnydMOglQeW2KZfApplKnHw7KJz/rc3Jy5EfcX70lkMDt0/AiQ+osYZxYhBTWbYGplZiDrEcig/SPSooxe4DTipnmG66LJHI05ZsFx4yW/QAdFL62OYubtPE/2SArAVIdAJhE0nbRwNOPIHBRacnrUEpU5zciMK8IRmV9kSwnVEaY/8pbMfDJQif7HkWmyvbkei9x7XvnXtw2vx/VHOIm2GMWY+yuqePNt63GCrg741+zxYNVWUIUdLSLvp+3M+bJfn1tX273rEstra2N0Oh1pYMmBqNF8HKHGAkDMog7ykWA6+cJfWmMuFc0Rl9puJDV6cROmbfWfjJM2n/mcxidRWX2DQEQprbz2vPithnVgY72iXIyo5K+4igiZ74nf48X0++LEjgEyjUIfbs8JMgSTVzQMubZvlIZFUvaf/GgeLrVnqSYhA7UG+ip+IzSVbfbmTk73jcPG3E88u3w1fNVyqukff6eZ/7S23Gl6wBTlPYlDHRWXl3tZjSRQybq3b1xiYGGZ7BYEuat8nOk0fXRQyHnS1/lzMROIG86PVvSiGsLSl+ALerTBJ5PeTvipmPNyhJzZ+tGSqRmvAWuAjXohTRKCsn1m0cLDGBGFZOWzmOHxZycCskZyhrCyZoT2aiTupH6El6ToSHn9O6bVEOp/AxwtWNxNyLBk03wnz0+csXq2GfNEo41f7o4dkum1WiT6cLcnGWMwp1jGDVKL7esk+mSFfxxUzhyABU3UB9u2SGDS5B4SNhsOx3XKpAHN0kf3BeIAXzZ2aW6tW9BiU/jhm0E++dp+wdPNOsKki133FWlh0jd0C5vD2GSBYjfIIWuGmlx/gB4uR2GFCWi+EWMdgjHH78yzHitTT9YryPR9sqVp3AJpFnFnp1hx4/8DX7Vv0zd9AIBDS329BVAdzRMHiLsFSIDgJLg7BIfgFtzd3d09uLs7BHd35+HuD3d35wj5/lcndVeVFzZhd6en9dczPf2OfhgHo7tS+SVI5AjqGuPq1N5+uR5T7A/DHdu6k2ccOcmqq8u/GyWDe7o92SpvOW3eWe/yw5acfj5Xj4yMUMx08w6QI/Kl0bKPOUmiHUzyJGXPABCHlpUGzS0tLR3+PdKcXKU34PqO7XCQ7Ebv6SF4TNdHLZ66FGDwkAdRq2E5grV1bS/OdcufnvXnWlsQiWOFHNlqkEfBfv0Ijxa1O8i7atKWgNQbFu860LUSTuPaIJv86StPEZ4wNRHz1VX2G5potiBH9VxR3SeuteGHLeGrQb+3/kF+2qDUVPaV7LtyxmwTJmbmKqPxDA1oZDyJtCI3qn6dP1CVZuFFRolqidnjLxE1iJ4EzrWdWmSn/NgvEZjfVLWrXNhHtqgicHhP+thCfi7G6x8l0Vb6MKHCQR49lswSLHH0OIYvGokL2/04WjLhNSJDX7JdNEh8oefhebt9T6dAUpBwt/cYXyA0VX6n8XyRJ62mmoRNQsU0hJime3gOwIgRNSt1M4KPOYSQIAkvX4+5iMVUUxw+39TdxAq3ZhD14JQUVyO1MAk3FvsWzSJCKjmlQc6wQcMQTZZc71ibIHTtzKiFqN4nvfv6m1OhoLg4WKBqbS2lwORnrkxKairHfLnG0+O0NM8Lw4RQ/crFha8x1qJN8tbQq6a23C57zh3ytQApcsLnFHFpkgANiiFFSLiF1dq0uOzcYEimozWMUCmi3kkzJ9YJOQUyWxbqQrsfPvrE9UJ/u9YAV7zeXhKbV08pPbjxkyUC9zdI8Jq2OEa0Lr+zqQ+OmTs6k5JoX0Z/Iiw+UGd6AOPUpO3jRs4FiMngIukOoZcVM7l9Vdsf2e+190sqiJ2QbI7BinmfmYZGXrfN1IZUbU+ZPtEo5oVh+wUP+MptOH62oWwtE973tC1X4ljR5ubmhSa7va6bo/mOm81Q2nb4WhBoH/A05c2iHTBETAlH1v6vA+yIVf04qYKwv83DKFyr6f8MYc0POYAGLCsZWFmRoasTHf5iQkCZ8FTjMISnm/WYG4RqwdQ3G6grV67aHHB6j6oANBKJc2X4QA3uB/fy1B8ZDvh4RCeyfLJ0xAHOCcK800Q/5bBCQsQPmJjXrJCmA0Sn4vYZvsc0iy79Lcq3VyWdjSf4LJ0l2DJYKyza4D+5jD0pd7Jykb74bPW2g1n8PQgZTzSfNFaUKBrG7e6Uq9H15vAXGfofNJAfVK/1cCgO6es1lX4mxKT0fbyNYrd5EyiLtmoJlHW/1wD9/seW0YMbqVahBrs7CN0synuo5fOcrqZ7OpSPykZn6M+vvOEvzd3EaSTldb+e554Uq/eq4YrlH198HnGUbNYIdjA9//jo94lXpXM4na61ulzRXl5entZU4x3enRpMWgB309XOiOeOoWZ9SnmnBgEFR5hImwcIGcpgfTtC4r2TBp/lHHL0slJJVPsJVuO/x0rkBOjlfaOvnWO5Pte5lqfkeVwLH0nTFCxtCxd4+hoB86pXhXnhnDaaynp2/wR8a99ou1tbJuS1U3bv1j9aU+m7ky7Qn1fPTvNJS7EbwN4rRadRCP+1ZNBtKlHTxwbfy+1Z5ZEcHngLDxn52yMxOI0HsDR2+QSu45oIU3KSy66gi18iVxmypAZSgt4heNKfkFEaIBKRX7XC9sSOgTzhwbn3obGv9wM83HKamp4BA1vJKspJktoWP5y9B07bQlO9HumqlwVVFW1E4EgW5TNqxQmTp6I0yL8XQn/DG4hDw6z2k1CCo07mPZOIMjniNYPPFUaOPou+v/N6YXnTm1JeUlNjq3Qa/xQe0qfr36NTb7Fc/9K0l6HW8i7VNpbzWjgQh6nY2h/KkDK77xLwyNnFIQUpMM1euDJfT0GcgWctUYW4Ee/dVd2wXPRhWtbdhNChUyK7A8MGCfkZxQMw1DDcozO6+tkcvdotiUaz9gVbsn1ttxrK/KdY+r0lqSRYN9wYBgHFD2yVUca6UnGnOQELi5MKAABQcevalo8U5FdeTiOUpjQ4qtUWUjjXjowETaZtyj3BO6kgEQROns4rGytiSetaGiv/PSJ5ZvLHj4mlJREnJpm4M+0hLqBB929Z1ZSvi1cX5ZrotTqY7z6le8N6t6xhben6+Wq8wsrMjINMvcEQ23uTBQTRcXLwh3aw9fiX7UYPcAYxXo2ISxXdKrUS282yHX2Al0qVol86XeUK9cUT22Q91jV6dW2pYJQ5dZB69zdTDi2/UQPOUyM9cFNco6q0oZto+yyzv8dA3pPmK/DIgRrdkSRzrI1+gaDGrd3F1kpL8KqEnsE/aAKy1V/Nm+k0oKrlBCcZk4JZvgehodKj4rNGHZgbrDx8c14fmA3DShjvAodeaHCSpr0bTTGz35/IXpgrU2vgfnu+4gMlAIDVBWPg5xbi3RcXNauS6uapdPPPLCqX+PgWd+A1B8am8ZmBGw2q0tMajRTto8/r/D4nj2Zs09WC2r8/0np7XNoeis28dm0DkpOTg2qfDbQ4X1xo2Y02YGTVtfAp8I2NqcgyYv3qipL4zhgQLeUNq6QYvqtlNJY7c7S97gN+bGn2w7cbKaiHiYXFsf12yQzb1MyMdbuX54v3ZreuaVqzWMkX42Pw5C/fHDm1/6Bx3eVw86IMZ6eejCzpRqT/0fsEyVhqBxt681ooszhuQKAS5/zUg8zzDHg663iD5860eocLRLFDE4tr3W0NayO0GffijpfpBYRu6ZgMg9XRs3bfhhILwvbGKjxBFcSnFxZE2gpw6X9/RQpa7PDyOvp7TkLqXZ+OWO7KII0xTn9DEqTLtbhqaRHk4NPhiitGp++uck1ZYU+oS7FgWGYD8YvqJLuUjeG3I0nqcjw8uzKYJ2Jv9apcHNhHlodEFHhoDlGioPY3ib3n3lGk0pN7u1F/OPZetEFyfT1Lu30fMefT/Ozxj0r8b7MBhw5+ukTiopbNlj+uyjtS5JXCBNyc8G02fxLxseEUtLe/rpdUtH9darTZevJQJgj1Ec+EAtHJbY1MkNWDnq7yPSLu1jX/JKGWfz+CxvcKZlPuSu+o9wkanP3dsIZ+DUUzau4hTl0pS48jrAcgWEP2EBLgkn+daHpH8dRyhVIvep6eryc9QcjQ6+ukTy6bGDxbgWdrUsK1nxkPdm/PVkZYK9pCfgr7P0Y64fHpDGzZ5EySqTVYrlaZTBdIgvF+cVa1JTMvobowwSbBOJ2Ec63QmjF6nh7HydxxVIKHWfhCoOZjYdCO050FtzxFT7QGew1+/cPmdLE+ZXvV3h5JDWOQECLBbhuCEz7uk2uFjz71gYr42KEv+5eaCMZa3QfebXviMqSf+tUBmMI0qrX7TaKxJBppmZnIvHx8oLE0SRJE6YRzi6Kt3/jd3J4+Wezv72e1taXjcjiae130YWhZGBsvAAIs/dN8857Wtdv4YYfZGOsJYiT3ZzgKAXSoOirgPeI13ieoWT4s9wajcVWX+Ua9/Jh7C9RBCe0ztrQcMwe2eyynMJtp1oAOSukMsAmi36JEBf7kAizlgqe3OJ29OgMSqDsGAYCWipycHGw2xwBmBD9rNglxcfHm8vLTtnepB3VvVKZ318s6/2CvQ7+NQhhSgc47tdWU5rqZYfwmHIHAlj52RCWGQxA7hBL8833MCIuVxosbVqD7VRsOyCK5uVlXJWEs/fdMcgIVbTEwixLFMtX9G1fSn7mTw8/P7gzJCEHI+KfOR2UNLK3Pl4CK6Z7OOpj3545jwaIGPdR4oiCGeNeX0NokPi8iHEH6PSNgwE9ln7JFJNP6Pi9x14+i/uyJ4TPVYm3DRyjHBpsid7xodjxZqissKNg9YjQaeza0sbkgTmW1WqtzOJqD0rFRNQepxmzkwwJHBU+I559MzOx+otJFUYzD/G6CknUKL2LHxtLDph89JjsEA9/zR6Ek43vq9A6JuJITDF06BVxLyrFyP38Hz6/ZcQqg576T1K/PL/PaJeiZv3jm6+vnJ++8i7XIPHpkyuuyMrfYhh3MDpJDJiegF4z23K2yzh5+xrNoq86HbysP8EYInnEb0TWWZyOHes2cGPmlWZSufiokUTsdpuTNgwmNRc8cIQAfHCaGD+n2t/PBYk+eVdC/2uRnEUwWlq6KJGgTfx2rIZ9lSI0ZRW17lkjVpUbbK0JbLhvOVyTx9ViWre7DOeGFhclHDIkg+L40oeX2ZAt7t9NofTU0J1JZ3V0Cuf+sX0ORMCEHOds8/jkHN7TPoWyMUNsOSJ2fLC79JRC/CB5qnhoFBC7EURU3VMvbZI0dNs9OFMzHbA8e6BG8D9sAMu3b5fCpqg0vCRehvAQN+MLfZBibjlHbvYunAvclq7BATVKqVPtmwjGgzvWVWn8PVgE+ANvo6Oaoj9nMgkCdFn0K6btZxw+11D8HLWt8+Y1BJvXA+t8eob3MBTu1HSSkp1UgqU9UX2I1ksybEEU8tW3oGi1TTh5ooYi61pu/guaJvP+73sINE9OoLbJGcJtw//pgjhpDOwSmL4lYc5OKQN9ncJeCuq6Js459OWRftGYonFFxu5fw9vvU77I9UlI=
*/