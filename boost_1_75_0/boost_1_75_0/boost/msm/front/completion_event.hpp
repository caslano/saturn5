// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H
#define BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H

namespace boost { namespace msm { namespace front
{

    struct none
    {
        // make every event convertible to none.
        // to support standard-conform implementation of pseudo exits.
        none(){}
        template <class Event>
        none(Event const&){}

        typedef int completion_event;
    };

}}}

#endif //BOOST_MSM_FRONT_COMMON_COMPLETION_EVENT_H


/* completion_event.hpp
W3KTlANEq+fZcTZm5mZDYJXzswUAV78ojygyRUD5m1OYYap0DoxaNk9qq4EJ05TC89qndXBpvFDIkGodwXoQB4b/UPY7XmMdKHQYHJ/0p7DmQnjqj0bDi+sNvX6Ex8NN9ubsqU4M7fHuTQKbLlh4jFw9wd5I6TnDYa949t8GZlX3i2cTph3ielfDUojrkqdFvBaNelZBgV837Ae33GYL+0aa+K0gmuIs4nZzhzXCmrPhqdvSDL3KkspMqdsML5f1cTRcY7b3jlfgjsP4bD4JYXSUq8ECsidW4TehAtthDU1EqCDn/c0gRTJU8dsI4W81PRk6WpDrxSzW4qxgaLtcs1jzDc6c2pjFp9mlAwA5myPpACEs3tN5fCNY4d+AlW+BM4u4NUPsGWcWK83ioBicrjpnauA7xpr1YdbGhb/+7Rn4xy5rYd7lhmuRmFuZzSrz25vFnvFsduDaAvOEzWasCRXr2KLHrVJt97FJAiRobpoBVZLMvPCPGTMzoxMI5nij2+Up0wPuDxLXWexCvMVuZHM2RmN2IcqzEm9ihngiA7w4bAq3F7IAQAQJBIlihGDhxXBD0dc4ozlk6fCzec3FcNyMURoFXz9zxGvu9RwwomM8+4zelWBh/WGTbBvOKvOgODZtUJWClie3y7eIuLFDL9h7xEO8Yv1SSDJd5YDGU93Wu5TwxSK3tEXVINij1LQnslcLy6KwicLyKBcb
*/