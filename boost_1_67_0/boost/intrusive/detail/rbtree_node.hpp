/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_RBTREE_NODE_HPP
#define BOOST_INTRUSIVE_RBTREE_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>
#include <boost/intrusive/rbtree_algorithms.hpp>
#include <boost/intrusive/pointer_plus_bits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/tree_node.hpp>

namespace boost {
namespace intrusive {

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                Generic node_traits for any pointer type                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//This is the compact representation: 3 pointers
template<class VoidPointer>
struct compact_rbtree_node
{
   typedef compact_rbtree_node<VoidPointer> node;
   typedef typename pointer_rebind<VoidPointer, node >::type         node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node >::type   const_node_ptr;
   enum color { red_t, black_t };
   node_ptr parent_, left_, right_;
};

//This is the normal representation: 3 pointers + enum
template<class VoidPointer>
struct rbtree_node
{
   typedef rbtree_node<VoidPointer> node;
   typedef typename pointer_rebind<VoidPointer, node >::type         node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node >::type   const_node_ptr;

   enum color { red_t, black_t };
   node_ptr parent_, left_, right_;
   color color_;
};

//This is the default node traits implementation
//using a node with 3 generic pointers plus an enum
template<class VoidPointer>
struct default_rbtree_node_traits_impl
{
   typedef rbtree_node<VoidPointer> node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   typedef typename node::color color;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return n->parent_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const node_ptr & n)
   {  return n->parent_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->parent_ = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const const_node_ptr & n)
   {  return n->color_;  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const node_ptr & n)
   {  return n->color_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_color(const node_ptr & n, color c)
   {  n->color_ = c;  }

   BOOST_INTRUSIVE_FORCEINLINE static color black()
   {  return node::black_t;  }

   BOOST_INTRUSIVE_FORCEINLINE static color red()
   {  return node::red_t;  }
};

//This is the compact node traits implementation
//using a node with 3 generic pointers
template<class VoidPointer>
struct compact_rbtree_node_traits_impl
{
   typedef compact_rbtree_node<VoidPointer> node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   typedef pointer_plus_bits<node_ptr, 1> ptr_bit;

