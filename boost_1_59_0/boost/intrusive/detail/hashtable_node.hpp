/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_HASHTABLE_NODE_HPP
#define BOOST_INTRUSIVE_HASHTABLE_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/trivial_value_traits.hpp>
#include <boost/intrusive/slist.hpp> //make_slist
#include <cstddef>
#include <climits>
#include <boost/move/core.hpp>


namespace boost {
namespace intrusive {

template <class Slist>
struct bucket_impl : public Slist
{
   typedef Slist slist_type;
   BOOST_INTRUSIVE_FORCEINLINE bucket_impl()
   {}

   BOOST_INTRUSIVE_FORCEINLINE bucket_impl(const bucket_impl &)
   {}

   BOOST_INTRUSIVE_FORCEINLINE ~bucket_impl()
   {
      //This bucket is still being used!
      BOOST_INTRUSIVE_INVARIANT_ASSERT(Slist::empty());
   }

   BOOST_INTRUSIVE_FORCEINLINE bucket_impl &operator=(const bucket_impl&)
   {
      //This bucket is still in use!
      BOOST_INTRUSIVE_INVARIANT_ASSERT(Slist::empty());
      return *this;
   }
};

template<class Slist>
struct bucket_traits_impl
{
   private:
   BOOST_COPYABLE_AND_MOVABLE(bucket_traits_impl)

   public:
   /// @cond

   typedef typename pointer_traits
      <typename Slist::pointer>::template rebind_pointer
         < bucket_impl<Slist> >::type                                bucket_ptr;
   typedef Slist slist;
   typedef typename Slist::size_type size_type;
   /// @endcond

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl(bucket_ptr buckets, size_type len)
      :  buckets_(buckets), buckets_len_(len)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl(const bucket_traits_impl &x)
      : buckets_(x.buckets_), buckets_len_(x.buckets_len_)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl(BOOST_RV_REF(bucket_traits_impl) x)
      : buckets_(x.buckets_), buckets_len_(x.buckets_len_)
   {  x.buckets_ = bucket_ptr();   x.buckets_len_ = 0;  }

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl& operator=(BOOST_RV_REF(bucket_traits_impl) x)
   {
      buckets_ = x.buckets_; buckets_len_ = x.buckets_len_;
      x.buckets_ = bucket_ptr();   x.buckets_len_ = 0; return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE bucket_traits_impl& operator=(BOOST_COPY_ASSIGN_REF(bucket_traits_impl) x)
   {
      buckets_ = x.buckets_;  buckets_len_ = x.buckets_len_; return *this;
   }

   BOOST_INTRUSIVE_FORCEINLINE bucket_ptr bucket_begin() const
   {  return buckets_;  }

   BOOST_INTRUSIVE_FORCEINLINE size_type  bucket_count() const BOOST_NOEXCEPT
   {  return buckets_len_;  }

   private:
   bucket_ptr  buckets_;
   size_type   buckets_len_;
};

template <class NodeTraits>
struct hash_reduced_slist_node_traits
{
   template <class U> static detail::no_type test(...);
   template <class U> static detail::yes_type test(typename U::reduced_slist_node_traits*);
   static const bool value = sizeof(test<NodeTraits>(0)) == sizeof(detail::yes_type);
};

template <class NodeTraits>
struct apply_reduced_slist_node_traits
{
   typedef typename NodeTraits::reduced_slist_node_traits type;
};

template <class NodeTraits>
struct reduced_slist_node_traits
{
   typedef typename detail::eval_if_c
      < hash_reduced_slist_node_traits<NodeTraits>::value
      , apply_reduced_slist_node_traits<NodeTraits>
      , detail::identity<NodeTraits>
      >::type type;
};

template<class NodeTraits>
struct get_slist_impl
{
   typedef trivial_value_traits<NodeTraits, normal_link> trivial_traits;

