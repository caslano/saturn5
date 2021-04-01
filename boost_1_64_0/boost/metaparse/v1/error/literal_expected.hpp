#ifndef BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP
#define BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <char C>
        struct literal_expected
        {
          typedef literal_expected type;

          static std::string get_value()
          {
            return std::string("Expected: ") + C;
          }
        };
      }
    }
  }
}

#endif



/* literal_expected.hpp
ILHMqvR9g6/rsnAw0f2z8lTfUzr1DqvpZ1Es/WQTk/HK3wNrIuekVwBt9AG93RarWv1nnMrqE7OE3Uvh8SRRuGXBptgzdOaKLMq5SEFDgcoIgO+Ui0YdSv63FEE32WledmjWZ36ZGMLEGJlcGzsXMnHmqs9Wp2bigSYpBtX7Oq3NjjQ/D26JPDMDhcyn/qW04X818OekM5JeWSdFA53BGkfAof4qiLQCUiBkUZRAEM5rcXfbmeDFsoxfv00AVVwiudKFkjJ/7sv7pgdIniknXJvuyVyF8A0vbWADdbeg26RkTHASWjU7qeKFY/RDEZ/QlbqNnTzc01KocUl8JRdHA24w9Z/a9OObz7ywO/cNMviYgg8MVP1724409s7jCUvXCH3DmtlDxVFZF82PbOKrI7KljHfPg0cMn+ID2dK4h57JR28g30/OBcaDQzq8saJVZp9q61y2VhpnSdCKIz/7DLWvB3kymcVzYiZST6DW8OmpiHqRngZTwbtuAdY5RIIETOGuZeg3QI6d8vEO8k0VZuceuOe3scZY/vB8t+dJMojq4ISKCGYKPBbdOw==
*/