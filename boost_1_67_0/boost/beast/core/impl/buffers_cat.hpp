//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_BUFFERS_CAT_HPP
#define BOOST_BEAST_IMPL_BUFFERS_CAT_HPP

#include <boost/beast/core/detail/tuple.hpp>
#include <boost/beast/core/detail/variant.hpp>
#include <boost/asio/buffer.hpp>
#include <cstdint>
#include <iterator>
#include <new>
#include <stdexcept>
#include <utility>

namespace boost {
namespace beast {

template<class Buffer>
class buffers_cat_view<Buffer>
{
    Buffer buffer_;
public:
    using value_type = buffers_type<Buffer>;

    using const_iterator = buffers_iterator_type<Buffer>;

    explicit
    buffers_cat_view(Buffer const& buffer)
        : buffer_(buffer)
    {
    }

    const_iterator
    begin() const
    {
        return net::buffer_sequence_begin(buffer_);
    }

    const_iterator
    end() const
    {
        return net::buffer_sequence_end(buffer_);
    }
};

#if defined(_MSC_VER) && ! defined(__clang__)
# define BOOST_BEAST_UNREACHABLE() __assume(false)
# define BOOST_BEAST_UNREACHABLE_RETURN(v) __assume(false)
#else
# define BOOST_BEAST_UNREACHABLE() __builtin_unreachable()
# define BOOST_BEAST_UNREACHABLE_RETURN(v) \
    do { __builtin_unreachable(); return v; } while(false)
#endif

#ifdef BOOST_BEAST_TESTS

#define BOOST_BEAST_LOGIC_ERROR(s) \
    do { \
        BOOST_THROW_EXCEPTION(std::logic_error((s))); \
        BOOST_BEAST_UNREACHABLE(); \
    } while(false)

#define BOOST_BEAST_LOGIC_ERROR_RETURN(v, s) \
    do { \
        BOOST_THROW_EXCEPTION(std::logic_error(s)); \
        BOOST_BEAST_UNREACHABLE_RETURN(v); \
    } while(false)

#else

#define BOOST_BEAST_LOGIC_ERROR(s) \
    do { \
        BOOST_ASSERT_MSG(false, s); \
        BOOST_BEAST_UNREACHABLE(); \
    } while(false)

#define BOOST_BEAST_LOGIC_ERROR_RETURN(v, s) \
    do { \
        BOOST_ASSERT_MSG(false, (s)); \
        BOOST_BEAST_UNREACHABLE_RETURN(v); \
    } while(false)

#endif

namespace detail {

struct buffers_cat_view_iterator_base
{
    struct past_end
    {
        char unused = 0; // make g++8 happy

        net::mutable_buffer
        operator*() const
        {
            BOOST_BEAST_LOGIC_ERROR_RETURN({},
                "Dereferencing a one-past-the-end iterator");
        }

