/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133)
#define BOOST_FUSION_EQUAL_TO_IMPL_02012005_2133

namespace boost { namespace fusion 
{
    struct filter_view_iterator_tag;

    namespace extension
    {
        template<typename I1, typename I2>
        struct equal_to;

        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<filter_view_iterator_tag>
        {
            template<typename I1, typename I2>
            struct apply
                : result_of::equal_to<typename I1::first_type, typename I2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
eB0B+wbHdJxHJfZNjplxzgNDXYyxb3HMjHP+2w3smXxPa9i+KzA+G5uqcNwDMPrBF6eBNe4IjPvBla/yfhAUbpClQX6tHUHejZijslSL3MqGe7b699Ky5STqnIvCblSFlUWRdqNlL6NgJXuTcTg7w9qpY+z2+flWOmVgjXPwCxWG1bwptzitMKzc2Z6ogRnnt5C9zUyNYxk/3s96qcRQMnpPc33I/ADdZtbEVaaA/Y5hJGrEu7zPxHb6ZHUAvwlKVuKoZSSMuJ+8n+HM79M3OTagUyFgiwc4Ru/RMv8Cz9T2AjunVo7QrepawWRXA295ak/eQ48udsD7XYP34IUjRyueuhsO3mum9+TJrgPe/Wf24qk74uB9c28e5RTp0h73njx17x5nI/v25Kk7+PCX9nl+L8v1c9e34mu+lyX72C9pDDW24pg/nkGnuTHJ39AOp/bgNO4azU5zHt+kNOwdZ5o81TGRp4stHIYq4DxytslZ19kG51Kbg2zfV+vKvhZn2KUevdOXu8BrO33DVmBuf5OrXLkAHzXxeuB4oNa3A02cllKNxMz8f7DNb9XD/FyTs7slc2XGcw4cvhFrnud/yfC7UZ81wD6y83luHyl9nPh2mv+/GUg+Ua9TzfLYjghLv0hivxCQUbdZN6/hYoCFsyoz7kIUhRdERR5XUV9DhL/W809W94GIEieLAj9itpfrLOK8HbEtf6l/d/FPJbksf6mnHY/AXvLv30pAomt73k7gxGbij5W/UvmraNhHb3P/D8BeOUUY9/uCPndxWmJtnxOw0duvcdz3AfbHWzSxRWBfjIGhP8COLDGwph+agrCGXwnMC04wjKV3/lkG1ojzK2c0Bv8X+EZc/FzTTj23bf/a/XuY65Otyo8Os4F8zVQdTnlAuPL7WIfvVgKwz5zR4UoA40z5gv3y/kNqJd6RYeXqcnw36YUGBneXhuzzTVy50FRz41fTefxA1cPJDXJ4Sdjmakf7Cb19p5ZYYv4dfkA/mx3vcWW3lqH5tHnHf35K4uq9c4R9VIVpHxVV2MFpGdYeT1/3in3I68lGOc++0sTa5Tz7chPn5TxolPOkUc6XoZx2q5wbKCfJLBw+0iznxoRybrTLSWEoJ74NX/qMOT4lIg2sqEht73/+27ABc/hnyPX59/Te6meN8oSecPPMyzInE5BBNtngh5EWo5sayBP5y1PjK0baLuep74CjyACegLHZg9heY/LEjKk9pS/rNjLL5GYizOIodJxcwL6+h2rq/eNy0iD/Xykv/Qil9x8g3b70abN/R4/TvgA+SNgVhpHr2s2eWkN+zOj7pXXcyqSMsffzjOZYose0KQND34XfFgND38U6a3aGcORFv9aM9RIRTFz2sXnYKTyvhemZcwecO+wzOequFK3VT8opH/rq6xRH7mk9+AizG90vw+kV9h0e/jMVPhyRf1gCTF8VCH/IotHnz36K9/nAjvMksf/fujz6/JVP8T4fuW4WZJH/7+nz9r/SB/7pPn/207zPu3YeRmXm/Of7/L9UXvR56SNBfNL41hl9/ixhZ03M6POvMr6Dk/r80/Fdbfd5YBP6PLCJfZ5w5GVynwfe7PMM27vPg7NnnyeO6vNHH9Ls809XfZ6H/0yGT+zzCJcC8LX84324jy/PjZ/VMbDLBjbs136b9DmWgT1+yVrqj1LKuyfPocB5JecEBke196Vb0fh/XjZD5Vmbxj0q+qBzfWrvH9D+vx0VYztd+lmXIXLtrXh8X28wpfEh0HvqtQQwiUgrEtoIHfU2un2VFaynxTTjDde2dzdWK7cmqMcfK448UKCDqwcfRviJGRmu5FYIQ/jbZhHOfH/P7kM4FciwpxyH09k=
*/