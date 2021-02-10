
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_INDEX_SEQUENCE_H
#define BOOST_CONTEXT_DETAIL_INDEX_SEQUENCE_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {
namespace detail {

#if ! defined(BOOST_CONTEXT_NO_CXX14_INTEGER_SEQUENCE)
template< std::size_t ... I >
using index_sequence = std::index_sequence< I ... >;
template< std::size_t I >
using make_index_sequence = std::make_index_sequence< I >;
template< typename ... T >
using index_sequence_for = std::index_sequence_for< T ... >;
#else
//http://stackoverflow.com/questions/17424477/implementation-c14-make-integer-sequence

template< std::size_t ... I >
struct index_sequence {
    using type = index_sequence;
    using value_type = std::size_t;
    static constexpr std::size_t size() {
        return sizeof ... (I);
    }
};

template< typename Seq1, typename Seq2 >
struct concat_sequence;

template< std::size_t ... I1, std::size_t ... I2 >
struct concat_sequence< index_sequence< I1 ... >, index_sequence< I2 ... > > : public index_sequence< I1 ..., (sizeof ... (I1)+I2) ... > {
};

template< std::size_t I >
struct make_index_sequence : public concat_sequence< typename make_index_sequence< I/2 >::type,
                                                     typename make_index_sequence< I-I/2 >::type > {
};

template<>
struct make_index_sequence< 0 > : public index_sequence<> {
};
template<>
struct make_index_sequence< 1 > : public index_sequence< 0 > {
};

template< typename ... T >
using index_sequence_for = make_index_sequence< sizeof ... (T) >;
#endif

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_INDEX_SEQUENCE_H

/* index_sequence.hpp
yqQiWaFNxO+I2AmKM1RZvWnwn7N6r89D2dZoVMKgbWqeHSRB61wkIUissoYmL+yllxgnMEaXaQ2LSTcRRkESzAMvNrCgizh/2teh5xgWK41ei27ffv2PUpRRNcbl03KsgxP4xzDg/0rqwJOCOJgwKlWDFwC5z9CUxMr5dlpQMVV8yshOr3yEsC9DhV5g42bMvNdkH7auyz5Kx8NecrHtF/HJ+NewStppYH+1Xc/+4npusjI6yXtzwg6vwb8Z3zF9Hx4IULnBoW2j1T+zZu+tdx1Q5CTLyIevtrd0jIgovDf6OicNroD2V8SArW+Dtmm4wPPf30l94tK/8oMbPw06j+kixlW/raPYccD24gAPzZfosaGFG3lunAS+t4LR+HSCuj/ORU68vHbSiyi4Pswd1fbaPk59A1BLAwQKAAAACAAtZ0pSXhG8vdcDAAB4CAAAMwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQVVUT1JFRkVSRVIuM1VUBQABtkgkYK1UYW+jRhD9zq8YuV/siMNxUym9ND2Vc0hDw4EF+FJLkdAalrDVmqXsEsdq+t87u+DkfE2VVDosGzzsvDfz5u06tyM4+maX5Wg4ePXKzDfDC+/7pEUr/qC5ejkh
*/