
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
hOaQDlgBWVbiHy8S5QBFjEseQ/9bQfZKVksgv9eQGB9/OsWXgdzUU4WUOf7UPHIvPZ3k6eFWkGG6wGBg6WmmRS+Psxcs+Xq+UiZ6N1IaO/nBWWsTxcugZ+2rMUu/zVS4foRyLy0VQ4Wm2Hbf9HNSkgJ9Azijcx/IRMet2lMDyckBuwj+J7JvdZsGJ2H+tKqA3ctrnOpeELoBc6XXrTd5ZifIcz3m8dfd490uHbd25q/7q3ehyzzlPni5j45Bekg=
*/