///////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_COMPARE_FUNCTORS_HPP
#define BOOST_CONTAINER_DETAIL_COMPARE_FUNCTORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/ebo_functor_holder.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {

template<class ValueType>
class equal_to_value
{
   typedef ValueType value_type;
   const value_type &t_;

   public:
   explicit equal_to_value(const value_type &t)
      :  t_(t)
   {}

   bool operator()(const value_type &t)const
   {  return t_ == t;   }
};

template<class Node, class Pred, class Ret = bool>
struct value_to_node_compare
   :  Pred
{
   typedef Pred predicate_type;
   typedef Node node_type;

   value_to_node_compare()
      : Pred()
   {}

   explicit value_to_node_compare(Pred pred)
      :  Pred(pred)
   {}

   Ret operator()(const Node &a, const Node &b) const
   {  return static_cast<const Pred&>(*this)(a.get_data(), b.get_data());  }

   Ret operator()(const Node &a) const
   {  return static_cast<const Pred&>(*this)(a.get_data());  }

   Ret operator()(const Node &a, const Node &b)
   {  return static_cast<Pred&>(*this)(a.get_data(), b.get_data());  }

   Ret operator()(const Node &a)
   {  return static_cast<Pred&>(*this)(a.get_data());  }

   predicate_type &       predicate()        { return static_cast<predicate_type&>(*this); }
   const predicate_type & predicate()  const { return static_cast<predicate_type&>(*this); }
};

template<class KeyPred, class KeyOfValue, class Node, class Ret = bool>
struct key_node_pred
   :  public boost::intrusive::detail::ebo_functor_holder<KeyPred>
{
   BOOST_CONTAINER_FORCEINLINE explicit key_node_pred(const KeyPred &comp)
      :  base_t(comp)
   {}

   typedef boost::intrusive::detail::ebo_functor_holder<KeyPred> base_t;
   typedef KeyPred                     key_predicate;
   typedef KeyOfValue                  key_of_value;
   typedef typename KeyOfValue::type   key_type;


   BOOST_CONTAINER_FORCEINLINE static const key_type &key_from(const Node &n)
   {
      return key_of_value()(n.get_data());
   }

   template <class T>
   BOOST_CONTAINER_FORCEINLINE static const T &
      key_from(const T &t)
   {  return t;  }

   BOOST_CONTAINER_FORCEINLINE const key_predicate &key_pred() const
   {  return static_cast<const key_predicate &>(*this);  }

   BOOST_CONTAINER_FORCEINLINE key_predicate &key_pred()
   {  return static_cast<key_predicate &>(*this);  }

   BOOST_CONTAINER_FORCEINLINE Ret operator()(const key_type &key) const
   {  return this->key_pred()(key);  }

   template<class U>
   BOOST_CONTAINER_FORCEINLINE Ret operator()(const U &nonkey) const
   {  return this->key_pred()(this->key_from(nonkey));  }

   BOOST_CONTAINER_FORCEINLINE bool operator()(const key_type &key1, const key_type &key2) const
   {  return this->key_pred()(key1, key2);  }

   template<class U>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const key_type &key1, const U &nonkey2) const
   {  return this->key_pred()(key1, this->key_from(nonkey2));  }

   template<class U>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const U &nonkey1, const key_type &key2) const
   {  return this->key_pred()(this->key_from(nonkey1), key2);  }

   template<class U, class V>
   BOOST_CONTAINER_FORCEINLINE bool operator()(const U &nonkey1, const V &nonkey2) const
   {  return this->key_pred()(this->key_from(nonkey1), this->key_from(nonkey2));  }
};


}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_DETAIL_COMPARE_FUNCTORS_HPP

