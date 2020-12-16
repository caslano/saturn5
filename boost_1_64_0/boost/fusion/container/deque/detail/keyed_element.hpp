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
8Odbdo7fyfrnQvI0RcppImGr8rl4v748Lcle4Uafb5Nzsf6bsPJf7N0JXJRlHsBxVDS1MkW88AAV7xtRUclQRDFRUVBx1WAEFFbECQbvA8v7xNK8DY/USpPMg1YrKivdaqXW3azcotqOLXej1sptrfb3zvx5fWfed5gZJXfbZj6fZ78rve/7HO/z3s9hLSe245Ce1dKefxKRN8aJuJX1zYbp0Xbocm+M05Xvl3+Orm9/jpb+PdfGvQ2urY57azhGaX27++Icy+QwW78kybd6/+hYN5Kk7X2a9BFIJij57lriKt+JSpfGG6qzRnmN1eXVeI6uts7viSlw/XliO/EXGeRJ2s5xlrixej7TjXOE2kZN0nerjKVVDXeyvs8HdulLzko1WVLVudBcj5Gs1DPTh1LP2DdSd3Rlj4xTXjYPAbNyqftE367SeO40x3HEZQxl2Q93y3NjmJRmPPkLwXDMJy15H2nzad0HDFodr+yGmemWtGuXZznWN6P8DMcEX45lY7Lv+5hta+a+yFePCVN2ZjfrvraWC895KPdDss8K1L/l8EdbHgv113d13Ptd1nKVpHNoZGnutWSs6UT2g7RtVP+mjtle17pda/Ujvmv3Os/7Wf8+zXEs9UIpz5GSzhjCWf5P7ifWPCsp4MG2e7eyc3ZDF+0Hg9Rj7Vra4drcH6gd+zlW2tRHE5pIG4PZyvXXFj83F3b3BTd0ni7rH6jOuaA/ntR0XZV0LZdryf2E5mwz9lM1Xeq9gDv3oUo92vSpe8+cmjQ5tJ21Rem4D49Km/2dMo7jFsKMUOWkoKZVzkeu0+luumzXG6xmX9/T5G9S36WNq1ov7cYlz68r3/BJZCv8EPcQbzHplnno1Am5UmdygUi32OY2dHHsmjXH7qzP7cs8z8d+fPIA/rbZds5RxycnttQUGfs7wWBMf6lP2jHwpd5pxvN3aLd7UD7QRcj7rr74iFKfvlDzqkwDxSRotjyrGXZjHHsln+Mvqfk0GLP82pwis+yfexzHu5e8Gb0fM56r4AD5Gsy/b7XGL/XHvozVMcs7S1kES9v+FnLOaUqwcGEtsW1jyjRqqyftlbM6KnElxrOWdRz87yQtMzvazwO2XOJtQLhd4h6jtGH9ezPtfHR0qIyKtO2BzJyMDNfp0Nbpq/X08149qtz7GMXh4Txz+53Ms7e6vr5NeAL5SjKKU20Q7n68Pxq0B69RR9ceXC0D/wb69PyG9OQbpycnO+360mKrq+r9hSXLYV9sb6Cfj+tx5RnFKB0ezr+33425B8uOfd+G+np3MJQt/qOZ8TyIHta9snqQZ9A34AniiXAWj4dln9ddn+featnbp+WyQZ4Pk5Zc0qKb+9DD/Jbt33mN9Pl9kjjyjeLwMK+L9Xnl/Cd5dbiHudRIf8w/pdSza+kYE5s4bKCn/TAsocbzSsYE6Mv2KMvW/tI+PrVY3YhTm59TAfr8FLL9rrrt50zzZB6746HG8/dFNNbvx9+xbJJ9fLZd6EF8FoNj9Kif8T483Vh/rjil1CWHNFhPEx6cO4+7cZ5Q92sTfTk8q9Qj0qCfM9NaGm6nY2w9XTq4fzE+dk830e//olC2WNrMsI+Rp/Wgj5PrWGxT/T54IZS/O4nX033Rx419EVJ2DDQ1nr8yr7RZhc9fObCZ8fyVRaXNbur8lWeaGc5fSWPFZj/7/JXtJQ3hgfp7w2HKnFG2NHBn6H7+h/rb3xeOtW6D+uRvf9wVSJxzJM4c+S5mljizr73bSc5INWXmmK/vfaG2rIOCpD+GfKPqIXHW/loXJ48BrscCcvpNTOIzN7ctXMTG/fAkvsiySXbx2SYDlC9xbj17GL8P0s6Vqb7zdZwnrLw=
*/