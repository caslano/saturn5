#ifndef BOOST_METAPARSE_V1_GET_LINE_HPP
#define BOOST_METAPARSE_V1_GET_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_line.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_line_impl;

      template <class T>
      struct get_line : get_line_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_line.hpp
FXk41tD9+8ksSI/8RL7ENeJVMprvSxvRC7hJYEmJ8/+S5/fj+VJ+/p/iRQjkEPCvERQKt9bjrSv4rcCmA/4auCk9GCRnqHsNFMI99wpwhRasgQCvosq8y0g/rTEcSFRmPUKFc9uNEtQ+OC0FPtVdBQsrtdDbL0UHiL9AHmkdiaSrM/6pp6u7hKhnm0EMBSiiq+jddi7UFaMA5N+YHrggNJ9EuDHZZcONKQpXYdFqcW6/OLffONcsBqpZLuVWWBAfReKCAFI2gWvgwjhxNs8q66OKrLJPu9Gq+LibVKXnx5J1501+6R/8+EI3Ov80P75zNh1f5xvBy/z4PD//FBy1/MepiK2lthg4KMlKGNX7fbHWHOmw1lo86rdeAOwteAITpAYTGTfDfxvZYmMLZL7CKTudyBEySjPGsynXTeF84IqEOYQNgDZv937klj61Bq06exAP9DhMNyw+YGzNFt6/BafSNFs4C1frzpkL7UrTXwATKAHWO2z0MWJCZA0ymBZjX9goaoA1S4ck8vFs075QhVG+bA/QnasCjF2iR1NsDlAZfr923xbaHNgtiwJ2RWw2+62bTV/aHGT9tP20OUB/Hz1FK1nUznjH8ha+OexXTBSFmwOEY1QJj2jRdNwZhlXxjWG13BjqBd/LzzfqpdVbN4XhC2lTYF3YVmJy9XXlIxS+KTSLdjUb7XIApe+0IaVXKNbCab26S1Iu70Ik
*/