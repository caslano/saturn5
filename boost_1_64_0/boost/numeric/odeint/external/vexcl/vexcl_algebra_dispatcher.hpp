/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_algebra_dispatcher.hpp

  [begin_description]
  algebra_dispatcher specialization for vexcl
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>


namespace boost {
namespace numeric {
namespace odeint {

// specialization for vexcl vector
template< typename T >
struct algebra_dispatcher< vex::vector< T > >
{
    typedef vector_space_algebra algebra_type;
};

// specialization for vexcl multivector
template< typename T , size_t N >
struct algebra_dispatcher< vex::multivector< T , N > >
{
    typedef vector_space_algebra algebra_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ALGEBRA_DISPATCHER_HPP_DEFINED

/* vexcl_algebra_dispatcher.hpp
6FPi0tKfn+Bpqu1OEat1hPH2GGqkXKcfFH00JvAWknUvBndcwcAw01NJftPiBcNZ6/LmsMM41VDCR6gAh3f7FCInQsDeZPFtxzse08II6MhfTMtSdIEMtAYItEQe7yV2PozclhOUSCXTPiKuf6my/9ToFPnh6WeuBvc/FosrCwBuv3URAu8PUsgaGco92ifgzz5iJaUmYoI76ddv38Dwc/DBcGY1AA1hgPbXtK30oylitkKp2/ArFaceBsOPQBDaZdd7hlaSem+AWc7ZG0NHraszVMVo3b9e3MIEANSBujyir4PYXnLEMxIkTH13wpAVv1I/OQgUcfXuw7T/5OmPblD23AV42nuSceHZntvEM3gUXEtqJ+VZ+FsuwxGbZiMf1mk6mgCVylSpaMX3X0FMLTfpjpTeIR3izSCEhjyVRR9oV7L53YHAjZTSgD8GmZXde31BDk7vRh5Z3MFgNcYVdWvD+C2vrDYnssuH6TSL/tJhyNXWA/tHuYNBwSgMvbc2opSUp1lYODY+4AqpIhsKA/4v3sDonvUCAVhPvuiYVczEj05eM7A9pszr6Q==
*/