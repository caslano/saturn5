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
MJJFwFhGtd535R+C2FXn3sJPOsxaWIXmiYKhBHeGiWV3OLI1u4DFNIxlRD1dUqJpebu8sMcOL5ZH7NBf6hRbDkHu1wGIZw7PEiomHz1/qweFBwXerbvSLYkCLRGt8Pd3nW1XgHfjw13Tpqejky2L9HWKxqtOvkQb45l/6fi61Ojzg3uKW72OiFdu6Mxwoq77pVIbJ6EI0ubaPjho1eJnN9C1eKbhhJi6rKFw0LJtzvfM83RTzIX+VgGfabB5i71e/rTSdzoCzrqIJ471cMQlWkmkmaEoX4H/ERJfHxpbhUy0hDiWocdKi8dhzQ0FP6Kdv9e6DBFA9/6bIdL3Fb3PkT1pyKe5cybEn/mlIrPm7A56O7lhZX8SZYHUxEiK+75uRd7JN/A7eJOEpIdGzMNzPyndzToeXXHXELE76MvTACFSyh0rYamhub+0oi5IOrCPFuAi8C4HgByjNXrdvn3xPlQaDCiKLjLkRXyYPFg4PLYM1NnrhmMGqiw+Nz6dywKSpNsAA5Pwl775gJ9AjeYMkKUL8oWOuYd8HRe/MzeLeVnfN9B8Dqvu1kebbd8H5zPB3fNrPtkFpTDcZ5FHrBDCPBR619shpmdCsbj5w5gxDZQKpDysGDrrd2x+DNFYiB2/DZy7sgueAR5GunDOxsHFYILqECCqCFVKM4t/LC97OTvVoMhaw0PjuhIOpkp+FH90P3pkCXaY9tU+hOcV
*/