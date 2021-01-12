/*=============================================================================
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_IS_NATIVE_FUSION_SEQUENCE
#define BOOST_FUSION_IS_NATIVE_FUSION_SEQUENCE

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_complete.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Sequence>
    struct is_native_fusion_sequence
      : mpl::and_<
          is_complete<Sequence>
        , is_convertible<Sequence, detail::from_sequence_convertible_type>
      >
    {};
}}}

#endif

/* is_native_fusion_sequence.hpp
aUqlKdOTU16koSvj7exs71QqZC+PdYjd7pMdGU92+zd+9IVUFsuu3bdh/x6bLIEZZ5SoYxUmxhlyFblyWft0wWrLXtWBXDkfPV27thxracSB7nYWGj2Z7AbzsyRPIDePs6lpc5ZEu17a3uus+5aRTeW1tDV5ezLclBIzyt59Flk1Vxb/xRpaqUUnwyLNWmnKJjb58MbuVOfJrAuxHklzX+9grl49VqxVaOYwxKv1Hbwl+Zif
*/