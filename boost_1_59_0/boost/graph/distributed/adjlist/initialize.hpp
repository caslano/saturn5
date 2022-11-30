// Copyright (C) 2007 Douglas Gregor 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file contains code for the distributed adjacency list's
// initializations. It should not be included directly by users.

#ifndef BOOST_GRAPH_DISTRIBUTED_ADJLIST_INITIALIZE_HPP
#define BOOST_GRAPH_DISTRIBUTED_ADJLIST_INITIALIZE_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

namespace boost { 

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename EdgeIterator>
void
PBGL_DISTRIB_ADJLIST_TYPE::
initialize(EdgeIterator first, EdgeIterator last,
           vertices_size_type, const base_distribution_type& distribution, 
           vecS)
{
  process_id_type id = process_id(process_group_);
  while (first != last) {
    if ((process_id_type)distribution(first->first) == id) {
      vertex_descriptor source(id, distribution.local(first->first));
      vertex_descriptor target(distribution(first->second),
                               distribution.local(first->second));
      add_edge(source, target, *this);
    }
    ++first;
  }

  synchronize(process_group_);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename EdgeIterator, typename EdgePropertyIterator>
void
PBGL_DISTRIB_ADJLIST_TYPE::
initialize(EdgeIterator first, EdgeIterator last,
           EdgePropertyIterator ep_iter,
           vertices_size_type, const base_distribution_type& distribution, 
           vecS)
{
  process_id_type id = process_id(process_group_);
  while (first != last) {
    if (static_cast<process_id_type>(distribution(first->first)) == id) {
      vertex_descriptor source(id, distribution.local(first->first));
      vertex_descriptor target(distribution(first->second),
                               distribution.local(first->second));
      add_edge(source, target, *ep_iter, *this);
    }
    ++first;
    ++ep_iter;
  }

  synchronize(process_group_);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename EdgeIterator, typename EdgePropertyIterator,
         typename VertexListS>
void
PBGL_DISTRIB_ADJLIST_TYPE::
initialize(EdgeIterator first, EdgeIterator last,
           EdgePropertyIterator ep_iter,
           vertices_size_type n, const base_distribution_type& distribution,
           VertexListS)
{
  using boost::parallel::inplace_all_to_all;

  typedef vertices_size_type vertex_number_t;
  typedef typename std::iterator_traits<EdgePropertyIterator>::value_type
    edge_property_init_t;

  typedef std::pair<vertex_descriptor, vertex_number_t>
    st_pair;
  typedef std::pair<st_pair, edge_property_init_t> delayed_edge_t;

  process_group_type pg = process_group();
  process_id_type id = process_id(pg);

  // Vertex indices
  std::vector<local_vertex_descriptor> index_to_vertex;
  index_to_vertex.reserve(num_vertices(*this));
  BGL_FORALL_VERTICES_T(v, base(), inherited)
    index_to_vertex.push_back(v);

  // The list of edges we can't add immediately.
  std::vector<delayed_edge_t> delayed_edges;

  std::vector<std::vector<vertex_number_t> > descriptor_requests;
  descriptor_requests.resize(num_processes(pg));

  // Add all of the edges we can, up to the point where we run
  // into a descriptor we don't know.
  while (first != last) {
    if (distribution(first->first) == id) {
      if (distribution(first->second) != id) break;
      vertex_descriptor source
        (id, index_to_vertex[distribution.local(first->first)]);
      vertex_descriptor target
        (distribution(first->second),
         index_to_vertex[distribution.local(first->second)]);
      add_edge(source, target, *ep_iter, *this);
    }
    ++first;
    ++ep_iter;
  }

  // Queue all of the remaining edges and determine the set of
  // descriptors we need to know about.
  while (first != last) {
    if (distribution(first->first) == id) {
      vertex_descriptor source
        (id, index_to_vertex[distribution.local(first->first)]);
      process_id_type dest = distribution(first->second);
      if (dest != id) {
        descriptor_requests[dest]
          .push_back(distribution.local(first->second));
        // Compact request list if we need to
        if (descriptor_requests[dest].size() >
              distribution.block_size(dest, n)) {
          std::sort(descriptor_requests[dest].begin(),
                    descriptor_requests[dest].end());
          descriptor_requests[dest].erase(
            std::unique(descriptor_requests[dest].begin(),
                        descriptor_requests[dest].end()),
            descriptor_requests[dest].end());
        }
      }

      // Save the edge for later
      delayed_edges.push_back
        (delayed_edge_t(st_pair(source, first->second), *ep_iter));
    }
    ++first;
    ++ep_iter;
  }

  // Compact descriptor requests
  for (process_id_type dest = 0; dest < num_processes(pg); ++dest) {
    std::sort(descriptor_requests[dest].begin(),
              descriptor_requests[dest].end());
    descriptor_requests[dest].erase(
      std::unique(descriptor_requests[dest].begin(),
                  descriptor_requests[dest].end()),
      descriptor_requests[dest].end());
  }

  // Send out all of the descriptor requests
  std::vector<std::vector<vertex_number_t> > in_descriptor_requests;
  in_descriptor_requests.resize(num_processes(pg));
  inplace_all_to_all(pg, descriptor_requests, in_descriptor_requests);

  // Reply to all of the descriptor requests
  std::vector<std::vector<local_vertex_descriptor> >
    descriptor_responses;
  descriptor_responses.resize(num_processes(pg));
  for (process_id_type dest = 0; dest < num_processes(pg); ++dest) {
    for (std::size_t i = 0; i < in_descriptor_requests[dest].size(); ++i) {
      local_vertex_descriptor v =
        index_to_vertex[in_descriptor_requests[dest][i]];
      descriptor_responses[dest].push_back(v);
    }
    in_descriptor_requests[dest].clear();
  }
  in_descriptor_requests.clear();
  inplace_all_to_all(pg, descriptor_responses);

  // Add the queued edges
  for(typename std::vector<delayed_edge_t>::iterator i
        = delayed_edges.begin(); i != delayed_edges.end(); ++i) {
    process_id_type dest = distribution(i->first.second);
    local_vertex_descriptor tgt_local;
    if (dest == id) {
      tgt_local = index_to_vertex[distribution.local(i->first.second)];
    } else {
      std::vector<vertex_number_t>& requests = descriptor_requests[dest];
      typename std::vector<vertex_number_t>::iterator pos =
        std::lower_bound(requests.begin(), requests.end(),
                         distribution.local(i->first.second));
      tgt_local = descriptor_responses[dest][pos - requests.begin()];
    }
    add_edge(i->first.first, vertex_descriptor(dest, tgt_local),
             i->second, *this);
  }
  synchronize(process_group_);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template<typename EdgeIterator, typename VertexListS>
void
PBGL_DISTRIB_ADJLIST_TYPE::
initialize(EdgeIterator first, EdgeIterator last,
           vertices_size_type n, const base_distribution_type& distribution,
           VertexListS)
{
  using boost::parallel::inplace_all_to_all;

  typedef vertices_size_type vertex_number_t;

  typedef std::pair<vertex_descriptor, vertex_number_t> delayed_edge_t;

  process_group_type pg = process_group();
  process_id_type id = process_id(pg);

  // Vertex indices
  std::vector<local_vertex_descriptor> index_to_vertex;
  index_to_vertex.reserve(num_vertices(*this));
  BGL_FORALL_VERTICES_T(v, base(), inherited)
    index_to_vertex.push_back(v);

  // The list of edges we can't add immediately.
  std::vector<delayed_edge_t> delayed_edges;

  std::vector<std::vector<vertex_number_t> > descriptor_requests;
  descriptor_requests.resize(num_processes(pg));

  // Add all of the edges we can, up to the point where we run
  // into a descriptor we don't know.
  while (first != last) {
    if (distribution(first->first) == id) {
      if (distribution(first->second) != id) break;
      vertex_descriptor source
        (id, index_to_vertex[distribution.local(first->first)]);
      vertex_descriptor target
        (distribution(first->second),
         index_to_vertex[distribution.local(first->second)]);
      add_edge(source, target, *this);
    }
    ++first;
  }

  // Queue all of the remaining edges and determine the set of
  // descriptors we need to know about.
  while (first != last) {
    if (distribution(first->first) == id) {
      vertex_descriptor source
        (id, index_to_vertex[distribution.local(first->first)]);
      process_id_type dest = distribution(first->second);
      if (dest != id) {
        descriptor_requests[dest]
          .push_back(distribution.local(first->second));
        // Compact request list if we need to
        if (descriptor_requests[dest].size() >
              distribution.block_size(dest, n)) {
          std::sort(descriptor_requests[dest].begin(),
                    descriptor_requests[dest].end());
          descriptor_requests[dest].erase(
            std::unique(descriptor_requests[dest].begin(),
                        descriptor_requests[dest].end()),
            descriptor_requests[dest].end());
        }
      }

      // Save the edge for later
      delayed_edges.push_back(delayed_edge_t(source, first->second));
    }
    ++first;
  }

  // Compact descriptor requests
  for (process_id_type dest = 0; dest < num_processes(pg); ++dest) {
    std::sort(descriptor_requests[dest].begin(),
              descriptor_requests[dest].end());
    descriptor_requests[dest].erase(
      std::unique(descriptor_requests[dest].begin(),
                  descriptor_requests[dest].end()),
      descriptor_requests[dest].end());
  }

  // Send out all of the descriptor requests
  std::vector<std::vector<vertex_number_t> > in_descriptor_requests;
  in_descriptor_requests.resize(num_processes(pg));
  inplace_all_to_all(pg, descriptor_requests, in_descriptor_requests);

  // Reply to all of the descriptor requests
  std::vector<std::vector<local_vertex_descriptor> >
    descriptor_responses;
  descriptor_responses.resize(num_processes(pg));
  for (process_id_type dest = 0; dest < num_processes(pg); ++dest) {
    for (std::size_t i = 0; i < in_descriptor_requests[dest].size(); ++i) {
      local_vertex_descriptor v =
        index_to_vertex[in_descriptor_requests[dest][i]];
      descriptor_responses[dest].push_back(v);
    }
    in_descriptor_requests[dest].clear();
  }
  in_descriptor_requests.clear();
  inplace_all_to_all(pg, descriptor_responses);

  // Add the queued edges
  for(typename std::vector<delayed_edge_t>::iterator i
        = delayed_edges.begin(); i != delayed_edges.end(); ++i) {
    process_id_type dest = distribution(i->second);
    local_vertex_descriptor tgt_local;
    if (dest == id) {
      tgt_local = index_to_vertex[distribution.local(i->second)];
    } else {
      std::vector<vertex_number_t>& requests = descriptor_requests[dest];
      typename std::vector<vertex_number_t>::iterator pos =
        std::lower_bound(requests.begin(), requests.end(),
                         distribution.local(i->second));
      tgt_local = descriptor_responses[dest][pos - requests.begin()];
    }
    add_edge(i->first, vertex_descriptor(dest, tgt_local), *this);
  }
  synchronize(process_group_);
}

}   // end namespace boost

#endif // BOOST_GRAPH_DISTRIBUTED_ADJLIST_INITIALIZE_HPP

/* initialize.hpp
FPD4SB3f9dfb1kx3T5mG+X4g0/a7cBgvlerSWzTnvTCjPa/QlON7cSGhtNHBHph7BqtIn18BHhqcFiUJKlBvIyZXO9ACR5+6XlwxNL1aJolmCVc4NE3fYjzNJx1v4KGfB/iBExylMwnSdahCLu8MM/ZhsoSMnuD4nYQh2qOiPcM1nb4+DgpyRol8hrXu5HU77guqSzagigURS63tvYhgGUaBGEJwTppnJbmrbkN83gyNoEIh86ESr88R2xTmIrMAuQS7NelYm0Uu5gjQFxD1YbmY8cdhXOAS8XoA1YNmvE2ocjZpKg4DOM3Xqq7p2TCaaX7voGmhUEGE0xds49LeuYy3D8RadKC8tgQKoad9Y56f1R1DzdbSBIwh9t6BT0o9ErKC3NaMgVn09PHcE4reIwBj/rlLhRanEmbjL9qoC+OIc/ghXQJKyNz/yl3WtOwppQJmKJpRAK+FkdEgw9TgmRb85EdrX4+b/TcrrDAlqsIz7uyW+bxYLZQQ/BpsOyQmOCb03VEkAQSSph+2/rNZMNUY8O7QTlqtCl4iyRP5jpcdnwMCr42tj3mOVyEIRddBrPDAyPwtxrP4IJC5ZC9gFSHSNKcGb4dRwxob8MuQhsUXUZ6+uXMajl/L4erlFCUVQ3FiqkqxX3eVDMCts5WJEf0FhwCpCY3T3QhhWUmqolyj7wQfbFqP6lCWoZHc6POlEc6T+qonnDoMYEUNoCpxJ7f/IWzb7KFdHz5tCQ7ampYzeNabIdxgvphjSmOZVhX4H0HYlZ2YH/ixnKB0ErR7K3AowJhsGVMpZhK37cTsEO37BMZ/mfbSeOAx8g2jWzzgMLjcSAeAsgC8neUkApn6YHLYnrF5Zjqz8KWiDe3VT+KGd7W/s7vxs9QWqY/palMZe/MXt2sXdIF97rxNKq9wNOKKIfcxCvisHQeXnTLgOXXwY99fTUruXZto9mJFWkLxjLxMPEu0PKDuYGfx7qF4W7NjUFHTfbAeYNX6NY3A5WA0nImVkb7odgYeSgmA/1E0haFKcCjQlp8I020IngqOyz4IPxn0dAvy0lWYyd65HgjDOfKP4NpoU5cwcGRINsp7PgH/++lQDxDwoVaH4EAZEI5YHhbqNyvCi72El+4X0k/ismbCDq1mDPsHh8DkS1BitkdAda1zucoHG+sevAlZglFhoCdB77kRcQ1m9Ft67CFp4Qi4utjONLeIaGti5vUvpWbpdE4UoKiC4d9g5dNncgcU0yAShF31qMs/v9LeG4nlJxXlxdXB5v+cNqSoj+djSlPBE1L9cP2lgcSGSAGJMWMrBkf1aglwt1Ui1ICtb2vA90k//1UBJp7wGbT63LhhrmxRZ69snWsCIIC/o8rUF/68y4fVe7ajAdDkHsCyc/5tuByuqMzJFaPUgVJckaUWgKiHIlXeeSG4AsVTBrtnQpYrODTdam/c0ZQR50v+K19nrHrAnATS87fYj3x7sNPoDOX/dlD1VMRb3lfEhekzShZXgZ/X8zv4T+RZIZhjn8DY83tAzeH1VwJd/On3igmRVy6K+EMQFl3gif054Ix8Lc7Jn3kT2usZt6RZrW9cYlWPKsTF/PR08/gq3y3B1x7dwPTYXcCqd/EIxPRlBDK7mQPQmWFQfzqdMQKz3glI/G45DBCpNOKrH7YLhL/eCfIeGNiJg78evFlVcfY9IMHVN3/6CHzHJB9/PYBQ27mDJAI3HoHg5v7SzJ4YrbjadD/5GYKfS9fOEQTxCKIcMPtIZoDNGOqks/juw3pj3G5Mo3mPmgmUcdJZ9A0qarMY7mpU9gPxiS13x3ROC7BHtrBNcRxrmEHdX0UtZzPsN1WgeGA+iLI4oAzdwr6fBHZQAqt7WjLoM4HFfV0Oi4KXA2sFWWlImwS2Fiq41ZOMSlhYFi9IGzRInCQVeH6+GKaVyGTOmXFS3/s3eUC1GCZTO4ILqRjcBSAZ0DdKrlEZbJfAREAEoBZSAYyc08T+XzGMHNSkPpIiWKzxJEGOMliSdfIASSGMuRl+pdPaet98b1Oc62Md3cb6GL2W2UP3SZMiGB/MjNxbHiROmnVYIs31g1NuPqt0ciz62jH/Cqnre9JJSNcXnDMVA9XWMX7WiNv7LzBmWFy3d9ovpDFOpZR6xVZ49JDeG59fSMts3zaVPmsKRph4gEM7LAb40UOzq03YrDHeX0nIaIwrRnBpPzzK9cZxGZ83yPXm2QTXZLaGgi4k39AE16uyMhBGulbx+mmA611+9IWysl+FYpwWhwhwEJ97ijZuOyCgOPtt0inbSLJiIG+3MvBqpBG2edWD5CVSLcz/YOMI+b4jsjKQBuUmSQ0O/wTp9gh586G0Z8sf1KkjqQKO/ltxqZziKLgyYGaE641ugPtw/XcaEO8eClCPYQOcxapWddDsKNeRVrWwY96HedkIV/U/Fg3w3TgD3Fb5puneWRMKv1ty7dAwHMMVO43qIJaaVyaMZ74oF4zYNLT06iHVujtr1WfCS/8jKrfEVpQVwvtMfVxTD9kVQr16uL5XkiY4cZkVQEqoJzh9XDHEyz2ClX1nrnq4uq8I9TAHzJMSqGEud5BLhonhWdBhrrerauERzkslUBgPFHrPR/jMEf7sTKhKy4glA3+Dvhx8qRPcE+gdQI4wjR7OMGXJ7CGBGU7zdKziO4Q22TZe92kh9IJMo78G8H0UHwRSkJGbD1UIUkdzj7kjzNbXYuC/X7WNZ3BRh+17bo44ZforRD/GCKgMQxYE3IsKSCcVxSL9SJQgsfBlMkQ/RdkFh7bcopAmLy3OVNQyYmRGg2bU6pocsTJDmwVh3+ZsVcv59NHM5gVMrvVrV6oYTzcF48/e3ba2tnBTpmv815dtL7vduNvP3le+3dleH2zoeEMtaJHKLU5XsbUI7eHoz9GHMYi2+Kj8WTJ9E4XaaEzaqUjYEiXShq80cvvDYinsEQJj2QtsQbEtX/iJcL6caPcBOOPhmHnj4aMpPQmxp684Y5GLofHwiDgCYrLR8fCl37BodxsZax84kAaSK3UTvejEMxaN5jQxrWZ7FSBN6nYG08WQBk456OTFN6hbsEwQOBDaSooQ56sHDtR9TNM+JOVTRRYQFQhziBYKU0jaAF4Q1PXL5Pf7RLA8YKBBMVnqHqE4EgKKa4ksLEAECXygnuIWGEJjeVExId97s3HRvTvXDYEppXME7j3iCSQ7nqA5YbVzXC7EhgkREZateXZumMyxCRycvDcYqDlJzUJGJf/gegySYFx2bnVnJKJIEhAgQ2Y4QCwgxvCLNybcl30g5bB7iOoItGo2ZYSkZ154XffK3iQgW+T7+o5FGZ50SXAeOuh1HEXHDEnw4X8YxbZlxUHQkuAk3qMWQZm5xXhJ1eGoFgjwz1YwBwYiN1z3CLO6fHq4zO1mMWR42RI87QcKVsn320y7JLikhkR4PxJ582YKHpw1xFqWCnD3lRSNIySLtj5lg1EEiyYNYD8sK/1j3M4ZvTVTzlIypfwCGYGKoNhoaEr01ur2l6lzqv/0Ty2pCtQ2sggDakR+RnyTQXoMgnmi/3p3o+YPUkTiYJmrgRQlyzJ8+3GYqH+dIEayhCcmvFbjoN0Xf9FlC3lGgkOFH48olxNtPzIRnvEqbuuRHo42D2MJrpQk7nKZLIKogKTDKHWwa5tPkhiQSEDpcJx/Tsia4XstIHOlcOSrLvQkOtgcUHAq4g0MTErHp2nRguDugX1SePmhmW86wc8J2IVhvxa7NRIP1IWR7XyfuhsKP/FgvqlcCbyC1nFOoYT7G62IC0B/xIUVLmpPx/kbbPDOXhesA7vNCHdUOBDwlMUR30CONxjQ7fi5jzOO5OQekT46O+ykpov2SZ0XMquk3pwi1+HAlVGWyvkWcgTnq0j2unYu6qjPxVtQcjFr/L6HBGSBvYLpRdwNaYon8lvPlL0JLI4mQe4Q0xGwfY/t/Dl/LaYm1ga+/XimC5LRPc+SP6FnhUfAPCy4xnSvRiedu2gNUdqKAOL00kuXvvhaoe9PWkFU32Ma+KmUXwLf9ImyzbaWoOCX1f5jFe0HKdmUDP+iePjWxqC2NENosJC4s7WgQyljBb54kZQk7/GuO4qranNT3xVjQcpG4jSplbCE14JYPQeybGn2ogeqkkvY3XQYnZaWz1rcLFx64pyFtWbHosAJdAvX5nrnyJWBDbGi0T8F5yomCMgNSRBfD74DmkrQI+yxeLeZHBO6W1lN+uNzFgapTMlQiJSsffAKa+o4+0CIndKjzooCIaTDMxTNQptrVIwIlHJvZNB5XsoCtfjhxSWsj8JTVPxd/LUt2OTjadzamGuDvratAjb5CTeu4Esg/O+Y4qQxUOcQe2uydw97a6b0A8yNcdBXvJoX7UC5O/5fU05Wtwq8s8bTjNIKt+GzG2UVjF9nY/SbFZITuv2ij1f1Y7tKIPezl89oj3wCS4etDGNaqXkoiiYqzVm6EDEDb1v2vfheZ8z9buhlVvQvc7tj9C+adk/0r1F7qhIwwRzQBwFk/tXIv45YQ524VZ1+yF4xgGVqozKp8pTGU8nyMyVNAmtkWeFN8MMFiexG8ohK8ebsiqQa/eDb0TRX6fTO2YS5QLrT45HqqHIZyndOiEA0V2CAGwl4yDBnb9H/ciPJ5ZFuiGwWoI1hcSKREWIR7eBeaIkBR/AG8RqDuHClAbKwbf+BXYgABFtd4L4pWPJkYqPHISkCvwHGYD9axVPPo2bOgUairGbqHkXAbQKAOh76qXx5RqWtyIqwk2gvYRdYtwpqRRRvSuRIaLmZtTD/ZDwhlhIIHJ0RqQN5PYZF3t/hb9gbWvpGpl68GIXf6ANrS3DUoRfKlU/gV44GE8qYtQzbFrcolQIhyDCx5GEE4jX0n3QMzhSZCG9mQKf6L0XBh2E3ctWKyca8cSA2g4z5st+Nhoh5RR2LXivWwOA73M+3pXf2GYTpAXGgbQ8v4Y3d0f4L8HhL7Wd74a7PMkOzbkB8SWpnQLstWnbtD3zK3MEuvr7AuucsmnE80xsy38smQ0Proc1xsUUL4WOZvK4M8gR+addPvmxdA5gqEo0GNg8ETHDFUI/ug9NXTGxfGQ3DmQQ/gk87wN4a7JFahhzp4gL/TnHlgvS2x8ETYTNUiA3Haq+z4s0mpLH7uvdXDfKUNl1nkyIiUZYE1RQw+M8LwM45TDIjpuctexARoVLQ5SEMSMjGm8SSAzUpoHg+BKxEQCjOINEy8iUqVpPWsB6fn43BZdeMoXGN0lnFPjpXMeKqqk1zEuInINJmnwwhJ2ZsO98hd107ks5jAYmps8CWdJJlK5T+Mgc5Xh9Rhdndg/wQPAhRZvdwyPyeaQACLP3TsK6aAYJwRGYKmPdy0GH2UIs1vr+1Urod7rBO8w2iBW0lHeSswQ7WaLVdf23wRGnhd//FmS2FjX8rd2wjA/pduBI2VCKIK0ACFggZewnktcW9kJzXrzKzcfXkfCNDyP6GVfrItNuhcxKf5NtXOdoR8m4FuXnugbesYjFvz8E2Zs+aWQlweO5NbuYHRVXz4GauRGioQti8qlGYhVtrOJS9W0W7UVXXzVPgcLMJOGbOzVClewL+SGUDWTFzeULUUkHTlbzKqkOXMXv7bCFu6N6lUETyAFVPjq1LdQiRqnDTZHpGGb1mTWYw6a0VZBb1Rg6tcmO5nAv6tGQQ/ISU1QLUe8NUBk/SK660hPR+4BHlEX9MvEMhxt4MjztvzwUJAA3zacX6OcK+jPWFXtollBt5DeWDPueF0BEuHLsRocf4/Gwf4+TsqHHEgFA7QyPhB/Y9LEPk/q18VG7Bfk9JpqghDlLzWP2ZvjvYj/WfAAyeSE2f3KmQttXNwMlvo31Z0Ldl++JoaUUG6rqo4w2xE2yW43EQegKLXTBXo8kgeYqVCApbwMYIqqvFuo7SpAHF1SVI/NQ+8Uf11PT4gL5r5gqQWiZCVRNmFbG3ENVDr24kV4PIkPYzifTtfM5A+PaL5xlEQ4OTKBerTJUEfeIr3+Pxxa7YNQLsfMEVhwhKNebQpIh2uhVSlcP2SxuikailEObgXvm5ouZtACojlP/COXL8O9gr/sqEHQ6gOZ011+GzHc8hr7RvXFrevS1Bn83RK967j8QBguglAC78c5cVH1o8kCcEPwMRDl9u2EDXDZ99JIGdQzicg4OKNquxwBPe2Lh4Su2awYCtbOIX4tx+XhA2jcArS6fWPK3Ia9Zwih0OGVFiJhGAY9AxgmMxIIGnK0iepumEYRDgfAqP/xk4cWewJbFDOJ5Ug7oU0MBQvMMUz78fnXCx1UnSU5ACiFH64v4iUUV/ku5m3MhjUvyesxQK0jQspoaeyA6Uok+0TvIIrW13isC6309mJf8x5WtWjMbsscEJz250qMoaYuWSZpR6/qFmV6ZTb16L8O995jZD3qPv69aGf5x9VXnBXS2u66nyMDCARDyEYv52xJ9oM/pf6PbSYKoxWv8xyiEJiI3QT33uLp9fTXYQhb7nzu6ZLrxotk9oPV75s87AmWN1vzif4CRGA/6TkN3P2rd00Cs03F/JYsoVZkIjfRO2pZhjTlbVAAYKp1SAnz40TUDt64SPrZ2YIEgR3enMTqhFjBMHqBjMhlF7Jb13asC7QWmwGa5G9B6ujuDC8EPeSX3a1pIiFD5xhJQ6yG7I9cQbrHcW6180KUeAqCVFhMqmG5Imbxgr5ilPD5YiNZCXLDdFqswGsSz9IsbstyNfE6PuZ8vkX2DrzIZZF/QMcxz4y1c9pF91FZ1jYyb//+4KLZb0i6UUSA5ev8mTEPeMB3GWiG2R4jbskO+JTmD3CU/ION1wPYKzK4KhBQd32y6RdmzAAd9+oIXpOtYsWP/3BemVjpW7ynJHLokwk9CgSL3ENa3hcpmIJglaRqghVWSpJuQBIcidY7dINE6/a9woGiJXU4oBMxZqtaeEtFexbM1pxblDtKYScmCEfo1Ez1zR84LjRg+3Zgt8EjRydtOOW02L2Wyw++XiD8fsO6PXrYbXtcv3StvOrVffOrFtuKKuYjb/pKjOvay8YS0xYR7RBJK55uKS549/e/lUJN97ebvdO4ExBrGB2agehZMX11ykSBk4CvXt4rCSLu6OJTXwXH84d41JZV9W43dO/O7ukbW8mZ/b7acLG4bomYAu8aYKcVlaB/O1N54NxLNY3hZho2zLEYidZ6O0txOQtaeW7uL6Tls/VJkBbun/X0Jc3oQqcpU28HvG2cTVwx5ViKqF6cxOzUo8iydz8NtXUWd0Stz5+WuGWprhvKCXmy63zNRSqC7taWuEE4y4Hee4kjl7A3DUsEavrKKXm9QwqU3DYo6bsmKozejZ6KJGGqyJNtMchmXOlrk6z+ks1QQxUu5BWGZH8bzQwgBEbZ9M3Hf0lbQg3X07/bewX7s0pkRUT0McbH9Bc+09xyZYgYDvBbt7KD3tEpgQ/MTz2+eNCHSLYIfzBujnlBEvqx1ainBysFoSp/nRz5dpVUA5C6kD235A4M5zOAOtsIhq6gDCXYdU5RoeJfvlkEvmSboJubUmrHjPjZrO0URJrahUn8OQGjGbDJZP6SftBdYD3HkRhtQMiNZJDfuTGd+cAeaSleGtaDy1VE/IT1DQrxCE/PC4w87US2Z70zcn7tp7gYAs7X0cE6CC
*/