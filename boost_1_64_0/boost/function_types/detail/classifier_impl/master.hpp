
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
p8mGE7iDUaTv8Pb46xXaU1STvgwjrrv3j65UMBY5fJYypdBS+7fvYXXlELAhOQy2YNMgDhZgZG8KNWlgN0fS2avZfDAUtS/IiFuT/+Oytnf1QkbQXIIJDhoeKdfq8kjJDY98vIEhv6F53MGWc5ZllJaWz5wqRlu9Q/nKTmyN5HVqyTxccdFP9S+7kamXX1d61IY4UCoxcusu3s92bbtUdF8zGcFLpYkjnqj/+f6sfHZrB24Q1MDOHI9ihkoFzxRgpD/gdGarFwAjhkWh1LoylCE1mFd8OqLf3P327FvNUPxHSMq2FOn7r5HOGADCW0AUJkZnphN3gI9VkgHKPD6jTCFEglYeZEXcfhFlw0LfMs5XdZWZr4vHWSGQMmxYPZ3OlvRBcC13/qwbao3vOsb35eiwFAHl1MJMKkp+z/m6s5p5JZkYcY6FDMrXU0yk8y//aFGRCyaxgxg0D9/wHH4IWHJoGQvfMYq4M4CsOiB0wn1ZtTWEb/icUOp0VFrPuZfevrdUFFWgjCOwhRjdJR12ICpIZx2dM25Tm5bAaWe9e2Obqq8udiX5txwF9g==
*/