
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_type
      : detail::synthesize_func<typename detail::to_sequence<Types>::type, Tag>
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_type,(Types,Tag))
    };
  }
}

#endif
 

/* function_type.hpp
yF1e158cbTKAs/wlktSwPYM18/qRkOnfMjH3KpE2bBrD9AyBtpmBZN69KAhU7YQb790i+2tOhgudV8LA1o+4c8dHkx2Ffufm1toCu+9+BqZBh+Hk0/HMJ+OPkQU3ikBQeB0Y9lzLVCutIR0GPmeeje8Je99fztmK9IaNd9O4kwd3kfbaV1ztAj+QoQPnkzERVfE67yvu1zMm8lPzELj/oDzsmnOe1Ll0AW6StVx67/Gk9bFvmSk3x8Oi1Y25XWjTMU+vMVWSvofzF77h5txpCHOvVuTO4vLiz32Ow5wx28mpjoM5+4Qc0nufHRaePwdLdbVhr8Ufkr/+nCu6HqBXt61Es9WXhBQsAvtnzSCqwlam4+lvyM8rj0Hk6M/h6TUl98WGEWRAlUPcN20fkKL1njGGus3I9G93cx+/GAWTB3ZkMtpdIE923oeqp7eRLEVFiPxkCfQ8l8Lc/rE7afF5ErF1KwxXBzch1Q5UJLVO9yftV39Eoi4vJT3Gfg1ZdUpB7KR55MyIxUzEIIDZvRdyu8e+JHV/CCMvR+XAwoQO3JFCl0hc593w0eaFZFzpG6R+FgeBv7TnEg92g6mFipLNy05B9WFDYfyjGXD01U0y8NR6Mk35gnt+pjt8Vs3EfFX4IlwbXpP509hKpOeCRszuKVVI25xw+LDUUzBkshDxYhuJu/KKq/OwA3RYNZIsMA0iRa4fZjR76xJo2prr+KI4+L38mJxLPU4KrPqcazhmG9ypNYv4P51Kuk1VkqQUAk8HKKF5w/qgqPYAlG3fh5jw2pD2xVrY3nUn2b9oGWmj+hp61igGHd/3gfk9a5CvuUTm6nkl6VeNY2bW60smH7rPGaaWIlseTYTjR0dD50YluNC4DtCrXQWyomBt4vO8EtQ6lQrlxrQgZWtdIrfbtyJtfi4I00bEwN1RneBYnQ2k5r2CZNWMRIgtdwL2lJzPNY6+Sew1ZzI3XnQnlSdomT9t2U1W7DNDRpX6cKxLMFTtVR2qLtcyX67MhpRadugQ15b0KhbCTLy/nZx75QdLz7UhkyZtJVGJqRBXMAxuXzhONq36kWm36BQp/vA0fD3mIxiU/Ah2fPoSGtirwaVei2D0zbNwucpBuFV5LrE3KEAelWhCapQpCJNeNuQqV39CNpweydXNnAObsYz+qisQEgPcwYmX4K+rDsKsrhvBL7MeN7hAOOScfoDjYi28nHiDWTr5JBx/buNixmyB0qqmXIcS08nisBNwullvSLVf5ZIuHiQ9XpVkPul6jpQvPpCZujyOrFs/Hl40awm3b5/kvnl/Ebz3IJBZtK02OVW3D8OufUpKJ1ZioitoSEjZCzB7yjBy7tQd5uZBApmtZ8GVQp9A83KzmG7MJeg9Qc1FtVtIZnT7Emom3Yd9t5qArbSSbBxSmGwYEwW1V19naiZ1g1+WTIAn9RcBOyeO+6zhdPjhfjfuzMcFoH6n2swHZ76Bvqv6kkp7PyVNb07kktb3htdZq5n53w2DJy+KwN0K38GkIR9A3ar1IKDaPDJCXweuf98DpjVYAQ3HlSENi5cnv5IFzOJULTGvq0CSzxmg5YlxkFDsFJk3dwa5V2AxaBaooIahFzA+SdAhtSZ5sWAtsF13kzpdZjCLY59AyDUd82GVBxCRUxHCjZnk2fIRsCXrKShm3eEiin4AXdoUY9aplpKISeOJ/4qiZOpvfcjqG2fIoY+Xkftn3iON+33KqZbGkK9r3oRODRNJ5Rb1uLsJ/Ui94V8ygZYGYJ9QFxZMqAQ3jgzkan1QB9t3JFf7yniS7pNGqhYfAfPiujMxMw+TL74/xy3xiyHrteWhuj0QejUewhRTFIKQyL8yx37/GoqppzI=
*/