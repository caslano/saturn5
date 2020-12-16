//=======================================================================
// Copyright 2001 University of Notre Dame.
// Copyright 2003 Jeremy Siek
// Authors: Lie-Quan Lee, Jeremy Siek, and Douglas Gregor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP
#define BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP

#include <boost/config.hpp>

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_GRAPH_DYN_LINK)
#ifdef BOOST_GRAPH_SOURCE
#define BOOST_GRAPH_DECL BOOST_SYMBOL_EXPORT
#else
#define BOOST_GRAPH_DECL BOOST_SYMBOL_IMPORT
#endif // BOOST_GRAPH_SOURCE
#endif // DYN_LINK

#ifndef BOOST_GRAPH_DECL
#define BOOST_GRAPH_DECL
#endif

#endif // BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP

/* dll_import_export.hpp
UN3ijGM0luxM9Mgh7lg8NDt59Q00rclkrz4dt379Rh17Ub5eh89YM3x8G5gOH6f7tvduSarJto6cDGsM1KCELae48/qg55k3hH05+7lVLsOBTDHvxTPS+QqQFsb/REdPP6SAqLclY608t1nOdN5JXfeJ0vea8Fz2WSY/ZEw97ixjlRA/kymtY10m1aqvZVCFJkbxWCzhClD1OnKdb9jZoQ6PEA/I9JHioOrSJkxBx2Vx6vF0aoUkClIaf23rRdv7Yq3t25BhOC/6leoxj0mqN4lTU78rutbNcp36hHn1Y63DsjfPvGP6gpzviGl7r34lXLnjThL1LdtUipnbdC59MzIhEUuifqtJztKpL+5WIbHZk2SxV/MtGxub1kpSwE5PslstcunCrpRfRH0HRhO2WefWKEbT7noY69ymE8WugS+wy2RW826n+5BtIbajVY6f3aRjLH6nr0eIGJ2tyS3GI7SLrpjo27Nsw4TLTOoci491YRJae5cNuWMgnuhP9UPZG+uUYqZ+Y3LaYQE/t/SnetrlQshnSdzoxLajXubyvb033mcZJNWvbD9FW9yKX0uNG5w0buKs73jZ2gqf8U0CXTIzrbPgJ2bRlQKlHtH+waWWYbqY6/KDmxl4kcLdzhjqMowgpNIkE6m4Gmf7yviJvn4JqcyVVrnqE2Gnxinc8YBCiJYIMqVVG7WsaWlZv7EJi/xiJietZxgGvRLf3B6VY8LvQso8XVTd7UlUz76ovnJ/jSkTWohVGNuvEJn2OeUIpdW6A+ijTj22EK3Gl2QsKQEXZMoiytr32Oll6h3GDEZXREFMjpZXPxVdp87PqENxoXNYXTJ64qVc0KVUjzOc6la5WAHn03lbP51VLAEHvGZaWKCYp3DR0zu8Zoy55a9dX96a2bp2tOpLaNQ0K0Wou0VNdamb1BKtlrxHnZLfktfqvPbRBGCJwWeaUNz6yvgpR9hjv2aDt6nU9YMhmfqn+q38696W0hfxKfVX0+rR6epVVndErTc53dnf16crq7RD6jVa3xS7WxgPuzz80fjImKud2XpWLPtyUUBrb6xP/T2j/dUXsSXo63Wvqa6l7X1iNpfy9taw3TNaztiLa4SFvNe1wkhm09FSC9x6UswrXXrOsrbcvIt1fQ3uTkjrsOAif9TDbMd0MyK6CPy37hazNdmZgn/PNa61CTuU7JFEjZl+DwrdV2gxG8s0ScS29m+PiQzuzDDVnmujpFvG45q9nlgrb9K03Kay2GAFEPPXj9AGJFE/YS2lb2jXFu/IkObOVuKN3n4yJbFduz7s7JWIjZ4ocl03e91aNi1iKy3SlI2y3NMn/ccu6T1e0H6wZzHJ20c0/dM7xMQpoR5whs2YSVspcrxa7MsYwq4yYvIpp7xkdxyyxtdTE3XJ8Ne43t4kPwurdrTASG+5Zwji22n6Nl+0psfl4z6Xj7bVVl7xiJGl+DiS6cERZaWdIzHtgzFnflHWzmDqeuXsHku6tfek9CvgZp/W9uQr+zrVOauv1tkZiyP0QtWQOcxQP7dkfT+SoS+KTLsD/sVd8fRKrNXpGNJnCiz1ZyM7nL3bN7n8evm2nljKIRej9MupV089W7LtddeG/pR0K7eKGGA6O3pfJfKe26slupB4bzCunX23i6JLmas+7ilTlB7qC059afecGXrKaSpi7vMZ7bt0cCBtMGLo6UB1ubWhKtrbi7kDn65BYqNL7yhuXtXUIMWdY5KJosPuiWgVi4785m07Eywd6xpA7I5Oj/NQjfu2obx8xqnDG5c+5tDTUYZNROcjTl2RzZ9w6sT745buJ12629BDP2XroMHsjL9SPT9ndfOLwpGNrVvlplSVoFpbiG6Lq5U=
*/