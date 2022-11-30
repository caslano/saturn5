/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_DETAIL_MEMBER_VARIABLE_HPP
#define BOOST_PHOENIX_CORE_DETAIL_MEMBER_VARIABLE_HPP

#include <boost/proto/detail/decltype.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4180) // qualifier applied to function type has no meaning; ignored
#endif

namespace boost { namespace phoenix { namespace detail {

        template <typename RT, typename MP>
        struct member_variable
        {
            template <typename Sig>
            struct result;

            template <typename This, typename Class>
            struct result<This(Class)>
                : result<This(Class const &)>
            {};

            template <typename This, typename Class>
            struct result<This(Class &)>
            {
                typedef typename boost::mpl::if_c<
                    boost::is_const<
                        typename boost::remove_pointer<
                            typename boost::remove_reference<Class>::type
                        >::type
                    >::value
                  , const RT&
                  , RT&
                >::type
                type;
            };

            member_variable(MP mp_)
                : mp(mp_) {}

            template <typename Class>
            RT& operator()(Class& obj) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<MP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*mp);
            }

            template <typename Class>
            RT& operator()(Class* obj) const
            {
                return obj->*mp;
            }

            template <typename Class>
            RT const& operator()(Class const& obj) const
            {
                BOOST_PROTO_USE_GET_POINTER();

                typedef typename proto::detail::class_member_traits<MP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*mp);
            }

            template <typename Class>
            RT const& operator()(Class const* obj) const
            {
                return obj->*mp;
            }

            MP mp;
        };
}}}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* member_variable.hpp
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
*/