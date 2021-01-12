
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
95UtMX/brGn15Vmsrmt9UcxJI12L82ZlzfWq+4zeN7f+7G9obn3Th7b5R/1vTP+h9ddPBK18+47+5e++8t+bW/+1zaEfkDkcfR/ou2w9EomUaSG8WMcq58OW8FLYCy6C/eBieBZcAifApTAXXg5/D5fDSnglXAVXwqtVf63qD8Ctpm6TelnCkYhscZy9EQfTYRs4AnaCZ+gY6kgdmx4FEWs0HAvP1PCMhXnwLDhH57IugxPg
*/