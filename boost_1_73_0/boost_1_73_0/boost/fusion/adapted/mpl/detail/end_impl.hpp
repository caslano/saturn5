/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_31122005_1237)
#define BOOST_FUSION_END_IMPL_31122005_1237

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/mpl/end.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion
{
    struct mpl_sequence_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<mpl_sequence_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename mpl::end<
                    typename remove_const<Sequence>::type
                >::type iterator;
                typedef mpl_iterator<iterator> type;
                
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence)
                {
                    return type();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
s9BY25ln43HZ6xYrGVeqNOPyGoqosdvPqlpjNlu2A9VZsAp6w0Og/SFsVSVqekeIcLHrN60wTXiTFgaU1VhpMLxtB3doKrjxJXDIBrRC2gkdZi8svRklDUW7bNT2k40I6+Co7rXEcAgL7qsUAh9CLyuu3X4HxHWUAWUH+TdadpN7BUpiVjCKM5hlI9gwI0wIJ7P8dbrK4SReLuMkX0N6DHGyHvy9mSVHyA2BUTXwq05zg1loENuuFbz6JPhPnfQgyl/DZLWcp4u8WCWz90WWTt5M82IR4xcPYXT4FFIc6AeH9x+NYNSKDREAHkePDqNDXKCngjOzKwy31Gr8Q1YZdJy9hiR+Ow2+6v30HjbYwkqKK2zEliHBjSrPuXW22TpJF9ksC34Rsmz7isNzCuYJ2LwInN9S4frnOezRN3DQIDVaZMjX4iMdG6bhoGO22f/NxTyaZpPlbJHP0iSYSqK+cURA8hIn7mZqaLZKJSWKHpYNXFadEtI6Whr6nswpQoBsO61n9PG0XkQwq289EoOS1Xwe0nb55TjIMyQZ5VRFEMuAbzu7A2KdPINL0bY476ZvLekE0o9rjfzBwTVqixlQUiHgkLidUtlrZ0NtwRdiRkFwQulwh0QVOqC9g6FkGiEq8K4xZmEsZxW55sYy
*/