   //Reducing symbol length
   struct type : make_slist
      < typename NodeTraits::node
      , boost::intrusive::value_traits<trivial_traits>
      , boost::intrusive::constant_time_size<false>
      , boost::intrusive::size_type<std::size_t>
      >::type
   {};
};

template<class BucketValueTraits, bool IsConst>
class hashtable_iterator
{
   typedef typename BucketValueTraits::value_traits            value_traits;
   typedef typename BucketValueTraits::bucket_traits           bucket_traits;

   typedef iiterator< value_traits, IsConst
                    , std::forward_iterator_tag>   types_t;
   public:
   typedef typename types_t::iterator_type::difference_type    difference_type;
   typedef typename types_t::iterator_type::value_type         value_type;
   typedef typename types_t::iterator_type::pointer            pointer;
   typedef typename types_t::iterator_type::reference          reference;
   typedef typename types_t::iterator_type::iterator_category  iterator_category;

   private:
   typedef typename value_traits::node_traits                  node_traits;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef typename get_slist_impl
      < typename reduced_slist_node_traits
         <node_traits>::type >::type                           slist_impl;
   typedef typename slist_impl::iterator                       siterator;
   typedef typename slist_impl::const_iterator                 const_siterator;
   typedef bucket_impl<slist_impl>                             bucket_type;

   typedef typename pointer_traits
      <pointer>::template rebind_pointer
         < const BucketValueTraits >::type                     const_bucketvaltraits_ptr;
   typedef typename slist_impl::size_type                      size_type;
   class nat;
   typedef typename
      detail::if_c< IsConst
                  , hashtable_iterator<BucketValueTraits, false>
                  , nat>::type                                 nonconst_iterator;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr downcast_bucket(typename bucket_type::node_ptr p)
   {
      return pointer_traits<node_ptr>::
         pointer_to(static_cast<typename node_traits::node&>(*p));
   }

