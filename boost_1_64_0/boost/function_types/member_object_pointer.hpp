
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_OBJECT_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_OBJECT_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types> 
    struct member_object_pointer
      : detail::synthesize_mop< typename detail::to_sequence<Types>::type >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(1,member_object_pointer,(Types))
    };
  } 
} 

#endif



/* member_object_pointer.hpp
UPPdOHLAiHfX/EK192TZwVqNGwI+U9fwFgY8O8YjW2OR3GKAGLNAl9pzpjG5zBc7xjnL1SXj4PF9gjzoORNnEr+ydMVyZvwcy2uziJFPrnBInyss+H5MTJzihGhdTS55Ngvn75cxqk9/lCZNQafq/7Dzo5OYelsfPv62ovTDZgSYj2azrPOQ2m3lvvQn2M9aaiEOPQ68FgvK8rEgy1Sab8vmg/4mCPi2kpdPfROh662hqG7He0eH8LDjSNj1uAqbk3OQHL4BcXGt2CmvGNFXf+KIXxpmRyfKKFVfps+uEMWj/Nhdww5aAYE81yJSnlbezCN3u+OkcwhaaXUXMToNUBj8kyjKwMjEEvGkshlGXg+R/jcU+cAnkOnaOfjU+SVmTl+KDtuDuP+RBXbPCpB/YrNZGBaMgyPi2PeLPToNjkKxPECtw5cZcLG7GOjagy/Xl7PyhDJGpinL76tasYWiquxivwIrsx6hdYQugraXcUO6Lr1dt8q4rRpYOGEQFH9+Y6qRCbYGLaFhrxoZUZzdtPemyOCwB9ytYywOmpZy/uRo8ejCdcw8OISOOz5R+5YJPzy9QqsXBbKlbwoPD78jmkgy3I9OEqGlUbxaoiqdPyzg6o7nZMu/0/FnSgKN5rUkLvtiUoLAmNZPROK2YqSZb2NhG1fc65mH82dqqf7pijjwKg2/z7qI2F2/OWRdpHD7MwymE7rJzil3saHVKzlq+SykVkbzn5U2fDPGY7eTEd85xsrBZkZ4YrKaQ77+pVWLXiIo6huX9SqB33UzKsT9kOPPXWD3l8nUePAPjR41yA4YiZW3nWm4+hv6+tXwgXFvZPpuxhTnzjzXo1z2G90Ibb2/bGo04UT+AqH3tAo1vW1llc0D5rc/KvMXBrLIVVXuulCN+AebuffOWX47eEe8cO+ParNY2UzhJ9QfXZKXctQRGVQge7bpTxz3kyc6ezNmZjaOHmyDqO3Txcvh/zDUbRuWvrmHxvhp0ihFA5pNnImDnbncNFi6Pq7n6Pq1XGfynN6XR0j7OVWIzJ8mjCfrY27WATg8PYEJj6+ydv5AdNS+iPVr3mLYmX7ikxjNtve2Q+FpHwabPMSZRdMxpHgq0kzNkRznL7Yqn6RZ4kD8NyEMgUNuiT6DpmPkZ0NBdV3WOYZjdtkmmE5/Tzg/4+GkrzjeaTIur74rt3xYBp7ZjuOtvbjOIpMX72bRd2g8Hc4KeGUvEVaaEh12N5d7zEdjS8p1Tos+wrVzT+NcXjjztkVx/5FRjFlXIf8VHMGPtgPgaLAFKee8EDr7IEestRGhWtU8rDdefE3qh+EH3XhswFjerQ6Wc40eIdJliHyppUZLBUvhpj2ful0SkDq0LU69LuKsloJvz62QlXkOWPSgXs7V1uLTqB6i9EEDm904IxeNVEDbTf1xb9GUJhbzhfsSTbDuTyTnjPgA72dG8n7OWqj8thKjG4Iw3v2gCN48EzPmjaBP+VF2dt6Lgn0tMOHHOhFZ40TvAR2xZVIzRBl15GTzlbi75BD6K+dwfd824q/SPuQG7Edd7Tv27zVHeBVsREz9XDExK5CzFDsJ137NmTNRT0zx3IHPJp/Qa6gTc3p6i+53m3LwjzPSYeUeuIfp4YvyFRp6ncZU+ZCJKjEw+xLBgWPSZGVAEWrszkgr/daIzhmHDYX+6PvWV4R7fYW36yUcnHcftve8kBZ5EoOcY/EnpSMzXr+UuuZtUbNnNz6WPuGFh1r0ufiB1h59xYBfKuw42wX655Xwc+06dK4wQ/73CDZfbcx9atXyoVoD69v/4kKfaqQ2T2Fd1TDqVO9gnFccZ2X0ZtrfPU08JAF5Xg9QN7BMuKfaMd/wLof5rKA=
*/