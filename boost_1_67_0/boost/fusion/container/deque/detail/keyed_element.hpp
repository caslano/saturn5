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