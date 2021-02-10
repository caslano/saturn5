
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
Xcl/0LKb2DNSElFRJ4hpFHdoxbTQPp2N5ifRYk5nwWwWTObnFB1TMDlv7b0bTY6ADQGvFfHPZcU1oqhIbMpC8OyO85866V5/fkLDxWwcTedJHI+T4Wh6Es6S8Sie0wF19l7Q37UEvPeedahTiJXtP73oH7zoP8WG/Zdwpq8SzY3tNH4AlYbd+IQmwWnofc/4ske65CmQQKkokbduYUJrJD4fx85EfD6JpvEo9n4VMi3qjNNr67OBYf6n58ynCvtfh7JjT+hxDoAUwMl3wgAmc1bRYyDQ7P7uXB6F8XA2ms5H0cSbMvSBtTKAqhLSCPnRRspI1kXRs4ARktm+WwTgLFdF5mSAIGsWaPLuydChMx4D2FKCMq9H0alsajxWnPSVNAyHKSsK1ElVmGnjewA71IAr47CqJLdg2ShgsfHUxgKMcky+i25l9Qto9cFgmw2z+PJ0yVJM1c3IpykvjZv5VlMhasC61XWSUlUbFw9SyXxaPvrFPnqeHcXloyeUAv2IvW4ZTGEunZ2+5x0jzKjk0iZuxd/KGp2mC1aIDLhngHsz5G0ahUtx2/rubPisF58EXd9bdrHuPUGvll2fujBysdd1JrtH4XGwGM+7TTkzvmZ1YZqyYlCvgwdKQBNcWtr0UrUpLa+2sSFS0Fe3
*/