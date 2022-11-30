/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_DETAIL_KEYED_ELEMENT_26112006_1330)
#define BOOST_FUSION_DEQUE_DETAIL_KEYED_ELEMENT_26112006_1330

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && BOOST_WORKAROUND(BOOST_GCC, / 100 == 404)
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;
}}

namespace boost { namespace fusion { namespace detail
{
    struct nil_keyed_element
    {
        typedef fusion_sequence_tag tag;
        BOOST_FUSION_GPU_ENABLED
        void get();

        template<typename It>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static nil_keyed_element
        from_iterator(It const&)
        {
            return nil_keyed_element();
        }
    };

    template <typename Key, typename Value, typename Rest>
    struct keyed_element : Rest
    {
        typedef Rest base;
        typedef fusion_sequence_tag tag;
        using Rest::get;

        template <typename It>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static keyed_element
        from_iterator(It const& it)
        {
            return keyed_element(
                *it, base::from_iterator(fusion::next(it)));
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element(keyed_element const& rhs)
          : Rest(rhs.get_base()), value_(rhs.value_)
        {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element(keyed_element&& rhs)
          : Rest(rhs.forward_base())
          , value_(BOOST_FUSION_FWD_ELEM(Value, rhs.value_))
        {}
#endif

        template <typename U, typename Rst>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element(keyed_element<Key, U, Rst> const& rhs
          , typename enable_if<is_convertible<U, Value> >::type* = 0)
          : Rest(rhs.get_base()), value_(rhs.value_)
        {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Rest& get_base() BOOST_NOEXCEPT
        {
            return *this;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Rest const& get_base() const BOOST_NOEXCEPT
        {
            return *this;
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Rest&& forward_base() BOOST_NOEXCEPT
        {
            return std::move(*static_cast<Rest*>(this));
        }
#endif

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename cref_result<Value>::type get(Key) const
        {
            return value_;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename ref_result<Value>::type get(Key)
        {
            return value_;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element(
            typename detail::call_param<Value>::type value
          , Rest const& rest)
            : Rest(rest), value_(value)
        {}

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if BOOST_WORKAROUND(BOOST_GCC, / 100 == 404)
        template <typename Value_, typename = typename enable_if<is_same<Value_, Value> >::type>
#else
        typedef Value Value_;
#endif
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element(Value_&& value, Rest&& rest)
            : Rest(std::move(rest))
            , value_(BOOST_FUSION_FWD_ELEM(Value, value))
        {}
#endif

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element()
            : Rest(), value_()
        {}

        template<typename U, typename Rst>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element& operator=(keyed_element<Key, U, Rst> const& rhs)
        {
            base::operator=(static_cast<Rst const&>(rhs)); // cast for msvc-7.1
            value_ = rhs.value_;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element& operator=(keyed_element const& rhs)
        {
            base::operator=(rhs);
            value_ = rhs.value_;
            return *this;
        }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        keyed_element& operator=(keyed_element&& rhs)
        {
            base::operator=(rhs.forward_base());
            value_ = std::move(rhs.value_);
            return *this;
        }
#endif

        Value value_;
    };

    template<typename Elem, typename Key>
    struct keyed_element_value_at
      : keyed_element_value_at<typename Elem::base, Key>
    {};

    template<typename Key, typename Value, typename Rest>
    struct keyed_element_value_at<keyed_element<Key, Value, Rest>, Key>
    {
        typedef Value type;
    };
}}}

#endif

/* keyed_element.hpp
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
*/