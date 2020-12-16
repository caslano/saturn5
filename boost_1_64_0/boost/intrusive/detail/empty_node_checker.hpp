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

#ifndef BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP
#define BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {
namespace detail {

template<class ValueTraits>
struct empty_node_checker
{
   typedef ValueTraits                             value_traits;
   typedef typename value_traits::node_traits      node_traits;
   typedef typename node_traits::const_node_ptr    const_node_ptr;

   struct return_type {};

   void operator () (const const_node_ptr&, const return_type&, const return_type&, return_type&) {}
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_EMPTY_NODE_CHECKER_HPP

/* empty_node_checker.hpp
wFL+AYWaf0Ab+X5eXR+fxbFLHizvCx06YsSQMdkqnUrXKFJ9cJL2h+J78C9J9wfkTdIuLU+bfOVOmTg5b57yf7APIeOfLk1Q49QLF2njgBc9RDwqJtqKN/TLSbr8J2vZ8JdKz9Qvh25gH56M6ZVj7XnQN8d6NeMc63r8t9MJYD76qdqaYGkqr/cyxt4tPhVeHf5xxrD/TaUxzTqTWpuE+PkYiM5wlc4cK2AMtTOn/Isqja/JY4w1gL+ukzw9mKDSYcWrcl+HGSqtPrLNCmf2NvHscb12n0W8PWaBAjKg9yY1rnd46LXyUiROF+JcbsepUVQc546xgsb2it4E9Baq8ZNFnwSO7W3BdrR9ftl/gnhFyBX8XSx/L+bvKxFle2H4DNi2kyy24+s3TYgnTOwhUV9HQM677h/QRS6GYS7iwSEQu8UhxGC3Zps12SfxzfaZIuenjtrfwFWf3My0JprsljSMduusOTVB7d9NvvOZP7ad0XYlDT+71Mekn6f2J7hCrXnVUO3v5NLs1blufqn23cR2vjM2P2O9HVbdWauEM+3Mt9BY6bd1xVjuQBt3fB7qKp1zXYnUYk9spbbm8zABWYIsRp6L9/59FVKd41wt4UXxah/2VPlaFPYYa/IrY6xPn02tEOeLcWJTF4lNFa8PsCmnGQzPpohfoU1tVvvPFJuaZLIp0qjYpk6o/QfI9xzrZqujyaZIo2KbelvtbxzSpnao/T2NNnXWI/a+W9me59jUEcJ8NrUmwKaeVWl1rdCmnlA6fULa1DXS5gxM4m/NpookHJtiX/g2deSR02dTncTH5Q0ZY3+3HOwupKQRbfQ6ZVPySDFxcuG8/LBsiXgBdjB51hSzXwu6gXaXO29agXk9KF030RLd/HL7+pfaf5UVSy95HmfUtE6UnsaJJNIQ+7F1kzTdpOBy8JszU59PZJa6ZzZA6jk2006FNaN+PcTz+fNJ2y7xEtAhVccGm6jtmo4f1lIycC1yndiHzUWG+5anCvctde6950HsQWxE6pswqSsJy1dhqk6oJ8J811nXhFiVX8aDxsvaYmJHSwxzCrxH25S9wc9XatDwASNspy5VP++kV+gjRdyT9+kibaNPV2FccD7/iG5OcD71aQTkGa3i/OZovqjrEyqfRyBnw8nPI0BeguYR4JhB8wh0k3LnGOYR+ANpFBjKLY5sYZ2jgg3h+7EVbDh5P7Z30sPzYyuOCuV/VnX/KrMfUmg/J7M/U2i/peHKL630hu//8Mp3Mx66uUb+scPj3nv+9Pl1/af82Mz+XqH9Bc1+gVX3RzT7sYXyC6y6f1sof8Eh0+3w8dPufi3+/jF/XfLlhG+uTxu7N6Sfor7+inpXyoInkMu1vxdqfzvrakjbWx1Zr88PIOsI2GwBq2nrCHzkvGdSzxIvFTks8Z6TeLthLbgH1pN5BlrLPAPt4ItwENwHh8E/wBFwP7wYvgynwgPiG/eKzCPwKrxR9G+CB2ExfA1uhK/DJ+DvZZ2SN+Ae+BZ8Gb4t63Ucgocl/ieyTso/7XLAH1T64hvmkncTefeyy9sUSZJvFEPRi4UjoR0+SuZFuFbKOxp2gxfCsfBimAsvgfPgpbAITocr4Ay4CubDEpgj5ciF++Ac+CqcAt+GefAdWADfh3OlPPPgZ3A+/AYWwm/h5bCmC3uAteEVMBEuhknwStgYLoFNxIcvwyXzAMAi/s+ES+EQSDmlnuR5m7/HGerpeqmnm6SeVkg97ZB6ulnq6Rapp1VST3dIPd0p9XS/1NMDUk8PSj3dLfW0RuppvdTTPfBdeK+c70fgn+AGeAw+KvnfKOd9E7QLsRnGwxKpl9/C+vAJmAq3wBbwSdgKrpR62QY=
*/