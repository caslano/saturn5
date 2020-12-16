# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitnor.hpp>
#
# /* BOOST_PP_NOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_NOR(p, q) BOOST_PP_BITNOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_NOR(p, q) BOOST_PP_NOR_I(p, q)
#    define BOOST_PP_NOR_I(p, q) BOOST_PP_BITNOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* nor.hpp
W4rpqJVuKEtbgR2kD8altamG2AhS1TAH3z2ZmR+fjb5630LRubMmzZiqho1lDXLRptaD/Fj7VMLedGl4VHAir63FyRJkIJxMxiA1TIgPovVgU30ObmJDe6EHp/6Fd6XKQKqzulYv/SPi2aqVvt+7KonDO1HvPmMtwUM5KBxvAGntMk5eQq+JX0BebBNRaxXd6Rc3tljOOh5aNgJcHeCouIyDdrCjsahKmtyP4UpwKaXJFTOEpHZ/DixbPlNZIRe336+GtX7xcBn01ZBSuEqWWZ6+ytuoJ6c4m9/s2ds+Kv0Fdc2r0UUV1Rc1f15O6hT10NCn0dpTt9kEYpcK822t6pj2G2rQe0JTPzWzMnaTvWKKsr8RvReu32FbFV6nfkHsE1nHmlQyH6/06Clewt1QlfiztXLiD8RB9KGlz8jjgK6SVmZna9X1rVTLvlin6bSyphWc+jVdW8aDMuFSw7jJmF73ypLdR58YxOrnD4e8/aUwfw4ftHdqrXTbJlfCEq5uBu6c39XK21y8B3aS3HjyqvSG/ULI/xa9nQr0OtRLUSWxDJi+ydxeXdrcucfeq2732KrtSSVJT/y39tRezT27gPOgJduFkGRL0cqmXTev1o1d3Wyr/silbMzAk3Is4w0RVv95mq3x5gnei+0qLk+ghSUueZl5mnoXSr94dw3p+6czrw9vnY16v1FK5Sa4oY0LveYe8LWGFYOLstTbLV1U1vqR3ocBF+5ZOENnzpwdnV7LiG7x0iJh5Bcic50Cnj69YZQXqLtnNn7TwTXy/aPO1pJo53VUtX3eYF3W3Jx081FJo0NyLRX2s5uOEtq1phny0u85VfwZOFPyHZWELhAWND3suS4zhud87922D8Vqdz267yxpDoOr78HDJw5JH2iIPfEy1U/hXWBgQA2t6AhSnllYmD0yPLg/nVJQZV0J84CwKsFWTe9eW9vxLujszPxCecn4OsuNrG32qPoiJH+oHBkaokFdtxHutg8Im2Q0Net/RAbTAW++kXBKD4KotNXrNq4by9pLkmi1EireBLIq7qbVaG10IWxUwQRH0YcbtDD53g8XW401EvqYn/nmJtTek3J9Ch6upiZ34/KeMyUGkzwQcOfxuGf7USjcomezUJ2YctdXYETvqYJbPW/rhCBxLnKnyNcUgH2TSLXfGo5mC+Py8TQujzw78r25EfZyxlIopBL8zPhxqzyJb3iEp8ZrzxM8NZDw1BjD++7OZqESRTo/2G3wDkETmYA4F91FmxAg4Z3+RmOyd+nRPOEny362u2XhMNqoAKbsVIPwoeplEj9bq8eAK4rzgY8g83d4jozAt7GpXJ9HT9j3FeQHPyv81bXG8PEhzp42kQ4eWcbN37v4U/05A6KIZ2V5pXpvrizrO4JkEc+74/FY4XlX/MrSlhz/L1WB8avhIEpxHniOy+k8shzndPD9BY6GdzsbXm0uaRlZsaKX8ZjAwLEh3imW5TUJi/I0PxqUPleb/vTwJGrHxXfc9cNp1ir/yTs0fDhNK6FppTR8eJo1TH8nURGf0EDveVN6f4c+4iON05NvJeeppDwhs2crPI8fUxJ5p6z0nbLyp3rjiTd74s3K8Qol8XfI/B3S+N6q3j3dfqpYnTe21qIMReJoq9gBx1S0mQ0qd3f6VLnWfn5qNHYisTcew1fhO13qN6etudk5wACjR08/+TmBu7s+ttW0fByXKlabmZ2cZgBeHJ+ZPn3gWYjjWNInphzT47Wiotheq8KdmDx17j6L95+8/8zcQ3QM3Y5xyo1twclT9ZPVxRJ0Mgi3u+9Z8s6fms1oLmuHifleukZs1q/cFveoTu3vKXuQk/cUh/Sci4/GfN5owN0/VPQ=
*/