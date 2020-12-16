//
//! Copyright (c) 2011-2012
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
namespace boost { namespace numeric {
    
    
    template <>
    struct numeric_cast_traits
        <
            char
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            char
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            signed char
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned char
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            short
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned short
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            int
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned int
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            unsigned long
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            float
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            double
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            long double
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            boost::long_long_type
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            boost::long_long_type
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            boost::ulong_long_type
          , boost::long_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::long_long_type> rounding_policy;
    }; 
    
    template <>
    struct numeric_cast_traits
        <
            boost::ulong_long_type
          , boost::ulong_long_type
        >
    {
        typedef def_overflow_handler overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<boost::ulong_long_type> rounding_policy;
    }; 
}}

/* numeric_cast_traits_long_long.hpp
ICfIeIzeTXe3Q40kM+E1a2D1QJw1yHi+jC/RHoicEM+0e7+pJnKCjOfS7WK1TcgJMgtuVcboISfIDHl9+eAUj/VHZsVs9LstqTiHiH6Ge19DfhaR2fH13vKeEepSmmpfBp7znILfLZHx+YzNU/59iyDRrrxJGPIznIz3c8kI26mYMzLez+9NptdEXSJT8BgdKlqIc7noy8D9sc/w/VO87+n13BGoS2Q8z1qPi1b+/TgyWz4+9bbTUXsOqJ7PEhfOKMcZjMyK93P2Xh+cJ8hcmL1OiMXdMIpMn9nGK3+Px35Lxuezo7vNEeQLmYLPp4vxaezFZMa8vpx4+x3zIuxM7M7nONOK8emWh2lijyPzqLTeZAuWutbBmf2gulp9ZgmLPN+jtpI1qfxzlb3E/9fUuoOYswqLur42DudIsprMhtSzRxxeH1T2pSfZ3lk3xqDWHaLfqzEbnOqj/PdUyTwrLZws8k80zuzxh5TP7EH2/Nl6fCPLJPv/n8fsTvZme3PcLYIPo58VZuN0uR9qJJkZszFLrs3C+8iMmMVs+YH3JZPpMQvp9CMUtYDMkNncqVPuoRYIG3bQxQJ7B5k5szSfGvqorWwM3cjofxZgPo8o78xdyS7n2yHn25N5VVoXsqyWU3Cej2PWmazdaJfTiC17Zicyh7jjHxBbMptK+w/Z0tMjh+NccJRqFjNzrSaIuxuZBbMfVjr7UOfJPJkF2h4MwvojM2LmEX8Tz4wjUzB7sDpzL9afsF993pzC+hPWxmFpBGJEZsissMs2a8SITIeZ987CrqhZZNrMVhwa44rfxwlrkl2+FbEl02V2Zv5BP5wZyAyY5aSeVmBPTVd95s2ANriT6KYr/2xTR7Ktu+w6oH6mI5cq7POwmwdxPstQtusg2lkcQ7sKa37N9Crq5zFl/ELIzi/J/oQYHVM+s4145qjjeGaFlU2aPQtrjEyn0lqTGTdZnov4kdkyK7TPLkONJKv8e0QVtny9Rifcb0/gfRU2f4bheuTuScpdZj/6D89G7pLZMDvwcowR9lQy3pdam00u4BxCZs2seq0antg7yLwrLZjsYdb3jVh/ZPrMJj8/dgu1TtiQF7l2yE8yI2ZjMg69RQ6S6TKbWjRsKta0sCGlibnIFzJ1ZtFhUdg7Ssn0mDUPb4y4a56iP0/E7F58w+M4v5BpMyuJbOCHPBPtOj9cijuXA5k5s2lFL/Cty4+Mj6FMEWWHGJHxfiZZGG9FjRTtJim2Y02Hk/lUWguydo3r3cD+QOZcac3JLmn+B+shnSyuMgf/tbVjku/gzH5aXc2PtbOqFhWImkWmz6x28rIBWA9kgczMhxYiJ4rINJh1bBLxDjWEzINZUhtjnMtdMtXVOlTY//rZqG27wchPMj3WbmtPnTY485F1ZO0i6RfNyCUyXdbOKWks2pWQ1WX2Z7wazlm1z6ir+TLbF6bRFN9+ybyZOayduwrzQsbfZxmXH469mMyQWb+AnGjUeTKjSgsiq9Hu9mWsIzJLZqv6DaiL8Yl2bTdUs8V6EO1yVj5tjbw+S7Wc2ZhtU9aivpDxZ2rNTVB+EyezZbZOp/Mo5BKZIbNRl3Z0xr2YTMHMOfxtJs49ZNbMtlTbqIccJDNm9n5xHvbprWRmzOamFb3CfArTGKxoj72RzJTZjh1lXTGfop/DPzxG7fkp7PR5r+o4056jes1seuR6XeQSGY9D6oe65ljvZPyZj2+Vm6Jek/H5/H3gMc7zUaLdyjcLR+LeSGbObNHfHbB3JJLZMHu9tPVfqBNkPA4rfvjvx5yROTA7uLHzJuQZGc+lpI1+iJFuluq8VN3ueA77OxmP7bPRLvgmECDa2UStnIY6KNoZnHo=
*/