// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                   // BOOST_DEDUCED_TYPENAME. 
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/traits.hpp>         // category_of. 
#include <boost/mpl/void.hpp>          
#include <boost/type_traits/is_convertible.hpp>         

namespace boost { namespace iostreams {namespace detail {
    
template< typename T, typename Tag1, typename Tag2,
          typename Tag3 = mpl::void_, typename Tag4 = mpl::void_,
          typename Tag5 = mpl::void_, typename Tag6 = mpl::void_,
          typename Category = 
              BOOST_DEDUCED_TYPENAME category_of<T>::type >
struct dispatch 
    : iostreams::select<  // Disambiguation for Tru64.
          is_convertible<Category, Tag1>, Tag1,
          is_convertible<Category, Tag2>, Tag2,
          is_convertible<Category, Tag3>, Tag3,
          is_convertible<Category, Tag4>, Tag4,
          is_convertible<Category, Tag5>, Tag5,
          is_convertible<Category, Tag6>, Tag6
      >
    { };

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DISPATCH_HPP_INCLUDED

/* dispatch.hpp
/J+i4/9OoZrbu2pqp/K3s1VvX/K3a1U/j+A/X1Bzu5y/PbN6u5n//EV18yk1n7/wt6NWPy/jb1+t+XxNdfbJHiHrD21I7Xv/u2xIm2I/+rfZjuagPjajTbIX/VVb0cZ2omD+KZBAAgkkkEACCSSQ/5ZssfF/YcGk2rD/p7L+t0tz1lOzeDDBmlJeNLlsfEn+FKs17glk5l5xlydy7nBBUT47nicfZon/w86+APHPy58ysbywbLwsm56WXzbV3P+IuV/c9e7I/c3gCuMvXuMLigpkS2YXXZe8MhL/9PGxQcZPp7hIaBl7gmQOI405jK66trtKhxnd3W/Bo9uS1gEF0bXdE/PyZP9Ciybu2QX++xe4x7uPlf8rKp/mu3dBw+rehYF6xn1ZyfTiw/32LsTFTVkiUnTmTIHdxL+J2bdaouHd9ehbb8J6dHefA/nUtfnx3+cnP549DgPFTdOta8CnyXMt65n02DX0YV3fnhoB9xGnc/iop5wjO54t/d7A75f1nBqU9Zw/KLt54l/XlN2Zcp3wp8qOdFdfdlpGlVpGq7SM+mgZrdYyulAjXow+TZglnjI6hGZs3pDpnDlr8lQ2rVgco/umX5D7Cqxc/VYl7y6Sb/ZlvyP+e1qZuKSTVyetLfFYTGq2ga3Q84hoW3gRbuhG5VAvrhy8+eF/feu8+FDPPpfS/PK86Vr1m1j3xYduet0T9nfrvvzQ2Lo/9tDNW/dzDtW6j3s/2te1EO7TiB3HFwhT6Smr0vz8PJw36beosgZlVPkHZXS2+NcxZXTJoZvvt8Upo4u1jFbHvR+Z2tjmobau2d8xmXN7vWXE++H5C8QzpN3jrw6ecwVelfvG8Pcj7H/OvObT5x0zZ1fcJ2FmWS3471B0e8qkrvsetTDvkLxTrdM27R1K1bJy0p3iSbe3LD7Umw529wegL5HGCYf5lIX+Vrj1a2v9+uRZ77f1zJbo7wF5IO2bXs/Oc1L0Od52fspW+lugNyWjl/OfKm+6yyaWlZda1bbH9w6LfWe/lOtQjdqj087Wc58T/mW3nelerAzd0NhZ21knTaMV2Z+3UQcDn9izKzxn4HSQe8LmTIp6cp1k9iBS8Kim1/8bvkPd39V+mr71mr4dNX0ZuldsgKbPvwNEXVp7N83k3pXodpRRfbt+h/rD6oQaNEqMS0/1+cmXZ9Qz+cnR/ISs4U398uAtc+/ZIkvqx/e7dE9dJA+Sgcn0aovKi8lDmaXnY8g71DAFlTIbIe3jmKfwqLNxv9L8fZc4625Sm6gs1DPYtU187aQ1RLtu6Ng2jr/qghffezwzc+7jIyoKTr1yXc33rNXUprKHPLes5YnfzN33/APndTngoiY9tlrLvqKnHPeiDjcNaFXnh2++npC9KPuk3FHV22BaNHLcL73p/Aeff3LGhiOb3Zm8Q73v9q65DW9z29L8bVTV2cZqblN8S8oz+7tOHUd+O3v+dXscmLau7snHVGc7rLkNr6Y2y5ra9qqzNX7rOR/GebcrYXv0S3SAO37Q960STUR7aPgTdG/ZfJgIF8Am8ES4MzwJfglz3L40TNV46qDZGs+pGs9pGs/pGk8lbAbPgCnwTI1PzsPX+C7U+Jqjl2t82Rpff9gaDoBt4Ci4PRwEd4SDYR+4GxwEd4eotQc8AObAg+CeMA/uC0vgSDgH7g+P03iPh8Phyep/nvovVn8tB/qV1ZfDOZruc7UcFmk5nKflcL6WwwXQrZ9Kja+ZT/0co/HN0fjmwsbwWNgUHqfxLHL7LHCextMEPUXjOZBwckYPbAsPhu3hdJgOJ8CucCLcFU7WcsyDQ2E+HAGnwAP0vtGwAE6Gh8ECOA0eBYu0PKdr+qaa/gU=
*/