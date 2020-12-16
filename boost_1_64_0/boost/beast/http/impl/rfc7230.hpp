//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_RFC7230_HPP
#define BOOST_BEAST_HTTP_IMPL_RFC7230_HPP

#include <boost/beast/http/detail/rfc7230.hpp>
#include <iterator>

namespace boost {
namespace beast {
namespace http {

class param_list::const_iterator
{
    using iter_type = string_view::const_iterator;

    std::string s_;
    detail::param_iter pi_;

public:
    using value_type = param_list::value_type;
    using pointer = value_type const*;
    using reference = value_type const&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;

    const_iterator() = default;

    bool
    operator==(const_iterator const& other) const
    {
        return
            other.pi_.it == pi_.it &&
            other.pi_.last == pi_.last &&
            other.pi_.first == pi_.first;
    }

    bool
    operator!=(const_iterator const& other) const
    {
        return !(*this == other);
    }

    reference
    operator*() const
    {
        return pi_.v;
    }

    pointer
    operator->() const
    {
        return &*(*this);
    }

    const_iterator&
    operator++()
    {
        increment();
        return *this;
    }

    const_iterator
    operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

private:
    friend class param_list;

    const_iterator(iter_type first, iter_type last)
    {
        pi_.it = first;
        pi_.first = first;
        pi_.last = last;
        increment();
    }

    BOOST_BEAST_DECL
    static
    std::string
    unquote(string_view sr);

    BOOST_BEAST_DECL
    void
    increment();
};

inline
auto
param_list::
begin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
param_list::
end() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

inline
auto
param_list::
cbegin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
param_list::
cend() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

//------------------------------------------------------------------------------

class ext_list::const_iterator
{
    ext_list::value_type v_;
    iter_type it_;
    iter_type first_;
    iter_type last_;

public:
    using value_type = ext_list::value_type;
    using pointer = value_type const*;
    using reference = value_type const&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    const_iterator() = default;

    bool
    operator==(const_iterator const& other) const
    {
        return
            other.it_ == it_ &&
            other.first_ == first_ &&
            other.last_ == last_;
    }

    bool
    operator!=(const_iterator const& other) const
    {
        return !(*this == other);
    }

    reference
    operator*() const
    {
        return v_;
    }

    pointer
    operator->() const
    {
        return &*(*this);
    }

    const_iterator&
    operator++()
    {
        increment();
        return *this;
    }

    const_iterator
    operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

private:
    friend class ext_list;

    const_iterator(iter_type begin, iter_type end)
    {
        it_ = begin;
        first_ = begin;
        last_ = end;
        increment();
    }

    BOOST_BEAST_DECL
    void
    increment();
};

inline
auto
ext_list::
begin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
ext_list::
end() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

inline
auto
ext_list::
cbegin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
ext_list::
cend() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}


//------------------------------------------------------------------------------

class token_list::const_iterator
{
    token_list::value_type v_;
    iter_type it_;
    iter_type first_;
    iter_type last_;

public:
    using value_type = token_list::value_type;
    using pointer = value_type const*;
    using reference = value_type const&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    const_iterator() = default;

    bool
    operator==(const_iterator const& other) const
    {
        return
            other.it_ == it_ &&
            other.first_ == first_ &&
            other.last_ == last_;
    }

    bool
    operator!=(const_iterator const& other) const
    {
        return !(*this == other);
    }

    reference
    operator*() const
    {
        return v_;
    }

    pointer
    operator->() const
    {
        return &*(*this);
    }

    const_iterator&
    operator++()
    {
        increment();
        return *this;
    }

    const_iterator
    operator++(int)
    {
        auto temp = *this;
        ++(*this);
        return temp;
    }

private:
    friend class token_list;

    const_iterator(iter_type begin, iter_type end)
    {
        it_ = begin;
        first_ = begin;
        last_ = end;
        increment();
    }

