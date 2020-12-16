
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusion

#if BOOST_FT_ARITY_LOOP_PREFIX

#   ifndef BOOST_FT_DETAIL_CLASSIFIER_IMPL_MASTER_HPP_INCLUDED
#   define BOOST_FT_DETAIL_CLASSIFIER_IMPL_MASTER_HPP_INCLUDED
#     include <boost/preprocessor/facilities/identity.hpp>
#   endif

#   define BOOST_FT_type_name

#elif BOOST_FT_ARITY_LOOP_IS_ITERATING

template< BOOST_FT_tplargs(BOOST_PP_IDENTITY(typename)) >
typename encode_charr<BOOST_FT_flags,BOOST_FT_cc_id,BOOST_FT_arity>::type
classifier_impl(BOOST_FT_type);

#elif BOOST_FT_ARITY_LOOP_SUFFIX

#   undef BOOST_FT_type_name

#else
#   error "attempt to use arity loop master file without loop"
#endif


/* master.hpp
7f5/q/4QNX86CewQfOhczvgc5UzrqpzxH60cJun2OUhS/6Y8Js1dnwf7VMSW17Q6V3mclxzl8ZJo7vNDcTnKIRBEvPOQBUs7/15yp/OzbFHj5Jq61avW+EGgmE1+BGM6xLW8x+wvoRnm7lhMPtR38u4SNpNPx3puXLCkNhOHltk77hz5JvW6ZHW9DESXc5HafJP6XM7zLa5Hk19Sf83SD+WII3f6HemO9dm4uLG+s9/knwSVkvxXL8+dr9QnbaVmfI58qE/R5bjG5dqeeuR5nzag9+fT1DEec5I8mmxozLk/Sf3xLOXjMuzIxHPKplXXIOXYTym8U/5rVq6SMWitX/evVHeVb7rRPUHBzp/frmnReMYTPK92j9VXNskVkP29dqaM6BWyGxlV/mqOnHmkPPWfyl5rfhULkrCw9+3tjGXTFjQsWFgvN7P62sZOfndz1+v5yOnj7WNUnqOPG3+C1EOneMb4nI9Rg86PmmVD/wRati5bWN9UlvmqnTXsW1LupK7LldFy5zjKP1SubG3Ktf1XpltO6sP8/2zTb3XqjImPnOB2NVtBKxrlVjmn9qRcz+Nz1Id7JwunGV8lL6GUSXZrkp0y5VJBtZTaRXliyl1erlJs+3A5dKwXAq4f4Ktw+zZhIqfCXUOB+Vu8MnuJfND5e//hlFN1o4LAXE8NtR91f6Q2zLYunP0P7gdVOirI/XzDPWiaumhRbWPn6017kuTBRocnUmXJBqZ+/Rwk0wm4N0XeX61HTaup1v+X4fe2w75SZZ37N/8oq/EjlEN10Z+WJRt2VZ5sQHmd9o9pT6fy+G6CTr4yjJ36taWra2s7PCCeWXNUkFNn53O1vfrGVR/u79w2eBZcsXDV4lM777d7NLdAburJ/pT5p35lh6jXXh92I9mmIt25/86xN3arpLx0TcciPzSfBl7cmduxL5m3X8WkfU27Nw28rEk26PQuPG/GJHnsJXl85PKnJtsxjviQ8qvZsGyqKbNs2pFlB3/kcg/pOGYc94+Uy5a67aT33S/sOeL+/L52bn16fzb779+fs149zsYV9StqK+SOxrrZzh9vxbHGv6gpeP/7eXOnjd/Hnlaz3YIFvr3Nnm0+X740c70eNmd253IW87xu5qyajp83NpzU4fm+u8Lnrlq13H1k97PerdMFlDlT2aol+oA/Zz1ULPKjneR5vsne+uljc5RD59bFdqvqF9vx2sJFOXwrGpdWnDyho49Qvd2PpsaKTPRxQdOa1bUVkycHgc2/afWHb7ffvh22W72gsbFuVUND7WoK/YDt/WA1KddsL4V/pO27Kp/4vz2/FS4uVN/QZP1JZRq/u6e612KR3r9dF+Vknkw11rnpTM7tVizIXd7cmrnupuzvd3UL5N/4yopqvu8xl3+6+pPvh6xo6Nq/yM8HdZtO5eTan+lHT6thdGaqgfI+cLvGBulHau2GTcsbl9Rmms/7rnc9PxSZxOEPZQPrb6xdtMYNZWYtWFi7PMj65VXROYey2sm/YvmMzP+AqapvbHKvGpr9GlfRsHpJru2ot6r6lR36gQYpfeYRM3KW07hUGqn/dspO/rKZmbfmav37VzOapQZX8sQnVz61KyUiySR+rvnuKVFOWdAwddoH7G/O97umNa1evneDi/hlBt/HTK1m8JfrOBYsOnrB8jU5yj1mbnUOv5y3eokGSqmZM9IY2HKrO5XLu408ROj6OObUZr6hrfM8NnPua2vqZLLsH9Hkrj+ZIUtVS0RYT2xNTVVZsoFpT75PtmEIW56PEL+/PJ8gPO0y8RWQlKsb2u2yz0jmrlpWu1LLk+nmqjVNOfyZbrBRe8GZi4OOfzWyXRkb5trOfU9ffdOKzi0=
*/