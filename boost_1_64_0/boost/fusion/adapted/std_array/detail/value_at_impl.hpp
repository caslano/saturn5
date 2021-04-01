/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_VALUE_AT_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_VALUE_AT_IMPL_01062013_1700

namespace boost { namespace fusion {
    
    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<std_array_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename Sequence::value_type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
2coRg5lntgYIBEDLwYARQfBMJjgJ0/fIV9OtLqkWL3dVZxxKBI7WgWhiuNULY/jWhIHevIjTr3C8ItXBzng4Gz7BFHgNesXmQ8JbCVFthNKs+FIAqyDTfIeYR+9uuIGD/0RXSog/R+3TjseOKguMf1HaigDyZBf/eXrdO7WjxVLM/gY2LjGF2YMoxDha9JmhYjg66bMMEaUEDH1MmLOUYkxorZArzX/tNdJLnXL3nb2rCPwXeg64PshAfZnRSHq9+gTV2zYGdxdp9+7/tEzleGixX9tnP2kQzoIJK6RfMGQ4E62ZFW52Z6sEnVrq6W0+IsY2/achiS86LHL9wSYMEaggyDkdjlCi1zkpFTAEh7Lhdrl6tdICGUT3tcB5o87HRHq9WYJrBJ3iudRRwFKen8dSBow0W5ymTSJiqR2tzD7gTxBnDXJ3O7fkPH6yg/41m7xvjtkXcBI+YedGrQ7IzuLNf8uzoKSxV4iRLPipDsKy8CcCJJQOVEuZLOHgakVz9IOXW5rug9iayAsttyv3cN4HDqL+ekt/ZL4PXQVGE47TpFvl4NGugv/0Ow==
*/