    BOOST_BEAST_DECL
    void
    increment();
};

inline
auto
token_list::
begin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
token_list::
end() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

inline
auto
token_list::
cbegin() const ->
    const_iterator
{
    return const_iterator{s_.begin(), s_.end()};
}

inline
auto
token_list::
cend() const ->
    const_iterator
{
    return const_iterator{s_.end(), s_.end()};
}

template<class Policy>
bool
validate_list(detail::basic_parsed_list<
    Policy> const& list)
{
    auto const last = list.end();
    auto it = list.begin();
    if(it.error())
        return false;
    while(it != last)
    {
        ++it;
        if(it.error())
            return false;
        if(it == last)
            break;
    }
    return true;
}

} // http
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/impl/rfc7230.ipp>
#endif

#endif


/* rfc7230.hpp
stfy+q1+NqbHulqwf+sdLr2OYD1+T4weazidu29RJ/XKOqkX6aTezmPoLXLbr5N67Z3U6+ikXvbSzukVdVKvLIlegfov77vU9l9OfePqRPgrB/sqkwZ2DvZXJv1LM7vts9xdf+Xq0l4nxWf5ZPkr/y/5KnfWTzn89kyrEClDtiC7kEeQg4hVzrevkBIkgtyMPIAcQF5CsiuwE9KC7EIeQw4hmZWkiZQi9cgOpA1pr0z5NaeON+eRhjS9Ifz/puqmyoZqcQCwrG75ANg8/xoXz39kyMsbt5x9GD2c5frGymrNRDmv8K3O8fxfAfeHur7e4r/uEbSO1/V1GP91p6D1t6D1va6vs31Kvgk85vSb922/a9ahP+zI+cr481+6qevrhP7rWkHrgUHrnEHre8HraX+ylA/sWg/J5A/MbPZ6rdfnqQ1gfg8r6ZwteL7mnau9hOgczT0303mY7xzMd961yjXfOozY86ypCHOrhG+H7kFi8yhQ504jF5g5E3Ol5POjYsRnTiRzoWqd+zDn8cxxdG7jmdOs9sxj/OYwnnmLzlk88xXvHMU7N9G5SPDco1TnHH7zjeC5BmmXeOYUZj7RkfptTx2pI3WkjtSROlJH6kgd/0XHG+f/b3/4wH767/6z/9vyLPPNndJQop/772wf/7OzLK+Pvzz/R5rqNpGP8nUbG6pa6hob/L5VRdyu+ba7vlVl8nVY8+U8HfTSfBUF5GvjWk+2/PKlcTOPK1/nab5aeyTm6yXyVZyQL+oXV5+6GtvjB1JvkrwVdyNvzjpOtfrdP4WMQuRdLS/oyzx5M/VYCWUSo3m+YWL8LrZKnDs1f04ak6wc890F29511YYnbnQmmG9FbJLwvRLnsHwbZ2OdfLWjsdr4RTeLzgMSLjNp4M9nfNaroLOvraxaj19RS6Xx7YiI3sMSvsDEyxee2TNiDbu/xPxkfi3XJ2oYL49iOzyY+1wyIM3xB1NZk9317xDler49Z2wj58tAys/5WPmHe77zEFdGfJR+Kfkl38Rz13FJhu7FrHX8Da3jiuKEOqZP1NdVSRX71/FNEucup45JI3kdo+Op4xskfN8x6/ha0fmMU8ek0bk6bhW9L5o6Jt4x6/jvxd46HrfgzV3HR4u1juO+UWXpHgYFXBwF9gc70IksiK/j+EHGv55vk3i/03p20pkkur+TOms29cs1T/3eIuE/i81fnhitq/LqBlO3H5Lr/zB1S3zjq3wgT/irdsZMne6U6z1DWqfox+p05FDRl0p17z2AjtkzIELYbmu/nyi6jS21sn+D0S+K04cH6tc2jf7sOH0WLoPapYlTHBfnRsKjaWNE0W8PmjammNyvt5/nWzDUnbYd6odws/lG4csSljow3yjEzpwTOxsfemzJObGl8aH/vcQ1NpPzrQHt9sZjtNttC6Pt9o9x3+872Dvx22pfoQIPoe/ayydoLuH3LS2N20fq5NdSh3ZcO2r5Ote4hN7xfWttuO6nQ9qE3Wl7y9amheqriYW1bB3esgXNR3zKpnFJMcdTNqJyey2Xo9PlcuV6y2XSFb8yLdOOrMQy/d7ucPF7L/mONceuN9IwZfujKRtJxMqGTvfKRrqETbqd4nufKF53V/nb/+3f4XlR3lt9J6P0iu0dr/9zxD8jBVP6X1mS+g7PZW8Q39vwpc8O/u4L2GrjeOUvT3DzpTVepk+8SRpvMtgLnOLmSx8j3qkar0jjnabx9iBlGu8pjZcD3uniS08C54LTwHnKc56v/MWzledcDC63vN9JWa+8sQ3gErBJ+ZBXKh/y3eBbwJuU/3grWKr84vPBr4LLlce6wuRX55bgMz75vUjz+1bN7yWa3zWa37drfss1vxU=
*/