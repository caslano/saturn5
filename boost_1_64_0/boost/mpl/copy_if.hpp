
#ifndef BOOST_MPL_COPY_IF_HPP_INCLUDED
#define BOOST_MPL_COPY_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Operation
    , typename Predicate
    >
struct copy_if_op
{
    template< typename Sequence, typename T > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : eval_if<
              typename apply1<Predicate,T>::type
            , apply2<Operation,Sequence,T>
            , identity<Sequence>
            >
    {
#else
    {
        typedef typename eval_if<
              typename apply1<Predicate,T>::type
            , apply2<Operation,Sequence,T>
            , identity<Sequence>
            >::type type;
#endif
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct copy_if_impl
    : fold<
          Sequence
        , typename Inserter::state
        , protect< aux::copy_if_op<
              typename Inserter::operation
            , Predicate
            > >
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_copy_if_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , protect< aux::copy_if_op<
              typename Inserter::operation
            , Predicate
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, copy_if)

}}

#endif // BOOST_MPL_COPY_IF_HPP_INCLUDED

/* copy_if.hpp
9GkHu08MfYK/TUCfs7dF0+cNbyx9Vin6rDoM9FkF+lzp1fRZ1Qh9FBeRaH3guMUsIUo3E5SZ75qVRxL5YOXGcqDbv0RbAWwGAPiNxfNohi4hslK2huwXyuFbjPx1LV2x2Y7ThVHwjy0NWhPZ/tpULh3vn1X5kkHL9tWJ4TRp/qd1fvuureJYl9Cee4vk2/GOGHaTnH/9Qo3HzRiPHHhsVDjfvnsTMIm2qGVgVLV0tI/icD6G1LzX5ctF4RkYVPOdMVqox3HdL43OsvAc7Zu69BszalfRR5T9/kYzakP0EcWfRnGMWhbtEMYyatUCP1M1YfXm7zhs3fQBsJB9p64qdXOj45f2m0fE7D/nx7yPwbvb/6n2APR7xKJbPgyL8Xt4MT6z6oCJ8yDBJubxQRnttVDcR6wC69m4GB7NQIoFSK4AiVyrISzaayCMUOuKcVykRIocsKXIqZiLMq5kM2kEQh+bGHpnoLylPIsExGP2gcPrBGHk318dep0v9FrBlQ61E9Br/F8S0+u63zG9pmt6CZDaj2PpVYicDCFf0esSTS8psuXjhumVH0OvWSiPzWsBseDjw08vTaV5QqWt+vyDVFX1sKFS7p+jqNRfqDR5D74DV00ogfPrjwTl6RpIT84slyJ1RbADTSspdbdTqs+yySreek4IIbCTBQoZo5x4cr4zOdz7/SMa8T/IbyR9TJJ0fHHzj4pofxNloeBPUfYxTx9vNKxk/i2aytdWO1Qe6iHGWXMhFnvqGNHHvP+incKHtoSS72y7iiV6EVs9G43Xw/r9SOI3ckQ3iN3qNHIOUKfMrNBFekX5eAvHOaDR88af0nyMjlWt27U64mpXsQQkD3shztpykDq5RZddcfg4WHCjLpeF+9KzSj/x4uqbGhJbJ8MtM2MZhbCrKJ9cIU791zOdZEZeR0eTd9EoVQE6P3NrYeruQQUBB4S9ckdkhjJp2u+20Idj/DgcQ5uTWeHLAAYCa/jbAERn45HNOQN1UHB4gVukA78g8lTPFnGflvAn7CTNNweVEWrmHCzl3mXuRDk6hku4GZdbG3my9YTymBEZTRjgWo32WGrhWorpaGmanPhNw2kcNJJaSGEa6XLlqnW0oNb2Q2EIY35z4N8i9L8TX/F+Mq5E20/16MLeMTsUq1jF9qukDMoUGFyFVmi71AafGVwqUCuG+77yCfsK9bw60x81XvhyGqHpMULRwj26JxApDRcU11U9b46Vuz+vwedaBGfEdTEIMvJLrgdzrRYxRmrVQFfXManoMPMmea5vDa6iYr60xxGOfbzlErs1XJTPWA0fW1d0AjI+9YZg1w0DlkcDxlkaGWBqMBooBZ4paZFUHArBUqQ1xm/APQpO2gVg9tYdB+qbuEA/zD/DD2d+rPsSmrrqGdYej4Zvs2eG4lGYcVVecClpw7xfCxtMLj8V6U+We11eVcMETjRCPbl8JZOPUyGiBKYghtUQ6FmBJt3voqWdn7kDHwvFdREo3ZA+dD/tFGOoi/uJMjIF2LrS1wpNo2ilV9If+zJKizG+tKU6lercvgkWWRP/FvUFBF/7rii481UYYCfte5xmfHsi25GURkFsirN0pPO3+fQA7PZpzYkf6PibtDkgy6bk/i1n/EE6I3F6//h0iLbsPx5o9DzS3Bel/sTpoz5rOH2or2F/mklbGy7/9McNpz+zKXE64gNuSn4+ayCp2on8f374ZsP13f1nSU8U/5uQRc0nP+922ijK4thicny9fvJB9qDIDk+x/MNJql1sbWGpNnEfpFrzDrXr9lqVyrZXu10QjPfXmcD4lc7tqY+vcxSv+uJ0LNGraW4B66DCtQZxwPTk7YnbWsg9xhz7kzBN2JA=
*/