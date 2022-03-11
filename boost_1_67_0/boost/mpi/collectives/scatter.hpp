// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.6. Scatter
#ifndef BOOST_MPI_SCATTER_HPP
#define BOOST_MPI_SCATTER_HPP

#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <vector>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/detail/point_to_point.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/assert.hpp>

namespace boost { namespace mpi {

namespace detail {
// We're scattering from the root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatter to do all of the work.
template<typename T>
void
scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
             int n, int root, mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (const_cast<T*>(in_values), n, type,
                          out_values, n, type, root, comm));
}

// We're scattering from a non-root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatter to do all of the work.
template<typename T>
void
scatter_impl(const communicator& comm, T* out_values, int n, int root, 
             mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*out_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (0, n, type,
                          out_values, n, type,
                          root, comm));
}

// Fill the sendbuf while keeping trac of the slot's footprints
// Used in the first steps of both scatter and scatterv
// Nslots contains the number of slots being sent 
// to each process (identical values for scatter).
// skiped_slots, if present, is deduced from the 
// displacement array authorised be the MPI API, 
// for some yet to be determined reason.
template<typename T>
void
fill_scatter_sendbuf(const communicator& comm, T const* values, 
                     int const* nslots, int const* skipped_slots,
                     packed_oarchive::buffer_type& sendbuf, std::vector<int>& archsizes) {
  int nproc = comm.size();
  archsizes.resize(nproc);
  
  for (int dest = 0; dest < nproc; ++dest) {
    if (skipped_slots) { // wee need to keep this for backward compatibility
      for(int k= 0; k < skipped_slots[dest]; ++k) ++values;
    }
    packed_oarchive procarchive(comm);
    for (int i = 0; i < nslots[dest]; ++i) {
      procarchive << *values++;
    }
    int archsize = procarchive.size();
    sendbuf.resize(sendbuf.size() + archsize);
    archsizes[dest] = archsize;
    char const* aptr = static_cast<char const*>(procarchive.address());
    std::copy(aptr, aptr+archsize, sendbuf.end()-archsize);
  }
}

template<typename T, class A>
T*
non_const_data(std::vector<T,A> const& v) {
  using detail::c_data;
  return const_cast<T*>(c_data(v));
}

// Dispatch the sendbuf among proc.
// Used in the second steps of both scatter and scatterv
// in_value is only provide in the non variadic case.
template<typename T>
void
dispatch_scatter_sendbuf(const communicator& comm, 
                         packed_oarchive::buffer_type const& sendbuf, std::vector<int> const& archsizes,
                         T const* in_values,
                         T* out_values, int n, int root) {
  // Distribute the sizes
  int myarchsize;
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (non_const_data(archsizes), 1, MPI_INT,
                          &myarchsize, 1, MPI_INT, root, comm));
  std::vector<int> offsets;
  if (root == comm.rank()) {
    sizes2offsets(archsizes, offsets);
  }
  // Get my proc archive
  packed_iarchive::buffer_type recvbuf;
  recvbuf.resize(myarchsize);
  BOOST_MPI_CHECK_RESULT(MPI_Scatterv,
                         (non_const_data(sendbuf), non_const_data(archsizes), c_data(offsets), MPI_BYTE,
                          c_data(recvbuf), recvbuf.size(), MPI_BYTE,
                          root, MPI_Comm(comm)));
  // Unserialize
  if ( in_values != 0 && root == comm.rank()) {
    // Our own local values are already here: just copy them.
    std::copy(in_values + root * n, in_values + (root + 1) * n, out_values);
  } else {
    // Otherwise deserialize:
    packed_iarchive iarchv(comm, recvbuf);
    for (int i = 0; i < n; ++i) {
      iarchv >> out_values[i];
    }
  }
}

