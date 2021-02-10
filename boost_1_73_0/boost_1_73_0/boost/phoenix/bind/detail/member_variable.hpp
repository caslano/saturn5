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
5Qc3DfzuUqEWhkBSHPmnVxQs2FLgOSf7mW6iPVvXclgRlko/4p9ioCA0HJ1s6v2B+7v9hBoYMkHwtZZKYnVatBfnpuovp/irv6x0r/Cyw3ZpZWvDCTV4yAEnpyBsO5hahlyDCgv5Ex3dICTpV5bFhYbk04u9iXcOBEaJWhNeAFDWi6/zGLZnaraqNUMEKJSVO7w17lkXXUtLvhxEBl05WzT5PmW5QrCG2cQewpp2iUDlDI8cv9OU9jHFAtAhxnA+rDKXRcSQB6bwngzYYdTgvaeVPaD/i0/hO8kIFAmgz4YstWStCVFdygijJsOA/nO1iipS8S060CgjgLM7+Mdj1T3Rco4oCwUk1yrtSLDoklHEmWxYbF7p+wPnNy0SmD7KL1kKk9FOyuHPV7/Dhh7HeEoeoHsYgiJ3d2xDYCNCwspolcWG2LeLKUkch7DKRsR5xdfFk22xNoPOMPFUKkmp74+8a4mN/GsHIuj9AmjgA07XoK1xA5wvQe1vdBLDh3VpXYPkamYWElxj0OOfPXyQVg72D/dM7AS068XnSeYFJogmuU9PDbyALsFCqsi5rZgKeFdIpz/17UTBWFse3MpgkiCjwQAkkFEli0pK3Z6XlTBWww/76jINrpeRBLD3AqR91AMsMVQOlJySWMle
*/