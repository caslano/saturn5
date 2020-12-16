/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_05052005_1126)
#define FUSION_VALUE_OF_05052005_1126

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct value_of_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template value_of<Iterator> {};
        };

        template <>
        struct value_of_impl<boost_array_iterator_tag>;

        template <>
        struct value_of_impl<mpl_iterator_tag>;

        template <>
        struct value_of_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct value_of
            : extension::value_of_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }
}}

#endif

/* value_of.hpp
bnT922i8OsY8q3uHttRnCtrLfCbWYwzUJ2I/VZ/2z1bVn+N23iAG0/renetD+Wb5qe0I9RHz5n77bjHPtH35WcYEdV+8zLjzbteFm41XxbjrTbF6pbj819aQfqBRGfXve8Tzl8zxOrSVds7e5hq5Tzz6nm3hdnX24HbHcc6KKXNcHdztmvBe+brYufr7YvsJdbpb/9fn00/Vf7RjTgx3XqC8f1aXlY0hJ7ayrofq7nmkX5+Ut4S+Le5fJTY+bjxb7+/+hLwab3PiMhE33xdf5rhhxLVVaPLbKOk+w/MDK2wvhk72PzPVSeoj0jkx4hybNH4qt2vIjNfCbmOic1f2Rn/7LK78UX3oUnFzobIE/cz5trzPPOxrxpznuJ64xHysx1hyqxj9tvcmPLomi4nfjjPEte/LxrRzx7ucp4b0fd+/TmzR3vv0x2vj1lZW/9PGR/26vSnm/3WJ7fuU/3T3U64X/8fs1g/M2ZLi80rte4Pz6RHiSoy3q7v61WLu7ebS2r7dvY/6j+LuN5on+X561vZF42oit9K1n7E9timk3+zcUzc/MQ/ovEY5LmkK9d/pV/KRqOjfs2v8v/aIfuseYBDvL5GHe/Qz5S8+olyD5hKzxtEjHE/s1/XJTjGf6FKGL2sX9dPu2OWzzCty4vdc84TUVuOWedOIc9Vp9t8rrecb90uu7R4QGxH3dU6UZ2nU77ame8Fc5jwx+TnzVPmpnu6cuUssjJhb27ZcdZwxcalMafOwsvcKH9ZWfzNGasPC8n2BVeZzYqxdWRK3xN07UKcPbTVnjKpjMdlhnBD3HV7LadcO9+7q73auuFC7Ha9P6muJ74jXvWLv9KeEwvuS7mWK6/vE9Z/0pSnxkNUvfUZafZ042ppQt157cKVYEnPKm7N92fhc1w7Bfbeieztl41F5046QKUSdk57sd7f6kLlK7C2OOamPn7PaMdTbncYQ66TnjD2pmlh4Qr/5q/zdp48YM4v3mLekG+Q77nrLeCbO283bq3n5LjveX7Vhs3OZvpi5QNt9wfn5Nc7Tvc5fa93D/657UuvE89W2/Y4x4k4xMGqea5xJu39SFlPtzs9Bm6RPVQ+zzvnXaoc3iCfptxsjiz32yZnPLc9bXyGeXxpzjjanXSW93k1iyPxffZRd24Tl+x3mroVvGj+MHXXnvdyD4tUYWvilPrZCXFwW9bsP8f2Ae5fWHO+oOIcY3wrbxP8rXU+9eVfodF843KmMf1ZvV5vfXaf8h4wN14rJrxozC869Q43S08+fEHf+bm8Vo5eo+2e7x6N9271WzWuPf8bN99WL9igevUV7i79/ibP9xjbnq4579bnnbQux72rzSe36LePl19Tfp7R1Tdt/V1+5VVwdZcx9mTKdIhY/73zn/nnidnXkfBa7ZTnW1NtNYtI9+Q7Ps+M7XZe7b+YeQe5y5/wZ7Z7y3GuZI91n0MYd0smOO/+O+b9HVeO+65HCjc7tU/L8pKaQcJy6MieuMBaY16fcJ02cJs9F78tTzvy+Q1mz315uC+NUyfjjHl35DvtcIP/me+HsLdYujyqjvvxDdZS1vXJ1/H6N70npU8aR9pfuVDeu+duUcUPCHG2tdbKV8xztYRytdosHY0cht964m7AO+E7t4FjbtM1Pjd1Nrjv6l+9XuDZsk7c/GYe1X/hkk8+fbXNGzBryYvVc56OCONgRc4/MuXLcOepN5icXiLF/uRfg+jrh/JX5nnra49xddR/SXCE9Z9weNp+5mn0r3OfVLkv60rTz0Ye1wWvE5Oqj3Dt3L0Zb1j9ofL/DNdS31Z+yFarS0FdT6405k9rqJuX+sevcSXXmHkVOXtPm14UZ7a/uyin5f5JzzKM=
*/