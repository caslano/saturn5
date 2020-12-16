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
P4AZyOTMPlyo0wtmIvNnNkZSehrMQubHbOaQtgNg2WRBzNIG/lgNlifkOXHTL8VhklLO++09dLg5TEEWyOzwnhm1YSrBylyzqmBaMr7fOMnV4bBEYb+QA01mwVKENZvv3hMEM5KFMluzbdgLmIWM96Vy5L0iyybzZLZ9mmEzLIcsjNm6Yr/MhuULlpn3viZMEelcQ5dnb8/AVGQ8bmPpNWNgOrKSzKQXnjeApZAFMMt/Fx8HM5Lx2r9qR4TCLGS89g0/FlPBssnkzPqMWfcbzE7mw2yo/NRxmEPIpdHF0+9hsih6HuO53Ir5FaYm4/MzDJy4C6YjC2Y27ofQaJieLILZVGm9eTATGe+17niVkzALmS+zpka3LrBssiBm6YZxalieEOfdcFdbmKS083lrWJ399V8bFUUW86+tllYZO3zN5f/+P/xk7b+ZRKNZQ/eRb4L/2gWzlsb1pdCMJ+qnwd6Q4d77m4UuatkKVkDmxuznA6WKwWRl6F6DrTni77ErYQoy5JlO9ldKtUBYazLs980a/pZTHdaJzIXZzWmN3sLiydyYLTnaKgGWSFac2dwWGnOhJfTVk8mlhfe7a6VzXMaUejkSllm26Nz8bv9Ye5eFZZP5MVvU8EspmJ3Mh9mgyTPWwRxk7sz6l3/UBSYpR5+pzBY3aOwGk5N5M1M0+LgDFkWGnn2zfcPbeMCUZDIWNzNG2wGmFvbbseDvxjAtmQ+vb1Hxp7B4IZehG0qvgiWRBTCLjvNXwwxkvJ/aJR2awoxkQcymBi7eB7OQyZnJl8U1gWULeS6p9LUOLIcskOcyrUYlmEOwQ5duTIfJytM5xqyMcpkapiQLZra+61EtTEvG13yyoeAVLJHMg9nXsIbLYHohrrhXeh1YKlkosw7Ju6vAzEIu73rE9YVlCza95LPGsDyyMGZ/NH34ASar4Dy/0nNeTIBFkfEZVV1W+hVMQ1aBWf2vto0wPRmvb+ye7j/AUsl4LvG9pl2DmcnCmSnnNUyEZQt5eulafoLZBct8VXwKLJ/Mj9moasOGwOQVnfOsG5Y1AqYkC2G2vdQMd5iWrCwzl+Glw2ApZDyXSreqvIIZBbM8L3YMZiYL5/ud0kyBZQt5ujUboSi05AF2Mlxb10mrx2btzK1aaIOGKpT/2XppbMKAUpV3/2t9dWSyf98XbJCOSd4/c0IuLD+66Drx3eYMnxcDk8U424aKbu1gCjJvZs0nB42EKcmimeU1GfcUliis6Zqb5QLTk+Fa98127vylKC6FrDizar3KuhbagP4GMvRsI9We3WCXG8xEpmD2MdWnDSyTzJ2ZZkT5N7ATZPjM+WZrN73sBLORebG44aPXp8HsZHJmLa73bgjLJ/Nl1qtzpf4weRW6fjIbNnlsH1gUGV+z4cK/U2FqMr7myuMxdWA6Mh9mAZGzi+IShTjdId1bWIoQd6px41ewVDLe6yG1LqwttP5V0snwebRJOkLfc86QOzALmRezR7+cPAuzCnEXXj67ArOR+TH7OnL5fFieYIfH532ASarS3Jndn1bbHRZFFsJMuudsFqwBGZ4Nv9mnjo8bwbRknixu+bLzfWDxZL7MDpl/vAvTC3HB/a65wgxkPswuN7aegRnJeM/ubW1wDpYuxGVV8WwDs5Dxfv5RY8kxmFVYM/Lc/qYwmxC3du+OfJhd2O+koroD5iDzZ1biQ8tNMFk1575MPPPEDIsiC2D2cUj2GZiazI/308teHaYj47lkXDDugyWSKZit6/I+HGYgc2fW1vSDF8xI5s0s5dKkabB0smBmPgGq9TCrsF/ckbY5MLtgmgefj8AkKueeHXiUegmmIAtkFrhr502YiozXvi/cPg6mIfM=
*/