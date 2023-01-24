// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_NO_FSM_CHECK_H
#define BOOST_MSM_BACK_NO_FSM_CHECK_H

#include <boost/mpl/assert.hpp>

#include <boost/msm/back/metafunctions.hpp>

namespace boost { namespace msm { namespace back
{
    struct no_fsm_check
    {
        typedef int fsm_check;
        // no fsm structure checking
        template <class Fsm>
        static void check_orthogonality()
        {
        }
        template <class Fsm>
        static void check_unreachable_states()
        {
        }
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_NO_FSM_CHECK_H

/* no_fsm_check.hpp
aiTLABNelROn0U4rLBwSLtUXsc+g1bgYaltOaWZGB5oXt3Dl6D39GcHaWAELgTT7kZvxTW4ceCY0RZ4JdVz1gedMaL7GYyZUojBOaT0PxpGx9WFAxpnjh3FK/DMOzYSm10JuNkPaGZmOVDtEg02JtnEOEnYSBx0KzkFjhsoc9MhQvg/fb1xEnEXmDMotAh7KAbDadM60CsOixBoQZhAcUWJyTKXFvBfHktFnVi/m+eOZG43vk6pQ8wyklp9/HVcVxDMUGDHHKzBCxsCYgPxy/5Xwy8d/6+vil+t4YEQW45kB6H9CnoEaT8vDuZkGuOHraXv4pVKN7OwNzkRhfpgobfrlMZFa5cRP5z6sy2ai2qpczwVy2yJlcUxiIrcPE43X+2eiBQGZqCh0JsIFMjUTLQrCRL4rZU7OROHbgoRVdBoss077wUF8WQeE4L6swwF9WYB337XyCTqQUsheSU9Ka+VnFPYqVfiKHSpIJR1+h1TSYs5emElC3OxMaSbNqRbh59icKqIdt2rVcyoDzak6tzPMiPCaU5VKmPs5IPNVhDSnWujFfAuJ+W47r2K+hR7MJ+HydpxTPVqXLws50mPiFKI/y3QeVN7l+bMW+Ux7aLpDtjKwN/CIjl8rwNbURmr2FC8mV8zBfv74nFvZfvTlXVP4qomK1eVyDd5ZCAKqTJw4OeXl8GkQrVG4UOJ4SsqjUpuLFY6fHubB8TLd
*/