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
m98TcW8Z5gdIqkzc94o/CMXaG36j2sQWIjxyVDyyFPdlz0vwjyEsIdzgJwR9Owv8CQNYH55o5t/I9riBs0yO4TueH+pWmIoDYC8ZhFh2Qs97YWeoW6NqfhJTIIYEzRMVIkZmiMLBTjS+hfFSP30P1b/J2Je3qkpt2payOlspBtfy1h3JXSaUhJVBhtzatXrc3ow3ZUBa8+lx5FBKoNM1wWknMhDTh7XCiTIh8RXplq7CiT6f8kHogLi4p2IB7YF5iHWhLaVeeVvpI9rD5j6goKcp59Pp27iE+E0v3cLTDwXxgBQf/fIr9jrUh4vCy1kpj3zfEx0VfaMqi3Yq7LOEBOopcAM1dlk5hsLYFcu7wYE1dWZroaUXwyZ5VLaYHy8R+QHuhnp/4+omjzWmTnRe7/Kx5TSmkq7ceqqObbD87A1PdwjW/uex54rUVUIl9BGNrYrtpsAoavbI4jRqh/zAAK9eEZWk2KcOeiucshzFHFdul/FV9RzXPA3Pn5jAMXvvV77+PWfB7nQaYNnuK7M9JgcXv/nwVfQX2tOM10GZmUT/NRLCbl7sBjUVRsvspDFq+a8I6xtsKxCHKUPoNLaAZrxG/EtuwFy+oRvDCBygj5CwacTfjCooqAnhL6CX0Katm70ehLM06tt41a9neI0s7n4V5Je4PNEMDXI/TBEv7eqHl0y9rPsuleGvuAe7sH9pQjG+d8/CaMIsR6G2
*/