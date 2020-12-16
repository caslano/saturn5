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
# ifndef BOOST_PREPROCESSOR_LIST_CAT_HPP
# define BOOST_PREPROCESSOR_LIST_CAT_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/list/fold_left.hpp>
#
# /* BOOST_PP_LIST_CAT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_CAT(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# else
#    define BOOST_PP_LIST_CAT(list) BOOST_PP_LIST_CAT_I(list)
#    define BOOST_PP_LIST_CAT_I(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# endif
#
# define BOOST_PP_LIST_CAT_O(d, s, x) BOOST_PP_CAT(s, x)
#
# /* BOOST_PP_LIST_CAT_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_CAT_D(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# else
#    define BOOST_PP_LIST_CAT_D(d, list) BOOST_PP_LIST_CAT_D_I(d, list)
#    define BOOST_PP_LIST_CAT_D_I(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_CAT_O, BOOST_PP_LIST_FIRST(list), BOOST_PP_LIST_REST(list))
# endif
#
# endif

/* cat.hpp
xkUDHdVHlVE1nbKphLhK5vRenxPFNyrGrUG4GrtpuKpjqxIR09Pj70CRdFtOK3o28AzsW4RW22jzVm7PfoYIevkRSNeEt7W4Nzqidt0sXNl8cKYm7kZGZ2uaMgN7QOQYIFLzj4JffmRH8QlDaw1kXboBhFPpWLEMflZcU4ZiwHfgYphGz+HLWPdyI7gWum9rmRFoqJW8gpTQwmoLNOBw2474A3kqj1nvWoPKIgorI+gjpYnc1L9jU+imI2z11qltujuTDp58D1pJ+TkdPSKFWQv0HI/zgfQK4kPJb9cq030zDKUMqyz4BqeeoXrz99CFPiM9UVZAaM9pr8z2LdqGk6JWgKkNfX2Jmu+3MmqaSTxU+Jba+Ts1GIGCU89koGT+N549BHaqb6Ylv3OrSvRBn8i5HCn7gm7M8C1Q/Pu5u/Gv3/VuKL18Kx3KCZHcCawvGGpVSbZnWAZyju8IioSlwSdM6JXs0QK07bXyPruMqPQFpvZYQBff8wdmxzHZu1sj6YnTX9SnG575HKGhPlEJYiKissUV37DG4mz+ImPlMuGeLVJbsa5dCiuKO5RFxuyyZikLVahoKkisb317LYrTt5aVzTpMUfIaVQnkN1wkYiIoxpAEmJRcxN8krv8k0uWcu2nuiCkUK08jhz1pp5w/wfSkkwy80XP8OZZM+gZDqymQWYLYujHofttv1I2P0AmpUIdQILJu8vaWZ0DIbwY83ssUm7H5EbfU2P+SXVtOQA2ZWp2I3/44LcufjjO1Z+5ESKoycn9OED0JlsLUZvg4TiAOgERnkhZBM4sokBtZrBCPJBq8zNZp2KaWK3h+whelUzmzXWbmTK5uOVLHkWUunynUtRsNTJMR2b4oZp1GNk5ULMQoBGToKhZHmYyAizaoK4W8f2H3Z/I1wITrn2r/XW1KlZA7qOxqC5sB895ICPGL6UmBOxhDHKVj58/PdO+KCgNRg6auYkSNiE+0zvBCgAO9ow30VhmlpvuUAkZnfojMBFlk4dq6kcWH74FRI6b8A2VrVg00kVsCtxRO46+6Phib1HFJXkaHbFM5ialSudJi8uXHHR3I/sVGY6TG6wWIsmfRjaNDHXic3dee2FM7PYRBDE6wZm/Nycuy4WwzAy4VLgEuGS4dH+Ww+Fj4EsVleyRTSPuFOekYqhBvQ625HXhASrDbtGss1jayrZI58bX4wXAG6+OaZ5tM2IUfsXE3VYU6lhGoNrECYWU25I4DWrsvseoxaxKli9yXpQJcL9QPfiRNt5bWae3k7ZrNcYNMJZ1pCPKEIkbsLSNtoJk8v7PQFIwso4m1HHt0Bce+WaPaeY2Xb9CldlAf4FjJHyy2O2TwU34dpUxq2HreotBUhKCn/ZW8X8d6BTGiADMW7ZbO1LrXnzKbxk90KPsM7nhzMbOEn5rKTBnn+WuYtORvE90Yxkdf0tWf9g7jTyotbXJiTppDOWVUeOdiOZh/sDqsVoVWKoGST6TOlipK2+gqzR1z5MUjce1rpEPmDqeaizFRY4GiKAcGY7b19DFV7x46u6SnXFR0oL2Kk6HIKp6eCdAcSpEBweZF8upRf8DoUBYgwWPFXIAJKPrP0hSGkz2dkMF93dKC2zBOr3rgfN7DdV1ML16ptIHXopGJLo4vjdlDFZ5XfaTilW7Ul2Z4a7XejqSqY7nqxtbaVnRaTTPW1qvlPZ2LqYqIoVQFnw81Hr47V8tPRwVql+HdYXi3Gd7NhneD4V2j9eW5ENVyhTL7F7pu/laNRuRolch61gdDmEjKrQR1WWPhJXx+ZTRcaXiXaRW31mHIYxguOQsGyhpCWX82Mwzx54V8AiHRoGOC4Y3XuMWN/0sT9jSBHlR5ilE=
*/