// Copyright 2002 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software 
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Boost.MultiArray Library
//  Authors: Ronald Garcia
//           Jeremy Siek
//           Andrew Lumsdaine
//  See http://www.boost.org/libs/multi_array for documentation.

#ifndef BOOST_MULTI_ARRAY_ITERATOR_HPP
#define BOOST_MULTI_ARRAY_ITERATOR_HPP

//
// iterator.hpp - implementation of iterators for the
// multi-dimensional array class
//

#include "boost/multi_array/base.hpp"
#include "boost/iterator/iterator_facade.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>

namespace boost {
namespace detail {
namespace multi_array {

/////////////////////////////////////////////////////////////////////////
// iterator components
/////////////////////////////////////////////////////////////////////////

template <class T>
struct operator_arrow_proxy
{
  operator_arrow_proxy(T const& px) : value_(px) {}
  T* operator->() const { return &value_; }
  // This function is needed for MWCW and BCC, which won't call operator->
  // again automatically per 13.3.1.2 para 8
  operator T*() const { return &value_; }
  mutable T value_;
};

template <typename T, typename TPtr, typename NumDims, typename Reference,
          typename IteratorCategory>
class array_iterator;

template <typename T, typename TPtr, typename NumDims, typename Reference,
          typename IteratorCategory>
class array_iterator
  : public
    iterator_facade<
        array_iterator<T,TPtr,NumDims,Reference,IteratorCategory>
      , typename associated_types<T,NumDims>::value_type
      , IteratorCategory
      , Reference
    >
    , private
          value_accessor_generator<T,NumDims>::type
{
  friend class ::boost::iterator_core_access;
  typedef detail::multi_array::associated_types<T,NumDims> access_t;

  typedef iterator_facade<
            array_iterator<T,TPtr,NumDims,Reference,IteratorCategory>
      , typename detail::multi_array::associated_types<T,NumDims>::value_type
      , boost::random_access_traversal_tag
      , Reference
    > facade_type;

  typedef typename access_t::index index;
  typedef typename access_t::size_type size_type;

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
  template <typename, typename, typename, typename, typename>
    friend class array_iterator;
#else
 public:
#endif 

  index idx_;
  TPtr base_;
  const size_type* extents_;
  const index* strides_;
  const index* index_base_;
 
public:
  // Typedefs to circumvent ambiguities between parent classes
  typedef typename facade_type::reference reference;
  typedef typename facade_type::value_type value_type;
  typedef typename facade_type::difference_type difference_type;

  array_iterator() {}

  array_iterator(index idx, TPtr base, const size_type* extents,
                const index* strides,
                const index* index_base) :
    idx_(idx), base_(base), extents_(extents),
    strides_(strides), index_base_(index_base) { }

  template <typename OPtr, typename ORef, typename Cat>
  array_iterator(
      const array_iterator<T,OPtr,NumDims,ORef,Cat>& rhs
    , typename boost::enable_if_convertible<OPtr,TPtr>::type* = 0
  )
    : idx_(rhs.idx_), base_(rhs.base_), extents_(rhs.extents_),
    strides_(rhs.strides_), index_base_(rhs.index_base_) { }


  // RG - we make our own operator->
  operator_arrow_proxy<reference>
  operator->() const
  {
    return operator_arrow_proxy<reference>(this->dereference());
  }
  

  reference dereference() const
  {
    typedef typename value_accessor_generator<T,NumDims>::type accessor;
    return accessor::access(boost::type<reference>(),
                            idx_,
                            base_,
                            extents_,
                            strides_,
                            index_base_);
  }
  
  void increment() { ++idx_; }
  void decrement() { --idx_; }

  template <class IteratorAdaptor>
  bool equal(IteratorAdaptor& rhs) const {
    const std::size_t N = NumDims::value;
    return (idx_ == rhs.idx_) &&
      (base_ == rhs.base_) &&
      ( (extents_ == rhs.extents_) ||
        std::equal(extents_,extents_+N,rhs.extents_) ) &&
      ( (strides_ == rhs.strides_) ||
        std::equal(strides_,strides_+N,rhs.strides_) ) &&
      ( (index_base_ == rhs.index_base_) ||
        std::equal(index_base_,index_base_+N,rhs.index_base_) );
  }

  template <class DifferenceType>
  void advance(DifferenceType n) {
    idx_ += n;
  }

  template <class IteratorAdaptor>
  typename facade_type::difference_type
  distance_to(IteratorAdaptor& rhs) const {
    return rhs.idx_ - idx_;
  }


};

} // namespace multi_array
} // namespace detail
} // namespace boost

