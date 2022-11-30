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

#ifndef BOOST_INTRUSIVE_DETAIL_KEY_NODEPTR_COMP_HPP
#define BOOST_INTRUSIVE_DETAIL_KEY_NODEPTR_COMP_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/intrusive/detail/tree_value_compare.hpp>


namespace boost {
namespace intrusive {
namespace detail {

template < class KeyTypeKeyCompare
         , class ValueTraits
         , class KeyOfValue
         >
struct key_nodeptr_comp_types
{
   typedef ValueTraits                                   value_traits;
   typedef typename value_traits::value_type             value_type;
   typedef typename value_traits::node_ptr               node_ptr;
   typedef typename value_traits::const_node_ptr         const_node_ptr;
   typedef typename detail::if_c
            < detail::is_same<KeyOfValue, void>::value
            , detail::identity<value_type>
            , KeyOfValue
            >::type                                      key_of_value;
   typedef tree_value_compare
      <typename ValueTraits::pointer, KeyTypeKeyCompare, key_of_value>      base_t;
};

//This function object transforms a key comparison type to
//a function that can compare nodes or nodes with nodes or keys.
template < class KeyTypeKeyCompare
         , class ValueTraits
         , class KeyOfValue = void
         >
struct key_nodeptr_comp
   //Use public inheritance to avoid MSVC bugs with closures
   :  public key_nodeptr_comp_types<KeyTypeKeyCompare, ValueTraits, KeyOfValue>::base_t
{
private:
   struct sfinae_type;

public:
   typedef key_nodeptr_comp_types<KeyTypeKeyCompare, ValueTraits, KeyOfValue> types_t;
   typedef typename types_t::value_traits          value_traits;
   typedef typename types_t::value_type            value_type;
   typedef typename types_t::node_ptr              node_ptr;
   typedef typename types_t::const_node_ptr        const_node_ptr;
   typedef typename types_t::base_t                base_t;
   typedef typename types_t::key_of_value          key_of_value;

   template <class P1>
   struct is_same_or_nodeptr_convertible
   {
      static const bool same_type = is_same<P1,const_node_ptr>::value || is_same<P1,node_ptr>::value;
      static const bool value = same_type || is_convertible<P1, const_node_ptr>::value;
   };

   BOOST_INTRUSIVE_FORCEINLINE base_t base() const
   {  return static_cast<const base_t&>(*this); }

   BOOST_INTRUSIVE_FORCEINLINE key_nodeptr_comp(KeyTypeKeyCompare kcomp, const ValueTraits *traits)
      :  base_t(kcomp), traits_(traits)
   {}

   //pred(pnode)
   template<class T1>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()(const T1 &t1, typename enable_if_c< is_same_or_nodeptr_convertible<T1>::value, sfinae_type* >::type = 0) const
   {  return base().get()(key_of_value()(*traits_->to_value_ptr(t1)));  }

   //operator() 2 arg
   //pred(pnode, pnode)
   template<class T1, class T2>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()
      (const T1 &t1, const T2 &t2, typename enable_if_c< is_same_or_nodeptr_convertible<T1>::value && is_same_or_nodeptr_convertible<T2>::value, sfinae_type* >::type = 0) const
   {  return base()(*traits_->to_value_ptr(t1), *traits_->to_value_ptr(t2));  }

   //pred(pnode, key)
   template<class T1, class T2>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()
      (const T1 &t1, const T2 &t2, typename enable_if_c< is_same_or_nodeptr_convertible<T1>::value && !is_same_or_nodeptr_convertible<T2>::value, sfinae_type* >::type = 0) const
   {  return base()(*traits_->to_value_ptr(t1), t2);  }

   //pred(key, pnode)
   template<class T1, class T2>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()
      (const T1 &t1, const T2 &t2, typename enable_if_c< !is_same_or_nodeptr_convertible<T1>::value && is_same_or_nodeptr_convertible<T2>::value, sfinae_type* >::type = 0) const
   {  return base()(t1, *traits_->to_value_ptr(t2));  }

   //pred(key, key)
   template<class T1, class T2>
   BOOST_INTRUSIVE_FORCEINLINE bool operator()
      (const T1 &t1, const T2 &t2, typename enable_if_c< !is_same_or_nodeptr_convertible<T1>::value && !is_same_or_nodeptr_convertible<T2>::value, sfinae_type* >::type = 0) const
   {  return base()(t1, t2);  }

   const ValueTraits *const traits_;
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_KEY_NODEPTR_COMP_HPP

/* key_nodeptr_comp.hpp
gIm4Qq8ArJc9xnPGONMMtoB3O30MgRERe511iVM375ESIfMOcM70ChKH6Ugqmb0TWVSjYHCNQ2BkyfaNDXt/jejd9sgcSuL0vJ3XeUWLNGjnIK6KpWp3oTd7aMRETAz9E3IgXLzjZCliP93bZUN2xsP1f/XMp9i9SHUvBHecW4FqfwtSa3igHM4w3itbcb/tfFiBky9jMu8rPrz2DHPJqfm9LyaJDNLwLeblPpXvhu15fEvdwCFM2UXapMhgK1EQiwVtmUBXySBLtWg7aSxPA1DSrSx7kBUjpXJ6UyjmufJmUYjCuc8lb7OefoaVa1S6fEZrXK+yTVaZhc8z7iHbVMG5+e+LnSjnVJYBGNyqgz0CO6WcVci628ymCAObTTH4u/tG//ASYbycofSdHuUk8ioGdhCU4JgKOXTyyUhNRZFJEtQiWpREbBiZekB+LE1PG7lSreyq4UBFgiJZTZk3yCeMPkCJaoyZg11AIRTEyQaLH7ZlFr6wpfP2IKcYPyLmcWMNEIymkFgrSUWCttBYKOCQNGs6aPBFnDsLRf2V8U6wgKkdPNt8LUCPFwOhFzAZTNTkmxN2+Z+4BR0h57TTI+tWt58se95U376RWmkAjZevf+LdO33wyR70nO9HfnFjm1dof47bqu53Xst5qap+rIzGRcriUYCEu9Vo5N42QJykHW+aWGCsSS3vwi1GFBwqEDUamEl5VbLjVeEt9TCFU/mhtzR+IUzZR9qqyFAbVRkhEgrjQUCrLARI1F7ckaSPBdWJ6UfAAmRvGcoF7myEbsDMEM4CJJcFyqfjF1NHZu0vF9VqrZ48w51St3jkwaI3J8+k2VayqM+rSFs3koQEJ+NaZ7rp4MQu62aqxXjTpG++N1V8WyR4LQlDLStgIyanQlSOtcHj3E7XI+eKl+7UucOCSMgH1MOMbvQ/oCZxYoF0+aAqzMLbBpT44kMKarqcdPVJvZdpdQil0ZGZBXGEQ0MX6Q23rP9QYpJ6Y61dLCdjlb9EusxsLJGRbxwWpI92r21mo41ARTQapfp5nA7vjOaWYuFiTZJRISGjGAoY8AoaQKaW4fbiLWcc0BfHgAJJW+0iCRtVJruPGu6ZH3lsz20LoJjlnKviRQxuVDnCjAzPP035xW6FoBx16i9LxsI+tJoDMGKf0usscxQADoLDH2uYbwHZfw9zjEqWKme814yC+75whb8AAAEwAZ4KNaZFW6+89IGC7xNKayEs+hxnX3T9Llh6giYZWFPTu6vw9j1Ll+dgL4IjqI/r5Of+tczRegIECRTxMNPkx/lYLhGIEnKGT+KtMGcNg32cTvSvwvRwi3Vfv2KUypv8XfyinXPlGPJIqcMm+8UgYhIT0fNvoxg4DKQoTgGwhdLvcAsR6esve2Ld50eemLDJqTqm0M3I5cIjuPguZ42EdfzN4HlYGF1hptId2yNforjW7BKTrhwiF4wbDPof737eLf2P5nv7PTioOkW0qZLA/YmLPIGDdARm7UDkKf7pjCO8psZN84+1AoYAMBfTdTd4XSaMGjSBEb7af0CYvF44Z6ywmqLHmI8QO5l+OV69KfEVnXpqMOAbYDPqQ0l6goiqDf1FR/ZuzjZVdyKXSursdCF6FJ2mkwZjIIUAAOZwpC6q6uIBNWOacqGrgxBA7eXatIkIxAIJLtr8XpO89gu/oRyVAr0qjflS7nM+uYKzVaa10dU7spZR48ewPMhnUSWJGGNZL6ujEefcWQGp7Cc1dxQ3OT/CyiQOgrTaW0CRCwOjn0q61AGJsdtOMYUapM4e8MaW/FPgMrIdHqQD65bJgK9WowW+Y2RN1QIktAS1NcAIUs0oAEF3OBoaWxValV7nWblxf1Q0myaF0x7jktE+EOGkpHF38KNRnq/j1upERR05s+/+1QLq3OudKqaWAdLVwFE65KAwgGh7WEEk6hXl+CXUyE5r3tWiOcIRXwRIh4RxRt07J3TuzmEqyiVQnvBGJuZnEMX+5JdZ8iBU98STmxN5TnOrwtOagAwmARSQQSiGTdPzEucJgAAoSRAFUAchGhS1yhLFFAXil6W5kq7EWEvZh5sc9c+k4qp1OQFJyYAiplnAIkl2cEmgtuA5qaHxRjg5+95HNJu8WYI3KyMsOhVVYg75hc8/CMXg6OvtsQw1c71V5a3EmbPTEipOMvEQBS+djN2PfLw6b4QdKAdlnjt+gY2cKMTti91FAld5NQMxkyK1i1ogkLDvVVSRdo1oYUcvOOYKc1A65Zc0+6tuwK+WQyvVRc+FjSCPoUAvbiIIUguLzwKvUNsgJLdgVd1uYXQGdMCjKLjAm5lPFFe+Uj7oEAL2dABPPnvg/XkILiUpUnTr4Lu85UBwqxG4BiMCgq4swqnCwvqw2461HjUMEH6P5ehdFMooz0ADnXcMl57SqUB6P/68Twe10Bk0D/H1hSO41dL/x63/s0rJ6f+OOvfWdhB1gAL4rxM9a8BVB8c0sMnWJvm+AAABAwGeCjmmRVvaoNK/QC8Z9wesuKBbKmch83TPH6UiuT3exxznfPs57KWS/GYujRlwLGTm3LmiY0IbTCH1yUzaQFUwDHF+Bt2BwjA6TpibIcCVUx61EnbuV91H1Cb2oVWdXnWPWkkOZLcIrs29zODmvf2/oRMABRYwiWfC6SeX34tjqsVORv16Wc5jbbst8k4nuh4sitmvmgX0TBRGtGZC/79Wei+zDnI3mEYF1hqNVE42ub4FLsU1xVRLSQPw8PWeLALZxHCJaQsITwPVgasKor/fKvIcGvyUtbOrPn9ClsQYJe6Jqe7ZG+xRIQjQPF40ss/TIjmJZCQeNkWtpKePV5ODRxwhGhTdyhDFIIoKRxLXXGFNKiyK1l4DVijfsc/AixMRJYDWh/p33fnrV3PvjPM2tVlpwcPRiG5xaW4ZTL6y3DFL1ikvFnw2on9ZQoFXwKPpoOOpiPk8E0UoTNmG8GwpH3gKRp2V1P7KB1Gqal0JD0ONT1M01jbNG/Gtm34rWHRDrXkw5bgyq2FxRwQbyvFxprAG4X6iM65dUIVzzT6T+OCxRZyU1rFoczIEA0MLxeuxyXbxys59VpsCtO1miKoBwTziqywYlNVSCgbR/+qqZbdgx+KTLgF3E9k3SkUaY4xSWe+anSi80BIOAYIhFEhBGAxEBSC0Q0gEaQvVg8G+kQ85on6W1vGXCZG/fACXpFOdk1xAjTAHb0fvwhV5rXPI9F+7urqomu5eoY04MdEjXgO180WWhmrX01oGLwgO0Y9HN2VJL0Mla9d2F9QfZgfsIRoUxaaZB2GiQC7uokq6uk1Sy6vZm5dDQ/NtERPzt0RiBBytA6NzrAsYsmEjd+S6uO93VTaI+vv3j13SNTJMawar3Txdpk+Tzf0pkVQdUsiYV1gcrbRml0FJYu5Z/UeSRRD6fjGbu4PkdVBSaJULvsQmYj9fzY7tbjNaWihV96IebI0pBgKtK2CXJvoSwwMMsMJiCqwJKaUZVhcSqy/IgRtkkVYH7CuQlb1XUO6yHGxAMTfrG/DHCm3zYU92ns07qZ/fQWjDRwxqjAy0DMv4HQgmtk34QZevG8F5vldA+cxviSiSQfTC1YM/Of5uPf5kswTME5XbuTu7uWZsrYLamSlboGB6j0n8j+R/cfkf+Xqfue9G5Vy0lXAwAWgwcFcAAPma5VjZCt29uN8ZIuATxDix4kACmoUoxjcLjs6Jc12tHOb7RKs+yI3TEuPZwVNYIZhHCzM2KxiOuHG5Z6r0FzUBGxTFWlaYujwAAAEPAZ4KPaZFW9iiqZ2bYAYAQ+KyZDuRbiWcDYzfJtHOjR3m19yPkd6Qns06dVa5s5LMTyw/J9qQPI3fYR9tSQhXcVJoICnWHHC7ZXet9uAl8pXIPoYjbhf5rX/rQH/w2cxhpkAhXUfG6m3RrX5JaN/3UKgT/fdqNDy1fSoVrUrNMWcQX4Au8VRhUrI6vUhINr85zXTq0g45Gfiu4OoKewVJvixgqRPPmJnbHqmOlLFF//GV4XKSS0z47XXS8iW96jC64L413xJbj3+y2qG7CD9MfgTqnJOTO2tWbeI5yJeZkYcMqptTWQtWfmzSsNls//t+suCTIIH2fX3NkZV55oDV0O4ps5mhVFpMaFeOkxePfiEaFO2qnwZhIch0Ws1vVSKtaVIiqmxQfPplil3JgrJAukvK/8Sp1EgB+JnYH3GE/wed52FgbZg1uv53WJ+e83g/X5TUbVkdabzlSdc96uJmc/6yEqyqvSFRAhfQQ2PhHwjELK1pq6LsS+uXT9VYNCRnG99h2W8FxtqqTK+9DdlqsTxtdapmp1iTkNPcGKRWQbem8hT6lrrppI8Enzu42dsTKiQ93A3ZIoXMzaiRx0n+PIu/FFfIKSQRpIx2TkYW58stQ32TpAgaXetNOli5VoLMpbCXQll3MomeukicJ3qlntLa8SmimYmM9LtZXdEXXzhZuiVSHooRSO7UDkd1I9GpYVAv83sZ6zBYMsskrsGKFoh2O/SNiOKaAvSQSvG7zDvRDBQghBYAXa6gQ4AAOv6k2770o5E+r0UG+r3K1nVa3J9b6dmz6w8SNJWkxfKNIeLeyvauoECcP428bprHGxrr7R229BCGe/K+BjjYRj6IYLB2NhiskjeRucKeIRoUxcIewkIwwC6mkqLpLzWLgDEoJ4uqKTgjJhISvquTKkL60QZjSTFSlEwi3A0Gae/vUXpVU4hk4nnfN3PZOKwmdHe0Zt5J0ZEIxvjoXPuj5t7/aIXoVKKabIhFtiryQalG2xM7JuNZuECCryRRTT8gNKTNSZafBFSdA9g21slEl4H6JctGLFMUuNdxU9WuRSk1SIQmheoUME4agTqiQ8RKfSKKpKdUEly3GMgwqCmegTPTESMLxhEElrwhfrS9rKoyT7R/+DolVFLbqLNYg5TuJ1WkinK910Tn2KiEh3lF8UWfiEez6/3xhLB2JfV1Rw8+Iorr4G7VheeRk4H1JK5QkpRKddK4Yjkct6hu66FllotLvsPOkLg0VgYi4QgyrvFoMAACDRBAB/l7MDd12j6nbMG6YxqjGlcIrSKJUw45QEf9fspbzQjHtkvzpd9pc4zyTORfdctKA/wAAA7kQZoKUGA7f6j6M/RBMgUDGXJW4s4CVPvIhJKQr2kw76vI8Kqw+OGGcBlw3PQaJBibnACoi/+IPnRECI4AnHFC4cCFfT/GqxxF5iuCsDkSsYBXakYDjZsypI9qhJJzr5UEcOv3xShfG/hO0sCifkjSTMk4EBe493NwILgVX8hseSm0D4WjQAQgesxhekMhdfZIUng4SVm9HJmpe4TZnrlfd5kz6Id32iHwKUF1pT1PbJpwASUMpRIS5S3HmhyEf2M47Be7qzvpKxSlAb6pSETT8+W07PLCGpESAkMSv5d3VHkHr0QbrC0PrH6MGtWPr754H5iAwdyvbZbnaE4kNI7YKYjMdjDQXH3fvRElg4RNooT2VtRJpqarKhvFu/ChTQ9kiwfRU1YZ75tnsyE7Ksz/iy6d92qSZM5pnZWfDbVuF0O414rg+ECuU2qd7TtHJmbDVUIN3ZG/5yMFbeCGr/UzYo05TnmZE5o4z54MYgdt0gY3bTxYfcUlC4c+dIBGuc1MlVFANIfBbtw292IHuMlpVMxnhAgjlDtBKZ3BFUAA5Sa4Hne4ovto27LjRslDOG1MyMQQWp6OQIaeks0f/crPsiFmal6BhzzxKVU/h4OvmjWEiTVl1L6TrMpWWtNvnWf5l0OZL8mVRGhyd8fnmcl0CDg2mPXcTBDtrkCdRZGeb68DZ3tvh3kRelAQPFu+WQ8XezIfUzQYNjPkegRHKoRxBNFDBvcqvBrXszt7wACCKe17KDmGolk7fQIGM7XrVrfpCliAyukUnzznk2bTF56/ewA+Bwo9OKP9gAdInyTUyrYDme+XV1De8x86rxmrwnxP6xKwbHYS25b5EIfnRGTG40/K7gYPVQ/tDDt05hlMjEP/JVE2Mrv3t3Lf6r3DjYSB3xelfAOiKhhpeXcjPDLcdJrJnhe+dTtKtctbPM7P44xdQoodGsgiO3h07XW3JUw86B2UuLBKJXqNlR7LPeDCH3pysD8hEkUgcD0idkW6+AnD3a25w3f8+7ZebFIUBLaXwBaw8W5Ip5gLX61g7TghRan2FHfJ+xmLxRwjopbVLSXFCcG70mdSQiyMcTKosuCJwxqiCehDL+TG6o/2S2doz4YhduV1UwtyxgbHr9sKX0B4uRJkad17w7VcZn7nn3L0VRCUEUOHLKRCFBCZRcNdoiQH72ZFQRB1f0bYYbakCulYaTTUMNCibLToD7wbnOXtBNrxrrThXx3vdOv3oQVxxQXhttk2G0Z+XFEVCSjKLtThT+j/hWz/Jlp57boq/YVuje5sd8PcHZvEe9jNNuAmPE5R4q6xzF9NuDR8qeT+XMIVoBRzHkj2FjCaT0K3riUnHXjdYq2tIHcvgo1RRmNwliNlMOLvLbZkWSoZghQY2Mmo8+ENYjxGz09lnFPOlyswVqwtBnwY9nay60UUndBqcfYQ97IIhmTVeIH1vKuIHawi8ODWRkjNV2ki5F2qHA1KuVAPdviBqc0ccC6Il3kfsB3ekuPn64quiabCmuPYxo2J+wDHUe+gC8iaXbHeOGQ9FwdL/Pgp/IW68pHVKbfeJF9cCyqjaM/NEe5kNPZfLoy0wbrBAucHDfEjQeBdZVKBI0cytwK8ALioJ0nd59tzSqRd0giFrVhBlcRfaedMINBnDH3rfrd0GOTflLvq6b6/0C0m4nhS+/XFbscu1hQDT+yAiM34MHid2Mhd+XMBF5a1bV+jUDiEOL94bzl/4JeCgaTaIn70Rd/EnrBu9aTqXyIVt/VIl9ZTjfsOmpOssO1tAQ7JDvjuTYMDQ7bcar1uIxHKx6nZwDP+Rp6G9SA2UKY82F19Tno2zIVMx8hWzSU4XTjEDQQysG91aOb2p8qlkB6WcPcCdhHNPyNpl3aHC02IDs3xpQbrTCtnAEIh8nwgHVPHOgIzu+Dzqlx1vw5yNEma9YerYen7INC54BUd0qajPnHlxJsRb9jd3ac5rIoazhNwtNVcWZbKpMEXjiZ/kD/3Ojq64rxcKfJ7+dLePr7urxSoqMn9me+aRL3wrwkMamhYLbel6yJrabTbGyNI+5mVgWX2zkgky8NCxOIEw3gzpBkpPlLN4cdmeE97/2/bU1cmvQOPCyZdlkqWQplYaWX50ssXDuvW+LzKgQzrW0Fo09mSjAZn3BUjlbisiYzoC6pi/8d+x8fRnyd0orMzTLDA7WS1J1wFIzRDyIPGxiUuuLMpb++GhqVosDsGSIyii8RiyavwGqyfKsQK0bD95ib7xur6mrKFL09EMcg7p9lvkJC/WPIfsL0iMgIfV/Tf3pt6K/bcSpmAJW+KauNwUg8kcU2bz/F2HmwHwWMtTMDDO5Q6xtxzDEv0dkJzACsTfEfWYMmRTwcliExqnD+9rrgTkRRU+nmk6ZpNsGqZGTvd20VFf4KYANdckj38qG7bHvnOgC6I+AxJGtMPoUIzo4VEdvrogxLA7TproDEmGkU3OG1h2I8BsnAMuIyT9k5D1XPEPeY0XZecIKgr2kIaZBvhbNm/UunfgRSpX3r9e+I+
*/