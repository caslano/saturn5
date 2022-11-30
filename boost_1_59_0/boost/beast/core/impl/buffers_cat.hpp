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
# define BOOST_BEAST_UNREACHABLE_RETURN(v) return v
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