// We're scattering from the root for a type that does not have an
// associated MPI datatype, so we'll need to serialize it.
template<typename T>
void
scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
             int n, int root, mpl::false_)
{
  packed_oarchive::buffer_type sendbuf;
  std::vector<int> archsizes;
  
  if (root == comm.rank()) {
    std::vector<int> nslots(comm.size(), n);
    fill_scatter_sendbuf(comm, in_values, c_data(nslots), (int const*)0, sendbuf, archsizes);
  }
  dispatch_scatter_sendbuf(comm, sendbuf, archsizes, in_values, out_values, n, root);
}

template<typename T>
void
scatter_impl(const communicator& comm, T* out_values, int n, int root, 
             mpl::false_ is_mpi_type)
{ 
  scatter_impl(comm, (T const*)0, out_values, n, root, is_mpi_type);
}
} // end namespace detail

template<typename T>
void
scatter(const communicator& comm, const T* in_values, T& out_value, int root)
{
  detail::scatter_impl(comm, in_values, &out_value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, T& out_value,
        int root)
{
  using detail::c_data;
  ::boost::mpi::scatter<T>(comm, c_data(in_values), out_value, root);
}

template<typename T>
void scatter(const communicator& comm, T& out_value, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatter_impl(comm, &out_value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const T* in_values, T* out_values, int n,
        int root)
{
  detail::scatter_impl(comm, in_values, out_values, n, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, 
        T* out_values, int n, int root)
{
  ::boost::mpi::scatter(comm, &in_values[0], out_values, n, root);
}

template<typename T>
void scatter(const communicator& comm, T* out_values, int n, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatter_impl(comm, out_values, n, root, is_mpi_datatype<T>());
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_SCATTER_HPP

/* scatter.hpp
f6zyv7jTt2EbKSA9P3lIOx/82dzii7tszi23NFsrtgfOW8bSbh0edBtHfCp/tuTop3DvR6JvF3afWSzv9DGGadMCy/Z6+VSqF1T1GiuQ1TWNysV7LHwqv7f8aYHVWzK0wOIFxpchOlVHC9yg0Fo2T6jdtVyJe0fcynwneKB8/p2r8tZK99z20x5uPpWKdbtvpmV7z/lOX9klxynOI2VoC41Q4wPQ+bwFS6eVn3c1caK/EHlxon+g77d0n1DInoOfnHph2424VUSjyLMwJcwnxUOJ6NtiZtRlCjNq/kATcNP2tya5HaGHex5lPg688N/siCQUxvyljjBvqtfQ2oMaD0a+/Qy6IPRyxmtrilhdVnVz5WiRCScqId/ofYMX4FGJo9Q609+Qr7zRO892tqGOxY8yoLYv8u4u/LaOSGmfj1D5F1SG8jA0XO4QhzJM7b4mFhZHthFIGHD2Gk+p9d8DyvVP4UQwmZ7IZIaNXn6ysw0KPKXbehy2kNkHlCDHcCIA9pIbntKiSzhRB/nZxhcctvuJB5QiZ5+JRC8+E2UH90b6B/RGUgb1RiYH9kaKYkF2bvR2Y1M9q7P3/8Z9VUQDzgqtzjbkVc42MrG8Yw/wqKBUuu2kVGodJmILWSFiW4XhUbJdRBCRswfUgonYWK6L14CbeJQiV5FE3QdElFbHWLaJKNdfdq5RsnVCKNlC5ijZVveIKEH7WP5LYUSUQaiN3gx2pdtodqUAtwdKAb4PlFoVHrB1Sj5gC5F7wHbv9EDptuJBwJksztkGO+5Grz/eRi8ezlkR9wM2F7JwIkWs6Df2MgB7OY0j4OwCC1LtbOM7R4CHHZVSqzQxW8gTYrbVx/iUICYstPiUaHliNiUWfMqgyI1eUyqlHIrPRMPYrCgWDc6zjUAsP7GMUQWcLWCJ5TwrUsZne0oaQeQf2xPpHtXjPM95ttpLFVCrgo9WZOpTWHxPfBTCr24KVWyhDlDjXkBUc1R/HPj2q0XKFuWGdx6hGXa5MOK/nUhHuZf3TOnlNwU9h9+6t3wJEiXfX9ZxGFEt3HST2sc31jc9W3pd5TImDUwi3YXiokV/13wblS9Gv439Ni1hIX+JnEAkX48A61rD3FBPRDUXMhCHfa6zYMhD9trrik5r+s0g7f1w4Z9evN/As5C1ChV9QF/ZlJH3BW2jkXRyvkhm9q3tuH5HYGgvb1Z+a2BoR6Aya2RUIB0r7OQNK1mM+FSCU7dBcpzeMhziZvNybkyFI0PYfWtdfCtXbxltoLZQ9FKyzii9iv6Dq1abn+cbRczLFMEfE9hnCYycIUz+BAGS2lc01T9+ttRq3Kwv4OzscLroMA5z6b9HbT6tMlhURqCKf8l3s78sBG6pIZUgki3rI2Xdy15lE5LOLbvX8ckB+ZKY6juN98LLjoKuSuWITrC3Q2hAUNJwffmxSsdUvWLxYdBac2fwH1fN4BrngrVhV8JTYYlY1IE8nz2oNKmBexlRHjNjwhUgY/7FT6/ZIqUq6SOSPare89BAQwpN/+Hhu1aKtR/n3SZWgIAhoVXJazcntdAl81Zo4i2XpwHpZUmjKbzNekb5Z2YiqX1Notd04KMwC8b5Cwgp/PfemHnIM0g5On8Oo5PRxvpj4oTK3i1WwFvx+bcVzrFVCsM9vy8SLeoZzvviE7vdjP0W6DSGe+MjSqPPBoPipzV8WQMbs6Jx9uK3jbmm1NtW2rZ6ZCrzNEe2Z4LPE/6VPxJnVrc4Fzz/QOY5uCVXy5F0u8W1Ze9Z2VD5lbvalHZYYTz0fOybNMivW6xsIHCd8Pxarptz15f8vF/uEEVVY+k511EINvKs1h5sumGnsh023nNxmt8DfH7pWSGDoR7LapFQcdHIDSp/O455MsKUQW4k83tUH3/PHfbEb4Xq0dA3fLBxXDbfKxiYyuQSXsP7CubPM1N2yo+Wi5C55vEkOm95ikHiL8+pbKHxl98I/9Ujawgxx3X9IxqR45twa4brOr4Q09wUdeu6xet6dvnJVpu5u8VtW3bM9V6zbfLuJtTsRY6ukZayr1Szma87/YdygeAfeuNA0ZFHzeauf3QFzP9NddafLKOnNTctSe1vnCTAsmN26plF4KL1Mr8CI9VjToomyViPjuuCJ0L7T4/fFyRS7IG5119YzOLk+/uKGR/OLAD7+rznx+hI7JEHWkl+ANjMOpCkPjp/1Whp1JtBselSFH8pTd8VZS1grqEYrNh0T6nXt/pZwvLK1fTStYrDPGUH1MQDN+YLLNB9rYjp0g6TzaE9zphJyvcb++joTzN9n1jqhwYbFie+NqH15f1VITuaV9+pUrBjNtNouDjot/jzBEjt8tjfbLr6nYC5PqrG6Y77X9erMu30OmlSJcjk4u9c+f32JpToZxdqe9jxwg1GdhpQY1JX+b0f0lYm5V4AUGZ3mUrW0zmYnTpdurz1kNw7L8wbKmADPNL85OBSIfdzI+nft1u1QcHsXHDgOd7JwqRNiwBuhy5XeRx7e9M5wMvB1xNxt+RryDxaE9/HViD/V3Kl3O/uQ97QuqBiLuy7K/Q+K0SRt9GusH9KT7jWW2N8FW611t/FP+fZqhUPfDeltB7fsgOocYVjDyano0ArVGN2bj9U8M4CyIQkbdWXzN/m/7SU+AvtU2Mv62IF7Gr1iSl58mOm44mCv+WEUovV7c2a1dkIPEjoEl0N8Zf7DoSYy+5B/JeG7pEixW7BsGPk1N9uA/1ta1/R6SZOth/AVKv4iuzhnZuK+5CA2WO/t0zj7iYEgqehOpM311UMIcLJo6GBXMbpLTc3pw4VSXPLK/y5l0e/cvxkJ238tVn8Omy9wYZvdcYxjwuBq6+9Fw9be6YFp5YOjBy/QudKxRZCvvetDmYNmXrrM3kf/HQakDD5KR4L4kxk8LJk8lxWdzoKbrKv6mtNc5hI3VP8LQXR/onQfzLp//qKc+zoDdN19k9K2qtNnhp6+Nu9peVbWiX6XYxtc9xalbSkp3XpY1+M8dE9ylGD/d5C716NffrXQaS1+ZdkuNm0yfz8bOgv2seSFoVUe6FXXUkfr86fPrbld/0QRxsaIMIf5+j4iohg4FIyQCTbnmqlhms9oze4/ZpxQCZXMmDaaZojTGR8B7xJHSwIUp49FMurPawtSjyR9fyuUn1gtEvxwQOg9WWd7JQ/rbdBn0by++qVRXnh5dutsbB4sGwTiXdTmDCm+FXz1zs4TQVyE9obFp9OpqYFsPdG5WVfBm2GZ2GqLBehsj2hYXgTDSrv12AKas0Z9YqCHebpa8IjCxQfEezR9ahGSZmifCDnyCOyTwhKhZ3AAKdYMQzzzr17CjSRXAJOdS5um+ngX1M0WzQl5ttM8YP8iuzdtOgMZw1UGPZor0s9D05DGtMamxOwRHU39GRLT33/6CgOTl5ck011or5/aT+QHVNbbSj+IZTyE7EK4xWv0sB5BOhDrJzKDL151rZ61jZeTc3YFgzsYIgeerrjPv4Mcve0GznuhTE0VsQoCjZOVvqhW175fb0z+HgHJ5aIHs7Z3mG4lGabXcfw7Fps63ZEhWmjOpLECyfFT7X5QaFkvnD+LeQ9imOcvbgzGy1N7dpv3KXEfVtrm9MpUbkLSLkvm9DXK7NM+f3z5ZpYdyjbHujOpoJS+JSugNP33ryhQy3FTLyPxZR7dVgFt4My4eN5d1FJnsKTX3aivsdgH/z26eOEyNUfJ7MKdF5sEii3lnIHB9ei1lhYW9AeG2CbG7HtSB96wK6GGaMu10S7d0545vFYfWtYvihgs+mcMDsR5Mio+oEOHYBLKRp9dsmTwBsQ1/MLrAmxeqlRI7aQ4CX8McNZrcSClEkjf03ma1iz56PVJt8Mu8FffpjPia3Gfn/gZBeA8ihxmwSE1dDGZVsnmsJziaE7FHrNbWcMqS3fue2hOjYxhMkO2WCebT3eVor3JvO96WU4PBarefzHcWvT95Jhby/9yn9e7v4NZKFKjzRE3bzjY4cty/TJmqdSS+R2AuXQpvqRXLcZdxINgF8kZ0O+aIA0zoS6JrfHImASf68Prl/L+tJ0Wobr1uWjvQGxfXlj/fhdlPiBnDcdK3gdQywxONx0zV7s0mbcbCxgXpGpdz3qGhqomQO4WB/6glFIgt4/9vzLcylBDfs2d4EhaR/nF7aGf9ixmLf8DFrWTnJ8bpd2vsQzzcVDQVv+hf8geBPA0J0TsIB5UGyYoeDC+j+/v2VJ+irDJMuNGufxz13OKiUXK9wfi1xPLj6aazx3+knw5g1HPuMTdZa0ww/1JKOmS+sJ6TZ8bvtvKh/FLb3U+k1ml/MS/DR9kCf3sP5p/HP/Fv8s0/y1iTdHCmNyfH6PitUGTvZCgpKZY+3+vC4EhE75s8HXvWFADNI/9mbF0zJMb1JQofC4fI0/gfUMzeBnRQgKIu+GPQwhumVTwWwwrSc/sMKhsDSSXhJeXEC+nRomMCNNn5QXbfzJjpwJW0B/Tso9byGtD+NbERo57LaHYP30O9Bgw7n7EpzdmsrW/p5PbWHwgzmBGXsI4weQz0OFu6NKNEk9HR9zim1nEqrwaCx7AvN4Of0c/F8jwa9S5iE9rZ2960Bqn6czvx0V6AlYh8l3009/UAmlC9N/QJ3x9oTUkSjEcPqhNVKaJMySOY4Y+hRfqo9lewoucOa12SnEAEidS3Nv2X7l6pSbzYivfYBjPlee8A2e424DePflGIGqKdc9QNHt6U6eSvtYMwz9B72XN0UczsxDXWtiR5jPSaQKof23rFE2N6jsz9Xs7Tj7mgm1cIwIe/7F0kv8G05+5K19ExG7Qvl31O0s/KSXORLsD51YH/dJnvdA9MJNY6hDpldHUI4msgkzLG2+UQu5ip5rAztlDV1/R2Fy7G/C2iJXoe8yrcs/g61bVELdYXNKL8LIUeTdLGdHeouKCs+ckzr8kvtrIMkzCovKz46WpnNWdwJINgq4woMfvn+tWqVMQfkw9CGLeZE57auTvcc+Jzh+6E3Ri1DLS+soNJH13Ua8Yjj8D96cCpB4IzgcNyM7Hse3uV/Yw1nLc1pOZ/XOcGuKlff0s+GWCOPb7nI2oMav4g0XHKjRRghOnmjEZaZhyPCsQNM2IPGf8nxwSWM3fMXwsVbH+1mi3Mge9wi7ngM7uX7FoTDM8w0p1XLiVrbWx6aKZV5plybFBqrloQleWw9AJEoPQ9gXSe9NNpw2gAk2lMdZh3auwExgS5312bQPqWNDhGJ4cASEqBkXQ3HLdeaoSnSmt2G4gTyT9ek283+bI1q0TVBAZIWz/iAJzzGBdoqAD/e6x+I9Ti2+KcWqTJK3bmuYfV4+hirEN7nCbyZEeILgpd9vjoruyT2A2kLfB8owYUg5BXHIzcpIv2teKj4bAXpP5jSfw39XxhxDvLpMsluxyYzozEUxF0P0iyD6KQYdfL8WpPQ24KoeqL4ohUIpDg+F3iXliNCPG+UbSqQsOUV3vjbP8qukLWi3uiODgomCffxrtfyxSWvzxmXQiDnslatLWyR8F1Z7Lrp4FWF3RqGIEdjfl2Y9vC/hcP5271BSVDPzTQmzD/wC6b4hRYmNyCKC2dXyQtySjvwjGcbeGlCpX450b9zxqIBfcgN/lAkCKUibX86+aPl6cIXcrSvFGH/BAXVKkIs/gBDc9Fh9qXi7cdE7XNFD/d6UYZOlSDDBxTim7pbgFFxkR8ndvVysiGDLLDoiMQrlvW/3EJW0HGXCN8NLd6X6UDU7ikHNvp04+ZyEp+Aunm+Azyp7OSo6ctcLGLpNdyfeFsnzyYoSYo0vsiMxUWHt5MToL4b3OMZSYhj0Ub8lv6RPv+9zygtNPFKlUkfJhGgSncjipTumWJmcXb7S8yEQb9S8w19kH5hZv6dvnYrofLwooT7oxkaz7BHzdU1kpL0XMn0bjM+qF7UFJx91vCeXjVagjahjVNt2McHfrZf/7IX0wZ+XCsbfvZknHjtYUSObn9jGDpM7z2evYIXPXnJUAzOSS6TUGeYAD1xg8heetrbUUllAWsBr7jh/T56l0WSejgruUUo7HsRbau0wt+QoSOojLSOe3bmII9lzxN8XbwE/YnbbiuxNf4XWShKHAcQezD1PLTQ09KlKfCaMb4wrbDgmWv5+liL/RmDeGsSUBa8k1YpCtgmMvWUP8dUydENGsN2vkcqz3zPgf3KkOXR40l1A7fK9yGjUp52AldlnOWfKhJvyHCWLwxl2djP5/L4nrIioMBg2JE/qOf06TIpU5uXM7w8K+Z+TQrOYjhx/MuS4YM1Rb7banu7er1r9vKrbIwIz2nRlgZFlhxK9CL/3inJ8kHJaudWZA6KgcKshcZ5B+sRmgsMI+b9fSz6+zLkscQppfF7RyUblw/L3iUm1eFuBsxtJWzglStVAKnETgCOqYcTKipukZZSfLx0r5kcxb6Ms5kgxfzCvus3yZ9vhvSWV+rRbN9Eqdsbkh2SKlL8UX2bX4EKIbfdDe0TeY1cl7GMovhLjwExwMluRP8XQskUzmt7rvW395vYzjF09odrC6AdmfDPKdFf2wnZL9emdLtxCPkI4lfib9L3hV8EOQzNKRlTqJ05fixFewWRNjupkk+XICNfbDlavkxnv8HLaTv3FgxhLE7KmSEq5L9OoVoqBX562XcKVJU1PZC0/V76Nl84xThRMLtoO1+ef+f3W2+V2YK7dav82PFI12XjQ8XsKcBxkXluSr9WpfSmQHA81XDeZKPETyNc6qQ9kazKaVPrUovme9Eyrh54T7r3PSjgt2hvMchNGeYWHp6pXOWY4xVqMsn2LlCatd60z1cUzD282zTQYZg1UpqM6brX9XRhGpkSuiCG5f5J14cUIBkfEyPVxFQnq7/YWycv4nnzhNnf1/OPe/FBBZPEArz0C5fmEfUpQ7vT06Lle7nISX0FAydZv4CBO+tZv6w8DRioXERXnbdRBj1WDOz85jzfa2bJ6Pwxr2xYH4Cif5xSGZ29MU3kosV0a4e6V408Y9ORhD6p2uHv87y2xhw00/hz+e//Pnzryan+Hwnlq70RHPu2VWE07wjE2wwMo5sIeZ1wY3fvJkLEVFYtYj/q1PSHrkrJxv6Ny0hNCtOTl78I8PKxZje56letDYnH3fGtMm2ctM+5R/93zw9z5uLmbxLg3s2E5L1wxIVyDe5/Rwz2zcZ8mrB65OPt8pM//RB/aulqz0hft99dm/QHwsQf9meH7iiTbIH0tcdRzrUuv2KS7S2oL9l6oVhFciPUaCsEBDEIAsWui4XcEf9akJctulvo+ZD+svyFYlLVQdb1RqIZYFR0ad/Vs2tysF3i+7HTvenLmRJdG2RAR15MQPZecJVoa9qYzxcsqohv8dIANZwdi8euu7x8xZ0z0E8IKjgq91/Wx+Fh1OYlP8aZ9LDihp52Tm/arKyztud1xE08laZqAbLf2j9WQvOeokwaeSqI0cf20t25PCHL59t9I5ON9TmJVOHk5zLvfmv62WuQhNv6oSEyDvnXOeNXxGvsRqHHGkoulSTADDPv5yspV0LTw50yrSsbnQIAGYl54ca70yRKO2kKKDvrxzz8hnxwehvJmhgSx3b5+Mnil84dpJVqyfMpyX5ETQnfc2gPEDaAJIJR7cM99RnPGJPYgr/mLB50YRQ7ZBO4eHviBXo9wD9OGynvJM5KNhp5uomY8a7x2ehvhhi9VGAe9/PIZ//cF33mvzM6Scfqvo7wjFN4reAh6SM/grz6sxJPBMQ83wKN8YE2oEO6O0xHO/gAZzh/hGAENV9l4vEHlwfWlWDnhl1SlXsSBGlmo40e2/4eKt4CK6vvChhUEpEW6RZQUkG4QURAREJGSFhDp7hgapYaSTmnpboZuAekeeugBBpgZpl5+7/9d61vfWue5Z8e9a+6c2Hs/d+6a2pdVyoE4+Em5u7VGf646U9wwZKYMihWLG9o5thVjA5b88/Eo/ueD/s9giMhX07es5PnCYHlo1SCVc4p7Oy6Oog5ZJNlI9YjeM9yMOaQZL7iT3skMusnlfJVOrF4wvZV+DQ6Nu9fKKcJjdsHYKjTyhJmA0coykHBU16ZMQppnqdbmoybg/np/axAzgs2h1WWdSC4jRKK3id2HlCFRTUpIZ764IVQo9UMlKFjL6k/Tb68zYVfokoS3XRC3T0eIIGKJyOOerKguc85jKcwmidXvuPqHkG/azM9ttLGX9WVx0Q1l7A6jnyTcvoZLjPV1kp5JBkN7VCgdAsiY8/qH0gyXgEaVQ+ox5uMDVpSk9c2DBi0vuACmppUr4wIH7Rk5rkoLlLItwVTL4bB6XfDYP5JAfmZPWkSYw559Rf5xuKa3hD+W48Bns1Ayy8395zLq/fT8fkK1oOry7F/q7XFtpBhp/Q3LRGIsSGPaVakUeHj1UEZhQHjEIyA0XoK+DvK1RiDNztSi2u4YYYBkQ76q/AiyKCXwyo3ICevRd69zCjYGVEcXqG/eKNtkH/pY7t1a/6Der3++hMPLDP71irQ26KcMvdvHTY8XHGZAfC2BAgTOkXg+1X1zbrccO0/NXfN3uNjgcsTUlu3CeZKzA7ifuM59DpfYFIKVlXQBjylDMosHqLs+77XLmZa5/peQHP+3F0pVp12FBjMzDhEPWP+K/IIgHrTlSXI/rBPsZxsWkfMnCgIw7iHVlkhPh9seCNK3aobtVFjPfUvr9WT1YWb4pcWQpuVWjixKywIG7gfEKm3qIP+o2O2TijOyrL+iPy8M0OV+T0CheBLfV1O7twup3IvuVzBzClPqjbeQXuY11PSSwKsIbhqvwxpMngGoI7oHrdQJDONCTqbEEroM8AfbpvO3HaikPhBKYAkMmU/kKf2FejeE0uVrerbwholdsh8MQ2I5DbkbhWDLfCNH+uY15hFMFVEPWI9JBqF0VqybUCu0PgErpUfnKzDJWK8k/2eKK9LwVpJH9NMfX7EM4Q3+e+GyRLKEjXpyHJ5zhmfXQukaGL3M/EgKPZHrVPAI/H57yuQn5vDXn8gU0na9gzOz8pUBhQgKHHThjw00EECFwxZOA2bPAc4Jxxuy2r0ArTNi+WCAm1zNZ2FVbmKkRf3b0MruhK8T/FZwUGg8rYzi/y0DGhJyAFRW8h8knozY6fEuT1gVTFa/zjF5G1jw9dcRKZ3SIuE6uzLcusT/3bSnEnyAzwurP31R1zpEYHhqt21WmymPe58Iee4=
*/