#endif

/* iterator.hpp
/dJKf2sIFzAA+oM4jCyBDBqRsyszU6tFHL9WZ9jp23f64kVK0PPjbA5F6H0amP4hepDbk2suhjoVq6qNhq+zFUmjJ6L5aQm96amdC8DN1ZURQwuzOx+B5XaRPoXYy/e2Tt5gwd01nOSMzticvYxhLSTjOJwJ5TZIhyH4pK4POq4pauqXV9/WtV7jbQIsE5cSjtm+hhui2/Hi5ooY2usehcbeGfIyPOPSFrqbuKSUrtYmTn2pq15qM0XdZdBZP7sTxQY+6b5PqLLxUvltw406v2nXBO2hcZom9B0oX1WSYk7mSe/i1NvbaWpystT7aGMgE4dUvPo+lwA05X63pcUo78ui/SNQOSpFI9HKAlh3wMTde8lxigoKfEVW3KP1nbSl3IIZUxNZk0n6basNsRLw3+vHbE116EXa2Sxsra7l+Yq51WG98FtAdG1erm+n+UIO6yzdfdt5r7vZe/z2Sm1k5UCeO2fKXjn7TUOa6z9GvEPwpL06QL7PxfRrlq2DwoOFbRxwNDbitEO8u6n204gshRHD8z24hVq8OQqpGXXfwRUZCr39ISwm4LFnhbTT0V5XkIpShlnw+j+mKR0UmNmjzDlE5rP8OHmMlFhp1tB33IMruI+DXhSwlN5Ed97dpVqqRNKojYJf1ZwvFPV8hLmrJ3Ox7pu+za46O458ccOjSQmMnjURbNJwpGisnhg6DN7o88BzRXEMxcKoWYSeN4SFIpLx8542DN9wtJ/vPeeH3dytplmnBv4BPeu6Fv85Ogsl6ktNfBetwwTQtrgYQbKlvNgrOKWrJDolj7t/fGHH7uUKPfiG9DdV76CpG4vzqPCB1acj6rvC+6cl+2MGW5vas2UGU0J3fVphe7wl3+sxyoqq15oRR15SWsQY6QtkZ21RQ9lMVZRNtmw7WSlHm3xXw0dHkLKyM+6+/oPvNNxAhsWz0PuZcH8S8HBVfVG0MElgLRWtt11Jc2DKQixKeejNbX064VFqwogZpa+mPzoDmjX8W9Ss+xGy61+1FSUndjeiLfMic+PtBfOFFYplpUXMg895ro3ARx934T4YGUnqJ0QHoyTYYS3swjaoQdv/blSbe5neeJi3PX31QPzRfUhjhqNpaXyAtkZEVTSfRR1LYVc2CtzIvQNSzGpku2JxoHlLKzpBOJaGRTz1VZOj+1LFr685yAJkzLx1tjJ11q5VetJPJOu62K2zOLx2WDOSpTsEwQSs7PBcCQe0fmHFrvXcQSv5QGiQyi0ExAzne/boRFfF4ahXThSppoCBpPYmykPSLtEsUyQXfbOTkHIecgkytIDv2/vPKQanfiSo/ILryxuU+IXKk9LIHcZMC6xPkCUITPUSGLge+dxDme4RZGj4xEBAm9JyIiSuNhIlg7S5Q3fxPLHAaf4RbzwI53ig/u2nO5O35XywjIj0LpiK1qcCwXos8n7rcq8eViD0KxCQ9+bz4AHGGes7AingybvPdWPHH6pmJsxLGiIovWa0qNRSjO6jZhiKOcVZBpU5UjDgiy+1auTkAoi7x0SoRFILqeDZz6P532tSxtIx9K3GDXvqltbTH8a9Sg9WA2qs94tqydfHPP8eJecO5Bwzb/T53aW399V8LjgiEDUHC78KMdqMq3GCKgo1YnZjbqdsjwWd61pZbsZMSUgLwP4ccwSwscX779A70cM8iWWyzMNOLDdrfZs8JNcRw17aLWQNUipG/NaDQ1+TeN5dPkqsL6X/iukmiBQtXkp98p78QMDEBKI6VHGEySKLWFYpWjD+gAgW+0sVpE7itDyKko4JxBeTOardFNdErlqGpiHTPl3lV0pSvYjNNuAGIA29KEveyLjYBqGAizw537V6aJrRlw1vTUYYjhE93MPWqWdotyBUYp5LEi7/JCgrwUMqlkibxSmvRJJKqqkZ9blu80KiCSW4U9xPBYz/uaTFnPEfnfbdwHQhXL/fk40E5fCub/x/5Oeugdlp4e/vLIx879+UPellQP5IcBDIL9xDP2XPLOb7eLThHd3UdiOtN0Jq7ciiiIEBUuIP9x701XwuTHEVhAIsyVEx2EcrOxORt78zrXfbkufb2NvvaZyvPI2Po+WDm92FARdKmdrU30L51dPi4FD1Wj7pVKDwn0jdP436kplYsQB5AZrZDnEBGyXiS7bu+slKgf8yKbA0CWyGmNl9UHOHJrz11RjeiLXMdnQ5BMM8CDYlplHwCom5caXGv0+sxLTijsxWgnsmkyrhWTLLRmlN2krXzXX+A+SMn1hax2uCRVsR1uunPshIQ4Q8VUC0IQFwOKn3DAkBAGJWI8J9UpLoUJnhpKS6L4iurzdvDuKXywLo1m727lBrguZrrZSnDlVBI5beUEE2OjBk/fuv7MBVqbMkYNRWua2f9v7OUjMzED1thoePM9v+xBI6wURqMWXDVpc/n940wmGmhPyLov7Ek/JyiKGlWYSU+hUsjYCmIPTVWSRvJvIu0NRK7m7qNFugsxYA/GqD8rdIHUk32zBNgINkIbSYt9mo4+4LYy5CTC3y19iNhfzBA2e6IdpEQtCBh1lqxYN427x8oL+uAUCTbEKfBOKthH+M4Di9znIgf5X9f9U2Iw4M7O9WYSh+rkrE857agz7s3IYnZXMYx36C0BmjaA+0E+uGzYMBxsH7aCcpzOXMArsbh8ys+mZa/OyDNW1R5gEs9ndowFZO4rOppBydaTRppQJk1LKqDLk7X2njU6ds7e7aVzK11dR9nUu0lTkpvkwK1QNlYiQU7/3VjBDflHrMPkuwV2DpZ7ANHCBvsh9Q2wnzrq1eBU2bY2/0fXLNIPSBdylJ3eqZrY3DGLO9ZPK5961SUi4T7roEdsuNdHfbAO5IG7HkYStUgl/lq+6DNh0ed58hxYVNR6Rcd5Xi7NRaA5IsWED6RxmPEXbZYTu2+hiMzWv6uQB/GrLqBArSZr3o36aT98qha/13JyJ3O5r6whFz3D0Vt4HJw/a5LZJ41hLnT6NED4uMeD/OsHxczVlpI9S5e3RNMZGqv4v8sBzfcPk4J+FcHwwPHLGGUkligZpSIlbVhBkGZUiKCaq8yN5NvZmgm9A/sfcBbvpEh74yeqcXPzroplO/WPuNVizEywZ30HVUSENOF/jOxM/R6oc6lhA8NJkwj2qguYPLCqL357WDltfT1txToVBCMvn9p9+UvLeViB8H2lBf4dmXkJeh/ks4M/kLVX4Deb02zJTidEtVsfryEZrY2ub6qBwuHWgMQ2wRyTHDfQt09kzmVwZOe9seB9DrsvwxPJAMMx+XaxpEzWIcBIxj9v7ATm8BZLJ8qzRpHFr82accboPafK1CWtKcVVPK9bMD3wqn/v+1iPZO+OrJGKQiG7VpUAEznT4r8s1iJyXNdeQZ907UJr6tHQRfQl9ag8bydGKLX7+0Dw09O7Nq/3/QSiduEk95GVzIv6nR47hNRsavyIFGjuDR+cymVxl3wakYYRVI4N9pjexLTG6aayV3NLPILBioUj7vHKfw62X8C3ioVtXKMsX8CdY/NflHV9g4cWVciABkzTRyxSUjSAw0ozOQ8ERJmJjAEyTsRJZXHhMmQLUCNNlyasjCKR/4NUUiuT/zFvdXFvWfs4WBWpOqUzCLGm9yy0/5GN/WY2sBb6MFmCGUXmjG7/SPykhExMRAK9Ekf8IFk6j94UU1jDpgj0BhGZ1MbvORFxmPyrFK6tbi3JMfe2ClC7fmBcSCwEFkmxyWg5ROBoEx5qe+90ZjRfgA3B/ygb5bLVyuf1aClDT+KCWh+oZtsrWnJ5bFr1tNCFPYtR8tlj5qVhd9JBmIbfYxbooE84T8jGM1J5OrnmVaqQKm3HmtEqn746UEGmaLUUfYks4u7c7fz7S9rU4s2irG6CziwREPCa6pt6KP4GYgd2QHvYVBSRXi7GpmwcH5dwiqzopiUR2nU1O71wXl+R7+qgOTBLKKCyf0lW4kDDvyzq6SQw+9QaDx6itQGlhrg74GiDlYRc8KkZ/tyhz30Mhsap4J2gr+/lPsHm0MabW89Gv7IRkmLCaYjQx8Dc4QVpzzakMZf9wXNfQvGt184U1Ll70qE0ssgGnld7dCvbbyIXWlutaqAu2Hw6hGsmZnbyQnPKEtQdVXlhLzxgf2PYqQWbmlv/TozudM/MgAlLlstJUZeKeQH6k+JOG+gMeX6gxCI0jIY73PvoO6XK8Huq914Y0qn59LYrM+4dQJ225K0dlN4VXgN2QGmifE6E0orrx9u8TRC/gkPbOC8raaXdxDpR5n+h3otIxsyUVHmDB9rZMyyQo0MV/rs27zq7H254UZg+NqKXgps4JKkK2G1DMkLYqkSXzuYLtRugpxkjBrAXhOmiw4NfGz2nRuvR5gDIKfG/TO2eHzxf7BovEjAn2SBLtA0yTulvMhIwF1mqcfNO/aqhWJnQYjB8quZZJ87qqLO66dk9vic6LMx4czPznIGACGq5i5ptGP9uN8L3+Lu/XekJaVELggECZbi4BvFReev8V36Aw6f3bT+uY0GQtcx9PEe2AZCwjsAybjTxXSDS6R+gJX4wKP84lidMb4UM8LKX7NCm/GhqQW0djQxF2Pbonr7X3Fq+NHHlsiR6fqVP/QQQ7CEcy9r0bQ9icjz0B/9xZHfXwGCAt/HaPXtMHv12hkbBJ4Rdk+VFwvTtMkM2wkgpcFACqIQHq8KIggIm7OsguKowpFCcTZeo06mMTgbLAeg54pCWgBB2HBaK3wol0FHgZn8ufCE2As2IJY8+hQ42KkSierZdeLvzlXWPySYjTLBtniTdspjEb5NHtNHWOIUn8VwoLMF192ZtGtBKVAq2trDgLWelcXv12qk3UnCB1Hz0gJX+pB39oWedqsq3YQM/BDbU174D/sXF07BnrmlMQzh/d6FQSUuS7nE1Ckq5dhTh0uuANe6WzxJcmLrjh+fQFrm97e+C1R1USSTLUtXdTPE9Bf5So+SE7igan8PStc/tLR2ROzdxzBY56GnaxMUtsqRlQyn7q/oqcEg+e/mEfW+CMyR7ijHg9U0Z8HF2tvaleQvM193KV4+a/eDur+PkhiqMpVoDBawtpNnpNH4xlFHup4lyaLrn9d8cyfaftUvejBM3gnHlrlAoTFzzvZqSaXpoxQc3YiWyWqVkyWEVK9gSEihmDp+ALwEKZ/07HVBzd0T489/FfKIHeAEnp5CoSBIGUiL0ifMQKrcR5u8pZ//CIUbgq5SLVEeXNvB7mxZ4CpGRZ7zpR70WjipATRCTJiZo5Q959ejV1MXAVSVIxqQPqjJHxibOeXZH0fZIhphdFCb2uYIPRg8D6O9nCexjXnJq6yNvi9dUePglDJuOOEFI2odhyg8DgKQhLXEQXvRHDgpsXjsRWL+blz0zEvH1dKkUrGk1uxQOfxFU3vkO/ylqZlY6Nwv01xZGCyFS0ojH+Qbj2/q8cmFIXE+k73zaW6xP20qOzdpRFkNVybNcHeYjmVgdvshMQiKpULS5WbQtEj1IKKamFeBvDG9Ts0ujHA/5KOcNj5mLWl/hptKwudeifnc4KcSM+8wQWOvNgy/lJLR6gbvHSulQWoB1HnQLbUSlYHoNJqLdcDBnr1i+Z4X1rB1DBM8J2Jnrp+hAe9u0hUW1lua/1QjyCwE2rWF+G3MP0MbIrJ6qh/d4iJP9Sj0xRK4ni8OniIxl471nSB3y5wMlbHmqxje9y1V2qlBmHVNhPO0zevpYgS6V/dy1ieJ51jtPmTkaHyemZoATcCwqiBI5BcKrEI+yxKh3Ns6wNPoS53zs3B88pQcVnvibgh0/0gMU+zBOumx2DYf29GxfN69tb+svA/u5x22ObDc+zZMOGBCiSkgim2tPol+hdxX5oID4UZlTdx0AVJqmLOh0T9vfjv4Kr4jsUFiYyKahprY46ipp6lo3fxauRNyMoEuokY8q8XCjqrdPyvz9+f7aEtvLy+21sVw+e8/RVcUjLZ+YA2WqYJB9EqIPOtYKoHufF+6ehl3wrt1HLev+yOLjIzJ3CPSxt5HsOqQjdOrAMDzNnoY5Miwfz6ARBFhRq7u88rz1lNwmafeOU3ujZkwUxVIMTJcr9oug40RVn0QRhrvJeuGnqOQj8D8EnQKm5KFgEFY4UaL5qFJVfhIJ1yaQtLk5vojXChRU9uEiNUI/v3+IJ5xAXkY29VHrWxoAu3IEDQv/lG+XO8fLffRBvk2JIRqSrV1MSXN9P+KIS7VlTtxRcmrFcpm+ZYA393RQVYBhgUdVji9ui03815tsDznh85VKm+eHl9qH+O7W5K7vbHFBesQGYbvNI7c53+mAnimJvg31bUpLSlbCudYj7yZwjZ0B2BPvzuyj8tN8nMEwrn+UMsWzRaMlHX7fOWHXI/k0kPkBm7PL6Q+mRa5+TDSvvx/I7g6BznCwvRSA9Y0trzSmc/B+wK6Q6DxDHXX8M6Kp5FOEvUt4hoTNQuYTWaDkn4VwgHONGw1uQHsYH1seISP3Q8XqqYu+9l6uwYiBRR919iYPZQrEyY89UGUxrjEYv2s+KWv6pop38yuGMN1baPopQGLxZsu3JHsrmHoux+QPHobEsrh2yKzGxB6AL1KGUK6EQTX71uLHyvixXrICLfKBXC5BfVYwbR763rqENp7WcEfPpICXaItVeC/fYh9Tka7GyPIoOCx2oR2Iymb0FJOd8iR7EAg1wZnXoHLrMm1/kF4bn9Tu+x4pSexOc1FeSX9p6j377m4sb1q6pDzMw2BVI9JlmwxEGP+rZMldjLMyF9wdjzbBtKuYAG20dLLA0HM9S+cRzjtg18+PjA4l/QvvNuvGf467RKd9Eo/AqKc5jCP0LAnCJ7XzzuZJeojCyIDrPUFaBJwazKpLu9hEQOVLl6/0rXTKok6WWcUk4Yey/DnuJxYkG2KP7SYd7SbwbFs1Up0vIeV4NMz+yX24K4bBgm+y8bR/Eqn/+5jJ79vACFDU1264ORAgTSUVMyOGb0iGhsJ7CwsOQXORQt1jdg7CxCeQddmex/FKhStwg4U7g22Sd9HWHfcdj4PnKGgU0aEUY7WNBnzB3r/MRvhD69XAqAA2mPoY4NnFk0yTKOJclz4VatMdL5RiOFsICIcEmRJVrZpuuF7GAl+0VOHaJocCpAW8TROYqk+vs20oBG1gQDsiB7+kOsKd56J6575WaAm8eKz5Bja6VyXzwCHp+2adcPFD9xjWef8W/RRiF1nbJhpe1sSd3Vcdu/7YPV2F0+EmPbLyQqccH62cKcSAw3P2fPfbbCXLChOJM71bmErQbon77CJMv8aTfh6adz/bCbdpdbkcksVlg1LrUT3N3heDODuH+5Vxds8sS41G1xfncHbq0c9T7uPBiov5spGK31SW043L89V8NWogqnJ+nwHDa2FZZoZ5SB4z4OG18bA9/t6paK1IBcz7vFeJYRGSu1OdKMRPzZuNLTcFh0/JprS58TAAmA7p1uT0VVZyGG0vSrU/Dqi8rhwGo60Bwcx3Z2Cc5bWyphnTBmGhPbFs6uGGu3rrbdWIOsOVm3FSa6kccseBqhq/OEzglDlb9tO5lbqOdEKKfSQu/e58hELX+nK5inH0K1e12eoHLM79BZcT3Y4ozwGfLtHpo35e4aGfYFCYrJ4/1Y6VNnmXc9UI2a0NTuNETq5LfBZBbcjkBPSD5u2HGNpW+PVCwFXxRRn0jMbYlqBi+Bk5u4dKom9xeYlhj3S7Zo+TOy1pvegenJ4NoeWSrXZeNmO/J76LGBpcWeoM9GYmRYL0XAunGt0L/PnXo6dYmc4N1ei9LmsZFrZNUENnyHTM4wcR0kj43bmLe+xkTqasAteqzLh+Hq6tFOd6iB0+sPjuwV3fHbpvb1IldZibUYc5vo5rkfGr1wG1IBZHnd/h1xes3+sf/+1+V7tyv8LALgae8LQPma+8PQ3ueB/uJa+/+Azh3CMlLI/+8PYznmCklbq2PIEKIimQSCVkAW54sglEogxchciIjxePF6opkuFxjFlKKAkBEESiW48UiZLhAYmYuoQklUJ16zvPi79HfZcW+7GT4aTXkZ5rkZvE/XG09/f6uZLRIdAkp08cnQ33vX1pT37nTzQtvhMiGGnRx2GC6WEH4fSPBw2+6+0BxbgqgSaLS9EG5+MafGlwWZGrQ1mlPeqkvUEmpf0TZ7e8TrDw9HpgtIy+QPJswbiPRMzB/0drtlY+YrysN0EiqViDEea5b9tt8R3jLCj3U7CM5qZZWtSzFkVjQOd/diqz6EsDzPqovIDY/54DOd0MFdVc7MP3kHty0xW7NJzgk9d9cVejTwTyw73Z3+vHtes7M4rdgPQoWuvhS8yiRIMUNeqZ+QKNptjTZ2lDfJ0FAfHi6BFxUN5t0fnDOzL7tWvjfbK8RplgIZA8tpPt4ULj5cnmmc8tMyMFnFdq66moq7dmUtU5RkvwTUCRIxZ9xVvMOUxARxgab8hvhKWsN0ORi4379WyXVxa5y1GAP4mT0e/4zQNp+kEEUItFNDRZXLRaIZbu54rMt6e5LZnyp/MhoP/okvMJhreLtCUWkByCKMJXJEIRxYvDgi53hF26gvXUE6Orq2N6vyjC8Qok8oSH4M8LvRzj1CGF4Hh4N7kIMjhu9Z39mJ5wOD+DRWMOxkWTdDRdI80gfdYx/qYoqZ2pORIoSCn9tr2pteqhjX0IFMFQqfyUZR0nbspMuoZykBjXG6tTkEGnuqSO818Cu6RIXIqGGN7TWsz4nhtbafJORsQGwfZQC2TX6BcY24Fw9N8lw/NoMWcvegZmmjPHIO3AhPGZWOi3EFFf+mjDG7EFqQAcObBa025SNr9Z9kxU1zBpS3+j/z6/QFHey1xDsFEf+VrcEt5QHiZEDyAgIIYPvj8Wz0Wihbmxs7xzIf1lzh11nz+n+YNh47z9rQeizvmL/veicPDyhgo49nRmsI+2vrz7yChZOezoPRkjEiSjff2PX0FKyU6o/6E68NKM5C6a7IhDGyvGJ2bBS1ZfTBVTAOIZ1fwOklOs/Z5jbb3EKA9Iq+1sZw7eCj82CwX1QzOI4kEyoCe0a6mWymzSL6DVIv2QOjCiFa2Giu9YYMwUu03o5HSXJchn8/51bTeCB6qc01PQ52anp3rxm4OJg+yTyu0qLH/Zd1dhdcrrGUVrqJt7UHkm3ctnZHnE4D7yL9D8/Fq0hIeW1MD5UH3fAfGLPtXDkUb5wPSv4ZkJE=
*/