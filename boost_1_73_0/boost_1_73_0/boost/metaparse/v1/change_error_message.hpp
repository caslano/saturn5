#ifndef BOOST_METAPARSE_V1_CHANGE_ERROR_MESSAGE_HPP
#define BOOST_METAPARSE_V1_CHANGE_ERROR_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/reject.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Msg>
      struct change_error_message
      {
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            reject<Msg, Pos>,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef change_error_message type;
      };
    }
  }
}

#endif


/* change_error_message.hpp
GtbC5k+vmEO9q5MVAoMzB8l5JuQCuGG05AgS1CiQMrVcUpnVXJIgaHaZc2vGceJGxV1X75rX4+lsNEmaLuhkfDMLojg+A9/PqtDIb4+Cy22SmPwt12K+AacN0LlFMk431y2QU4OjjOPrmVxZj6SPlS0ClFpZxVQxJHiJQh1pV33sA2VsAj8RapDPSNo/X2DoBNhKF0Hz9upmOhp/apBzxniJr4+DY1fDF8H++iZxCjkBB979vVvfe9j5vzUMJ7DSYuBV8SsfUypp0GYe9846WSdGu/A0irv9Dou6vayd8dP4oZ/1vJekmAYHFdNgL21w+Hj9AFBLAwQKAAAACAAtZ0pS71mIFz4BAAAhAgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyM1VUBQABtkgkYJVSPU/DMBDdLeU/nII6FqsglspEoFJEp4YmLWI0yYVEOHZkuw3591zclooRD7bv3rt3H7bw6HwhHSZMNLoydHzh0BtbuoQ95ylbptmObdDtW2SCXzDBj/QryNAe0E5dUxLDYqeGET1dCF+oBrU/4UUwiOBCVMIq3xH7bIHQssWQGfadMrIEG3JD3/ga+toohKqhTSqLshygNL0eeVhSMD9GgyhM20pdBvk555OXdZav0vmE
*/