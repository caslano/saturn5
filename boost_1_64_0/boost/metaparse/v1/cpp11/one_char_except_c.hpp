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
mf9xOO8Z2sJ5TJ2/ocaXm5WO+Sba5xZpz6q03dJGBg6sNeKvu7Z2G/J9G/n6w32vkk5xbZ9ba1wb7VsU1jba7RRXlmsLLxdXDp4TXM5O+47k75jlZBzJCY/PdzL/iJcc/13F17vB17tqfN59j/mMMMPeiLSbAXtPjeZt/nXLewUeouWsQf7YpYkwbH/4TDLpNwodf6Tjw5IWspZms4ON3V7g07EkiKN6N+GM4c9r5BnD+rVtiWbj93G1D5jqNKf9weHwRPC6KUym9wGffa8a7bLYOTdJdWjspoWpVE8q58cV/p2D9+CN7MF/ZeD39FeinpNsuVY3rGY8okw6Ab6AnTLQHYDTk13Z1U5Rnh2tLOtRlt+MKEtrsiuVThEmYHQLVRACPqa43S2t1uRwY3/PwIqBwb4O6C3IgJPuPXsq5OCBkXIAuIEue2CA0XGxCgBpn7i+Tzg63zAwmMpu6eN2Ez6MW1GWB0eWZTBFF3TM5YyWAJpLEZ4M+gtBf56lz3tsTJ9WSci3ahO9nGracH3wFtmIMjTavEv7u9tEBi5FOICWH7RRsp5uQ1EjWhezXJZcvPLbniV0hGMT5OfhEfLT0N/Vkc4M9ZLYdQOFaQouXX4Q9imsZaieNighQK78IM0LePVoiOwAhqS0iyi6glMQgkqzPkyXvAFtYHTK49ApQXv8sYblQmXzCvd3Pp/5p5qxrMst8d6WZ+z8s83f7a0CP/8ygp9tdC4iORimGXQaahu+PrMXes/w7K/g2QcL+OP+W40/vmylbZWgv5caXU1yN7gzbZTD0qDzuz7MkxaApHK1PNdRZvJ68p1iCuP8xSrYBH93bAJUAYrS7QDhaYVljYrTPtjRnwlFWACA+fYP8K0gjaWbB5PJ/DQ0gKbxNGiE7knsJU+sX79Ry97SkclsJ2fqocgVQHjZnwWNUWyHUAI6VZf/eeBuhcw+ZWVlK1kZvoz90w93BOFnbJjklyJM+DkbTm8P0l+wYZJfKnvgE/vf+9jvX0S/X4F+/9KIfp+36qE8PTWMj2/gWG74+gr4OhN1utQ/yzLYi766p0b4Dod+/M8+8ulV8CmwD/4bwidZ6votA6kuNjPzpxNNtpnRvmZIdsY7iltvl3BzNvPrkv4+yOkXHdpdMAmYfo2lj/hR9Ggp61HHhlhsdSyRpiIQ/Jj0K9/N7U52Dm22fJ9I9R5Xy/WugN3h0tQ11+lc99B3BPYRp5HP/WrR7wuMVSW11tYKwePzbHiKvfvbnx4cyCa7CMLMTjJe7g2FCYIPk9wyL6dFAS6sTkA/CtWpb8A8wNR/IupfM0b7ptTWZdBiM20f9NkDavetz77J5u/2OoO3FQXPSsPHvpEVHh3M8nNTGD/fILvY8PQg8LQzv0yhr3anNtN58FwHRdqba9E/O9JK1mADIZ/3PL899BbBrzJbl+UWRosY4h0J21R4b85kEpa3rw0zFt8oMJCxyeDHqaPTCVO8ltKoUKB1MGitGp0WDGHCICnoNOCdCryfKNCmt4S1acYbtU2n1Fqdy+xDnnKKLzNjJcKHULjcy+SKliG6wRs002od2xZV0K2PWG77cD7t5RzC8OlQ8OnCAnyaYfv6oPVVsK+2f5d9o2fQdHYvOJtVzme+yU++9TtC66I0V8e4dJgcl94A2z1UP78B81rDz7eCn2e4Z4E5g/NWS3IHSVY3KaY86cNRMzSZVOKrjI/p+LfVjnzT5e37qOMra9156+GOji+gZsKTLO+fHFXOMq6chelcjOGTbN/C8C3ylHm5ewahclnO6V6AazrZAxJb0HYV6L/yLGEly6s9Lz/b6yN5ZfmdB/k9Dj6IZwm+LfBcdRXSS9mGGl0nOvJtEeU=
*/