///////////////////////////////////////////////////////////////////////////////
/// \file utility.hpp
/// Proto callables for things found in the std \<utility\> header
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_STD_UTILITY_HPP_EAN_11_27_2010
#define BOOST_PROTO_FUNCTIONAL_STD_UTILITY_HPP_EAN_11_27_2010

#include <utility>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{
    /// \brief A PolymorphicFunctionObject type that invokes the
    /// \c std::make_pair() algorithm on its arguments.
    ///
    /// A PolymorphicFunctionObject type that invokes the
    /// \c std::make_pair() algorithm on its arguments.
    struct make_pair
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename First, typename Second>
        struct result<This(First, Second)>
        {
            typedef
                std::pair<
                    typename remove_const<typename remove_reference<First>::type>::type
                  , typename remove_const<typename remove_reference<Second>::type>::type
                >
            type;
        };

        template<typename First, typename Second>
        std::pair<First, Second> operator()(First const &first, Second const &second) const
        {
            return std::make_pair(first, second);
        }
    };

    /// \brief A PolymorphicFunctionObject type that returns
    /// the first element of a std::pair.
    ///
    /// A PolymorphicFunctionObject type that returns
    /// the first element of a std::pair..
    struct first
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Pair>
        struct result<This(Pair)>
        {
            typedef typename Pair::first_type type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair &)>
        {
            typedef typename Pair::first_type &type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair const &)>
        {
            typedef typename Pair::first_type const &type;
        };

        template<typename Pair>
        typename Pair::first_type &operator()(Pair &pair) const
        {
            return pair.first;
        }

        template<typename Pair>
        typename Pair::first_type const &operator()(Pair const &pair) const
        {
            return pair.first;
        }
    };

    /// \brief A PolymorphicFunctionObject type that returns
    /// the second element of a std::pair.
    ///
    /// A PolymorphicFunctionObject type that returns
    /// the second element of a std::pair..
    struct second
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Pair>
        struct result<This(Pair)>
        {
            typedef typename Pair::second_type type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair &)>
        {
            typedef typename Pair::second_type &type;
        };

        template<typename This, typename Pair>
        struct result<This(Pair const &)>
        {
            typedef typename Pair::second_type const &type;
        };

        template<typename Pair>
        typename Pair::second_type &operator()(Pair &pair) const
        {
            return pair.second;
        }

        template<typename Pair>
        typename Pair::second_type const &operator()(Pair const &pair) const
        {
            return pair.second;
        }
    };

}}}

#endif

/* utility.hpp
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
*/