// (C) Copyright Andrew Sutton 2007
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_NULL_PROPERTY_HPP
#define BOOST_GRAPH_NULL_PROPERTY_HPP

#include <boost/property_map/property_map.hpp>

// TODO: This should really be part of the property maps library rather than
// the Boost.Graph library.

namespace boost
{
// A null property is somewhat like the inverse of the constant
// property map except that instead of returning a single value,
// this eats any writes and cannot be read from.

template < typename Key, typename Value > struct null_property_map
{
    typedef Key key_type;
    typedef Value value_type;
    typedef void reference;
    typedef boost::writable_property_map_tag category;
};

// The null_property_map<K,V> only has a put() function.
template < typename K, typename V >
void put(
    null_property_map< K, V >& /*pm*/, const K& /*key*/, const V& /*value*/)
{
}

// A helper function for intantiating null property maps.
template < typename Key, typename Value >
inline null_property_map< Key, Value > make_null_property()
{
    return null_property_map< Key, Value >();
}
}

#endif

/* null_property_map.hpp
26/ehf5Y9IxZUX4xj62qfI21Z2Ew8+16xtmZsnd5GRKsMvwdxnnSKytZRpUR2cz4d8R1MfDGIky6GU9e3CnLsJzzhRcyrnE+ZdaF+k4W2nXwAmt/6DeC02vreC511vmQuReIDvaN+udS2/yT51INfucfMf/QCXcUBrkPNIw44y/Qc6mv+Z2Fy5B09wXv3yK8CXW1njVd5ZkOnj1Rnju8PG2FZz14vuI8XN3jwQTs387z3Yuh4W6Hn695J0Td3hj7MMAjA0HejV73uvf+98VAuf/d1gdYPhlCYxci6XhXmJ3GwS4SZtM1Yz1rz8ozbhxoxrumv/DUS385eAJRnnZ+PHvHWWvYdX/2pr8mRvoXedK/jnSyK8x3EWZ8NP3z/NKfNB46WZTnMi+P1DXWr0Tw3GTVtQbqu893cOu7BTH03VIfuRyOIZeXu+Uy/deqrFd5pHeDtxd7yBldv4D8gJ3KD+qvjdu79dl00E59dxZop35c7eFfCdqp//ax7ka40ODfatkTWQEciTQVdLT7CiTOXoPW9zlsuXIVea+x1/lJd9KzEz06GZxVLEC/4D82pT97bxroVaQLTdX57DPalMe9Ge4jxlyE69TzLqO/HJeedzvtzjVvAjflsGdPzHCGFadnq+vIP9eMyMQx6E/HTLLGpDcNCw6uPdYf9uUT0ddOEpk4TGRiKwjBzoGz8Ss7MuGSgOFqAaWi7JNUuegvE9tKmg4xDT/CKG+8sRBpuxqrBU8CI2nCXZi4DF/HpTuCaTHHpeQbPskal85QuannUGTcmITa0BiG6Tr9+X49Q/psJ20/nvV5rSe+e9ubWDqPY1z4Wkd3vX2ro7ueN+/krucbOnnuEegU+16AVy8y+LcShnvBYQ6C5+1OrnoeMcVw031IpkEbqdsWf0jXdj4nXWwM97nz6CTd52L1IVHbkBEZN0JUOtcyMjvzXSDM36frmhlOtrjG/CnkSeLcdS+02174pmR8HU6hBwM5p+yjyF8O/kYR/qxpWldQ9s72oGcaz2Nc2S7/m+E/he9/tK+33mTRvzqDdSbkL8qd+esaW4Tz6o8tJkZkUmdXWVX7z40JL3zauhx92HuNOp9+bBHlaaNji8tJN/MdW4Q7u8YW8H/6sUVB53/P2CLar0S++fRnwBoytrDKpu80g3/XIZEDBC9CXFvtstF16wz7u4uiqdPyEf6hOlfyK9J5nLucFIr6yS+ssfUJ9TNIdePXSH/DVPnpOafxR7r3N0PW/QIIMxIkL5Rwzh2Q71yGs7WZ7N8tLtIxw7t0H2daa2eU03C3+r/f0n2lzh++10XmyME/OaTvRuk4wLunhrKefjKEtsJI4lx+DQpv1tTo/nucStqK/ffjuAM/cgCrcbDB+++t9M5l2Ou96WU7tu6OWmeFkW5Aguo7FqwFtwGPwGywdCzz1GumfU0534H+ondXtgl9x6UJ7BC/63xUgan1T+sN7NkmUTdgr3VDZQny2bWv/06GiRrh0Xd6zTL490eZd38L+A347dvVrr8LS1b4yRXh66N15xLSP4jz12ssP130XM4M0hVxC4zlug9/f/foHQEhx/mlFUUl0cVyGe+VavwbzNE4lbMNd0T0wi85myNhBL3yiX6nnMLvFNsv6+Y0tr8Srf8/pL/lTrmFsNxjZnv9ALlnT/2qn74eP+td55zgx7EWPYF81eYg7F2LN6doPTWYxkzTZ4ytbxYeZZhhBGrL5jfpN0ffUZvOOF6Ki+hSA6eh8s3QNYc69KMc8076Bua0ZljnIRNOufBwpusOZd103cH7fdQ5ixF3/AxLv6tr67PuQL7WMyz9rq7Sqd9Z3zZJw8nzW3cg31UzrHWH0b7rDtVd7XU=
*/