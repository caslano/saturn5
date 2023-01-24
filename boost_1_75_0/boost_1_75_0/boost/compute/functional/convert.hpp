//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

namespace boost {
namespace compute {
namespace detail {

template<class T, class Arg>
struct invoked_convert
{
    invoked_convert(const Arg &arg)
        : m_arg(arg)
    {
    }

    Arg m_arg;
};

} // end detail namespace

/// The \ref convert function converts its argument to type \c T (similar to
/// static_cast<T>).
///
/// \see \ref as "as<T>"
template<class T>
struct convert
{
    typedef T result_type;

    /// \internal_
    template<class Arg>
    detail::invoked_convert<T, Arg> operator()(const Arg &arg) const
    {
        return detail::invoked_convert<T, Arg>(arg);
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_CONVERT_HPP

/* convert.hpp
D8f7GWxlTONc0F/mDlHFovMJ+c8e6MQf9L3KIbs6+SZyXkH7wX9zlCZsk1lAL9H7UfQXhcbR8ykHq5F1CEaiCnBWcUnwSCla52LmMAao7d3iRk4o2ufZpP7A7aW71dmlJkfl2bXSPGwvFKN0RS5fd/OHpkrT5lGT3uSdZ2+y1oePMP2VT/7QvKW/iTZ8ki138nuMZz39qce5nNAL3OYQWHwZ+FWM9QOObTtG74HuLy1/H4+ELl/pDCfvs+yZ5TF0/mFHHm9BMLAqInZkmhF5p+kLVU984vC5K0wvK6ZAFWVTy8KYUtp74QGDWuN6u5QFl6g3tnh28fq6h3eVaywokucAHSqemwJRom5syPVt2duDqrFTmsPN3VkSXU/qp6NveZh9g1dKVUQ1F11ixEB7u9eNU7MdIvz6GQ6a/JVfsoR5s3lghbVZ5DI/T4OJXPSRsNJQnnswAXnJyjUyjHqEsev1M29xcPXM5LhIBClW3qz0jfpNC6tCXTsHNF9nBg++IgJnquAd6Au6YWxLb5u/3t4En182FzCeEYndg/HoB0PJZgk1qOKTNL3UrY6luen8gV5juXLw2PvEZ8sEip06JXgOCdK/FqDLnnw551QxIS9SA1WYRutAXQ7DHayfNrtDGPIx3b1g3K9SxTXknctoYNlmOG1rt83OFDfb2zt9ZkTRwe5brfd0pRDb9rV+STM1stqlpE+F1JH3sYjb
*/