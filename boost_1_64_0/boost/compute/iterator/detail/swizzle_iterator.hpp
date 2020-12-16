//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_DETAIL_SWIZZLE_ITERATOR_HPP
#define BOOST_COMPUTE_ITERATOR_DETAIL_SWIZZLE_ITERATOR_HPP

#include <string>
#include <cstddef>
#include <iterator>

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/type_traits/make_vector_type.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/iterator/detail/get_base_iterator_buffer.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

// forward declaration for swizzle_iterator
template<class InputIterator, size_t Size>
class swizzle_iterator;

// meta-function returing the value_type for a swizzle_iterator
template<class InputIterator, size_t Size>
struct make_swizzle_iterator_value_type
{
    typedef
        typename make_vector_type<
            typename scalar_type<
                typename std::iterator_traits<InputIterator>::value_type
            >::type,
            Size
        >::type type;
};

// helper class which defines the iterator_adaptor super-class
// type for swizzle_iterator
template<class InputIterator, size_t Size>
class swizzle_iterator_base
{
public:
    typedef ::boost::iterator_adaptor<
        swizzle_iterator<InputIterator, Size>,
        InputIterator,
        typename make_swizzle_iterator_value_type<InputIterator, Size>::type,
        typename std::iterator_traits<InputIterator>::iterator_category,
        typename make_swizzle_iterator_value_type<InputIterator, Size>::type
    > type;
};

template<class InputIterator, size_t Size, class IndexExpr>
struct swizzle_iterator_index_expr
{
    typedef typename make_swizzle_iterator_value_type<InputIterator, Size>::type result_type;

    swizzle_iterator_index_expr(const InputIterator &input_iter,
                                const IndexExpr &index_expr,
                                const std::string &components)
        : m_input_iter(input_iter),
          m_index_expr(index_expr),
          m_components(components)
    {
    }

    InputIterator m_input_iter;
    IndexExpr m_index_expr;
    std::string m_components;
};

template<class InputIterator, size_t Size, class IndexExpr>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const swizzle_iterator_index_expr<InputIterator,
                                                                 Size,
                                                                 IndexExpr> &expr)
{
    return kernel << expr.m_input_iter[expr.m_index_expr]
                  << "." << expr.m_components;
}

template<class InputIterator, size_t Size>
class swizzle_iterator :
    public swizzle_iterator_base<InputIterator, Size>::type
{
public:
    typedef typename
        swizzle_iterator_base<InputIterator, Size>::type
        super_type;
    typedef typename super_type::value_type value_type;
    typedef typename super_type::reference reference;
    typedef typename super_type::base_type base_type;
    typedef typename super_type::difference_type difference_type;

    BOOST_STATIC_CONSTANT(size_t, vector_size = Size);

    swizzle_iterator(InputIterator iterator, const std::string &components)
        : super_type(iterator),
          m_components(components)
    {
        BOOST_ASSERT(components.size() == Size);
    }

    swizzle_iterator(const swizzle_iterator<InputIterator, Size> &other)
        : super_type(other.base()),
          m_components(other.m_components)
    {
        BOOST_ASSERT(m_components.size() == Size);
    }

    swizzle_iterator<InputIterator, Size>&
    operator=(const swizzle_iterator<InputIterator, Size> &other)
    {
        if(this != &other){
            super_type::operator=(other);

            m_components = other.m_components;
        }

        return *this;
    }

    ~swizzle_iterator()
    {
    }

    size_t get_index() const
    {
        return super_type::base().get_index();
    }

    const buffer& get_buffer() const
    {
        return get_base_iterator_buffer(*this);
    }

    template<class IndexExpression>
    swizzle_iterator_index_expr<InputIterator, Size, IndexExpression>
    operator[](const IndexExpression &expr) const
    {
        return swizzle_iterator_index_expr<InputIterator,
                                           Size,
                                           IndexExpression>(super_type::base(),
                                                            expr,
                                                            m_components);
    }

private:
    friend class ::boost::iterator_core_access;

    reference dereference() const
    {
        return reference();
    }

private:
    std::string m_components;
};

template<size_t Size, class InputIterator>
inline swizzle_iterator<InputIterator, Size>
make_swizzle_iterator(InputIterator iterator, const std::string &components)
{
    return swizzle_iterator<InputIterator, Size>(iterator, components);
}

} // end detail namespace

// is_device_iterator specialization for swizzle_iterator
template<size_t Size, class InputIterator>
struct is_device_iterator<detail::swizzle_iterator<InputIterator, Size> > : boost::true_type {};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_SWIZZLE_ITERATOR_HPP

