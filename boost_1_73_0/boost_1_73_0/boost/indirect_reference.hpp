#ifndef INDIRECT_REFERENCE_DWA200415_HPP
# define INDIRECT_REFERENCE_DWA200415_HPP

//
// Copyright David Abrahams 2004. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// typename indirect_reference<P>::type provides the type of *p.
//
// http://www.boost.org/libs/iterator/doc/pointee.html
//

# include <boost/detail/is_incrementable.hpp>
# include <boost/iterator/iterator_traits.hpp>
# include <boost/type_traits/remove_cv.hpp>
# include <boost/mpl/eval_if.hpp>
# include <boost/pointee.hpp>

namespace boost {

namespace detail
{
  template <class P>
  struct smart_ptr_reference
  {
      typedef typename boost::pointee<P>::type& type;
  };
}

template <class P>
struct indirect_reference
  : mpl::eval_if<
        detail::is_incrementable<P>
      , iterator_reference<P>
      , detail::smart_ptr_reference<P>
    >
{
};

} // namespace boost

#endif // INDIRECT_REFERENCE_DWA200415_HPP

/* indirect_reference.hpp
Px8CHMEzrt8Y2D083KRruKm+Hefg9HGzi3WFbj3xriGnq+fM/29BvxjSheGPR+OvFla+O1tOHw+6rjvQIOodbdhtWkqvg21z+rjnutasPLfub6vu0kbjzx0aqdbJS9VvTuk5vH7UdsNG+YdDb7rjBdxWt2jkhpjj6APHfYz3anCD706t4yJp+v708XjOQ6op79rurCa8od+Uk2o0XuFPmIR7Ci9MhKZYyC7ZHp00KgFU1gjKEFIXhylcCweqaw3ptelWlO/OmG3T1oBDcz08tCPszhM9z0xnOLK2Op3szhbN2N5E2byfqrPcLWMN++xvc7YVZXsItz5b1u1ht2TijjJJWXjP0oCHB4Psl9cl/wFQSwMECgAAAAgALWdKUn+JslyXAgAAjAUAAB8ACQBjdXJsLW1hc3Rlci9DTWFrZS9GaW5kTlNTLmNtYWtlVVQFAAG2SCRgrVPdb9owEH/PX3Fq9xCmDLo+tVM1jQFdo1aBJdAOqZJl4oN4BDuyHdpq3f++c6Cj3Yd4qRHYXH5fd4bDt6+3gkPYu1jzZrRo94SR0d8xd/8GM/YImxeRbmnfY9GBHeORtWAv4xHChsG2Hmf+zNgem1sfzH90PPGW+SNVgkPi9XT1YOSicBD2WvD+9PQE3sHx0fFRBH2u
*/