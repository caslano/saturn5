//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP
#define BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/small_vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T, std::size_t N>
using small_vector = boost::container::small_vector<T, N, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a small_vector
//! that uses a polymorphic allocator
template<class T, std::size_t N>
struct small_vector_of
{
   typedef boost::container::small_vector
      < T, N, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP

/* small_vector.hpp
SzfJRrcTaGc5l+6yaJ9Lzydx66Q6m8HChJls/3ascRTMpGGfSXG0lh4wVZhi+/dzv/B3JsAi7t/P4TKWAmbSsDQmLgusj4atBIvUsCLGHgYza9hzjP2WabOFsZNM379i4oz9tWuxgmnFjQLTGrNUsDDvsp0j2fVgWGeRZPNIPtnywGI1bBtjNWDxGnaIiesCS5AM57U5xjd35d8R2cD6e+PulWwCmFXDbgQL07Bskm+uvK0Dw3m9RbIixirATBpWQ2qR7TXGmsAiNewok+8zps7eVu24PowNYWy8VbsPqWCqhqWDmTUs26rd95VgfTSsmKnlYcaqmP7VMdbI1HKU6ftppn89TD51gHa+eLD+GjaRsRuZNnPBtGopYOK2MfmqwSwa1sBYG5hdwwyx2nFWMK06x4KpGvYTMK35MpOxW8CCNSw7lpnXYCYN28zYDqbNKqbOl8HMGrYfTGv5dTBx3WBWDTMPhP2D1nIA02pzGmO3gGnlW8nEbQHTGrNyMHm+4L7jBTDcF8vnmuvBcLnfJ9l+xloYO8rYKcb+ylgPY71t2mZirD+YRcPGgtlkw+MXgEjPeErnfmFdIfnk5wGLiT0onzclViq1uZFps1gy2uYOYvJzhAowVaPNaibfy4zVS0bHbD+Y0WvFUv8O4XjiuBDrIHHymHWSfPJ5lK+IyW0qcaRNyYxgWnGRjFmZNhOYuFFM3HjGfqJlcJ0GpjUu6WCqRpuZxOTll0Pa3C61uYyYPAcLSJ3yudFCEifbAyRO7sMOMKtGH14A668xLk1Sm9RaiMnrXxvTv5PE5LguppbgeKnvJM5MTO5fLJjWch8CFqbRvyQwVWNb4ATTWqdnMDabsduIyXXmEJPPzy8jfZDNzdgDYFpzvgxMa1tXCaa1jF4Di9QYz2YSJ9tpsHgNUwfB3NUwO2OpYBYNywTTWu6LwPpomBssWMO2gKkatoPJV8nE1YDFe/eb8uscD4HZvCa/zvGvJE5+naM5wRcnv84xCQzj1snPH4jJr3PMBxvitQ2S/YLkk1/n+BqJo78/6u25wfNuzhWSmTQs0HubIQz+3w1EzQXp3VCebEFwCRWlQU3fwT/x3c7QvkqQ912g8b6v3gtWQsR9MFZ43/EvFO/jDAreZ9+qg/s8vcT7+g3Fx/VW8L4YHd4XqOB9u3rjfUYF77tjLvzkrVfch7c79NvHQ81QYSgcAycq45QkZaZyu7JBeUSpVd5VPlZ0uv66ZN01uoW6u3VP6H6t+6Puc12IPkF/hX6efrG+WL9b/7r+qL5H3z9gXIAz4OqA3IDNARUBewMOBXQFBBmGGJIN1xuWGIoNTxveNrQbegyhvYb1Su41rdfCXvf02tbr2V6v9nq/1xe9wnrbe6f2ntt7fe9Her/c+3e9/9w7KNAc6AgcEzg2cFxgUuBlgbMC7wzcFPhI4IuBBwI7AnsCzcZE4yXGa40LjRuMO43PG982HjN+bQwLGhL0k6Abg+4Mcgc9HFQbdDDoZNB3QYHBtuBLg68NzgleHnx/8O7g14Nbgz8PDg4ZFDIx5IaQxSH3hFSE7A05FPJpiEEdoI5Xr1Wz1XXqZnWr+rT6rPqc+rxao+5RX1BfVN9Qf69+pH6hBoQGhsaFOkNvDs0NdYdWhP4m9ERor7C+YSlhM8MWh20Mqwx7O+yTMH14aHj/8DHhM8JvDF8cXhz+dPjb4YfCPwsPMEWZxpimmTJMd5jWmkpMT5peNr1r+oOpzdRp+sIUEBEe0SciPmJkRFLEZRFXRFwZkR5xU0RGxJyIRRErIgoiHo14JaI54pOILyPCIkdEpkbOjXRFPhD5VGR95PHIbyLNUbaoS6Ouj1oStT5qZ9RLUe8=
*/