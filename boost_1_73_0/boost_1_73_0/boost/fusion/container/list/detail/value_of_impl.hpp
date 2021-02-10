/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07172005_0838)
#define FUSION_VALUE_OF_IMPL_07172005_0838

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type type;
            };
        };
    }

}}

#endif



/* value_of_impl.hpp
wCEK2cEB/d5pBvL5MacUeItHrVBJs1d4+atRPIYyQSb54hr32C0NUm6j2LRD8Kzhngqz8h6CQbj8Uge1kmMpHARti7W1UUBfEqgO0w3/lScGhndjBjjG5uq4VRM1KBTVgFhaWO5qpTxh741Hr3yKl6H1Lis/oMo9d25iWw+4AdlPgpzGecNyCd8Us9WIXXkX6ilUIlLJOD4HMTB56r80GysPf/bqjFdZ7zWd0t5xtnAhLHaBbzrSUIVEK6TW9X4KE5I0WsuD2zaOXWVJSncH8Q2Lh4LGreT1pUWoInQRKyKS2htmNxCUPOGAyYpuay1KWsJgDsS+jLlK2OWCkLEbHqpshfidZ3hurStICkEy0O84zUJYLXjoMDbSKQTNh4eISh7yypy5tUmlmDC/59Iw8NvJb1D4uOm7J8ny5LoCRaU7QFBuS/dPNmjsr/Jun9Lemqub9uwtlV997+IFNRScmwMLiE3gO0HltC2/pE7JLeS58pQ6g1+LBp2vorsQyQ0iSYolFSrZYW4rbzXNXY/m31u64WJPJ3mwvdoXCTTe8FCyvXJv6Ah8HWFSk0a2VvsM7YtGlVLFeoerC0DoHjdxggQmHcBVf9zDEoAzHVz2z/BlJRjp0h2tQzxuizzYzhixBQSnbt8gfJgjOpKb
*/