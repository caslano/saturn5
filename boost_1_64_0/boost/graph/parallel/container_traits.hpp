// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

//
// This file contains traits that describe 
//
#ifndef BOOST_GRAPH_PARALLEL_CONTAINER_TRAITS_HPP
#define BOOST_GRAPH_PARALLEL_CONTAINER_TRAITS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

namespace boost { namespace graph { namespace parallel {

template<typename T>
struct process_group_type
{
  typedef typename T::process_group_type type;
};

template<typename T>
inline typename process_group_type<T>::type
process_group(const T& x)
{ return x.process_group(); }

// Helper function that algorithms should use to get the process group
// out of a container.
template<typename Container>
inline typename process_group_type<Container>::type
process_group_adl(const Container& container)
{
  return process_group(container);
}


} } } // end namespace boost::graph::parallel 

#endif // BOOST_GRAPH_PARALLEL_CONTAINER_TRAITS_HPP

/* container_traits.hpp
R1C3zOLppddf6/JBZ2dQJ3Hx1rBOQSCkU0nr9Kyu8+ZcvDuxBtXkJ2PuxJL5Mvel4aOlf7M6YCWgVN70O/YLRKdqVFqKqofzds04nZZSeVpWXfagQmfZxaYuSuhsQ0fJXnU3PmDqvITOQaOz/PNYOlxIWucmdyydakbn5rGxdM5Bxylt8OarY+VrUljHs7KprRNdD2vCOs6Vm4Ob27ouf9jniY+xt7IOs5swu6R+Vz7pc5YptXdfDa3Xt2aojqnZ+FvGJraBDkdiQmJNfri8pdqweRfglj5zCu9mWpjntSYiu4iWXUmdr1JjzrmJF71KUeVQXDNcDqsWlNo/XOusQ+dJdJyrGkj6EhPtMngK+dO4yDLYVzPcrlZP4Zo5+GvXzPGa4Wtm9bJY10xmLepC4ruqjbFZUEKnNTquoI5/wV9K7RHrYv9Dy7ZpcMcfdOvEnsFv6/0jbopO03ptY+EZfa5rcCtxc3CX4xZo3qX3b5yNuy7i+GDz2+azOi78zJYKybbDJNwhfj+njy+yncQ5DLcfd14g5A7w+3m4G/cCboU/5C4IhOK7Td83AvzupGVf4n9R4i+VLmGRHLP9owP270L7t+gsFtpp34MbIeFD7pDmSyKL7XI5PsyUr522JTrul3Gv8vsVuBcXPLYvKMPp82uWztN+ZK/hXtc6BSXy/kYJeS3N3ppvau7HXRGR5gNa/hb8S8Tvt+3fsLR/Q0QcechytfwdqPeDlf7nIP5kfYw2Jtf5IjgcDitdfzrdpfNL/nCiJ/6/BssQvgvfw03EHcJN1mX8PvwA96Guz8O4wbq9fYSri/sY90mJ8x3Rep9qnbdwn+HydNjPcV/ghutwXwadtN3o+s9Q/WVu2fc5ik7YzNk145KWY6WvlPmJa9y/bpPkOne0TZJ5F9k2SZoODdv3aGbsgFS1ZcYOSMCWGdslpy4wMmO75EtbZmyXvGfLjO2SA0Z2lrFd8rItM7ZLdv6dvfsMj6JaAzg+s8mGVEgChBAgRGqQYugdIh1poRqaBAiQQEgiNSBiQEQQxFAURJAiIFWigKKiIqDEKwgiIgoqAnq5ioJIU1Huf9+cPbO72UW+3ue5+Lz+cs6emZ165szszBkrr7Ez7xUrr5Huu8TK0/Mxy8rT85Fh5en56GPl1dPDDtJ5ej5aWeX0fMTrvIZ6PiKtPD0fflaeno8bA3Seno+frDw9H6etPD0fR608PR8HrDw9Hwt1XgM9LblWnp6WCVaenpZRVp6elv5Wnp6WrlaenpYAK08vv9/76zy9/C7ovPp6+X1h5elpft/K09O8w8rT07zeyrP6tbHy9DQ/beXpaZ5l5enlN8nK0/ORZuXp+Rio8+rp+ehh5en5aGXl6fmoYeXp+RgySOfJfMSQN0/lcUfFkKyRQ/hxS67isl/zXUP0ZzJ8FVn+7n3wnLEX7YPngr1IHzxyDy/39ZIn9/VK3jLT2eeLXMKTvKuilJOL6VHk1aJcJcnT93NJ/jrT+d3WvVrFyU8j/2H5/hwpl6DL6fszJD+bfO5tIF/f2yD5DfT36d/7JD+cfH6nId/6nYZplt8BfozS/QtJ2Sqmcz707wKSH6fz9W8Ckh+qp9G6BsO45Tw5R+aFk2cfeVFuefo8m2XRNOIj2Q5oFZcpTMcMVO/cUOkEj3QHj/Ti4YXpx6MK0y+nFqbnlS5Mj3+4MD1Ypeeo9CE1/MwJ1vByD7u63z6huSH/Xme6K+Iy3MowSY84yuc6Fnz6yCmF5wQ2huU+U27U1L/fqHJVJd2X9ERJz7dF6nMIff+RlOmih6kk6e6kx0k6W6VN4+Sj8rn+TZfP2LDUubQevqG+b+gJSU+1Oa8jmfq+QK7B6vI=
*/