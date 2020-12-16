
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_CLASSIFIER_HPP_INCLUDED
#define BOOST_FT_DETAIL_CLASSIFIER_HPP_INCLUDED

#include <boost/type.hpp>
#include <boost/config.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/function_types/config/config.hpp>
#include <boost/function_types/property_tags.hpp>

namespace boost { namespace function_types { namespace detail {

template<typename T> struct classifier;

template<std::size_t S> struct char_array { typedef char (&type)[S]; };

template<bits_t Flags, bits_t CCID, std::size_t Arity> struct encode_charr
{
  typedef typename char_array<
    ::boost::function_types::detail::encode_charr_impl<Flags,CCID,Arity>::value 
  >::type type;
};

#if defined(BOOST_MSVC) || (defined(__BORLANDC__) && !defined(BOOST_DISABLE_WIN32))
#   define BOOST_FT_DECL __cdecl
#else
#   define BOOST_FT_DECL /**/
#endif

char BOOST_FT_DECL classifier_impl(...);

#define BOOST_FT_variations BOOST_FT_function|BOOST_FT_pointer|\
                            BOOST_FT_member_pointer

#define BOOST_FT_type_function(cc,name) BOOST_FT_SYNTAX( \
    R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,* BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)

#define BOOST_FT_type_function_pointer(cc,name) BOOST_FT_SYNTAX( \
    R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,** BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)

#define BOOST_FT_type_member_function_pointer(cc,name) BOOST_FT_SYNTAX( \
    R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,T0::** BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)

#define BOOST_FT_al_path boost/function_types/detail/classifier_impl
#include <boost/function_types/detail/pp_loop.hpp>

template<typename T> struct classifier_bits
{
  static typename boost::add_reference<T>::type tester;

  BOOST_STATIC_CONSTANT(bits_t,value = (bits_t)sizeof(
    boost::function_types::detail::classifier_impl(& tester) 
  )-1);
};

template<typename T> struct classifier
{
  typedef detail::constant<
    ::boost::function_types::detail::decode_bits<
      ::boost::function_types::detail::classifier_bits<T>::value
    >::tag_bits > 
  bits;

  typedef detail::full_mask mask;
 
  typedef detail::constant<
    ::boost::function_types::detail::decode_bits<
      ::boost::function_types::detail::classifier_bits<T>::value
    >::arity > 
  function_arity;
};



} } } // namespace ::boost::function_types::detail

#endif


/* classifier.hpp
X/SuRQgZU5sgF7uVyMhZDQ71vUFT+F6k30+K692bPcftCYTp2Xe9kRPeWLjiC2BNJMWOZ9GhUYUsvK4yATKvhCPRClJkyByGn+4tgmLrhyh4gyZKNBNAgQ090L0rDoTDE9FtmRZ8tDMVrGbbfascQharqdEtYwTXBLLxez1ngUfYFYVYOYMxdzEkCMkirWP9+CfuQNAfO4MfMvWHdHs29O7ZB3T8xm3UXp2K+BI64UT2cTigPYNdUQpAmVONOCZyHfmo6mBf7TXAVG4MnRktQS/9gvDdTaZINs4dmYpnob1T8cjl7Gs0upESVwxbgeimx7FDXtGo+ctHeLxuBxIuKcCE6atR4+z7PIHd7UjqIA0+mTmAbli5IC2O87By9v2+BrsUUO3PQ1fNdKCBcx+eptiEZHpugmSLAejGCEG/7iRIx1ZhXCQ8YPt1HYTFvYUMz1gU49KC7r65gUqrIpDKShydXPMB5RwcQ8ZyN9FkcQjeFSoGkySieKOQOiSZPQUVel/Ajdiw4TYVtLFVDyMLtAUvy9d4zodG+NAUghrWDyFZUn84H6MMRyIMQT1hFXy1dsNKJH0Rxm2DIitbEflZX8wx8xDy3FuFgsdskKrQFGS+HgNqewrQi9+DOobHIOs8AxJKtEHWrRUwNGiKr599zpPHEY7sGBTQMsVisDbXBPNRMtDnHEUvM7SwbQ2kKORtCGKY7gJZg8v45FQbyrK5j6N0e2gmxyF0lQscKTiBNnb4ocKgYyh17+nZ9yJc2MqWtUiK3Q4btcxHGifsUVTeLtDuv44fLYoAmanVaCicCiblvfFOz8dI2rATaw8KQ9Elmkh4/QqYcIrEWvNV0bniBFTeT4QunLPHBitPgntDFeq0kkEKw9K40bpcdFNoBdZB8xXt0z4ACpIBYOA4e18S+BAZr9bCl6+vgLHlF2BH8+xz50wTVEazA56VnATb7R6IuOYrZLe9R1y5+vjpR5OoSFYMvq1yhht5LZhTRTwaPXgVNtbVID0bRxDjUAU5xtPoJTEZShx3QlWtb8BEpA4SE9oRzW5ObAsvGdCGyKJ1uYqQN6oDpoZ8QCROBTxphajeqhO/oaCNDpXvxOWjI9GqiUvI1Oke1NllolqacvAZ+4TZKdDBsmFB7PEOazjKfxSjHEgCMpLjEGl5BrUTkcLx1xmo6Mh6bNBbB7VQvsK+GQ0Ad1I8ZhLmBU+aiVBvUhEiDQqDVMUI5JhxBl3/mIuYKp1RtOAL1B7cg/yYFaFiYxj2QWk5HGxCaDAnDujFaXFx33NIuKgT7S35hrgfV2N8wz5glLgeQk5XQfMXHlzMKBQ93hSK5FuPo5lj9Oh5wBp0L9ANbMxWwDWSU5gU2RFUPGKAr193AVTpHJCH+V5oqOnH6gs6gE9mArWUqUOWgDSWxgFo+8oo1LQ8Bj036Me8mByg8qgtknm4G33134Yt670Hm1RbITFJDbXRC2L3ryiiTY8GoYqrG03ekULZxV2I/RH17Dvyu6ifIwlbq8iLrvWmw+miWnh+C8d4W0TRoP40Jp+cA2tPj0OOoibypBlE+k5EUCY1AD3396NTRhmo+MMLuHrzJdYrlYPE/Z5hrqv6UNGmMTgXeRbFvNSC4daHwE99Efu6Lwh8Ju/jxo8YkNaTS3CGczmaEvKHg88jUPozbvxxnDSS0z6NPSDCYCD4AOav7oW6z2JIM3Q3XEt5iMoZN6MuojasP6EK6WSIIT7tSKTirY0fpk4Ad9r1GCtdB1pP34SixsXQazFfYFZ9AB1Z03j+hQHY9uAoZntzEqVveoHxmQWgLCoDOPzEGrntAlxj51vkme8LJ7O/gjFPHD59ZzO6WGSHv1K6ieiifLE=
*/