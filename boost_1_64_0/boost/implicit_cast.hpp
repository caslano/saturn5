// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_IMPLICIT_CAST_DWA200356_HPP
#define BOOST_IMPLICIT_CAST_DWA200356_HPP

namespace boost {

namespace detail {

template<class T> struct icast_identity
{
    typedef T type;
};

} // namespace detail

// implementation originally suggested by C. Green in
// http://lists.boost.org/MailArchives/boost/msg00886.php

// The use of identity creates a non-deduced form, so that the
// explicit template argument must be supplied
template <typename T>
inline T implicit_cast (typename boost::detail::icast_identity<T>::type x) {
    return x;
}

} // namespace boost


#endif // BOOST_IMPLICIT_CAST_DWA200356_HPP

/* implicit_cast.hpp
Z72mpQ+TxVG8SuhUifsyEGcmk36V6CxrYxdvnkSherK9P2+rZ8Es9et4EiJcCpIeUyPOsH+v1Vi8Fay+3pioZy+SsOIX3kyulLByhdoXE6sbrPcqVlbelfm/Fdhyo5DgwQ4E/R00gbTFiGh6Nh7L7RocXG/WCQnvRQSFveqWTSAkwlr0DXID7CfifgMw2acu2dRUpadY8hu7Ts82stwosxwYpWdpVBfEZDmx/uPk/KR/LkYreO5gR3fQCKVk+AHLJfXFq1nMzGJuyOgHAtQ5hZ0BgpqcOwLgx6WfkCvA2KTiqbyt1pNFco3koicYovCw/eobGzE2U7Xoe2V0R9HRl9DRFPURxMtNLx8d/WHz30ef/8+0+Yd196fOkPpps06Ppk/Bc3mS1oC1BhEYLmIbDqk/Q/2624Jjlv/pp6L8EASchBhZ+ZyJifNEbYP02npF0w/nHLG27lptz2/gtOKgfX+rXbkd732a5v/iU21+rxiI+fWn1yQV4YEfbQl/l3MUlWIhsK7JIn39iU6Cf3SOQYKPwxLDJRtJ3XwKv3P1gHex2gky48UvjUWUKxbRF31RjSAsAheDRu+5VpAQbuhlIcKgzRuMgbpkpKTNF6wH2IS06H0SbAaJuAeFo5VrEE8JtJ4whwgnmF+a4cQl52NReAdPMSq+DeUzQQImlzJCJBy/+hqtAz25UJMSOiG4U/N/taMJ+hJQtXDR/ZCuknDM/e5OPet+sPV1GQnsfcFoVOx5hRdKPHaR2PMuk3hsrPrLdUfa85R3lA24cwh+Yla7fiTOQ9vApPLPBt3CMohmBS4WaBjnCIF2n+4jFvPYaPr5eCrvoHu3NWalYgRH/lt1F6av/E4t+go5K38Scb8VJ6b1iG/ZJjKPZpUna9kSJRUlWoFM30fT+8rqL4mmV2THVF9sVO/Uqr8ptvprZPW9EIdLFbRALTpi7VTPS8I9AP5B+858XgCokFisiqY/mi1x/LWAzTtWCRqg9EleYaSfzaYkaHVNwb+yGrUt8QnEpn6+JqYlv5ItecSnD8SH6so1R2wK3yWSY+C/ZPs+7k/T+WXPRxpg7pGAOUG2/Cs8zuQsBg9HA9no+OPDJYA+JgB0eNhDNfihauVqjoFO6JMSmCl9QvGMbNACBEK7pqu5ozcBAXqrCSh8NiqxlXLTAUyv12Das03SaWchmHB9JQuboIOVAdRaeZt6S/G8aPp1eDIA600DsNRhErC6rKaGgY5ueHFVT24qAffyZoArqkPZEnBvNspvE1v+20b5C7XyX1/F8nV4WcnyrxDlJ/gn8gg8ELsxdQAvjekOx7KTqKogMZqebFT1u14xVa0zqjpVq2q4qGqhFr+eVe3BD2uJgk2Of6yCW57RjnVVYpwG9tILPx9PRoffa1r/XhZ+UN1Vy8IDMf6v6u/HD++KEvwewXcTBRb1ksvq7Gj6ziyU2EbLsc0o8UZR4vfq70SJM7T4v5Gr7m7yP6UBDxbqX1iMTUv2F6OY00Ux36gXi2J0TcQnCQuKXJVJIsUDal4toVGU+tOdPf8dnxbn3UHbxLLFmqWSonrua/IQNBazrWzh7KzoKWfHE00ficfyRG3Yfm4M68ahHLTD6uFqoLm7tOiz5IC+KuLuxwr4Sv2oWhJv2qHyR51ICi6+hAxiXRFj9gei9XARR5v8lOmpdyufg96wLQhpd893z8ODdpK/NFcozV9GCnrg1fm2BUUiDgfmcNHXPvqhU8/5I2VepyW6cqZl4ZvpcjTYwh8Z/riV4ZlgZd7ixl3BAKUwCxeIlkov7lSKa3n8ssCp8K35nU0+S9SZ0+C2fOEyT8tsZv/bUzw6y2MZDaPIhbjFGZGvvosVyJvMuV0=
*/