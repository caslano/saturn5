/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_DEFAULT_HEADER_HOLDER_HPP
#define BOOST_INTRUSIVE_DETAIL_DEFAULT_HEADER_HOLDER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>

namespace boost {
namespace intrusive {
namespace detail {

// trivial header node holder
template < typename NodeTraits >
struct default_header_holder : public NodeTraits::node
{
   typedef NodeTraits node_traits;
   typedef typename node_traits::node node;
   typedef typename node_traits::node_ptr node_ptr;
   typedef typename node_traits::const_node_ptr const_node_ptr;

   default_header_holder() : node() {}

   BOOST_INTRUSIVE_FORCEINLINE const_node_ptr get_node() const
   { return pointer_traits< const_node_ptr >::pointer_to(*static_cast< const node* >(this)); }

   BOOST_INTRUSIVE_FORCEINLINE node_ptr get_node()
   { return pointer_traits< node_ptr >::pointer_to(*static_cast< node* >(this)); }

   // (unsafe) downcast used to implement container-from-iterator
   BOOST_INTRUSIVE_FORCEINLINE static default_header_holder* get_holder(const node_ptr &p)
   { return static_cast< default_header_holder* >(boost::movelib::to_raw_pointer(p)); }
};

// type function producing the header node holder
template < typename ValueTraits, typename HeaderHolder >
struct get_header_holder_type
{
   typedef HeaderHolder type;
};
template < typename ValueTraits >
struct get_header_holder_type< ValueTraits, void >
{
   typedef default_header_holder< typename ValueTraits::node_traits > type;
};

} //namespace detail
} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_DEFAULT_HEADER_HOLDER_HPP

/* default_header_holder.hpp
LzgV9oPT4aXwMjgZzoQLYT68Bc6BxXAufFu2/woXwU/gFfBzuBhWs9ezhjXhNbAVvBZmwWUwB94AZ8DlcCm8Ed4NV8DH4a/gS3Al/BO8Df4TroY/wDtgI07Y3bA7/DUcDe+FE+B9cBK8H86HD8Cb4Dr4EHwI7oDr4WvwUfgu3Ajfh5vgMfgYPA43w69gCfTQfm6B8fApeAbcClvDbbA/fBpOgM/CyfA5eDUshbfCvXZ54QtwC3wJPgMPwAPwFbvc8CD8GL5mlx++AaOwu7dgXfg2bAwPOT638p1Bvp8cCvC5bYieS/NRTRff16awLWwpPtVnwB6wORwBz5QxDC3gpaLnrDEpx7tYjqePBUiW46VI+vUk/RRJj23xrZZ3PXm/PRTgW53k8l5X9WFdmAozYUM4ATaCBeJzfw1sCh8Xvadgc3gQtoJvwsbwkGzLmrHyLsH7lBxfXzO2jYyBaCdjENrD5jK24izYAXaHHWGmhPeDnV3iiwtHwvPgDBnTsRB2hdfK2I7bJd6dMrbjPhnbsckOl/L0gvu1MR3pvudmqfexAT6l3CMdvYJK9PZ5wvc9DXftP93f9NBnVfM5PR3r/v3Uvqaesp9m3b8OZafH39Rv3b8w1/yrqp/phLKT9zU9nX6mlfmYrigLf32/k/EtLUY2llXdt/S/2a80wKf0lP1JC/p4rJVICXIA+QiJ7svafEgWko+s7BvxA438Ir/IL/KL/CK/yC/yC/f30/j/z8uba7v/n4a1/3I1//+VhrX/hqQRvqm8P3Rk/wuq5ONIXKf/+a3EkL4H6Pn38UxiR7hrt5h8dThWUP9/qxgVV/UntIRfw9eouxJT+fCNqcgf+T0VZ49nrruG2bczuNxOn2zrx+x9l7ijraHuNOmLf9gOI+p7xP6la4d1Y1Qz6/dRaS5TXZG22R9S8wsoVTqr3WdHTXelKV8viUfp+7tutt7Dj3q6u4G1x93a5UtbdIz+OK0l70fV/nR3AjXYk5Hq9/BFNYb07sOfeR9+kUlR34sfW/nxOI6T//iAYxxP9s7zWDi/3N8vqkTF85aFv75X2+tcF7BKpOY76dRnJ1V3HZTvZOA4iXr8la7iXx31Dl/x5rtcLhVOyCeb7fAno86x3qEf4QJXovhpesNLqbkos8+kpPuWKsc17mQ0Q6UZyu9xstLrzPe7hJD+hE3R8fcnnGm7jzk+rl+qcj/lvhmdM6IaWNdEtVbHy9LmUfaldc1vbd1oLa1cGhDNJ/xxe//5UjY8StX2ZFcjqy9pOnU6Q/fLLFI6aa5Ue1vKTn6i6nHuJrOqz2pXmqv8fFzmHOtVFW9XJcdS0106vpO+c9LW1cDivAT6ijr1mq/Sas65jHH5fHkHq7I3dPwK/q50qpE2+53jT+M6SXGNcsUp+/0mwA5qls9P7dTpDSpeTaV/PEC/vBwyF7vkZbEdh+MctLqFOr6Ke0yf/1Ti9lN2/LCkhcWr7SauJOvToHU5nDFISkf3/Z08b0bhjMm5+eU605ROnMmP1PE3ra/yeDtX+BBXoC+pXO+6DmVh7Q8X32lr4BeEbpzr2llx0e44V9GTDKoJMaZG4kwgzh47To1ri/Q+f12nCJ12tk7t68736bRJ8Oq8ynYnzZd1sm/sjEinBN1H1Rs2BZ3lCeU+px8naT6nEj9P2EHi2PKAxFkvYTuFO+BSSX+q+KQWSRrvJFHnsDv7pkuapMEcWOjL8YXMo1W5D2siPqwLlI1b9mSxs2lNvWtOPR6eX+tbiafq16raJYlv9leND/ZXde7LnOQgn8dhPHeUPeF3X66y32PZE+E9e6BXoV9pzy2hfRZ/IK7PZ9G2zTY8YzSiPDOSbdvsoT/PKNs=
*/