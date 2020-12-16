/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_assoc_struct.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED_NS(                               \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_AS_VIEW(                                    \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)   \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED_NS(                                   \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_assoc_struct_named.hpp
08qpe94iLhnVzWeZWqcMujvIK7OdMvUN8yN+mvL3m+OUU3OFURfPzZn05ww3r5T/3h70dHIyT7JMXXqZaBzxqt+TDB8WJ/2LpZVT+a4hrYx/FBbnu7hbzpnv5rlljTzV6JYx8lQinQwnl5JLuuWQ95RcyimnN0fYx+6WM/LogvQyjSnULwtdMrKaQoMh99ksgpxLb36mwTVGRK8cnXPmz9J59hs06ubF4JW+HesogMvVYWqfw9kGzhmB8XN8PLUQ8yPs/xLg+hWIWETA/Lng5bjVWHHNcf+JwZtt73ng8Fb1XOy3Ot/Ea6rRjl9g4Ch7cOtCg+MMxPhFJh6Nw62lBo5yBe5ixameJuL7U3DBeU757iUmj4wnuWUGJz+mv2/d5+r9Oc7lGoZRPbIo1kRovI6vAK7NsbAflwPH/CpjVwDT16n/DJhMYW4IOb+vBC5WFIa562JfXYi1ELqcrm5CXK8Cr8/LXg0sOH+DPesGH2tI5tQmvfVN19rchEhtA+ZrrwPnmuu9PsjJc+mTjVwH/FznzbLp97lugIxjjkiez63z1n2eNxocEomykt4nXGXIJGclhBt8Xa7kb9J5o36QZ2j+0uBTYmqS8Zs1HM2Y3NNu4A01iTj2tAN3zGtzXFZrPHqPGO1VN0aqcf9vWplw1NOZrtmTTFUkNh/+3Z5OjleaSrfu2KMMO8Zyd7rkULL1tad3KTk1WkOZWWty6pxv4NbcH3P3gLPm/Dh+68A55/rg9r2WjL4W5j7Fqbk9pN39FheJhSNhznd8maO8F1iTUcXRHG/8SsnYa+jlWgmNV85L7kHFyZFzXSTmubve4BobFi7yJGRaPwTeXnfwcBCX+ogIVRUJrI3QZMziKvlHFe/cW/GYi5ctIvO/AR9Y04A0eRy8a1/GBo2rt+q4J3RO1XFyT7zP1fNRbdXhM+RaCOBqj4f8/huBB+tvbn1Y5um0Mrz4kuO6CTL6t9fbr2ccvHxb+rHZyWNpJ84keNaXScp99Hjmi+rDXKvJtRAGzv0auYceOA7ahfqJKwC5HiLAK+63JofXcKY5OP1++q3AuNqMho17F34HDqNd2QVAOrxkcrKzzVGjDx2Wbe/LLhmmUeq99RCmnJSY7c3iKrlX08kB8OaRXksrNy9VXcdne/v1weuQ1SeC9fvftwV5uMWx4XC9kU5GDVfkmgi3HE5N8YXZzd87ZJGASDv5TbdDTn44rIMAZq8Negu4tdxX3jFsckRgLz5w1E3ohknubXDoZkgtBd57BxznaqteeFfnrL7Pe4rT2ivcMaw4Z939geJRB3Pdz+/+SXHO+vlDjUdc5X57hTvr3r8o3ll3/lXxgbVgH4GT66BwvzAwew3U34Br9Xc4VR+X++yDHHID9tmDN8Kn7Qn4NMijUsMaBTePSg9rFJRMPN7QmIxoqy69PLbLk/FrfOy7t3HtHsgvwWHdF6/z8rivwKELieyHvfcGF/Hvjvw7cIzqGPsamL4f7RsTw3oYrBlwcMaJUQjfd5CrTuqrZXHPsIPT943+4ODR12I+1MbNJ7E2LUPx2spV6Xem4mZ7e9vhNqddM4PnF/m95jaugsx8iyAPZyXfMsgb+0QOAD+fz7ZQZ1K3MvBGJqF5Y/5ABx+njxvFXoeDHHxjdWx2BN/iYIuvqY41xKJn+vVKa5OXga+N8ruHBDnD7TYWj3D7c8GH2nwC3mt95raWDBXDRARz4O1Mzr/3h2s3tIft08k0RuR1Q6JyQng6aLKJaNi7PaKhUcaK49TRlAl8j8NMXk9P5g83+UCadDJ5Z5p0tmT0NDnC5Jxp0iUoE0wT+HWkktW0EziPXXHGOepHKdx5jno3J6/WwXcP8MFz1LM=
*/