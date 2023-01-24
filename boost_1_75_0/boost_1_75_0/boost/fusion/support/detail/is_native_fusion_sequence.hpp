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
20bx7d8cKVS0/Ov3LUmjqm7GYKRRU+p+ffSTrqliRKnr8kfQ5Yc59bk3T1nC5C2UUng/LLstuJb4cmJUNciuRdQ5gaXWsk+2Ap581Eozn+R7Un0RbWeZMEx/KpQAkqqISmEz3czZOtTzlUQJ6vI6/LL3zoabsDxCdgB5b8+9+1L8Xu3MVoRB5Y1O9lnx3Y8n+X8vRw20naLUJz09/UYo2Q7CSclvWiSTVdzl/sH3PNYq0tj5a/9Y+rdVu1ljR7nRzOnbktm9iJZMU0jtN5Rl0sD6Kd1d6a7gstt0TxNGEOH+ZY9E3F6KRIplftLN1hXUhteUYM/jmit8FDprxie1s1YdDXytY2VQ13LnIfW1p/mphrviARtqgRWNqNafS7eiQw1q+aUSckXqN9bYZkG/OTeegF2TSvttY+ez3jGuEpxuHlhmmIlwD1pX0DFyW1F8H0J4hjxvn5h9Pvqvd5E3sVkaNLu5eK85g7cGXI3L9wOe9H7ZMN6lZTIi8aWkxDYru0Qkg6ZVf4PbfcZ/Jf853s6kM1sZEbPGTeAGoi4+RJ91KGDKR8R7oJVvV+85fzwBpDhG2SSMmwq1O7cwhUM/6fJYt8otRYiUEf/kyDh4XaYZFYWac/x5jlEvN+GaONnKeUy+5qUbs6ICt4Xq/n7IwBOZ6luTaSN7UiN6huxkWUrWye1k8aH2uZH1m6/tiPFUejJFK70jST6aFaNc
*/