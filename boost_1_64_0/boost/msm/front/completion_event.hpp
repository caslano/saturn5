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
uIL+0NVskfFvo1jqVGTClgqOltpZlpf4gUK7JdvYtvN3ykvEtjs6I7XUH6YCZDtj+zBXkslA8LAHj+Wvz2Foda9JfSji+gxzjbi+Wdt/K0pK1ETeHgLdfL7EsbOiq9lxj39b8nRpZ5OeJvuQ7Tew5tl/A7b4BWakXcXO3ycmqBLbKHNHoxFRaDuOduCg/F3X0cj/JA3zIb6Hd+Zko70Rt1ob8h5Q7/1XHuv3WpqZm56ZHr9Qf2xx6s72jV72LXO5BuWbuUEuR6utYmwsfmGv4Y7MlhfNYoyzj1zyNFPK9Oc7Y56Qvrt855m5mQW6tW3eXc4+a1fHXDPEiP28fkg3SRRhDDXjvIdf/pDW5Vm5ba3bZIr9Oc3Y75p1qHOec74HNMpjT1c3tuh8Aew+kG7Kegll82Gty3XyyVtr3X5/bwPz6EAYCdLddNJd+kiI5XTD9/22wy0eO7S0MON/Gz7MGCPkcg8x1gD3ZWVwomCYu9x96jDPLe+Nv4mbKlEz03fu4+omYVKP7uvqVDfUL4q+ytMpQTwmssY3Byhs+C33c3V5yBj9h2DsImnlKvBHWLNXudgX9TS6ncFhrrBmb4mwz8iaui9QXh1rs9MzU6ZPxlYZfL3HCt0MZiBEGE9mhvpmEOhD2tBV+KOnstbywsd4K5nYHNBM2IaeBU1uHzp7RYPnOAzFwAzGgQ/vGTNzSwcmjJVi3MXfKWn0d37j/krjv5enajWygeTwyVZjte62gdKvQ4zbBkbhcMjkmOn/w2WOVDcbG+e89kZxacaNaxgMx33DY/Avl5lvL1Sb6zZjEfcBxV+HOYqQ91nCYTl9WHHPlR1GxAam4MWFmOT9bS8cjonztv2mlKG3RMy7HtOzi0vySyZVzBvfkMeZOJnr5oZH8RKX2dDw42MbOjpPEIUwvS9L8y+MXdIZ/FtyG4+/mP0t6xrYP+59FZqz71L4Gv6+RC8xJPYTcnPwn6Cja9jM0tC/5N5UOz86hvaWpet8pGETPvUImpOGbfw9nIYudJ2G5UvZNByeQJuPzsPfskRsIn2spYkQWvnSrNmINlFf6XhjxjXzdtni0sIUVdai/a4rn6ue/O4uXOXwXCRt6nth1raXOcxFw3E77aUbDsv9VsXjLj5mSD9Suefs3IGJaBb9sNTsISzHX3ue1Lc2Y9pAbgl9W+lrsRx/ouezbjMYI2xPsy8/VeAzSH09fS5jhTYf67INv8Bjkrp9pVPsTfiMnbFg/Hyh0M07SMLH7vmayb8IO3qRr1P+xTi0I3TbtcR85ojaOGkzS4uHp8oz6aNBizP3OEa3XDNvMmML192NNfbMbHFXlhIh+/dPuexi+W404o/jPoxxK8iYOJmJPh1iKC5isHa7cSWfma3Q8E12Z/b32afcDHP2HACPAzrOWVtsq+iXm4GwyAbsq668fxIIS47d5YBui3IFY9ekZqxzvYK2H0pPgvSwjxKHONohF/H1A4z//cf+Tto/zC/NkhnMZG2wDdv3ddE/Dz3N5pd/+33Tb5ojoGn/Q5vnvMY7lBouXEEf/MDRcesU6/c/1DrfOuX2VfiRy1HVctv8savZc9H8ppOnU/aIqZGHzPPEnZ9KBi+KQy/9Ejplv9JaeQD1P+L38SX3SZ1qMP2mEdL/G/x+JaFL2KsnK2yTWqOHl6M6/MyLI2yaunK9FH67F39v12k4k+9P/M7TbJKTiMMdcLg05RX3M87D3+lUq80MVct6Is5FXTrErJxLMdEn/xHpMNPctOeX6+DQ8RBJNdNGQmuaj0QJrfsnaKY6SWRtyBr9fWKjGQntz45GhcLa4C+OlsjfDf4KjX4z4cTX+5uj0Q0icUfjMlk52SIy7VLkv/c=
*/