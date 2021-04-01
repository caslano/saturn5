//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ALLOC_LIB_HPP
#define BOOST_CONTAINER_DETAIL_ALLOC_LIB_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/auto_link.hpp>

#include <boost/container/detail/alloc_lib.h>

namespace boost{
namespace container{

typedef boost_cont_command_ret_t dlmalloc_command_ret_t;
typedef boost_cont_memchain dlmalloc_memchain;
typedef boost_cont_memchain_it dlmalloc_memchain_it;
typedef boost_cont_malloc_stats_t dlmalloc_malloc_stats_t;

BOOST_CONTAINER_DECL size_t dlmalloc_size(const void *p);

BOOST_CONTAINER_DECL void* dlmalloc_malloc(size_t bytes);

BOOST_CONTAINER_DECL void  dlmalloc_free(void* mem);

BOOST_CONTAINER_DECL void* dlmalloc_memalign(size_t bytes, size_t alignment);

BOOST_CONTAINER_DECL int dlmalloc_multialloc_nodes
   (size_t n_elements, size_t elem_size, size_t contiguous_elements, boost_cont_memchain *pchain);

BOOST_CONTAINER_DECL int dlmalloc_multialloc_arrays
   (size_t n_elements, const size_t *sizes, size_t sizeof_element, size_t contiguous_elements, boost_cont_memchain *pchain);

BOOST_CONTAINER_DECL void dlmalloc_multidealloc(boost_cont_memchain *pchain);

BOOST_CONTAINER_DECL size_t dlmalloc_footprint();

BOOST_CONTAINER_DECL size_t dlmalloc_allocated_memory();

BOOST_CONTAINER_DECL size_t dlmalloc_chunksize(const void *p);

BOOST_CONTAINER_DECL int dlmalloc_all_deallocated();

BOOST_CONTAINER_DECL boost_cont_malloc_stats_t dlmalloc_malloc_stats();

BOOST_CONTAINER_DECL size_t dlmalloc_in_use_memory();

BOOST_CONTAINER_DECL int dlmalloc_trim(size_t pad);

BOOST_CONTAINER_DECL int dlmalloc_mallopt(int parameter_number, int parameter_value);

BOOST_CONTAINER_DECL int dlmalloc_grow(void* oldmem, size_t minbytes, size_t maxbytes, size_t *received);

BOOST_CONTAINER_DECL int dlmalloc_shrink(void* oldmem, size_t minbytes, size_t maxbytes, size_t *received, int do_commit);

BOOST_CONTAINER_DECL void* dlmalloc_alloc(size_t minbytes, size_t preferred_bytes, size_t *received_bytes);

BOOST_CONTAINER_DECL int dlmalloc_malloc_check();

BOOST_CONTAINER_DECL boost_cont_command_ret_t dlmalloc_allocation_command
   ( allocation_type command
   , size_t sizeof_object
   , size_t limit_objects
   , size_t preferred_objects
   , size_t *received_objects
   , void *reuse_ptr
   );

BOOST_CONTAINER_DECL int dlmalloc_mallopt(int param_number, int value);

BOOST_CONTAINER_DECL void *dlmalloc_sync_create();

BOOST_CONTAINER_DECL void dlmalloc_sync_destroy(void *sync);

BOOST_CONTAINER_DECL bool dlmalloc_sync_lock(void *sync);

BOOST_CONTAINER_DECL void dlmalloc_sync_unlock(void *sync);

BOOST_CONTAINER_DECL bool dlmalloc_global_sync_lock();

BOOST_CONTAINER_DECL void dlmalloc_global_sync_unlock();

}  //namespace container{
}  //namespace boost{

#include <boost/container/detail/config_end.hpp>

#endif   //BOOST_CONTAINER_DETAIL_ALLOC_LIB_HPP

/* dlmalloc.hpp
V5M2WX7rPJ7lY1jJc+1BAqUlpwcxkHlr6zY0SKYgvhHxX8ULk0URc1yoO9A1eAr2RY797/te++Xt6RaUk5wS1dJB9EGJUtgw//e/h+kaoylPwy6QFSza2c9pRQg0fhydsJUza3uJOEHrn86FKSXNrUwEOuQjINHccNSEguSzRnOvFMFIX868oEoZXFBXFi3BZfB/NkvpGHikg/pv6ESmsgdNxfa7ZPmS4cpI/dLzvS++WbIdM68HI5xct4viMJawOnAls8x9Y9nvL3DNb8Hq9/iCmTvcDf8IbxTQ46tjlavIjLVRqxSk23gaotN/CsHwTD9+pQr4tcQQ3AQ9wM/+CwYMcbLhjrM6pAcMQAPDQlnOkAqvT+pMoh7/Fnl0kyP5fGmLF/BTTG1lKqijY6HNTYVJDttNTFxiGczHWCYMbCCSpoD1vyCtPJjqw5oVLTSTY9FOLafwE8tKy+Hq+I+pJ8MYcEa3y6w99O0RXC2lMcLm+ARSzxZbdjE3j0WqZ6h1dFby35zy77AOaOk8detegJhwCRGLJr0DOu/BVEdpPeNMyNUKN1HRt93wWA==
*/