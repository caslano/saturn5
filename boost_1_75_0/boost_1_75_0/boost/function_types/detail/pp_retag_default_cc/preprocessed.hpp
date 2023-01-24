
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is guarded externally

// this file has been generated from the master.hpp file in the same directory
namespace boost { namespace function_types {
namespace detail
{
template<class Tag, class RefTag> struct selector_bits
{
BOOST_STATIC_CONSTANT(bits_t, value = (
(::boost::function_types::detail::bits<Tag> ::value & 0x00008000) 
| (::boost::function_types::detail::bits<RefTag> ::value & 802)
));
};
template<bits_t SelectorBits> struct default_cc_tag; 
template<class Tag, class RefTag> struct retag_default_cc
: detail::compound_tag
< Tag, detail::default_cc_tag< 
::boost::function_types::detail::selector_bits<Tag,RefTag> ::value > >
{ };
template<bits_t SelectorBits> struct default_cc_tag
{
typedef null_tag::bits bits;
typedef null_tag::mask mask;
};
class test_class;
typedef constant<0x00ff8000> cc_mask_constant;
template< > struct default_cc_tag<33282> 
{
typedef void ( *tester)();
typedef mpl::bitand_<components<tester> ::bits,cc_mask_constant> bits;
typedef cc_mask_constant mask;
};
template< > struct default_cc_tag<33026> 
{
typedef void ( *tester)( ... );
typedef mpl::bitand_<components<tester> ::bits,cc_mask_constant> bits;
typedef cc_mask_constant mask;
};
template< > struct default_cc_tag<33312> 
{
typedef void (test_class:: *tester)();
typedef mpl::bitand_<components<tester> ::bits,cc_mask_constant> bits;
typedef cc_mask_constant mask;
};
template< > struct default_cc_tag<33056> 
{
typedef void (test_class:: *tester)( ... );
typedef mpl::bitand_<components<tester> ::bits,cc_mask_constant> bits;
typedef cc_mask_constant mask;
};
} } } 

/* preprocessed.hpp
MDA6w8FYCzDWYhxkC4wpEsb0Y2j7N40P1Yk4eYPj2Hi/xrSHDhRdJvftWObqB6eQxztaB9yl+pCg7+/10dL9FS3wF9xg8f9NCd/n8xLDeNdsMGKLadKG3BdiF81jEL+50Xm6+IaQefL3jzMGTIFoTLFqYqJuaMrETG8XZmKCfSpKN53Op+LFnFCfCrItmsHLLo3Nl9IE30erZjG+6azEoNnS5UG6VLz/NbmosqlOidO0rImjLlW0FgevE/TY9JdQNTo01wrA2s4WP4qfBjTFj2KkM7wfRca4Bv0mbvii0fkbOyBk/gReDhCTmGE8PMk6iX0HNGUSq9qGTiLRiwP3KL5Mc70X5WLe3mjaEGGWxGO9Apx1RlA9aPuL/roZNyZ220a01z3RLn2lTz5gt0nI7OVvAwUv2xzwCN45UJUPoSGPANP9hCLbr03Sy9+DrLu17OAwzyCmcbZ/QoZHEPTpXxdd6Patcf8/2r48LqrqbXwGGEAFhhEHrSzRMCmtKLUwtWYKdEhQcinKjbKUyooKihZTA5dxnNS0rG+LVn6zconKBS0Vl1xywdxNUzTLi+SSJWIu8zvPcs69d8DlfX+f9w+9zLnnnvV5nvOcZ23988UFpQXRAefZTBAYV7qxuU1a8qvKgDyFzbs3aXFiImi6m5Xu65GCQ8KYgwSqWUaL8X3A2fu6Cmr8UKQyGQdpNJiMZxUMQtiGNpcVgsl4
*/