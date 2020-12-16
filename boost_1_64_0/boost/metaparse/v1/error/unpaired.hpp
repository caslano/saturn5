#ifndef BOOST_METAPARSE_V1_ERROR_UNPAIRED_HPP
#define BOOST_METAPARSE_V1_ERROR_UNPAIRED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/vector.hpp>

#include <iostream>
#include <string>
#include <sstream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <int Line, int Col, class Msg = boost::mpl::na>
        struct unpaired
        {
          typedef unpaired type;

          static std::string get_value()
          {
            std::ostringstream s;
            s << Msg::get_value() << " (see " << Line << ":" << Col << ")";
            return s.str();
          }
        };

        template <int Line, int Col>
        struct unpaired<Line, Col, boost::mpl::na>
        {
          typedef unpaired type;

          template <class Msg = boost::mpl::na>
          struct apply : unpaired<Line, Col, Msg> {};
        };
      }
    }
  }
}

#endif


/* unpaired.hpp
5aQgGq7H7eVBYDx4wse7l8lt0+4XnaT60Y/7Pkp+GpuKsaI44z/F91NoLolyFeCCxYBT/RuX3MUbMy+AwbMjgZJF25eF/Lf8Wd9LJB3thKT9OJXqJyscqP8RahMjk+pP80smtmEtyheU+0oHaXvG95q5YrIr50+ZLsNqROAOzPsZtBXcvXcxnbKfCfZFJtQXbd6+G7jJCYc9rm/lOu+ZW+w/U1KX4M+aNLxF3RnP7w3ljju/W+Kon2WsC3h3hxWb+Sns1s13lKKtBTygsrlG/BiGOVGZyBpTbD4DFXq7AHhogPLg8zj6ULcy3kS5aeDZFedyF/rlMBNp/MU96+N+z1aKkX5/80FqzvtwX9CThNL3uIjsKNPIN5VZ9ukwr9A+4+N6v/u59y7V8ZmVywVM+BOfDtPTa6WbS5nAmnNZiI6fm2bZvhChwfiROQtJB+G2NaqD31d2PtY1wB/zBXef92ryu24m2I4GFtvvmqrYv1Rb+55Z2Arip9qec2bJL3Oq/q3JuZF9wI+gg12uakm9qgXxIdLLzwh2X4ph9xDsTgG7j2B7i7IPEOxaQfcgwXoE3UMEWy3ofkWwhYLudwQrCLonCHa3gP2DYO8WsOcI9lLBL7XEwR4XdHMIdqqA7UCwvwrYTgS7RcB2IdgfBWxvgg0K2P4E+6CAtRHsACHfPIKtE3SvINgOgm4xwa4UdL0E+5eAvYZgFwtYH8GmBKyfYNMCtoxg1wvY8QTrFLCTCPaQgcWdR1M184NEINj4Rsb9VarPsgH1uDtiMLL1QiD/+ARwyB/jIquElmvWpMC78DDbsRLhBt3djkJ+AEuai6SZWAr7PkSXB3oIjqe0vVXg0B67Dmn114DPl+l9XShAlt1EfPtRjLLkBGKOWxyeHsmrZ6GDwPuJpzo8vXHMa8ubo3wj+7FNJLdtcq6KpZZ92zOoPN2vofMBqETmrAMN7HIkzY+L3THduQ3ownG894l+ClJijy3uiEYYuU7lvF5LFBp058Zq0UTKclMil/v5Gq3/OR3TXaDSkXZEXOEjjflVsrUa7jDz2jiwv9O/Uat1VSAf5e3hMxrqI5M5iTuB2/pxva1YYt3u3jTWa8MnZ5BNvr1xqauTzhYLeTk+/PVfo8mXaRzyGLtczJulhPN4fNafe5sKk+VKoCK5l/wc0cEr68hUPeFt+3jfSjSjCH87Rm5/6PG4yuGdCgs0K9ZC2ULWL8l6aoYR5xe4WuBczTwHryScKSL77lqnI/r6wKi9UKyIPO9fI/xUbQPEdpq0FYh5fCPPnVErkT/BRG6nCA1PLv97LleXS36DeCT59fyWoJh7If1wjnRJwzXVJJ/bhJ5JhzWrrxrb0tuZT0cYd0cAV52Ub+l/x7WB2BZRNR0rug7x6e4U/VHIuxde6nafMB34NnwNbIlQGvMT8/l7S3QaNvQ8Dr7uaImA/du7SW4aAITn/Iw/Ueyjvx7hszuypz79z5rQu65n/j9fMnMutmphY03yv5foVeZsVnz6Tzbkz8ZF5kC6vzE9GdSYe3fPj8hrMZ3H1T3XA3IMIbTkGQop30NEQ32eh4RFZAqtctPF2SLRFrM1Rgsb8BvCQwXFvKK7xxrVZXqGRnqmyLGx80Qcl87r+ftux4vtF/ava+FiybX4yeDcMKRucuBeweqhAd++P6XMISZjG/aP3R1dH5DFMXxW6JqSKYr3ZZ72dJ53eVW9t6/nN+bhLrSAi6T7S0SmdteBEAr5HP1z8b8G1qY+70zcrE32LE/aq79pttNFKv16/67RcNQT7eR2hIjQAJb/nySXsY2RDhd0/6F2UlixlM9W885ZzmXl2HuO6Rgt2pbqEX4pjphq2Q0FpxOSWbU=
*/