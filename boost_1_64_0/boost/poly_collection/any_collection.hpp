/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_ANY_COLLECTION_HPP
#define BOOST_POLY_COLLECTION_ANY_COLLECTION_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/any_collection_fwd.hpp>
#include <boost/poly_collection/detail/any_model.hpp>
#include <boost/poly_collection/detail/poly_collection.hpp>
#include <utility>

namespace boost{

namespace poly_collection{

template<typename Concept,typename Allocator>
class any_collection:
 public common_impl::poly_collection<detail::any_model<Concept>,Allocator>
{
  using base_type=common_impl::poly_collection<
    detail::any_model<Concept>,Allocator>;

  base_type&       base()noexcept{return *this;}
  const base_type& base()const noexcept{return *this;}

public:
  using base_type::base_type;

  any_collection()=default;
  any_collection(const any_collection& x)=default;
  any_collection(any_collection&& x)=default;
  any_collection& operator=(const any_collection& x)=default;
  any_collection& operator=(any_collection&& x)=default;
 
  template<typename C,typename A>
  friend bool operator==(
    const any_collection<C,A>&,const any_collection<C,A>&);
};

template<typename Concept,typename Allocator>
bool operator==(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y)
{
  return x.base()==y.base();
}

template<typename Concept,typename Allocator>
bool operator!=(
  const any_collection<Concept,Allocator>& x,
  const any_collection<Concept,Allocator>& y)
{
 return !(x==y);
}

template<typename Concept,typename Allocator>
void swap(
  any_collection<Concept,Allocator>& x,any_collection<Concept,Allocator>& y)
{
  x.swap(y);
}

} /* namespace  */

using poly_collection::any_collection;

} /* namespace boost */

#endif

/* any_collection.hpp
1wdU39o1D/2TylGz+q1FOk/9/F6Nz57SeGt/Wumjfu68UaXznyf+bkz14jiNgz6o9FA7vUXjuL0qL6tVHl//ndoPo+IxTf3dQdWXW9Uv23Tc7QqvWeNtzdeu0zxielbpsELjmBNVjoc0r9S4Y2mv6vsrKodOxfv6iXGS5jOvqb29W/2ISe3sCeq31I7vWah00XHXaf/qFp1/n+qN6sUmfW80K6xypvuee7zSb7Pas1G1mxN/J/5u9SsF3VfbW1VPlw2q/VW5mqN8OXiZ5ruaf1apvq3IqN+P6vneNJUX5eOMN7Rf6fjCsaq/byoeqvdrD1N+FVQf/UqPuRrPxJWP31O6t6p9VX+4Ia36mVO79X6Nz6yqH1GNqzZqHHO76pHa4dc1Xrn8p2oXdym8T6mdUPpfpfq9++vKRz2PqVK92a526nSVq1Mt6mdPV36ovd+neJ2T0O8BVC/PUTw2zlI5KKvdaDy0vXKeysUXtTUqf5XPy8rKp5cUf33PeKr659OfVT+sdn2xxrsnKV1XfFPjF83jFyjftiq/X3hZ7Y5D56u+bD5c86TDlF5K152r9Zz3OY3v5qufsKifMCo/NY6fNTHv1nP4xUeo3LapnNyg87fpPotUTwfV7qndXtSi8bK+v117rdrBrerH1I5e8wWVG7Xje1Q/pisd1ysdZ42qv1Z6vH6U8k/teJXCeb3GSxvVvx1Qf7NV/cq9T6r8PKT8rNJ5D6p8PazPFY7VF+v6Dyh8yqezz9DnJ6iebVZ8lqh8af51nvJjs9L/oPqpubtVzxp0nRH1O0bFd4f6w1N1nft0f7Wncx9RfdF445zPq3xrfrhssdqjgMplWPdVO7ti4u8AtqvfaFL5267x0DKVg71qJ9XO3rtVnx+v9iug+VOd2r2J3ylr/rfo5yqn6ifOKem57bsmyonKx77n7rvoNv+Zb3639+Z7bpq5ZdlHrrvgzc/8acOcX55/4jPHPbdy7ZsPbLhw0fevvuSD4a+e8NlX2k5IvjJ/5/Evpr/9s+7HbjjxzbqPfWfvKRuvrJ3R/LeVxXPb7F946FcXrfnq8hXv2XPWuqV/m/ejuX87dUH/5x7sf+XRK+9InF9csfPEhy+89OJP/uFjdXNvWpD/0sbSL57yrvvRH1567feHf+7hixvve63+Xede+NLCzcYr7j5lzY83PfzQ7/pyx93/hqXpuzd99LN1j9/ymY88X37kZXf0ufI5nzy99eCfv/O5ffdd+dLHv/uDjt98Pnn+pTeve/kL9w4suX2o541r0+v/ePUzQ/6vnDxwfOzlkdMO97fPaWo071nd2Ff74rOW81517zjjxe0ritnv/GTgO+9fUn9y6oZ7Fx3z7A93f7pq6W+6Gp5d/aVVWwpPP2l9/PcPf2rHw6XOAzuuf+6YJVtuXnzynT/+eNO0uP2OrUdca9hpvz3zwfRdG66ac33XPXPXffLX3zs8fs97f/mp5I/Xvevj2z+2pHrnA69v+cyzyaf2P3n+p2a/+7JX/vSDD7704MvFb3w098jhP9hXdhYffei8mm07bJ/Y+vQL6w6c+mDqc88Uut6z/sjhtbEnTvzM1475VPPm1af9pnaN9ZTuH5lmdGUMLZ9MX/27u7+09iHfj8+6Y9ujA57jbj35jcevKzs/uWlzW/mhTb9Y8dVHZ9/VsKv78B88cXtr7tqrVzduWr654YH8zz5xzn7v0LPrdlWdbZ/98uvf/ebeutJ3P2nQv9pJ66a/1ZrpAUSRqFgzvYx6ClMLuqZYJ90D/6R10vNaI70ODRXro/fDimE4MYpYxZrpRRio22ZY0IRWdGAQDngr1k0vVKyb3jhp3fQBDMEOD0KIII4UshXrp1c=
*/