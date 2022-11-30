// Boost.Range library
//
//  Copyright Neil Groves 2014. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#define BOOST_RANGE_combined_exp_pred(d, data) BOOST_PP_TUPLE_ELEM(3, 0, data)

#define BOOST_RANGE_combined_exp_op(d, data) \
 ( \
    BOOST_PP_DEC( \
       BOOST_PP_TUPLE_ELEM(3, 0, data) \
    ), \
    BOOST_PP_TUPLE_ELEM(3, 1, data), \
    BOOST_PP_MUL_D( \
       d, \
       BOOST_PP_TUPLE_ELEM(3, 2, data), \
       BOOST_PP_TUPLE_ELEM(3, 1, data) \
    ) \
 )

#define BOOST_RANGE_combined_exp(x, n) \
  BOOST_PP_TUPLE_ELEM(3, 2, \
  BOOST_PP_WHILE(BOOST_RANGE_combined_exp_pred, \
                 BOOST_RANGE_combined_exp_op, (n, x, 1)))

#define BOOST_RANGE_combined_bitset_pred(n, state) \
    BOOST_PP_TUPLE_ELEM(2,1,state)

#define BOOST_RANGE_combined_bitset_op(d, state) \
    (BOOST_PP_DIV_D(d, BOOST_PP_TUPLE_ELEM(2,0,state), 2), \
     BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(2,1,state)))

#define BOOST_RANGE_combined_bitset(i, n) \
BOOST_PP_MOD(BOOST_PP_TUPLE_ELEM(2, 0, \
      BOOST_PP_WHILE(BOOST_RANGE_combined_bitset_pred, \
                     BOOST_RANGE_combined_bitset_op, (i,n))), 2)

#define BOOST_RANGE_combined_range_iterator(z, n, i) \
  typename range_iterator< \
      BOOST_PP_CAT(R,n)          \
      BOOST_PP_IF( \
          BOOST_RANGE_combined_bitset(i,n), \
          BOOST_PP_IDENTITY(const), \
          BOOST_PP_EMPTY)() \
  >::type

#define BOOST_RANGE_combined_args(z, n, i) \
  BOOST_PP_CAT(R, n) \
  BOOST_PP_IF(BOOST_RANGE_combined_bitset(i,n), const&, &)  \
  BOOST_PP_CAT(r, n)

#define BOOST_RANGE_combine_impl(z, i, n)\
    template<BOOST_PP_ENUM_PARAMS(n, typename R)> \
    inline range::combined_range< \
        boost::tuple<BOOST_PP_ENUM(n, BOOST_RANGE_combined_range_iterator, i)> \
    > \
    combine(BOOST_PP_ENUM(n, BOOST_RANGE_combined_args, i)) \
    { \
        typedef tuple< \
            BOOST_PP_ENUM(n, BOOST_RANGE_combined_range_iterator, i) \
        > rng_tuple_t;   \
        return range::combined_range<rng_tuple_t>( \
            rng_tuple_t(BOOST_PP_ENUM(n, BOOST_RANGE_combined_seq, begin)), \
            rng_tuple_t(BOOST_PP_ENUM(n, BOOST_RANGE_combined_seq, end))); \
    }


#define BOOST_RANGE_combine(z, n, data) \
  BOOST_PP_REPEAT(BOOST_RANGE_combined_exp(2,n), BOOST_RANGE_combine_impl, n)

/* combine_no_rvalue.hpp
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
*/