//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_CREATION_TAGS_HPP
#define BOOST_INTERPROCESS_CREATION_TAGS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

namespace boost {
namespace interprocess {

//!Tag to indicate that the resource must
//!be only created
struct create_only_t {};

//!Tag to indicate that the resource must
//!be only opened
struct open_only_t {};

//!Tag to indicate that the resource must
//!be only opened for reading
struct open_read_only_t {};

//!Tag to indicate that the resource must
//!be only opened privately for reading
struct open_read_private_t {};

//!Tag to indicate that the resource must
//!be only opened for reading
struct open_copy_on_write_t {};

//!Tag to indicate that the resource must
//!be created. If already created, it must be opened.
struct open_or_create_t {};

//!Value to indicate that the resource must
//!be only created
static const create_only_t    create_only    = create_only_t();

//!Value to indicate that the resource must
//!be only opened
static const open_only_t      open_only      = open_only_t();

//!Value to indicate that the resource must
//!be only opened for reading
static const open_read_only_t open_read_only = open_read_only_t();

//!Value to indicate that the resource must
//!be created. If already created, it must be opened.
static const open_or_create_t open_or_create = open_or_create_t();

//!Value to indicate that the resource must
//!be only opened for reading
static const open_copy_on_write_t open_copy_on_write = open_copy_on_write_t();

namespace ipcdetail {

enum create_enum_t
{  DoCreate, DoOpen, DoOpenOrCreate   };

}  //namespace ipcdetail {

}  //namespace interprocess {
}  //namespace boost {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_CREATION_TAGS_HPP


/* creation_tags.hpp
SJlI2Ui5SPlIhUjFSKXI/xg7C/BmmiKOF9fbw93d4S3ulFKgSD9oi0tIk7QE0iRkE9zd3d3d3d3d3d3d/ZdbmbUrPM/7Njv/WZmdnZ21u72bVDetblbdvLpFdcvqVtWtq9tUt6061e2qbrVX9ap+Naj2q4Pq9tWwukN1x2pUHVbjalJNqztVs0pX82pR3bm6S3XX6m7V3at7VPes7lXdu7pPdd/qftX9qwdUD6weVD24ekj10Oph1cOrR1SPrB5VPbp6TPXY6nHV46snVE+snlQ9uXpK9dTqadXTq2dUz6yeVT27ek713Op51fOrF1QvrF5Uvbh6SfXS6mXVy6tXVK+sXlW9unpN9drqddXrqzdUb6zeVL25ekv11upt1durd1TvrN5Vvbt6T/Xe6n3V+6sPVB+sPlR9uPpI9dHqY9XHq09Un6w+VX26+kz12epz1eerL1RfrL5Ufbn6SvXV6mvV16tvVN+svlV9u/pO9d3qe9X3qx9UP6x+VP24+kn10+pn1c+rX1S/rH5V/br6TfXb6nfV76s/VH+s/lT9ufpL9dfqb9Xfq39U/6z+Vf27+g+HfMdTx1cnUCdUJ1InVidRJ1UnUydXp1CnVJVSqlanUqdWp1GnVadTp1dnUGdUZ1JnVmdRZ1VnU2dX51DnVOdS51bnUedV51PnVxdQF1QXUhdWF1EXVRdTF1eXUJdUl1LH1Kq6tLqMuqy6nLq8uoK6orqSurK6irqqupq6urqGWlPXVOvqWmpDXVtdR11XbarrqeurG6gbqi11nLqRurHaVjtqV91E3VTdTN1c3ULdUt1K3VrdRt1WddTtVFftqZ7qq4HaVwfq9mqo7qDuqEbqUI3VRE3VndRMaTVXC3VndRd1V3U3dXd1D3VPdS91b3UfdV91P3V/9QD1QPUg9WD1EPVQ9TD1cPUI9Uj1KPVo9Rj1WPU49Xj1BPVE9ST1ZPUU9VT1NPV09Qz1TPUs9Wz1HPVc9Tz1fPUC9UL1IvVi9RL1UvUy9XL1CvVK9Sr1avUa9Vr1OvV69Qb1RvUm9Wb1FvVW9Tb1dvUO9U71LvVu9R71XvU+9X71AfVB9SH1YfUR9VH1MfVx9Qn1SfUp9Wn1GfVZ9Tn1efUF9UX1JfVl9RX1VfU19XX1DfVN9S31bfUd9V31PfV99QP1Q/Uj9WP1E/VT9TP1c/UL9Uv1K/Vr9Rv1W/U79Xv1B/VH9Sf1Z/UX9Vf1N/V39Q/1T/Uv9W/1H454j1cfvz5BfcL6RPWJ65PUJ61PVp+8PkV9yrqqVV3Xp6pPXZ+mPm19uvr09RnqM9Znqs9cn6U+a322+uz1Oepz1ueqz12fpz5vfb76/PUF6gvWF6ovXF+kvmh9sfri9SXqS9aXqo/Vq/Wl68vUl60vV1++vkJ9xfpK9ZXrq9RXra9WX72+Rr1WX7Ner69Vb9TXrq9TX7ferK9XX7++QX3Deqs+rr5RfeN6u96pd+ub1Detb1bfvL5Ffcv6VvWt69vUt6079e3qbr1X9+p+Paj364P69vWwvkN9x3pUH9bjelJP6zvVs1rX83pR37m+S33X+m713et71Pes71Xfu75Pfd/6fvX96wfUD6wfVD+4fkj90Pph9cPrR9SPrB9VP7p+TP3Y+nH14+sn1E+sn1Q/uX5K/dT6afXT62fUz6yfVT+7fk793Pp59fPrF9QvrF9Uv7h+Sf3S+mX1y+tX1K+sX1W/un5N/dr6dfXr6zfUb6zfVL+5fkv91vpt9dvrd9TvrN9Vv7t+T/3e+n31++sP1B+sP1R/uP5I/dH6Y/XH60/Un6w/VY+Ge73Z3abzyQ2vdYn+aLSytr6+sbPTudbGzvr25o12N4/b6uw=
*/