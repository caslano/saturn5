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
rReMElu1KVOvw8b0QAiQfY7jG4n3XfA/0x/mfHu2XFUgKhtVzbEMj9MUC2DwhXraAi7w7MKhhZUM96fdG4m3wPgx9iWAhjCaDtGcJDzSC0VnzYD6xlVMU7byri71gPJnywaTGXeukwMBryaDF1J5r5lkAnhWIFNUNj7isuD2/AOAun4+FTF6OPveUHrgjybJiIp58fIzKGFirEHc6hIeXWgG5tHxFSte/ZgylxtNXnspecp1kjoPCUiO3oXK4pBSuTbYAkh4I7WqA5mEVY+GgqHCeQLPCutHogWYPbUAu4eUiNtNaCCdnYY98Wq+SdGcuCYpI5kMbicEf2JX+ICuJhQuJJd675YxmuPxbqBJ3/vAmUs9e0kMFhsVWTjuuqqsBb654Ok8VUC/ow5w71KiGucS80V0S+rI5M2aB5yPJjCJ/2nIN+XLvEANgQ5LcO7cSWUTxRX8AV68XUXTOA5P+2gSWhcECFowcdVsg1xj1gs2EB3IGHavbi6LPOvl9clGMZfUM8XEHK5Rgrfm9Vs6ehAoUn8BiatM+panVZ3TnEv+5+OyARHKoepxiA==
*/