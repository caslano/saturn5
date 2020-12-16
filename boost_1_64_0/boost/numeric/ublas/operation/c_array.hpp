/**
 * -*- c++ -*-
 *
 * \file c_array.hpp
 *
 * \brief provides specializations of matrix and vector operations for c arrays and c matrices.
 *
 * Copyright (c) 2009, Gunter Winkler
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * \author Gunter Winkler (guwi17 at gmx dot de)
 */

#ifndef BOOST_NUMERIC_UBLAS_OPERATION_C_ARRAY_HPP
#define BOOST_NUMERIC_UBLAS_OPERATION_C_ARRAY_HPP

#include <boost/numeric/ublas/traits/c_array.hpp>

namespace boost { namespace numeric { namespace ublas {

    namespace detail {

    
    
    } // namespace boost::numeric::ublas::detail


    template <typename T>
    BOOST_UBLAS_INLINE
    typename ExprT::const_iterator begin(vector_expression<ExprT> const& e)
    {
        return detail::begin_impl<typename ExprT::type_category>::apply(e());
    }


}}} // Namespace boost::numeric::ublas

#endif

/* c_array.hpp
25GNwRSswoKC/MxAt0mv8+T+rLDerjwvcwryQ0kXFcwSPLxMUtx5y8nJdtO9w2plBsd3gnrXL/HtQ9w8tPEeCKkJkvjtcP82dp6tfXbaG9Amht1huFHk6jZx5YWufJxfjl3YavEcvxR6q1U6NPieJyAu8knPt5nJAT8lWJoWpO9QNMnxh9EJdiAn3wTOHsgZeGbxJubBYAv67mJ+TcPM5RqJb74GoQRClvt8nVL0jo7gb87zdspnML+vFOkCWtxvyd9mezarFAelKXnp8P3bnj6YLopp4z9geIumoyeTXVuTNGbMqHEpzNpgWlHqpGC5zwObGCzz9cgILvf8d3rL8tDe3B/bX2ZmJl1A7vq92ReIyS/E0oOCKrtAXPCztzN/It59mLX4J2LdJ1mnXSg28OTyhAvEYhh9sSUXzBv8dPDNF0jB7FHAD8m4UIpA657rSl/kTBk3DNYF2tKdifgJaVgjeI7THbq3WRoaA2vPSvNVUZ6FMxLWlN8PyZky3f9yfDqLWX+e38COG+QkzhsTk4en3zg0MS3ojN1Wymr+po2UlYR1jSeWsQZOXCgWeqcwNyfbTfGDL0VpWSbcr2lFWeS0K/Ef5fA2tyufHzY8LT1lTFLi8Inp8eOHJrW27M62MYHW/foCMWxqfZ7Ugp+Mzy8tLc8pwcj9RArfG/IIJo253t0EZOFPpS3LxyzfFzEW0UmJY9Pctj3FwqyoovKSKfT2mEnQ7+BnszEwZeWl5P5Abn9kDtl9SRFm3S/HGTosqDVsaGYGS3y7bFZAFnBO2Cav+JE8sKNZ/KbASmG3KOWlmbko7ZqOY4aPTUlPjR+bkhjnq6HIleHuo7gIFsA9RGRlluZDW05tjcNlWDlclPxWCVu00NquZCzOzEnxtGRWQuv6/LwDix82dGzicBbNqr2utSVjksf6e7uA7YzzYkhdh2TmauW6z1rTYSaRYUyE28vyghzmArV3Jfk+ERL773eNCDxi7Ct/Ifvuv4nXWcjd95tpzW3eR17a6pfCnywO9lJLcRFIfhWQsKGgucm8NjLXzyRkAys/qHBSHkjJ7hnd81dOWU4J9tkTfv90SmZhOqvrWEBnsFfgyQs/bi+LeL5NPW7qb4K9WIQ7/PhMkj503AQSdp68zXCQ0PNjg6JuD7aC2TkF6Aa54zxZEdUymSW5hNwVJGfzRH8kYSuYkEXBcaXnx13ezncWyHUfAQ+8uw7dwNxutjKu9Kdip/UDrN/sPibQ+YaAzOfAsBH53fkpyZttUqFtvt9i6F2exr5nl88oZpcj2BcLmMR/s9+J3QO7vvkMeoOBQnEohOX7ReiwZKir9Nk5Jag1ASHmNbArwi9CEMrKLxSzCsmX7Du+4iwfglTuAv44LM53p/IpvrW9YdwGmc9q+E4pf2SpmG25JZfsQoitSmZMmlicP3Q66NaZkO/b3EvDe2GrtfX++xALj2cHXVeyN7Ce3bvt3UFh//nyrja7g96BvtAqmwE9jsNQ8FZ4rc2tKZ56p2dQ/GyRXVzEzkyLg8q8cIq5gRSIYGcqd3Xc3laOtC8GZG4rWm8yt/04hjQGdiU7jJE7mNYNfs7c7fc1vlXJlnLbxUum0PktpzcKe9ndIVvhReyagixgOooNKJnFvvsdguwct8mvsVn1z/ElrJXxrDuBnxRIVJDU/wNIZLDMnUJya/C9btBIzfyRnJCn2f1Ka9/LOiSMHjq81c6XBMLu2p3lhgNtmu2Gfa251Q352kHan/+bi7sGt553W56OU5XrFcVi/Nw6J+Gb+zJ/UUk26Y6Q+yPo1CkeWVQwdDDt6R7eK5KeF45TcaIkf2CeeoHvbuE9FnJvK/Jz87PhL8FevN9WmjU=
*/