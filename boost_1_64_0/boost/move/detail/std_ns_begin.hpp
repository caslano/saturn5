#//////////////////////////////////////////////////////////////////////////////
#//
#// (C) Copyright Ion Gaztanaga 2015-2015.
#// Distributed under the Boost Software License, Version 1.0.
#// (See accompanying file LICENSE_1_0.txt or copy at
#// http://www.boost.org/LICENSE_1_0.txt)
#//
#// See http://www.boost.org/libs/move for documentation.
#//
#//////////////////////////////////////////////////////////////////////////////
#
#if defined(_LIBCPP_VERSION)
   #if defined(__clang__)
      #define BOOST_MOVE_STD_NS_GCC_DIAGNOSTIC_PUSH
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wc++11-extensions"
   #endif
   #define BOOST_MOVE_STD_NS_BEG _LIBCPP_BEGIN_NAMESPACE_STD
   #define BOOST_MOVE_STD_NS_END _LIBCPP_END_NAMESPACE_STD
#elif defined(BOOST_GNU_STDLIB) && defined(_GLIBCXX_BEGIN_NAMESPACE_VERSION)  //GCC >= 4.6
   #define BOOST_MOVE_STD_NS_BEG namespace std _GLIBCXX_VISIBILITY(default) { _GLIBCXX_BEGIN_NAMESPACE_VERSION
   #define BOOST_MOVE_STD_NS_END _GLIBCXX_END_NAMESPACE_VERSION  } // namespace
#elif defined(BOOST_GNU_STDLIB) && defined(_GLIBCXX_BEGIN_NAMESPACE)  //GCC >= 4.2
   #define BOOST_MOVE_STD_NS_BEG _GLIBCXX_BEGIN_NAMESPACE(std)
   #define BOOST_MOVE_STD_NS_END _GLIBCXX_END_NAMESPACE
#else
   #define BOOST_MOVE_STD_NS_BEG namespace std{
   #define BOOST_MOVE_STD_NS_END }
#endif


/* std_ns_begin.hpp
wxJGuyRtH0tT6Fja0c+JQaHLbUTSreeXkvH1CAnvLXObqrcSeoq4UbW+9s/GiNlDAeHuBt33fSOgE3wr+iGwyugUTTELJb7dqD99M08kif4EDPAfk7f2WcWeBv3hV9OWEg4mWX5RkxHTIy1X7ARtlAXdNIbusm6Gjpv7xXXcXAM5yQ8QRzTVbj/gOhTtfJheiYLtKxyE6clUuS0yEo3JAParnQyRdpgVCqAXSijtwht8tuXP/wY+a5//ehn8Lo12W+e/+i0XFtJd/djtkalj8u9ZuUjDViEjm959KKJ+tZyB4ZAknwtMkaUXRBVmkLhf7DNJ5AvyCSncfi2bufo3N5pHUlINet8+eeETWBfulhe9u9ehzhzkM2TcSTOtfUZT8OgTIaJPSut/SQpgc/zl1Eq58f1QNslveYQjjbI4/RXbOUj7s0niDPcvfyF9+BcrlLChb5LQxJBm8G/5Y+nHj+jl/nGcz9O7v2+fOfqVnOMGuj0w4uch/ddeA9mBRd+keMaAv4Ob15ryRMdGTpCBcFkkQgPhc8/yQEh+gbvNxQfdfvyigf2uwbRxzasvZimvD4+cwgVoK+hHn7fZqblup87D5MHFXG4Ws3zQ0sObAL25jeOSh7It5nrA49F/9CSne/uPbtr2fy9Z+LSmeQWeFUKCk6sIK5X62V1p49w4K5WveNjG+FcdGBd809GJm3STvC/lxn3j5xa2x0U+LsgC2XPhr/5eED6JSbHuBQNHNegH5xEp9lTgMfY9OO1TTxg4Q7Umzlp2Ms6GYdR2AB/j/nU5go1SC95//qIlL7EV6jDPilj2fWe86OwPn8E92ol6tBJ4HYLWTI6druQD0gMQYZpLZf5JFiW9wxuEVn1PE7qJPo2CiBvB9s0GoAIAEDvgXY56/dlXpHPksGk/VWnyoQ9rX3BnzYXojDG/k7kwYkZqi6hE6ftKfe9vDbJKNhCyKq49RrvCStfmSPeMle745DFa1Eqz1JHme5LmbTofZN9/3kPFnrETR/djV+8owgNK15Zh6iZ/A/Suv3YDb0Xxi+bx4LjOnYQBov6pggv40VlmcUwMlhGEm9f2CG7uMGMiN0SupJY8J+E0e7z1ptj+X6AhthY7oJtVVq/RoXxtV7YEU0SQfUYgMEhpv/TTTuVbZqR+NiPGgfp2GvVayxzfTSzcXvBdQ6ZKmWNiQMaEwcKH5m9Un9ELUVV6gbIRnpdZwzEXvsnc/ued8h7vqCokcGF1V8yg7iHZhNzOkSKCaT3UQaja1aD/7WWhdMHZUqrGlAjDCZyv/OUmQyKMTdH+ARxuyZICD/+N9O5eiYQUqMWFVF2/sTr4Q9gQfU7BvN3JKDE1AZCmuKLA/SwHUkUBWvTSqLuHqkBWL0WLxDTrhbddYrL43T1MyM0+a1xxNfvhf88xPbhlIhmMHRNp5NazvwJtiSBg8FfmdDLbzZu7UEDncEpqnAhZ/lUmCjDhvNfM4oueF/GBOUUUB1vskJF3euSCjC4ZTV2yWKqNXCgQxR0QzbUg+plsN0Pz0mAU744UZ5T9wcjFOWVPMsq+RMpe4ii7TKKgOIYkoBdxc3w8JPVf/dFJZzvRt6nB2IzIoH7VT0wKOyVyeUZ9HqpvY6fUN1do6/NmZas63042+JY/lrw2l9qHjrXmMyGLCRo2ZR2UkRDwX/il2Q93esypr79BU3KnPsJLMcSw6HTt29njL0AI+rqUpH3HqucWRz3NVj2TPBYF5vIlU8xfcq+TAl+zKXA2SCSdjwIJLuxK5RCK14BrkwVX3Nn+X1jtd1t0+CmpBHSYVcO2fDXcK2VoP7VqWOKoodWq4RSzBk/0MqbFQ5OGlDY2RlWChUcOjxwvfMA=
*/