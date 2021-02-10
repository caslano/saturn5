#ifndef BOOST_METAPARSE_V1_SWAP_HPP
#define BOOST_METAPARSE_V1_SWAP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class F>
      struct swap
      {
        typedef swap type;

        template <class A, class B>
        struct apply : F::template apply<B, A> {};
      };
    }
  }
}

#endif



/* swap.hpp
wU+oQhtJtramReLER48H5d1Mr1gX6wbacUGtHdbgcuzSg1xZeEPU4NvcOCLZd1iiqGrjTGrKmLWDkR44fioemxrrJFzI8thvcobfbqg1JbKrSzF4nSyWD7MX75CphGtx7bH/lXvMI8HndpE4aRDnn+EfUEsDBAoAAAAIAC1nSlK3trkE3QEAABMDAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTI5OVVUBQABtkgkYGVTXW+bQBB8P4n/sCKyIlm5HjhuWk7IUpSmddokWDaN+nqBtUHBdy53dsK/7wL+qGQJCfaYnZ2dgdihdZmyOGFxqZeGbm/YvJs6txM2TdMZ47zGv1tCcafqFToWixMiFn0Tu2AXsMB6hzW3ZY4srnFTNQTIlVM9kwg/hTAKAkh+sW/KoYR0i1cQRPBsdvQiDCAcy3EkCfLjKWU9nYRWIbddIZbqDdmjooMnk5fLEvM9S3gNP7e6pSeWkQyDA8t9qlYS/FEYjD7zPPvCr6PxzWgcffXZbZbhxvG50iu0El4bmsTujHaoHX9EvXKFhKA90Zi50mgJWWUsHjFps8FW34cThVtX7PtW64YXqEhVg5YuRg71DsRi70hn1V1VtgS9VVlXEKRfcsIK5zbUcCgh1mpNAS1Q
*/