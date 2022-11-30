//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_ARRAY_HPP
#define BOOST_COMPUTE_CONTAINER_ARRAY_HPP

#include <cstddef>
#include <iterator>
#include <exception>

#include <boost/array.hpp>
#include <boost/throw_exception.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/algorithm/swap_ranges.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/detail/capture_traits.hpp>
#include <boost/compute/detail/buffer_value.hpp>

namespace boost {
namespace compute {

/// \class array
/// \brief A fixed-size container.
///
/// The array container is very similar to the \ref vector container except
/// its size is fixed at compile-time rather than being dynamically resizable
/// at run-time.
///
/// For example, to create a fixed-size array with eight values on the device:
/// \code
/// boost::compute::array<int, 8> values(context);
/// \endcode
///
/// The Boost.Compute \c array class provides a STL-like API and is modeled
/// after the \c std::array class from the C++ standard library.
///
/// \see \ref vector "vector<T>"
template<class T, std::size_t N>
class array
{
public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef detail::buffer_value<T> reference;
    typedef const detail::buffer_value<T> const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef buffer_iterator<T> iterator;
    typedef buffer_iterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    enum {
        static_size = N
    };

    explicit array(const context &context = system::default_context())
        : m_buffer(context, sizeof(T) * N)
    {
    }

    array(const array<T, N> &other)
        : m_buffer(other.m_buffer.get_context(), sizeof(T) * N)
    {
        command_queue queue = default_queue();
        boost::compute::copy(other.begin(), other.end(), begin(), queue);
        queue.finish();
    }

    array(const boost::array<T, N> &array,
          const context &context = system::default_context())
        : m_buffer(context, sizeof(T) * N)
    {
        command_queue queue = default_queue();
        boost::compute::copy(array.begin(), array.end(), begin(), queue);
        queue.finish();
    }

    array(const array<T, N> &other,
          const command_queue &queue)
        : m_buffer(other.m_buffer.get_context(), sizeof(T) * N)
    {
        boost::compute::copy(other.begin(), other.end(), begin(), queue);
    }

    array<T, N>& operator=(const array<T, N> &other)
    {
        if(this != &other){
            command_queue queue = default_queue();
            boost::compute::copy(other.begin(), other.end(), begin(), queue);
            queue.finish();
        }

        return *this;
    }

    array<T, N>& operator=(const boost::array<T, N> &array)
    {
        command_queue queue = default_queue();
        boost::compute::copy(array.begin(), array.end(), begin(), queue);
        queue.finish();

        return *this;
    }

    ~array()
    {
    }

    iterator begin()
    {
        return buffer_iterator<T>(m_buffer, 0);
    }

    const_iterator begin() const
    {
        return buffer_iterator<T>(m_buffer, 0);
    }

    const_iterator cbegin() const
    {
        return begin();
    }

    iterator end()
    {
        return buffer_iterator<T>(m_buffer, N);
    }

    const_iterator end() const
    {
        return buffer_iterator<T>(m_buffer, N);
    }

    const_iterator cend() const
    {
        return end();
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(end() - 1);
    }

    const_reverse_iterator rbegin() const
    {
        return reverse_iterator(end() - 1);
    }

    const_reverse_iterator crbegin() const
    {
        return rbegin();
    }

    reverse_iterator rend()
    {
        return reverse_iterator(begin() - 1);
    }

    const_reverse_iterator rend() const
    {
        return reverse_iterator(begin() - 1);
    }

    const_reverse_iterator crend() const
    {
        return rend();
    }

    size_type size() const
    {
        return N;
    }

    bool empty() const
    {
        return N == 0;
    }

    size_type max_size() const
    {
        return N;
    }

    reference operator[](size_type index)
    {
        return *(begin() + static_cast<difference_type>(index));
    }

    const_reference operator[](size_type index) const
    {
        return *(begin() + static_cast<difference_type>(index));
    }

    reference at(size_type index)
    {
        if(index >= N){
            BOOST_THROW_EXCEPTION(std::out_of_range("index out of range"));
        }

        return operator[](index);
    }

