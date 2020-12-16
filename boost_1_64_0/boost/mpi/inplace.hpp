// Copyright (C) 2005-2006 Alain Miniussi <alain.miniussi -at- oca.eu>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4. MPI Collectives

/** @file inplace.hpp
 *
 *  This header provides helpers to indicate to MPI collective operation
 *  that a buffer can be use both as an input and output.
 */
#ifndef BOOST_MPI_INPLACE_HPP
#define BOOST_MPI_INPLACE_HPP

#include <boost/mpi/communicator.hpp>
#include <vector>

namespace boost { namespace mpi {

/**
 *  @brief Wrapper type to explicitly indicate that a input data 
 * can be overriden with an output value.
 */
template <typename T>
struct inplace_t {
  inplace_t(T& inout) : buffer(inout) {}
  T& buffer;
};

template <typename T>
struct inplace_t<T*> {
  inplace_t(T* inout) : buffer(inout) {}
  T* buffer;
};


/**
 *  @brief Wrapp a input data to indicate that it can be overriden 
 *  with an ouput value.
 *  @param inout the contributing input value, it will be overriden 
 *  with the output value where one is expected. If it is a pointer, 
 *  the number of elements will be provided separatly.
 *  @returns The wrapped value or pointer.
 */
template<typename T>
inplace_t<T>
inplace(T& inout) { 
  return inplace_t<T>(inout);
}
/**
 * \overload
 */
template<typename T>
inplace_t<T*>
inplace(T* inout) { 
  return inplace_t<T*>(inout);
}
} }  // end namespace boost::mpi

#endif // BOOST_MPI_INPLACE_HPP


/* inplace.hpp
hfYOXgLeTDrSVIYROIdgntEZO0IbNRx2BzwaWbRR+ZyzDumHXF3ncwbbFNFJ4thn39lUdATTTiTdeBrRbzz9Mnr9eLWW0/KEwvDWqyYtaHCI6QUNOs9fvsXJiejQpR+QHHvhIOlQlFhUF30MikhYxji8nFRAIpv9fFAwstqBZy7Dq5wk0XtJVXb+B4/wqPOPAArAhOeKlsAkEp7cwJcYdFC4K/mUld88tb1QUwo7wxc7o6dbik81F6eATvr8xuV6mPhYrXsASFe4abvSWbtKD8I6AjimUJNxkAb7D+YHYrAwwrjfS6mjkFqHtvCG6pSDbzCPIBCjX6ANvuJG6NaO+byFCAKB1A/na2ANGvrJZDheRMvrjKpN8FtW2Cd4hT10m6ywb6asMA1+nsnrZWWoZ3AZIOJJWi+4OzqIuC/XllzirJ2EGyr3OG01xUG+5ND7HmUSothmQ3HuLXywDu3AmaZuRvmCbjVcZhjlyXv3ZebJmwYNmAkj6iWDNI+bf0WmFoCJuDfSZr0LJy3OFFEW0MCI1HccVjrJfLqgMTBkcXzzEXSc4ARUtqsJR6rAbfvoC9H7aOseTgEaiSBT067oaughhlbTIZT8qbUgb/CFwfzyAVy8diOSb/QpyMJqmpy1cBFIsTDeO4ZtOxg13ax1207auZOT9THo7RE4HUTzfejtopAU6zKk42oTXWCQPJpTFEdqcY4i6tfVjdprJsl+gWyl8qELwqh7SbkLL9EN8Jmdcy41E8xePipA8+8OV7j1Fa8Z7hruBS5F83EMNI+gsxFcwdgZb7roRJ7YfwhKVbuxDjFnYLY4xetXGMSDrB5Ad27mOxb7h/OhIrFw4P3oH3uR2h+S9kk5IxIcjLYToANAmXTaAGeYHpz8t88wzt8O8v9Um/cLnqu/Tn8xTx4GvJve6cO/tvtL+cUNzLZAPbzBoZ+vDpMx5iSVylWdjzYPvYwXncLZyyib0xq34t/w1mr8js7GWyT3VvU6YPWk0NP4E40eF/ZCIIEZEqmiJvBvZSO9J1ihed6hji7+CgBjyJ01JURxerFGoM0CPg807DMKuaAQ7niBOx0LQWktTy90ilHIW/vGCD8EyGCssVbZTVW8FM9Rf7JEKynnUdFrhPwSIfCOp+zs8tpKqZSXRX/DtLvA7S+h0jWrGrdi2v6DMIJbqc2zVqiB/oUeOLyVIdA7tY73QzQt3ugKRpjRzm/KVTtfPYp2DupbaDRnYAwJqbh4t3ArVmpc3jx6JlIR/1y8fMtoTVEjPVMDK4hxhULcw61wTvgSJwoGyqyexjksHvZ9VKmqeUygxmn+7rcytUGq7Em8s+a/ZU8CP0fcH77oI8hfvfsHSS9xk4xy8ak6VC+W19HRCHlREpOcdp17gpShghR423xsaf1bDRmkv0UxRhwtr0LucpCNsFTOuSWgsbBzMx1zcwGXIE+uA0PkT0o6KLD+UmCvfFDKkKg6ZGPEge3k95PDydrKhRk6iO5kW96lDgI/HaKysolA9s1kUjHcZLObD9Bu4bKvJRUY+uwjH6b5kfjsoKs4a6Yarqmv1jMHmebANwYg01VzqnEl4mt65ihfcfTWzkgJTnvHA8xOfsGHnEzxpUnmPrpRHOTiu8fZnQVUYIntTbZbgc4DzsVStXopt2qTS0XruFSuunOEz2UWRVDgxen82iyZQX0LjHPB9lzPVadDGp5pQf3QC2U43LeTTRSmLnULvq+WKqEZY4XbKwGed9WaJh99mgyti8ngCwQxUbkUKIICVuim1JljUFvLkl6a/E27tC4prjTkZEnvvC3Q6OL40lmBBCwBMgNjYRc6wwIQV5p8QE5STeO6rTlCTqGYqHmk9PW/lnQ=
*/