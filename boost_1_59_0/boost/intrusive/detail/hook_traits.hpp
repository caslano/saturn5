/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_HOOK_TRAITS_HPP
#define BOOST_INTRUSIVE_DETAIL_HOOK_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/parent_from_member.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/intrusive/detail/node_holder.hpp>

namespace boost {
namespace intrusive {

template<class T, class NodePtr, class Tag, unsigned int Type>
struct bhtraits_base
{
   public:
   typedef NodePtr                                                   node_ptr;
   typedef typename pointer_traits<node_ptr>::element_type           node;
   typedef node_holder<node, Tag, Type>                              node_holder_type;
   typedef T                                                         value_type;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const node>::type                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<T>::type                               pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const T>::type                         const_pointer;
   //typedef typename pointer_traits<pointer>::reference               reference;
   //typedef typename pointer_traits<const_pointer>::reference         const_reference;
   typedef T &                                                       reference;
   typedef const T &                                                 const_reference;
   typedef node_holder_type &                                        node_holder_reference;
   typedef const node_holder_type &                                  const_node_holder_reference;
   typedef node&                                                     node_reference;
   typedef const node &                                              const_node_reference;

   BOOST_INTRUSIVE_FORCEINLINE static pointer to_value_ptr(node_ptr n)
   {
      pointer p = pointer_traits<pointer>::pointer_to
         (static_cast<reference>(static_cast<node_holder_reference>(*n)));
      BOOST_ASSERT(!!p);
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_pointer to_value_ptr(const_node_ptr n)
   {
      const_pointer p = pointer_traits<const_pointer>::pointer_to
         (static_cast<const_reference>(static_cast<const_node_holder_reference>(*n)));
      BOOST_ASSERT(!!p);
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr to_node_ptr(reference value)
   {
      node_ptr p = pointer_traits<node_ptr>::pointer_to
         (static_cast<node_reference>(static_cast<node_holder_reference>(value)));
      BOOST_ASSERT(!!p);
      return p;
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr(const_reference value)
   {
      const_node_ptr p = pointer_traits<const_node_ptr>::pointer_to
         (static_cast<const_node_reference>(static_cast<const_node_holder_reference>(value)));
      BOOST_ASSERT(!!p);
      return p;
   }
};

template<class T, class NodeTraits, link_mode_type LinkMode, class Tag, unsigned int Type>
struct bhtraits
   : public bhtraits_base<T, typename NodeTraits::node_ptr, Tag, Type>
{
   static const link_mode_type link_mode = LinkMode;
   typedef NodeTraits node_traits;
};


template<class T, class Hook, Hook T::* P>
struct mhtraits
{
   public:
   typedef Hook                                                      hook_type;
   typedef typename hook_type::hooktags::node_traits                 node_traits;
   typedef typename node_traits::node                                node;
   typedef T                                                         value_type;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<T>::type                               pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const T>::type                         const_pointer;
   typedef T &                                                       reference;
   typedef const T &                                                 const_reference;
   typedef node&                                                     node_reference;
   typedef const node &                                              const_node_reference;
   typedef hook_type&                                                hook_reference;
   typedef const hook_type &                                         const_hook_reference;

   static const link_mode_type link_mode = Hook::hooktags::link_mode;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr to_node_ptr(reference value)
   {
      return pointer_traits<node_ptr>::pointer_to
         (static_cast<node_reference>(static_cast<hook_reference>(value.*P)));
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr(const_reference value)
   {
      return pointer_traits<const_node_ptr>::pointer_to
         (static_cast<const_node_reference>(static_cast<const_hook_reference>(value.*P)));
   }

   BOOST_INTRUSIVE_FORCEINLINE static pointer to_value_ptr(node_ptr n)
   {
      return pointer_traits<pointer>::pointer_to
         (*detail::parent_from_member<T, Hook>
            (static_cast<Hook*>(boost::movelib::to_raw_pointer(n)), P));
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_pointer to_value_ptr(const_node_ptr n)
   {
      return pointer_traits<const_pointer>::pointer_to
         (*detail::parent_from_member<T, Hook>
            (static_cast<const Hook*>(boost::movelib::to_raw_pointer(n)), P));
   }
};


template<class Functor>
struct fhtraits
{
   public:
   typedef typename Functor::hook_type                               hook_type;
   typedef typename Functor::hook_ptr                                hook_ptr;
   typedef typename Functor::const_hook_ptr                          const_hook_ptr;
   typedef typename hook_type::hooktags::node_traits                 node_traits;
   typedef typename node_traits::node                                node;
   typedef typename Functor::value_type                              value_type;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<value_type>::type                      pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const value_type>::type                const_pointer;
   typedef value_type &                                              reference;
   typedef const value_type &                                        const_reference;
   static const link_mode_type link_mode = hook_type::hooktags::link_mode;

   static node_ptr to_node_ptr(reference value)
   {  return static_cast<node*>(boost::movelib::to_raw_pointer(Functor::to_hook_ptr(value)));  }

   static const_node_ptr to_node_ptr(const_reference value)
   {  return static_cast<const node*>(boost::movelib::to_raw_pointer(Functor::to_hook_ptr(value)));  }

   static pointer to_value_ptr(node_ptr n)
   {  return Functor::to_value_ptr(to_hook_ptr(n));  }

   static const_pointer to_value_ptr(const_node_ptr n)
   {  return Functor::to_value_ptr(to_hook_ptr(n));  }

   private:
   static hook_ptr to_hook_ptr(node_ptr n)
   {  return hook_ptr(&*static_cast<hook_type*>(&*n));  }

   static const_hook_ptr to_hook_ptr(const_node_ptr n)
   {  return const_hook_ptr(&*static_cast<const hook_type*>(&*n));  }
};


} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_HOOK_TRAITS_HPP

/* hook_traits.hpp
UKBbUL94WETX680Z9kmaQB1yw37dOXwdYZPeCW6cKB65PRCnpGxN8bpOtNqBWjFZND7U8zg2cNYQ5afHu9L+g55zFHBbCj/wnM3yZqaxhtYlLQw42zLfYkA/6j7CCIWWXFtVOA4XvPhuM5LCnprQTy2Ci0IB5I8CyEIwD8XO4anmgZ3nxU/cX9TKHctKQKQpNtOjgBXaTjog12YtR8OnZewKGGBn6Cq6WfNJDSfu9yiIMoYE120RUGXzgd5f/gSiu1mTY9S0XBNrvu3hWz1+iB7zCU1ukaqk/PcuXph8v44Gqq4GDb0zxFjERQz+dxxjajFCUf23AjIFdNWCBAG8ZAHoSWdEFA4VEvjSAOC4PsCBDDqejowQztvCikiwyl970deoF5MCcoAoqOCWwze8vv1wubu1eC+qRTx++HZwd7YEmj/QsRLiR3m3wzd57liCAAMiI9LTU1IgtlHZ/+V5vrjjgZVsOZCfXu4M7PwhAPMXxNEtc7sb/FAHrx4BAOXz4ZqPXb/5zpuf+bl0fNuubTr+qOhpVc671tWYKuXr7RLRzVIxyUnhqUK5oNvw0PpLvSsAKoXQrxGu6AEh7PM4BQmhDtEAQOz6g3dFtfU3F1azyYd3L43WLWBgD0aYOMM0Xj7SQD+5GmCQWTBzZdEB8gGQCoGwSabMXjxs805c3u+Cab9bdTm/Tgk/mulTBdSitb1qjxsl5j23ZJxS9T089GxFADpcqin5Eh4AALDvf72HUe3p/XrT2MIyoWAQKigIGOSBUq8lM0a+AkE6DlpOmAk80s34/5RNOWgO5MG2pmxgivYKILsSkvSgJlK42nf+LKxqHLw65+5AuVoAwN9Yy9kJ5yqq76xC+KovjaLGBrzd/M62f4CBdgqpbxaesD3oB6OdMh+1IFWwsoGkNe14dEYQ8FlK7a1XH9+MKvbVc2W6XshLZosP1jFuyvZRXRHk5EWyEZTZJcq4P41B5rNVH2RqEnHZP6uNmbcvw+J0BvEje0U8FAHlre8PHwCCbS1oAkUGPNgrR7TYVffm9zJXMjEFKISaBhsKBj3F1XZjXW1X7uFeFw97a09fSUr13omOVsFvkXbBQ43N2nqrBLnFrmsX0T2+by9bULh9OFFRK6sEyCKaziPV1F5zUK1TaXP0Qq8hG9vIeqQOHV46g8Ma3e9KB0SLE4UbQSZKtjBKP6EGIMUZagXS2PYDom/WQlodRhGWiellCVV8eZ2Gcka/1+UUBCcaPDAZlTSy5grpwETicDcRDMkz69xD5HnKkVoQ+8rmGY79NqUGTiqAp2L3EOKzPCe2uVXRPYKiyBHCYvrL5kz2B7dZo2yf479DL/87KxQq1bI1DUhUp4JZgIWGhkZcjdVX3P42ZEcBDmNrlCi00J30nW9KZzklRGJWh8JYNTGGSWeCOZRpRTO9EEXljrc9kN1xM+vkqMqmPb5EZVXLSg2LbM3xWWaHVHVHDjimNVUqNc4Mj2aj+qagtqm/Z8WxQ8KVlJ4H1lipsSyUCredlK2z1LqlIuWu+kSqF2TDxsyljocLvrD1Ko7GqyE1ObWeQSV8RS+rbAauseK4KIcWW4x2PtZEowJiMdZyakzEH2oCwogwFJB7Nw2ABdqiuR/Idru/eXCo/+xyZoIhbcIOfdbkbzAdM/kKVgNYitkjYTw1ImhhzbjSqFfXnAwHwtwpuCM907aruV1Z5O0aKCd+PpCeATnGDN7EeahWf+Fqcs3UvsCM3s18yWXsfIEK6DhAOACQAO5/Rbg0c0gwCgA0RCvBKb8eYJvpw8rhqtgIIPv0VMKDoItplxxoeqJ7ljC7pRZq7ni7O/MBd7JRTUqKBkrwTFPlCdiiyatLRUockdGAtB60wsRsAwPapGkP5vGBNihUGl9mFTqi8Z5Yg4pW2QEM+s/Kyp/ze3Qqvvsn0rTDoMm2R0qFM2vmLvUUYHIXFl/elNCzybVRwwEth2r1lw9Obpfp6myTkdpB1+b6OmzIAhoH2KVNIW+E9lJm9cpUqfqeAjKPEhKjYsYFICWMZBDorb1rKk1gQRzQgJtFp9mc0AVNnk5cGxaAsYAK7gWWV8Sssvo/Th/Cz0SqhfdWwlWD8jJr4v7uVffvaXXHK5zXHqnnK+i9TzhWb45FttfNYmqfSAuWjLZS0oVIqp6djTfQEWpuafuTOW7OSVLRnQm8CFJLDkEqd5ggDNqBTRPXug/degtrvxWl/H8NZFHtAZMeCiWFbJtXq2kcaWehDTJy3m55TCCDyJQu7I/SafvIvWD80W9LaL+rI2BZXU0hAHpe77fDpJQ1j6G+pBQLDbtzPogpDQZf49NE0B2lWlMsTnHcPulUAGR3gGaTj0XqkOmdK6Hn9cWS5B3jgFJQwJW6E38cQtgnVQ1pUOaVCbHKJalMdIHu1B+QrYjZqBp1kEwfkc1DNOyNQY1yhXG1wGJyZ2x77WkDXc6DcXSRyFCWBxQY8vljcaCBbeTFLWzd0YM3ObyTSjWojyytPLjhDn0bExkLFi2Kf9pmrvniYpiCOj7tHTbvdEIXkU+vbwQNJXvuZ5w1FJtBCVyNOA4Irxo4OkPB/0RoWoNSRJB+UGXssh9DvZDT9lFKny6k+Cp/FpvG2hFGmGdPxj3CJNebY81p/mtYmaDvOmcHUkgBdIFv2Yoc1UovuAsfIvU7riwHmFB7Ez3MGttxm79nVheaKlJQJQghPv/o1Jhwy7H6Y+o5sFl90d23ZkAJijQGUq7NTPxoy6wwR0TcLMTNAPUPAdTeGTpxwCMLf+xMDakRk/bO/7/S0Rs9LAS1OcHKNFxHGGhRBaAbPpsdOvRtNkdvUa/EnxG7vaDHMqrpans0sex6XV29GSONU2Dc1myuGV2c4Q2fMltVy8pSwPquzey47n0vgVmIhPBiVnQQ3UkEpnsXk8lWsqxLXl6xyZJDduOIrobVb5RmUOpwO3cnzDNhkX+eiNKvyt2Ca9V46yLL5Aytia6zdlk+Pt6Y4qLUk+JQWLXWJtKZRqL1l1NKJz+EDvQ0sfDDjWOuMsIRFRccVCQqqivZbdmCSe8zBloUQMLWmeK0A1zi9tZdY0aTsM4LWr1JVeNMZLvZwA6LgZscyRQOI/q+I9SpjKKKeXImblZTRh37aDo3L+CyIiQ42i1jJieSl9LmY1af5qN+a+l4b1OJj53oGw0tk8ldbyXOqDnGpUvoIcgVpCrzvCYCAQDUpvlQ4fK/8ttTizIsGIU+402IqER1CAktg1Y/xEkeKvwxdvNSdfPIyyRke5i9uX/HBnmb3irSswSdcXK3XUZn80+fanQ6dWqkt/8fnCzPkBQRyHMitE7QaBZa7Jujj235cJtuk8OZhPtT5YtG1uxoZlF8J0+cr4YAYE2LW+aD7sndtD9g4wlXeH2pM2vGqbyr6VnLA6HNToVOMr+mHT3ScHLzd5V1IgzvQWF8SIMC8bfu/R6IyXZ0Fnor1NGa5Efs4ng6osaBRIMjTyUIMbo0C8KZPyTEwjf5E9gyRQaevgbo8/DNanzBEG8RlycnLC+4HGHo7j0+uBJWn7dEVbVaxqN6bLDmWXuvULeAnM2z6uRx/EbBNo1JvLMlv3diqhWBmlUZ6gikae2YoUQVuV4rskQd93DoiwRcviPQaiBAplRh/awnAADAz/96aKLaC6J6hMtsSPIkmSjSfvuCaGdD5vcXal6FhMoUA9Us6bNhmBgnc2BZnzzc+87/s1iCRqS+JZ49mZmeaV12EL5XJquNaJRbzjoc9sdpka5TpukO4DBpHFB+eGvHmGZz7n6zrXxzachJvSkRHuNVbv0DDeAaO3rnJZkf86NMxfzyPQfNVj/UgYqd3Xe29Bk8GjkGEiK9iHQzkRKe7xLC/9xD8lzl3wBJgTFYJKycEj593iUGf4w6enwraCBW9AMireuZFYX+MxU9BokdVsMJgbd2Q9bTi1LYIikEg/kUJvVcm5F9L0f8irj7AQo+13LrgSRC+R0mN7uXVuVPSIUSUxoGo5A/4g+CSstYXgWhDWBuqHlx9bbtNI1knShxedcJgCcpe+b14L6tGIc6ZXiP7+g2YHZnFjcCADQ2JqLmDu4En3wiUYd6hT1DTPK+5YJUa0ylTRQsqwyE5ijq0Gi00I5pxhKZ/xcFkUWKvggUAeDBdit6NNryLPmsPm+wC6AOrBmdpisuCws9hYhddKykW9E4IbJ97XCLamiT55VoDnKATTbe9Q4t5bpKhvjAJJxQDWuBK/t1JTkZYCl9lDGApkhQ1dXmMBOiHoDl8nFvYe/M1WIxbLK8BsC+9t8BBFl7hmqy4y7dFsTBTvBfiGqbXKTj8el5m1y7dRED5Nx3eoVGSS6LT9Be9tnX4g4ETwaMH6yNyGoterqUaEaC6xUHQvDMf+OcAydMqrhsFNGOJc1oIUmi1ScQagBgigCAkwAASKaCmSCEMrh9VVgpFO8ifWlrjZcc4/LSge/Ni1EOXHN9vm4C6I3YjrKO0h0ziYUFrDrVdahJNW6HmvkBC0E4NYBXRxMCyy2N9Kx/dNPpEyoinuZ4pwsvu40GzVCN4je1FponQf5qMATuZ9KRBHTO28Q/xkDefiHt9nf0WN70hN1cEXIlnzN9MwTbNb9cT6QGI/U3DZGv9cc9+mX1nRrESclRMV/UxTMuAeEIBJSpdGAWyffhy5vjMT7GvWABfRynU6HpEunhvwTSfDVrLD+HTCucFZU3rLfgmyWH4WKoqfxtvhnjnBcReKIIIUckCvfjVAO0Wyazb8H14ROxZhLoVtkPA+PpoMLkW/WtjZPJHQ6O97namxcD2wNjwN7xWnfgG0+louHI/k47DomW/fSMHnDF+MvRoP4ZDSsPomqbOt7xfQGTv/r570yI8dCooqkfxSXaHk1IzAe2VfJfXVsyrtkhpbJ9t1FWoe3r+Ns945YZ21sQiMdW29ByFI7nWF1oz9sF9UFmS4ULznb2EmT09nCPhUp8MkMY/9eCussfUbg58IpcfFNBQKUZg9uvcWqGOVn9PwHQcmpPS5G6icmg4ud6vgp1MBaoqKoZM2MMM9VPdENjwPI4qD3tGDKZxHuVjFoct56JkoZg2BS49P3STT9dG8CuW6HisFyWMXs1mR/bmLrW+XPeZLSVRI/cP8wUhPtry2WOcmGX99fe228HRwG5APwq183O78K5b/W8Z9reI5aa5eJs/ViD6VNc2dAQZhlM5trDWqNhtRPLbx1Ok1PjQckAR/k+f2FMWkMeskNkhW84dVsQI097iJwGQJZdyuBQjzsL2wX+HjQBZCi2u3NN6e7ekd1hAuCiSa36NpcgmaIpL8nnLCo8yFpfodmMk+bXHmNAZ3jcQSmIkxmqW9GxHb/2U1AotF843r/nD/yxm1dwE7SUyjDvtuYVtjXO2u9Xc7YvU5rxImxv3nQziKR845WwfwKpx0QDSN04jTxCS8xaEWXmgAMvHYHvPjFIQtFc4d52q6vnkow9B1T+biFgxXTZjOCtyPwhGKgQm1h94XV1JxHHtbPIIZrTTk9MfBsZsDAQuUpZilwi6vr5XBGDmVYsxODN0OEUF9xBvLYYaxFSuzJKObkt4YMX+pPKjjxHJw1Yvj4z1sHgX6qfr6P9SAZJnH7iENQJz2YhJ6L+7loEWnkYKoj/E2oq0jDZRXL/ugmAssvP2hL7M+wOqRcqFtP3z86pf4bnS2osl9LRHWo92veQ2wMa5645PoMc5jxgQzO0LOI8oFw7olkro/7AHHBFA8kyPw6CiG4HM9fi9psWyCN/8DrFCc8Kpmaw5G9gqk0+Ca2x+rF4sKFe+qR1kMwZ1N4DpSj6GKpr4B9npxQ76qyOoSD/+fPwVIBc0NQNC3cJskMM3T67CacVo2XXDdgbs1bVSHFDk9CK1f0r2sIEYAiduA3ML4MhxtKlq/s9iqwlZ32v0MQSVaVDdSyKVP5Y2vnPFQh7Q001xWDNi8v4/oyvr1VNX+aQfr1hpizkZsSwhGH1M+I2eW/GfogwsFf9bn5M/cVQkmnB5otpQKoxkgCCWHyuqEo9EN4cpUN0tFGsScLmfKMMvMQKJuRdIJIULiZTJK2wYdq/lYUv+xaW5Gfuc7hznzpUh4tZUG01+J3SSEOZ7ed7e5xitSEoTWFYCkhsHzrCYmLntsyPCTlFLcZlMTzkQXVOTrg9raypZ5Rv6Zsyfyd2vIGHsmxLj9wle4nZ+Cmzt8bYrGftrR4Bn2p/WjtWYyGw2fGYOEKOeviLeLah0djzggQ7jIiQ9vZm5Q6Ix/FtmDSvCqkKWDMZaSLQ8HtyXCMrUVynC0ZRn8j5gmcfLTxYfN5xcFr8CLTq+/6By4gEBm8i1HFg9Tnv4Oo64jvB1L01dHCb4NeEZ6kNcO+oEAMDZWSk7vrHFtk9K3IvnWoiM9ukMpg+QI2YIIM9erGhzGOf00bWOEUanAUoKE0c5Q+9BsnIh8NXH+YiVx61lPTkWpCuh2KrX+SV4y/yhpsGhGujjylK8rKqCdDAdwlmnzfK7G2ETvw8cXUQQUqv7vwU2105NSDRl7EIynWJZZG9ncdhExWGYFvJJ8reqbS2eCl0jQz5vK9f968zq+0Sf+RiQ9xAN2fxaRYok0ypZ4BtBNbPMltc/YNG0pPsAHi8bzBLoqcKHlRjD8mlo0mGH0ekeNnxesuP8vbi7vXfnB17PbupC0EaLUmzwVLFpxe72nbjbKJSronhOgYz/lgsE+9Lyo3ZVXX9OKBFpjyLHH8tDePiBaVN7jZRvAxoS+aeXYl0D1FbUPdFUTmPXTwsrUv1h0fxFzx+FYbTAIb7aBHXVBz5wxdAQbkzMvnocOILjsn53jU+ecTdGiRIQdysjV4CuFA0I6rHHE/dPjJYtt014viVPj1zjKiKkVMfonjWZH+hy27wqeOOJD3a4q35NS1KaElGA8FLp1Q07Kvh1Ecrb/F4ZzlW6B5L8VAIn8N/b2bNnjKcdcV7eJDpK67C8odaJR3+lm8SkUYoRKf11bKQnads0ia0t6PT/7OTV2RIrFOs9A5Z/V3V9AXLhTjDvXwdCyDdwmeddDGJJEvfhyqIdXo05z0UQjIaYBbSYenN1w6LPvkgADGVCL3T6bPgispMnji239Oz4Z5mFu8Nin9giOGtN2XHZoOsTb7Uss3OuZ+wdBtBL36pMAGsNKYVME8uH57EOwRQaZnmXPymldHnRcl05hWI97yNJQF8ZFqCBnRy0lDQxf9eM7YT6KiLtaEwvPNEQzUc+kpoWVBEqACVfIOb30lj8iVWhu4cUYc0FLhpT44hYnX/fPJYXQYwC+R64wW729MbLl7JaDRK9XHdVVPwskcE0PyJ+EhjynT93rEILGLUyIhiIzVyH/KZyy2fNBooBbFdONYB+EAwHLHViosIZliHjkPVIW7E/kcDuGUfo1gxdTsLHf1OYa4H0PtjRt6NQa90XcBg4kkSTipyexLH7Vu5cQKI1/90VrjnfFmX/3NcLqFr9ABIE5/nPd7/FmDW+Qlz841MFkkMdnuH3x3hIXKevmM9NbDzk5OIEFk/1PyB0mJsItaxEJcAo3NjENdPwcFVVzO/hbOLnzI0VLO3TskYFk4LlD3dLmlugYTtimt7ZjYJPhuE/JMSMtDvmn5CZVe6l0HM7qYZzM7NBYe989xmuUb+rj24
*/