        operator bool() const noexcept
        {
            return true;
        }
    };
};

} // detail

template<class... Bn>
class buffers_cat_view<Bn...>::const_iterator
    : private detail::buffers_cat_view_iterator_base
{
    // VFALCO The logic to skip empty sequences fails
    //        if there is just one buffer in the list.
    static_assert(sizeof...(Bn) >= 2,
        "A minimum of two sequences are required");

    detail::tuple<Bn...> const* bn_ = nullptr;
    detail::variant<
        buffers_iterator_type<Bn>..., past_end> it_{};

    friend class buffers_cat_view<Bn...>;

    template<std::size_t I>
    using C = std::integral_constant<std::size_t, I>;

public:
    using value_type = typename
        buffers_cat_view<Bn...>::value_type;
    using pointer = value_type const*;
    using reference = value_type;
    using difference_type = std::ptrdiff_t;
    using iterator_category =
        std::bidirectional_iterator_tag;

    const_iterator() = default;
    const_iterator(const_iterator const& other) = default;
    const_iterator& operator=(
        const_iterator const& other) = default;

    bool
    operator==(const_iterator const& other) const;

    bool
    operator!=(const_iterator const& other) const
    {
        return ! (*this == other);
    }

    reference
    operator*() const;

    pointer
    operator->() const = delete;

    const_iterator&
    operator++();

    const_iterator
    operator++(int);

    const_iterator&
    operator--();

    const_iterator
    operator--(int);

private:
    const_iterator(
        detail::tuple<Bn...> const& bn,
        std::true_type);

    const_iterator(
        detail::tuple<Bn...> const& bn,
        std::false_type);

    struct dereference
    {
        const_iterator const& self;

        reference
        operator()(mp11::mp_size_t<0>)
        {
            BOOST_BEAST_LOGIC_ERROR_RETURN({},
                "Dereferencing a default-constructed iterator");
        }

        template<class I>
        reference operator()(I)
        {
            return *self.it_.template get<I::value>();
        }
    };

    struct increment
    {
        const_iterator& self;

        void
        operator()(mp11::mp_size_t<0>)
        {
            BOOST_BEAST_LOGIC_ERROR(
                "Incrementing a default-constructed iterator");
        }

        template<std::size_t I>
        void
        operator()(mp11::mp_size_t<I>)
        {
            ++self.it_.template get<I>();
            next(mp11::mp_size_t<I>{});
        }

        template<std::size_t I>
        void
        next(mp11::mp_size_t<I>)
        {
            auto& it = self.it_.template get<I>();
            for(;;)
            {
                if (it == net::buffer_sequence_end(
                        detail::get<I-1>(*self.bn_)))
                    break;
                if(net::const_buffer(*it).size() > 0)
                    return;
                ++it;
            }
            self.it_.template emplace<I+1>(
                net::buffer_sequence_begin(
                    detail::get<I>(*self.bn_)));
            next(mp11::mp_size_t<I+1>{});
        }

        void
        operator()(mp11::mp_size_t<sizeof...(Bn)>)
        {
            auto constexpr I = sizeof...(Bn);
            ++self.it_.template get<I>();
            next(mp11::mp_size_t<I>{});
        }

        void
        next(mp11::mp_size_t<sizeof...(Bn)>)
        {
            auto constexpr I = sizeof...(Bn);
            auto& it = self.it_.template get<I>();
            for(;;)
            {
                if (it == net::buffer_sequence_end(
                        detail::get<I-1>(*self.bn_)))
                    break;
                if(net::const_buffer(*it).size() > 0)
                    return;
                ++it;
            }
            // end
            self.it_.template emplace<I+1>();
        }

        void
        operator()(mp11::mp_size_t<sizeof...(Bn)+1>)
        {
            BOOST_BEAST_LOGIC_ERROR(
                "Incrementing a one-past-the-end iterator");
        }
    };

    struct decrement
    {
        const_iterator& self;

        void
        operator()(mp11::mp_size_t<0>)
        {
            BOOST_BEAST_LOGIC_ERROR(
                "Decrementing a default-constructed iterator");
        }

        void
        operator()(mp11::mp_size_t<1>)
        {
            auto constexpr I = 1;

            auto& it = self.it_.template get<I>();
            for(;;)
            {
                if(it == net::buffer_sequence_begin(
                    detail::get<I-1>(*self.bn_)))
                {
                    BOOST_BEAST_LOGIC_ERROR(
                        "Decrementing an iterator to the beginning");
                }
                --it;
                if(net::const_buffer(*it).size() > 0)
                    return;
            }
        }

        template<std::size_t I>
        void
        operator()(mp11::mp_size_t<I>)
        {
            auto& it = self.it_.template get<I>();
            for(;;)
            {
                if(it == net::buffer_sequence_begin(
                        detail::get<I-1>(*self.bn_)))
                    break;
                --it;
                if(net::const_buffer(*it).size() > 0)
                    return;
            }
            self.it_.template emplace<I-1>(
                net::buffer_sequence_end(
                    detail::get<I-2>(*self.bn_)));
            (*this)(mp11::mp_size_t<I-1>{});
        }

        void
        operator()(mp11::mp_size_t<sizeof...(Bn)+1>)
        {
            auto constexpr I = sizeof...(Bn)+1;
            self.it_.template emplace<I-1>(
                net::buffer_sequence_end(
                    detail::get<I-2>(*self.bn_)));
            (*this)(mp11::mp_size_t<I-1>{});
        }
    };
};

//------------------------------------------------------------------------------

template<class... Bn>
buffers_cat_view<Bn...>::
const_iterator::
const_iterator(
    detail::tuple<Bn...> const& bn,
    std::true_type)
    : bn_(&bn)
{
    // one past the end
    it_.template emplace<sizeof...(Bn)+1>();
}

template<class... Bn>
buffers_cat_view<Bn...>::
const_iterator::
const_iterator(
    detail::tuple<Bn...> const& bn,
    std::false_type)
    : bn_(&bn)
{
    it_.template emplace<1>(
        net::buffer_sequence_begin(
            detail::get<0>(*bn_)));
    increment{*this}.next(
        mp11::mp_size_t<1>{});
}

template<class... Bn>
bool
buffers_cat_view<Bn...>::
const_iterator::
operator==(const_iterator const& other) const
{
    return bn_ == other.bn_ && it_ == other.it_;
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator*() const ->
    reference
{
    return mp11::mp_with_index<
        sizeof...(Bn) + 2>(
            it_.index(),
            dereference{*this});
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator++() ->
    const_iterator&
{
    mp11::mp_with_index<
        sizeof...(Bn) + 2>(
            it_.index(),
            increment{*this});
    return *this;
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator++(int) ->
    const_iterator
{
    auto temp = *this;
    ++(*this);
    return temp;
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator--() ->
    const_iterator&
{
    mp11::mp_with_index<
        sizeof...(Bn) + 2>(
            it_.index(),
            decrement{*this});
    return *this;
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::
const_iterator::
operator--(int) ->
    const_iterator
{
    auto temp = *this;
    --(*this);
    return temp;
}

//------------------------------------------------------------------------------

template<class... Bn>
buffers_cat_view<Bn...>::
buffers_cat_view(Bn const&... bn)
    : bn_(bn...)
{
}


template<class... Bn>
auto
buffers_cat_view<Bn...>::begin() const ->
    const_iterator
{
    return const_iterator{bn_, std::false_type{}};
}

template<class... Bn>
auto
buffers_cat_view<Bn...>::end() const->
    const_iterator
{
    return const_iterator{bn_, std::true_type{}};
}

} // beast
} // boost

#endif

/* buffers_cat.hpp
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
*/