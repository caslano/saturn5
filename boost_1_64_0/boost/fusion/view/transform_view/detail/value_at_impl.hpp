/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_20061101_0745)
#define BOOST_FUSION_VALUE_AT_IMPL_20061101_0745

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/utility/result_of.hpp>

namespace boost { namespace fusion {
    struct transform_view_tag;
    struct transform_view2_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<transform_view_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::value_at<typename Seq::sequence_type, N>::type value_type;
                typedef typename boost::result_of<F(value_type)>::type type;
            };
        };

        template<>
        struct value_at_impl<transform_view2_tag>
        {
            template<typename Seq, typename N>
            struct apply
            {
                typedef typename Seq::transform_type F;
                typedef typename result_of::value_at<typename Seq::sequence1_type, N>::type value1_type;
                typedef typename result_of::value_at<typename Seq::sequence2_type, N>::type value2_type;
                typedef typename boost::result_of<F(value1_type, value2_type)>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
6df2/86ZwaxlLg+u8T4zYXbCMpd5NyLLUfaS+3ruaM4TJnv71+usLM7zT+M+XLh+vS2ZD0yOu7ciJJIsUBk35/iWrmShMEdZw/1VDzhPmOzRk+jbi8gSYC7C3v1234ksVVmv854NnGeGss+PI3Lbk2Urc0ZfeHOOTFtifM4aHq+3iUwPk2e3zp+beS8BMA9hD8tM6EAWpoyr370b7yUOJmvw/LV2DJ8XZVybLc4JZGkwa2HHqlw6xLXDZH0zfCdPI8tR6lv3ZE1xMi3ROLODs928uHaYXK9P8NKRZD4wvbCWPbfUJguClRRm323qbLJwmOz7puDfffg6UvaS+KpzIt3rkmB0r9uv9dD8dp44QJYJsxbWO2jveLJsmJWwe99KziPLhfXMt+B863tlXz+ysKW4bsW42xdmBNI92QCjvRzAPfntFZv9vE+YuQbTAgMPYlxK7FZzslQYve+HacklKpXjHsHotdsh1F7cyaYhX7cwa2ENLFYWIzNfhvWEeYT4LOb+wXTCnrwwBJH5w+Sc1U7bZ5AFwqyERdyuqSMLVtY7XLFfN7IeMHq/CdP+3NC2LfcdZifGHT97+ABZHKy0rP2I/RyyZJi9sEmfpsWSpSs19Bw55RtZJkzm+d6j5CSybJijML86niU5a2W9rqO3byTTLTe251MuDCXzUWzx8J4jOE/FOve40pwsVDGLeVvq0XkxwOicHcZ5cXBxPU+WBKPX10dgToFrF9CcWWJcOua0zuy1jmtYYaIF/Pw5sKOwoCoRXEP8Sj6f+VY6svmrAquupcPcfp7rY1qEFu13eQpZNozep8K0Z9M2+JKZrzLRqgpbn1B9HVkgzErYb0mu28mCYd3zLTjfTG8/fch7gQ0SdqOFgx/PuZpfm+ZbxOpnP69pfy0YppkX1J6hjdLCry5ZRj9T/yK58POe01qU1v5+zXZkubCiwjoOHNmFLC+Zr4d8a55ea1SBjdV0f5nw7z04o1XTKpVO5/OpbYJZFNgVbaQ2vnYnM/p9ELt2F36mc13ro9ln12hHlgaj12AwbUGD9p/IsmAWwmabTxpElgPTC/MYtvcYmW6PiZZWcCbyrfnDY2PJvAAVxbh2naK2kIXC7IR9T1npR2aA2Qo78ajtCLI4xarFpvJeEhQr2fPAUbIkmI2wPnMHNiJLhVkLi3pV+k+ydFhxkef2BV1XkGXArMS46QNLPeE8YTph+371e0yWC7MXdmvfu1/Jiuzj+2C+PW7wfD9nDZM9+uvQt4WcNaycsNdWN+nfHdCCYZppQY+ytN6aZ70n3cnSDvD5zLdmdYt/I0uH0fmEaROeN3pKlgmzFeY0pkVZsmyYqZhzb1DZ2mQPFas8xWE1WY6yXusTQ0zI8pT1ij3/twOZ+UHjOT+MbVSVzFqxsG8HK5LpYMWFnVutDSHTw3zlekXpOW6kFgyj83IL2XebHmlJFgZzENb8/T9ryGJgzsLmb+70B1kizE7Y2cMv15GlwhzlnPdn1yXLgJUQtnXw5alkOco+0/8NSSHLU8yx/LwFZOaHjGv43HBZOJkXzFbYwdO9/kvmD9PJ9eK7DiMLgsn6uqfUrsmZKebXeXoeZ6asdynmaweyeMXWT2m9ivOEyfpmN5uYSpYMsxF2d8zChWRpyl6aTxu/kixTsYgxySactbKXJhldR3LWSi7D3e26kukO45oWZpd7rT5nDZN9/3Vbn89kATAnYYN9Gh4hC4bJ+vZ8NrvGWcNkb5ckdA3lrBWzWp6dS5YAs5f7DN+u5zxhrsKSOtss5fMJk5kNSbwTQpatrFdswWk9X+8weh1yG5fls/sHxtLvm/E5Umh3tAHaee+UDwVm0EJhNOd/YYcmr+o=
*/