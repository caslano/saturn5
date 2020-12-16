#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_EVAL_LATER_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_EVAL_LATER_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/less.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class R1, class R2>
        struct eval_later_result :
          boost::mpl::eval_if<
            typename boost::mpl::less<
              typename get_position<R2>::type,
              typename get_position<R1>::type
            >::type,
            R1,
            R2
          >
        {};
      }
    }
  }
}

#endif


/* eval_later_result.hpp
/1FyTEDjborG++kZ8MrUf3fyQC6v32okGdidzjJcjFH+FrfluJm+5oX+kXFxd8xf4/XSBDJNDR+nUZ+ypF3kZClTNFQZ7z1iTKPN9+npdLGf9tR6zPnl0SlSc1O5jGOfrA/xRnPUrgY5Eq/O20VZDFs/LKNmbV7IxCaq+6H0dGm6O0PlWIUY+P/Dmee96XyxZPb6p3P5w5H5n+7RFvY4qeGdqeSMGu/rg7juSdoxp+nzbnN0ks9Sbvd6433gsDxj2SjPjSKvJjMOF3cF934x1hAvS2Ze3kvv76RTkq4uWsOFlWmrLeP6OK7XXBqWcTu9HaVkfqK3v3cqNX5xfylrG2s4Z59qErzbFeD14akThSrzHA5wAxxLEddjVMdbqjh+nx/vjJMvoD56kUdDqn+kyTDB2Pn27dUXiv47FdW/+gZo/KIzo+ef3YDONR+K9OGB+1PSrzLe24DufYnV3/gWev1yoXevAH0/Il2Z5bOYNKM0F5UPJrI587dk9psLPLfj+FKW7jQnjT0zF2+JwIvAOtJo9p4wj7uyQ5ZKy5ZYtXdhOFtp/K0ZujGWnMB0J4pTqdDPy+sp/ypai6inmFdivyBfpGh7Zz2RLiSoK6byNGlOtY1PJfN19rp/3Vb/r1yLSNHxkzNE5h0+ceXjuzo3zVNa12N7jL2yGXs/ryLa5inK7uFU0brWq+W6wGJrY4WrEqruPvKxRfDNX3wwKitDvnL8/lao2/rfZN4wljx0qV1dgqevWYCnzwdPX1sxT8vUtBLGzktx2fsUiYJJMktLH7YDUKpMevywLa5MnPXLfKy1pV7P9eJ9HOLNSlohfQPFkVBMpveX8n56WjvFHaQ3Sn4cJQ2D89Unm6T5+WxkbjpW1+nN89TpLRF1GkSd3irr9B/QsRh9Mmu6YKLod77/cn/oSZxn5SiQ/asXkP0DkP23Vyz7Tm0qlHmfqjcfPc/+F2qYaGSd8Y4F+JYH3955tHxbjCpGm356EfyL1DH/Ez7Op99YLt+9AH9fDP6+p2L+Rpa6KD7PR/mZ3jKhxxLxXbSyKRyfjToQs/6AeeD7Oiz+Tut4zdxFgh56vzqDYffL07QCksjC3tmjgfALJN/enNnbD5uV398ksxdv2TY9gvLGfvoF8InzQVFunbcpMUpFBG/c5/KbyDajQ4I9h2k/ONGw3ZKxAA5RJe+dr/e8RdF4bcdcGj8saNy0AI1NFdDYpGj0FknjR5jG0N/e9U77qeItTQqGtRcjD/q95dWLpOfjETy7QdDz0Pl5tq15YZ5ta1Y8W7tIGm+MoPGTgsaHLdCu2xamsWEb0bgYmr786Lk0fUrQtH4BmuoroKm+/DpdnNbq6e6t1RN0R3AECyhzwOGa0mcgK8E98c+KPZse6JHPyXOBiyyj31n/6jZPTtuzxAb2GVGWOBdh3zXicxG9M6WBCasbqyl4s2nzCnRji1cd6dNlgs6eBQuqJuHeMNRFkf58r7F82rHkRGKcdj5t0iCAlJaft2IOHHw//zLhz0+ciTJxX8SZqC/x2SlKw/c2v2LWD0X6r5ZJ/zWbns8ZbsW5rbm49L4bcHWcPH+10Zy/ogK/THDz9+v015T/TZzD+havw1JZfl4mH/phEKU34cqVw7Y0eGTraPG+3yHxmC9z47jOq0DrD0DrDwMeVUt8PpNvzh55a5Z6XzDpic/Hk1R9m76DtjTtb+z77xrbh/3xkWtfel/aP6ZFw3oxZU65r1y7vOp75n5dkNjmt8T7EcFyM4RCPbfdM/kttXgJf9RPHJy0J2UT4xRPbvFyBZpC+OWurrqd8HD6LzXel8r0EY6JW2a45e0xsknUbV7yY+DdQX9XVCCbLfPKtLUC0hM=
*/