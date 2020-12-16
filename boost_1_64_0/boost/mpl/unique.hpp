
#ifndef BOOST_MPL_UNIQUE_HPP_INCLUDED
#define BOOST_MPL_UNIQUE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
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
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_spec.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate, typename Operation >
struct unique_op
{
    template< typename Pair, typename T > struct apply
    {
        typedef typename Pair::first seq_;
        typedef typename Pair::second prior_;
        typedef typename eval_if<
              and_< is_not_na<prior_>, apply2<Predicate,prior_,T> >
            , identity<seq_>
            , apply2<Operation,seq_,T>
            >::type new_seq_;

        typedef pair<new_seq_,T> type;
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct unique_impl
    : first< typename fold<
          Sequence
        , pair< typename Inserter::state,na >
        , protect< aux::unique_op<Predicate,typename Inserter::operation> >
        >::type >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_unique_impl
    : first< typename reverse_fold<
          Sequence
        , pair< typename Inserter::state,na >
        , protect< aux::unique_op<Predicate,typename Inserter::operation> >
        >::type >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, unique)

}}

#endif // BOOST_MPL_UNIQUE_HPP_INCLUDED

/* unique.hpp
Gk/vr5fyWP5C+ho+OFCt4M37/yPuG9yv4HVhy0Z4PCw/FHaGxFZw+ZkYPDT8XNZMC+4b4z9DkgJ/LyX6Vx45UffD56rLjUiWFSfZ4GmcLNt6X0hbiL/8RMQeXsea9x9O5/sFYJtp2KVTBv+xHrtd4cvl3vlC/2M06gMPPK2IUgtbN0MoEXxausmPg6e9zjIOWW5EFmagdZZGUe0kOpTBbigVVuvcbExbmoBXwsU7SqTeMkHTRRc9FkXnWaHpKIvGNk3aRJw91JT8TrKbEZifJX1Vyb0J1IiofajUJR0yl+Mudy7NChR6CUViZlV2ROKikfrcNR2DMvkMfJDTdX5ndCcdtqUxoPZWqhkcsR/sH8H+5WmR440ud7uN105XgNO0JgpQqiLKJslzlPXVJetJOdQp0+2Fr0WwH/xnE/8xkvBnN7/tUddh/BkocBKdSPvbEQsJStjLU9pe7ezr6T9jfS9MXIqXI0YX9KCpsVNpauxkmeNOOvvB0LSH18gMsrPh78gfiGSR/6NgrdM/Bljl4k0Cfetvo0ZTgpIG3EJoCGcpwQ88MQvdaGqGnRtlRz3sbmWsMkxaPlG2vjYYqLX5j/HMbG+ipZfQckWhifFAS6LLLxLhFaClL9rHfiBg0qr76RKV0m9+DVUdFFWx7W0UPswYQLWZVQWiqjq20JwBqqrJbQXs+9Uysx/LzH70CGHrp6fJlWZ/4HyKLFXfr0SrhEJOLV3P5xfC/5Oqy2vLjBs4k2dRVPUPF8RW/04bqncJ9/fCeTmkADG6sgPvu7ePxavq8BxAtosGiJr8bbKA+gBGloZ1nyN90XmERWqvnA8I5D0OuDdvCNYm+8idyW40jvgke5lKfD8Sp+KOzK6C8kMBQp4d6A8SZNaDcobIJoRx+mjpLHoHcYFVRXuCgT22QE9CX4eSbk87xeIn+ywCXiRJv3m6Q0KZnL7oa57OBUX7KzPJ7LutkvxM77UJ/F4n8fs9jd9DlxJ+7+wB/KZ4oBch4kf/FIjYjlqGbcMhWVx3RQPPKkbj3cbsU/j08R2lfTUJ6D4Bg0jxrxYr0nRCNU/rsVkF4yZV9KO37WOzGulHSbHT7c9FIQKnZShpkCppgS4pS5WULUpKQ4ZsURKaeSVMxNejWyW0fztVIc9YnK4+x+ebni+jkGfWCCBPRHd3tHT3frJcBtZieVtFbsJXSnW74kn+6VQzjO8bvg5KmSBTWPQwJnKFkvCEC1DISfyRuhZcjrpBWDqJYAQfU4+VVaHQGDTCKYbbN1dTrfntsCXAqHZzqlGdKUb1m24YVYrXo/ojjapW++l9tOUaF7Z1W22VGfS/gzaB2sd6/SHZryl1f6MgcMzunyyxPYOwXTBm9H9gtzBLvJnSYHfZkbHR3w7MxCRHIKXutwQHqBxup6MFaPnu7UV7bQpEe/qiuZRO0flXi9DTunsKSicJRF4tmzxGN3mtaHKSajKMSnHPaizofYqag2gPeSPfRR1Y0Y07upY75b2hcgJuFGR9I4O1saoEpuT9PdGoH0Hla2gFEL2ww0EcQ90rZLZIDDWI0wMTUBONo678oiJNvzxnOSPR7tuTrWinSZdGuyu47KqSeuDN4Dx9l5Jm22a7OOOYOAmIfShZ4SXqnUSTl5v1VaeIsRY7NYz1hoixTqaK6hq/b2xEK3pPQGEa/ybIsvnC5675ZJ7OSPLnYJZ2V+tdsi8dTGJZZ5naQKpe5izprBHw7n4RQD0WDDwGc4yPOXzOMN/JIfV6kPBOFpR4ejyKVteFd1Vme7swoSqTwqo/AlTSEldE5DTFKRVMUETkZERk6HXa1w5rXbatIts7VmKOV9rtkcWFUNxeMv+lQMljUMjVqr8=
*/