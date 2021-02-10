//-----------------------------------------------------------------------------
// boost detail/templated_streams.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DETAIL_TEMPLATED_STREAMS_HPP
#define BOOST_DETAIL_TEMPLATED_STREAMS_HPP

#include "boost/config.hpp"

///////////////////////////////////////////////////////////////////////////////
// (detail) BOOST_TEMPLATED_STREAM_* macros
//
// Provides workaround platforms without stream class templates.
//

#if !defined(BOOST_NO_STD_LOCALE)

#define BOOST_TEMPLATED_STREAM_TEMPLATE(E,T) \
    template < typename E , typename T >

#define BOOST_TEMPLATED_STREAM_TEMPLATE_ALLOC(E,T,A) \
    template < typename E , typename T , typename A >

#define BOOST_TEMPLATED_STREAM_ARGS(E,T) \
    typename E , typename T 

#define BOOST_TEMPLATED_STREAM_ARGS_ALLOC(E,T,A) \
    typename E , typename T , typename A 

#define BOOST_TEMPLATED_STREAM_COMMA        ,

#define BOOST_TEMPLATED_STREAM_ELEM(E)      E
#define BOOST_TEMPLATED_STREAM_TRAITS(T)    T
#define BOOST_TEMPLATED_STREAM_ALLOC(A)     A

#define BOOST_TEMPLATED_STREAM(X,E,T) \
    BOOST_JOIN(std::basic_,X)< E , T >

#define BOOST_TEMPLATED_STREAM_WITH_ALLOC(X,E,T,A) \
    BOOST_JOIN(std::basic_,X)< E , T , A >

#else // defined(BOOST_NO_STD_LOCALE)

#define BOOST_TEMPLATED_STREAM_TEMPLATE(E,T) /**/

#define BOOST_TEMPLATED_STREAM_TEMPLATE_ALLOC(E,T,A) /**/

#define BOOST_TEMPLATED_STREAM_ARGS(E,T) /**/

#define BOOST_TEMPLATED_STREAM_ARGS_ALLOC(E,T,A) /**/

#define BOOST_TEMPLATED_STREAM_COMMA        /**/

#define BOOST_TEMPLATED_STREAM_ELEM(E)      char
#define BOOST_TEMPLATED_STREAM_TRAITS(T)    std::char_traits<char>
#define BOOST_TEMPLATED_STREAM_ALLOC(A)     std::allocator<char>

#define BOOST_TEMPLATED_STREAM(X,E,T) \
    std::X

#define BOOST_TEMPLATED_STREAM_WITH_ALLOC(X,E,T,A) \
    std::X

#endif // BOOST_NO_STD_LOCALE

#endif // BOOST_DETAIL_TEMPLATED_STREAMS_HPP

/* templated_streams.hpp
VVJMT1BUX0xPV19TUEVFRF9MSU1JVC4zVVQFAAG2SCRgrVRtc5tGEP7Or9jSL7KHILvq1E1jZ0okEtNgwQgcVzOaYU5wiOugO4Y7LGvq/PfuHdiOnXrsD0EvB6vdZ3effVbuyobDH3ZZroaDF6/MfDK88LwLilvxD83V/wdk2S30Lwxc4fmKVGN4iLrNDuBVUbcwMlHZkOtU32fZK9KtdJH6a6yDV5m+RUsfOcRPRbNv2aZSMJoewPHbt7/DG/jl6PjEgRnhjNaQKMrXtN04cFoYy58VublxJX3vAFVAavcRYFoxCVKUakdaCnhfs5xySQsgEgoq85at8YFxUBWFktUUplG8DOafHNhVLK8GnL3oQFaiqwuoyDWFluaUXfcwDWkViBIREL9gUiFmp5jgLqanoGi7lQOMLoLUUgC5Jqwma0xHFFRKNfKP8Tjv2ho7GRcil+P8jgq3UtsnXS2xmi3Zg2gUKAGdpA5ofwe2omClPpEiNDbdumaych7KwoS8GIsWJK3rAQ5DGZV9CxSSgS1He0KD1TOlDym41Nl2ldg+ckRaB6CyazmmQ1rQrxBIvAMdL2hr/A0Rd1kGlg3lL4zsofYCBMeqwPYSCBIb1kQy6cBVkJ5HlylceYuFN0+XEH0Eb74c8D4H8xlq
*/