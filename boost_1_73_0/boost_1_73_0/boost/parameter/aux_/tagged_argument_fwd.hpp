// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP
#define BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    class tagged_argument;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    struct tagged_argument_rref;
}}} // namespace boost::parameter::aux

#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg>
    struct tagged_argument_list_of_1;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* tagged_argument_fwd.hpp
5DPh49EKxzsADw4/367l8zxWMZ55fpqvDyjvG8xa+pKHSzLU5wjuEb6n2KedWUffpx2rZ+9pl6rAZyrnRinPrdxIymxCbzfMpivbL3C3V+xjnhsmmrdcnmjqked0hzwlr5fzvlzvNrivJnuHE3GdhXGVC24W7VZsaKELbp7VwU7kqbRlFj7E/R2aeeyquQNc6iKf+4U8d6AVMZ2NzC/ORn1t7JKuMp7U1kfIE3/wkEWf1rzHRROPPuKOvqUsF4k=
*/