   typedef typename node::color color;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const node_ptr & n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  ptr_bit::set_pointer(n->parent_, p);  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const const_node_ptr & n)
   {  return (color)ptr_bit::get_bits(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const node_ptr & n)
   {  return (color)ptr_bit::get_bits(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_color(const node_ptr & n, color c)
   {  ptr_bit::set_bits(n->parent_, c != 0);  }

   BOOST_INTRUSIVE_FORCEINLINE static color black()
   {  return node::black_t;  }

   BOOST_INTRUSIVE_FORCEINLINE static color red()
   {  return node::red_t;  }
};

//Dispatches the implementation based on the boolean
template<class VoidPointer, bool Compact>
struct rbtree_node_traits_dispatch
   :  public default_rbtree_node_traits_impl<VoidPointer>
{};

template<class VoidPointer>
struct rbtree_node_traits_dispatch<VoidPointer, true>
   :  public compact_rbtree_node_traits_impl<VoidPointer>
{};

//Inherit from rbtree_node_traits_dispatch depending on the embedding capabilities
template<class VoidPointer, bool OptimizeSize = false>
struct rbtree_node_traits
   :  public rbtree_node_traits_dispatch
         < VoidPointer
         ,  OptimizeSize &&
           (max_pointer_plus_bits
            < VoidPointer
            , detail::alignment_of<compact_rbtree_node<VoidPointer> >::value
            >::value >= 1)
         >
{};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_RBTREE_NODE_HPP

/* rbtree_node.hpp
iCdOukF7zjzeXWKi1C9x0EyNnUuLly6/MQjDR1om8UoR4olE9qpSmqbfirrHZFj8sE1DXYmfKsmZA8XRkvLimy3OyX0GglDXVM+EXukdEfgnKOvytUH+lNiE+NgP2EZVOtRGR6gbVDPNhJ7ZWVmPCrYok/Z7lpgQxc6dh08i67kNmgn28Pl3tLnbza4XfDVafXRxtscMrG7QZaPLjlBMIIyD1kNjj+u2W9lMqxiw2UxqZYPCBf3IefRjoVTV3zxQI+FHrltC64Ada9J8vVhCYAr/u088ri+yU+dMDHhIMIHX+MGW9APQgfYZtD4/ZR80xScCf3oNLvAGId7XoC8wDCsNeCAreclBPD3xp9LPb08BuQTI3grMhX2IYvj2JIHSfcRzLEGYIec9fP4pjq/6fEcgy/do4pyAFN8XT5bMu+I66m4t7aMlAef8prFGCXoFYUEb5cb35RXmQQLUzJXQWjvagnu8gXcQD0fysfqb6V+h21/HhqtNRBmEVBpt7yddC5/ZfuwCwcGuQLaDqz5qdDU/xkEsQQv9KWGfpyver6KhF63sa54XrzsiBJzqzTM+LoQFDWN0Hb0f9wyBS117a2J2iHY9OyGPRp3lVpi5hjgvjDTi9UBHw1SYpSXG2VvGx7JZBaa9sfs/wyRB3p8OpINqC7A2oQMyOAlA4xAMZAWxZcI4DnglhqtzC1fcVH5Bu7y3vmzGX9wic4V22ssz6DXT/Lz7OpK06EmCbUYEW2Ad1ALMx2Swvu+beZce0V0UtzcNTEF+lv/Q7TgeNedyxZLDDNgDjzV7Ky6g1BDDTugvAnwBzFfsJoWPkZXbZ996MgDiwMoc8CHPI7QKLDCq4YrLwtggwU1KYJtMpedlLEByEMNMle6Djhnr04jyLIGk9BRYTmCRwzliaMMyrYwBYXXMu1/Iz6cL5HHBul4uXbCgQcd0GoSCfsCFYPoH6MHid9akPv4MjY8BLb1yE/muTwGr62o72oLR/nhC+t+TAonGp6dyUfFV1/P4Pp9K6ZwfDfzaw2HFOwNX/ewD2bsfZ4wYnW/OGbEr4E107o1eOadUkyHDx0FnFp1T6YCEfuQTBMY3dtrsS7rzunQTUewyw77crbidm0k14kyHP9h/LE1pQVtjt4ewN+1EN/NyJ5xXMST+mEDZSMzfD4BxKXkXy6/krfD7mCg+QDPrfyg4a8vrcX7L2Dfi6wEZpB9+c1Ul4BczsuLUvXvoKqQOxd+LPv37X0oMnuhXSLHRcgtZIHrAXKR7UxIiqufXyBO07SJPzq1LhLh0zQVBQiQogm2+G7suMhJuJNQ/4GwttdkGCSFE+Ny10Nma7WXSZyIqffKaX6ZlJhK+EUjABXFS827HcTMEYPpDSEn2nDpqvwj0XSq7MTKQolL/dUGEvqWRPfek6keoqBaXW8pyE49WuOBHHJhiu3MHshyGCFn01NBJ7Jqsh48g8k0hUgJsUpm5S/ts799vBH3LvgARLG9RVJAZX+/eNnI7KJEOobVQEXOPyPkcL/fQt4YY+pGNMOefAwW+Zo8+B6ZNU6f0fTIBR2VRUrdn++DFUTNFBEwXoYV7VWtMsBYiC7p2bdHyRzsdhHvNjKEFYIB02B1GEXg9GhXqXmL8qHho/VhG5oeJEJaJ80+iehF6eB3pnz9BIpe3LR6+RIOPule35SkMjNMQcFZAXvl27Fu/ATEubNSTMIMtIm46AqGjxKm+jI+gOl2fF1CAAW/Q2aAU4XGCfKGxxTv1KdAl81dnhqD3awDkSTxWm28Hy9+Jc1kRPTton+p8GLtYqHPqsO/ARN++wDTG6uW7aJqJyfdeoqNxnQN2g/4EB2tll2EI4MgSf1lBS+lZkAB/VHQ1u/7sys9rK1a9TL7Sue/Vh9GI/oX/7HNXSIFukq7R95caly63WkPf2uUkQNOIIP6v/TsUYUeBalPfzRmpQkUjjfMi985aHsezFmm2v5p/QC1Bf/xffMcUfeRUciZeEg/InBhtnp0b6/jfkQdQ0W/VkXO0gtC0aOH/lZee3OW2SOTgykEPaBUKu4XwBatQhElzNaa00IZeDl+Q/D0dbhKPIG5drLpovS7FTWDxjH4gLOSGV89t29bmaXS3Gq3k33mykMMvLAjPrJ0k0QBn1dKAUYJst6hkMWAqb7l+WCUrX1TZmFO1GZmeQ6pfqYOq4OOI/PtP5tUgvaD9drJBgoOHHwLIoPxvxCXFCd6gPaYeUPN2loen099dImSAslErAzowPlS6xc3D7gtAj5GkrnB0MNTYr7pgSbgzrlwcraz6KmW9OEuZg2VYxA50048QiQmklJShPSkUq6tSp3FvUVB1kWXpOl6UaWrj3Z9hJXKR3TvhsSgUHcmoauUplZmJumt3Z0a5DMYkUX4s/Jc+GPTWGBY8QQ8o6G94yTS92SA23htjlSjLRGBGnjWWpt+HHJBF1AfI1IeY9Dzw7Gs0QZoeH0Z77+HycUObnEMHff4WeW8brJC24+EtDyfttw580FqR1oKJ8c7pQiQQTW9cfLn2/MmspKCv9Ssx5CXUhuT0RQhJ0bnQ99IunITZTANH/jDrbKfGZNzdlS3mKWBLzLC+CF57DKczdW++NWHUNUtanS/N7hFl3WioGFur4rww8pPpDN1Nri1A750WN4ChttAKwZk6fe/gktCA0OD7kt+GEtTqs4zpX65jBMo8pZfneK7rSJjamVOuE5J1MyTREx+xpQzvtqtLGpN+ayGrxvsFoPb9WX3Y//ULLucq+wS+2xPdim38HNjfx6oPNuWJ/kNAJ6wP8K73F3Ofold7pygX+V+36AnoQ/B8z18BXPnwHCo9MJ9DY305et30Zx8x5qRDPwv9wS8hQPnrf/TamT/xngoDFH+jBQHnJAb3vXojSxRQiIrkDv9ivIvRQuKkxAmOZ+GBPmrwuvCocp4KjgWWc0Af+QxlJzZstG0z7shx9L1zgk1IBesya3zN4pvJXO7MZpu8Co/xImP85j3C/plNDjI98uWBn712CFVH2A+gnbVn+sc5ttHP9uf1tHZgnr2PJ5tgRIa/Aqkpsdb/cauiuGvh/qhVjL5efKPdqC5JlkbObVqdj5YQyGxL3wzbhY1q2SBipFriVG8k8IvccRY5aHZgcOHhNn40aHRWPOGRr0pytrbvU5RcNg3/tWja79zo7ThMfdQuTPRP7j3DrU5RGHSzJj2hMHRXzIUlJdsdnR0BlqY0xCnRPPMp1nxBaYwHP6RinfRg32V0rfU/hZ2UVzRWI/eCBS9Q4cSO6ehGTt/Ukpa4dgj1TTwhz5aPVJaDvCEeJgbhU1TLvpR/6hK2UbH05lWuGRmfCxXcQHRR7pQkmoljZLE8hCqHFqbOXNLss8RAg6NiYqmdSGgwmio7NBjoLi3OpjZP5FghUfInVeZwmuh0v8EsRlLXuX1XrvfAIR4Qz0o8KmbBeN86lKwBVc3VGVjw3rVDLwLGXXv7EC4snvGFzUx6EHRh45CP3CnBYyTq49vu+d/Sv782RC7gaZgVTStuX7t/CcsOpk1JqDOLCS8B9NGsfGd9DfX/9Pljxg55NoG7dSg+SRGFKr405hkSu/+gYQdZjDZVDTWlUbEvIdIcPQumWeDgtCBqWsjZRnBbcFq9FdC2HPLTI6Ek+kv+jgTajgyMdn0Auay7713NBD8A6AobEebFIrB+ViFKJRzcmBhmcZzoF5yAOc0bR4rdYH2nxm7QQ67AE5oL8PkvgNs28C4isUMWsJxap4REflfmTwoMtB47AAdPg5U37rlJgJwGeY/bt1k+xN8Z/UYYSlg8yrtar31keZtgZNcvIWdJdmTcuPForjpmE0TIumtTMUn+ijmZbtb38r+w1tdfn+SZJQwLq9A+YJx6J9RXWV6CSOLDwuJxZu/EQcI1Gy3P//RtjXQwLx1VwUA88SXR8QcCP9bK9/lh/6nq78lz9G8Qn/9tr9v5P2bViPyRLCY/Rk0Lb3etu61AsgmIViCi1XQgHf3qC4u/P3C6L5cJfJRq28mBpXXGnVUMusw2iqTD2xSWbog+Tm30WIFBW87KozuffNTmpzKmErH0DkGGlRRyLrcT1PybCFEdl0HsFoPdzL5DXrNtPu97cEXEG48b8M4yEdENvfAyO3PBlrYt7sD/9pEZm/WeC1w4S/o6AR6QzycxNQfIr23X5DK5lFC99J5OIQEp0V2WNNOBBR67vp2YHHZOOrdcwrNKLBa1fsB2OxllUN1N9ApB1ws2apaxl4FHfwABTrCou3ltY/fQdP05cIId6EOL4lzSvOOyYgiBZFTHmN/y+Bpp2nisB/E0IYLoZwdt5h/+lkbnaHRPpXPg1tp3t/xmGAE7KM7W7xtJ5MnbTG/hJDK89Fe2whPf4DyOQpbfr8xLOi9T6RlsHTjeo71au10Q+ugFXmJhTJrsyOy8Z5tMthjcXI01TYBp5UY4wXSKJ0IuaewQP0p6wX0Sbb6hNlbkyVLSL4E13VSfDAw9+otfPBZ28G+XRVe7Pe3rCKf5qW7rM4RMJfCqNyzb1zyA9yh+Bx9itKqub+fRXo/3JU0tnGtJbBF/DzAKBkZQZ2nU0sBIqReF8qr0XMv9kOMryGIvTzcwSTsFz/Al3qHJO2zI65zxvLDE3JH8IDCrf3gZn0Wf/fxuOhHBPrXBhkT4IE7Jv+JAYbbY00fHASengHBtBa8vt1B/q3bisxvndnOdR2Ty8bU9RzrYqGl24D+QuQRkj4NYd73pnWMi3dWJ+0gOlgOP0zHKPuMMFHZU8PDpFqLKqhwrgBpb/FawGGJsfzwGdcailTmB6Te5d1GGTjvaZOH3Lg/Q372YG5jvswZnFbtiuD9CEyVa9zzktZje5Jn3zJ6IBvBg0lUidGZc3fYw4lvAXL9P4r/idMZFlk6yxdbB/RxAeYDVGSUqcokrcfuCHiVUtC/Co56bno7T8+oQ0AUNLxc7RXne7U8esbz8JGqV0I92UtPDSsDVhdXgq/0jbEpxSA+WuhYYUI0BLaFE8Etpm5n8DZEaH7fxzm/7LsyQ9hUtkgIfoyDxxaaePWi3PpmlWl1fMSkCcd79SORm7w/Rk/8caLHxvn5Le0WRofJfO+vBkzVrI9N8jol158MV12yjNCwkV8Lni/WLI6t+DvRQdX4OVUjhH+Fasclb3VxhjMM7eGsIbYXJHBfuyTKSHPphWwtyvaZ3HaQ7PPYahwdglU2wE++VsD6VQ0yWsSieIUgFrBgL0N3uL/B0o1P7BUPE3VUlo8nEae2J6g4utqKlPCvbeFBVfSWm2XSgIiucMv2U5Smcq2usexYhBo82LUW36U+iyg+jqANzcxzQDSpz361r/IIBVc7T2K7Dnm1gquy3gcH78mk7oR4B7uvJs4CHpa6JW7S5lMNerBruUcLcb+mmjMoCC7lvTyTtO0Lbt/fOSyXQOO/T2sARIja63M0xtmmrI/h7yBV9Sqbk1Z5Lu/GbCgIMEHi2YaHnwyy1XTJQaSoYDHF0N01hOCZuPfXTBJ/P9FMtxS3VBZPgA8N9sJJw2tuptV0kbATicF7uHGtwmRvkZTRWZshtb+pRqr077tbEPhe6z28nQ2ryQQJcAUBtNz6lXwHgFMg6qsmSZ4tMgLKXBOFnj8BM29Hc13OnFvkbjjn2SERKm/6lnRDC5Pelu0E3ua9Vrmatu5s7r0VBaiHv46H0doEror8O2vG63iC7zhaMEPb6gVu+4zdyDvRgG5j1vT08fklt1oHxxrsc6X3LkrB4g3ZHFlU25ZrKcQq7+N+yPgtuWZvrV9lrMEd5ntHBvrXTqKWSQLMfeRCZ1WJJmmVln406UuE2XKz1SLp9ZOjU2k2/lh0O/HmnidkEl9KHa2FJp9rV8CRNpc9pIExYYcDyBWINJzJizIvSjZMR+6vGqXVz1GB6Lv7FeXgVso6XqXwWiatM33rKBnA85lFDuN3Dpkgk126iMg/TcWd2cf4YSuxiT5Yd4knhYaUDveoZKmoB4aszCMGQapL66E484z8ruCUsXqwYGngG8J7SuG8oIqpPu6771EGNyvtElzKjN2JyD30KIyIOTh6RIunuJi1bcz+rqyHEnFTPoRMTJdvO9hum4NI3piKk9uO2sSGB9xnhYdKoM755OB+I/WDsDIFkZy1vU5bWIO4kJqcrEgylg5jEXWpVmKyYU5Gete9qIakH+QoDVHmru9Wu3T+S+hmMLS4zTP2ycKuj3sxc60Cpz8tUTiNdIPa1XIXhS7nltGBuMMN1YXrCQDDpe7OQKt1BmWj1KSg+Kz0UEvyRbn1Bml1euhRN0XZ9l3hwj7GWMwVy4lRnysZOLgQA8pc0DT5h+Wn9eKTDGXNWKYQ2tmXmEUp8szPt2zLNJ06kEt3Uvy2gvLg3bRK1YjsC3tqOlwkue79ctQqCcySxOHveDu86yCnzZVsbGK4ABiz502Yj/UOboCa7y+nbU1pxLVrmzuLNnDbvefVs3SsJMBssWqJEzFN2zabdQyDt3yzDzDL23OMOt+mzeXlQeBi6uzuLY1+4Rzi6C8ZqIbogXF7RbmRdj81gj2qy6AkabPKL86n3Sa/jekWQeYhmyJ6oIAIYBX5by+ONkR1TUrrlArvaxQSBSxPTPYWlLJkONPkT25hkrlJsO4xqkbXmPmxUs/sm1EiHApWLckfA5IM78sJ9t+IbQp5n8siYbZyUP7tmVPvGkcKcnFZvWDlKmX/E0bHmM7v09qoNvc3WguO91386rRgJHX3DXFbmiKp+Ut0BJF1KfiJApMlF4I8kJn0SO2x2nrp1j+MSdLH4YEkNwQT6hTwZDCFhwBEc0XsKNVhsTvvcxOXT2kmDjurl/M4qGleqex3WNhBPnxvhhzKB6dW6zW/RTwaRUCA5zL9z6Ku7BBLBEAwDcvE8M9kQNJNYBMGirB/KOc6Zy76P8avElHqPOH8ZA5AdmHXXfsHNyROLc7U/bF/lt9hRA67s63lqa0cMIX2RGgwIZfQAESln78ekMHjog+r6IbOrD+Lh6ro6ZnA68/XQFiXwy9UPNlnyaGnP+qtqGQtTckaNXn3AjXo9u96E7RF+DZS333V/CuaSS0AHLlR4ZKlPNgN4sf8cEYYceaYPR3Hmpy2E+NeIvRxsKvwEsky/aB2oz4+J8gdvKRfOzHoT5ERTmEnAYDFu3HQEj+oW/NmyQ4cJGc7/jt2BFP8//TBi4koKt9OuF7kHKaB0J7mok8x9Zs96hsoDl783cE5dv2no34IIcEXqoUImQim/TuOlMVaymZU7rVgi75eMGvRn8OLhXi6k9kkZHV82BogHe6MHglhihCYW0K2q379zH7Qq3Yz730mWZDQO2PDwuaOazOZmiaA3F0C3TRMFByjcgbUCxieNgWX6II7pxtUvbCV7mNitL/76gE6pAp+NcQu9nz9kugAhCjJc/putepiD3X0DpJgAW9byG6q83Hh9JmGrFcVRR+Opg3TIxOm3ynR7nInv8nuV7CekNGoz+gYLK/k17cOsw+oimSMuHVweyGQN6f7dyleX4w/TWTUadF8r5Ns3avdIhuDgJJgMeJdymK90W10rt9vzFS2e+VrORC1a8QmsDrJ3o5rgCsDub4hh9e2KX6yKgPTufun+plq+ulL9I12CEZn1m3rBLPllfi7YNyF11h7EII6nDwOQD076oqOca8eZRKWO721OTj/FXRFR/USxmmBQmny+3eTUXbDifq4mYR7L/VFjZhR/j4nLCmYGl8nXXGuemBkJl6yzY9IB5s65B4Z0fya8aKU8/UnuHR9qL2TXfwrG42R3Bafxy0KFn1YMvPsk6HozyIR13QJmm3/0FIlTMXRsunuhpgDpLKws523S4g3c3i/rgyNlyWrisuopNFVQcPN0lmQPJOKtIsAXTo6anyzTXNCp9pZIK3z6TVi7Bk94e7p3zBweOjowC2TdeFowJbrhY20vxh3QA4Xkfcs8E0UB3pWYIHgOz+Qkx229KAQkomsLOmhQlzOii//P8COWj4O5oeJ/P4g6mRIvBzeP6us0jD/ltEWOQ4/rwtc92GDXJPAOOjuNN/WH6ImtJEmUiIEMDnP1DL45FFx/7mf6WhY0kW9ToytteIAbBVkPHyLQ6ciR5bdYdZDBb6d3HnyH2VuOqxy+wnyYFqTwstRO3MZPa5PENADLejUYJwVH1IOd/g9DWx4W4gT2gopP5tUGrFP15D1v6nTncwM2l4nmQ/DrgB69KkTnv7fSeDcMHiRMuUR8C7D9v+DvWYgjaOF9oYKPrfuqC/T5bt0HjmND0q5qZKeyTe80oJrx9Lt1bb2mrwZN1AVkA50pVMf/TN3JZKuzMHmfFd/HbZH/GaGPgfKC46PIJCznv179aDhbej+Q0WHnSzJns7lXJVPeByJ4ANGa80fQUHXYO7ef0GwRV3umLJkDGzgEqV69goQFS1H65uN/mMJw6vHu1FvKo7mmPmMos7BeuHoh+OTyR0CUTEhbasqss1ubiLE1Z6MXiVq6PsrCTsqbtZQmUcq70XRvX7aeaWDT4JmXwFJXK5ab3w65fnYSR05hLfvbU54+CeToTiOIlw5SSxjxj+cPlHAwN/MzHLT1i8zeXSqz0tJ/Fh4jlZ96iesSIx5oYVpiYWUZHH8/pAvEN737C7K19zWHJsY1xlfu5w/332nPTJG4kdvDCHQrLAH53App/L4ij+ZEkeqQ2gXPymwmfXfrYoRdPL+EXBgHfhpTXi6Es6URVJ17XJaNs6vaU4i7lrQUnflDHFiVObPOwjN0nh6grUX6M4krL8AMPbs4n07LMFwFXsz+OreN1eyKo0h6rJW0HsJibZEmVv8X3NCD8ECe8bn87oA1WsaOwH9rHo/PWl/sIaKCieTNxC6VBEPkNoj4tLlPqZtaNyJkMDpQnBs6h0ZT4xhYfxbYuD6aSgwDJfBltToLVJbrWHBCrY44fbsv4XiFEgt2oYDtL6bdeBDEnPERPTvdS2Ps5Shp1wRTrRlOr2IbOn1qszdR/6rpf9i07K2fGd851YDdnN0H+jv2qBCicsC6cSN3HAJtqfdCgm6biZEN4mBDBHe13MSTsDJqcoYu+IOXV1G38W/OvrY63fBh8RE+jy8pGkgJElY7ZWlrInpqLV8C6QHVXzjwDFG0Z58erZk2aSb9DH3mIxcJV5YZ8R0hHEdUp19Ufp0RWnzd6GhqQ+hXjZqlVafD9hL7Sfg9eCA=
*/