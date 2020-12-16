#ifndef BOOST_METAPARSE_V1_IMPL_APPLY_PARSER_HPP
#define BOOST_METAPARSE_V1_IMPL_APPLY_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/unless_error.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct apply_parser
        {
        private:
          template <class ListToAppend>
          struct do_append
          {
            template <class Item>
            struct apply : boost::mpl::push_back<ListToAppend, Item> {};
          };

          template <class Accum, class S, class Pos, class Parser>
          struct apply_unchecked :
            transform<Parser,do_append<typename Accum::type> >::template apply<
              typename S::type,
              typename Pos::type
            >
          {};
          
        public:
          template <class State, class Parser>
          struct apply :
            unless_error<
              State,
              apply_unchecked<
                get_result<State>,
                get_remaining<State>,
                get_position<State>,
                Parser
              >
            >
          {};
        };
      }
    }
  }
}

#endif


/* apply_parser.hpp
8gb1hyIL6PGrTVlT9L8q8zkVwti4rkkd7vtXbBP2KgqsNAP7NXQqz0ecYZz3s1bw+1fGtZXxXoU/W/UWtpv53wDfW9yOD68JHmCdt3jJkc6lH/bA02bhA7nmQbCZZjyPzX3jf0TH7sGu3IcOfc746ir2J+DXEuzDzazBC2DQl/FbU5gn/DR8TzJlIKXGSXRgDFhoEc+dX83zeovA8IzxUkPPsQdhRcTbtLubchnY/flj+GruOXYNYxuPLcLed88Be2IrDF4+DwZpgj+YS/tIYocxyeyzLaFuPXOqwZqDbfPiWYPbaIux2X4jfFuKjILFlnDNJnRh5SZwBHsWw/eTn7kDez4QDByB/14MfsGG3wLGevYvYEhy6pHk+WZz3Z5IfGEhz00sBC8Wsg/7Pj6Dsa1Fxq6YZ/g767mcl9nr2udhj+UhrkEvVoCHaxFfvUFeqt1G7CH+5nA7/Bu5ym08o5OwlHFxzXx8y30b8JHwZwJj2PwmmM54ZgEMsBad6Yw/rIGNu6MmdvV68lzI3f7a8DEJrN0e390MDHY56wMWn42uTqaEXouPimAtWZNLqOv+Blh9JbxEfxpfCQ/IgV1ZjT0OMES/jcQTYMEuYIDoVfgf2n8brZmYZj24u5GPZ0ygjSe+iXqF3CF/V2Uc7cmPfB4BRmEM/vsU68u/8ZnbO6BTzPE58FtRCrlbfHaVJmDCONZ0HLJbgJwsZm+Ne19HHmtpOvvnM5Fd8iiZMdiQTeBXxntsNzaDe2X8k737jI+y2AIwvikgvYSOlNB7DL1LCx1CgNCDoRcJvdtARUUBBUQFREGUosJFrqhgRWwoimBFOkq7CNhQECn3v+xek9vrh/tBfj5udnbeeaecc+bMeWd237YHNS+7vYC/c8k4RYuTGfMv9yuT7leQ53Hlv5dkvS/9UT7B/mH2pbKLy7JLJ6fbDhvvRuzZTOM4kz/omqIFxPXYhc3a9Xo9zxX78M8LWWNYo7f1eSfsjPN8yPol22vaQTbLH+X78OejAtaA3c3f7FlUeetXeVMwM7e+Elu8h14kfMSGfmNvsrlnWAe+qM874/xy9eGb1dIfB+W71do0v7F62L3miYFv8Vx3lDqMqxB8XsMXqhV5pey+aM6f+viC9ax6D7iNfrQ3b5o/RpKHdqXEM9mwV/Tx9mnWDKesPwdZx2xVZ9fOw4NYiMVYiseQso5dIlsl1GFMNs+Gze1Nl7JXpZRxnTmUn/fmSXLwM3nXloe7Wt9d73nqH5SREhGo+Zm4g3X/KXaoVHHrwOxsx0R6dyt7Yq1W6w3zxktixtZpu1YYE/rTS90zsUXvDDfu1tSTa1pfNdO2NPLfUwxUPx/m0xzi73b7JUCXxQysud5ty/+11hxbgY9+yjr3AL1wv0cuiyuN44OeieRXSo+CeSBLK3aooTm7T9CXNM9ctE6zDkoWF5/6gnV1Y3OCeFeJ1hFiBOZ9n6fRwZv7sLueQbwZQx4a+qw/XeFrj7mKLByyrlzF3pHZ1WICG9n7hb3IQlnxgcfVdwCfagpfxPz+CVt2kB1M7mp+kV6ev/LtYvJ2lo0ka5nJYi526+23ree28QGn8z+M9w/aunIJnz3C3td89MQen52XjGcjssvfv/WgWJ5+yZHGt9S+mtozayCdG6IetxgXMvu6eidE0A1+yqVLZKyluYdfHEcvu4jdpbUmk6WN3e3WBZ+Qi67OLBuT+Z3Finbx1553zWU6Zo2daD19Ax0v+rp10Wnz6e/1yUrP3NjQqfIWWUrOxnomm6ad/MXLp/V9dfagKDtovbSHnB1Et4/5xNbIl7oaW3LVZJaY/HtiWzPomXVfh6nkfYv+YKMmdWCXHidrfK2VH4s=
*/