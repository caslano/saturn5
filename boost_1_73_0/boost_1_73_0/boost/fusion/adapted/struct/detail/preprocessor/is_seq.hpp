/*=============================================================================
    BOOST_PP_VARIADICS version of BOOST_PP_IS_SEQ inspired from 
    boost/mpl/aux_/preprocessor/is_seq.hpp, original copyrights goes to :

    Copyright Paul Mensonides 2003
    Copyright Aleksey Gurtovoy 2003-2004

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_PREPROCESSOR_IS_SEQ_HPP

#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#define BOOST_FUSION_PP_IS_SEQ(seq) BOOST_PP_CAT(BOOST_FUSION_PP_IS_SEQ_,       \
    BOOST_FUSION_PP_IS_SEQ_0 seq BOOST_PP_RPAREN())

#define BOOST_FUSION_PP_IS_SEQ_0(...)                                           \
    BOOST_FUSION_PP_IS_SEQ_1(__VA_ARGS__

#define BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(...)                                    \
    0

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_0                         \
    BOOST_FUSION_PP_IS_SEQ_ALWAYS_0(

#define BOOST_FUSION_PP_IS_SEQ_BOOST_FUSION_PP_IS_SEQ_1(...)                    \
    1

#endif // BOOST_PP_VARIADICS

#endif

/* is_seq.hpp
CAzxoJatM9FQ91zpSYpaarbrUmwfJZKsA9Cma2uiI1korxAkvI2uLlhr8o0Q9yyDykbyf1zZQ+8FRE1dwXJj+LGFdSa5tHHhJ6fhIsGFG0VukCwRnsANlgPemR9MyRucWFuwm6ZlkrpowbdNxVnxiPy/fukjJznFZBHNwnmSJt75fOYmHg5g7R/iS1eTr/ffWLAqvtYXj0Pn4NDZo4DepSyTt6lkSl8xPeQmSYDxKQL33Bv9gbp6he/kTzKiNvUPkxkvg3Ae+/HoBa/zqisYjjR0b7Py48ig5ILiTxl39Bu8LMkAFfngKZuN71l72W1ZrX7sfjBcUy+eRP488cNg2J+4i1li1vMoTMJJOIvNzvvmEopn1u5X15+5x/7MT5YmEHnJIgrw1Z0tvFHEFPlJGnovDc/Ae+v0cmhnyK5p6Mys6L3aJy6CsyC8CNLQdKOLaqEcA2/Fngd3Fock5XH0+1xxMvWiCNbOwa4N63d46h0vPp8sgonBGd6OfgFQSwMECgAAAAgALWdKUrNLttLwIAAAhKUAACwACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvc3ltYm9scy1pbi12ZXJzaW9uc1VUBQABtkgkYJWdbW/jRpKAv8+v0Mc7YHfWkizJBu4LJbYkrimS
*/