    const_reference at(size_type index) const
    {
        if(index >= N){
            BOOST_THROW_EXCEPTION(std::out_of_range("index out of range"));
        }

        return operator[](index);
    }

    reference front()
    {
        return *begin();
    }

    const_reference front() const
    {
        return *begin();
    }

    reference back()
    {
        return *(end() - static_cast<difference_type>(1));
    }

    const_reference back() const
    {
        return *(end() - static_cast<difference_type>(1));
    }

    void fill(const value_type &value, const command_queue &queue)
    {
        ::boost::compute::fill(begin(), end(), value, queue);
    }

    void swap(array<T, N> &other, const command_queue &queue)
    {
        ::boost::compute::swap_ranges(begin(), end(), other.begin(), queue);
    }

    void fill(const value_type &value)
    {
        command_queue queue = default_queue();
        ::boost::compute::fill(begin(), end(), value, queue);
        queue.finish();
    }

    void swap(array<T, N> &other)
    {
        command_queue queue = default_queue();
        ::boost::compute::swap_ranges(begin(), end(), other.begin(), queue);
        queue.finish();
    }

    const buffer& get_buffer() const
    {
        return m_buffer;
    }

private:
    buffer m_buffer;

    command_queue default_queue() const
    {
        const context &context = m_buffer.get_context();
        command_queue queue(context, context.get_device());
        return queue;
    }
};

namespace detail {

// set_kernel_arg specialization for array<T, N>
template<class T, std::size_t N>
struct set_kernel_arg<array<T, N> >
{
    void operator()(kernel &kernel_, size_t index, const array<T, N> &array)
    {
        kernel_.set_arg(index, array.get_buffer());
    }
};

// for capturing array<T, N> with BOOST_COMPUTE_CLOSURE()
template<class T, size_t N>
struct capture_traits<array<T, N> >
{
    static std::string type_name()
    {
        return std::string("__global ") + ::boost::compute::type_name<T>() + "*";
    }
};

// meta_kernel streaming operator for array<T, N>
template<class T, size_t N>
meta_kernel& operator<<(meta_kernel &k, const array<T, N> &array)
{
  return k << k.get_buffer_identifier<T>(array.get_buffer());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_ARRAY_HPP

/* array.hpp
1xKB53zgdGMhSCoqXUdEt6Pp6exGgmeq9g1F8nr1a4no0XPoHX82NoPKycTvwS02uVrKfQlLVdmtOSIrbL6gu3oHqEQbNPknYreSmLUrHQYmAZTrjavbV070lNEHpunGptK5q/cwQMgEyJNxwmkwsDqF4zL19Rn6hPaXmFt7KcF96WV092tDzEXSvjERwa6PRsRVnbYmpWqQk/+iT5BAt60jBNFKUIVKX/12yFBKBQOpDKSt0dhJAuMEQJm3T8uMzH9+QZ5rvasm1qklR+Z/AGFHTey0sCPm6ItIve0NyXVtYFabV0CihuQFNafnb3TVnP5JNV8T/2nN6UnrHfkatTqsjSMdVlk5qeLpd1dBXf+N9NLHUOcHQhsiYl3A6FL7Oy6IXuTq1XWXHTuqcn3CLNYVyEkXspnjfG0+IpsTDp++ZtbDlHI6BU+ngITGK48iolPdgV2uuoO59SxtjNr725UeHDKs9P5lBf33R6G5NjqNo4jFZaTXECVpvgh3MK2Gxp3JDoUFRgtVu9QnD0oX4qqzdAEeIMgpJ4doPxiXMjJA79+Hi2MDK6VDINAVbT8igRJDBCdyUASRrWwKpR5Sk8lY0GFhFKb9gyQOAANupZLn0Jn+uQ1P6NRhb0k7/2RIQQjj8SmLgIcRsCMB2zAB6QOW6Bq62Uwju2uX8k48y1adrt3cV8jb5ZtgdAOYlwdM1FUdQ+bxmUn6NcpS3q5WZ9BftWNBC93yhZgwg5TxfY02Oa2c/uZ7oxqSlF02tYwHXLKU387OIrb6WoW65/93LAp16bj7xch76I+QjfcwMpoDjGIvBaP23BUeKTkVra9ayGtFuSvcUh4gf/+RydOVZSGbNhmw5FkYd6VJ7M9/tLSlrIS0sHM6rPEJSBmI5a5Ilx1QHMhhtKow0179yChd+RGVnnblqPrcPjhKrX+klJZOJ1xYyOdry032xlnsJecWeuSrsAxTlWoPJ+co1W5OusxE01410SaVBaAU139vliIZqsYJ3KPEzy0A6voOYvAPBA7txTlBp0IdyFi+WuihTQAy35XKdC4fs62oUAvTJDxPpCWSiXTCIHP6HrxxnEctdOsT5qC2FvJ/YPt5Uv7Azpg6tyTKTtTQJsjmlyM084GUZ4TUrrOMVIl/FCnQPKeZ1pxDKqd7Z4IebH+WdfM8U9WbeJxyizdhw05UovmRlU7VIU3APUiektDE1RzYNHqlcU6QJCp38Dj4vxWjy4gDgmMwmET66XdDuHkJAiW4IX0TzwlhnA4tD+WvHlgONLTT5pExqZJcED4MCX1Gwvcw4c0QOB/33SxmkTkYmV1Cq/5ilrjiAvAr81fX3AAFXJRmFnARFHASsqSNb1nEyqFPqMd18EXp6qIMxkOdhmWVedKs0Jr+Ty7om95Lm4AT0qsacw+7Ib52iH6Pu98+YOE4C+NGS2FbMxgqt+k44wGUkE1fn65PyDNBjzJBYpnGV5Kb0itVHh4ZlWqRvVK910mCHijKajIbdfPtNB58x1xezlx9EEQayi+hP7vKkshkbzSA/+gvbFCP+SWrUasxJ1zkvzyUj0PH1XYGMxb+00PJIY+i1ZTgfpyHLmR7nnD6zz563q4YT7iUMC7kRG80jkday5SzzjVyZO0g9Jv3QBeOxws8StSpxJx1+6Wb5xYPyv6GwPcQzptb/L18bUNgCMIXzy0eki9sCOgQ9swt1uUURRx05sqDaxq1K4S38nV0m7VCCA1BaEjLg9D3EPpeuxpCgxAa1GYYuRF5UEtt8AChsXPHyqn5hfN9J9d8YxwlEd7iwKPOjmknRt9/UWYKB/6RUndkMddgT0Zj2GgTXnFmad9i7eoNCQBzK8024SVn1tpvI4U4/BjpLdznbMRh2zmw15iHnZC3r6xMl3HzBG6k+BtpVf2nfHuZxB4CiVWLoR7v/mX93yoD9jW5kYVJ5laOiTT/JDjfXb5PpL+2OHArh9LE42HFiyNoM5vP2c0BFXMYEF/V5VMl5gkS3D2TWVaWK6fLzrIyLcHYgRHSS4CZAX3CIG4C6i2hry49AR54c2QVHd7NIT78I7s5tv8KnfF0tptjeB/HENvHkfbj+zis8z1gbD2+k/JY39l1qcbJHTsOI7UHjBeHwuu1ePJk07rx9D9et5zLsfoQOpdlmCdkn/sr6/iPEMZFjkoipr2NY71KX2zdNb6TkgDkU8pLyuj5j7G+j97xunUohy6HIDHP5hhMslE8pLoYXNpMmoe5TsNcn4ESIV7YPMMTvw9dzwTzwJEx1GFngPLQDTJxcrDz87uLS8qhA4j404pL1KCbnfBBIUPCNPBQhXCIHRvifbul91Wb9rZxtE0ZuF8IByDGd1KoW4vPs8JDOBeLRbnpUVaU+K2Y0joeNOoc2a8N8QdHrnNBfcbOzRtV2vQTf1Jitv5O5Rtbg+j+Ht5abHMSJXSI7KRlcOVwRc0Y7erg3ATkAN5+xN9FG0GYEbEr4D1cAv/KI2JHgM2LbZmCEwnHIFwWoMnj0D7M6BOPOeRsvGtn7JwgxWNQR1E8Iccy7UrQbTnjHKhTo5DAJn8Fv3Z57+i4UcOzd+pGqeJ/wuf5/4RPbjSfr0/8f4zPcXWjdoqllZAK8xiUr1eeSLu3WkqdN4hKHVdAi3JF97q/w4CpPsHXXm0njfkAWD+G/nnryBinvTxSbWtOyCEt4f3V5zek1LVJCcKOtgLNEcqpqOfzbwjv3xSH7Jo5Lrx/w7ga3+yNqZqjmcspqpmTK/UPcTXXXSW79PlObVw5/XXzkJ4fKC+jH9exkfs5hhxMp7BtfkIJ6YhpzotwFqLsHTyoO/3jchX85flOkiRsO7sD2K65CE8Qq/IgDDHH+85IfG0Tl8dx2owP9E3wyPLu9zXK43y7ZLxfA4YtbjXgVD3agtomG6CppYNAh+yLfTUh1pOS0p5SOsgu9EjRxhOedMa0qY79KQccbbUteBRb5SFx+JB0FMikfLRyBfR7/PAZ/WM5o01uGnZDZarYVY5XUUTE9gCdhoOLCjwSH+JCY8FER+R2Mrh5c+Vm2jwN++wutYAXdoifqQ7hA7FHLXBGxKMBMDdl9NLLzNkfOQ1rWF3rXkGasJqzH8RqtjrTjDND+p4f/CsvK/Xq3q9xk2pKtGrCIhH3ofZ39H+sdHAqAFV4hcgMiExbBHHpI3EZEJeeEpVnkCVZ6UjAu7//W9KBO1fh2Uua+m8HeCtpxqdjn7YI4hDzlqw0xNmn7evc99W+jpTD8inEB6wMwF4IWXzh2LdmjA/w1vNrBB/grktamg0RF9ySleE9DCEPhNL89yX2f9zfoXzMkV3kAOnErG6SLVhwxcpGD7en5nT+2gk1pzPXJgh/bD/wVRNp9O6vOTL1AAWpePc3hez0t61D1sFUGHlD1YHG9OvTW7FB9Md6BnsHpSxwDlJxyy/9WTaHXmsCffuPVhtJP80M//lQFW7AS6LXZbNLP1x0NkOGrtxa4Ji3cMIkD1dGZreeTPewkd7Py8N98gW5s9sBIJXQ1CtxLUm+wcAAamzrsTQXjeeDTTj1NKBdEqDrMehrWTeJJNTkzZknjwXLwgfom+wUD/pPgtLsJAlA6YA5Y5IQWTjHpp36QR/5RMMQeCp4Qv1UQ2la3S22yfIUpcrDSeOIv5eorczlc86fLnrQkQqzM+H5P9Z5hpxo6XkQ0P/UzUOgVlbnHLbksYct/wAbC2mp9HUIdZU2ttS1xSZ76qKCWm5jd3mEb8LLtKrx/GcZbW2ChoGnI4VwCjvIoh+A4r9rnZD0ltHjCMADkJeU0c8gHBtwlUXy2Ilruh/e8VBkT4IjsaKCZQ3dSVNfvrNGqMPhexl9zUjOSL00itRvfkDq4X9GKmuTNJaU8jD4qC89VS9/p4q92lSUsXgq5DIM+9cDTC5QJevxcG8pD0NWR2vumLWpSrWTk3/mK0zfFFTHRIr0cNsGjz5mccPy1O9IQn36fScB31boBCEpPd8orTYYz1SSRu1qkCYMjpSoPTdh7RhGZLJSnW5fc56aoCQMobxIgnRBZW66NAmQ1ATSMmz906rRLFSq6Ui00GkfRbhJ6/xHe8UcI9ZNH1arOtRgr++s5M4NephPeBHOwZ+UJ9Df/fvwZmJn35DOzjmxw9A9NLt+CB2Fut9gbVf15K5MkwtIE1BYd4nhFOWOER7GifGGMaS0o95tryRjlGZ7ZRh6kHyf6FnTOSd4TKh7h02dU3aQ+U+oIR+wGVL5J3j4efe6KaQZi5sAxV0sfwd+Syq8ynx2876BfFX0YD0YzmYH/JaV6OuHPR6hTsTBebBXCOexPDrmLLfpcoM2Y1SikD4qDZhucJQEliQJT9+xk9XsFbejj3KWcMAFJRUeUnEWnJHbxnYSiqcCIdsokqRdLW33HRDq3uZMXtgC0AHhEdzjopxxCQ8/z8ZXXRG33ef3CA9/Cf6Ut031H/QdqJ7WsCT1lCG8ubuFuj043+M/OD8fYpFXf/vGT0CiIEvhwfXAKcgT/QLKjkeIXdrPiNiDZ9WzhG1jwE84pI3dYXire9fPzFca7cK25Erfbvmr+NohdB57i8FtYQIZcRuF8HGIo89vGTlcPpKH0jpy/uLJB4adj+JRPrcaHAQPdxH4xYvgaa+fMux8EzEdrB04gfPQ7V4/Q5czwNqmldFidqQMzYB8sZGGZm5B31lbCir6Nh2/xbLSa04yK31tPnOiW9aBnUvXJaF+im9gfRLVfo9ejHaItLSIgwFcH1meY/q+uOwvDo6s0aOhO/fCJS8zeenBppBn9Va8xoH+Huf/1eDRkI3e/CCuMwcHQ46ValWPb14mGJKqW0j/ix7nJE9uxlZJJM6tffluRRIC9Mp9piFy6OCx6WkbZzA0wFCimTDyngU6xSD6rK305zWAzN7UjK2LtBetyxfYBRHiUfp74KIJOOivGb54oRh6oCfTPUM4vX8px72ILyi7xO1oy9qaQhxeaoFjAr4Ysstno3rpMxi78FZ9YXWV0aq9Qzo6WoXuii0PypPoK7+zLllQlrozGbX4PDTl+VIq29Nm3EekHdlik85TKp3cFo9Qh3cWghVUeobUMWB70BZBDBujh9Ak3ZrSBOA/4EYn+XJ6SxhXGjJ9vZKbFrFwPjirqVAHtPd9Nh+IfcWzGOwvdONeqXKhTmEbKXhyXaTIro4hS9OzB7J3q0udYb16cjl22HTBU2zOAae5lyqtmZBhfB4b97iV03j6/jSevo+B1Qcn8Ixxrv5Jdq7etR07IOhGMqUJJegbFNPZ7+n69EZDH6WZmG+QByOrmRPtkB05y0DBQbrrN1a+uAScMiw2LZE0XYSBlbeuOGdXCBhYcfOwgX2pFwxsgtl3KkLdWQ6FLYRP4tMO9Iyi4AY1w7IbYkwqo/cDkxWaC7hTE/R16fo6voz+CaxFRYAWPGbwVOjEuRy8QRMGHcakDpRIqAtz7JaCB+XiMvrAHlNVc8roL/eYfWYWuOs/23Nup3nzHtZpVhi95kpTbg35zqwH8x6UE2uXurlMjqutTsfpPXkCloeXxvwBpxTkxJZCdhUIdAaFziFhmw0XFcdoE9kkYo9HiXqSDKVhohu9N8xdrnyksxsVfllGP9o9ZN6o4Gs550KFjthZ40KF5865UOEiQPvf3acgnUffemm4OtK+AevSYgxQgrzvU+mE4dPwddH7vtxilz+3fJnBd/C6kwRfIS8nsT67LR+qYYzZWyfNSZcSAaC9Xo9ds17oHO6ZUSuwBT0Tcq9uRyOjvMTu9RHdwpPgmYF2XDLCDhpiMLja5ajhJx4073YxzVUHm5NWxaM/NBjrXmJXtbipVzEsxj+5BAt3co4ayxR4hG3g1611k4SicjWCa1/SzUVSQZE0q0i6qEgqLCqSxhcJ4c244BneqBtHa7XclgR2hvrRYfA4BE8zwmMxPNEI4/WkeDB5o3nZaXGkOr1cfxNfafqfrXu3FpMCXhnwSND4JoL+D0wGP2BVdEgDVzbaXehRjnzeHdyqtDlUf7Q8shTtG6MQCSPDxu1cW7YyQ27cC/Ymwqn3LQBdhyc206ybulLKqOP3J5nB4fVr6P3/wS6wMabA35V+ePMWXnQ12B0cGLlgi8GMi6a06ThA2PK4vGQY9CG724yv+Dhewe6ru/8qjOpKzd8z3lNs0EG03zK0gRE0nPnGkV4+/rQNX7JVth2v8uo84t3v7Xsbr/DKFdPkubmlHvn+Ttqxz7hXT8Bbgo07HNxjbCZfFwDwp7btdmvbtm3btm3b3tput263bre2bdvt2/87yS+5c5K5mWQuzpkP9zFjSIBja5yV4E2X6EMd/prmigd/BO1Mxz8rJ37Ml3hMmYFz8Btoj//UpM1ZUIhzqPiFpNSdF17QXt/ww1AMbkEtL9A9UtUV/5rqkYELWLB30EcYeg6aULrFtN2vTSdqNNBu1lgCSt7KFb8OcAA9Z+XAuEQV5LRGpr+yWiTbKjEGHDRs8IHOU3si0uiha8Jlib/qzXa8gaXYq/14jdSKRpqeMLVGfPEL1p+aUkrB0EAFdAtR/Z1TjnDB6u3RIzOrTOcxX2kocK2ptbx2It0DQXhdBz8Mnkofy8GGB8zvTllOZzRe5bHnTmr0a7zRg1fPtr4ymjp6tDuxsiib3Z7snklgwC6KppG3xodtcRbSjEXJrurThmpkcecJp2GfbxluvDYPDIlyAyfrLFbN5Hqcf6bobX0Aysydyo2i8wEk//EaYRv5alFnfNiBnvw+Jjx5jbf48HRmIer0HfN0jT7xyrc2OyXeC52IeJXA85me40bTRPJP+gHXVECnkJNzldeSzATt5SwdQJ0Hp0HjYWX0k83FfKrakbLD1tYoeiU0tj0i5ancOLL3vMe3sjf6Zb0fEu8EipOKTgYwdefbUHkA6ZCyeRab5yNacbZHot0ffapgNpeVG2X67KpWksXkFRpLYBDxogHN0zQUjPRKYRlaPhnmwCYcDhtq8HfVZlxUcxHo1+Vu31OyLkQPaG2B9S4d7eXZNw7Uk0ga/7J0l8n1Q3wfedjLfp9F1EahV6TPTR9Gx0qRyiOHSrvxPpBOaayvYfwLhF9S9/JyTyK5esVcMsX0ev7FYcqf+7D3PRM2pi4WJY7KxvHqceR12TiBjdVO2IYgNoGe3VuhzeCVwq97q0qSyaKqU5iirDQqb2/ohoCtz1XvGqsOqiT2Wfbm4VPuYNeZfrbWg78notnQi6xD1ZWsbHVX3ECsrCba5zdn0QtVo+Kiz77ARSBqvBhcEStxmuolQrKxCwiSkyHAYkfZh9Go62GHn/4CG0SdzzeNHlBePDH02wcsL2j4ryDsG5V6FY/7ZO/YyMwc+CWE3+QPxnewBjP9K4OLLjzzOwb1a6rdHDGv9PXtGKsfRqjZ4Q77K8MS9K8Wb3rBY/aAJGBjJ1A1PNA4BB9LR63FhobP3r8V7B3AiymRj33Hg9tr256COCs8BhQlycVmQBykK1U5U+nKkf4IlLwlahyLDVqNTlzKbkAiuSYu/m1zz1f4rO+f238Lpt6+CwUnGeHOqr/bsBY0v/XZy52/srEXOP8V6H1tbxYcMQd7vXKCs373Ngjm3u+Ds1732ilc6/DaKBiqvNNu8VLKF9/nNZu15F0anjt7fGt42iXo8+fpceCqD+yxrK6n
*/