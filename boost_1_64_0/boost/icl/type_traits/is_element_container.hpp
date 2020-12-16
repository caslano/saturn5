/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ELEMENT_CONTAINER_HPP_JOFA_090830
#define BOOST_ICL_TYPE_TRAITS_IS_ELEMENT_CONTAINER_HPP_JOFA_090830

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_container.hpp> 
#include <boost/icl/type_traits/is_interval_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template<class Type> 
    struct is_element_map
    {
        typedef is_element_map<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::and_<is_map<Type>, mpl::not_<is_interval_container<Type> > >::value)
            );
    };

    template<class Type> 
    struct is_element_set
    {
        typedef is_element_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_< mpl::and_< is_set<Type>
                                , mpl::not_<is_interval_container<Type> > > 
                     , is_std_set<Type>
                     >::value)
            );
    };

    template <class Type> 
    struct is_element_container
    { 
        typedef is_element_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<is_element_set<Type>, is_element_map<Type> >::value) 
            );
    };
}} // namespace boost icl

#endif



/* is_element_container.hpp
yetGN1+FJudSEvts9KRTjo/Gc7UzpDx67vKavTrUA+nZ1e68W3jv7Ozw1o+vXB6ch+dZPOfjeQeeC/C8gOfd8Gy5bnlwIZ6teBL9KjyJfjWeRH/uecsAh3yG9zF8O54kp4BnC5778CR5h1jeTXjac0yWO9PPmrC96mMTJe7b2RIdXzDz3ELK978l0Vqc0yxlAWLdJUpRUOgUn5h4mgOQ0Zg7qOhd00cK6KE4vIyREIbFdL5TVaOBLL7JLhWdT3Fp50H6ArTXRG/KS5wKYlMNjw0DIx5h/TvGPu4cyFO5Omn2IiHn8O2Vj7Ca7kyMX7MYUBtOMz/DnSdeY9jwxUA4+5XOvdxEBJSOw1RHUB4Ofnec1ObvLhnTtnVo89Dw44euYvsvx3bsOzU4LwZ+/Df3rjHgJzXa2qeuLE2BhWUDL3xVJ1+Q7oujeSakOj8GG87pfUOfcgheR3A+2bqpGeW8NuOdGRUybkm+mVjoPVLHcDjwNrZiYkYdA+XyLp6pUhbrcvNojv48xHp8SZ6A4eJPF65mxHLKQyBSDqUICq03XtCESuToOMfUqKXnAghtGsOkYc8qWQbDh2BbNbhkb6YGY7yKuASbadUn1+Qu0c5Oju1VeF7KT6xvL7r+PDq8xKWpzPPgyeSSYPeWJcEjeO5EYLCH3+LB6vPuWnpV5vtN+8X59g15fLuZj3wwvmkoeTuivFvM99Wxi6d3QuF7L/O1bbk4XyC55OI0d/EH0+UsI6CIXhxmrCnu9II56c5kR4ae6hjtmk7FztLTCBkBe9nd2x+LphOGLGXpN5R4vOGL428c5AIUuid3PZ4KLYHte3WTI/3biHdz4gkebGvPQH+MQfjp8bjOJ7DoCHai0okRXjsnYgqI48zmyeprpsEZqs6IoUHxG8U6Ko+dcHlPbtucGS1W3Xid//CKvWQBpoEtbzAAqMFAKOsyqpeupHvBA8vzx43VeD1XzSA5eTILw0vV0Qz+pCYMrgur7eqqYajX4iwOcSoGn9mTuCeiGBklAN7kXcpMa9VsPlOctN/xxWkmmhoKZ+rg1OPCocL3YEQ3/WBMzHDcHJ3J4Uq0UfzBHhdW5fxxHKu0TGIbltH9yb7ESEbcEoTj7PA7Z0WPZ+J99pkvC/BpOPeOIssH57ZNE24meX705CvqpVtnOM7Vwu9cHWpcF8I46mt2ybnE/nAWpuO0ih/NOtckr+s08iZ9rAiYwGkLnBa+Ei9O0joRlcPxcnYca0v+Gpph7t3LnDWBTzpTB6ZmeLFqUG70NZlzVtAoWqAuldR1MhaQEOQcwHSqhpee/B0uprw60qBuouOd77g1NObgkG9hxkZfgCodC2RExSB9eenhaVFoFbDW09bweXMX6s5dkztxHKCSuHtTL8cxLc/J8pDW2A38YSNpCODwN/vLloGO4BSFK1x8FpO77PW0mhmBqyBqHqk7gikFxtrBrilkSMm6tpblPKNJp+MgFi1VxtwIFWldfH6DL9QpZKhOeIzyxhRtEEmPbE2lE3EdHEAtQDGQHVuXTMw/cQEE7G8bNjXxdpXxSCPSQf8YjzA8+wGLlgERVsVtKBARhTuMjY82LCytcFBydGLMd+hH+ziLbowxQ7GRJySRI8Djic0hOhgHcAAnaTs6165b37Uh2hOjq/OVX4LWegZ6pd14Rq1QRwe8Zu71pJ95cASgv3gtvBr+KDNPALiHjCzUB/PiBlb+Tg9WVwTNZRjEDaKxgUR0hN+HhwbskbMnGg+ln5BMNJff6FytlpvnzdGhJ+gDr5eGjsFPh+jjOo2NxhXrDdpWgAD2yEKm9Gck7KsDs7Q0GrkNa+6rnJZuK05q3yQY96Dg+ETwRFgdCNGvJ7E=
*/