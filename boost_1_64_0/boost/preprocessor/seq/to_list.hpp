# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_TO_LIST_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_LIST_HPP
#
# include <boost/preprocessor/punctuation/comma.hpp>
# include <boost/preprocessor/punctuation/paren.hpp>
# include <boost/preprocessor/seq/detail/binary_transform.hpp>
#
# /* BOOST_PP_SEQ_TO_LIST */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
# include <boost/preprocessor/seq/size.hpp>
# include <boost/preprocessor/seq/detail/to_list_msvc.hpp>
# define BOOST_PP_SEQ_TO_LIST(seq) \
    BOOST_PP_SEQ_DETAIL_TO_LIST_MSVC \
        ( \
        BOOST_PP_SEQ_TO_LIST_I(BOOST_PP_SEQ_BINARY_TRANSFORM(seq)), \
        BOOST_PP_SEQ_SIZE(seq) \
        ) \
/**/
# else
# define BOOST_PP_SEQ_TO_LIST(seq) BOOST_PP_SEQ_TO_LIST_I(BOOST_PP_SEQ_BINARY_TRANSFORM(seq))
# endif
# define BOOST_PP_SEQ_TO_LIST_I(bseq) BOOST_PP_SEQ_TO_LIST_A bseq BOOST_PP_NIL BOOST_PP_SEQ_TO_LIST_B bseq
# define BOOST_PP_SEQ_TO_LIST_A(m, e) m(BOOST_PP_LPAREN() e BOOST_PP_COMMA() BOOST_PP_SEQ_TO_LIST_A_ID)
# define BOOST_PP_SEQ_TO_LIST_A_ID() BOOST_PP_SEQ_TO_LIST_A
# define BOOST_PP_SEQ_TO_LIST_B(m, e) m(BOOST_PP_RPAREN() BOOST_PP_SEQ_TO_LIST_B_ID)
# define BOOST_PP_SEQ_TO_LIST_B_ID() BOOST_PP_SEQ_TO_LIST_B
#
# endif

/* to_list.hpp
N93jc/svCjUX5DeH3Bd+Fz2wHP6dI6BjzQmE/Uyp+2MmMF0kcGHHcVXwsZvHUZpAzxS0cHkmcjSU5jvqy+uCUqB5YhAn5jUYp3juP2AOYUrdd59Mvme/PmbnxRzFk1f1Ajhx9Lia/c4LkTiizxydk+vze/1t/pzc6UXgppzc2kJwCDwnNye3wlE90VFdVueosNdXljdyATr8xKoKOai8gWN9YzmgvNxRX9nQWG8vb7TX1jga6irLxxewvaK8sgLv5k1N4wt4rGlIyDHdXjOqkP9f0zhef8P/b6rjag2NVcehVVZVVTvdUd1Q7phWWe+otjdUlzWWT9ZC7I2V9WWNtfWOisqJU890VFVOq6yKolY/tabRXl3pqLJPrC+rn6HXoGwRsazGUVaDsuMC0prahsr6afbySlmjYlQh+vdhrcyT6mrl0qKwKEqFvdZRVj/R3shTh/UVleQn+yR7ZT13ZUXltIJ8JTMeram0xEEJ8BmJLlDqqXW4IuUquujmn/zZ+SX5hZrUXslFY/J5sqShpGKvaYA2r5famgo71dlklKzKXnOmnKpj4lR7VUV1Wflke02lwzF+WnljbW1VQ0VBcX1jNaVRUWHn/m5A3PF0x/MsVds4Vd9kex3XJb9zQU3ldEdDxRTKonbSJHu5vaxKzomMmVjZWEYXk5qoKuvq7dPKGitJAQ6sH19RgdY3qriEN7mp1BQra6Y5JtXbK2H7jPH1WPZ5vHJ81GFN+WRHw4yackd5LaoW6U0rq5oKj1DzJVec2YFmXjk5xP9Dj6huhAhVMdM19iJXuzPoCNN1qz/Y4MLxGQLrwe6c3EYU6yJ3UX5xsVpeEhQUFxIW5hfIWFBEOLqwmHBMSb5AObwkf5SMhaMJS0eVEhYVlwgcLVCRj5EzHoP4k+xud4vT58OKsx135bJGCVKc6QUHEOXMSeA5KFgd7+ryZjrkbJVCYYxNrhBiFBQVlhTLWFQoY3GRjKWjZRxTQjgqv5CvpQuZNQN/qoye3fQFJ4P7gVNStLP4/uA0cDo4A7wcPsoEyumUlhIWF40hLCmQcUx+sUDk19bpDLphhzPoah9rLxtVyIt73Mt/N45xXWEHJeLo8IQ6nGFXO3fSRI8PrmlCOfhzwYwYetoVnyLvdBPBWWB5z1OHq318Xwy2CNk0yCZhD/SJSZbVi7qvGNuM5uGTnxnJlyFvLi3ocwvyCvLyW3O7QmgTo9UwjMu5IbQwyZ0blPDgKCQJDTZJTZNPfM0i3rTy5kYqdXUDLguK8gry8wqLEUI7psn+UBiDBe1MXF7aNe0ZLtLJy2vGP5GvsKa5I9TsDAS4v/L4mmTmj18Onj7fAKlzQK79R0w950dNTVlV9ZaqSO8YwUoquvXuirwC0+bSETP4Pv6r3SdMPXyzs+LxTf+8Yvj1aY8wQSbi7vTW2aNMzCCDDDLIIIMMMsgggwwyyCCDDPqfICudH5ls/BrnISHlxCAPL+HT2QwbZ4vFm34WNUYy3td4wsmY9ssBw+pPzcGx7BQeehMbb2Oui9w/5kENk2ZL3/uwiZ8g8eMmKmepzQR01NZV1jQ0VDnK5AMmZpBBBhlkkEEGGWSQQQYZZJBB/+dkBZ+H/f+P++658nI7BPSt1zibKQffZrP+ODu47nwmMPIMoVb+ahqf0uSUy++nB/FNaJVtQAr/XjaFbIwzKXbLZAFXIXygl39PM9/RJoUd4oUb7U8BQGcQf+snOs0fQt8R9KF3abLAy8Eppow3PMPC9ldzu1aWVk9+aV0V3rqBPJ+JvCJsGCqu+yI9jslALu8HjANOBgeYQQYZZJBBBhlkkEEGGWSQQQb9ZygGnAMeBy4V3/Zz7CPCLLTPNcg=
*/