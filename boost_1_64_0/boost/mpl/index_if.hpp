
#ifndef BOOST_MPL_INDEX_IF_HPP_INCLUDED
#define BOOST_MPL_INDEX_IF_HPP_INCLUDED

// Copyright Eric Friedman 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/find_if_pred.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iter_fold_if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct index_if
{
    typedef typename iter_fold_if<
          Sequence
        , int_<0>
        , next<>
        , aux::find_if_pred<Predicate>
        >::type result_;

    typedef typename end<Sequence>::type not_found_;
    typedef typename first<result_>::type result_index_;
    typedef typename second<result_>::type result_iterator_;

    typedef typename if_<
          is_same< result_iterator_,not_found_ >
        , void_
        , result_index_
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2, index_if)

}}

#endif // BOOST_MPL_INDEX_IF_HPP_INCLUDED

/* index_if.hpp
6M9zuojsK2xZJCreFdZHrCngaJ+hOWUE7TIQiFgETVe4exl30zcSyO+QoznmBO1yQF+v2PErMnpXmG+PhRMaxxzNMSdol4NB8Q8GFYvrC5d/me6z/pMicFA/fJ6eXSEun/YdzOPpjLDG7rGhy4kqjSQuf/VUF9YI78G2R1cjjKV//szTtP7c9gv4biMeb2eV1Jhk7pcPXA75hTVaM0y2Kt1qOSVRX+vfHg0b0l2bVyi2YkonQVs1EhSjeXuKPR+ZDWBFS6g1b1Y0DMFeuOxBFYEziD2PNnmej+B7SAikJl97+SMQjhB/KY457+H53HgAxKHOkOSDGqFIdKYOpRF2Ck7HujEHtfG8A9dAOCkWiMosNJcJQLFTxL1bqpRSPXz2uhQZYhc6yxPSsNuZJTT6V1Phhn25cmWa/ykhflICkTuFmpS3+O25tmjg9v54zKeg2K/DSG0WVCPyHar+Wjfa/8+yPvPDlVj/LwU/oDviTC9iuKr9oFcs45ALOvUDL/U07Hmpu6tokF8dDuEugjdaZbgRp8wuXXNID2akiwhZlIsjpbm6dBtux+zSNYf0YO90bm4H7T3J8fBYeCb2kJdn1hUlKzwYr6p/8Xjxi+KPGItWeEaOj4WTa094B1yZ6xXDaDs5Q9//nsRC/4ix2AIn24mxYZ3+esKtHjhirPDRNp0seBQW8Y8Yi7Yabj85lsaFp+0WD7w0VowkMUMK7XclFomPGIut6XzRlsYXl747SHzRnM4XW9P44tXUIPHFpnS+aE7jiwtSg8QX7el8sSmNL57ZP0h8UZ/OF+1pfBHeP0h80ZLOF/VpfNH4ziDxxeZ0vmhJ44uz3xkkvtidzheb0/jisbcHiS/q0vlidxpfnP72IPFFUzpf1KXxxUPJQeKLjel80ZTGF59ImnyhU0SQsaE4/fWwlTD54+Rxo4sP3SNKCc/+YxEHYmyItLBEZQLr2+mBFqb21qx7blj6dZPQzf80CE2QqTL4wtcggPi2ezjsSFvtKi+qlesVOYREqX6XrMa5OhGPyDW2POF7UgDxcQfIV1/tshFcjTCv4Fv5Mv0iVY3VYWPhzHFsKElIAggjSVy3WyLJPFkAnjxBVUtwr6gySEVIAgghydvHHQaS3DfWHiT+ofrGvUIMBe7TkwIIIckO/bYaSFLfCA/SIKhqOnpFhNG5Ty0CCCHJxK03kKS+YZiWqmpx7hVVBlcRkgBCSDJx6wwkuW/sZPUcVS2BXsVBeJ2QBBBCkonbaiBJfcOOPWD0Db1K1IAvCEkAISSZuM0GktQ3cPTLb6m+ca+oMiYgIQkghCQTt8VAkvpGeJTqP1PV4oKdQPgkIQkghCQTt8lAkvoGnrz6rX7w5JYMnpz0Vj94clMGT7rf6gdPbs7gyScT/eDJjRk8eWfCwpPFPCV1sGEH4bUu9sJVJht+R5VMilkOQaOL6YGSxHl54LzPJyycV8wRPxJgtjZqHSUNmTDKRJqahlgAf+2WrTN/FYK/Yl0GnmgawhYsJVo3WaoBJYEnmqZ4I+CiFqN1whNcdLcqqQuJVBxKgHGajdYJTzDOd1ESeKJpLDjgFdU64Qle+YKJJ5qmuENgjx2ydZM9jjTxpKZBfHBEvdE64QmO6HrTwhHFID6YYKvROuEJJvgTSgJPahrEx7jXGa0Tnhj3e9+0H/ctGeN+zZv24745Y9y/9Kb9uG/KGPfRb9qP+8aMcf/nGwpPnFU9fEGyARcTG9hD0wbj8IrVfy00GGvhsWmtcZylQY2ylSaVXxMtY4tN44CLYEOrAW91dBopCFYT2Tu9b310VtdDn6HP0Oc/8WH91xzov2ZY3w9AJ0rmElr2I2M1tkfX7zkWloHSipc=
*/