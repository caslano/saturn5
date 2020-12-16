// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_CONCEPT_DEF_DWA200651_HPP
# define BOOST_CONCEPT_DETAIL_CONCEPT_DEF_DWA200651_HPP
# include <boost/preprocessor/seq/for_each_i.hpp>
# include <boost/preprocessor/seq/enum.hpp>
# include <boost/preprocessor/comma_if.hpp>
# include <boost/preprocessor/cat.hpp>
#endif // BOOST_CONCEPT_DETAIL_CONCEPT_DEF_DWA200651_HPP

// BOOST_concept(SomeName, (p1)(p2)...(pN))
//
// Expands to "template <class p1, class p2, ...class pN> struct SomeName"
//
// Also defines an equivalent SomeNameConcept for backward compatibility.
// Maybe in the next release we can kill off the "Concept" suffix for good.
# define BOOST_concept(name, params)                                            \
    template < BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONCEPT_typename,~,params) >       \
    struct name; /* forward declaration */                                      \
                                                                                \
    template < BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONCEPT_typename,~,params) >       \
    struct BOOST_PP_CAT(name,Concept)                                           \
      : name< BOOST_PP_SEQ_ENUM(params) >                                       \
    {                                                                           \
    };                                                                          \
                                                                                \
    template < BOOST_PP_SEQ_FOR_EACH_I(BOOST_CONCEPT_typename,~,params) >       \
    struct name                                                                
    
// Helper for BOOST_concept, above.
# define BOOST_CONCEPT_typename(r, ignored, index, t) \
    BOOST_PP_COMMA_IF(index) typename t


/* concept_def.hpp
Ehe+SLOUzbUXOuaRv+1HjPD5LMqdWOaFqPj4CKfhR8xKU3iRk8V5VPEOWhKvfMox9CNG+BzmS57FYaz4eh3z5oFOEPlOW+mFvvS9ONVHOcdW1HgIQxTyoS9FwpeyIM49nwuDsZwdzM8sl+7cD/e0L2Y8w7R1K7gXRjJk9nRwwHcY58KELynv8jhxLhg5erXZh+mOf5mmK8M8c5zUZ/Z1gwHjiYrv1oTPUeWVPHaTnNHrFFV6J6p2x0w+wQrHC7PMTTQbSQt9wkkrjwnnsRO7ktlXFwZ8mNY8TSvznFzGRcrwre3Qla2DfqZNnoLlUeqH3Beah5TJwbZm5S9z/SgVrmDlPGRwuNWGbQudP/RnTvh8lgRx5vE8Mvn0RcQRP3nvI7we4yJw0sTNNS+YBMKKvqYtvsiTTuRHGfLhA1rK90urjGkW8yQNfc2Hj2OpH0BI0OpPcc5jzwuGfJgc4dtq8XHPzUQQp5oPtNkuFWTxTRA+n/HAEUnuMvtGku1jMSZ8EUsct3DDNGW1V5ko7zzhDVmQBFGRpWWivD7ZYexDwpsw6fJUZpFAXjtl3X/xLp7Fzwvh554H9TK4B/2w9tQuY3un4ncrHyWEHxzUF65qghnlh9mLMZuxynB+JA8yEzIURIZ+nQGiqv6Dvn+/Qu9oRrHDHc8rCD85YKL3GScs/tTlEfejhPI/VHm06j20O4c5wPt+0uTPWOrlEQ8FZ8OX6rQvHNR49FEZRqrrRS4wjPag1jG0LSafZIrDT5JcMvp6nLatUyStgHkiF77ngY0op3yDuVbbvMyA9xJeT3gj5qW+TJyisHjLbdXK2w22C5PX85jrS5VqmjB97F1u3BzpHesunxjUbNlGFvqLrIUyzhMZCYszJ+RehCKansaZ93e3fZX6SMy4E4Uyt4XYN4lHfOXGRE4KdigMkihhTcf42qdmxT9v8bueL0o/3E3XBTS/W/VzzY/30xKHByKPkb/pXRZrMfS1a8tIvSBK3aRexkqtjL8RGZwFuSiveV3otoQ515n4GtWFz6ULV3hZ7TV6bNK9il9a/DIKXC8uClZ/vR75q3bdJ/wR427iRaHjstpr97RdnyK8BRNeDrueKVvnOr5OH/2kvs9KP/ecvPC4YLXX9Gn6ZwlvzqIiLrLcJ6wNbZmVfaJcPJp16DCvyN0gywNmPH/pt9s7GwRhXm79dcuXtSdVVtLUljNqulsO+k8neSmYn/MiiaPcljHSsA1/2Cet8kSel/HMoTLAhF+gPK+3yxNHXKnGs+WsV57PWOVJUxkHQZiNymguT+sbVv0ksUzyzCEypto7Oheqn2/Q8sRBEcYyHZGzbv18g5YnSZ3EF16tDLs86KOe5CNiWeZGqsdxU4bd33COa/EWSZr4YR5S3vq+skZ4c1YUiR/JnOS9QYdY/l+S8seqLjwvCJOcXeh5NhvK2PpNMx+ChTF3kgT7ybpDEMarIDI484TkMuMFa3xCTPkPEv6EFW6aBgXy1w9fpq94iz8NIi+InIg1PLG02+Jpk99zGXdVTaSSsws9wVVCsG8RGRkDb7RJ5KGMxqfJhozWtywZgSe4K8NaGSv1MqaJjJQV8JjVU+W90DNSw2d9/1vUv3lURImTcxaQGzu0PT/5W7Q9B76MwzB2KRO95mPHSrjUlCGY74UylJHPAvP2zoDpEL630Tw4P3eDMIb9l6D+6oo9Pz9H+GMWhdxPndyv56+WKGg/1KBH57CFKETsOpi+eYXF3lfZSng5izIe8lx4lFdN9K0tJKxrwp8zXoR+HDrxCP9RKsGcgx4kMiRLhBPmbsipDHWWsTozeH7UmVUPmVDMsP6JnIK58KDN9SIqB1x9jkhhWP+mDCU=
*/