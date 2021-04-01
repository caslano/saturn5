#ifndef BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_C_HPP
#define BOOST_METAPARSE_V1_CPP11_ONE_CHAR_EXCEPT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/unexpected_character.hpp>
#include <boost/metaparse/v1/cpp11/impl/is_none_c.hpp>
#include <boost/metaparse/v1/accept_when.hpp>
#include <boost/metaparse/v1/one_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char... Cs>
      struct one_char_except_c :
        accept_when<
          one_char,
          impl::is_none_c<Cs...>,
          error::unexpected_character
        >
      {};
    }
  }
}

#endif


/* one_char_except_c.hpp
BF31Xzt/5QUb9zdANLQ9E0y3sgzmLnizFIsIRshbTzvI3ZGmHg1j/piBoP7lyG0Je+i4l+zPjTsV0cWV2m7K2wooBYrmWAdVvHlGskUcT5zup6jxrjxpyhv0dkthhtEmBLPM4IsDuGKPzqIgerxRaLR2FeT4ki+LLDf0OK4m/9JsEaFLoCzs01QonXSXDPSBJusMD9EAt7nSuu9EDLKjoF+/HEzWrYx+axtHPIdtT7JPUL7OqTqIrN4tNDIn2FMmv8u6NoGB2b1YEJCOm2u0ATRk9QhZiduf4UqNMsqhwKGcemljNSTnAx/92hBHZnUr4SOXakXABJ1rpY//c903fTyFk+YcbjBy4fETJoCUEBZ8yFnAm6QKYRxb0Eeh/YgD/iBYgoRAMs9mo/8OUHo3t7yHURh6z7zPRilAOM4VCUnFUiS3LBRkyRt42fhhOs9WuJi8x/cQHl8cenJ5hT1/vXFhMRIh4vXzNF+dZsURWTDDyASqMo6cWDlHtDihE1g7SgxeKpLfu4/168n0RRnzc8TCdTVnGVWzg2zSIvIC42o+456p/x0KC8I4gQ==
*/