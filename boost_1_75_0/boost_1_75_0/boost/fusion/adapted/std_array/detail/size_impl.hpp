/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_SIZE_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/detail/array_size.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply
                : mpl::int_
                    <
                        std_array_size
                        <
                            typename remove_const<Sequence>::type
                        >::value
                    >
            {};
        };
    }
}}

#endif

/* size_impl.hpp
fegmFngPztoyfU+ItU4bV8m2/O4u7wpXl61p+gJN/IuOTe+yoqC5q6gyJL1kXUFNekllgd3vGHc/nP/U9LTRIfj8KXZc4aHpgqEZbr4kmHN7X+Re04vn0H7GCAzTIwe4MmGHRoLvg3PhdFj1eZ+HfnN7B+eIJQZhXJ6Gt1LGJ2QVPICbq0A5RaEcQAqo10sLKC1ARmQ0ysIRqukTc6W5IxhDsDaXww1EqZfEzZLjNExgX7wQ8JpYYYyFG7UX+x255vuJTHGQeacNhk/LCMYAcM1ssBH7OlPMC2pF0aoc8/BB2IIvn0dT+snz9WAtK2M7iNJXP5qilJVB+LF+d9m4CmFTKzD/yXBVkFK9JwClQ/RVP9SFy9zete4um/UFsaLfwyKdXbbIfq8s+K1kW0GE6PBTMK/yjfS4vRuMxS+anS5o7IRbrsnQMZPNLgeAUmfRRr/omDEc7Qw7Ela3L58Zii7Smd7nqLcGWT3/Jfe8q6A/y9QG40alggBqUEF8HUJisPNYnbnmPtkf15hOMYvus/ypRZFZ99EsgJ0cU+t0VxZ0V9dE3UT7TBVzY1ewV7VGA/6pEsWPzNL7ib8T/+HhP5gbiGinSPuPw960pf3x98GOxWE6Z4HIRy8WSBpZ1DNUL1kPe11DIsXYIOalaQm5sCMArv4uX/htT3Ncndt3WzWQyzbmRmlaT8H3Y/eCp1BubXTP7HaPtuqS3c7l
*/