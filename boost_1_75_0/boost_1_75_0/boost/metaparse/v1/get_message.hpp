#ifndef BOOST_METAPARSE_V1_GET_MESSAGE_HPP
#define BOOST_METAPARSE_V1_GET_MESSAGE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_message.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_message_impl;

      template <class T>
      struct get_message : get_message_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_message.hpp
GdGdjsfjYCc4HEe/DsaBjwpzJpmCnJtYAvPmIYdV6kLKdg1wB5TuPF6CoSRFgMWeWqSD/Uptx9UzIYCdEpesZr0RAQznLj6SnwYWkd3g3F+Aw4f3eydtBfOdvD2O3Q6GGP8OfgOefRgb4v+w6VpLCwxI2m9gXKGJvY0bLLbxChp4NC7lIYwS2S4BDRGXpSn3W1qNHnnXYjVCEw6Bf6lHPZO+FcbMhS2sLez5fhgaA3YuCqBhn3WVkLG2pwQJZ9yQ1/GNSy06AkNK9hR1M4xDjOhQTAnZF+ZyEbVOt5mNIIkSF9ScP03+RhG+fL7Ef1wAozenF+DeBp1zbkQ7z6qHIhTtAptNMQZMPAGDpjuftDyVSE89BE9pik1JU9GayK7sS8crt8GVHQq+z7ClwAKAedCd1yywi0vpVZvAtgBttMlFEm9cx27Qc9SU40/alX/agHJc6DpQSZ5lC4NN5KvZxOvopIkfFb6ay6+AOU539p+LXyALJaWo9WCnTPGxYAN9Yo20gWaAGASeVI8ApCPQrl1FgKfJ3QZjPWhomjcrbipjNP5Y8tS9ncpkjqaz6MeKVBkgSImXgkkWI+Z9ksWwHkG4siKC8K+Fs9kODVCXHDBWFlqPIhOeqY7FupM2s22ULfdTXUHwSxXb0LwDlThwUS+8Iwl7LXqnSeI7ZELLbS7EDA8vWxLjvYF1SIhpJevILRss4i5ICMZkP/5h
*/