   public:

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator ()
      : slist_it_()  //Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit hashtable_iterator(siterator ptr, const BucketValueTraits *cont)
      : slist_it_ (ptr)
      , traitsptr_ (cont ? pointer_traits<const_bucketvaltraits_ptr>::pointer_to(*cont) : const_bucketvaltraits_ptr() )
   {}

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator(const hashtable_iterator &other)
      :  slist_it_(other.slist_it()), traitsptr_(other.get_bucket_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator(const nonconst_iterator &other)
      :  slist_it_(other.slist_it()), traitsptr_(other.get_bucket_value_traits())
   {}

   BOOST_INTRUSIVE_FORCEINLINE const siterator &slist_it() const
   { return slist_it_; }

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator<BucketValueTraits, false> unconst() const
   {  return hashtable_iterator<BucketValueTraits, false>(this->slist_it(), this->get_bucket_value_traits());   }

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator& operator++()
   {  this->increment();   return *this;   }

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator &operator=(const hashtable_iterator &other)
   {  slist_it_ = other.slist_it(); traitsptr_ = other.get_bucket_value_traits();   return *this;  }

   BOOST_INTRUSIVE_FORCEINLINE hashtable_iterator operator++(int)
   {
      hashtable_iterator result (*this);
      this->increment();
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator== (const hashtable_iterator& i, const hashtable_iterator& i2)
   { return i.slist_it_ == i2.slist_it_; }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator!= (const hashtable_iterator& i, const hashtable_iterator& i2)
   { return !(i == i2); }

   BOOST_INTRUSIVE_FORCEINLINE reference operator*() const
   { return *this->operator ->(); }

   BOOST_INTRUSIVE_FORCEINLINE pointer operator->() const
   {
      return this->priv_value_traits().to_value_ptr
         (downcast_bucket(slist_it_.pointed_node()));
   }

   BOOST_INTRUSIVE_FORCEINLINE const_bucketvaltraits_ptr get_bucket_value_traits() const
   {  return traitsptr_;  }

   BOOST_INTRUSIVE_FORCEINLINE const value_traits &priv_value_traits() const
   {  return traitsptr_->priv_value_traits();  }

   BOOST_INTRUSIVE_FORCEINLINE const bucket_traits &priv_bucket_traits() const
   {  return traitsptr_->priv_bucket_traits();  }

   private:
   void increment()
   {
      const bucket_traits &rbuck_traits = this->priv_bucket_traits();
      bucket_type* const buckets = boost::movelib::to_raw_pointer(rbuck_traits.bucket_begin());
      const size_type buckets_len = rbuck_traits.bucket_count();

      ++slist_it_;
      const typename slist_impl::node_ptr n = slist_it_.pointed_node();
      const siterator first_bucket_bbegin = buckets->end();
      if(first_bucket_bbegin.pointed_node() <= n && n <= buckets[buckets_len-1].cend().pointed_node()){
         //If one-past the node is inside the bucket then look for the next non-empty bucket
         //1. get the bucket_impl from the iterator
         const bucket_type &b = static_cast<const bucket_type&>
            (bucket_type::slist_type::container_from_end_iterator(slist_it_));

         //2. Now just calculate the index b has in the bucket array
         size_type n_bucket = static_cast<size_type>(&b - buckets);

         //3. Iterate until a non-empty bucket is found
         do{
            if (++n_bucket >= buckets_len){  //bucket overflow, return end() iterator
               slist_it_ = buckets->before_begin();
               return;
            }
         }
         while (buckets[n_bucket].empty());
         slist_it_ = buckets[n_bucket].begin();
      }
      else{
         //++slist_it_ yield to a valid object
      }
   }

   siterator                  slist_it_;
   const_bucketvaltraits_ptr  traitsptr_;
};

}  //namespace intrusive {
}  //namespace boost {

#endif

/* hashtable_node.hpp
BjfhQhrzOw+Zcae9bL4inZuqmpf2zT/aPqpywqT2s7QN16UwvFlVy5wEtGgIQpXaKApllj8aPhNHHJ/Wxtge4bipCK4wMpaebAGwu1+B7rCBezPXNc4SAyo346TnImdrqzUaUtYlkwzfxvL0EmqoWp3pu1I7F7ZcqzcS6poqO0ReHPgTPooScVq+88GuUQiNcGsXGN7VoHxUU6nhCLeCcS0hi9zYUwX8gK4P8gZeLsSS2/sMtMnhEvZhARoTrPqAIgUtK1127ZUQISL6uNp4v+Ixp7CObQxCn9p/VrGzEa83CZf8LlnkgkU++yi0XvndsTSGBjik/1YGWj1tdx2rChknKwUQx3gQmmeJoyld1jEjmoMj4IJ/Jzey+iOSQagO+OUF0vbRCdoaNsxYUf8ltA9nRCwqbSP0MVUaVQNncsx64KeFUfKxULTf7GXO0koHgACAQ0sBAID/fwmuapA2b6tj8anGliyWpoTBwoCBMwK88NTtbKopnkdI2PEdag0+DnkYMz3/2nRbU3QderTGR2n9qwOPRD1QONYWRjNuYDTzQwiWsxyGY00czPDRT47vzocQO0LlOXNGd2eHN7zihsCIxv159Wty9NFzAXbcCjxk1nJ7sL/289UdAFXf0h3It+uKJ1D4HjDfVWJhJPu6PBw09+c9Hn9n7X2QLOB0jDhXFgZOvirWZsU9IrXVON2R22KqMZMNQcAAI0fbarcEpPstGspsEwdWn0SmGHQOe6kNHgQZdrHjZ8gojgjh1M5gPppdwmUVjyxqeVio0VCqAbLtBy1ZRaDRQ3fZMbNXcPvH92st8Qvp1BrsgyS7vnCvfEIhm7j1eN0PpWNk2cScX5AxgIsGMQPxXYatgtTRvpraS2aw331Zm4h3EY4Z9CLwxrWJTnGgNCT/Pt5uVG19rS6xrkf0VaK8JUyJB0VpCvRQha73FKyb80Oyq+eZaqRlxjGcIWHzfcxJ5OrwQloFVNxie4AxPVDB4H0GDcVn3aM2q8dmn+A7PUz8Qs+tmc928JS8hMck0Xna5w1gq6CDDpKjb9kT1YZHv6uyZE8LoizqWmHqmIZFbxye9FaWhjZYAQ9+Yz846eXl5QsEpTz6rgMe+zGK2dMtpvR4THl9YHui9VyEBpabFA6SotZQhKFgvGBHnM+/E+Oa49emibzTERgfGhVDn/+fSm7BBzBG/lPnA/dUCTDoHohXjrRxREPv3H6bRmdkKsVwKhj+dyhc8iGUIrKc45SuBkYkuvoyWekTrGk59SiDNM1a+zOXrzGIQe+mWJTx86byybmmbAplGWcScFkTUmEsAYygZ9D3Qfc9H5xowjpr5oh64eAhP5qUwJxrJxhLxyJLMn4q1OpO4OyBVS040A9kd5/dlsSvSsCdK/d0Fhc6aVpvd3yv22C37JrxxiRs04a/5OavT7fr1KF3X4DBK06L/sA2TmAPgyPzCvhLBztMQM+voAc7y07sy+tj1nKPt8i2vGl/TGfWptmMCViudhPTIDZcz9th+02ZZ8GzbMkby+QJNBoHkbhcA0lNlVLQLAVvKsKp5D4o+b611FA+7M5D9Rv6U1h2t7Q1Q6LkBkkiQypRhXD/IDbmDafWwmlUKIgnQEwitrB3iwbjY4fOXXAG8oo7hWzUD1kJUiY8F/InzdW2ox4mejn/7dNQcvgfyxYMwUkgupHyrKLSMu2NjGVqd+7ut0IZI1m4WICP9c7XI1D9M3JcWzQNqnqD04H2/xCItqbhM3fUA563bx+ilmNGynlHRK841Wpe/HSczYEplMvY7hMq6W3k3u2Z275LuhZLSpXGL79/MUlamZxm7rR+G7LYpbsKBqZHq068YQiGW/23yxYmLJ2exyfnbWQsFrHmbjSsTPFa8hR4zSYkq8mN3xXeBoqRzcgTf7xxy8PXjy/jherLzh92H+BQWNdWw3FZNU9jrrSyGwEICJoQrhyfIM2FLeBfdLJUq/k9qT9fuCRPBKUGobZiKJHtOiC4kDvXNkettljZm4MZbBa9BTu5ZxcbWZzbobpxF+Hz7k0ir/AGozIVK/DHcidlRdEMKzhtPybWPnHH8Bmvcs5lGEVTBWkcjz6D6I+Jbfvq7etuF0EwrplDAZcXMuwhHyYXZN3ybUQKeclLSBkpwhpuajoV06Dfrix1OSRinpdnISVWABE/ZIrEPXJ/+0+vZQEqtkGVGWcf+c15qLAK+NOOszKofW8GpcxGidkFF9m6GsfD/4WSv+zlC6unoUoVBHfEv8iLSBmrlby7IAdeRoziM9T8f5DnStHqvN2C89if21G0kmopmw1TS1LRUqA6BAQBMCKsSLuEfGfDj5vysB5U4oZCgsKd08kVad1Mil3it4EBoORczy5fwdPzEfDPLNrIECLMJOAD4jE2T4tqcKXuDHd7XnbQuGWKcyj0Swo44aKpwCW8KaHxak76+CQ4LlB94zHwMMqG3tzIKpE+mtw0kuoX5BTIH34QE8E5cY5G2o61Jh7xC3nt8iH14+EPzOErLV9pFIQQzR8UP53RyvjAnXhzUvNaD4UzkNlNdsKwRs1a8OvFuGSTVFgyP3crNMOJfnXOxryoyJywZwVXMCgKjOsSeGVn1wRZmIzwu6rxR+XnOIUFnStNrvrjfZ+Z2nooA+LmWp4ERd5pJmCvz4hhVC2sXnf3UBRkENETIQNVsnm11Bost/+wxABFZJ/MfobzbcuN+EXuXECODnJwAW8JNTOw0gqHpioJ5XlIhh06LP1b6waYmObLN6pIFIOBdoHT0FlHWWa5HaX4CoWL2Rk4Kk9MoOOHVXm12m8bzcasOB3yEV3uLJfFX3H0QLc7tvq7ZKD+e5FmMAvR7q8xhqxrjs5Wcb9a1cNp4vA1/PMzFUjhPKeKzbtNAHR4W8KDJL94o+My2gjxvGPBvoVa0hOzaptqwIcJZT0lCIQwCFuO7hwBISkrqoPClb0J1EnIDVsCDmu/YPc3DqgyPEowIQIpo2l2jBwn1cOvXprWW3cxkb1DQfO0rlfUIFMTNmTR3+9vGZRYRKhUH4w0dlWHzZEEcNcKCf/pPTQaRq+DcosJ+TDa1teab7vJ/EHkF52y77vdqXb4EaWLDibO/nhon+QJWNZD8eh9JAFlH0WeXiOjYzzYMTNHzq5Vl77nKCjVhoIXp7zgv7mPeoexv+5C1P/1kgZXq3kcTTcdWsDWNbBd/8p2QI3TNYN99Ggsfn0glW3jDeS3OZmJn0rEk1wtROSY3EsFl4L97nCqgD9yIBayR6OVO+ADqgbrOu/onxyVJG+Lc2BjsB1yAbjV6gdlpg81L59BgVNsZboavHj26wZfRjCc4XjsnwbkRUtAxwIbPp9T5/pyTEe+Xm6iJxxJdcCexEZM21QRfBG13hUTpqhDR48NNCWOHJERngfPXd9T9V9LEDCvTK3Ucj9VGLdAIEQ5VQuNJsNol22dRFuzp1Oh5fVfS4VRuoQR46Sm6dWjLUo862owX3xWPdRUVE9KMkkgVv5kBmajAU4T+UUVXGz1F7kJZ/d0870GIGkM4FqTHo2E4f6M/1CYowZzzYn/kFhM3LUPeaczTLvl6zQKitH7ve6sJ4wPVDcKB4CJg1cKfSTeyAzjeed0ea8yhUV/5zFgoitiqtzhtQ9VjVXmSw7v3AuIqKn8M8riKqvLGFe1Z8d6WqVasneFSP2YUtKhgW3y1ezt8GPDsH8t/BoQ98t+yLc8wKjIsS9Ph/X2EPdrcAAkR2q4tL+yufquYnQT7x8jItR23Av1Litm1+8WU3qxnmUtBy43lVDgY8tzpIGkI2hkwm8a52JJ+BgamijcPNhh+XxjqooUcj43kDuQseO27wZU/Ul5XU95zMzutzEouZY4c5RmrVvJ/V4nAgeaaMK5jg3ms0ocMtEav1zgeBPPkZg9jlBf78Yrx+OITWHVpGHp3y23EamSeGVpsUHigG0CvZlB+iSEEAJ0R2JZhjyJAh8UsSClmMJZ1oCK+UXMokURhMRkX6u7befPI6zR8oKQgfwH27hTK7SdFYQaFNOVSidzQsyGza2cHOYGdDeR/V9cZg4L0dEoECyD9ixItobJ8lYNbYpRXPwzd8hluucK85im0Tf+O9+AE/WF1+mpV400g9kzJR8OXZx4ljeFcqzo8YEgzyrUx9liCZER1tUCd/Bb462ylsRxzOjbFxr9oFodSSCI+xZa3UZmQBhlJw6bwVRNRX5Bjr3c5YGG85imh2IiLYhpRBmjf1JGES4K8XuJ07tJCxCrz/cNSEml9/Mk4A1qiobNWpeNj9lnOcq2gZZbC8TCWEqhKkGQ+XOq3ahEXjkRVDMACSz20wc1+tuKNfXxK5xEpjXXYnvfS1Fy511q5yoYa5hrETGSguIfEBWKbO0lWonnCxCAxNwj+ZHyD9S675DMdQEEbUA3s1voRVt0PaWRem8McYEMkurXUMHF0LLh2e7jUGsMRvhW5BkOYT0575BB3rIjQDwgtfXaTstdmced90Vl7TjnuKe4eDhJECcSqfZg1nTrTKwZI4hrrHRLKa73gv7mmGoOw0BcEcvAgaQywB2RUmGkxdpu4FDe6+pfn7eYLqZYgPjXnnQ3eVIVPiaEp+/apCshUNoAq8G/9f0/5gvT/PqcaFA/m1pDdAf94blHweZ2Q5XSdlIpk0GE1tg1x5vUyzztJuF/dL6gZX0HNtsUFmjCp1WdGdZ/o3LzW6YLrobYEkNyPcHvh1+k0cRcmfcvvK+9XenZwVcCUaCzkETjexFgoBaM5G4BOygJtGaU+FKVhaas15NRIUHQY5R4KpXw5US7Z5niRUHoMqY0tlCCRvX+gk0vSOsR+gGQh50hx0vC3cOQ3WoIU4oncLGYWBV+ECM64Uvv7j1CLqTiD7Qz2LW380HekdxDJDeiz2UypGlnw6Z7YJT0XG9dVMi3uj/SFa+gAb/b2mfAx0dYcSYZWl2Bopr0G+ejovmktO7GZbUniyT0pIXurkODm6TPomYW0sRB2AUI2I8/+lNv9snubYknpwtZTXkmSz1nyrFv5S56j6XXCfvhDMk2pI88ESzrLK2KRfBVIF4pk7uRHlwqOetrp69IUXizOUI5XHLVuPzygyPvJLJhg1iwuXxPXUhLXvtONJInQ5G8lLodW1l8WaWvHBNIJxyix6s6G6pHYsTpsytKJTtClBKnPoIjjykRP2+9AA7pZPhBoC6W71CPJ3dOCZcausDVxh69VvSzQPb/Vlh18foMU4dbR4IsOvQoxSL1LdgEnyabvkFOpfopw6Zz5v3An9e8oJ05xY0VF2ouBYzM9hbqrnQgIYDQI68B8lexliWzLYUMmL4nGNF0gwbY1mcJfVhlUpkyxh087QhUnCTdY3gsTbcG4Ni2bdu2bds2d2zbtm3btrWT7NjWyfudH/fvnqu6nlVd0zO1OmDOQA235N+v6ebPTVctXkMNuo/2gXZjLOv2bXY9nCe2KCBzmWrMHbXpv/LGkiZpQmKCzC/wEzlyX0Vk655Jghs64JpUQkLsrwwEV9Mr2vvRYQm89noBdOUSqKX74tKzm9ak7GMojedOKCWGR4WMT2lLl0G8VMM/s7360aX/tYy7ur/Ca+HnZyoDSt3uJgIdRRW7arJ3xuphyM25QXl2DJyc7S3Bw72xKi856g49A5wbCfbdWJQ6s0q0cx6YQZiSQYcV1eCuVhTwGW8QQHEq/mslTRKJ0ZMJZLb6Zk35DjFFQqVo7Gf2wi4wx8u2pqHObUlpTWUsrXc+fuIrX0OeOw+GXyJzt8X+0RjaxaU1QVhjg1g6dE5b01CtNuN3CtbPibzJouQ7o52DvJbWGRz6ZHnqvfcHiaGqXaF8A2SiiXAnqEkKEhYCroAgKsPOKqBcAjbrpEsWrHILGcmI3glfSsNtybYxW64/H2fIhaQWHpVSxOYQ5pcgjcLxmYGWud7KwWtr8Cgk4cYe5ywtw6C7X2lThIjXie5d9koGb6+kXAy6ph+FXPB0zTmMjUdNtukEKjdvBwvgrwjxnf3b1yt+ZAm3UhxtoqmtA2AKqzicSplDzyvJaQM6prGmANDqrtv+o5x8nhLXvpH1TbPQww/4riKFMJVHyAlwlAlfFp3PmAbh912iLIL8boehLltW5Lw3/iajzR6OKmJXRQ/BtgSWh7KcNr75VtNuZNh951UIU49hZRvDef0BC4vXax3i7QIW+RSDydklsJ03z+0HrseibjNgwQzYN37IeyQz5oXlFPhKZ8dAHgjv8C+ksE9UtCPWi+1PLRRkCwOlzt3Q8GJxDaqKJIOhQmquN6UGVnksMBnaZEZAwBcKnU1rATzlKlpxP0i5ZkYOGLtENawoD7jXpyfjU6uPOLCqisZNmmJC2Jh2r1CudvOQ5MAAvW6Um/eMcDE83Tqkf2ZIi5AyxFw7b4j4HBq02erN6RqTnKBGfQ5olV44N8mT9alGgshBPnZkIijfyIRDjb8kmyYaDnv6EtlY8WRVblhVic+7j1Re9ww/JEnSmpdKh0cK6q62NGd8B5JaOC6W1pwNa6xxZS03rNrneqAfIpqx7/0Oov0EL6Bndy8GDwbvEFW0R1ipYvZH6dVPvEmojQpAc4I1sJ3Xml508jGyFcR94dy4l94Q8MCXzaHwDE7sa9HlDvNmw6b8Ac+J+i4ZzcETCYPahkBbkKU5MVSmPDERqvkcW2Qr5abIJf9LTe7eAKt1RlomtDkRygK874LvWAxestOQkrBOaBvJxfxn30NOs3llIrW8FLDh7CZkZNaE7L+JFPtYLMwnyXjQ864lds3Qp9HazVoXvMJYZCRGwMnY+fnOniIdNyPjmlaFfCAH7qKIqrf7yhi0H9JQF7EgW+/VTXCBio47z04a79XCXoy7KBeqD3crqJSTGT76CirkqKsI7gOtmsVg7x2e4zVAhCrFza4sJ+pTtdwRjb7hptUUz93hzzS5wS7husvVhz0F4/ioIwXzGOR2OnxhsAS+tWPf4HziJnuw+IOtFJzqDk1TRx3M0HI11YxnFb4ZJC8qkRhxrQwxRhCY6tkoLQDY8tsTWooCvELNpO6qvCT0DzzM/C5NgUlzex/uBY5Ro5bwZbZdX+VrXpkp0UTf9H0RtsMfq2xaxhQHdcYcgvYrhfgF36ajEz1x8BkXnH5L5U1yseu04JIz4x5ZwBPbKVL/6ZUZUpt95QaeMvZ/qe/ijYEL7d2EoE18hiiIyWN/KCFwJQIEzXIHFvr9XEhALgUmFb5jZdO5ZaDGEXN5wnYBhN9XlpskwTq7GFy/LhgBD1ZS+9GBTwZECD2fJaml6z6K8rYimtKYURbrjTN1guLawg4EEZgJRVfaF5ietgwqIAyGQjJO4EMA/v6JdvCqv4Oud5sk7dYXp7xD7MNx/alFOTg8ImoqQx1rEAiwtNYjLrTlXkBLY3G+JZqUpEfxOO5jXw0AvWw3gGYbko9Yrs+VCVvd4nt+mndNpn/2FoPul+N8SWff3X2RZem8FnBLVledA4DF8QiZQJ12+J7LIXMfcvjbpXMddqumOfFaB89qqekiq4NHhCKXVzpsQBRvJXoB2RzFpwqoWvyQ41no03Z9xuFBd3K0KK2D6WvP1gYqWQAM7qkBxYtQWRe0UHhUyxT27NyNUWsRQAKZr+K3XyyvltOHf/ePyKIcublh4VRl
*/