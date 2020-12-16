#ifndef BOOST_METAPARSE_V1_LIT_HPP
#define BOOST_METAPARSE_V1_LIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class C>
      struct lit : lit_c<C::type::value> {};
    }
  }
}

#endif


/* lit.hpp
v6QjeIPa4FGaTRY59TC1y4jCX8X9hHSz4D/SPr7O+3gw6gOwyIPQtx/w7Azk/TI60zvjiiumlOSfjimFouLxjoqC/NKS4lI4yeXARvlsamnFlMKC4qLiwnGgA4WRksJMKS8bX15YUVE8rZDDZCSFKcaUBmxdAarZax3GMRVGshyNLBlXVFxeURnF0cIKjpKy6QlwYCj+SoakqKwcyZ2pwJWbQ6aRVpptD9MVxZlJKUzHcXpekkIYVs3Xp/xC+aaW+/6zuY+HQdn93f/BXMS/eTsW8DiL4p82fYAF7pLL5RIq1FIg1lJLaUtFqCRpSgNtGpK0tIAcyeXSXJvcHfcoLS8BERCRAioIKFYEBXwrykMePvGJiijIGwURBBEo8hac/Xf+m8f/3+VS/MTvbP7Z2dnZ2dnZ2d3ZXZc2/D3D8dJhzyeTgzc9+HqNmaE77vxvZ5Dz/axPtpR7oq6Cz3oACPcRlF0R563xweQmueYNMFhl4bDJBuZuYFpY2LUJAEuPwDKaU4LtbGDFFKwXEt40A1uPMCw3ZGA5UzDNySMGlofqAsybu8cMrN+YWqcEm+HyImEtBpawsH1AVu8CWT3IZDUP0vtLc3NcR8WxC/4juwS/h3HsesRbqxW6Fj8qAUs9Ul5xd/JJsor3QhmuXzgX/brHpC1dOZA3GJYh7wu4GtfcZKx2NnX4K9ZhfqBM4qbcRQtS0JENKfr05AN2FDLhWPI3Nv4/qXzAv8N3gdteyPUUyvGPLB/0Jfjb4j3j8kLyfhbxvDndCfB/RleODsk2MhJ/LsTonWn//mDI/o3tCvlsHjP+TDGeLObZLnmH8Yn2yR81uMD7vxH3Zcb7CQ76wCCXosP3/cg3vgj/bgbak8xaCHy/Br/X4fcG/LK1vB6TnDex3L1qabwy9AtIfw+gMxn+3kvJ42IfLcAKWx5qwrx+tm6OapuJYZJTkdJcOU1COpPDldYU1i6c9wGwEkOlHREOKOnP1DDJaacwyWlnxeO7wuYn5xDTkI9dwpX2VbMbE/kDPR7wg8rfjZUfYuWHVfl1Yfip8uux/EhFORRTuP7o8UAAxkeU8dHI+IgpPprC8FN8NCMfuyPuMrE/M5JMry8MyzmoOyu1+x3u/Nz1FUt2dpozZFaF3T0oSJ7w7jD3c80T9KpGFiTqtKS8TsAwmEyb4djLrqFAIXj/q8qyjTxnMHm+h8lzppLnXmH4KXnOQnnuPbZ+m7VBqgYBSv71vmE5D2oJy32492JZs722q6TDsBKbzIk+FZBAZc+hsuFvksdcxdP7kaf9wpanecjT/havUlvA83OwEUBtQSDGxwFjy7F/ZH0m55EREBynFobJzs6oSC+5KRtPpLLDyRI9AcE1tMVMHh9Aemuw3yxw5ZAwHlu6EKe+sihs+o7LWKowbPd3Dgy7+/vpRJz60EFh04dsiXbP2fajD/J+hG1qcmJJ1Ka+BOmPLFA6dAi21xLSoXJyXgMO9LJ18e7WntaVJG5fArXdoaQr8DfJrE3pUDvy1Io6tBR56qC2KqdDRsCkQQjgPBxGZcHfxEOn4uFw5GE58nAE8rCC5T+A5e9S+Vdh/gWYvxvzH4l4Ng/Zkl5lS/rgu0/ZktVIYw3izi+rs9mNyS2ksfab9H8t5m8bQ+eFddBglOmXxfiwic+NUMdB+WwHVDoOPOHcY52r44NJDiu4em3YlmOO8UMiBu72EcKNubChXBL719FAczrrNwdhLNYxYe6TZm3cW5yJi4OwjsE2a7NR9ZFMZmMx6+UVINK5DyvdOE71uTi26/GIN7tsebwgas8Bog9/k04OqnKTWG4CdXIIy13v9fUxx8lC/8AI9S9/Ao2ZKcbHBqbnG5U=
*/