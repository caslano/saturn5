//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP
#define BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/iterator.hpp>

namespace boost {
namespace container {

template <class PseudoReference>
struct operator_arrow_proxy
{
   operator_arrow_proxy(const PseudoReference &px)
      :  m_value(px)
   {}

   typedef PseudoReference element_type;

   PseudoReference* operator->() const { return &m_value; }

   mutable PseudoReference m_value;
};

template <class T>
struct operator_arrow_proxy<T&>
{
   operator_arrow_proxy(T &px)
      :  m_value(px)
   {}

   typedef T element_type;

   T* operator->() const { return const_cast<T*>(&m_value); }

   T &m_value;
};

template <class Iterator, class UnaryFunction>
class transform_iterator
   : public UnaryFunction
   , public boost::container::iterator
      < typename Iterator::iterator_category
      , typename dtl::remove_reference<typename UnaryFunction::result_type>::type
      , typename Iterator::difference_type
      , operator_arrow_proxy<typename UnaryFunction::result_type>
      , typename UnaryFunction::result_type>
{
   public:
   explicit transform_iterator(const Iterator &it, const UnaryFunction &f = UnaryFunction())
      :  UnaryFunction(f), m_it(it)
   {}

   explicit transform_iterator()
      :  UnaryFunction(), m_it()
   {}

   //Constructors
   transform_iterator& operator++()
   { increment();   return *this;   }

   transform_iterator operator++(int)
   {
      transform_iterator result (*this);
      increment();
      return result;
   }

   friend bool operator== (const transform_iterator& i, const transform_iterator& i2)
   { return i.equal(i2); }

   friend bool operator!= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i == i2); }

/*
   friend bool operator> (const transform_iterator& i, const transform_iterator& i2)
   { return i2 < i; }

   friend bool operator<= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i > i2); }

   friend bool operator>= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i < i2); }
*/
   friend typename Iterator::difference_type operator- (const transform_iterator& i, const transform_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   transform_iterator& operator+=(typename Iterator::difference_type off)
   {  this->advance(off); return *this;   }

   transform_iterator operator+(typename Iterator::difference_type off) const
   {
      transform_iterator other(*this);
      other.advance(off);
      return other;
   }

   friend transform_iterator operator+(typename Iterator::difference_type off, const transform_iterator& right)
   {  return right + off; }

   transform_iterator& operator-=(typename Iterator::difference_type off)
   {  this->advance(-off); return *this;   }

   transform_iterator operator-(typename Iterator::difference_type off) const
   {  return *this + (-off);  }

   typename UnaryFunction::result_type operator*() const
   { return dereference(); }

   operator_arrow_proxy<typename UnaryFunction::result_type>
      operator->() const
   { return operator_arrow_proxy<typename UnaryFunction::result_type>(dereference());  }

   Iterator & base()
   {  return m_it;   }

   const Iterator & base() const
   {  return m_it;   }

   private:
   Iterator m_it;

   void increment()
   { ++m_it; }

   void decrement()
   { --m_it; }

   bool equal(const transform_iterator &other) const
   {  return m_it == other.m_it;   }

   bool less(const transform_iterator &other) const
   {  return other.m_it < m_it;   }

   typename UnaryFunction::result_type dereference() const
   { return UnaryFunction::operator()(*m_it); }

   void advance(typename Iterator::difference_type n)
   {  boost::container::iterator_advance(m_it, n); }

   typename Iterator::difference_type distance_to(const transform_iterator &other)const
   {  return boost::container::iterator_distance(other.m_it, m_it); }
};

template <class Iterator, class UnaryFunc>
transform_iterator<Iterator, UnaryFunc>
make_transform_iterator(Iterator it, UnaryFunc fun)
{
   return transform_iterator<Iterator, UnaryFunc>(it, fun);
}

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP

/* transform_iterator.hpp
P3w1u0HyT6dRnf+boi1q6EI3t/lH/2x32XSG392M1vv+OZd5VspXWgq2sIDc3zfpJQ/KE18L0bnTqxx9EDL8FxIB+V9MicY4eT55eLTnpatZcX0zq/VODnijLl4JpQl751eXWUhrQiur3DMTSuUv0dLNQfOJbTaCaSEHC6hSxNJ+RDK6S+BJ08kDk+ckFf8yz+vVqP4L01dUDCyLPOTkUnCXTPYQT9l59VWGLePj62TxRN/Db3I5z2UWsujQRZfTlTp2vKovb8irxH+UItOsDJ8uBlbzPHZTDYOZwq0JC5QFeHEEbj49KvtSo0e0OT2dNIOWDKrb46uVG1D72lCUVhnQv1veAVs8mBSPdBDgu3qmYxgj+LXB66Lw0XeYRauGeFNgkIdcZv58775EkJE4j6IUHfz/tUeNjY4lVBHFq1XB2t8PQ///PerVyfbqR7Ec2g9sSBY4TxS/2cPj/3nUhuU6b3U6674WsMY0bY1xV1pUWgwnM+p2NSy3u32uG6UxZZ+Xgzz4meAHN/7oC/37X4/6ZLmB410Zw4T3m/X/j0e92aXKg3mj+611ZypXzHNtuofV3pK9h5J3tafj9+cak3rO79n080g/i6n/41GTK+FaBWV0YHq7YwiYDfql1xebnejtZvp7/u7qBf1l8r6SOj9YavdcP4aHGe2sDqdgmR+97D5f+zqQbTf7fuB2dM3hQ/GjD+9ftO/WkkBefviAxQLeUzCHAqncNqLwVLKKffY59jZi4DdS9rEU5m6lwS13JRlaYHx1MjdWltNH4dTZbo6mrK0Uxjol8+pkPDbzEhZaAYMgOmM2/CzWBBaO9rLUJsigvpb9oAqdr0Aqe0XQh2VLMkHlq6sKHUPOr5uJtkmmtL4qTUObqfQ4UQQ81k1ubImgTzUL5vifpF1E+BeAZdkeyZNwQXsBfCoe32dXTjp2GpLLSbFUK5m5zhn+Y6zWzkAVSRiyDkBnmlWCrMhVudHEj+Q+fVQFoznVxXebBntIZr0P4Klo4G35zVAUjfVAcVSE/+GuyjQu3a9tetiaqmxLTY7nKgnXgVLWR/f+bi52CThoqJgJqK/IYp06qIoFfK+rOcmy9uqc7LoZF1qWTOHpWOvKP2hq9NBp6sLQnRLXHmnAMHAPOCA5mZ1u/+QD4owWwg028p0UMo44JYGDXqDHlfAJz5V5cQeF00dhDqvwUbD6Y/Qohec0fByczo8eYxVy9h8FVzbMfcQpXW1TiYnNSP5Uyw4YHsFurAqrlEZghnGZA7dG5HX4HQZ1AFJH55oQci9lSZ9QR20KMqnCj7iaEXPJQ7Yx9xdKDpkKwctuxY1dS14FP4JXfJqPLld9PysEe2vefQ7i9o/FbqjjuBgavnK4U/C+2iQiItQV7ea3RlHHG6aDl0He9xekubtvrdY0Yxd6fkEYfVH4Bcyls6RG6A11Bh5DYXhh4rjgcxVlPDABd32hgwbQgoZsdBufu/DjJ6mYphxFkF9Tzy8J7DCYAHThjycEBpbFIIm94q9/y3spR5Ncw9jgg+05Pu8xECP7QSE0t7zMMoxLyJxb4XNazxo4TnRCKUb4bpZpYG9U8EEEaWooRAcqhfIyIAn8W+xxQWEbSggt4qOgRkqNAk3wmj1wFb/c7hdB6Wdku1DPXYyHeSZo5AHYdrVJwntJrsWt9Y/E5I4NNX2FK+Z1RsL0AIbDTDeUsCUW6MOnQtE19srErKckmnfl+OFyQxLci7BkdDlZsPsoqTUp9APQwLceXow3fiUueQ+mqGjBsG7N9QmIe7mp0SeePS7r72e0j8QuxSM95lIi7Z3C+5FxyKZ/JLQUfxKJY0uQwRsADVkMkB85SkyFgAsaioZZZ60zyJVpxZi2JICAEJUOy9G3iQ7PNROj9mFzvaRh6FctkNwjvCq5tWsDh8Hb8cVt7vRpWjXmEIZEMQ/MOB0cTR31Kh4B5QEr6wxHUb7ipMJVIbDGi8V9EYpBEp+med6pEppsDikV+pHOzftwOrqNfhtBQE+i0gDMr9RFRmimwvMT6bfaf9A+lGIVY9MFcvyyihlOcGf6f5+kJou7nEMcU56czuVj4dtKqW5oTYOsRIJTDLIqvV+/1xX+T+4tRWoVhHjrmdp5R7WOQNYrkiJgnIUNC8lGiIwdFTvdx1duZK3Un6Ii/iDUGmLYRn7Pf5EGREFFKgxS0cnNcdFEtoSPwyfeLdRpTGh7RBSyrGpJoi9ehT4hx9N09SBIUtkuBAkQC+dmwKryBYIiPRm5f+2z1a9cKPFP1qcaqyREWmIIefYYFyHR/ShRdgBIOY6QOx++P9miFL49QTWwOHCyU0/DO4SflkURaxF6SZneXe8mBi7/RNcAOQrYFPzci+ZEthaKOPCr5Yogl7G5M4GNNDwL8HnlYedLtoLKHxittrRZOgQ3hA2fO9r/VXBEMPOw2TP49CboJU0I+5S3rrbG1I9CVFXTyzieRUU04CavoYb0rFSFgYAyNdkMEQpJel4Zbd7hQhwgksgLdTwj+W4FEVWenw/uTAEcvN9i3g8dl8MxJprNL2fHuRrnozu0At8h+tjdo5C2Z6kItbJBrDAqCju/+YJwhAGLJxCnUL953CvNmcymbc4ybka1v+DZH3tkuYc7ky3th4h9BYN356FN9YZLatgGKUXnPpptAKl44qw1qabhdXSx7ONoC2WdP2BwaDazEHGArldsgtiDaogVvOGvf0mr8XthrEA65YQ1dTRR7jZRmMcku0laC5EkGgHJucdlxHHJ29GwHNpPVPNTOACJyN2wxeGXJ/PbRxGxv+onGhbxnDdWzx2FhLsoaKUNRy9mBB3hoX1VJLdKkkRrfJrMg2H+Qr4/NL+v8F71z+vWu+BLovQdc37ShY9PzMusWfjchNatd8x5XAw8U/NN7jSooI8lirikPOzu7KrNOHg/E1pPBKY9k89hpKaKnTC/Wkfgl+mZXqGhywfb+qI5Bk84lwmmgy8WfJVna87U+m7dfGNIBo6ileJ81W7qBXo8jvueVKfhK6vXUP9Bsqo0E8teY4AGIbLkXiwQq6XY90RbPtFu/3CVsHuJwTG+MbOS0h04aTKmemRHLGcBL2qPrBiEqEfBnaxvHWmCDP5kz5i/UvlK63a5cGODtsTlICsewBT3tvtTP6b/ToPuWSwdol/akaVtybX++pI0Tpnbq0otwMMmwdvi1w+59RnOjg+N049h71S7V14kyDbpk+BVRBygmFO2KrrwGscQQFLyEE3vJz7Ng51GFDXq4Tj/vndZ3k8pJT7TlgSQzBp3g61I+vegkRyc0M1m98snoNN0MNOXw5f/PhNSUJUQxeTKUVQyERT90Ouxg1UkF95iePymwJyx9ngWLUixEeqxKH7q4ddUV8lcdzBwTfR2+aziy1gVmuHDzIWHrE0soquq37NlgKXEZq0KGv4yxvf4U5DeAWnyj/Zn0cSzB1JFNmGP4GnPjLG4pS+Bey/vpVD4Uba/30mxVQIohYFUCK6tAGMXTm/9d8B0e8DDxuMvIUGCu1ZknPBzAAm85AUZCyeHCJfbECvnFQvXxAsDEAc/TYx+W7QyKloQj07YMkZggkWoO0Z2IkZ6L4ZnKUbkKkYsN0YSL1Y8N1aTO1aqO1ZuKVZdOlZZOu5RYqxRTTSfFLXERFzAAp0Uma0TNXQQTMyMBm93iiW6ikkEeQx/Nm1EwzZKDGQCPBzapWoqSKwDbarFRBxUdd6Kyef+BQq3qFt3BAe7iSmXq6dIi+hjKxMYqMVDl2BoraSsCVNpsDkDF074kumQi1heppe+RLIJhbhXTQKzvZgJRUIWTaDEaHxaqEdZTfAwONk2RuYndWJ2gKyEibwfDQwfnvAcbFybKHZDDnsS62PlqzEc5xDDSags7DZrQUaDAzM0J5urebJ8xW4UzcX37/VGtz+IKhXAKfzkG9WbM86+Vv/fE1YrX1M38dI2uNPWtdIO9yj5SdOu9lL3utNutDjuaCgur1JvtaKJB8nwqlklMzjfx3HgOLCRhmp82tWZNHSBRvk6qLlFXyqziLyGgOUGd9hMO2GIyUArIxXW+YhFbrjRr4jbtowACfiQcKY8GWTUkLAZKw53yErnllC04YQj2N24ZNJlo+VGkQCIPVC7J0vHHeg6l6VnRWAo80bP6o3pcpYrEtCJyuQBwTY6pd+BGeJbYS1dMDURqG575gtoFu58ENsQlw8+VzcqS0cbZq4NCNZ+ExaWYzGZo+ue85+xgkcb7uHob8fKFgjMESljS8wjS5ZhU8sg8/iTq2MUk5GX69uWm+7OnivDinbPK/ydm3ed9xqfIGsyN4cnv8gqrzIsv0Amr3wyv9Y9vzUpv1S7gNgd3atNbtQurYyk0HGime8qGLEqzAHmKAMLdV0Lp5cLk6I4xf8VUAjjUGHY4n4WLuW9fSrCxu8G9EPiU5YoDmIr/+tRR7tGY9E4G7+9XBYQv66LTpcpgFVFmz2Bi7TFV3nFMpss39WLt6zg32qLQbIlmNG43z1FvtolsN4SRKs/BRon37CYZ6iEwrqUToRNLQpf06GUYaWUdLCYXYSTe97CarOUM7xMiZaM/4yOXocGmFwmXFcCDCYDSQaJhJcT3HA8UwbmIhHopHKkTgkLL5m4h79yeAWorjx9vhx6Vq51U/FLpgJrWFGJW2le91Ynv1TxpsxipbIct0zVuGJ1t9L5Y6G3MkUlnP6xdZVXb5COB/vEXJW/daGrDrCyJfCNSHX4fpUEL/sTZbhnb3X0jWNQePUiaU1Mfk1IZcVLLKwk+aYmbTHaTQegDqrN3ne0MybUHKQ8DqstkrXO8KjO6mUutq4ze1NbsEKZ6FHXICtXml/1ZqWujVelhpe6Tra+W0ejWbZOL6P+vYd058fa+pv6EWvWPrr60fyGOLKGd3UNM/tC4zp1s7KNlEMNb3Ual/aZA1GP9MffNgHo3HoLl3WKNETdpK/ov+cSerMQTrYIjcKfuJrSdIrZL3C8BscQMLlnHrg12xq/lt3i+A57zWQqh6ytnYrjYqxttgVxLbxpVhkkivnJwbWUfiT7OBfKceLRvC0m7HTdNMfNdXQT4WzMKFHTNBvyekVduLsFRlAfYzvUZgvimOJogfc96caWNH18ytaNToOlZGqztPQ5uHCLNPzUiX5ZpuEOkCFggzMNC5P+VOoe6cBH48qfKuIDIEyqMrmcImqZulg0LqlYJ9NfRbOCTqjDM+iZMDwT90y1SwYuYlPgjl/a5dgHt/8p4usJDyTo8ozvCi6QwDXq7BrvwosK9fF8nvgP+FDeSZwJ2EAD3rZ4WSGBXBc26lOFPfFyKWS4Ot874SYpdnHP+7d1KwieV9FHVqb0VtOr133vbbjtrSXoq6fv65Dr6zro7Uzpe8fXV3Pw8h+H1z8zryGn5LclzkT2OIxZeQJhPSPawjZnxuQb+O9N4J2W8l3BdqUAsMgGRBWVPYsrN42dKvTF5xpFujfACX23VQSdTXIcejEdRPJohd/m4M44WrVqA8MLqSg2DQqa9xpTcayt3Np9ZvU5uDTt7yOMPGJaMNgS8PMW3GlfvBcVYFl7JBZtki4Ob3tKm9tuMIkX9m3/Q18tRXypRiHBM78UjMPZy8ERcPI53jAS2YexTZJQI4NqFweqwTss088JsXDAf15ZcpP+5TnAckkE66u3JZscJuQDn3Xh9Rcucpsymi1KMRh94julAXu9b6oKXQiiuApLAlMt8lgFeMcwWtwIuwHUU4MzC6vTz+OCHLSUnlKVLsmwfR0Y6OzXbngheU3iS0bwix4qbx/P5GR5VE1aihU2kUA/+/yXpB9OVMYOX8CoalN4BK1qLbHBU27VPsPtJsQi5ZQJFhDg2SzTKj0F8VWKoVw721Np3X/KEavjKFf23609On1dcjETA87wPkMwgB0pIq/1NE6tYNqSGKCPRX7EIokKDeHNF/qv53FWne3ESSMes/dQIKY6pguH0Bopwhi4mIk/n2GONPzfKYmEIRQYqycrPJz6VI2+YRCSrkB2TmKIItSHP18feX6nx0wRo1NrMqI5bffDq1CnVI7IXsJZeuZNgEHe8PNvP59RV44lbpvAn8LppXpHlAnUKsh/5cgwIyGrKdn+C5m4R+OQv8o7nsDdKTCT6gx2w+UEawF/czpPpEzgjZKutX/ZgGdhF2i8IecNzF6gKrPgNbbeiunoiRA9zXSCzeMkBmldUCQzoz+gpaYs05980/Dlsf5iwZrr5PHl5yDLkOF7z6ypbXWlfkLSJHm4jLiBsLLa32m4fIVRV5yXpr04xBvYiYCrCpCv4wEPDYmwSIfrEvbx0yisof03HCDQ3B4sQqJs/4SCCr/A9QnIiEhg4ylo96vza/q+Vpg+/0AMpWH+5eyze7Uxll595WfHCcmNcBh74/i1WhaMjAKO8JVCkF2fWqUMhBTFAZgvra5PvxdDl+EtUbmMkKIjK3okPH4xClzNPvrEgWGChKTLTYBq5R12kOtKJ+MX/csZVRPDRho3SmdmB00C4a/GylpqLs8Hc3RYWpyjnF6TuZH/1CaHX8JCdlNTgsFrL+h1oppdu+TeHnzJDlh7yhJI+Ixcxhn6Hel8x0V5SGl+Ixxha9L/UQtYb98jRk2hBMdnFd0AtFHGsyiCGjpkf46Jf2JIDNIOFiFy+/pZ4bWMcYnzuow/QrCYo3V10nsLu8mpDBgg/LGV/M3Ip1HhyuRzhJ/zL00lRf3vCCmCG06OGVeXBNatjvgwFSaEHD0k+nDhw98vqdKSdQoMARR20FYCmSy9C6958Lw2VRz5eLYMc0Mg37yP9Uv4fR/pSidwp8Xx9eUOcKhxDZu9uNGlknq18QCEYlvMqz+TD4XKplXvKv0O5PAj/Ga+VRT1WNmXEOeXldbG73hBFhUgQVMJW7f9kHiVLoNT8vvu7dZtibdUsNHnUGskPltC5raJ/08tMltzB41w+PoV+K+v91cEcenFbvVLhKjNtrrXymBmZxH3qNCiefiwhDwSgqje/de7Sy4tnCe19UWTJJL6kKbr+7d4CNvVoX7MOhbxRvC1MD5a7JdE4tKx4+MYeam/g5kFBR9mXi0/JT73tccil9mVn/CZE73APWERL2x6hgdXtZVpD4YqH1BloESznoPdlDLjZFcaMod/+7CKvHj1ieRWmCT9lGAbbxFux3qPJZN4TT4j/ktE2PfkZ7aMIVPkfbV8A32fko/JRIDsP8rnmrOzJ7t/q24DKih2rg16TV/JrKQOaJlrTgXsKry7UI3stXrUa1P8q6fg/Bdun/6xrlFTQHeTM9QQZ3JKXO9feo97LsNWBV30I6cn8BMAEMceUIpLju+RG0mWJdO2HmvMxqt8QtFylZKWw+nMVlFy9eoRMFWJHS10/crump/sOkvyOutDbUHa9WuSm5z168zm60ofYFHaTRXPTTH2qtHnJu/RTWvzTfWj20Kf23aS254PN90nNw3rt+9mbzGRFM5DZGG1tyk+QOdoCqeMrKJmxWVhIBSOS4vGsTYEIFquAFhDAG0JdNEOQNRCqL0MWGTG7WuCkpcoEs4BvjZDadHAldn7teIHd+GHLEngIvZ+jwROzm1pP1eCZBBwF60AKEeBUDHW8Cr3lleoOBzaDreKCnWEcoyfmofDHryMSiBri6LGDehUSEgnYU5jeWqPE8fBg+JGkbHopgiZEL/O5FDPFicz0uH3FdfVq2R9XYXqMXKnK7eyZz3kXnDHiXUgEPalIS0doyCmzUoq5/FQhdkyzFTafDv+0UNJUcWD+SY08/6FH/Had6nX65hESoI13c+bHKAK+/sYs7wv6gRBbNiflyfrdYjcA2vEaNjX3TlBzZxfwXQdbr0V+uXxChbBWM+VOqf24Leyf4+Xm4O+/3p7K3W28d6Cq/noNPjkFziFQOm4v8P1cLnTZ3ftx23I6eZoGpfd2l3Y+e+vzRZ2h8zch4H9BFPvdXJfWJ4qL9tVYgfu//0hh1M8xqOowoBuf/p8uEXyjA1+Xu3zGYrcDphVuoePoD/gA0fm2idVzg+HI1cDfPqgCuevhg83bIxobsZ+zr1HaDSI4IGwg+pylo6P01PNDAJI5ZhbD04UGPxYUNE8/NJnCtwpLDuTR/abLqInTRX8cgKNI/4fL3pHBOSEeMAm/Tw2cu194hZWmX2S66uCBry7/BqfZDvL//YpDBxkfpL7MS3Wp7RJaGqgQMKIzVLQoA86N9JiexNorPN/e9TnfQhZotfRHPxLfib/86hNTcyCzMxtgv7nUV984ZEb+PNZhN83wNz2/3jUlMGWjikS5kv0np1IIQ7ubuIpp/I3wdYe//Oo219fajzCaseQ5fPjgXRJOyX+PQ78/D+P+vXXz3QfiL610ykH/tej/hpi9/JWgcrWZ5Ax0faw5OKffSy5eahDPOXxeTHiGVEupzDU++q/HnWoU+pzqOValBxVmHOGruS18wkTcXQWY46+Kv7CajvN03zPrmuXwtmj4B2Vrun/etRU4XtmPv1Bk3KBL3Lb/ZOCb9xryrNl+wwcfmOzsoryisI9m/oub5xDc/hHQYkHR388Oz6bPz8K7OnMd53tcH7+rPeg6/lSCw9N32F3wftbHwyYmsH4XfOM9fEguUWE39jw1POTytlnEf4f+ez6fLs7uyICZuTWZb0IMtB6mrO6Uvfn+T1Hpl5tLzTug5acXC2fMrYu+mvGPP32ImRtPu6dxjP4XkPIVorUmvWc+viz6Z8FIQ/X5mZYcVPSgISH8MP24qzgxy3vDZ6fDlMXD6x7BoLfmXWn+0dcfg8p9ngkZKx4/HntHfbhoNIu40agcRwbCfiY+nyNwB5I1N335/5nRJPR+j/iKySewYzJKroYfE+tTOiCfnZTjsLhB2AbCTwMY9kOV4Y5TQhBFNFP2Z0dCOZxmjd7BuPEKja/cFoqi341TJCroMVVwFNhwjFKZBRzSDLuHmLhNEqijil1de5W49YgdZAifAutDFXnv2nyqj/YwCXIVheOb7VWVyuFaXJoiFe1WuqbltD9uBqzN/J7eRntxHgUysscnp4asu3ELKA+xlY0nxbDzr7JuTeiwmmc/jqjnJL6WkvLnysN+cqZgw9fS8zaODPb+Se51LW2lqRoQgn7DiPX9ahxFVlqrloZ75PrMYP3xtmWFOx3XnGquDPGORKmzGkdAaoDSR45fV+MB6JRKU4ZPLQXMONgtBWtLIQ=
*/