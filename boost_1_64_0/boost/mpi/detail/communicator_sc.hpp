// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Skeleton and content support for communicators

// This header should be included only after both communicator.hpp and
// skeleton_and_content.hpp have been included.
#ifndef BOOST_MPI_COMMUNICATOR_SC_HPP
#define BOOST_MPI_COMMUNICATOR_SC_HPP

namespace boost { namespace mpi {

template<typename T>
void
communicator::send(int dest, int tag, const skeleton_proxy<T>& proxy) const
{
  packed_skeleton_oarchive ar(*this);
  ar << proxy.object;
  send(dest, tag, ar);
}

template<typename T>
status
communicator::recv(int source, int tag, const skeleton_proxy<T>& proxy) const
{
  packed_skeleton_iarchive ar(*this);
  status result = recv(source, tag, ar);
  ar >> proxy.object;
  return result;
}

template<typename T>
status communicator::recv(int source, int tag, skeleton_proxy<T>& proxy) const
{
  packed_skeleton_iarchive ar(*this);
  status result = recv(source, tag, ar);
  ar >> proxy.object;
  return result;
}

template<typename T>
request
communicator::isend(int dest, int tag, const skeleton_proxy<T>& proxy) const
{
  shared_ptr<packed_skeleton_oarchive> 
    archive(new packed_skeleton_oarchive(*this));

  *archive << proxy.object;
  request result = isend(dest, tag, *archive);
  result.preserve(archive);
  return result;
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_COMMUNICATOR_SC_HPP


/* communicator_sc.hpp
NuLdIdN/MeeMo7jM0N8fXynn5omGN4k0EYIuHN5IJd2tD3X0z8NKTBlvvuzoHHLJ/hite108Y7JJxjFEkvf3mWx8W8JS5GQpRqiVyYWa4a+8xds9gCQ4AG23O0t2bVP6NH1UgvX++TPA9yPmqmYbfVdHTqFew5lEKwthCv++UKZwiV4reXQOv8NPjNacIsbVRVV/kquHsmmze3grXZhAO7o47Aq4KTQGiqzG97HiPr00+thOJUv/+xpzP1onNHdiM9Eqea5c2dmfz/2+0l8E/f7mCu53N1GjoH4FWdFFYb9/BtUgrD93NuXEifUW/3s1rEc2bGIhbcaceQTIUnsu4m4t9F8F3br0ClmNs/RhD/KzGS3GYK4mWz+TdgDXXEQ1+5s104V3oYN2+i+bF5c69d+fS9BZTH6J4G/0fk2F8flzuB8+o3xFxNg6+k8VVLkGerh2AfUwnudqk//cskzFcw4rttNBuYk8Az4k02Fqvi66mO7wViiYZczXhZGUlqGx0jR5JKnXN1vVa4HcUVUf3USIiMyh8XSieNmwTV0AJTiOT1b0h1pD8WfoMHsLkoQzU+oR/ckyqmIkU4bfWxtIv5ap2ML5NDHfI9uA7wGXXNv4PWDoyubl9R1WNeN/7rKm80vkPcGR/1saHa+IXbNyeCe8spXhPgxNtIcGncDON1mBFiYZinFTby+zc4GBVHRT6E7M1YiK0rY9e+lRKTyZ+nSDqL+1TFhqlYPoaba4Iw0syx2IZIQ8gFQWiJowqw7sqVRI1RnO0OY1X6Pma0th9HzROj57iuX46vUEaoW0uOcBNvXyM//wEEipKDw7bEQ+nkhRYXDZBO0kVPRpI57zwqSIjtxs1To3LQi6V+6MPiXbARtMC5SIC+QLJofO0D+U9lj5jJdAbOZrcaNApz4yOzWOOrVuLneqPdmH4iQE3dy5tJIPYJr4jLjeuzbZVIfyZ9Fbu3Ls3jaFWEE6ZbIUSzkuozQ/8/ERRu0c1JTDjfcBAlrrFsbTVmqw8XocpbKNTXGUyjKujaNUhnFBHKU04+Q4SnkNrclS+RnK9HUchHZBLmhtO3MeaRb77KhSJqritgmB+NycKTliBgs5KGogK9d6UsPok7D0eC7Lqg1ZfF4ua0OrAklQKXF8H3ynE2XQ3EkSH8YNHkM7I7awnjq/xY9WVQETu5DzfGunHDn/B7pG/cs+5nv+QWBYlXNZm1p72prbEmTjcfAnpaJ73hSaQ35qb4AoCWcISSFzkiHGsMvl6Kh6G7PyJJ8cAT0ToIlU5NAHHByAOMsEMY5A/O0yE8SNkAW9cwlZZgQAeZqb5T7yzFhDmFVDpOg+n7rU1aSVbRU140IiBtWAY+yxhJmyGkaMN6gGVH3kPJu6MBDSqo9Z+LIj7CVUN22186rRLriglpFcnIxhcjqMq5raqA7149hdHENa2pgY3QaeuQAK8K7sTA2tuKsGgpwRnvhQaL/UHbqMBnAeHSW0u8LFVe4Yu4e0Jsl6X8zbKcOTTJsTq5P2RSqR0kR83vMFSWWoP6YHeumLZS2oxBTj8xnqjPCxNdO/6xYwz6fUhY7n065LrPPpXtnbcBAsAHxbzRfRqgEuOZ/A7n2jWWgOFbpAFWrlUkb1g+FyAacW75YQycd8WLWzLFTEHMMx9ZRApNvvlivlmCKJnBxTW61jipr96BJu9he8A8iARB1Nk7Kts0nd+a/P77dWi6TDg3cc9gqWkryGqGm6lzOj8RdyXLxHhE4PZvI6kMlrF4+NRu6UvpKo6eVp/0oaafLnqQtY3i6RmtusLtJoI3X1n8kTq/uvwPP/Yp7Y3olQKRFe1yyP4GmJJhNYz7Z5yF27WBs8reRGN4E=
*/