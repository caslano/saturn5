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
DqzXPApMkdAg7A0NEQYRr+RbLzTVXdz3cjMGIKp9nsO+ZbwVHxv69wGwImHUHyDHSv4mCJrIy9iiGu8oZndo2VaJ+myrppKr6pYIi0bOziBRmBQLUpg6s2BJoLkbaKAWRXppW84AJjbPAC6YxxlAbrMMILdUxCoy7JW3xVPb+1dNgHyZ5KFahqaDZFHuNVi0zGJ/ZBtCDy6/amjb3MvMQfLp9Ww9mEK13isFXjV4aRI8kl23ML5Q/9MtDBZZEgXdsYx7lrYyeZlRKzPy4aiV+bE/rozvVWFNfFUzMXKbSP1wtMDQFEQIIL2+cGikvJkrl9a3Y48R7Q89irHEQApOxYto4pck2q1lpXRcz4+r+fHVUtIqVvDfy0q1GjTcRz9eZOHxgMuL+wrVtacLHDyHXBnfUyvsKvaxNfJvqyjCugYXfa1JL+ClOgONHukPwJjnTCJ/65F8pG7uBLZJu2HhRXeCU7k6p6QskEfNnyt40LW9+BoUBjFjg9znjoGHrfrqNZ1FiFtnXSB5Z95tuzO1boLewThdaEXDk1BoKtyxUxOxslnyTBZPPOD4Xnvxs/j98U7uCxYKK4WXx5MbWEQJvaARdueHYLPIDgX2Md2zhoHtQIXrIKBXhesISnph9GJ+ALommBxgX/0rXiV7+gezQ1MPGp8SD7wUH6tmek/Y17c9ZJAcsG31ZLVk+soFPAL9M5vAmYIQ4cJjC7jt
*/