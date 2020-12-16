/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_10022005_1620)
#define FUSION_BEGIN_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/adapted/mpl/detail/begin_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct begin_impl;

    template <>
    struct begin_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::begin<Sequence>::type> type;
        };
    };
}}

#endif

/* begin.hpp
X/84ETdVaSew45tn8TxhJCdtr4VxshvlzR5m8amjORkuzk3+WPCNymJoS/1fGh2HG5DnX0WYRtNvl3KbLv5ac9Fx9U+aEWnndYN/a0bYD4eTXEkzbD+8fnkBy0j72bK6tY2LWEbaRvGSUo+PRaV9nB8eZbjuk9uwnp1bW6h01hdW00dCYTsxzgVGC9NV0f/kLee7al4bbVomM7Maxu2RTLnaqHO6BqM5qhJuu1s7cyvpG/PiXp7lafZGhNwLu61l7j8Mk5nmDXYLRvZfzGzsl+H4fmn4VBbvqfQsI/uuFeyP3FK0CVpBkO8J5/dprU6ifEt2cHWhn1W2zXNn2f/5zGLu+JRh3zd39NgR+gDDsRn/rHkL4+JTQ90t35EDvUxLaDRTIeT+8CUN6yaqmG/S1FbsBT8txuq1meQZAZNOPpbQN7OO9gp/7pnQkGJKLq/Ph7pbQRE2sRnqzfXFVZoX0J4P3wljRvUT249Tf0+vHPmHwNB/vz1lysPzY+eVJ0+MH429I7s9iqNE+S1S3jt+x07sSru9Tktb4m52YUeeCowaXEPsY5d24Icv5ou17OYI1s8f19C+3jmCI3vx26mdLL3NnVjOX3KrrD2O5mmlbnhMoSxaF68bj/wd8slrCM+5hGOp8azSA2nybKVY13+uZnSvz+srXcuZsS7/vJDhkNDvKCaciYg3Qp4vOQy96FuKWpfnOpsYM18gGejnMAa9UOk04sXT0tTh+DOe7KPlfurqZGJydljElVN0zJD7sN8IjcOuI+zrXNrrONqqx9ubCh2qmOfMXibV/cP8lDBaJXIHwvm+5uDPCEP1vc07+L9nxbuX/fXkt5lGRbsXEfMbb78XOmQxTh2EXq3tVZlvYl0okUxQAKLtFS8WcrYdb13/MpJphGEhz3f3YWXinuSW0J4daGOs9b4aaHtZy/0l05ay+G6J9Zu5LF3uQldtYVhD4i5LD7qruTZVIo8DvW9m4dZl+fGZ65tnv21E285gn9Chijcm0C5w8aKJdlvMftuUcfP65XSmu1v4vtHL9dqZTHcXJWiMcdmW+1RZvmFOfOa6dDzQ0rZNJcN7RX3DrNc9xePkvSVDtwAzy5D+5X0847dH3Jn/MQpOvtPaXbAMIdCL1Uw/K8uK52nvGup3Kt9l4jDdTS/fciw5hzr4hNeO0Suns7NH5fvKg0+mmr9Pc3Q35vj+78MMJ0fRXnry7/52hshH881KJ6/BZUPU2ae8rp+r5b4oS6tbOF7v1HydcnlHdEpFtUp1gn0xH4f3JWooY59Xfwc5C7yKMfutgZ5mjzZ1Wy6Na/Df3zaak28A5D4DrlOgKlumd0vVW0BKp7QIrau05v2WRT42fsPa8GZwec+tCkIv/Vbo7gavu98l9Py20ffdSsx1cp+FbnZLEAczcn7QQfqF7j9Hx231K15zYfqL7dC+KjRfgfCZvyY1VzD4PCKnyzJ6bzDU6QECcRcUXDfkZIOTY2PIYebN5T0IGd/ssdcQ6rqB8trp10dxsENe0zcsJavDd2hLUk+dUvZ7viG1drScmyGzR5dz4Ztal+UsbWlec7qcpW+ouWg59zVjy9nospyFT/6tkBtdziXNopxxLyuzAypiafsD8ffQtnoDr6l7d1x3xS9A9/0Gz6W3lUb9Bmmw6y9BG2nXBTBxu97wOhcvp6sHzdr8FmuIE/cgv5xptJ4h4tryfxdPqeE3ie9D/DNq4j3z9O9pRQ07F2jzr1QaVZMYd54kNXzLqoO29WujU5J4LbT0zAs4fYqeoKG51HnqI19ow1GGkiHHtyij71YNPDNbOjp+3tzkPebSePgNumeFOsUh+3+jU/ikw/6H+9O8N12eHr/rZJA=
*/