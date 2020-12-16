// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_PARALLEL_BASIC_REDUCE_HPP
#define BOOST_PARALLEL_BASIC_REDUCE_HPP

namespace boost { namespace parallel {

/** Reduction operation used to reconcile differences between local
 * and remote values for a particular key in a property map.  The
 * type @c T is typically the @c value_type of the property
 * map. This basic reduction returns a default-constructed @c T as
 * the default value and always resolves to the remote value.
 */
template<typename T>
struct basic_reduce
{
  BOOST_STATIC_CONSTANT(bool, non_default_resolver = false);

  /// Returns a default-constructed T object
  template<typename Key>
  T operator()(const Key&) const { return T(); }
  
  /// Returns the remote value
  template<typename Key>
  const T& operator()(const Key&, const T&, const T& remote) const 
  { return remote; }
};

} } // end namespace boost::parallel

#endif // BOOST_PARALLEL_BASIC_REDUCE_HPP

/* basic_reduce.hpp
3qtO5vXsZwvl2Po6140zuC5h6aX9RHNeTnvCpD2uK7YzX9Ptpl1RHi/t9VQx/ZbrhcxnOR7a/Y5VzHPo9wmXaT/036QlosfxCK7TtHyE8diwguuafupTwHWXh3ZJufYVc957qedC+j2vG519mfF1JtedKq/Xx9I/mJfdpv1H0j+SeD6q0PLvWsb1V8XfVOYzkxgHL8+i3rRv9xydtEs76q1nXM9gPrySdsn5u12j5dm8PtPD/Jv7TYln3J+tk37op5tdXFc4pFQ5f4ueZ/xn3FQ5Ltc9Mu7Lvx4u/fdxnWSjnTfRLrku2MrrKbXc3811Rsrr9LsB6s88sYL9JZQwLmjXp3ldK2km83Qv17fMv89SX5Xj7OC89dJfpjzO+zbdHD/6yVbGxUnMtw3oX+I88w3tOgHbPUd5V51g/PPwOuEG3h9hmUR7dBuof6zWnyL9cR6jS+h/qvR7lXaR8qRO2uN6MoH7H6k08LqfwvtI9OMUnt8YV1T643F+nvQJ+gfjWCHt+SbXPZH08wkq1xWavbgYR+I4Ty7G2SJeJ5vP+7EPS9nP9eEeXgcKauvrTbzv9TzzIq7zF67kOm4F8/kZYVwvcBxo/7tbqR/jRQrvN0ywMw8Zx7yI55tMif+Ix7R/l6KkhuIBz6cV2vVsLV5upp3Noz6rZV16IpP9MT5eXsvzh59xgOvPbOb3B2Zx3cS82ET/c9P+ddTvFM+zaxjHa1dxHePk/JZIuY33+Zc38b4e999D+1jOebrC+bRxfbWceeEkxod9nK+UANdTyCP0ofp1vM7yIY5XO+PiMxxX+qWD9butith7H8dlLe2fcqzheXUHrwvu89BPUzmu62lfjHO72J9to9Rvph7q7+kvz/N+GeflvIvrjFLaDcfHO552xfk6nsP6tdRrPdcRbLeWdnCb598ptJ/l9INC+v9pN/2lg/exHIzbvN9RQfs8z+O2v8r7Eb28H76B+YCZ9zO5HnLT7jrY727aRybzhF0OPm/B8/b18/Rjnvd02bzOmEH/pz1OWaHZIfN5+stszS5V3ocs5LrWx3Wri/ZJv01hvKxQeL6lPTp43dPG+1LBdtZzPHrp7ztKaRdOzmse7yPTP7e/j/ZNuzZNZ7yhnotm8/qSH2Me+p7rqMsruc7p4Xgzj1hEf8pex/nx0g94Hk+I53x76bdxXC/z/snmWF4f0/y4n3bEcgfXP68EmQe+Qb8rkPumthmMk5Rrz+/ZH+ddx/tb3s8z/jTxvMC84xzbqaBfRNNOJmnP02xgnudiHErmeVLGG/qKXRQO0M6o33aV17E0ObTnfNYxXj7N8yT918TvHW55LiWa43ecdnGVeepy7XmVJPo17SyJ101u5lEPJ69r0i5PMa4cpz06ON4V0FPuazC+beJn7bq3yjyM+WDQyfyTcfAw/c+g5QdreT/sKv0si/mtKn55PZx5wYepL+3Hy3zFxPjd/wmez5ZJnNluYX7jZ1zwMb/mOmYX1zXZ3O8AxyPhNfoH9XCXMr40sT/O+0KuK67S3heN53q7TPK1XtpPpnbe5jynXORnzY/dXGc9zvU27d5dwOs9Eey3iNd3nuF1oW3hcn+N/fZmKRLHn+V1tPcbGN/op+M4zysp/wX6DeNgJO12K+3sAuOEwyPtbdbWv5TzKv0xSDt2UM/eX9A+mT95GY9sxXId9ib73cLzSNIOtjuO8V27/k+/6W9lnGPcncTrfhVO6sf9TpxkHGK8U2fwuJlaHsH5p/yLyjnP9H+Vdnnzvdp9E57/e7mO4/ELaf87XIzjHp7/tPUS46StTOqjP0k/pH3fNOj5fBSfU6KfpPyMcW65xAeVzyPU8vx00yV623geM3DeTNo=
*/