/* swizzle_iterator.hpp
U3cDVr+MbHP03l3QMad722/fPU0MxSTbpHkvbXBUNfltyC91LxMrg2CqTaGg4xsOGrj+Pmn67z4Ci/msfyfkTd/PxNjyjDXiAcDal3wYB887AozUH/TRSotp+WKOCowx6tAOH3+woPUbpHT762+OCZzZ8rCPPVTQpADh9U033e04zR8GmnmJro3lFz4cGOOyXN+PfY4RpqPvsBUEbsnpw2ErCFzsEu4a9pa/GYmDasMY/pwnsKN16IIP+kj9+LAAGGM/SQ9TUaeLIzDQhJq86bAfS/WCvCv9GOx39X74XtSPtdeCj8T9OBrzkHU+6cWgTZDjwtLZVZwlcfx/q+yxB2g6+5PjVzei6nvE8+MG/pDCQ9+2+z8Dp2DYvojpCZlTO/qwuNBu87XsFDjoHwB0vbOwCxj7Yhz9sbSHMP3rN+7N+SMMW1QcpU7OecqwJ4QFS8ujpfNMBWXpZ1mViJtbuSTgjT/sXQqPeKJpkeZVY8oIykcFecUD8z7/hWa9Kj+k3g89EfpY6Iv6nU/NgjPO63WeB+dunnn0PbJeCOaH2HoKC1tTxIMwKLOOncqy/ZzX+UqWBI7jeGnOtA6Hfblpr48+Y0x7W5ryMnSrNGJ2+E8Hdlqjbh5LyizweRChwbwZryKP1HLavC+6ZPAFLC9il4e+r9lu0Np23omx42Y8xCSM4izy2iKPP4ar4hA34uWD7Zrvd+B6Tun4JWvC9pVNv3zuOdr3PyihBnBijxn32RxxOY6bcTydJCe0qoafRMGJ6WZ8BYjLcdzsy8r/L2fXEWNXT4UzJEDooYceeockzMAMLb6+tm8vZAKEIpLJzIOMmGSGeRMYyuIXYsECIRYs6L3X0DuEIoQESBFCAgkWWbBgwSJCCCGEBLaf73d9fO+DBEHy//873/FxOfa1fY7PSdM2izsuLDKrQXyIZcIXsSyvlExKn892Wjg+LeGLmSjTLKsbwvcSeTpTL6M+8OzcgtcPTdQWbVpGOr7HIqYNsBeNDGCTRiuyikuD7a+QMb98bMXisqiyKs4MeKLDi29t78DehDiHd5wOYgSnbZ7GpeokTDbsHirkxxrwEZ9/OW+yvNTri+GmdgrEpKJ1zIRMuYpsg9xVGGRsdX1w/tV+/u6krYRKZM78+8KNDnvNL/85VauXpKRttC7aQzi1xV4ndW9EbAJ5Vt0UnmL9Qr5vH79oIn5GxrXAHGcHcS3/TNupJ65WX94y7zza8WwhFibV+bjguVI1MbmKrm+Qy3uV6mBbJWVS6xYPNsC07cd8vpI1CVdS5pmbjaazKP64j19py4g3pcrZ2pW9i/b7ZdHe94St0rW+VClPc9GVr8d6KOMsrVObC96Ytd6AZ3xBLBgfX7G65ublTKGvpgfVwnq/H/QXVypuW5EM7drUHv4ewpextomypk4Kx5etrr5Y8xnXyVU94yMEFH2Mi9lyXBl++qXrYqA8xsVauQaM/+GZxVt5goulciQZwyDmCmLEXAOOfCgANH6kn9D3A20KHP0wANnHejmfOSy+BCgPsV6udxgs07Ru10zO9RyYfnG173op7jpwZDEF8qEOd6wwuJ3nOBOpIVnaL7X9gFlat9e6sHdhS/sEuv7+swLNdvJDu3aW+J2075MmZk5Hw4wEpB/HKsCc7gfyCa7fb45jUNgzXF0ONMANlQzomU/mVMu2ceh0BDoZVef0kxVdpz6+2U8Whn3u7yXfA0zY3/25/8ghh8H42mMC6J8Z0jW7dy9x55Buji7eewjQoWM4h6CMuwwwpI7vGtCtEOy//wU6mRuQg/646yjOyoJN5fA4RssD5g5g+rkfxu85erchxo/f864xuhbi31f8C5gxXbECgf3A3f8=
*/