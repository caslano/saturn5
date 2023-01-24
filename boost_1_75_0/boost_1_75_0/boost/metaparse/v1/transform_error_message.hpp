#ifndef BOOST_METAPARSE_V1_TRANSFORM_ERROR_MESSAGE_HPP
#define BOOST_METAPARSE_V1_TRANSFORM_ERROR_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/reject.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/get_message.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class F>
      struct transform_error_message
      {
        template <class R>
        struct rejection :
          reject<
            typename F::template apply<typename get_message<R>::type>::type,
            get_position<R>
          >
        {};

        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            rejection<typename P::template apply<S, Pos> >,
            typename P::template apply<S, Pos>
          >
        {};
        
        typedef transform_error_message type;
      };
    }
  }
}

#endif


/* transform_error_message.hpp
9w6MPtwpKy2oW5SjKXJC1+jhaJONnouhZxxObABNr9hJP6FjpE7RS5wwQTna90RTCyDcjgO+401tAE+tOwCjcIIBC8yL4z6m6wH4hfND9ILVbEDCRS4UmSA+fJ9jHHl9iL5r/sHI5m/MgXttjrYrD+vIpciL23BDtz0EP+m6Iq7j+2rG6bWA7a5hf7Jajn8G/KMh7oINeJpMAn962GqWfgbWWDlcQLRHqnuBvULI8aSQaE7oD7LyCKsIkXf7faaIqssy/Y5Vl1qUYhEcb8jKOp4sjp5iRSTto0c2CvVPQd2u0FC6mGfY8gR5M9yI+ya4EcdH02KMZqU5ms+GHGc0etAcTbvlhKNpOf5o0B4XfarlxKO5z1CLmuGPTK+V+1b2uMH64vtW97jBKkfBadzxkEE/f6sA9qaMnmcg87arBjNHbzuZPz8eIuK/hwvb3hBLHEcc5J+eYABi9ab9znWmAQjloCAxT2itCypt+bo3WhCI3rUC0GcFjvjfD1oTKodXKEe8BW+zLLYc/Z9Uv0zH70Hd4wRByWMNKjdmy0Uwbge6oA4IKFMcsTTU6WPuFzh/fvIpOlrEMDqzmEQ5ChWJrmV7DNyqDCgXG47slXFl1pmkEdvjLXyb9OkcdRUVLFulGW3oelBYvttsKdxelcAXkN1cq2pMu/0QUz05XDxFSheJRQpWd8Nl9tZeZYShPSSswqh+Yf3w03Cr7Ukx
*/