// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/value_type_of.hpp
/// \brief Consistent way to access the value type of a tagged or untagged type.

#ifndef BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::value_type_of
\brief Metafunction to work with tagged and untagged type uniformly

\code
template< class Type >
struct value_type_of
{
    typedef {UntaggedType} type;
};
\endcode

If the type is tagged this metafunction returns Type::value_type, and if it is not
tagged it return the same type. This allows to work consistenly with tagged and
untagged types.

See also tagged, tag_of.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES


namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// value_type_of metafunction

template< class Type >
struct value_type_of
{
    typedef Type type;
};

template< class Type, class Tag >
struct value_type_of< tagged< Type, Tag > >
{
    typedef Type type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_VALUE_TYPE_OF_HPP



/* value_type_of.hpp
p4lGbqiMTJanW8eV01DZ6wi5oWETjex1SBlLKbfMxZj2uh+5BT/pk0wZK6sYKrUXecu99Ra/g8lvnJY7GD5DdMRsSgjoUPyR3V8y6B0JCUZu7KsheplaV0anHUPH8TEtU77usfbRMtVFlEkE4L3GsfrPcef1hGTf7bwN0rwdSlI5Lc1bnuqvqJvt5A2tDiobHJEn9dchqg7YmcYdXYPU+0e2rAXpPUq+0zq2NeW4Xes8p4V6B8Jlc0eG6LEIrftKvYgMtLScWvcHnTGzomZFg16mPOdQ9T/wuNcaHdPefcEjP01h+dHLm2d+mk5SfvboNmt7DdQOc0sm5532X1FvtFtaXv1A/bcPzLGWuIubzwq6JbU4r9ujzYcYzoX03WLVObhf5WQfVhnrPWZcybMLrzpUfzlGT8LPxf5VayFpXBwpp27k+J6cFKJvjHjCZWJFFNTogHhR3K9iDz/VqnZ0GhEuus6xTJ2bfyPuW6yp/D8f46WDt3xyYAzmMJ4SVe/Yfpfc+09bqd/IW96beoiQ95ayhszhs1QnzhOM9QLljXa7THbaRaW7vdpG/Y6SOX0h9t+J/fqk8sREZ67R+mpH9kvh38TPZ5NMu4h9fkS74F90a30o7huTgu26Zbqjt6jEHd7Ue/l55SRp50nkBKbIfV5iRtw2v5zDtlriOMx7y/dLOsPwd1j8bU/MMPEsW7ucIRWUfVxFWo+Ln72Ju/2/Jpx9Dk0eEtcLMqZ8cg2pNtftw5K34sS3rK/7g3pN82cE9a9NkjnxHfGzOcnO/9W9JF2jT60am3Nfs0LirSbegVPtMDcm1Fq5CXKOeH8u5x7wZ1tf8Ntxbe6gZaC9slWfbYrk/+PEJfFTrCrfX+KmJva08yH9KUnc6pMcPSMilWn0PX35dNs9Wfs9mmLF/orv2bhfW8/Gb3HrfjBhTpuGH8ZSjoYpEvvj/jTO9YuLjx/i+9ga4qd/BXXVqpx6po6Z16Runkv8u3Wtf1ri+UFdtdpWixPaWaMxk+R684b43ZLk5KPO3Gu8L/7fTdhrdUoI6iW4S+prZ3y+5Y/vK/7iTB9oR994P/7auGv93yeVwdZ9CXOtvokLLAlr6vpef3trq9T1/TKWGtbxz+i96C/9YmTccOuYkesuk3MJlhOm3oRZRJhdkv7TiU/Qv+QcYVbKuZcTsqx3/E7b0K4u3bkvSH76Wr3Fzgmp54upmxTktobEfTku2Vrj+7W1xr/FcuKoqql03QNcLe3ZXup+PvYLxe5jzGTQu9twb855VxlStAzJ1joJcyZh3pM2uDppYWKK9VhiAiEnd6jVddF3pN8Hz8lJHYfPc07z5NLN0lvn+48kztKkpda34mt9V8edl/CetS5xm5WZNE79OO3WP36JlU5/qknIpb2SrZXkgXEkcyMMzIdO/zCJZer4qJUyp/r/Evem9Y/4bW6dO0bv8jz8nS31e5N/m/Wuz9ZZOItrXPcOjBHmu7T4z81GV6E/LTUpNZ8fVEX4GtX0kTbSbt9NKLQ+lxCyTlU/GfAfUrYfJNxudU0InAvtf6LvVvNwKXl4Ios8dNgw0teVxNumutdTpr+0k/yntKi/uOM/EIzft+G91EQ7/mx3/Eafx90S3wT/Quu3vqB8+VI511Xi66vx5VPAJ4nPt2EfkXVuy6Kwa+qk1KlY4n2ha0FTZxUSz83+W62XiZtzJm5fSF43Zmhe/RsuS00ixnadotbFrBbOUXLvq3HvN3Ff8XZa26TUdkSflhKRX5lnbpM+9ZSv0Nrkc8eR3zEYx8a8tA5Jvk6RcZh7k5ckjst8V8S9Z30pnr4fMl/dR7td4L/WHxdnxx/sj00dA/3Rt/EBuzvGa3f0p0Q=
*/