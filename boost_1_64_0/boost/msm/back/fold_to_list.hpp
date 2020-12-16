// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is taken from Boost.Proto's documentation
// Copyright for the original version:
// Copyright 2008 Eric Niebler. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_FOLD_TO_LIST_H
#define BOOST_MSM_BACK_FOLD_TO_LIST_H

#include <boost/msm/proto_config.hpp>
#include <boost/proto/core.hpp>
#include <boost/proto/transform.hpp>
#include <boost/msm/msm_grammar.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace msm { namespace back
{
 struct state_copy_tag
 {
 };

template<class X = proto::is_proto_expr>
struct define_states_creation
{
   BOOST_PROTO_BASIC_EXTENDS(
       proto::terminal<state_copy_tag>::type
     , define_states_creation
     , boost::msm::msm_domain
   )
};

define_states_creation<> const states_ = {{{}}};

 struct FoldToList
  : ::boost::proto::or_<
        // Don't add the states_ terminal to the list
        ::boost::proto::when<
            ::boost::proto::terminal< state_copy_tag >
          , ::boost::proto::_state
        >
        // Put all other terminals at the head of the
        // list that we're building in the "state" parameter
        // first states for the eUML states
      , ::boost::proto::when<
            ::boost::proto::terminal< state_tag >
            , boost::fusion::cons< ::boost::proto::_, ::boost::proto::_state>(
                ::boost::proto::_, ::boost::proto::_state
            )
        >
        // then states from other front-ends
      , ::boost::proto::when<
      ::boost::proto::terminal< proto::_ >
            , boost::fusion::cons< ::boost::proto::_value, ::boost::proto::_state>(
                ::boost::proto::_value, ::boost::proto::_state
    )
        >
        // For left-shift operations, first fold the right
        // child to a list using the current state. Use
        // the result as the state parameter when folding
        // the left child to a list.
      , ::boost::proto::when<
            ::boost::proto::shift_left<FoldToList, FoldToList>
          , FoldToList(
                ::boost::proto::_left
              , ::boost::proto::call<FoldToList( ::boost::proto::_right, ::boost::proto::_state )>
            )
        >
    >
 {};

}}}

#endif //BOOST_MSM_BACK_FOLD_TO_LIST_H


/* fold_to_list.hpp
KvBs07jfjHm6pjni1rTqieNrtIUtyc54n+Wb8Ra6aIxm7gucZNPcua34kuJz6fyZ0eNmNC+OsgniLP3bzZqz9HIdXI2F6N6Onl6pg6ltBHV10VtGiPZJDk9/6QdLvpBc4nDgDZ/V/vDgXGvjv9bDMWXGdvjM18XIKmNVS0J2CFbnjKcsbGtXqm0FZtaLCbI9p2Pz0waj9mAowJb3xFvaNf8RC1ObZm9PT5z6+ORUK+QO7bdenGSp5retuq6xMTKrOoOB0fFnk43JRNta0rIwMLH8WYvOjHAcOLHWj2WLTlHRozh1eKj83tCJG7ZkWvU65qma3S1ZfMSChc2Ll0ab589ZEJ0xc+bsRYtU3G7X+whbwmLNTp/lLeFQs7B0V2zyYI+avbR5lrtGLNfHMKI117oYtx8Vevswh89Y1DwzOnPBfAq6Gc3zFzvzXKV5yvSDY0S9F9dfX4wo6EvXKu+iA3Bzom2tbVFWQj1r0vC9SNMrmt7ROm2qgzC116eKztZKjWL28XJvObR4W6vp29w7YGCNrmlmj1Bs49BSdccNwreip7MJikTGdWj5bZ17pT+uiK+xaIENtfua585fMg+BCWh6f3Yk9wloGMOsWRTTWAX1cE88k9F6DNXBdLR0J7oYRNcH9TCo0K4hqn4MqlkNP8YeAqN8GFJ4KptqS3UJdKh1XQeXwZfk5pOt64obV4vQvMmu657RLrqal6EHvXTmJLjf4SPsoS9PZbLJFtaQtZRt9D7GhXOt/9JuGuEgu1zdb2pED6anZZWjJrMuHuvDdLesMLEruJ2Pnk71GP+JuelYUs8piTY9FZMzj9G4lra2OBYqTtE8nOChUYgK1t3OPATvnzn0TLJvLYB+4x2J1ab2CdXBZHo7XJiYB5Op00/ei/H3w7pF89tGtm2ljiNr9GBr1trmAoOR5qPOXbq0zy+z6KlMXNohS/MuvX4xdBZNSWolsUL7jdU3xV2fP0R74tke6ryxzjwsDKwJvTf8kOs6cuJW8hn/scHDAsXK3ek62FU9cmHZ2dvS05LMYtY6h13oxqZZe9p7hHlPX1ihd2RT63r6WqU6s2NQ7McOhoDa2tupNQFGn928bzCdPS2sC1JJnDXb0hWN9/SkcGmzjg3tYbAUtdpuY+7rRH+R1PHTQ2PZktT1vJtG6dBOBWKdPdSl071VX8X2rYthGFMbV4ysWEHKgi6RFNQ4Do8lY88dfRYtLP5/NtzQWlsy8WlTTd7IDrRoOEDc1M25ddZ9bYn0cmjaDk637utKJNGNvFfLOXe3dW93u4lDZ1j3JVkkcsCITZj48WOb3tvVZcvgIdMn1tSVkNWXXc9+bO5t9xmBsSnxqY3LLE/1drUrv0rpfbmLDAZ9RFXuyDrzq2q6Z81wieu6rNI1f+lFmoaLOTFQRQSrTiheYuO0xRu/qUvn/KbH5JSyC+M+D6y4aAThGjmq894SF520xbZzWkR1vrrURZfVsjmLLrhopDJpzsR5/mlfO9aFIc+Y+wOuvmtakZ8gmTHqYQgxmVTS2KcLg5J7s+2pVUnTx3E2XU6xdY3MzXasKLr6yJhzIuOvyxGekwLjei16mUNXrmx8ke86s2jZWszWPnySQ8OjMtl40l5vjjO0VGoFm0gmt4d+pmndzEXvQetc4KEzGV9C07GoHhbZZuMmL6X9GNWNweT8GAI4okqtMTrwY/hB0BY/BT+GfQU3plgHA8uuPaqSG2NynCXjsgeD8ZqzrxvctMwWZBj2Yf0yjPkxfhn6MH4ZFnwYvwxLPoxfhhUfxi9DcaMHY2Ro/O5yFyZFHMarzNl30UeXkdXE1ZKhI36R0vs0m4dY16Mz5y0Sa7RPDdrKps2fNXs=
*/