//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_POPCOUNT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_POPCOUNT_HPP

#include <boost/compute/function.hpp>
#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {

/// Returns the number of non-zero bits in \p x.
///
/// \see_opencl_ref{popcount}
template<class T>
class popcount : public function<T(T)>
{
public:
    popcount()
        : function<T(T)>("boost_popcount")
    {
        std::stringstream s;
        s << "inline " << type_name<T>() << " boost_popcount"
          << "(const " << type_name<T>() << " x)\n"
          << "{\n"
          // use built-in popcount if opencl 1.2 is supported
          << "#if __OPENCL_VERSION__ >= 120\n"
          << "    return popcount(x);\n"
          // fallback to generic popcount() implementation
          << "#else\n"
          << "    " << type_name<T>() << " count = 0;\n"
          << "    for(" << type_name<T>() << " i = 0; i < sizeof(i) * CHAR_BIT; i++){\n"
          << "        if(x & (" << type_name<T>() << ") 1 << i){\n"
          << "            count++;\n"
          << "        }\n"
          << "    }\n"
          << "    return count;\n"
          << "#endif\n"
          << "}\n";
        this->set_source(s.str());
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_POPCOUNT_HPP

/* popcount.hpp
bKb0rOXywQvH8ru64qz0+3l73W37s8+EqgOpMhn7XMv12lx/YUW9Fa1/SwqK7bHsPPK33sSVfsTnlzivUNDnqn5uthGdsAjZi3ncuMSDLaHKmtqF4fG2Y9LEGHH+qRzfxaRp+r+HMWfT476aw5061VdVv7Ntd40Iq8xf9MOFNd4jHQa5VhguGwPfUXXgC8fQHZPAEUjO28V8bv+4i0ecYTZd9viYa206tFsib2un1VoxJ9hp0DVPSORJEsOqRuiaIVzfqXNYGw/heZOI569EHaSd1kyU39tp94cvVyqvIl3+7SQ3Lv9BkmfLT7zvY13A9pDcO9xn3No6B7dHHicnJ+901xb1sN+PQt0ad0hwlmh11tkIOqNAOyS4XjLDpMwynOIWg2CvdlE/y3OHT/Pov8zgLlAe8Oa4wY0tt/mPixm8XNaSHbMhfK5tGu4UehFljHBqZd73I/92ixcrg/4iXfLi+Xa7FsaZ28mhtwem7mmENHBnLzqca32lmxcbwuWFF9tcd0twjU/SZopjfPkaF09wWEjbKFuSx0KqzmSnU9wucYRdniqbsctbyTxJsIgD3TGMY9ZdW5dI8pLlb1xSc8mQd7fZKV/E173UEE4YAPQHa75LH8KlASC5jcscwqUBINdmO2RTCG61WIDM6nT8YiFUg+Xl4BqKFxYFHDfkbgaXfiGXVZhL3JuSOEe4u+IEnddDHys8LPnJhOT+oApHHFQE+izmOJ+IRH/sDeVyf2AOuHzM7bO1Dl79CsN5lCTbHzdSfVZpMHk+27hxjLd7q4sEtdEnps1IslYClt1DYfpO4pJOm8L1UCSXDvCG/i0MTdgHg7PFOC0LVHy7IZzSHkX576nzISnkPVDWv9RsYyGOyVkYL3cyuBsx5Qf24U9y4ve6t2JeiJDOb0tEnO7iWXr+Y/sk4lLri7epGyctvtGh3VOKwasS5Dcch/KxfsC6aO/OhuvNUy+OvLf7S9gYZYDsII9LWOf/SuHKP2tz6pIeC2GKJyZPYJhwHjuL6F96DhW58F34CKd2zxivdxJ4I8uh25K4v4HN5aBaWR5JisinFuFUW4E3I5xGKuFoj+UIT5aj9ZVLMm+qNTldqXU+b8u/bnGc2q2hTSOOaxTsFXzD4iq25Ar01BBe4YjgNZI8Gqc0/mV6W8N4PkXo0W+meH50Sv/eJI8ylXsKaQ75LxRKHrNvRTzqIHFW+kD0H50Sa5scYzWPOHp/1aRh7fbG2sUFzlH4M3k/awjHzjHbh/BI6MHbH8ILJgTGwrrh6UNEtl8O47nNFN536Umu3+P0Ydr8XRn2a8kl15sornU6/P6+bF/sWfY5rrTGSWb4zFWlz2X2+z9nsF+g0tB7m9sqDa9oBvNUE9432dMcu3fIb9Ff6FKGR3vIa3QFQ8SEOIjScvOWfT8/e6DluYZD36ZwHlIcy284j4YU82bTvCDAZzBnRTzd7oWYs7YO4RJvEe22YXmhC/gOw7bhxPt9nO9uxA2Tr1OXsG8tj/ea1mFvbaixQ6ohOxWwmsJcbFjMcReQaWMOZf8JhbOpRbhfKyZwsrFwB0KXvUj1A/YWrngJw+X2xXxwJctJt1lueKk221Myrfbn6MxOYtifA775AFWvvn9NnW0w9Xveg8OYw7522LfXZzlYn0Y8Ps+Bno04+kwGfX2HS0Q80lPs8xHhTgchLupFLB6diyzAxkxy3XkWPUxG5BOkibNu4DfTfL8HNDFYm9dxerLb2ToHuWW7tT6Ug8XYBvYVDuWSCiIu4qSmufasg+3noXw+78DcmuTymQf2gG9j24tkXsZDivqykvsO3ouM25tkxHYP12EvydfdA7li252e4dPxf7JfS6zqY2A=
*/