/* compare_functors.hpp
NzJ7me5qp7Xc8wJrm+yl4ZqhHNnBD4TDTe5W8bt/V3+V73P/VX96mT7v+chi9jT1j+DPS6mnfy64J49TZpIVFarlnpivDZjZMR7eo/RsiMJptI9eENTIuDU0HuAZJ4D5PZNPTnBY/yXCzev7TmqMTlscvev8T5vjTmOR3g253thNpzEl3o2jp9V7p9DP5RgNcsLn394wk+LcEAtkDNNZ+byV/2e/mkIq5tPt6MMRwXOxl/GkLIwnhsVU7cMbIPAyJpctIJ2X1/e8ehPdpEw4xect+NL3vVnOPhEWLAEc5m4m+tmXH8Ij8Vle6p9vX3A6ogQl1D/5jtlNVtbPTEBNjvWCmt9PMcJPJfNc7rfvlp+f6mc/rkw/ZQIXzX8XqgQXatetDpd+euuU9C8uOGsNCXlfGT0nFVO5TGmqKPJ4ZaZCatSEkn59abZ+eYhzYdGBeth5ZTOdTqh7gVt1Tk7t72Cc06HURtrvbHp96lB8dYHF/l4RIFLp70EAr3/EXCu49CAIuMHKUUFmRKiCRF+4eFsFXFvbRi2cWawq+xcHnJjA3pMQu3f4Bq8HHOdt6rb4hRME/gnMIJG7tpgLiHweuI1KDOhAHeh4xb6+QW80XvPRQ92dfBOnAzcCAyP7/VG/AtM7Utm5byi6ltJlbxetA2ELPmkqQW+K8ZJkN5MjgvI/4KXFd7o3BL0zTs2Qvc78MP2O4G5SJyhX1KhUNvhrQlDyL4Lyl3eTcMOXAcEfx1Jqx5OqVG4+Tt99XlA26odSY4EsZ4KbrFJaKwBciFiJZyFtv5PrP0FgJkCQV2xbcchnioygF2CQNbR7/f7T+OGIZlTn75CB18n13Bn4P+8Hnj+0b7i9dCIdiXigjoF2dYiNNzw07i/Vo4O/rj80pBN+MobopYdM0T1WLSh3rPsMs4bNreNHeoX0Pn+cex0WjUOIAwj9/iZsBY1t9H0ZPTQdtn6NPaoCGEOHbU1jU74NLeEN31XBnrwOrrUK30djTaMxZz4/7n8Oz+B7zOkALIyF//uXQOj92IsOP7tOaK177OeNuBxLWC1OX7OKuGlI2KB7umlAl+c81HREPFoRRAKwjDrdIbdOJ4jBGBi5gPv+Cf1wAhGrXu3/AOxUoj5H+6eM4+kMKplcLmdME9kcxuq4oOQ5WaVyi6Zal3OWqUKJgLOjP+esMyXy8ZkxI3jzzDAqrn6mgwv2n1V6H/TqXC855kvk2lksFUpc5httxzK53a64llqNOzKb02MAWm0+v3/UuV3zrPXKpWJstnP8kG0M/j8Au7Ea+nH7iiBSdySTVb/e/VZgL4bHheHGmE9wf6ZMJYtnlXjeKBKi1eJ5fCd8tIBpOZhNaSzyd6U74JzHjeSjXuWneGJez4ebiTq57nClvw/iF/s/CJtf4QRIXB0tdbzeOyRvtP67NZbFy/umyW487VvLy39Pn2a/vZYeaniJlnkq+4gZPvUPLYsC8iiaawpiByKisJuvzfU0Yj8gYgjVVQt9JqXF6OMoXU3MXr1cbadPoE+qyguIgIowJLFXO5MHv1ZqZ0jhn+gk4yr8LsqYJn4QuBRec3zDmC5XpFjiIU8VxJRJxk+xEqsmcbuTQaq3YZilYxbEnPbsRTzzG8tRE4bAF0ni6MoE7moVlnwXZTYrp8ePtyyF16VkMa6eo0GsRXuELtZFYXdvVzPxn8TZSsfV1BxKEzm6C3LpeO7Yyle9Z98kGioHs1cmvr21rXwXHExRIBouwfHx1TdTp48fq/Pni9Lq7zhq9aAcFrVtS+o/S7+tdnM2SAkvcTYO1BswVtjAQriaCZTIIDzQsCtqrbRHL51guc58rvaFLflV9596y8ZwD0dJnvbQx8Y6uWWfFlp5X58hup6dCc4374hGQjJapOeo53uWr35Z6Rc3XRKQlWtK8g7SaXF4wctp2mi50LXy6nI1M5iwV4S+5pPB0IGzU7kvD+9P3XGpy5usTjPd+V0Jr8fQ3t1FXRfuFlRuvRPljMmwc9n9CfemFvPUUN9pHuZh3x65jZVmRzTW+9N2zeLJo5a00l/udqnsvymHL7omZ9q/X8W3TJJBOl4OuljtvJFL+6ZZO2O+mSL4zo+qldRVgzOsY03+qzvJlF+nXvrnCezV0+U4gmOesMPvn9omi9pqLX7SvbRM38aRLcLlDDT/ez32F7a20P5a9ulH4YRpONxVoKecn01wO6xgeYp2pM3JRJKz+WvSfY/X12hBtysYZKVG5IwoKGCG2VHyeeQiZEMeAJ0r8PgERbcaSl87uqF7L0ngJwSXK6xQ6dtvxeheuV8BEdjAcp2IML1vHf/Cb7a3CdDSD7WTETJXTzbAawACLP3Tcd4Q0E7R5YaKzL7hyzAyZxxg6XX/sal1GKzQCgwWQ0LUdcI37EousGaknlwao2hCEUAZik9/mJWICC5Mz2yxCCfF40B4M4OykBMC7psBRGZVkVxrOpDmaRsPI3IIX9A6XYwEAMEAykG3SmLZ7/jY5cptCV93DkXcyCVoPYwx//edE+yUzhWwTfrReTgCoYuj52dHjMmmzOFYAsps3CJLrIJw39GDLe3LiIduXgtpNqUE9CpS4TUrixkA4vUh9lclnUPsHN9jScSwyMgXURG435O1H+KZcCjjI1S36N4UMhGSL6rKDvKna9NsMX1zbsdQ9UaD9rPoeZ41N3roIrELcAdkVTcgROmReIoJINI4dk2bXGsc3QR57ELEN4dMOVg6GxA7Si3KQ4IeprcAIm1n12YV0oe538QKvFWDsqsCC9A6e5KfumIjFH3f7vixCEWLT9rUt7zT5kuQ/hSUHgbLgp2Xy0t3UWr5K5+/u3oYE90F6MQ2b9Jhze0J/ArSinJsKdC7GSM76JomUhUq/8P0QZlYQvslg37FdWilhsbM8xz/7AomgByQhQ8M3mv+gG3z64ILCWBV3QTT3cTrElunv2eJweRDcujJwpMiYgar1IQj5bLV5yLyNsBSN5gERHAjWpPLGpXdSNMa1zlI+Rbde/SMq3mGulF0zBzChLlGBt82CkJzCcZWBeAuwaIJyrfAzx85cIddF5qj5hrQgRwGr/PjDQBk1X6G1QZ1rj+/UpVXP3/nylZ4Z1JDe9WkHQuUWUmaJ8DdasLGgpp3wEwXWS7pQrUARuySMNr+3NqPXq4mgm7Ln56Ea//pIMHZiITT29auMhD00uiEAKpT2oD1ZUjXidqIIvTVR0PosdwW1VpFUU6bZltdIOHZ3F8Wpk+wxVp5jK8vrvVEmlqkVfWcqI0boi7p/n7iCvnSvRa98uYzRhBHFN19OqiYvDlHic+67c6gYo28sUC4Jsrm/rXUw1yVoxaAWpUvHkg21PVtNRc9nms3BMorhZgeN8rgHhpVnCE6Io//GhAUGqF/CLfyodydJe8jjR62sWIeAUb/Qpbaycg+ioc3ZNS4mrIKCpNEXv4LqknZJqCJrMH8wu9Fn7zBkhxUI/+3OeOd1FL9Uk6H3qorByh5hy6ZrLblHYf94ld4i7/htIZ0lEzj3Wu5mLIZDDWoA07Iz2pPGwiVDupGc8UiCe81iNTaG5smZf3jKKXWx3FvfxxJE9aNVqBkTutzYScRK8f3kHnDi6DZYYfquLIaFaQQgaolQP+cZK6zkBiqBo/9gX81liAyLlT4c5eVdwdLX+n8g4IcBlt+fldfmk2q9nwuoao1RHfG1SEI/fDapXyLSiw/jiJzFeLEWE6qEhggP+ORzpKwOe9c6cqRx4eJzcX441fu5rG1TbtGNGI27xt/+uxPhxgxSdIplijivple21AMO7S2OTzQaUKj46YvgufswyZJUix58FKPTJscV7h3jIOFk8hDs8M6rocjpxTJHZYSh2a9Po5B6C6X1fQFGwIoporASIy7nfxnfw6OifpJunArZ/DX18cb7AjJsxIlODN7G124lyjeL9vv+feH2P3eD4wByFrjSsSw9oH+czJRmvY6W4MGIHQ8jhhZsOgUECawV+RKbDbrEP9bklgDfpC68uTf+cFtQ+tBye2fxU6fMcZRfZN4CT9ACb2b1nCcrELBUz3mXb3VPpH1ue0XTouXgcmmcKnXNaHfN7f22afzbVej4eBFAHQ8tx/3+WOeKj743fuVK4MPrzHdIiPLPN/R40TMNtdJHcPYbDDmRfp6ufzVk6kKRq8dOvLXVr0KieWGwb0yVxmG/J5YdhsuJooiBQ0b0Sg6LUa6LjnPbxAVTmTkn7Hc/wuuO4gqFH8AgENLndxVUBxAFyjoURh8gMFtcCe4hcAM7u7uDkETIIK7uxPcAgQPFoJ7cE2AQIIF10AIYfb/7627Vlu1W/vST/3Sp0+dc7q66htNUNeFF8S7LD0Av+dIma1t017cfMUw4m3kpD3h7JNpMnjhnzUmYO5UuLFA9h2MG28njz8qntz4J7OJ1bxIeL1e4/vxG2TzQ4hPCgjKgfqoEGpHR4k1gvPon9u9a0aiHEJ9l4+HO9naAeKYIqm8yfRSGRVdxYQJr0K7n5kPrWnN7E7CR+IGZ0cBtnlNn3JfSDFaNJqNZ37VNCipNt9+T6lxyomG9pCaDOe9WA0z3THO3jCf3kYsBhaRlW7XcowSsQzyGvfNqgDIWLJ0VHL9KPPQISWmGXQLEhvTN7QMm7hjkEyoH2nVNjJwLAR8HIJOGUSPMSIfBvkoh4CN+ZTwXG2erbWKDR+VHywjEwPWU3H+BQYmVK/G+mTWB2WOARzUEbT0EPgOw/c/EOca6206el+bhB/DtjUPmnBxy9HELIdn3ylUwRxpcuxhpXwTIXxppYQPcjTqRZR1THu/wvd0vnNXFgiNTDixyOmubghfUuiZ2L0Yw8jKPjDJrsoyUQ7xZZTu5jIfjxfdNFnAhe2evlWdRUSc6mTbRebnssK+sJpp4hddb5dgs9nXC6vjLoF03qDonXN+sY4BQzb0WWlAlfLXBN/3yMoVK7ed7iJvtyh++ZvKs41t7SI1E6y4Mr7HMG6qDUwMzIYKZwEiLbY0VMdWT1imfzFg/lhp1+KOU0ZUiKTqYGUBRWkMeM1JW5cf/sk9MY6lO6ReVHBgIIfwNn/V1TCRTTDfKmSyKAHJnoM42WJbYhmxsypMslSHtvA5IN8aFZbS5wqe0UNEjcfHeGnGmqwVTyuqFmNmpqw/NgEH1lhsuOSFIXb8uvKslBC8nRD0NQYds25FJNhPhMV4L1FZxa/WIm7Z/6mETXBI6PinzBgrnnifjN+ejP1Pz1MTZyYz3bQRsaA9bXkbDtS6uLr5Ys1e1RZo2H2bSRxtrGMo1yq79SuEEFJm/ghmPwV4ntqKboZL80H4IwoDK+1dApy0t1jRjkRCgk5Vd19q22w0erNGWSFc9lVodyfp32wSKWBe/CrZDDtUOxaFF7vs6/2g+xXctJJXy/SvFXGXH+RicejmDLKtN/d7RCLYCX96xu2zz4N4aSNE5e2b/1l4xY2Is0V4YkGdN7bHO/fRis6VdxUPwsmkfmEea9lR5D9lZnflEw6EI0AK02MDG3l7Gn2IOszGq/mDig58kvavRv1ZUeRrKfR9IMqhGFUIpa59CS9r3Drr3q4ZrCcUyiIXK1KTzqc6hHIxyAPu9JcYcpUqZNjSFFdFsVS2dOZLqzPsf+GQbfj1bkdduMHY74VRIa88R0xoJ0ENOsBZnkWWc1kpNG6o+6Z44UvRPk5tKVxzhHUY0pX1RmMICLH0KA0LUWVRQZaNtxUb3hFUOY4NOGvhEvc9VQbiq2cVyA6Jy4aaV7qGHA9wZNVWkFODPTe/fjqUehjk1h/EGqqNcmaQpTTM1ZBPQqP5kbDg5V1leRutPAZtUOT3ngFuSkBrQ+wQbeRBUw4pbWaxBWQV3S8j3tcui4E4p422g44Ud4xdpB1c7yecUt530k910isD9uiBjisN0pBVkWOZsSP5B+apXPnaSyYFwAD/AeqT40hq77ecdle7w6HWvmI07FgGfrwxpT3R4N5vi71RZwq2HwxFLw8IRgwacilEMK+SVSqtO8oGlCoEAFyk3uVI0mJ3HWq5K+Dxu3VKR2xTAhZ7wx37rOHuIXg9oKc5cpOSSgBNfBxFtEUgY01e1aClPAHqUHlWNv6ydNgwouYRnGMa9ezUJdwQMH8/ZJjzfpwasjSiAX8AQDJ4OnsHWqR5ZWghnafgfurpp5QovOPBn49ga/cTt6Fi+ySAg2OWhurQl7wq9BhmIOvwSMbdRXUWNEs/9EtXPjuTuYgea5zYjmikzwV3W9Mdiv8IAO2AF+4HNx76dnoHCLZOtwlPm4uODVEAGXxPvMbwrcsTQyTgKo1bNuWIQJvPHcE12mlq6NGgqJ7p3BUlbO/2n5Q2FqfJ/gX24XI68Rx+yuMhm/J+mfqJLP6TTvIPUzngp/gNQAh6C/f00XNYGp+PRH6AKId7gbrxJktxWnu3QsHJNjFs1VW+GcryK28ExE8zowl9JKNO2PTQ4FBywj+V6QBcZbnfTCTgqT/pVK2/wuK72au/zuJ5unMC5Ob90Rv2l83LRV797808utHoSBbiDBVwRDj/M4DS7WEYEg4dVDvGDbeeLOyFSzygcL83AqMnCT6D8LijF1Wfw7eedLaj4Dxu/7D6pfk9lvbOuM/lnkY0EfrCNnPmkeRMvwxcFAoOOmyGv/0eItYbFqDmxm+tUuJQYkGdYEkJLCqCmGgAEAgQL/09HuxsS/b5eB43AM9zC0sDyAD51yvLhh36N8uNDBNODf5A1X1BE4813hf2gNISe5P1jkpxq4mPOBginRTZFOTSLFKdxsatxFF/iQW0xvdkwRfqJL/6e/jhIkuO4Oo5oqzOyQ9rQVbQH4J+muEurX+2FdRM8NOLK3lE57W61Gbhe8bcfM6RATIXFal3PZvcfES/ViMHROAYelLKIu3MVSXjerzGcxkUCg/V138nhKKBgNYBO9PhQPe+1g4VRqsm/ivwU2EfWXidMMOQbBWPgFnr1EOfVMy5WDxWl7tNfD+bmSrWE/zBXbKvfFoGRPc1T24hwnry6CE/ualWuYd6YPGlktNIizFxJUHe2TZ0SFLeOGtompwqb0lQB14j9XJZ6mk+Ugvy9QGi8bSemfl846Fe5uBa0wyrQjwRclrk8sbwSxR0GgSe3pNHcYkwLFg95lJxkzAA+8L4Uc4a79yVUFf6ZZAtQW6QnofIsYeRVdS5V7n2p0u3whbTVgMUfajkd4jQYginp8G6rAJB3aDRJ5o/ttafeDF02D6b6AzKeZS8AVHMwg8RNRg+CP8Mg4X+Tx7KEL1w4Mf7pkMkizAzrIykbDxFu4tqIcEGbbIOcsPlA2aPoQyC9+VrW0KRPwacg4csreRdJlsVjK4JruTcJ9vttafHGgfyJfv1RKgsHrzjLiFm+T/Pbo5wUXnXjXbFe/5KqGnF1XGinnA8lifnph9f2GEN+DAafvV+PrY7ogqViOEbNGHe2LTBOl5vL5589fOEUuj9D0Ic17Nbe/5J38Oiqa8m7lSjodRD2k6RfJ6VsjEMAQLOXOJoKmc09BhxvCrSAEFj83tgTAP8IMW+hilQGE1mXH76w48YVTCz6Ld1kk0ZHAxgccnf4uWkNke0FG1johr2uvMMq1f+x10y038rXvC1TybDXps+chyOqSK72OJoXBiKCqV1xCGh7z58JuqR
*/