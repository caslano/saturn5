# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_TUPLE_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
#
# /* BOOST_PP_ARRAY_TO_TUPLE */
#
#    define BOOST_PP_ARRAY_TO_TUPLE(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_DATA, \
            BOOST_PP_ARRAY_TO_TUPLE_EMPTY \
            ) \
        (array) \
/**/
#    define BOOST_PP_ARRAY_TO_TUPLE_EMPTY(array)
#
# endif

/* to_tuple.hpp
R7ex5TdmgdP3wf9LwUu59KETuMqwN2C4MPxYn85ghabExBp8GUEMCQ6fTa72T6+Dl8GQH+Mb9V+JA1pjF14l7sA+39Sf+eUZyN4V2M+xzLnRnimd8Mno08Rp5B1bkWuqYW1NOHks7P1wsPJabPLcjsgPsUF/Ypoe9OlkfPkbMdjBkWA65GlCMXnySHSK8b9qIKlJwW9fDKa3UYY5sHx4t201soMdbofeNQf/tDTyePjd8/FzxRHE/Ylgdj43bUaXL6T/2EX7x7Qbn7HpVmw4Ot1xDr6tH/EO+K8X+L496xTKt9OuFbR3mIBhkfEZ2MP+5KWQ8amP0A7k6u5H4R/XRzN+z7fDnyVhQ8hHdcMeJO0kBv0NH/wyOjsfu499DXUTM4Ihc8F4Mzpq2G9i/D+RPy9jLUpH+tgLPQcn7sY+vr2W8ZwirOMhb4h9em4X/ManHwxhTN8AU1wJNjuMvG2hLdTx5Hp+P4DvSKfdv+LnXiY/xzoEY9/wooX4CQ++DL6NaUd/1iA/94JvV2LL+hDfnwYmw9/fwzgNJAdegP5H4i9y+V4Kth6/jLHIQx6ZEzvLyBe8hW3mWRu/RxaNdVH49XZDybtciv9tybWFxCrreebnxHZPkJN4EDzThTLMY0bDk2lng4ewY5fAy+QD6CR6efUA7InOnA7xa2gI+MHwc/iONOKmNuDbYuzIV+hhYhzYsA1jdzv4L5y25pPfps4XO4DjHmftxSPYdvC6ozG24TfaSA6+ZzVz5OjtgB3wFaxXjIw7n8H/gTFL0cHwfPJj+InOrYhFPgGTEyu/Blb6CNuYRJxUQB754NfoM3a3spL5N+S0/EnkKh679zy4LZSzKOHPklPwg7Ow5/D/6RboN3bxoxowBnlfnX5F0m8hZniMPMpfWPs3jrKOVHScuZY08iMhLnSJHMM1+PMuz5LnXkZ+oQi+YVvWGeupcohj4du3G/CbE4i1uzIu6Mvzb4DjqsF3o8HetMeJr71uELiBWD3lZuOgeWTxeuxtNPJcht8FG+XMIx6Gv/nQx17MmGEPfryI3AOy9XUyOa8/gwfG20y/vAg83Xo3/LmFtuLnpufgF2ZThnGe+yK4hLjiw+XwqS3jUy7Eo2Duh9D9JO9cZzztuOMrMPthbHMROSxs2dxV5IfQ25zG+P+J2MALkUkde4mvePIB1rlgW5axnif/kM78A77kGrDWOHQeXYzD9owDd0acg36Qh3czv1+Brdw4FvldgC10odfM0Y56Ett5Hf4kjzyQsV4SO7caOWjMekjXPmw54xV2CzYIrJBJDmdEb7CoE3lvxlhMoF3vaig5tv0KcP4MdBlbdxA7lprCMPKsV7j/ijeQWWx7O+79BBsQF8692J5Pz0KvFyBj2NvCGLAt5QbMILf1Bj6GvEAffO/FkfSDvneNBRP+Yrxni68CS9uRj3Bk6P5tyNqN6AZx0gZwZskR4uYniOFpSwE8vgtfv5Gx+OGv8Ai/NoZxvXw9NmQs9gadrEKXe2GP8sExLuzL4nnMnTWH17TpiyeRAXxlEbZmW1fmqM4gNmPcFzZhDV5jxqcD/FlCG5ibTAPzJ5NzLmPsD3jwDy2Io8GSK/F9o3nm/m/BHPeQ70pBzsAEXcjFzXuVduA7n8F+LSb+i7gOecJ+XUduJQb5vRU+hKwmx1+IPQzHl8PD5ALi/BDypY9ix7BL53yGjUCuI8kjNgsFX96LTWEe53InfNzKczoi4+9jw5jfDCFHO4R+ncUcTxZxROwm5qUr8UfwqqkDm43tOvsVbATP2TEG3RuID8GOXNUWv3UJ+StwwON8pm7DJ7OWuLqCeJM47/xh4Fhw95vkM0KwufO5dx6yPvkI+ZU=
*/